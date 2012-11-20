#include <algorithm>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <tuple>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/graph/graphviz.hpp>

#include <unicode/ucnv.h>

#include "encodings.h"
#include "handles.h"
#include "hitwriter.h"
#include "lightgrep_c_api.h"
#include "matchgen.h"
#include "options.h"
#include "optparser.h"
#include "pattern.h"
#include "program.h"
#include "searchcontroller.h"
#include "utility.h"

#ifdef LIGHTGREP_CUSTOMER
// check this out: http://stackoverflow.com/questions/2751870/how-exactly-does-the-double-stringize-trick-work
#define STRINGIZE(whatever) #whatever
#define JUMP_THROUGH_A_HOOP(yo) STRINGIZE(yo)
#define CUSTOMER_NAME JUMP_THROUGH_A_HOOP(LIGHTGREP_CUSTOMER)
#endif

// FIXME: should this be moved to searchcontroller.cpp?
//
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

void startup(
  std::shared_ptr<ProgramHandle> prog,
  std::shared_ptr<PatternMapHandle> pmap,
  uint32 numUserPatterns,
  const Options& opts
);

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
      aliases[LG_SUPPORTED_ENCODINGS[i].idx].emplace_back(
        LG_SUPPORTED_ENCODINGS[i].name
      );
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

void stdParseErrorHandler(const Pattern& p, const std::string& err) {
  std::cerr << err << " on pattern " << p.Index << ", '"
            << p.Expression << "'" << std::endl;
}

/*
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
*/

void search(
  const std::string& input,
  SearchController& ctrl,
  std::shared_ptr<ContextHandle> searcher,
  HitCounterInfo* hinfo,
  LG_HITCALLBACK_FN callback)
{
  // try to open our input
  FILE* file = input == "-" ? stdin : std::fopen(input.c_str(), "rb");
  if (!file) {
    std::cerr << "Could not open file " << input << std::endl;
    return;
  }

  setbuf(file, 0); // unbuffered, bitte

  hinfo->setPath(input);
  lg_reset_context(searcher.get());
  ctrl.searchFile(searcher, hinfo, file, callback);

  std::fclose(file);
}

void searchRecursively(
  const fs::path& path,
  SearchController& ctrl,
  std::shared_ptr<ContextHandle> searcher,
  HitCounterInfo* hinfo,
  LG_HITCALLBACK_FN callback)
{
  const fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator d(path); d != end; ++d) {
    const fs::path p(d->path());
    if (!fs::is_directory(p)) {
      search(p.string(), ctrl, searcher, hinfo, callback);
    }
  }
}

template <typename T>
using UPtr = std::unique_ptr<T,void(*)(T*)>;

std::tuple<
  UPtr<PatternMapHandle>,
  UPtr<FSMHandle>,
  uint32
>
parsePatterns(
  const std::vector<Pattern>& pats,
  std::function<void (const Pattern&, const std::string&)> onError = 
    stdParseErrorHandler
)
{
  uint32 numErrors = 0;

  if (!pats.empty()) {
    // set up handles we need for parsing
    UPtr<PatternHandle> pat(lg_create_pattern(), lg_destroy_pattern);

    UPtr<PatternMapHandle> pmap(
      lg_create_pattern_map(pats.size()),
      lg_destroy_pattern_map
    );

    // find total length of patterns -- or 1 if tlen is 0
    const uint32 tlen = std::max(1u, estimateGraphSize(pats));

    UPtr<FSMHandle> fsm(lg_create_fsm(tlen), lg_destroy_fsm);

    // parse the patterns
    LG_KeyOptions keyOpts; 

    const uint32 pcount = pats.size();
    for (uint32 i = 0; i < pcount; ++i) {
      const Pattern& p(pats[i]);

      LG_Error* err = nullptr;

      keyOpts.CaseInsensitive = p.CaseInsensitive;
      keyOpts.FixedString = p.FixedString;

      lg_parse_pattern(pat.get(), p.Expression.c_str(), &keyOpts, &err);    
      if (err) {
        ++numErrors;
        onError(p, err->Message);
        lg_free_error(err);
        continue;
      }

      // FIXME: read the chain properly once we add support
      LG_EncodingChain enc = { p.Encoding.front().c_str() };

      lg_add_pattern(fsm.get(), pmap.get(), pat.get(), &enc, &err);
      if (err) {
        ++numErrors;
        onError(p, err->Message);
        lg_free_error(err);
        continue;
      }

      // pack the user pattern number into the void*, oh the horror
      LG_PatternInfo* pinfo = lg_pattern_info(pmap.get(), i - numErrors);
      pinfo->UserData = reinterpret_cast<void*>(i);
    }

    if (pats.size() > numErrors) {
      // we successfully parsed something
      return std::make_tuple(
        std::move(pmap),
        std::move(fsm),
        numErrors
      );
    }
  }

  // nothing parsed successfully
  return std::make_tuple(
    UPtr<PatternMapHandle>(nullptr, nullptr),
    UPtr<FSMHandle>(nullptr, nullptr),
    numErrors
  );
}

