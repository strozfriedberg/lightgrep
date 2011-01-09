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

  const ThreadList& first() const { return First; }
  const ThreadList& active() const { return Active; }
  const ThreadList& next() const { return Next; }

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

  bool _execute(const Instruction* base, Thread& t, const byte* cur);
  bool _executeEpsilon(const Instruction* base, Thread& t, uint64 offset);
  bool _executeEpSequence(const Instruction* base, Thread& t, uint64 offset);
  void _executeThread(const Instruction* base, Thread& t, const byte* cur, uint64 offset);
  void _executeFrame(const ByteSet& first, ThreadList::iterator& threadIt, const Instruction* base, const byte* cur, uint64 offset);

  #ifdef LBT_TRACE_ENABLED
  void open_frame_json(std::ostream& out, uint64 offset, const byte* cur);
  void close_frame_json(std::ostream& out, uint64 offset) const;
  void thread_json(std::ostream& out, uint64 offset,
                   const Thread& t, const Instruction* base);
  void new_thread_json(std::ostream& out, uint64 offset, const Thread& t,
                       const Instruction* base);
  void pre_run_thread_json(std::ostream& out, uint64 offset, const Thread& t,
                           const Instruction* base);
  void post_run_thread_json(std::ostream& out, uint64 offset, const Thread& t,
                            const Instruction* base);
  void kill_thread_json(std::ostream& out, uint64 offset, const Thread& t,
                        const Instruction* base);
  void thread_json(std::ostream& out, uint64 offset, const Thread& t,
                   const Instruction* base, Thread::ThreadLife state);

  bool first_thread_json;
  #endif

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
