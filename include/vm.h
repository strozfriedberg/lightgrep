#pragma once

#include "basic.h"
#include "program.h"
#include "thread.h"
#include "SearchHit.h"
#include "staticvector.h"
#include "skiptable.h"

class Vm {
public:

  typedef StaticVector<Thread> ThreadList;

  Vm();
  Vm(ProgramPtr prog);

  bool execute(Thread& t, const byte* cur);
  bool executeEpsilon(Thread& t, uint64 offset);
  
  // numCheckedStates should be equal to the number + 1 for the reserved bit
  void init(ProgramPtr prog);

  bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);
  void reset();

  void setDebugRange(uint64 beg, uint64 end) { BeginDebug = beg; EndDebug = end; }

  const ThreadList& active() const { return Active; }
  const ThreadList& next() const { return Next; }

  unsigned int numActive() const { return Active.size(); }
  unsigned int numNext() const { return Next.size(); }

private:
  void doMatch(ThreadList::iterator threadIt, HitCallback& hitFn);
  void cleanup();

  bool _execute(Thread& t, const byte* cur);
  bool _executeEpsilon(const Instruction* base, Thread& t, uint64 offset);

  ProgramPtr Prog;
  ThreadList Active,
             Next;

  std::vector<bool> CheckStates;
  std::vector< std::pair< uint64, uint64 > > Matches;

  uint64 BeginDebug,
         EndDebug;
};
