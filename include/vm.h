#pragma once

#include "basic.h"
#include "instructions.h"
#include "thread.h"
#include "SearchHit.h"
#include "staticvector.h"

class Vm {
public:

  typedef StaticVector<Thread> ThreadList;
  
  static bool execute(const Instruction* base, Thread& t, std::vector<bool>& checkStates, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset);
  
  // numCheckedStates should be equal to the number + 1 for the reserved bit
  void init(ProgramPtr prog, ByteSet firstBytes, uint32 numCheckedStates);

  bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);

private:
  ByteSet    First;
  ProgramPtr Program;
  ThreadList Active,
             Next;

  std::vector<bool> CheckStates;
};
