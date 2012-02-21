#include "container_out.h"
#include "vm.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"PC\":" << std::hex << t.PC
      << ", \"Label\":" << std::dec << t.Label
      #ifdef LBT_TRACE_ENABLED
      << ", \"Id\":" << t.Id
      #endif
      << ", \"Start\":" << t.Start
      << ", \"End\":" << t.End << " }";
  return out;
}

#ifdef LBT_TRACE_ENABLED

void Vm::open_init_epsilon_json(std::ostream& out) {
  if (BeginDebug == 0) {
    out << "{\"offset\":-1, \"byte\":0, \"num\":0, \"list\":[";
    first_thread_json = true;
  }
}

void Vm::close_init_epsilon_json(std::ostream& out) const {
  close_frame_json(out, 0);
}

void Vm::open_frame_json(std::ostream& out, uint64 offset, const byte* const cur) {
  if (BeginDebug <= offset && offset < EndDebug) {
    out << "{\"offset\":" << offset << ", \"byte\":" << (uint32) *cur
        << ", \"num\":" << Active.size() << ", \"list\":[";
    first_thread_json = true;
  }
}

void Vm::close_frame_json(std::ostream& out, uint64 offset) const {
  if (BeginDebug <= offset && offset < EndDebug) {
    out << "]}" << std::endl;
  }
}

void Vm::pre_run_thread_json(std::ostream& out, uint64 offset,
                             const Thread& t, const Instruction* const base) {
  if (BeginDebug <= offset && offset < EndDebug) {
    byte state = Thread::PRERUN;

    if (new_thread_json.erase(t.Id)) {
      state |= Thread::BORN;
    }

    thread_json(out, t, base, state);
  }
}

void Vm::post_run_thread_json(std::ostream& out, uint64 offset,
                              const Thread& t, const Instruction* const base) {
  if (BeginDebug <= offset && offset < EndDebug) {
    byte state = Thread::POSTRUN;
    if (!t.PC)  {
      state |= Thread::DIED;
    }

    thread_json(out, t, base, state);
  }
}

void Vm::thread_json(std::ostream& out, const Thread& t,
                     const Instruction* const base, byte state) {
  // put commas between consecutive threads
  if (first_thread_json) {
    first_thread_json = false;
  }
  else {
    out << ", ";
  }

  t.output_json(out, base, state);
}

void Thread::output_json(std::ostream& out, const Instruction* const base, byte state) const {
  out << "{ \"Id\":" << Id
      << ", \"PC\":" << (PC ? PC - base : -1)
      << ", \"Label\":" << Label
      << ", \"Start\":" << Start
      << ", \"End\":" << End
      << ", \"state\":" << (uint32) state
      << ", \"op\":" << (PC ? PC->OpCode : 0)
      << " }";
}
#endif

std::shared_ptr<VmInterface> VmInterface::create() {
  return std::shared_ptr<VmInterface>(new Vm);
}

Vm::Vm() :
  #ifdef LBT_TRACE_ENABLED
  BeginDebug(Thread::NONE), EndDebug(Thread::NONE), NextId(0),
  #endif
  CurHitFn(0) {}

Vm::Vm(ProgramPtr prog):
  #ifdef LBT_TRACE_ENABLED
  BeginDebug(Thread::NONE), EndDebug(Thread::NONE), NextId(0),
  #endif
  CurHitFn(0)
{
  init(prog);
}

void Vm::init(ProgramPtr prog) {
  Prog = prog;
  Program& p(*Prog);
  ProgEnd = &p.back() - 1;

  uint32 numPatterns = 0,
         numCheckedStates = 0;
  for (uint32 i = 0; i < p.size(); ++i) {
    if (p[i].OpCode == LABEL_OP && numPatterns < p[i].Op.Offset) {
      numPatterns = p[i].Op.Offset;
    }
    if (p[i].OpCode == CHECK_HALT_OP) {
      numCheckedStates = std::max(numCheckedStates, p[i].Op.Offset);
    }
  }
  ++numPatterns;
  ++numCheckedStates;

  MatchEnds.resize(numPatterns);
  MatchEndsMax = 0;

  Seen.resize(numPatterns);
  SeenNoLabel = false;

  Live.resize(numPatterns);
  LiveNoLabel = false;

  CheckLabels.resize(numCheckedStates);

  Active.emplace_back(&(*Prog)[0]);
  ThreadList::iterator t(Active.begin());

  #ifdef LBT_TRACE_ENABLED
  open_init_epsilon_json(std::clog);
  new_thread_json.insert(Active.front().Id);
  pre_run_thread_json(std::clog, 0, Active.front(), &(*Prog)[0]);
  #endif

  if (_executeEpSequence(&(*Prog)[0], t, 0)) {
    Next.push_back(*t);
  }

  #ifdef LBT_TRACE_ENABLED
  post_run_thread_json(std::clog, 0, Active.front(), &(*Prog)[0]);
  close_init_epsilon_json(std::clog);
  #endif

  First.swap(Next);

  reset();
}

