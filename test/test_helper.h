#pragma once

#include "graph.h"
#include "parser.h"
#include "utility.h"
#include "vm_interface.h"

void edge(Graph::vertex source, Graph::vertex target, Graph& fsm, TransitionPtr tPtr);

void edge(Graph::vertex source, Graph::vertex target, Graph& fsm, Transition* tPtr);

void ASSERT_SUPERGRAPH(const Graph& a, const Graph& b);

void ASSERT_EQUAL_GRAPHS(const Graph& a, const Graph& b);

void ASSERT_EQUAL_LABELS(const Graph& a, const Graph& b);

void ASSERT_EQUAL_MATCHES(const Graph& a, const Graph& b);

struct STest: public HitCallback {
  std::vector< SearchHit > Hits;
  GraphPtr Fsm;
  ProgramPtr Prog;
  boost::shared_ptr<VmInterface> Grep;

  STest(const std::string& key) {
    std::vector<std::string> kws;
    kws.push_back(key);
    init(kws);
  }

  STest(uint32 num, const char** keys) {
    std::vector<std::string> kws(num);
    for (unsigned int i = 0; i < num; ++i) {
      kws[i] = keys[i];
    }
    init(kws);
  }

  void init(const std::vector<std::string>& kws) {
    Fsm = createGraph(kws);
    Prog = createProgram(*Fsm);
    Prog->First = firstBytes(*Fsm);
    Prog->Skip = calculateSkipTable(*Fsm);
    Grep = VmInterface::create();
    Grep->init(Prog);
  }

  void search(const byte* begin, const byte* end, uint64 offset, HitCallback& cb) {
    Grep->search(begin, end, offset, cb);
    Grep->closeOut(cb);
  }

  void startsWith(const byte* begin, const byte* end, uint64 offset, HitCallback& cb) {
    Grep->startsWith(begin, end, offset, cb);
  }

  virtual void collect(const SearchHit& hit) {
    Hits.push_back(hit);
  }
};
