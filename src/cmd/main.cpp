#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>

#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/timer.hpp>
#include <boost/graph/graphviz.hpp>

#include "encodings.h"
#include "handles.h"
#include "hitwriter.h"
#include "lightgrep_c_api.h"
#include "matchgen.h"
#include "options.h"
#include "optparser.h"
#include "patterninfo.h"
#include "utility.h"

#include "include_boost_thread.h"


#ifdef LIGHTGREP_CUSTOMER
// check this out: http://stackoverflow.com/questions/2751870/how-exactly-does-the-double-stringize-trick-work
#define STRINGIZE(whatever) #whatever
#define JUMP_THROUGH_A_HOOP(yo) STRINGIZE(yo)
#define CUSTOMER_NAME JUMP_THROUGH_A_HOOP(LIGHTGREP_CUSTOMER)
#endif

// <magic_incantation>
// this ridiculous piece of crap you see here is necessary to get
// boost_thread static libraries to link on Windows using MinGW
// found it in the boost issue tracker
namespace boost {
  void tss_cleanup_implemented() { }
}
// </magic_incantation>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

void startup(boost::shared_ptr<ProgramHandle> prog, const PatternInfo& pinfo, const Options& opts);

uint64 readNext(FILE* file, byte* buf, unsigned int blockSize) {
  return fread((void*)buf, 1, blockSize, file);
}

void printHelp(const po::options_description& desc) {
  std::cout
    << "lightgrep, Copyright (c) 2010-2012, Lightbox Technologies, Inc."
    << "\nCreated " << __DATE__ << "\n\n"
    << "Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]\n\n"
    #ifdef LIGHTGREP_CUSTOMER
    << "This copy provided EXCLUSIVELY to " << CUSTOMER_NAME << "\n\n"
    #endif
    << desc << std::endl;
}

bool addPattern(
  LG_HPARSER parser,
  uint32 i,
  uint32 patIdx,
  uint32 encIdx,
  PatternInfo& pinfo)
{
  const Pattern& pat(pinfo.Patterns[i]);
  // set up parsing options
  LG_KeyOptions keyOpts;
  keyOpts.FixedString = pat.FixedString;
  keyOpts.CaseInsensitive = pat.CaseInsensitive;

  if (lg_add_keyword(parser, pat.Expression.c_str(), patIdx, &keyOpts, pat.Encoding.c_str())) {
    pinfo.Table.push_back(std::make_pair(i, encIdx));
    return true;
  }
  else {
    std::cerr << lg_error(parser) << " on pattern "
              << i << ", '" << pinfo.Patterns[i].Expression << "'" << std::endl;
    return false;
  }
}

boost::shared_ptr<ParserHandle> parsePatterns(PatternInfo& pinfo, uint32& numErrors) {
  numErrors = 0;
  if (pinfo.Patterns.empty()) {
    return boost::shared_ptr<ParserHandle>();
  }

  // find total length of patterns -- or 1 if tlen is 0
  const uint32 tlen = std::max(1u, totalCharacters(pinfo.Patterns));

  boost::shared_ptr<ParserHandle> parser(lg_create_parser(tlen),
                                         lg_destroy_parser);

  // parse patterns
  uint32 patIdx = 0;
  EncodingsCodeMap encMap(getEncodingsMap());
  EncodingsCodeMap::const_iterator foundEnc;

  for (uint32 i = 0; i < pinfo.Patterns.size(); ++i) {
    uint32 encIdx = 0;
    if ((foundEnc = encMap.find(pinfo.Patterns[i].Encoding)) != encMap.end()) {
      encIdx = foundEnc->second;
    }
    if (addPattern(parser.get(), i, patIdx, encIdx, pinfo)) {
      ++patIdx;
    }
    else {
      ++numErrors;
    }    
  }
  // don't enable these unless debugging -- will mess up enscript
/*  std::cerr << pinfo.Patterns.size() << " Patterns" << std::endl;
  std::cerr << patIdx << " Byte Patterns" << std::endl;
  std::cerr << numErrors << " Errors" << std::endl;*/
  return parser;
}

boost::shared_ptr<ProgramHandle> buildProgram(LG_HPARSER parser, const Options& opts) {
  LG_ProgramOptions progOpts;
  progOpts.Determinize = opts.Determinize;

  return boost::shared_ptr<ProgramHandle>(
    lg_create_program(parser, &progOpts),
    lg_destroy_program
  );
}

boost::shared_ptr<ProgramHandle> createProgram(const Options& opts, PatternInfo& pinfo) {
  uint32 numErrors;
  boost::shared_ptr<ParserHandle>  parser(parsePatterns(pinfo, numErrors));
  boost::shared_ptr<ProgramHandle> prog;
  if (numErrors < pinfo.Patterns.size()) {
    // build the program
    prog = buildProgram(parser.get(), opts);
    if (lg_ok(prog.get())) {
      NFAPtr g(parser->Impl->Fsm);
      std::cerr << g->verticesSize() << " vertices" << std::endl;

      ProgramPtr p(prog->Impl->Prog);
      std::cerr << p->size() << " instructions" << std::endl;    
    }
    else {
      std::cerr << lg_error(prog.get()) << std::endl;
      prog.reset();
    }
  }
  return prog;
}

