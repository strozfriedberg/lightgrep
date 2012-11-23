#pragma once

#include "basic.h"
#include "encoder.h"
#include "encoderfactory.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"

#include <memory>

class FSMThingy {
public:
  FSMThingy(uint32 sizeHint);

  EncoderFactory EncFac;
  NFABuilder Nfab;
  NFAOptimizer Comp;
  NFAPtr Fsm;

  void addPattern(const ParseTree& tree, const char* chain, uint32 label);

  void finalizeGraph(bool determinize);
};
