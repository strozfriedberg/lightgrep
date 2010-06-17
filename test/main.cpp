#include <iostream>

#include <scope/testrunner.h>
#include <boost/timer.hpp>
#include <boost/thread.hpp>
#include <fstream>

#include <boost/graph/graphviz.hpp>
#include <boost/bind.hpp>

#include "utility.h"
#include "vm.h"

using namespace std;

class StdOutHits: public HitCallback {
public:
  uint64  NumHits;

  StdOutHits(): NumHits(0) {}

  virtual void collect(const SearchHit& hit) {
    std::cout << NumHits << '\t' << hit.Offset << '\t' << hit.Length << '\t' << hit.Label << '\n';
    ++NumHits;
  }
};

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

void writeGraphviz(const std::string& keyFilePath) {
  std::vector<std::string> keys;
  if (readKeyFile(keyFilePath, keys)) {
    DynamicFSMPtr fsm = createDynamicFSM(keys);
    writeGraphviz(std::cout, *fsm);
  }
}

void writeProgram(const std::string& keyFilePath) {
  std::vector<std::string> keys;
  if (readKeyFile(keyFilePath, keys)) {
    DynamicFSMPtr fsm = createDynamicFSM(keys);
    ProgramPtr p = createProgram(*fsm);
    std::cout << p->size() << " instructions" << std::endl;
    std::cout << *p;
  }
}

boost::shared_ptr<Vm> initSearch(const std::string& keyFilePath) {
  std::vector<std::string> keys;
  readKeyFile(keyFilePath, keys);
  std::cerr << keys.size() << " keywords"<< std::endl;
  DynamicFSMPtr fsm = createDynamicFSM(keys);

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

int main(int argc, char** argv) {
  if (argc > 1) {
    std::string first(argv[1]);
    if (first == "test") {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
    else if (argc > 2 && first == "search") {
      std::ifstream file(argv[3], ios::in | ios::binary | ios::ate);
      if (file) {
        file.rdbuf()->pubsetbuf(0, 0);
        boost::shared_ptr<Vm> search = initSearch(argv[2]);

        StdOutHits cb;

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
    else if (argc > 2 && first == "gv") {
      writeGraphviz(argv[2]);
    }
    else if (argc > 2 && first == "prog") {
      writeProgram(argv[2]);
    }
  }
  return 0;
}
