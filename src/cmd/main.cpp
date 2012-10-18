#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/timer.hpp>
#include <boost/graph/graphviz.hpp>

#include <unicode/ucnv.h>

#include "encodings.h"
#include "handles.h"
#include "hitwriter.h"
#include "lightgrep_c_api.h"
#include "matchgen.h"
#include "options.h"
#include "optparser.h"
#include "patterninfo.h"
#include "utility.h"
#include "program.h"

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

void startup(std::shared_ptr<ProgramHandle> prog, const PatternInfo& pinfo, const Options& opts);

uint64 readNext(FILE* file, byte* buf, unsigned int blockSize) {
  return fread((void*)buf, 1, blockSize, file);
}

void printHelp(const po::options_description& desc) {
  std::cout
    << "lightgrep, Copyright (c) 2010-2012, Lightbox Technologies, Inc."
    << "\nCreated " << __DATE__ << "\n\n"
    << "Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]\n\n"
    #ifdef LIGHTGREP_CUSTOMER
    << "This copy provided EXCLUSIVELY to " << CUSTOMER_NAME << ".\n\n"
    #endif
    << desc << std::endl;
}

void printEncodings() {
  const uint32 slen =
    sizeof(LG_SUPPORTED_ENCODINGS) / sizeof(LG_SUPPORTED_ENCODINGS[0]);
  const uint32 clen =
    sizeof(LG_CANONICAL_ENCODINGS) / sizeof(LG_CANONICAL_ENCODINGS[0]);

  // group the aliases by the indices of their canonical names
  std::vector<std::vector<std::string>> aliases(clen);
  for (uint32 i = 0; i < slen; ++i) {
    if (std::strcmp(
          LG_SUPPORTED_ENCODINGS[i].name,
          LG_CANONICAL_ENCODINGS[LG_SUPPORTED_ENCODINGS[i].idx]
        ) != 0
    ) {
      aliases[LG_SUPPORTED_ENCODINGS[i].idx].emplace_back(LG_SUPPORTED_ENCODINGS[i].name);
    }
  }

  for (uint32 i = 0; i < clen; ++i) {
    // print the canonical name for the encoding
    std::cout << LG_CANONICAL_ENCODINGS[i] << '\n';

    // print the aliases for the encoding
    for (const std::string& alias : aliases[i]) {
      std::cout << '\t' << alias << '\n';
    }
  }

  std::cout << std::endl;
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

  if (lg_add_keyword(
    parser,
    pat.Expression.c_str(),
    patIdx,
    &keyOpts,
    pat.Encoding.c_str()
  )) {
    pinfo.Table.emplace_back(pat.Index, encIdx);
    return true;
  }
  else {
    return false;
  }
}

void stdParseErrorHandler(const Pattern& p, const std::string& err) {
  std::cerr << err << " on pattern "
              << p.Index << ", '" << p.Expression << "'" << std::endl;
}

std::shared_ptr<ParserHandle> parsePatterns(
  PatternInfo& pinfo,
  uint32& numErrors,
  std::function<void (const Pattern&, const std::string&)> onError =
    stdParseErrorHandler)
{
  numErrors = 0;
  if (pinfo.Patterns.empty()) {
    return std::shared_ptr<ParserHandle>();
  }

  // find total length of patterns -- or 1 if tlen is 0
  const uint32 tlen = std::max(1u, estimateGraphSize(pinfo.Patterns));

  std::shared_ptr<ParserHandle> parser(lg_create_parser(tlen),
                                       lg_destroy_parser);

  // parse patterns
  uint32 patIdx = 0;

  for (uint32 i = 0; i < pinfo.Patterns.size(); ++i) {
    const int32 encIdx = lg_get_encoding_id(pinfo.Patterns[i].Encoding.c_str());
    if (encIdx == -1) {
      ++numErrors;
      onError(pinfo.Patterns[i],
        "unrecognized encoding '" + pinfo.Patterns[i].Encoding + "'"
      );
    }
    else if (addPattern(parser.get(), i, patIdx, encIdx, pinfo)) {
      // std::cerr << i << " parsed " << pinfo.Patterns[i].Expression << ", for " << pinfo.Patterns[i].Encoding << std::endl;
      ++patIdx;
    }
    else {
      ++numErrors;
      onError(pinfo.Patterns[i], lg_error(parser.get()));
    }
  }
  // don't enable these unless debugging -- will mess up enscript
  // std::cerr << pinfo.Patterns.size() << " Patterns" << std::endl;
  // std::cerr << patIdx << " Byte Patterns" << std::endl;
  // std::cerr << numErrors << " Errors" << std::endl;
  return parser;
}

