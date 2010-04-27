#pragma once

#include "basic.h"
#include "instructions.h"
#include "thread.h"

class Vm {
public:
  
  static bool execute(const Instruction* base, const Instruction* pc, Thread& t, ThreadList& next, const byte* cur, uint64 offset);
};
