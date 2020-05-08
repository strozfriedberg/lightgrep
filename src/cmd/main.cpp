#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <tuple>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/graph/graphviz.hpp>

#include <unicode/ucnv.h>

#include "handles.h"
#include "pattern.h"
#include "program.h"
#include "utility.h"

#include "hitwriter.h"
#include "matchgen.h"
#include "options.h"
#include "optparser.h"
#include "reader.h"
#include "searchcontroller.h"
#include "util.h"

#include <lightgrep/api.h>
#include <lightgrep/encodings.h>

#ifdef LIGHTGREP_CUSTOMER
// check this out: http://stackoverflow.com/questions/2751870/how-exactly-does-the-double-stringize-trick-work
#define STRINGIZE(whatever) #whatever
#define JUMP_THROUGH_A_HOOP(yo) STRINGIZE(yo)
#define CUSTOMER_NAME JUMP_THROUGH_A_HOOP(LIGHTGREP_CUSTOMER)
#endif

// FIXME: should this be moved to searchcontroller.cpp?
// FIXME: is this still necessary?
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
  uint32_t numUserPatterns,
  const Options& opts
);

void printVersion() {
  std::cout << "lightgrep " << VERSION
            << "\nCopyright (c) 2010-2017, Stroz Friedberg, LLC"
               "\nBuilt " << __DATE__ << std::endl;
}

void printHelp(const po::options_description& desc) {
  printVersion();
  std::cout
    << "\nUsage: lightgrep [OPTIONS] PATTERN_FILE [FILE...]\n"
         "       lightgrep [OPTIONS] [-p PATTERN | -k FILE] [FILE...]\n\n"
#ifdef LIGHTGREP_CUSTOMER
    << "This copy provided EXCLUSIVELY to " << CUSTOMER_NAME << ".\n\n"
#endif
    << desc << std::endl;
}

void printEncodings() {
  const size_t slen = std::extent<decltype(LG_ENCODINGS)>::value;
  const uint32_t clen = std::extent<decltype(LG_CANONICAL_ENCODINGS)>::value;

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
    std::cout << LG_CANONICAL_ENCODINGS[i] << '\n';

    // print the aliases for the encoding
    for (const std::string& alias : aliases[i]) {
      std::cout << '\t' << alias << '\n';
    }
  }

  std::cout << std::endl;
}

void handleParseErrors(LG_Error* err, bool printFilename) {
  // walk the error chain
  for ( ; err; err = err->Next) {
    if (printFilename) {
      std::cerr << err->Source << ", ";
    }
    std::cerr << "pattern " << err->Index << ": " << err->Message << '\n';
  }

  std::cerr.flush();
}

size_t countErrors(LG_Error* err) {
  size_t numErrors = 0;
  for (const LG_Error* e = err; e; e = e->Next, ++numErrors);
  return numErrors;
}

void search(
  const std::string& input,
  bool mmapped,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitCounterInfo* hinfo,
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
  HitCounterInfo* hinfo,
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

std::unique_ptr<const char*[]> c_str_arr(const std::vector<std::string>& vec) {
  const size_t size = vec.size();
  std::unique_ptr<const char*[]> arr(new const char*[size]);
  for (uint32_t i = 0; i < size; ++i) {
    arr[i] = vec[i].c_str();
  }
  return arr;
}

template <class T>
std::tuple<
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)>,
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)>,
  std::unique_ptr<LG_Error,void(*)(LG_Error*)>
>
parsePatterns(const T& keyFiles,
              const std::vector<std::string>& defaultEncodings = { "ASCII" },
              const LG_KeyOptions& defaultOpts = {0, 0, 1})
{
  // read the patterns and parse them

  // FIXME: size the pattern map here?
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
    lg_create_program(0),
    lg_destroy_program
  );

  if (!prog) {
// FIXME: what do do here?
  }

  // FIXME: estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  if (!fsm) {
// FIXME: What to do here?
  }

  // set default encoding(s) of patterns which have none specified
  const std::unique_ptr<const char*[]> defEncs(c_str_arr(defaultEncodings));

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> err(nullptr, nullptr);
  LG_Error* tail_err = nullptr;

  for (const std::pair<std::string,std::string>& pf : keyFiles) {
    // parse a complete pattern file
    LG_Error* local_err = nullptr;

    lg_add_pattern_list(
      fsm.get(), prog.get(),
      pf.second.c_str(), pf.first.c_str(),
      defEncs.get(), defaultEncodings.size(), &defaultOpts, &local_err
    );

    if (local_err) {
      if (err) {
        // attach the new error to the existing chain
        tail_err->Next = local_err;
      }
      else {
        // first error, start a new error chain
        err = std::unique_ptr<LG_Error,void(*)(LG_Error*)>(
          local_err, lg_free_error
        );
        tail_err = local_err;
      }

      // walk to the end of the error chain
      for ( ; tail_err->Next; tail_err = tail_err->Next);
    }
  }

  return std::make_tuple(std::move(prog), std::move(fsm), std::move(err));
}

