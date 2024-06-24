#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <stdexcept>
#include <tuple>

#include "boost_program_options.h"

#include <unicode/ucnv.h>

#include "handles.h"
#include "lg_app.h"
#include "pattern.h"
#include "program.h"
#include "utility.h"

#include "factor_analysis.h"
#include "hitwriter.h"
#include "matchgen.h"
#include "options.h"
#include "optparser.h"
#include "reader.h"
#include "searchcontroller.h"
#include "util.h"

#include <lightgrep/api.h>
#include <lightgrep/encodings.h>

namespace po = boost::program_options;
namespace fs = std::filesystem;

void printVersion(std::ostream& out) {
  const std::string buildDate(__DATE__);
  // ANSI C now defines __DATE__ as 11-char string of MMM DD YYYY, but double-check
  const std::string year = buildDate.size() == 11 && buildDate[7] == '2' ? buildDate.substr(7, 4): "2024";
  out << "lightgrep " << VERSION << '\n'
      << "Copyright (c) 2010-" << year << ", Stroz Friedberg, LLC\n"
         "Built " << buildDate << std::endl;
}

void printUsage(std::ostream& out) {
  out << "Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]...\n"
         "       lightgrep [OPTION]... [-p PATTERN | -k FILE]... [FILE]..."
      << std::endl;
}

void printHelp(std::ostream& out, const po::options_description& desc) {
  printVersion(out);
  printUsage(out);
  out << desc << std::endl;
}

void printEncodings(std::ostream& out) {
  const size_t slen = std::extent_v<decltype(LG_ENCODINGS)>;
  const uint32_t clen = std::extent_v<decltype(LG_CANONICAL_ENCODINGS)>;

  // group the aliases by the indices of their canonical names
  std::vector<std::vector<std::string>> aliases(clen);
  for (size_t i = 0; i < slen; ++i) {
    if (std::strcmp(
          LG_ENCODINGS[i].name,
          LG_CANONICAL_ENCODINGS[LG_ENCODINGS[i].idx]
        ) != 0
    ) {
      aliases[LG_ENCODINGS[i].idx].emplace_back(LG_ENCODINGS[i].name);
    }
  }

  for (size_t i = 0; i < clen; ++i) {
    // print the canonical name for the encoding
    out << LG_CANONICAL_ENCODINGS[i] << '\n';

    // print the aliases for the encoding
    for (const std::string& alias : aliases[i]) {
      out << '\t' << alias << '\n';
    }
  }

  out << std::endl;
}

size_t countErrors(const LG_Error* err) {
  size_t numErrors = 0;
  for (const LG_Error* e = err; e; e = e->Next, ++numErrors);
  return numErrors;
}

void search(
  const std::string& input,
  bool mmapped,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitOutputData* hinfo,
  LG_HITCALLBACK_FN callback)
{
  std::unique_ptr<Reader> reader;

  if (input == "-") {
    // stdin can't be mmap'd
    reader.reset(static_cast<Reader*>(new FileReader(input, ctrl.BlockSize)));
    hinfo->setPath("(standard input)");
  }
  else {
    reader.reset(mmapped ?
      static_cast<Reader*>(new MemoryMappedFileReader(input)) :
      static_cast<Reader*>(new FileReader(input, ctrl.BlockSize))
    );
    hinfo->setPath(input);
  }

  lg_reset_context(searcher);
  ctrl.searchFile(searcher, hinfo, *reader, callback);
}

void searchRecursively(
  const fs::path& path,
  bool mmapped,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitOutputData* hinfo,
  LG_HITCALLBACK_FN callback)
{
  const fs::recursive_directory_iterator end;
  for (fs::recursive_directory_iterator d(path); d != end; ++d) {
    const fs::path p(d->path());
    if (!fs::is_directory(p)) {
      search(p.string(), mmapped, ctrl, searcher, hinfo, callback);
    }
  }
}

std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)>
loadProgram(const std::string& pfile) {
  std::ifstream pin(pfile, std::ios::in | std::ios::binary);
  if (!pin) {
    std::cerr << "Could not open program file " << pfile << std::endl;
    return std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)>(
      nullptr, nullptr
    );
  }

// FIXME: we need to handle the case where the read fails

  const std::streampos end = stream_size(pin);
  std::cerr << "program file is " << end << " bytes long" << std::endl;

  std::vector<char> buf(end);
  pin.read(&buf[0], end);
  pin.close();

  return std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)>(
    lg_read_program(&buf[0], end),
    lg_destroy_program
  );
}

class Line {
public:
  friend std::istream& operator>>(std::istream& is, Line& l) {
    return std::getline(is, l.data);
  }

  operator const std::string&() const { return data; }

private:
  std::string data;
};

class Lines {
public:
  Lines(std::istream& is): is(is) {}

  std::istream_iterator<Line> begin() {
    return std::istream_iterator<Line>(is);
  }

