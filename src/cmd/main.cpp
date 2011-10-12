#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>

#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/timer.hpp>
#include <boost/graph/graphviz.hpp>

#include "encodings.h"
#include "hitwriter.h"
#include "lightgrep_c_api.h"
#include "options.h"
#include "optparser.h"
#include "utility.h"

#include "include_boost_thread.h"

// <magic_incantation>
// this ridiculous piece of crap you see here is necessary to get
// boost_thread static libraries to link on Windows using MinGW
// found it in the boost issue tracker
namespace boost {
  void tss_cleanup_implemented() { }
}
// </magic_incantation>

namespace po = boost::program_options;

void startup(ProgramPtr p, const KwInfo& keyInfo, const Options& opts);

void writeGraphviz(const Options& opts) {
  std::vector<std::string> keys = opts.getKeys();
  if (!keys.empty()) {
    GraphPtr fsm = createGraph(keys, opts.getEncoding(), opts.CaseSensitive, opts.LiteralMode, opts.Determinize);
    if (fsm) {
      writeGraphviz(opts.openOutput(), *fsm);
    }
  }

/*
  // parse patterns and get index and encoding info for hit writer
  const std::vector<std::string>& patterns(opts.getKeys());
  std::vector< std::pair<uint32,uint32> > patInfo;
  std::vector<std::string> encodings;

  boost::shared_ptr<void> parser(
    parsePatterns(opts, patterns, patInfo, encodings)
  );

  // build the program
  boost::shared_ptr<void> prog(buildProgram(parser.get(), opts));
*/

}

void writeProgram(const Options& opts) {
  std::vector<std::string> keys = opts.getKeys();
  if (!keys.empty()) {
    GraphPtr fsm = createGraph(keys, opts.getEncoding(), opts.CaseSensitive, opts.LiteralMode, opts.Determinize);
    if (fsm) {
      ProgramPtr p = createProgram(*fsm);
      std::ostream& out(opts.openOutput());
      out << p->size() << " instructions" << std::endl;
      out << *p;
    }
  }
}

uint64 readNext(FILE* file, byte* buf, unsigned int blockSize) {
  return fread((void*)buf, 1, blockSize, file);
}

void printHelp(const po::options_description& desc) {
  std::cout
    << "lightgrep, Copyright (c) 2010-2011, Lightbox Technologies, Inc."
    << "\nCreated " << __DATE__ << "\n\n"
    << "Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]\n\n"
    << "This copy provided EXCLUSIVELY to the U.S. Army, CCIU, DFRB\n\n"
    << desc << std::endl;
}

void addPattern(
  LG_HPARSER parser,
  const std::string& pattern,
  uint32 i,
  uint32 patIdx,
  const LG_KeyOptions& keyOpts,
  std::vector< std::pair<uint32,uint32> >& patInfo,
  const std::vector<std::string>& encodings)
{
  const char* error = 0;

  patInfo.push_back(std::make_pair(i, encodings.size()-1));

  if (!lg_add_keyword(parser, pattern.c_str(), patIdx, &keyOpts, &error)) {
    std::cerr << error << " on pattern "
              << i << ", '" << pattern << "'" << std::endl;
  }
}

boost::shared_ptr<void> parsePatterns(
  const Options& opts,
  const std::vector<std::string>& patterns,
  std::vector< std::pair<uint32,uint32> >& patInfo,
  std::vector<std::string>& encodings)
{
  // get patterns from options
  std::cerr << patterns.size() << " pattern";
  if (patterns.size() != 1) {
    std::cerr << 's';
  }
  std::cerr << std::endl;

  if (patterns.empty()) {
    return boost::shared_ptr<void>();
  }

  // find total length of patterns
  const uint32 tlen = std::accumulate(
    patterns.begin(), patterns.end(), 0,
    boost::bind(std::plus<uint32>(), _1, boost::bind(&std::string::size, _2))
  );

// FIXME: very BAD if we pass 0 as sizeHint
  boost::shared_ptr<void> parser(lg_create_parser(tlen), lg_destroy_parser);

  // set up parsing options
  LG_KeyOptions keyOpts;
  keyOpts.CaseInsensitive = !opts.CaseSensitive;
  keyOpts.FixedString = opts.LiteralMode;

  // parse patterns
  uint32 patIdx = 0;

  if (opts.getEncoding() & CP_ASCII) {
//    keyOpts.Encoding = LG_SUPPORTED_ENCODINGS[LG_ENC_ASCII];
    keyOpts.Encoding = "ASCII";
    encodings.push_back("ASCII");

    for (uint32 i = 0; i < patterns.size(); ++i, ++patIdx) {
      addPattern(
        parser.get(), patterns[i], i, patIdx, keyOpts, patInfo, encodings
      );
    }
  }

  if (opts.getEncoding() & CP_UCS16) {
//    keyOpts.Encoding = LG_SUPPORTED_ENCODINGS[LG_UTF_16];
    keyOpts.Encoding = "UTF-16";
    encodings.push_back("UTF-16");

    for (uint32 i = 0; i < patterns.size(); ++i, ++patIdx) {
      addPattern(
        parser.get(), patterns[i], i, patIdx, keyOpts, patInfo, encodings
      );
    }
  }

  return parser;
}

