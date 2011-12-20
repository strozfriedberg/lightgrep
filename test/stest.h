#pragma once

#include "graph.h"
#include "parser.h"
#include "utility.h"
#include "vm_interface.h"

void collector(void* userData, const LG_SearchHit* const hit);

//struct STest: public HitCallback {
struct STest {
  std::vector< SearchHit > Hits;
  GraphPtr Fsm;
  ProgramPtr Prog;
  boost::shared_ptr<VmInterface> Grep;

  STest(const std::string& key) {
    std::vector<std::string> kws;
    kws.push_back(key);
    init(kws);
  }

  STest(const std::vector<std::string>& keys) {
    init(keys);
  }

  STest(uint32 num, const char** keys) {
    std::vector<std::string> kws(num);
    for (unsigned int i = 0; i < num; ++i) {
      kws[i] = keys[i];
    }
    init(kws);
  }

  void init(const std::vector<std::string>& kws) {
    Fsm = createGraph(kws, CP_ASCII, true, false, true, true);
    Prog = createProgram(*Fsm);
    Prog->First = firstBytes(*Fsm);
    Prog->Skip = calculateSkipTable(*Fsm);
    Grep = VmInterface::create();
    Grep->init(Prog);
  }

  void search(const byte* begin, const byte* end, uint64 offset) {
    Grep->search(begin, end, offset, collector, this);
    Grep->closeOut(collector, this);
  }

  void startsWith(const byte* begin, const byte* end, uint64 offset) {
    Grep->startsWith(begin, end, offset, collector, this);
  }
};

void collector(void* userData, const LG_SearchHit* const hit);

