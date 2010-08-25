#pragma once

#include "basic.h"
#include "instructions.h"
#include "thread.h"
#include "SearchHit.h"
#include "staticvector.h"
#include "skiptable.h"

class Vm {
public:

  typedef StaticVector<Thread> ThreadList;

  Vm();
  
  static bool execute(const Instruction* base, Thread& t, std::vector<bool>& checkStates, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset);
  
  // numCheckedStates should be equal to the number + 1 for the reserved bit
  void init(ProgramPtr prog, ByteSet firstBytes, uint32 numCheckedStates, boost::shared_ptr<SkipTable> skip);

  bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);

  void setDebugRange(uint64 beg, uint64 end) { BeginDebug = beg; EndDebug = end; }

private:
  void doMatch(ThreadList::iterator threadIt, HitCallback& hitFn);
  void cleanup();

  ByteSet    First;
  boost::shared_ptr<SkipTable> Skip;
  ProgramPtr Prog;
  ThreadList Active,
             Next;

  std::vector<bool> CheckStates;
  std::vector< std::pair< uint64, uint64 > > Matches;
  boost::scoped_ptr< std::vector<uint32> > SkipTblPtr;

  uint64 BeginDebug,
         EndDebug;
};
