#include <iostream>

#include <scope/testrunner.h>
#include <boost/timer.hpp>
#include <fstream>

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
      char line[1024];
      keyFile.getline(line, 1024);
      std::string lineS(line);
      if (!lineS.empty()) {
        keys.push_back(lineS);
        // std::cerr << "read " << lineS << std::endl;
      }
    }
    return !keys.empty();
  }
  else {
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

boost::shared_ptr<Vm> initSearch(const std::string& keyFilePath) {
  std::vector<std::string> keys;
  readKeyFile(keyFilePath, keys);
  std::cerr << keys.size() << " keywords"<< std::endl;
  DynamicFSMPtr fsm = createDynamicFSM(keys);

  std::cerr << boost::num_vertices(*fsm) << " vertices" << '\n';
  std::cerr << boost::num_edges(*fsm) << " edges" << std::endl;

  ProgramPtr p = createProgram(*fsm);

  std::cerr << p->size() << " instructions" << std::endl;
  
  boost::shared_ptr<Vm> ret(new Vm);
  ret->init(p, firstBytes(*fsm), 1);
  return ret;
}

static const unsigned int BLOCKSIZE = 1024 * 1024;

int main(int argc, char** argv) {
  if (argc > 1) {
    std::string first(argv[1]);
    if (first == "test") {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
    else if (argc > 2 && first == "search") {
      std::ifstream file(argv[3], ios::in | ios::binary | ios::ate);
      if (file) {
        boost::shared_ptr<Vm> search = initSearch(argv[2]);

        StdOutHits cb;

        uint64 size = file.tellg(),
               offset = 0;
        byte* block = new byte[BLOCKSIZE];
        {
          boost::timer searchClock;
          file.seekg(0, ios::beg);
          while (size > BLOCKSIZE) {
            file.read((char*)block, BLOCKSIZE);
            search->search(block, block + BLOCKSIZE, offset, cb);
            size -= BLOCKSIZE;
            offset += BLOCKSIZE;
          }
          file.read((char*)block, size);
          search->search(block, block + size, offset, cb);
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
  }
  return 0;
}
