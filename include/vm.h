#pragma once

#include "vm_interface.h"
#include "staticvector.h"
#include "skiptable.h"

class Vm: public VmInterface {
public:

  typedef StaticVector<Thread> ThreadList;

  Vm();
  Vm(ProgramPtr prog);

  // numCheckedStates should be equal to the number + 1 for the reserved bit
  void init(ProgramPtr prog);

  bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);
  void reset();

  void setDebugRange(uint64 beg, uint64 end) { BeginDebug = beg; EndDebug = end; }

  bool execute(Thread& t, const byte* cur);
  bool executeEpsilon(Thread& t, uint64 offset);
  void executeFrame(const byte* cur, uint64 offset, HitCallback& hitFn);


  const ThreadList& active() const { return Active; }
  const ThreadList& next() const { return Next; }

  unsigned int numActive() const { return Active.size(); }
  unsigned int numNext() const { return Next.size(); }

private:
  void doMatch(ThreadList::iterator threadIt, HitCallback& hitFn);
  void cleanup();

  bool _execute(Thread& t, const byte* cur);
  bool _executeEpsilon(const Instruction* base, Thread& t, uint64 offset);
  void _executeFrame(const ByteSet& first, ThreadList::iterator& threadIt, const Instruction* base, const byte* cur, uint64 offset, HitCallback& hitFn);

  ProgramPtr Prog;
  ThreadList Active,
             Next;

  std::vector<bool> CheckStates;
  std::vector< std::pair< uint64, uint64 > > Matches;

  uint64 BeginDebug,
         EndDebug;
};