class SearchController {
public:
  SearchController(uint32 blkSize): BlockSize(blkSize), BytesSearched(0), TotalTime(0.0),
    Cur(new byte[blkSize]), Next(new byte[blkSize]) {}

  bool searchFile(boost::shared_ptr<ContextHandle> search, HitCounterInfo* hinfo, FILE* file, LG_HITCALLBACK_FN callback);

  uint32 BlockSize;
  uint64 BytesSearched;
  double TotalTime;
  boost::scoped_array<byte> Cur,
                            Next;
};

bool SearchController::searchFile(boost::shared_ptr<ContextHandle> searcher, HitCounterInfo* hinfo, FILE* file, LG_HITCALLBACK_FN callback) {
  boost::timer searchClock;
  uint64 blkSize = 0,
         offset = 0;

  blkSize = readNext(file, Cur.get(), BlockSize);
  if (!feof(file)) {
    do {
      // read the next block on a separate thread
      boost::packaged_task<uint64> task(boost::bind(&readNext, file, Next.get(), BlockSize));
      boost::unique_future<uint64> sizeFut = task.get_future();
      boost::thread exec(boost::move(task));

      // search cur block
      lg_search(searcher.get(), (char*)Cur.get(), (char*)Cur.get() + blkSize, offset, hinfo, callback);

      offset += blkSize;
      if (offset % (1024 * 1024 * 1024) == 0) { // should change this due to the block size being variable
        double lastTime = searchClock.elapsed();
        uint64 units = offset >> 20;
        double bw = units / lastTime;
        units >>= 10;
        std::cerr << units << " GB searched in " << lastTime << " seconds, " << bw << " MB/s avg" << std::endl;
      }
      blkSize = sizeFut.get(); // block on i/o thread completion
      Cur.swap(Next);
    } while (!feof(file)); // note file is shared btwn threads, but safely
  }

  // assert: all data has been read, offset + blkSize == file size,
  // cur is last block
  lg_search(searcher.get(), (char*)Cur.get(), (char*)Cur.get() + blkSize, offset, hinfo, callback);
  lg_closeout_search(searcher.get(), hinfo, callback);
  offset += blkSize;  // be sure to count the last block

  TotalTime += searchClock.elapsed();
  BytesSearched += offset;
  return true;
}

void search(const std::string& input, SearchController& ctrl, boost::shared_ptr<ContextHandle> searcher, HitCounterInfo* hinfo, LG_HITCALLBACK_FN callback) {
  // try to open our input
  FILE* file = input == "-" ? stdin : fopen(input.c_str(), "rb");
  if (!file) {
    std::cerr << "Could not open file " << input << std::endl;
    return;
  }

  setbuf(file, 0); // unbuffered, bitte

  hinfo->setPath(input);
  lg_reset_context(searcher.get());
  ctrl.searchFile(searcher, hinfo, file, callback);

  fclose(file);
}

void searchRecursively(const fs::path& path, SearchController& ctrl, boost::shared_ptr<ContextHandle> searcher, HitCounterInfo* hinfo, LG_HITCALLBACK_FN callback) {
  const fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator d(path); d != end; ++d) {
    const fs::path p(d->path());
    if (!fs::is_directory(p)) {
      search(p.string(), ctrl, searcher, hinfo, callback);
    }
  }
}

void searches(const Options& opts) {
  // parse patterns and get index and encoding info for hit writer
  PatternInfo pinfo;
  pinfo.Patterns = opts.getKeys();

  boost::shared_ptr<ProgramHandle> prog(createProgram(opts, pinfo));
  if (!prog) {
    return;
  }

  // setup hit callback
  LG_HITCALLBACK_FN callback = 0;
  boost::scoped_ptr<HitCounterInfo> hinfo;

  if (opts.NoOutput) {
    callback = &nullWriter;
    hinfo.reset(new HitCounterInfo);
  }
  else if (opts.PrintPath) {
    callback = &pathWriter;
    hinfo.reset(new PathWriterInfo(opts.openOutput(), pinfo));
  }
  else {
    callback = &hitWriter;
    hinfo.reset(new HitWriterInfo(opts.openOutput(), pinfo));
  }

  // setup search context
  LG_ContextOptions ctxOpts;
  ctxOpts.TraceBegin = opts.DebugBegin;
  ctxOpts.TraceEnd = opts.DebugEnd;

  boost::shared_ptr<ContextHandle> searcher(
    lg_create_context(prog.get(), &ctxOpts),
    lg_destroy_context
  );

  SearchController ctrl(opts.BlockSize);

  // search our inputs
  if (opts.Recursive) {
    for (std::vector<std::string>::const_iterator i(opts.Inputs.begin()); i != opts.Inputs.end(); ++i) {
      const fs::path p(*i);
      if (fs::is_directory(p)) {
        searchRecursively(p, ctrl, searcher, hinfo.get(), callback);
      }
      else {
        search(*i, ctrl, searcher, hinfo.get(), callback);
      }
    }
  }
  else {
    for (std::vector<std::string>::const_iterator i(opts.Inputs.begin()); i != opts.Inputs.end(); ++i) {
      if (!fs::is_directory(fs::path(*i))) {
        search(*i, ctrl, searcher, hinfo.get(), callback);
      }
    }
  }

  std::cerr << ctrl.BytesSearched << " bytes" << std::endl;
  std::cerr << ctrl.TotalTime << " searchTime" << std::endl;
  if (ctrl.TotalTime > 0.0) {
    std::cerr << ctrl.BytesSearched/ctrl.TotalTime/(1 << 20);
  }
  else {
    std::cerr << "+inf";
  }
  std::cerr << " MB/s avg" << std::endl;
  std::cerr << hinfo->NumHits << " hits" << std::endl;
}