boost::shared_ptr<void> buildProgram(LG_HPARSER parser, const Options& opts) {
  LG_ProgramOptions progOpts;
  progOpts.Determinize = opts.Determinize;

  return boost::shared_ptr<void>(
    lg_create_program(parser, &progOpts),
    lg_destroy_program
  );
}

void search(const Options& opts) {
  // try to open our input
  FILE *file = opts.Input == "-" ? stdin : fopen(opts.Input.c_str(), "rb");
  if (!file) {
    std::cerr << "Could not open file " << opts.Input << std::endl;
    return;
  }

  setbuf(file, 0); // unbuffered, bitte

  // parse patterns and get index and encoding info for hit writer
  const std::vector<std::string>& patterns(opts.getKeys());
  std::vector< std::pair<uint32,uint32> > patInfo;
  std::vector<std::string> encodings;

  boost::shared_ptr<void> parser(
    parsePatterns(opts, patterns, patInfo, encodings)
  );

  // build the program
  boost::shared_ptr<void> prog(buildProgram(parser.get(), opts)); 

  // go free, little parser
  parser.reset();

  // setup hit callback
  LG_HITCALLBACK_FN callback;
  boost::scoped_ptr<HitCounterInfo> hinfo;

  if (opts.NoOutput) {
    callback = nullWriter;
    hinfo.reset(new HitCounterInfo);
  }
  else if (opts.PrintPath) {
    callback = pathWriter;
    hinfo.reset(
      new PathWriterInfo(
        opts.Input, opts.openOutput(), patInfo, patterns, encodings
      )
    );
  }
  else {
    callback = hitWriter;
    hinfo.reset(
      new HitWriterInfo(opts.openOutput(), patInfo, patterns, encodings)
    );
  }

  // search
  boost::shared_ptr<void> searcher(lg_create_context(prog.get()),
                                   lg_destroy_context);

  byte* cur = new byte[opts.BlockSize];
  uint64 blkSize = 0,
         offset = 0;

  blkSize = readNext(file, cur, opts.BlockSize);

  // init timer here so as not to time the first read
  double lastTime = 0.0;
  boost::timer searchClock;

  if (!feof(file)) {
    byte* next = new byte[opts.BlockSize];
    do {
      // read the next block on a separate thread
      boost::packaged_task<uint64> task(boost::bind(&readNext, file, next, opts.BlockSize));
      boost::unique_future<uint64> sizeFut = task.get_future();
      boost::thread exec(boost::move(task));

      // search cur block
      lg_search(searcher.get(), (char*) cur, (char*) cur + blkSize, offset, hinfo.get(), callback);

      offset += blkSize;
      if (offset % (1024 * 1024 * 1024) == 0) { // should change this due to the block size being variable
        lastTime = searchClock.elapsed();
        uint64 units = offset >> 20;
        double bw = units / lastTime;
        units >>= 10;
        std::cerr << units << " GB searched in " << lastTime << " seconds, " << bw << " MB/s avg" << std::endl;
      }
      blkSize = sizeFut.get(); // block on i/o thread completion
      std::swap(cur, next);
    } while (!feof(file)); // note file is shared btwn threads, but safely
    delete[] next;
  }

  // assert: all data has been read, offset + blkSize == file size,
  // cur is last block
  lg_search(searcher.get(), (char*) cur, (char*) cur + blkSize, offset, hinfo.get(), callback);
  lg_closeout_search(searcher.get(), hinfo.get(), callback);

  offset += blkSize;  // be sure to count the last block
  lastTime = searchClock.elapsed();
  std::cerr << offset << " bytes" << std::endl;
  std::cerr << lastTime << " searchTime" << std::endl;
  if (lastTime > 0.0) {
    std::cerr << offset/lastTime/(1 << 20);
  }
  else {
    std::cerr << "+inf";
  }
  std::cerr << " MB/s avg" << std::endl;
  std::cerr << hinfo->NumHits << " hits" << std::endl;

  fclose(file);
  delete[] cur;
}

int main(int argc, char** argv) {
  Options opts;
  po::options_description desc("Allowed Options");
  try {
    parse_opts(argc, argv, desc, opts);

    if (opts.Command == "search") {
      search(opts);
    }
    else if (opts.Command == "server") {
/*
      KwInfo keyInfo;
      ProgramPtr p = initProgram(opts, keyInfo);
      if (!p) {
        std::cerr << "Could not initialize search engine for server mode" << std::endl;
        return 1;
      }
      startup(p, keyInfo, opts);
*/
    }
    else if (opts.Command == "help") {
      printHelp(desc);
    }
    else if (opts.Command == "graph") {
      writeGraphviz(opts);
    }
    else if (opts.Command == "prog") {
      writeProgram(opts);
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
