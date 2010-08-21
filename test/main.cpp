#include <iostream>

#include <scope/testrunner.h>
#include <boost/program_options.hpp>
#include <boost/timer.hpp>
#include <boost/thread.hpp>
#include <fstream>

#include <boost/graph/graphviz.hpp>
#include <boost/bind.hpp>

#include "utility.h"
#include "vm.h"
#include "hitwriter.h"

using namespace std;
namespace po = boost::program_options;

bool readKeyFile(const std::string& keyFilePath, std::vector<std::string>& keys) {
  std::ifstream keyFile(keyFilePath.c_str(), ios::in);
  keys.clear();
  if (keyFile) {
    while (keyFile) {
      char line[8192];
      keyFile.getline(line, 8192);
      std::string lineS(line);
      if (!lineS.empty()) {
        keys.push_back(lineS);
        // std::cerr << "read " << lineS << std::endl;
      }
    }
    return !keys.empty();
  }
  else {
    std::cerr << "Could not open file" << std::endl;
    return false;
  }
}

void writeGraphviz(const std::string& keyFilePath, uint32 enc) {
  std::vector<std::string> keys;
  if (readKeyFile(keyFilePath, keys)) {
    DynamicFSMPtr fsm = createDynamicFSM(keys, enc);
    writeGraphviz(std::cout, *fsm);
  }
}

void writeProgram(const std::string& keyFilePath, uint32 enc) {
  std::vector<std::string> keys;
  if (readKeyFile(keyFilePath, keys)) {
    DynamicFSMPtr fsm = createDynamicFSM(keys, enc);
    ProgramPtr p = createProgram(*fsm);
    std::cout << p->size() << " instructions" << std::endl;
    std::cout << *p;
  }
}

boost::shared_ptr<Vm> initSearch(const std::string& keyFilePath, uint32 enc) {
  std::vector<std::string> keys;
  readKeyFile(keyFilePath, keys);
  std::cerr << keys.size() << " keywords"<< std::endl;
  DynamicFSMPtr fsm = createDynamicFSM(keys, enc);

  std::cerr << boost::num_vertices(*fsm) << " vertices" << '\n';

  ProgramPtr p = createProgram(*fsm);

  std::cerr << p->size() << " instructions" << std::endl;
  
  boost::shared_ptr<Vm> ret(new Vm);
  ret->init(p, firstBytes(*fsm), 1);
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

void search(const string& keyfile, const string& input, uint32 enc) {
  std::ifstream file(input.c_str(), ios::in | ios::binary | ios::ate);
  if (file) {
    file.rdbuf()->pubsetbuf(0, 0);
    boost::shared_ptr<Vm> search = initSearch(keyfile, enc);

    HitWriter cb(std::cout);

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
  string cmd,
         encoding,
         keyfile,
         input;

  po::options_description desc("Allowed Options");
  po::positional_options_description posOpts;
  posOpts.add("keywords", 1);
  posOpts.add("input", 1);
  desc.add_options()
    ("help", "produce help message")
    ("test", "run unit tests (same as test command)")
    ("encoding,e", po::value< std::string >(&encoding)->default_value("ascii"), "encodings to use [ascii|ucs16|both]")
    ("command,c", po::value< std::string >(&cmd)->default_value("search"), "command to perform [search|graph|prog|test]")
    ("keywords,k", po::value< std::string >(&keyfile), "path to file containing keywords")
    ("input,i", po::value< std::string >(&input)->default_value("-"), "file to search");
  
  po::variables_map opts;
  try {
    po::store(po::command_line_parser(argc, argv).options(desc).positional(posOpts).run(), opts);
    po::notify(opts);
    if (opts.count("help")) {
      printHelp(desc);
    }
    else if (cmd == "test" || opts.count("test")) {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
    uint32 enc = 0;
    if (encoding == "ascii" || encoding == "both") {
      enc |= CP_ASCII;
    }
    if (encoding == "ucs16" || encoding == "both") {
      enc |= CP_UCS16;
    }
    if (cmd == "search") {
      search(keyfile, input, enc);
    }
    else if (cmd == "graph") {
      writeGraphviz(keyfile, enc);
    }
    else if (cmd == "prog") {
      writeProgram(keyfile, enc);
    }
  }
  catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n\n";
    printHelp(desc);
    return 1;
  }
  return 0;
}
