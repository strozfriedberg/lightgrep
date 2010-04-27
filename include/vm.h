#pragma once

#include "basic.h"
#include "instructions.h"
#include "thread.h"

class Vm {
public:
  
  static bool execute(const Instruction* pc, ThreadList& next, const byte* cur);
};
