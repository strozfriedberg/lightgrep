#pragma once

#include "basic.h"
#include "encoder.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"

#include <memory>

class FSMThingy {
public:
  FSMThingy(uint32 sizeHint);

  NFABuilder Nfab;
  NFAOptimizer Comp;
  NFAPtr Fsm;

  std::map<std::string,std::shared_ptr<Encoder>> Encoders;

  void addPattern(const ParseTree& tree, const char* chain, uint32 label);

  void finalizeGraph(bool determinize);

  std::shared_ptr<Encoder> buildEncoder(const std::string& chain);
};