  std::istream_iterator<Line> end() {
    return std::istream_iterator<Line>();
  }

private:
  std::istream& is;
};

bool skipStdin(const std::string& path, bool& stdinUsed) {
  if (path == "-") {
    if (stdinUsed) {
      std::cerr << "stdin already read, skipping '-' in files to search" << std::endl;
      return true;
    }

    stdinUsed = true;
  }
  return false;
}

LG_HITCALLBACK_FN selectCallbackFn(const Options& opts) {
  static const LG_HITCALLBACK_FN callbackFnOptions[] = {
    &callbackFn<DoNotWritePath, NoContext, false>,
    &callbackFn<DoNotWritePath, NoContext, true>,
    &callbackFn<DoNotWritePath, WriteContext, true>,
    &callbackFn<WritePath, NoContext, true>,
    &callbackFn<WritePath, WriteContext, true>,
  };

  if (opts.NoOutput) {
    return callbackFnOptions[0];
  }
  else {
    const bool shouldWritePath = opts.PrintPath;
    const bool shouldWriteContext = (opts.BeforeContext > -1 || opts.AfterContext > -1);

    return callbackFnOptions[1 + (2 * shouldWritePath) + shouldWriteContext];
  }
}

void searchRec(
  const std::string& i,
  bool mmapped,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitOutputData* hinfo,
  LG_HITCALLBACK_FN callback)
{
  // search this path recursively
  const fs::path p(i);
  if (fs::is_directory(p)) {
    searchRecursively(p, mmapped, ctrl, searcher, hinfo, callback);
  }
  else {
    search(i, mmapped, ctrl, searcher, hinfo, callback);
  }
}

void searchNonRec(
  const std::string& i,
  bool mmapped,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitOutputData* hinfo,
  LG_HITCALLBACK_FN callback)
{
  // search this path non-recursively
  if (!fs::is_directory(fs::path(i))) {
    search(i, mmapped, ctrl, searcher, hinfo, callback);
  }
}

template <class T>
void searchInputs(
  T&& inputs,
  const Options& opts,
  bool& stdinUsed,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitOutputData* hinfo,
  LG_HITCALLBACK_FN callback)
{
  const auto searchFunc = opts.Recursive ? searchRec : searchNonRec;
  for (const std::string& i: inputs) {
    if (!skipStdin(i, stdinUsed)) {
      searchFunc(i, opts.MemoryMapped, ctrl, searcher, hinfo, callback);
    }
  }
}

void search(const Options& opts) {
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog(nullptr, nullptr);

  if (!opts.ProgramFile.empty()) {
    // read a program in from file
    prog = loadProgram(opts.ProgramFile);
  }
  else {
    LgAppCollection col = parsePatterns(opts);
    prog = std::move(col.prog);

    const bool printFilename = opts.CmdLinePatterns.empty() && opts.KeyFiles.size() > 1;

    col.errors->outputErrors(std::cerr, printFilename);
  }

  if (!prog) {
    THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("failed to create a program");
    //std::runtime_error("failed to create a program");
  }

  bool histogramEnabled = !opts.HistogramFile.empty();

  std::ofstream histFile;
  if (histogramEnabled) {
    histFile.open(opts.HistogramFile, std::ios::out | std::ios::trunc);
    if (!histFile) {
      THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("Could not open file for histogram at " << opts.HistogramFile);
    }
  }

  std::unique_ptr<HitOutputData> hinfo(new HitOutputData(opts.openOutput(),
                                                          prog.get(),
                                                          '\t',
                                                          opts.GroupSeparator,
                                                          opts.BeforeContext,
                                                          opts.AfterContext, histogramEnabled));

  LG_HITCALLBACK_FN callback = selectCallbackFn(opts);

  // setup search context
  LG_ContextOptions ctxOpts;
  ctxOpts.TraceBegin = opts.DebugBegin;
  ctxOpts.TraceEnd = opts.DebugEnd;

  std::unique_ptr<ContextHandle, void(*)(ContextHandle*)> searcher(
    lg_create_context(prog.get(), &ctxOpts),
    lg_destroy_context
  );

  SearchController ctrl(opts.BlockSize);

  bool stdinUsed = false;

  // search each input file in each input list
  for (const auto& i: opts.InputLists) {
    std::ifstream ilf;
    std::istream* is;

    if (i == "-") {
      if (stdinUsed) {
        std::cerr << "stdin already read, skipping '-' in --args-list" << std::endl;
        continue;
      }

      is = &std::cin;
      stdinUsed = true;
    }
    else {
      ilf.open(i, std::ios::in | std::ios::binary);
      if (!ilf) {
        throw std::runtime_error("could not open input file list " + i);
      }

      is = &ilf;
    }

    searchInputs(Lines(*is), opts, stdinUsed, ctrl, searcher.get(), hinfo.get(), callback);

    if (is->bad()) {
      std::cerr << "Error reading input file list " << i << ": "
                << std::strerror(errno) << std::endl;
    }
  }

  // search each input file (positional args or stdin)
  if (!opts.Inputs.empty()) {
    searchInputs(opts.Inputs, opts, stdinUsed, ctrl, searcher.get(), hinfo.get(), callback);
  }

  if (histogramEnabled) {
    hinfo.get()->writeHistogram(histFile);
  }

  if (opts.Verbose) {
    std::cerr << ctrl.BytesSearched << " bytes\n"
              << ctrl.TotalTime << " searchTime\n";
    if (ctrl.TotalTime > 0.0) {
      std::cerr << (ctrl.BytesSearched / ctrl.TotalTime / (1 << 20));
    }
    else {
      std::cerr << "+inf";
    }
    std::cerr << " MB/s avg\n"
              << hinfo->NumHits
              << " hit" << (hinfo->NumHits != 1 ? "s" : "") << std::endl;
  }
}