void Vm::reset() {
  MaxMatches = 0;

  Active.clear();
  Next.clear();

  CheckLabels.clear();

  SeenNoLabel = false;
  Seen.clear();

  LiveNoLabel = false;
  Live.clear();

  MatchEnds.assign(MatchEnds.size(), 0);
  MatchEndsMax = 0;

  CurHitFn = 0;

  #ifdef LBT_TRACE_ENABLED
  NextId = 1;
  #endif
}

inline void Vm::_markLive(const uint32 label) {
  if (label == Thread::NOLABEL) {
    LiveNoLabel = true;
  }
  else if (!Live.find(label)) {
    Live.insert(label);
  }
}

inline void Vm::_markSeen(const uint32 label) {
  if (label == Thread::NOLABEL) {
    SeenNoLabel = true;
  }
  else if (!Seen.find(label)) {
    Seen.insert(label);
  }
}

inline bool Vm::_execute(const Instruction* const base, ThreadList::iterator t, const byte* const cur) {
  const Instruction& instr = *t->PC;

  switch (instr.OpCode) {
    case LIT_OP:
      if (*cur == instr.Op.Literal) {
        t->advance(InstructionSize<LIT_OP>::VAL);
        return true;
      }
      break;

    case EITHER_OP:
      if (*cur == instr.Op.Range.First || *cur == instr.Op.Range.Last) {
        t->advance(InstructionSize<EITHER_OP>::VAL);
        return true;
      }
      break;

    case RANGE_OP:
      if (instr.Op.Range.First <= *cur && *cur <= instr.Op.Range.Last) {
        t->advance(InstructionSize<RANGE_OP>::VAL);
        return true;
      }
      break;

    case ANY_OP:
      t->advance(InstructionSize<ANY_OP>::VAL);
      return true;

    case BIT_VECTOR_OP:
      {
        const ByteSet* setPtr = reinterpret_cast<const ByteSet*>(t->PC + 1);
        if ((*setPtr)[*cur]) {
          t->advance(InstructionSize<BIT_VECTOR_OP>::VAL);
          return true;
        }
      }
      break;

    case JUMP_TABLE_RANGE_OP:
      if (instr.Op.Range.First <= *cur && *cur <= instr.Op.Range.Last) {
        const uint32 addr = *reinterpret_cast<const uint32*>(t->PC + 1 + (*cur - instr.Op.Range.First));
        if (addr != 0xffffffff) {
          t->jump(base, addr);
          return true;
        }
      }
      break;

    case FINISH_OP:
      return false;
  }

  // DIE, penultimate instruction is always a halt.
  t->PC = ProgEnd;
  return false;
}

inline bool Vm::_liveCheck(const uint64 start, const uint32 label) {
  if (label == Thread::NOLABEL) {
    // if we're unlabeled, and anything live has priority, we're blocked
    // if we're unlabeled and we overlap any matches, we're blocked
    return !Next.empty() || start < MatchEndsMax;
  }
  else {
    // if we're labeled and an unlabeled or same-labeled thread has
    // priority, we're blocked
    return LiveNoLabel || Live.find(label);
  }
}

