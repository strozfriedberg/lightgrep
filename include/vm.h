#pragma once

#include "basic.h"
#include "instructions.h"
#include "thread.h"
#include "SearchHit.h"

class Vm {
public:
  
  static bool execute(const Instruction* base, Thread& t, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset);
  
  void init(ProgramPtr prog) { Program = prog; }
  bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);

private:
  ProgramPtr Program;
};
