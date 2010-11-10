#include <iostream>

#include <scope/testrunner.h>
#include <boost/program_options.hpp>
#include <boost/timer.hpp>
#include <boost/thread.hpp>
#include <fstream>

#include <boost/graph/graphviz.hpp>
#include <boost/bind.hpp>

#include "utility.h"
#include "vm_interface.h"
#include "hitwriter.h"
#include "options.h"


// <magic_incantation>
// this ridiculous piece of crap you see here is necessary to get
// boost_thread static libraries to link on Windows using MinGW
// found it in the boost issue tracker
extern "C" void tss_cleanup_implemented() { }
// </magic_incantation>


using namespace std;
namespace po = boost::program_options;

void startup(ProgramPtr p, const KwInfo& keyInfo, const Options& opts);

void writeGraphviz(const Options& opts) {
  std::vector<std::string> keys = opts.getKeys();
  if (!keys.empty()) {
    DynamicFSMPtr fsm = createDynamicFSM(keys, opts.getEncoding());
    writeGraphviz(opts.openOutput(), *fsm);
  }
}

void writeProgram(const Options& opts) {
  std::vector<std::string> keys = opts.getKeys();
  if (!keys.empty()) {
    DynamicFSMPtr fsm = createDynamicFSM(keys, opts.getEncoding());
    ProgramPtr p = createProgram(*fsm);
    std::ostream& out(opts.openOutput());
    out << p->size() << " instructions" << std::endl;
    out << *p;
  }
}

ProgramPtr initProgram(const Options& opts, KwInfo& keyInfo) {
  keyInfo.Keywords = opts.getKeys();
  std::cerr << keyInfo.Keywords.size() << " keywords"<< std::endl;

  DynamicFSMPtr fsm = createDynamicFSM(keyInfo, opts.getEncoding(), opts.CaseSensitive);
  std::cerr << boost::num_vertices(*fsm) << " vertices" << '\n';

  ProgramPtr p = createProgram(*fsm);
  std::cerr << p->size() << " instructions" << std::endl;

  p->Skip = calculateSkipTable(*fsm);
  p->First = firstBytes(*fsm);
  
  boost::shared_ptr<SkipTable> skip(calculateSkipTable(*fsm));
  std::cerr << skip->l_min() << " lmin" << std::endl;
  const std::vector<uint32>& skipVec(skip->skipVec());
  uint32 numMax = 0;
  double total = 0;
  for (uint32 i = 0; i < 256; ++i) {
    total += skipVec[i];
    if (skipVec[i] == skip->l_min()) {
      ++numMax;
    }
  }
  std::cerr << numMax << " numMaxSkips" << std::endl;
  std::cerr << (total/256) << " averageSkip" << std::endl;
  return p;
}

boost::shared_ptr<VmInterface> initSearch(const Options& opts, KwInfo& keyInfo) {
  ProgramPtr p = initProgram(opts, keyInfo);

  boost::shared_ptr<VmInterface> ret = VmInterface::create();
  ret->init(p);
  ret->setDebugRange(opts.DebugBegin, opts.DebugEnd);
  return ret;
}

static const unsigned int BLOCKSIZE = 10 * 1024 * 1024;

uint64 readNext(ifstream* file, byte* buf) {
  file->read((char*)buf, BLOCKSIZE);
  return file->gcount();
}

void printHelp(const po::options_description& desc) {
  std::cout << "lightgrep, Copyright (c) 2010, Lightbox Technologies, Inc." << "\n\n"
    << "Usage: lightgrep [OPTION]... PATTERN_FILE [FILE]\n\n"
    << desc << std::endl;
}