UPtr<ProgramHandle> loadProgram(const std::string& pfile) {
  std::ifstream pin(pfile, std::ios::in | std::ios::binary);
  if (!pin) {
    std::cerr << "Could not open program file " << pfile << std::endl;
    return UPtr<ProgramHandle>(nullptr, nullptr);
  }

// FIXME: we need to handle the case where the read fails
// FIXME: what to do for the pattern map?

  // this is seriously tedious compared to, oh, I don't know, file.size()
  pin.seekg(0, std::ios::end);
  std::streampos end = pin.tellg();
  pin.seekg(0, std::ios::beg);

  std::cerr << "program file is " << end << " bytes long" << std::endl;

  std::vector<char> buf(end);
  pin.read(&buf[0], end);
  pin.close();

  return UPtr<ProgramHandle>(
    lg_read_program(&buf[0], end),
    lg_destroy_program
  );
}

UPtr<ProgramHandle> buildProgram(FSMHandle* fsm, const Options& opts) {
  LG_ProgramOptions progOpts{opts.Determinize};

  UPtr<ProgramHandle> prog(
    lg_create_program(fsm, &progOpts),
    lg_destroy_program
  );

  if (prog) {
    NFAPtr g(fsm->Impl->Fsm);
    std::cerr << g->verticesSize() << " vertices\n";

    ProgramPtr p(prog->Impl);
    std::cerr << p->size() << " instructions" << std::endl;
  }
  else {
    std::cerr << "Failed to create program" << std::endl;
    prog.reset();
  }

  return std::move(prog);
}

void search(const Options& opts) {
  UPtr<PatternMapHandle> pmap(nullptr, nullptr);
  UPtr<ProgramHandle> prog(nullptr, nullptr);

  if (!opts.ProgramFile.empty()) {
    // read a program in from file
    prog = loadProgram(opts.ProgramFile);
  }
  else {
    // get the patterns and parse them
    const std::vector<Pattern> pats = opts.getKeys();

    UPtr<FSMHandle> fsm(nullptr, nullptr);

    std::tie(pmap, fsm, std::ignore) = parsePatterns(pats);

    // build a program from parsed patterns
    if (fsm) {
      prog = buildProgram(fsm.get(), opts);
    }
  }

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
    hinfo.reset(new PathWriterInfo(opts.openOutput(), pmap.get()));
  }
  else {
    callback = &hitWriter;
    hinfo.reset(new HitWriterInfo(opts.openOutput(), pmap.get()));
  }

  // setup search context
  LG_ContextOptions ctxOpts;
  ctxOpts.TraceBegin = opts.DebugBegin;
  ctxOpts.TraceEnd = opts.DebugEnd;

// FIXME: any reason this needs to be shared?
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

  std::cerr << ctrl.BytesSearched << " bytes\n"
            << ctrl.TotalTime << " searchTime\n";
  if (ctrl.TotalTime > 0.0) {
    std::cerr << ctrl.BytesSearched/ctrl.TotalTime/(1 << 20);
  }
  else {
    std::cerr << "+inf";
  }
  std::cerr << " MB/s avg\n"
            << hinfo->NumHits << " hits" << std::endl;
}