// while base is always == &Program[0], we pass it in because it then should get inlined away
inline bool Vm::_executeEpsilon(const Instruction* const base, ThreadList::iterator t, const uint64 offset) {
  const Instruction& instr = *t->PC;

  switch (instr.OpCode) {
    case FINISH_OP:
      {
        const uint32 tLabel = t->Label;
        const uint64 tStart = t->Start;
        const uint64 tEnd = t->End;

        if (tEnd == offset) {
          // kill all same-labeled, same-start threads
          const ThreadList::const_iterator e(Active.end());
          for (ThreadList::iterator i(t+1); i != e && i->Start == tStart; ++i) {
            if (i->Label == tLabel) {
              // DIE. Penultimate instruction is always a halt
              i->PC = ProgEnd;
            }
          }
        }

        if (!SeenNoLabel && !Seen.find(tLabel)) {
          if (tStart >= MatchEnds[tLabel]) {
            MatchEnds[tLabel] = tEnd + 1;

            if (tEnd + 1 > MatchEndsMax) {
              MatchEndsMax = tEnd + 1;
            }

            if (CurHitFn) {
              SearchHit hit(tStart, tEnd + 1, tLabel);
              (*CurHitFn)(UserData, &hit);
            }
          }

          t->PC = 0;
        }

        return false;
      }

    case FORK_OP:
      {
        Thread f = *t;
        t->advance(InstructionSize<FORK_OP>::VAL);

        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          if (t->PC->OpCode != FINISH_OP) {
            _markSeen(t->Label);
          }

          _markLive(t->Label);
          Next.push_back(*t);
        }

        // Now back up to the fork, fall through to handle it as a longjump.
        // Note that the forked child is taking the parent's place in Active.
        // This is ESSENTIAL for maintaining correct thread priority order.
        *t = f;

        #ifdef LBT_TRACE_ENABLED
        new_thread_json.insert(t->Id = NextId++);
        #endif
      }

    case JUMP_OP:
      t->jump(base, *reinterpret_cast<const uint32*>(t->PC+1));
      return true;

    case CHECK_HALT_OP:
      {
        if (CheckLabels.find(instr.Op.Offset)) {
          // another thread has the lock, we die
          t->PC = 0;
          return false;
        }
        else if (!_liveCheck(t->Start, t->Label)) {
          // nothing blocks us, we take the lock
          CheckLabels.insert(instr.Op.Offset);
        }

        t->advance(InstructionSize<CHECK_HALT_OP>::VAL);
        return true;
      }

    case LABEL_OP:
      {
        const uint32 label = instr.Op.Offset;
        if (t->Start >= MatchEnds[label]) {
          t->Label = label;
          t->advance(InstructionSize<LABEL_OP>::VAL);
          return true;
        }
        else {
          t->PC = 0;
          return false;
        }
      }

    case MATCH_OP:
      t->End = offset;
      t->advance(InstructionSize<MATCH_OP>::VAL);
      return true;

    case HALT_OP:
      // die, motherfucker, die
      t->PC = 0;
      return false;
  }

  return false;
}

inline void Vm::_executeThread(const Instruction* const base, ThreadList::iterator t, const byte* const cur, const uint64 offset) {
  #ifdef LBT_TRACE_ENABLED
  pre_run_thread_json(std::clog, offset, *t, base);
  #endif

  _execute(base, t, cur);

  #ifdef LBT_TRACE_ENABLED
  post_run_thread_json(std::clog, offset, *t, base);
  #endif

  if (_executeEpSequence(base, t, offset)) {
    if (t->PC->OpCode != FINISH_OP) {
      _markSeen(t->Label);
    }

    _markLive(t->Label);
    Next.push_back(*t);
  }
}

inline bool Vm::_executeEpSequence(const Instruction* const base, ThreadList::iterator t, const uint64 offset) {

  // kill threads overlapping an emitted match
  if (t->Label != Thread::NOLABEL && t->Start < MatchEnds[t->Label]) {
    return false;
  }

  #ifdef LBT_TRACE_ENABLED
  bool ex;
  do {
    const uint64 id = t->Id; // t can change on a fork, we want the original
    pre_run_thread_json(std::clog, offset, *t, base);
    ex = _executeEpsilon(base, t, offset);
//std::cerr << "\nNext.size() == " << Next.size() << std::endl;

    if (t->Id == id) {
      post_run_thread_json(std::clog, offset, *t, base);
    }
    else if (!Next.empty() && Next.back().Id == id) {
      post_run_thread_json(std::clog, offset, Next.back(), base);
    }
/*
    const Thread& x = t->Id == id ? *t : Next.back();
    post_run_thread_json(std::cerr, offset, x, base);
*/
  } while (ex);
  #else
  while (_executeEpsilon(base, t, offset)) ;
  #endif

  return t->PC;
}