std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)>
loadProgram(const std::string& pfile) {
  std::ifstream pin(pfile, std::ios::in | std::ios::binary);
  if (!pin) {
    std::cerr << "Could not open program file " << pfile << std::endl;
    return std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)>(
      nullptr, nullptr
    );
  }

// FIXME: we need to handle the case where the read fails
// FIXME: what to do for the pattern map?

  const std::streampos end = stream_size(pin);
  std::cerr << "program file is " << end << " bytes long" << std::endl;

  std::vector<char> buf(end);
  pin.read(&buf[0], end);
  pin.close();

  return std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)>(
    lg_read_program(&buf[0], end),
    lg_destroy_program
  );
}

bool buildProgram(FSMHandle* fsm, ProgramHandle* prog, const Options& opts) {
  LG_ProgramOptions progOpts{opts.Determinize};

  if (lg_compile_program(fsm, prog, &progOpts)) {
    std::cerr << fsm->Impl->Fsm->verticesSize() << " vertices\n"
              << prog->Prog->size() << " instructions"
              << std::endl;
    return true;
  }
  else {
    std::cerr << "Failed to create program" << std::endl;
    return false;
  }
}


class Line {
public:
  friend std::istream& operator>>(std::istream& is, Line& l) {
    return std::getline(is, l.data);
  }

  operator std::string() const { return data; }

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

template <class T>
void search(
  T&& inputs,
  const Options& opts,
  bool& stdinUsed,
  SearchController& ctrl,
  ContextHandle* searcher,
  HitCounterInfo* hinfo,
  LG_HITCALLBACK_FN callback)
{
  if (opts.Recursive) {
    for (const std::string& i: inputs) {
      if (skipStdin(i, stdinUsed)) {
        continue;
      }

      const fs::path p(i);
      if (fs::is_directory(p)) {
        searchRecursively(p, opts.MemoryMapped, ctrl, searcher, hinfo, callback);
      }
      else {
        search(i, opts.MemoryMapped, ctrl, searcher, hinfo, callback);
      }
    }
  }
  else {
    for (const std::string& i: inputs) {
      if (skipStdin(i, stdinUsed)) {
        continue;
      }

      if (!fs::is_directory(fs::path(i))) {
        const fs::path p(i);
        search(i, opts.MemoryMapped, ctrl, searcher, hinfo, callback);
      }
    }
  }
}

void search(const Options& opts) {
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
    nullptr, nullptr
  );

  if (!opts.ProgramFile.empty()) {
    // read a program in from file
    prog = loadProgram(opts.ProgramFile);
  }
  else {
    // read the patterns and parse them
    std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(nullptr, nullptr);
    std::unique_ptr<LG_Error,void(*)(LG_Error*)> err(nullptr, nullptr);

    std::tie(prog, fsm, err) = parsePatterns(
      opts.getPatternLines(), opts.Encodings,
      {opts.LiteralMode, opts.CaseInsensitive, opts.UnicodeMode}
    );

    const bool printFilename =
      opts.CmdLinePatterns.empty() && opts.KeyFiles.size() > 1;

    handleParseErrors(err.get(), printFilename);

    // build a program from parsed patterns
    if (fsm) {
      if (!buildProgram(fsm.get(), prog.get(), opts)) {
        prog.reset();
      }
    }
  }

  if (!prog) {
    std::cerr << "Did not get a proper program" << std::endl;
    return;
  }

  // setup hit callback
  LG_HITCALLBACK_FN callback = 0;
  std::unique_ptr<HitCounterInfo> hinfo;

  if (opts.NoOutput) {
    callback = &nullWriter;
    hinfo.reset(new HitCounterInfo);
  }
  else if (opts.BeforeContext > -1 || opts.AfterContext > -1) {
    if (opts.PrintPath) {
      callback = &lineContextPathWriter;
      hinfo.reset(new LineContextPathWriterInfo(
        opts.openOutput(), prog.get(),
        std::max(opts.BeforeContext, 0),
        std::max(opts.AfterContext, 0),
        opts.GroupSeparator
      ));
    }
    else {
      callback = &lineContextHitWriter;
      hinfo.reset(new LineContextHitWriterInfo(
        opts.openOutput(), prog.get(),
        std::max(opts.BeforeContext, 0),
        std::max(opts.AfterContext, 0),
        opts.GroupSeparator
      ));
    }
  }
  else if (opts.PrintPath) {
    callback = &pathWriter;
    hinfo.reset(new PathWriterInfo(opts.openOutput(), prog.get()));
  }
  else {
    callback = &hitWriter;
    hinfo.reset(new HitWriterInfo(opts.openOutput(), prog.get()));
  }

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
        std::cerr << "Could not open input file list " << i << std::endl;
        return;
      }

      is = &ilf;
    }

    search(Lines(*is), opts, stdinUsed, ctrl, searcher.get(), hinfo.get(), callback);

    if (is->bad()) {
      std::cerr << "Error reading input file list " << i << ": "
                << std::strerror(errno) << std::endl;
    }
  }

  // serach each input file (positional args or stdin)
  if (!opts.Inputs.empty()) {
    search(opts.Inputs, opts, stdinUsed, ctrl, searcher.get(), hinfo.get(), callback);
  }

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

