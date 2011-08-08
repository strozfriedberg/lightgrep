#include "container_out.h"
#include "vm.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC
      << ", \"Label\":" << std::dec << t.Label
      #ifdef LBT_TRACE_ENABLED
      << ", \"Id\":" << t.Id
      #endif
      << ", \"Start\":" << t.Start
      << ", \"End\":" << t.End << " }";
  return out;
}

/*
std::ostream& operator<<(std::ostream& out, const Vm::Match& m) {
  return out << '(' << m.Start << ',' << m.End << ')';
}
*/

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

void Vm::open_frame_json(std::ostream& out, uint64 offset, const byte* cur) {
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
                             const Thread& t, const Instruction* base) {
  if (BeginDebug <= offset && offset < EndDebug) {
    byte state = Thread::PRERUN;

    if (new_thread_json.erase(t.Id)) {
      state |= Thread::BORN;
    }

    thread_json(out, t, base, state);
  }
}

void Vm::post_run_thread_json(std::ostream& out, uint64 offset,
                              const Thread& t, const Instruction* base) {
  if (BeginDebug <= offset && offset < EndDebug) {
    byte state = Thread::POSTRUN;
    if (!t.PC)  {
      state |= Thread::DIED;
    }

    thread_json(out, t, base, state);
  }
}

void Vm::thread_json(std::ostream& out, const Thread& t,
                     const Instruction* base, byte state) {
  // put commas between consecutive threads
  if (first_thread_json) {
    first_thread_json = false;
  }
  else {
    out << ", ";
  }

  t.output_json(out, base, state);
}

void Thread::output_json(std::ostream& out, const Instruction* base, byte state) const {
  out << "{ \"Id\":" << Id
      << ", \"PC\":" << (PC ? PC - base : -1)
      << ", \"Label\":" << Label
      << ", \"Start\":" << Start
      << ", \"End\":" << End
      << ", \"state\":" << (uint32) state
      << " }";
}
#endif

boost::shared_ptr<VmInterface> VmInterface::create() {
  return boost::shared_ptr<VmInterface>(new Vm);
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

  #ifdef LBT_HISTOGRAM_ENABLED
  ProgHistogram.resize(p.size());
  #endif

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

  Seen.resize(numPatterns);
  SeenNone = false;

  Active.push_back(Thread(&(*Prog)[0]));
  ThreadList::iterator t(Active.begin());

  #ifdef LBT_TRACE_ENABLED
  open_init_epsilon_json(std::cerr);
  new_thread_json.insert(Active.front().Id);
  pre_run_thread_json(std::cerr, 0, Active.front(), &(*Prog)[0]);
  #endif

  if (_executeEpSequence(&(*Prog)[0], t, 0)) {
    Next.push_back(*t);
  }

  #ifdef LBT_TRACE_ENABLED
  post_run_thread_json(std::cerr, 0, Active.front(), &(*Prog)[0]);
  close_init_epsilon_json(std::cerr);
  #endif

  First.swap(Next);

  reset();
}

void Vm::reset() {
  MaxMatches = 0;

  Active.clear();
  Next.clear();

  CheckStates.clear();

  SeenNone = false;
  Seen.clear();

  MatchEnds.assign(MatchEnds.size(), 0);

  CurHitFn = 0;

  #ifdef LBT_TRACE_ENABLED
  NextId = 1;
  #endif
}

void Vm::markSeen(uint32 label) {
  if (label == Thread::NOLABEL) {
    SeenNone = true;
  }
  else if (!Seen.find(label)) {
    Seen.insert(label);
  }
}