void writeGraphviz(const Options& opts) {
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm(nullptr, nullptr);
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog(nullptr, nullptr);

  LgAppCollection col = parsePatterns(opts);
  fsm = std::move(col.fsm);
  prog = std::move(col.prog);

  const bool printFilename =
    opts.CmdLinePatterns.empty() && opts.KeyFiles.size() > 1;

  col.errors->outputErrors(std::cerr, printFilename);

  if (!prog) {
    THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("failed to create a program");
    //throw std::runtime_error("failed to create program");
  }
  // we don't need the prog; we just need the compilation to succeed
  prog.reset();

  // break on through the C API to print the graph
  writeGraphviz(opts.openOutput(), *fsm->Impl->Fsm);
}

void validate(const Options& opts) {
  LgAppCollection col = parsePatterns(opts);

  const bool printFilename = opts.CmdLinePatterns.empty() && opts.KeyFiles.size() > 1;
  col.errors->outputErrors(std::cerr, printFilename);
}

void writeSampleMatches(const Options& opts) {
// TODO:
// - This behavior should be turned into a C API, to avoid the cast of the FSM.
// - It should be unit tested.
// - Output should be UTF-8. There's no longer any reason to support EnCase's UTF-16LE.

// TODO: Writing sample matches should not be unconditionally EnCase-specific.
// There should be a switch to turn on the behavior EnCase needs.

	std::ostream& out(opts.openOutput());

  // Write a LE BOM because EnCase is silly and expectes a BOM for UTF-16LE
  out << (char) 0xFF << (char) 0xFE;

  // parse the patterns one at a time
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm(nullptr, nullptr);

  size_t pnum = 0;
  //for (const std::pair<std::string,std::string>& pf : opts.getPatternLines()) {

  // FIXME: opts.getPatternLines() returns a vector of the pairs, it's not clear
  // why when looping over the pairs we then turn around and put each into a vector/array.
  // const std::vector<std::pair<std::string, std::string>> a = { pf };

  LgAppCollection col = parsePatterns(opts);
  LG_Error* err = col.getError();
  fsm = std::move(col.fsm);

  if (err) {
    std::stringstream ss;
    ss << err->Message << " on pattern " << pnum
        << ", '"<< err->Pattern << "'";
    std::string msg(ss.str());

    std::unique_ptr<char[]> buf(new char[4*msg.length()+1]);
    UErrorCode ec = U_ZERO_ERROR;
    const uint32_t len = ucnv_convert(
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
  else {
    // break on through the C API to get the graph
    NFAPtr g(fsm->Impl->Fsm);

    std::set<std::string> matches;
    matchgen(*g, matches, opts.SampleLimit, opts.LoopLimit);

    for (const std::string& m : matches) {
      out << m << (char) 0x0D << (char) 0x00 << (char) 0x0A << (char) 0x00;
    }
  }

  out.flush();
  ++pnum;
  // }
}

void outputProgram(const Options& opts) {
  std::ostream& out(opts.openOutput());
  writeProgram(opts, out);
}

int main(int argc, char** argv) {
  try {
    Options opts;
    po::options_description desc;
    parse_opts(argc, argv, desc, opts);

    switch (opts.Command) {
    case Options::SEARCH:
      search(opts);
      break;
    case Options::GRAPH:
      writeGraphviz(opts);
      break;
    case Options::PROGRAM:
      outputProgram(opts);
      break;
    case Options::SAMPLES:
      writeSampleMatches(opts);
      break;
    case Options::VALIDATE:
      validate(opts);
      break;
    case Options::SHOW_VERSION:
      printVersion(std::cout);
      break;
    case Options::SHOW_HELP:
      printHelp(std::cout, desc);
      break;
    case Options::LIST_ENCODINGS:
      printEncodings(std::cout);
      break;
    default:
      // this should be impossible
      throw std::runtime_error("unrecognized command");
    }
    return 0;
  }
  catch (const std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n";
    printUsage(std::cerr);
    std::cerr << "Try 'lightgrep --help' for more information." << std::endl;
    return 1;
  }
}