bool writeGraphviz(const Options& opts) {
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(nullptr, nullptr);
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(nullptr, nullptr);
  std::unique_ptr<LG_Error,void(*)(LG_Error*)> err(nullptr, nullptr);

  std::tie(prog, fsm, err) = parsePatterns(
    opts.getPatternLines(), opts.Encodings,
    {opts.LiteralMode, opts.CaseInsensitive, opts.UnicodeMode}
  );

  const bool printFilename =
    opts.CmdLinePatterns.empty() && opts.KeyFiles.size() > 1;

  handleParseErrors(err.get(), printFilename);

  std::cerr << "numErrors = " << countErrors(err.get()) << std::endl;

  if (!fsm) {
    return false;
  }

  // build the program to force determinization
  if (!buildProgram(fsm.get(), prog.get(), opts)) {
    return false;
  }

  // break on through the C API to print the graph
  writeGraphviz(opts.openOutput(), *fsm->Impl->Fsm);
  return true;
}

void writeProgram(const Options& opts) {
  // get the patterns and parse them
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(nullptr, nullptr);
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(nullptr, nullptr);
  std::unique_ptr<LG_Error,void(*)(LG_Error*)> err(nullptr, nullptr);

  std::tie(prog, fsm, err) = parsePatterns(
    opts.getPatternLines(), opts.Encodings,
    {opts.LiteralMode, opts.CaseInsensitive, opts.UnicodeMode}
  );

  const bool printFilename =
    opts.CmdLinePatterns.empty() && opts.KeyFiles.size() > 1;

  handleParseErrors(err.get(), printFilename);

  if (!fsm) {
    return;
  }

  if (!buildProgram(fsm.get(), prog.get(), opts)) {
    return;
  }

  fsm.reset();

  // break on through the C API to print the program
  ProgramPtr p(prog->Prog);
  std::cerr << p->size() << " instructions\n"
            << p->bufSize() << " program size in bytes" << std::endl;

  std::ostream& out(opts.openOutput());
  if (opts.Binary) {
    const std::vector<char> s = p->marshall();
    out.write(s.data(), s.size());
  }
  else {
    out << *p << std::endl;
  }
}

void validate(const Options& opts) {
  std::unique_ptr<LG_Error,void(*)(LG_Error*)> err(nullptr, nullptr);

  std::tie(std::ignore, std::ignore, err) = parsePatterns(
    opts.getPatternLines(), opts.Encodings,
    {opts.LiteralMode, opts.CaseInsensitive, opts.UnicodeMode}
  );

  for (const LG_Error* e = err.get(); e ; e = e->Next) {
    std::cerr << e->Index << ": pattern \"" << e->Pattern
              << "\" is invalid for encoding "
              << e->EncodingChain << std::endl;
  }
}

void writeSampleMatches(const Options& opts) {
// TODO: Writing sample matches should not be unconditionally EnCase-specific.
// There should be a switch to turn on the behavior EnCase needs.

	std::ostream& out(opts.openOutput());

  // Write a LE BOM because EnCase is retarded and expectes a BOM for UTF-16LE
  out << (char) 0xFF << (char) 0xFE;

  // parse the patterns one at a time
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(nullptr, nullptr);
  std::unique_ptr<LG_Error,void(*)(LG_Error*)> err(nullptr, nullptr);

  size_t pnum = 0;
  for (const std::pair<std::string,std::string>& pf : opts.getPatternLines()) {
    const std::pair<std::string,std::string> a[] = { pf };
    std::tie(std::ignore, fsm, err) = parsePatterns(
      a, opts.Encodings,
      {opts.LiteralMode, opts.CaseInsensitive, opts.UnicodeMode}
    );

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
    else if (fsm) {
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
  }
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
    case Options::SHOW_VERSION:
      printVersion();
      break;
    case Options::SHOW_HELP:
      printHelp(desc);
      break;
    case Options::LIST_ENCODINGS:
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
