#pragma once

#include <initializer_list>

#include "automata.h"
#include "parser.h"
#include "pattern.h"
#include "vm_interface.h"

void collector(void* userData, const LG_SearchHit* const hit);

struct STest {
  std::vector<SearchHit> Hits;
  NFAPtr Fsm;
  ProgramPtr Prog;
  boost::shared_ptr<VmInterface> Grep;

  STest(const std::string& key) {
    std::vector<Pattern> kws;
    kws.push_back(key);
    init(kws);
  }

  STest(const std::initializer_list<const char*>& keys);

  STest(const std::vector<std::string>& keys);

  void init(const std::vector<Pattern>& kws);

  void search(const byte* begin, const byte* end, uint64 offset) {
    Grep->search(begin, end, offset, collector, this);
    Grep->closeOut(collector, this);
  }

  void startsWith(const byte* begin, const byte* end, uint64 offset) {
    Grep->startsWith(begin, end, offset, collector, this);
  }
};

void collector(void* userData, const LG_SearchHit* const hit);
