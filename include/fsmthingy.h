#pragma once

#include "basic.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"
#include "encoders/encoderfactory.h"

#include <memory>

class FSMThingy {
public:
  FSMThingy(uint32_t sizeHint);

  EncoderFactory EncFac;
  NFABuilder Nfab;
  NFAOptimizer Comp;
  NFAPtr Fsm;

  void addPattern(const ParseTree& tree, const char* chain, uint32_t label);

  void finalizeGraph(bool determinize);
};
