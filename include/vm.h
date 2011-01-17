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

  virtual bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);
  virtual void closeOut(HitCallback& hitFn);
  virtual void reset();

  void setDebugRange(uint64 beg, uint64 end) { BeginDebug = beg; EndDebug = end; }

  bool execute(ThreadList::iterator t, const byte* cur);
  bool executeEpsilon(ThreadList::iterator t, uint64 offset);
  void executeFrame(const byte* cur, uint64 offset, HitCallback& hitFn);

  const ThreadList& first() const { return First; }
  const ThreadList& active() const { return Active; }
  const ThreadList& next() const { return Next; }

  Thread& add(const Thread& t) { return (Active.addBack() = t); }

  inline void cleanup() {
    Active.swap(Next);
    Next.clear();
    if (CheckStates[0]) {
      CheckStates.assign(CheckStates.size(), false);
    }
  }

  unsigned int numActive() const { return Active.size(); }
  unsigned int numNext() const { return Next.size(); }

private:
  void doMatch(const Thread& t);

  bool _execute(const Instruction* base, ThreadList::iterator t, const byte* cur);
  bool _executeEpsilon(const Instruction* base, ThreadList::iterator t, uint64 offset);
  bool _executeEpSequence(const Instruction* base, ThreadList::iterator t, uint64 offset);
  void _executeThread(const Instruction* base, ThreadList::iterator t, const byte* cur, uint64 offset);
  void _executeFrame(const ByteSet& first, ThreadList::iterator& threadIt, const Instruction* base, const byte* cur, uint64 offset);

  ProgramPtr Prog;
  ThreadList First,
             Active,
             Next;

  std::vector<bool> CheckStates;
  std::vector< std::pair< uint64, uint64 > > Matches;

  uint64 BeginDebug,
         EndDebug;

  HitCallback* CurHitFn;
};