bool writeGraphviz(const Options& opts) {
  if (opts.getKeys().empty()) {
    return false;
  }

  PatternInfo pinfo;
  pinfo.Patterns = opts.getKeys();

  // parse patterns
  uint32 numErrors;
  boost::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
  std::cerr << "numErrors = " << numErrors << std::endl;
  if (numErrors == 0) {
    // build the program to force determinization
    boost::shared_ptr<ProgramHandle> prog(buildProgram(parser.get(), opts));
    if (!lg_ok(prog.get())) {
      std::cerr << lg_error(prog.get()) << std::endl;
      return false;
    }

    // break on through the C API to print the graph
    NFAPtr g(parser->Impl->Fsm);
    std::cerr << g->verticesSize() << " vertices" << std::endl;
    writeGraphviz(opts.openOutput(), *g);
    return true;
  }
  return false;
}

void writeProgram(const Options& opts) {
  if (opts.getKeys().empty()) {
    return;
  }

  PatternInfo pinfo;
  pinfo.Patterns = opts.getKeys();

  boost::shared_ptr<ProgramHandle> prog;

  {
    // parse patterns
    uint32 numErrors;
    boost::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
    // build the program
    prog = buildProgram(parser.get(), opts);
    if (!lg_ok(prog.get())) {
      std::cerr << lg_error(prog.get()) << std::endl;
      return;
    }
 
    NFAPtr g(parser->Impl->Fsm);
    std::cerr << g->verticesSize() << " vertices" << std::endl;
  }

  // break on through the C API to print the program
  ProgramPtr p(prog->Impl->Prog);
  std::cerr << p->size() << " instructions" << std::endl;
  std::ostream& out(opts.openOutput());
  out << *p << std::endl;
}

void writeSampleMatches(const Options& opts) {
  if (opts.getKeys().empty()) {
    return;
  }

  const std::vector<Pattern>& pats(opts.getKeys());
  for (std::vector<Pattern>::const_iterator i(pats.begin()); i != pats.end(); ++i) {
    // parse the pattern

    PatternInfo pinfo;
    pinfo.Patterns.push_back(*i);

    uint32 numErrors;
    boost::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
    if (numErrors == 0) {
      // break on through the C API to get the graph
      NFAPtr g(parser->Impl->Fsm);

      std::set<std::string> matches;
      matchgen(*g, matches, opts.SampleLimit, opts.LoopLimit);

      std::copy(matches.begin(), matches.end(), std::ostream_iterator<std::string>(opts.openOutput(), "\n"));
    }
  }
}

void startServer(const Options& opts) {
  PatternInfo pinfo;
  pinfo.Patterns = opts.getKeys();

  uint32 numErrors;
  boost::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
  if (parser && numErrors == 0) {
    boost::shared_ptr<ProgramHandle> prog(buildProgram(parser.get(), opts));
    if (prog) {
      startup(prog, pinfo, opts);
      return;
    }
  }
  THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not parse patterns at server startup");
}

int main(int argc, char** argv) {
  Options opts;
  po::options_description desc("Allowed Options");
  try {
    parse_opts(argc, argv, desc, opts);

    if (opts.Command == "search") {
      searches(opts);
    }
    else if (opts.Command == "server") {
      startServer(opts);
    }
    else if (opts.Command == "help") {
      printHelp(desc);
    }
    else if (opts.Command == "graph") {
      return writeGraphviz(opts) ? 0: 1;
    }
    else if (opts.Command == "prog") {
      writeProgram(opts);
    }
    else if (opts.Command == "samp") {
      writeSampleMatches(opts);
    }
    else {
      // this should be impossible
      std::cerr << "Unrecognized command. Use --help for list of options."
                << std::endl;
      return 1;
    }
  }
  catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n\n";
    printHelp(desc);
    return 1;
  }
  return 0;
}