inline bool Vm::_execute(const Instruction* base, ThreadList::iterator t, const byte* cur) {
  register Instruction instr = *t->PC;

  #ifdef LBT_HISTOGRAM_ENABLED
  ++ProgHistogram[(std::vector<uint32>::size_type) (t->PC - base)];
  #endif

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
    case JUMP_TABLE_OP:
      if (*(uint32*)(t->PC + 1 + *cur) != 0xffffffff) {
        t->jump(base, *reinterpret_cast<const uint32*>(t->PC + 1 + *cur));
        return true;
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
  t->PC = &Prog->back() - 1;
  return false;
}

// while base is always == &Program[0], we pass it in because it then should get inlined away
inline bool Vm::_executeEpsilon(const Instruction* base, ThreadList::iterator t, uint64 offset) {
  register Instruction instr = *t->PC;

  #ifdef LBT_HISTOGRAM_ENABLED
  ++ProgHistogram[(std::vector<uint32>::size_type) (t->PC - base)];
  #endif

  switch (instr.OpCode) {
    case FORK_OP:
      {
        Thread f = *t;
        t->advance(InstructionSize<FORK_OP>::VAL);

        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          if (t->PC->OpCode != FINISH_OP) {
            markSeen(t->Label);
          }
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
        std::pair<uint32,uint64> s(instr.Op.Offset, t->Start);
        if (CheckStates.end() != CheckStates.find(s)) { // read sync point

          t->PC = 0;
          return false;
        }
        else {
          CheckStates.insert(s); // write sync point
          t->advance(InstructionSize<CHECK_HALT_OP>::VAL);
          return true;
        }
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

    case FINISH_OP:
      // kill all same-labeled, overlapping threads
      for (ThreadList::iterator i(t+1); i != Active.end() && i->Start <= t->End; ++i) {
        if (i->Label == t->Label) {
          i->End = Thread::NONE;
          // DIE. Penultimate instruction is always a halt
          i->PC = &Prog->back() - 1;
        }
      }

      if (!SeenNone && !Seen.find(t->Label)) {
        MatchEnds[t->Label] = t->End + 1;

        if (CurHitFn) {
          SearchHit hit(t->Start, t->End - t->Start + 1, t->Label);
          CurHitFn->collect(hit);
        }

        t->PC = 0;
      }
      return false;

    default:
      return false;
  }
}

inline void Vm::_executeThread(const Instruction* base, ThreadList::iterator t, const byte* cur, uint64 offset) {
  #ifdef LBT_TRACE_ENABLED
  pre_run_thread_json(std::cerr, offset, *t, base);
  #endif

  _execute(base, t, cur);

  #ifdef LBT_TRACE_ENABLED
  post_run_thread_json(std::cerr, offset, *t, base);
  #endif

  if (_executeEpSequence(base, t, offset)) {
    if (t->PC->OpCode != FINISH_OP) {
      markSeen(t->Label);
    }

    Next.push_back(*t);
  }
}

inline bool Vm::_executeEpSequence(const Instruction* base, ThreadList::iterator t, uint64 offset) {

  // kill threads overlapping an emitted match
  if (t->Label != Thread::NOLABEL && t->Start < MatchEnds[t->Label]) {
    return false;
  }

  #ifdef LBT_TRACE_ENABLED
  bool ex;
  do {
    const uint64 id = t->Id; // t can change on a fork, we want the original
    pre_run_thread_json(std::cerr, offset, *t, base);
    ex = _executeEpsilon(base, t, offset);
//std::cerr << "\nNext.size() == " << Next.size() << std::endl;

    if (t->Id == id) {
      post_run_thread_json(std::cerr, offset, *t, base);
    }
    else if (!Next.empty() && Next.back().Id == id) {
      post_run_thread_json(std::cerr, offset, Next.back(), base);
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

inline void Vm::_executeFrame(const ByteSet& first, ThreadList::iterator t, const Instruction* base, const byte* cur, uint64 offset) {
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
      Active.push_back(Thread(t->PC, Thread::NOLABEL, NextId++, offset, Thread::NONE));
      #else
      Active.push_back(Thread(t->PC, Thread::NOLABEL, offset, Thread::NONE));
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
  CheckStates.clear();

  SeenNone = false;
  Seen.clear();
}

void Vm::cleanup() { _cleanup(); }

bool Vm::execute(Thread* t, const byte* cur) {
  Active.push_back(*t);
  return execute(Active.end()-1, cur);
}

bool Vm::execute(ThreadList::iterator t, const byte* cur) {
  return _execute(&(*Prog)[0], t, cur);
}

bool Vm::executeEpsilon(Thread* t, uint64 offset) {
  Active.push_back(*t);
  return executeEpsilon(Active.end()-1, offset);
}

bool Vm::executeEpsilon(ThreadList::iterator t, uint64 offset) {
  return _executeEpsilon(&(*Prog)[0], t, offset);
}

void Vm::executeFrame(const byte* cur, uint64 offset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  ThreadList::iterator t = Active.begin();
  _executeFrame(Prog->First, t, &(*Prog)[0], cur, offset);
}

void Vm::startsWith(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  const Instruction* base = &(*Prog)[0];
  ByteSet first = Prog->First;
  register uint64 offset = startOffset;

  if (first[*beg]) {
    for (ThreadList::const_iterator t(First.begin()); t != First.end(); ++t) {
      Active.push_back(Thread(t->PC, Thread::NOLABEL, offset, Thread::NONE));
    }

    for (register const byte* cur = beg; cur < end; ++cur) {
      for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
        _executeThread(base, t, cur, offset);
      }

      _cleanup();

      if (Active.empty()) {
        // early exit if threads die out
        break;
      }

      ++offset;
    }
  }

  closeOut(hitFn);
  reset();
}

bool Vm::search(const byte* beg, register const byte* end, uint64 startOffset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  const Instruction* base = &(*Prog)[0];
  ByteSet first = Prog->First;
  register uint64 offset = startOffset;

  for (register const byte* cur = beg; cur < end; ++cur) {
    #ifdef LBT_TRACE_ENABLED
    open_frame_json(std::cerr, offset, cur);
    #endif

    _executeFrame(first, Active.begin(), base, cur, offset);

    #ifdef LBT_TRACE_ENABLED
    close_frame_json(std::cerr, offset);
    #endif

    _cleanup();
    ++offset;
  }
  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;

  #ifdef LBT_HISTOGRAM_ENABLED
  for (std::vector<uint32>::const_iterator i(ProgHistogram.begin()); i != ProgHistogram.end(); ++i) {
    std::cerr << (i - ProgHistogram.begin()) << ' ' << *i << '\n';
  }
  std::cerr << std::endl;
  #endif

  // check for remaining live threads
  for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
    const unsigned char op = t->PC->OpCode;
    if (op == HALT_OP || op == FINISH_OP) {
      continue;
    }

    // this is a live thread
    return true;
  }

  return false;
}

void Vm::closeOut(HitCallback& hitFn) {
  CurHitFn = &hitFn;
  if (!CurHitFn) {
    return;
  }

  SearchHit hit;

  for (ThreadList::iterator t(Active.begin()); t != Active.end(); ++t) {
    if (t->PC->OpCode == FINISH_OP) {
      // has match
      if (t->Start >= MatchEnds[t->Label]) {
        MatchEnds[t->Label] = t->End + 1;

        hit.Offset = t->Start;
        hit.Length = t->End - t->Start + 1;
        hit.Label = t->Label;
        CurHitFn->collect(hit);
      }
    }
  }
}
