#pragma once

#ifdef LBT_TRACE_ENABLED
#include <set>
#endif

#include <vector>

#include "sparseset.h"

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

  virtual void startsWith(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);
  virtual bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn);
  virtual void closeOut(HitCallback& hitFn);
  virtual void reset();

  #ifdef LBT_TRACE_ENABLED
  void setDebugRange(uint64 beg, uint64 end) {
    BeginDebug = beg;
    EndDebug = end;
  }
  #endif

  bool execute(ThreadList::iterator t, const byte* cur);
  bool executeEpsilon(ThreadList::iterator t, uint64 offset);
  void executeFrame(const byte* cur, uint64 offset, HitCallback& hitFn);
  void cleanup();

  const ThreadList& first() const { return First; }
  const ThreadList& active() const { return Active; }
  const ThreadList& next() const { return Next; }

  Thread& add(const Thread& t) { return (Active.addBack() = t); }

  unsigned int numActive() const { return Active.size(); }
  unsigned int numNext() const { return Next.size(); }

private:
  void doMatch(const Thread& t);

  bool _execute(const Instruction* base, ThreadList::iterator t, const byte* cur);
  bool _executeEpsilon(const Instruction* base, ThreadList::iterator t, uint64 offset);
  bool _executeEpSequence(const Instruction* base, ThreadList::iterator t, uint64 offset);
  void _executeThread(const Instruction* base, ThreadList::iterator t, const byte* cur, uint64 offset);
  void _executeFrame(const ByteSet& first, ThreadList::iterator& threadIt, const Instruction* base, const byte* cur, uint64 offset);
  void _cleanup();

  #ifdef LBT_TRACE_ENABLED
  void open_init_epsilon_json(std::ostream& out);
  void close_init_epsilon_json(std::ostream& out) const;
  void open_frame_json(std::ostream& out, uint64 offset, const byte* cur);
  void close_frame_json(std::ostream& out, uint64 offset) const;
  void pre_run_thread_json(std::ostream& out, uint64 offset, const Thread& t,
                           const Instruction* base);
  void post_run_thread_json(std::ostream& out, uint64 offset, const Thread& t,
                            const Instruction* base);
  void thread_json(std::ostream& out, const Thread& t,
                   const Instruction* base, byte state);

  bool first_thread_json;
  std::set<uint64> new_thread_json;

  uint64 BeginDebug, EndDebug;
  uint64 NextId;
  #endif

  struct Match {
    uint64 Start, End;

    Match(uint64 start, uint64 end): Start(start), End(end) {}
  };

  friend std::ostream& operator<<(std::ostream& out, const Match& m);

  std::vector< std::vector<Match> > Matches;
  uint64 MaxMatches;

  ProgramPtr Prog;
  ThreadList First,
             Active,
             Next;

  SparseSet  CheckStates,
             Kill;

  HitCallback* CurHitFn;
};
