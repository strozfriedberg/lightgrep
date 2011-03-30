#include <cstdio>
#include <fstream>
#include <iostream>

#include <scope/testrunner.h>
#include <boost/program_options.hpp>
#include <boost/timer.hpp>

#include <boost/graph/graphviz.hpp>
#include <boost/bind.hpp>

#include "utility.h"
#include "vm_interface.h"
#include "hitwriter.h"
#include "options.h"
#include "optparser.h"

#define BOOST_USE_WINDOWS_H
#include <boost/thread.hpp>

// <magic_incantation>
// this ridiculous piece of crap you see here is necessary to get
// boost_thread static libraries to link on Windows using MinGW
// found it in the boost issue tracker
extern "C" void tss_cleanup_implemented() { }
// </magic_incantation>


namespace po = boost::program_options;

void startup(ProgramPtr p, const KwInfo& keyInfo, const Options& opts);

void writeGraphviz(const Options& opts) {
  std::vector<std::string> keys = opts.getKeys();
  if (!keys.empty()) {
    GraphPtr fsm = createGraph(keys, opts.getEncoding(), opts.CaseSensitive, opts.LiteralMode);
    writeGraphviz(opts.openOutput(), *fsm);
  }
}

void writeProgram(const Options& opts) {
  std::vector<std::string> keys = opts.getKeys();
  if (!keys.empty()) {
    GraphPtr fsm = createGraph(keys, opts.getEncoding(), opts.CaseSensitive, opts.LiteralMode);
    ProgramPtr p = createProgram(*fsm);
    std::ostream& out(opts.openOutput());
    out << p->size() << " instructions" << std::endl;
    out << *p;
  }
}

ProgramPtr initProgram(const Options& opts, KwInfo& keyInfo) {
  ProgramPtr p;
  keyInfo.Keywords = opts.getKeys();
  std::cerr << keyInfo.Keywords.size() << " keywords"<< std::endl;
  if (keyInfo.Keywords.empty()) {
    return p;
  }
  GraphPtr fsm = createGraph(keyInfo, opts.getEncoding(), opts.CaseSensitive, opts.LiteralMode);
  std::cerr << fsm->numVertices() << " vertices" << '\n';

  p = createProgram(*fsm);
  std::cerr << p->size() << " instructions" << std::endl;

  p->Skip = calculateSkipTable(*fsm);
  p->First = firstBytes(*fsm);
  
  std::cerr << p->Skip->l_min() << " lmin" << std::endl;
  uint32 numMax = 0;
  double total = 0;
  for (uint32 i = 0; i < 256; ++i) {
    total += p->Skip->skipVec()[i];
    if (p->Skip->skipVec()[i] == p->Skip->l_min()) {
      ++numMax;
    }
  }
  std::cerr << numMax << " numMaxSkips" << std::endl;
  std::cerr << (total/256) << " averageSkip" << std::endl;
  return p;
}

boost::shared_ptr<VmInterface> initSearch(const Options& opts, KwInfo& keyInfo) {
  ProgramPtr p = initProgram(opts, keyInfo);
  if (!p) {
    return boost::shared_ptr<VmInterface>();
  }
  boost::shared_ptr<VmInterface> ret = VmInterface::create();
  #ifdef LBT_TRACE_ENABLED
  ret->setDebugRange(opts.DebugBegin, opts.DebugEnd);
  #endif
  ret->init(p);
  return ret;
}

static const unsigned int BLOCKSIZE = 8 * 1024 * 1024;

uint64 readNext(FILE* file, byte* buf) {
  return fread((void*)buf, 1, BLOCKSIZE, file);
}

void printHelp(const po::options_description& desc) {
  std::cout << "lightgrep, Copyright (c) 2010-2011, Lightbox Technologies, Inc." << "\nCreated " << __DATE__ << "\n\n"
    << "Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]\n\n"
    << "This copy provided EXCLUSIVELY to the U.S. Army, CCIU, DFRB\n\n"
    << desc << std::endl;
}

void search(const Options& opts) {
  FILE *file = opts.Input == "-" ? stdin : fopen(opts.Input.c_str(), "rb");
  if (!file) {
    std::cerr << "Could not open file " << opts.Input << std::endl;
    return;
  }

  setbuf(file, 0); // unbuffered, bitte
  KwInfo keyInfo;
  boost::shared_ptr<VmInterface> search = initSearch(opts, keyInfo);
  if (!search) {
    std::cerr << "could not initialize search engine" << std::endl;
    return;
  }
  
  double lastTime = 0.0;
  boost::timer searchClock;
  HitWriter output(opts.openOutput(), keyInfo.PatternsTable,
                   keyInfo.Keywords, keyInfo.Encodings);
  NullWriter   devNull;
  HitCounter*  cb = 0;
  if (opts.NoOutput) {
    cb = &devNull;
  }
  else {
    cb = &output;
  }

  byte* cur  = new byte[BLOCKSIZE];
  uint64 blkSize = 0,
         offset = 0;

  blkSize = readNext(file, cur);
  if (!feof(file)) {
    byte* next = new byte[BLOCKSIZE];
    do {
      // read the next block on a separate thread
      boost::packaged_task<uint64> task(boost::bind(&readNext, file, next));
      boost::unique_future<uint64> sizeFut = task.get_future();
      boost::thread exec(boost::move(task));

      search->search(cur, cur + blkSize, offset, *cb); // search cur block

      offset += blkSize;
      if (offset % (1024 * 1024 * 1024) == 0) { // should happen every 128 blocks
        lastTime = searchClock.elapsed();
        uint64 units = offset >> 20;
        double bw = units / lastTime;
        units >>= 10;
        std::cerr << units << " GB searched in " << lastTime << " seconds, " << bw << " MB/s avg" << std::endl;
      }
      blkSize = sizeFut.get(); // block on i/o thread completion
      std::swap(cur, next);
    } while (!feof(file)); // note file is shared btwn threads, but safely
    delete [] next;
  }
  // assert: all data has been read, offset + blkSize == file size, cur is last block
  search->search(cur, cur + blkSize, offset, *cb);
  search->closeOut(*cb);

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
  std::cerr << cb->NumHits << " hits" << std::endl;

  fclose(file);
  delete [] cur;
  // delete [] argArray;
}

int main(int argc, char** argv) {
  Options opts;
  po::options_description desc("Allowed Options");

  try {
    parse_opts(argc, argv, desc, opts);

    if (opts.Command == "search") {
      search(opts);
    }
    else if (opts.Command == "test") {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
    else if (opts.Command == "server") {
      KwInfo keyInfo;
      ProgramPtr p = initProgram(opts, keyInfo);
      if (!p) {
        std::cerr << "Could not initialize search engine for server mode" << std::endl;
        return 1;
      }
      startup(p, keyInfo, opts);
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