void search(const Options& opts) {
  std::ifstream file(opts.Input.c_str(), ios::in | ios::binary | ios::ate);
  if (file) {
    file.rdbuf()->pubsetbuf(0, 0);
    KwInfo keyInfo;
    boost::shared_ptr<VmInterface> search = initSearch(opts, keyInfo);

    HitWriter cb(opts.openOutput(), keyInfo.PatternsTable, keyInfo.Keywords, keyInfo.Encodings);

    uint64 size = file.tellg(),
           offset = 0;
    byte* block = new byte[BLOCKSIZE];
    {
      boost::timer searchClock;
      file.seekg(0, ios::beg);

      if (size > BLOCKSIZE) {
        byte* block2 = new byte[BLOCKSIZE],
            * cur = block,
            * next = block2;
        uint64 blkSize = BLOCKSIZE;
        file.read((char*)block, BLOCKSIZE);
        do {
          boost::packaged_task<uint64> task(boost::bind(&readNext, &file, next));
          boost::unique_future<uint64> sizeFut = task.get_future();
          boost::thread exec(boost::move(task));

          search->search(cur, cur + blkSize, offset, cb);

          size -= blkSize;
          offset += blkSize;
          blkSize = sizeFut.get();
          std::swap(cur, next);
        } while (size > BLOCKSIZE);
        // assert: all data has been read, size - blkSize == 0
        search->search(cur, cur + blkSize, offset, cb);
        cur = next = 0;
        delete [] block2;
      }
      else {
        file.read((char*)block, size);
        search->search(block, block + size, offset, cb);
      }
      double t = searchClock.elapsed();
      std::cerr << t << " searchTime" << std::endl;
      std::cerr << cb.NumHits << " hits" << std::endl;
    }
    file.close();
    delete [] block;
    // delete [] argArray;
  }  
}

int main(int argc, char** argv) {
  Options opts;

  po::options_description desc("Allowed Options");
  po::positional_options_description posOpts;
  posOpts.add("keywords", 1);
  posOpts.add("input", 1);
  desc.add_options()
    ("help", "produce help message")
    ("test", "run unit tests (same as test command)")
    ("encoding,e", po::value< std::string >(&opts.Encoding)->default_value("ascii"), "encodings to use [ascii|ucs16|both]")
    ("command,c", po::value< std::string >(&opts.Command)->default_value("search"), "command to perform [search|graph|prog|test|server]")
    ("keywords,k", po::value< std::string >(&opts.KeyFile), "path to file containing keywords")
    ("input", po::value< std::string >(&opts.Input)->default_value("-"), "file to search")
    ("output,o", po::value< std::string >(&opts.Output)->default_value("-"), "output file (stdout default)")
    ("ignore-case,i", "file to search")
    ("pattern,p", po::value< std::string >(&opts.Pattern), "a single keyword on the command-line")
    #ifdef LBT_TRACE_ENABLED
    ("begin-debug", po::value< uint64 >(&opts.DebugBegin)->default_value(std::numeric_limits<uint64>::max()), "offset for beginning of debug logging")
    ("end-debug", po::value< uint64 >(&opts.DebugEnd)->default_value(std::numeric_limits<uint64>::max()), "offset for end of debug logging")
    #endif
    ;
  
  po::variables_map optsMap;
  try {
    po::store(po::command_line_parser(argc, argv).options(desc).positional(posOpts).run(), optsMap);
    po::notify(optsMap);
    opts.CaseSensitive = optsMap.count("ignore-case") == 0;
    if (optsMap.count("help")) {
      printHelp(desc);
    }
    else if (opts.Command == "test" || optsMap.count("test")) {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
    if (opts.Command == "search" && optsMap.count("keywords")) {
      search(opts);
    }
    else if (opts.Command == "graph") {
      writeGraphviz(opts);
    }
    else if (opts.Command == "prog") {
      writeProgram(opts);
    }
    else if (opts.Command == "server") {
      KwInfo keyInfo;
      ProgramPtr p = initProgram(opts, keyInfo);
      startup(p, keyInfo, opts);
    }
    else {
      std::cerr << "Unrecognized. Use --help for list of options." << std::endl;
    }
  }
  catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n\n";
    printHelp(desc);
    return 1;
  }
  return 0;
}
