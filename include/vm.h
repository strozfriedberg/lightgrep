#pragma once

#include "basic.h"
#include "instructions.h"
#include "thread.h"

class Vm {
public:
  
  static bool execute(const Instruction* base, Thread& t, ThreadList& next, const byte* cur, uint64 offset);
  static bool run(const Instruction* base, uint32 num, const byte* beg, const byte* end, uint64 startOffset);
};
