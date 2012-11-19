#pragma once

#include "basic.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"

class FSMThingy {
public:
  FSMThingy(uint32 sizeHint);

  NFABuilder Nfab;
  NFAOptimizer Comp;
  NFAPtr Fsm;

  std::map<std::string,std::shared_ptr<Encoder>> Encoders;

  void addPattern(const ParseTree& tree, const char* ename, uint32 label);

  void finalizeGraph(bool determinize); 
};
