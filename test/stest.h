#pragma once

#include <algorithm>
#include <initializer_list>
#include <vector>

#include "automata.h"
#include "parser.h"
#include "pattern.h"
#include "vm_interface.h"
#include "utility.h"

void collector(void* userData, const LG_SearchHit* const hit);

Pattern makePattern(const std::string& s);

struct STest {
  std::vector<SearchHit> Hits;
  NFAPtr Fsm;
  ProgramPtr Prog;
  boost::shared_ptr<VmInterface> Grep;

  STest(const char* key) {
    std::initializer_list<const char*> keys = { key };
    init(keys);
  }

  STest(std::initializer_list<const char*> keys) {
    init(keys);
  }

  template <typename T>
  STest(const T& keys) {
    init(keys);
  }

  template <typename T>
  void init(const T& keys) {
    std::vector<Pattern> pats;
    std::transform(keys.begin(), keys.end(),
                   std::back_inserter(pats), makePattern);

    Fsm = createGraph(pats, true, true);
    if (Fsm) {
      Prog = createProgram(*Fsm);
      Prog->First = firstBytes(*Fsm);
      Grep = VmInterface::create();
      Grep->init(Prog);
    }
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