std::shared_ptr<ProgramHandle> buildProgram(LG_HPARSER parser, const Options& opts) {
  LG_ProgramOptions progOpts;
  progOpts.Determinize = opts.Determinize;

  return std::shared_ptr<ProgramHandle>(
    lg_create_program(parser, &progOpts),
    lg_destroy_program
  );
}

std::shared_ptr<ProgramHandle> createProgram(const Options& opts, PatternInfo& pinfo) {
  uint32 numErrors;
  std::shared_ptr<ParserHandle>  parser(parsePatterns(pinfo, numErrors));
  std::shared_ptr<ProgramHandle> prog;
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

  bool searchFile(std::shared_ptr<ContextHandle> search, HitCounterInfo* hinfo, FILE* file, LG_HITCALLBACK_FN callback);

  uint32 BlockSize;
  uint64 BytesSearched;
  double TotalTime;
  boost::scoped_array<byte> Cur,
                            Next;
};

bool SearchController::searchFile(std::shared_ptr<ContextHandle> searcher, HitCounterInfo* hinfo, FILE* file, LG_HITCALLBACK_FN callback) {
  boost::timer searchClock;
  uint64 blkSize = 0,
         offset = 0;

  blkSize = readNext(file, Cur.get(), BlockSize);
  if (!feof(file)) {
    do {
      // read the next block on a separate thread
      boost::packaged_task<uint64> task(std::bind(&readNext, file, Next.get(), BlockSize));
      boost::unique_future<uint64> sizeFut = task.get_future();
      boost::thread exec(std::move(task));

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

void search(const std::string& input, SearchController& ctrl, std::shared_ptr<ContextHandle> searcher, HitCounterInfo* hinfo, LG_HITCALLBACK_FN callback) {
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

void searchRecursively(const fs::path& path, SearchController& ctrl, std::shared_ptr<ContextHandle> searcher, HitCounterInfo* hinfo, LG_HITCALLBACK_FN callback) {
  const fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator d(path); d != end; ++d) {
    const fs::path p(d->path());
    if (!fs::is_directory(p)) {
      search(p.string(), ctrl, searcher, hinfo, callback);
    }
  }
}

std::shared_ptr<ProgramHandle> getProgram(const Options& opts, PatternInfo& pinfo) {
  if (!opts.ProgramFile.empty()) {
    // std::cerr << "creating program from file " << opts.ProgramFile << std::endl;
    std::ifstream progFile(opts.ProgramFile.c_str(), std::ios::in | std::ios::binary);
    if (progFile) {
      // this is seriously tedious compared to, oh, I don't know, file.size()
      progFile.seekg(0, std::ios::end);
      std::streampos end = progFile.tellg();
      progFile.seekg(0, std::ios::beg);

      std::cerr << "program file is " << end << " bytes long" << std::endl;

      std::vector<char> buf(end);
      progFile.read(&buf[0], end);
      progFile.close();

      return std::shared_ptr<ProgramHandle>(lg_read_program(&buf[0], end), lg_destroy_program);
    }
    else {
      std::cerr << "Could not open program file " << opts.ProgramFile << std::endl;
    }
    return std::shared_ptr<ProgramHandle>();
  }
  else {
    // std::cerr << "creating program from patterns" << std::endl;
    return createProgram(opts, pinfo);
  }
}

void search(const Options& opts) {
  // parse patterns and get index and encoding info for hit writer
  PatternInfo pinfo = opts.getKeys();

  std::shared_ptr<ProgramHandle> prog(getProgram(opts, pinfo));
  if (!prog) {
    std::cerr << "Did not get a proper program" << std::endl;
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

  std::shared_ptr<ContextHandle> searcher(
    lg_create_context(prog.get(), &ctxOpts),
    lg_destroy_context
  );

  SearchController ctrl(opts.BlockSize);

  // search our inputs
  if (opts.Recursive) {
    for (const std::string& i : opts.Inputs) {
      const fs::path p(i);
      if (fs::is_directory(p)) {
        searchRecursively(p, ctrl, searcher, hinfo.get(), callback);
      }
      else {
        search(i, ctrl, searcher, hinfo.get(), callback);
      }
    }
  }
  else {
    for (const std::string& i : opts.Inputs) {
      if (!fs::is_directory(fs::path(i))) {
        search(i, ctrl, searcher, hinfo.get(), callback);
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

  PatternInfo pinfo = opts.getKeys();

  // parse patterns
  uint32 numErrors;
  std::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
  std::cerr << "numErrors = " << numErrors << std::endl;
  if (numErrors == 0) {
    // build the program to force determinization
    std::shared_ptr<ProgramHandle> prog(buildProgram(parser.get(), opts));
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

  PatternInfo pinfo = opts.getKeys();

  std::shared_ptr<ProgramHandle> prog;

  {
    // parse patterns
    uint32 numErrors;
    std::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
    // build the program
    prog = buildProgram(parser.get(), opts);
    if (!lg_ok(prog.get())) {
      std::cerr << lg_error(prog.get()) << std::endl;
      return;
    }

    NFAPtr g(parser->Impl->Fsm);
  }

  // break on through the C API to print the program
  ProgramPtr p(prog->Impl->Prog);
  std::cerr << p->size() << " instructions" << std::endl;
  std::cerr << p->bufSize() << " program size in bytes" << std::endl;
  std::ostream& out(opts.openOutput());
  if (opts.Binary) {
    std::string s = p->marshall();
    std::cerr << s.size() << " program size in bytes" << std::endl;
    out.write(s.data(), s.size());
  }
  else {
    out << *p << std::endl;
  }
}

void validate(const Options& opts) {
  PatternInfo pinfo = opts.getKeys();
  if (pinfo.empty()) {
    return;
  }
  uint32 numErrors = 0;
  parsePatterns(pinfo, numErrors, [](const Pattern& p, const std::string&) {
    std::cerr << p.Index << ": pattern \"" << p.Expression << "\" is invalid for encoding " << p.Encoding << std::endl;
  });
}

void writeSampleMatches(const Options& opts) {
  PatternInfo pinfo = opts.getKeys();

	std::ostream& out(opts.openOutput());

  // Write a LE BOM because EnCase is retarded and expectes a BOM for UTF-16LE
  out << (char) 0xFF << (char) 0xFE;

  for (const Pattern& pat : pinfo.Patterns) {
    // parse the pattern

    PatternInfo pinfo;
    pinfo.Patterns.push_back(pat);

    uint32 numErrors;

    std::shared_ptr<ParserHandle> parser(
      parsePatterns(pinfo, numErrors,
        [&](const Pattern& p, const std::string& err) {
          std::stringstream ss;
          ss << err << " on pattern " << p.Index << ", '" << p.Expression << "'";
          std::string msg(ss.str());

          std::unique_ptr<char[]> buf(new char[4*msg.length()+1]);
          UErrorCode ec = U_ZERO_ERROR;
          const uint32 len = ucnv_convert("UTF-16LE", "UTF-8", buf.get(), 4*msg.length()+1, msg.c_str(), -1, &ec);
          if (U_FAILURE(ec)) {
            std::cerr << "Error: " << u_errorName(ec) << std::endl;
          }

          out << std::string(buf.get(), len) << (char) 0x0D << (char) 0x00 << (char) 0x0A << (char) 0x00;
        }
      )
    );

    if (numErrors == 0) {
      // break on through the C API to get the graph
      NFAPtr g(parser->Impl->Fsm);

      std::set<std::string> matches;
      matchgen(*g, matches, opts.SampleLimit, opts.LoopLimit);

      for (const std::string& m : matches) {
        out << m << (char) 0x0D << (char) 0x00 << (char) 0x0A << (char) 0x00;
      }
    }
    out.flush();
  }
}

void startServer(const Options& opts) {
  PatternInfo pinfo = opts.getKeys();

  uint32 numErrors;
  std::shared_ptr<ParserHandle> parser(parsePatterns(pinfo, numErrors));
  if (parser && numErrors == 0) {
    std::shared_ptr<ProgramHandle> prog(buildProgram(parser.get(), opts));
    if (prog) {
      startup(prog, pinfo, opts);
      return;
    }
  }
  THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not parse patterns at server startup");
}

int main(int argc, char** argv) {
  Options opts;
  po::options_description desc;
  try {
    parse_opts(argc, argv, desc, opts);

    switch (opts.Command) {
    case Options::SEARCH:
      search(opts);
      break;
    case Options::GRAPH:
      return writeGraphviz(opts) ? 0: 1;
    case Options::PROGRAM:
      writeProgram(opts);
      break;
    case Options::SAMPLES:
      writeSampleMatches(opts);
      break;
    case Options::VALIDATE:
      validate(opts);
      break;
    case Options::SERVER:
      startServer(opts);
      break;
    case Options::HELP:
      printHelp(desc);
      break;
    case Options::ENCODINGS:
      printEncodings();
      break;
    default:
      // this should be impossible
      std::cerr << "Unrecognized command. Use --help for list of options."
                << std::endl;
      return 1;
    }
  }
  catch (const std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n\n";
    printHelp(desc);
    return 1;
  }
  return 0;
}