bool writeGraphviz(const Options& opts) {
  if (opts.getKeys().empty()) {
    return false;
  }

  // get the patterns and parse them
  const std::vector<Pattern> pats(opts.getKeys());

  UPtr<FSMHandle> fsm(nullptr, nullptr);
  uint32 numErrors;

  std::tie(std::ignore, fsm, numErrors) = parsePatterns(pats);

  std::cerr << "numErrors = " << numErrors << std::endl;
// FIXME: do we actually want to fail on any bad pattern?
  if (numErrors > 0 || !fsm) {
    return false;
  }

  // build the program to force determinization
  if (!buildProgram(fsm.get(), opts)) {
    return false;
  }

  // break on through the C API to print the graph
  NFAPtr g(fsm->Impl->Fsm);
  std::cerr << g->verticesSize() << " vertices" << std::endl;
  writeGraphviz(opts.openOutput(), *g);
  return true;
}

void writeProgram(const Options& opts) {
  if (opts.getKeys().empty()) {
    return;
  }

  // get the patterns and parse them
  const std::vector<Pattern> pats(opts.getKeys());

  UPtr<FSMHandle> fsm(nullptr, nullptr);

  std::tie(std::ignore, fsm, std::ignore) = parsePatterns(pats);

  if (!fsm) {
    return;
  }

  UPtr<ProgramHandle> prog(buildProgram(fsm.get(), opts));
  fsm.reset();

  if (!prog) {
    return;
  }

  // break on through the C API to print the program
  ProgramPtr p(prog->Impl);
  std::cerr << p->size() << " instructions\n"
            << p->bufSize() << " program size in bytes" << std::endl;

  std::ostream& out(opts.openOutput());
  if (opts.Binary) {
    const std::string s = p->marshall();
    std::cerr << s.size() << " program size in bytes" << std::endl;
    out.write(s.data(), s.size());
  }
  else {
    out << *p << std::endl;
  }
}

void validate(const Options& opts) {
  const std::vector<Pattern> pats(opts.getKeys());
  if (!pats.empty()) {
    parsePatterns(
      pats,
      [](const Pattern& p, const std::string&) {
        std::cerr << p.Index << ": pattern \"" << p.Expression
                  << "\" is invalid for encoding "
                  << p.Encoding.front() << std::endl;
      }
    );
  }
}

void writeSampleMatches(const Options& opts) {
  const std::vector<Pattern> pats(opts.getKeys());

	std::ostream& out(opts.openOutput());

  // Write a LE BOM because EnCase is retarded and expectes a BOM for UTF-16LE
  out << (char) 0xFF << (char) 0xFE;

  for (const Pattern& pat : pats) {
    // parse the pattern

    UPtr<FSMHandle> fsm(nullptr, nullptr);
    uint32 numErrors;

    std::tie(std::ignore, fsm, numErrors) = parsePatterns(
      {pat},
      [&out](const Pattern& p, const std::string& err) {
        std::stringstream ss;
        ss << err << " on pattern " << p.Index << ", '" << p.Expression << "'";
        std::string msg(ss.str());

        std::unique_ptr<char[]> buf(new char[4*msg.length()+1]);
        UErrorCode ec = U_ZERO_ERROR;
        const uint32 len = ucnv_convert(
          "UTF-16LE", "UTF-8",
          buf.get(),
          4*msg.length()+1,
          msg.c_str(), -1,
          &ec
        );
        if (U_FAILURE(ec)) {
          std::cerr << "Error: " << u_errorName(ec) << std::endl;
        }

        out << std::string(buf.get(), len)
            << (char) 0x0D << (char) 0x00 << (char) 0x0A << (char) 0x00;
      }
    );

    if (numErrors == 0  && fsm) {
      // break on through the C API to get the graph
      NFAPtr g(fsm->Impl->Fsm);

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
  const std::vector<Pattern> pats(opts.getKeys());

  UPtr<PatternMapHandle> pmap(nullptr, nullptr);
  UPtr<FSMHandle> fsm(nullptr, nullptr);
  uint32 numErrors;

  std::tie(pmap, fsm, numErrors) = parsePatterns(pats);

  // build a program from parsed patterns
  if (numErrors == 0 && fsm) {
    UPtr<ProgramHandle> prog(buildProgram(fsm.get(), opts));
    fsm.reset();

    if (prog) {
      startup( 
        std::shared_ptr<ProgramHandle>(std::move(prog)),
        std::shared_ptr<PatternMapHandle>(std::move(pmap)),
        pats.size(),
        opts
      );
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