inline void Vm::_executeFrame(const ByteSet& first, ThreadList::iterator t, const Instruction* const base, const byte* const cur, const uint64 offset) {
  // run old threads at this offset
  while (t != Active.end()) {
    _executeThread(base, t, cur, offset);
    ++t;
  }

  // create new threads at this offset
  if (first[*cur]) {
    const size_t oldsize = Active.size();

    for (t = First.begin(); t != First.end(); ++t) {
      #ifdef LBT_TRACE_ENABLED
      Active.emplace_back(t->PC, Thread::NOLABEL, NextId++, offset, Thread::NONE);
      #else
      Active.emplace_back(t->PC, Thread::NOLABEL, offset, Thread::NONE);
      #endif

      #ifdef LBT_TRACE_ENABLED
      new_thread_json.insert(Active.back().Id);
      #endif
    }

    for (t = Active.begin() + oldsize; t != Active.end(); ++t) {
      _executeThread(base, t, cur, offset);
    }
  }
}

inline void Vm::_cleanup() {
  Active.swap(Next);
  Next.clear();
  CheckLabels.clear();

  SeenNoLabel = false;
  Seen.clear();

  LiveNoLabel = false;
  Live.clear();
}

void Vm::cleanup() { _cleanup(); }

bool Vm::execute(Thread* t, const byte* const cur) {
  Active.push_back(*t);
  return execute(Active.end()-1, cur);
}

bool Vm::execute(ThreadList::iterator t, const byte* const cur) {
  return _execute(&(*Prog)[0], t, cur);
}

bool Vm::executeEpsilon(Thread* t, uint64 offset) {
  Active.push_back(*t);
  return executeEpsilon(Active.end()-1, offset);
}

bool Vm::executeEpsilon(ThreadList::iterator t, uint64 offset) {
  return _executeEpsilon(&(*Prog)[0], t, offset);
}

void Vm::executeFrame(const byte* const cur, uint64 offset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  ThreadList::iterator t = Active.begin();
  _executeFrame(Prog->First, t, &(*Prog)[0], cur, offset);
}

void Vm::startsWith(const byte* const beg, const byte* const end, const uint64 startOffset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  const Instruction* base = &(*Prog)[0];
  uint64 offset = startOffset;

  if (Prog->First[*beg]) {
    for (ThreadList::const_iterator t(First.begin()); t != First.end(); ++t) {
      Active.emplace_back(t->PC, Thread::NOLABEL, offset, Thread::NONE);
    }

    for (const byte* cur = beg; cur < end; ++cur, ++offset) {
      for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
        _executeThread(base, t, cur, offset);
      }

      _cleanup();

      if (Active.empty()) {
        // early exit if threads die out
        break;
      }
    }
  }

  closeOut(hitFn, userData);
  reset();
}

bool Vm::search(const byte* const beg, const byte* const end, const uint64 startOffset, HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;
  const Instruction* base = &(*Prog)[0];
  const ByteSet& first = Prog->First;
  uint64 offset = startOffset;

  for (const byte* cur = beg; cur < end; ++cur, ++offset) {
    #ifdef LBT_TRACE_ENABLED
    open_frame_json(std::clog, offset, cur);
    #endif

    _executeFrame(first, Active.begin(), base, cur, offset);

    #ifdef LBT_TRACE_ENABLED
    close_frame_json(std::clog, offset);
    #endif

    _cleanup();
  }

  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;

  // check for remaining live threads
  const ThreadList::const_iterator e(Active.end());
  for (ThreadList::iterator t(Active.begin()); t != e; ++t) {
    const unsigned char op = t->PC->OpCode;
    if (op == HALT_OP || op == FINISH_OP) {
      continue;
    }

    // this is a live thread
    return true;
  }

  return false;
}

void Vm::closeOut(HitCallback hitFn, void* userData) {
  CurHitFn = hitFn;
  UserData = userData;

  if (!CurHitFn) {
    return;
  }

  SearchHit hit;

  for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
    if (t->PC->OpCode == FINISH_OP) {
      // has match
      if (t->Start >= MatchEnds[t->Label]) {
        MatchEnds[t->Label] = t->End + 1;

        hit.Start = t->Start;
        hit.End = t->End + 1;
        hit.KeywordIndex = t->Label;
        (*CurHitFn)(UserData, &hit);
      }
    }
  }
}
