#include "container_out.h"
#include "vm.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

static const uint32 NOLABEL = std::numeric_limits<uint32>::max();
static const uint64 NONE = std::numeric_limits<uint64>::max();

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

std::ostream& operator<<(std::ostream& out, const Vm::Match& m) {
  return out << '(' << m.Start << ',' << m.End << ')';
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
  BeginDebug(NONE), EndDebug(NONE), NextId(0),
  #endif
  CurHitFn(0) {}

Vm::Vm(ProgramPtr prog): 
  #ifdef LBT_TRACE_ENABLED
  BeginDebug(NONE), EndDebug(NONE), NextId(0),
  #endif
  CurHitFn(0)
{
  init(prog);
}

void Vm::init(ProgramPtr prog) {
  Prog = prog;
  // Prog->push_back(Instruction::makeHalt()); // a special halt; killed threads will be set to here
  Active.resize(Prog->size());
  Next.resize(Prog->size());
  uint32 numPatterns = 0,
         numCheckedStates = 0;
  Program& p(*Prog);
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

  Matches.resize(numPatterns);
  Kill.resize(numPatterns);

  CheckStates.resize(numCheckedStates);

  Thread s0(&(*Prog)[0]);
  ThreadList::iterator t = &s0;

  #ifdef LBT_TRACE_ENABLED
  open_init_epsilon_json(std::cerr);
  new_thread_json.insert(s0.Id);
  pre_run_thread_json(std::cerr, 0, s0, &(*Prog)[0]);
  #endif

  if (_executeEpSequence(&(*Prog)[0], t, 0)) {
    Next.push_back(s0);
  }

  #ifdef LBT_TRACE_ENABLED
  post_run_thread_json(std::cerr, 0, s0, &(*Prog)[0]);
  close_init_epsilon_json(std::cerr);
  #endif

  First.resize(Next.size());
  for (uint32 i = 0; i < Next.size(); ++i) {
    First.push_back(Next[i]);
  }
  reset();
}

void Vm::reset() {
  MaxMatches = 0;
  Active.clear();
  Next.clear();
  CheckStates.clear();

  for (std::vector< std::vector< Match > >::iterator matchIt = Matches.begin(); matchIt != Matches.end(); ++matchIt) {
    matchIt->clear();
  }
  CurHitFn = 0;

  #ifdef LBT_TRACE_ENABLED
  NextId = 1;
  #endif
}

inline bool Vm::_execute(const Instruction* base, ThreadList::iterator t, const byte* cur) {
  Thread nextT;
  register Instruction instr = *t->PC;
  switch (instr.OpCode) {
    case LIT_OP:
      // std::cerr << "Lit " << t->PC->Op.Literal << std::endl;
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
  }
  t->PC = &Prog->back();
  return false;
}

// while base is always == &Program[0], we pass it in because it then should get inlined away
inline bool Vm::_executeEpsilon(const Instruction* base, ThreadList::iterator t, uint64 offset) {
  register Instruction instr = *t->PC;
  switch (instr.OpCode) {
    case FORK_OP:
      {
        Thread f = *t;
        t->advance(InstructionSize<FORK_OP>::VAL);

        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          Next.push_back(*t);

          // kill the child if the label is in the kill list
          // FIXME: overzealously kills threads for (a|b)+ on ab
          if (f.Label != NOLABEL && Kill.find(f.Label)) {
            f.PC = 0;
            return false;
          }
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
      if (CheckStates.find(instr.Op.Offset)) { // read sync point
        t->PC = 0;
        return false;
      }
      else {
        CheckStates.insert(instr.Op.Offset); // write sync point
        t->advance(InstructionSize<CHECK_HALT_OP>::VAL);
        return true;
      }
    case LABEL_OP:
      {
        std::vector< Match >& lblMatches(Matches[instr.Op.Offset]);
        if (lblMatches.empty() ||
          ((t->Start <= lblMatches.back().Start || lblMatches.back().End < t->Start) &&
          !Kill.find(instr.Op.Offset)))
    		{
          t->Label = instr.Op.Offset;
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
      doMatch(*t);
      t->advance(InstructionSize<MATCH_OP>::VAL);

      // kill all same-labeled threads after us, due to overlap
      for (ThreadList::iterator it = t+1; it != Active.end(); ++it) {
        if (it->Label == t->Label) {
          it->End = NONE;
          it->PC = &Prog->back(); // DIE. Last instruction is always a halt
        }
      }

      // also kill any thread receiving this label later in the frame
      Kill.insert(t->Label);
      return true;
    case HALT_OP:
      t->PC = 0;
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
    Next.push_back(*t);
  }
}

inline bool Vm::_executeEpSequence(const Instruction* base, ThreadList::iterator t, uint64 offset) {
  #ifdef LBT_TRACE_ENABLED
  bool ex;
  do {
    const uint64 id = t->Id; // t can change on a fork, we want the original
    pre_run_thread_json(std::cerr, offset, *t, base);
    ex = _executeEpsilon(base, t, offset);
    const Thread& x = t->Id == id ? *t : Next[Next.size()-1];
    post_run_thread_json(std::cerr, offset, x, base);
  } while (ex);
  #else
  while (_executeEpsilon(base, t, offset)) ;
  #endif
  
  return t->PC;
}

inline void Vm::_executeFrame(const ByteSet& first, ThreadList::iterator& threadIt, const Instruction* base, const byte* cur, uint64 offset) {
  // run old threads at this offset
  while (threadIt != Active.end()) {
    _executeThread(base, threadIt, cur, offset);
    ++threadIt;
  }

  // create new threads at this offset
  if (first[*cur]) {
    for (ThreadList::const_iterator it(First.begin()); it != First.end(); ++it) {
      #ifdef LBT_TRACE_ENABLED
      Active.addBack().init(it->PC, NOLABEL, NextId++, offset, NONE);
      #else
      Active.addBack().init(it->PC, NOLABEL, offset, NONE);
      #endif

      #ifdef LBT_TRACE_ENABLED
      new_thread_json.insert(Active[Active.size()-1].Id);
      #endif
    }
    do {
      _executeThread(base, threadIt, cur, offset);
    } while (++threadIt != Active.end());
  }
  Kill.clear();
}

inline void Vm::_cleanup() {
  Active.swap(Next);
  Next.clear();
  CheckStates.clear();
}

void Vm::cleanup() { _cleanup(); }

bool Vm::execute(ThreadList::iterator t, const byte* cur) {
  return _execute(&(*Prog)[0], t, cur);
}

bool Vm::executeEpsilon(ThreadList::iterator t, uint64 offset) {
  return _executeEpsilon(&(*Prog)[0], t, offset);
}

void Vm::executeFrame(const byte* cur, uint64 offset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  ThreadList::iterator threadIt = Active.begin();
  _executeFrame(Prog->First, threadIt, &(*Prog)[0], cur, offset);
}

void Vm::doMatch(const Thread& t) {
  //std::cerr << t << std::endl; 

  // check whether any higher-priority threads block us
  bool blocked = false;
  for (ThreadList::iterator it = Next.begin(); it != Next.end(); ++it) {
    if (it->Label == NONE || it->Label == t.Label) {
      blocked = true;
      break;
    }
  }

  if (blocked) {
    // check whether we replace any already-recorded matches
    for (std::vector<Match>::iterator im(Matches[t.Label].begin()); im != Matches[t.Label].end(); ++im) {
      if (im->Start <= t.End && t.Start <= im->End) {
        Matches[t.Label].erase(im, Matches[t.Label].end());
        break;
      }
    }
  }
  else {
    if (CurHitFn) {
      // emit all matches which aren't replaced by this one
      SearchHit hit;
      if (Matches[t.Label].size() > MaxMatches) {
        MaxMatches = Matches[t.Label].size();
      }

      for (std::vector<Match>::iterator im(Matches[t.Label].begin()); im != Matches[t.Label].end(); ++im) {
        if (im->Start > t.End || t.Start > im->End) {
          hit.set(im->Start, im->End - im->Start + 1, t.Label);
          CurHitFn->collect(hit);
        }
        else {
          break;
        }
      }
    }

    Matches[t.Label].clear();
  }

  // store this match
  Matches[t.Label].push_back(Match(t.Start, t.End));
}

void Vm::startsWith(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  const Instruction* base = &(*Prog)[0];
  ByteSet first = Prog->First;
  register uint64 offset = startOffset;
  if (first[*beg]) {
    for (ThreadList::const_iterator it(First.begin()); it != First.end(); ++it) {
      Active.addBack().init(it->PC, NOLABEL, offset, NONE);
    }
    ThreadList::iterator threadIt = Active.begin();
    for (register const byte* cur = beg; cur < end; ++cur) {
      while (threadIt != Active.end()) {
        _executeThread(base, threadIt, cur, offset);
        ++threadIt;
      }
      Kill.clear();
    
      cleanup();
      threadIt = Active.begin();
      if (threadIt == Active.end()) { // early exit if threads die out
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
  ThreadList::iterator threadIt = Active.begin();
  for (register const byte* cur = beg; cur < end; ++cur) {
    #ifdef LBT_TRACE_ENABLED
    open_frame_json(std::cerr, offset, cur);
    #endif

    _executeFrame(first, threadIt, base, cur, offset);

    #ifdef LBT_TRACE_ENABLED
    close_frame_json(std::cerr, offset);
    #endif
    
    if (threadIt != Active.begin()) {
      _cleanup();
      threadIt = Active.begin();
    }
    ++offset;
  }
  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;
  return Active.size() > 0; // potential hits, if there's more data
}

void Vm::closeOut(HitCallback& hitFn) {
  CurHitFn = &hitFn;
  SearchHit hit;

  if (CurHitFn) {
    for (uint32 i = 0; i < Matches.size(); ++i) {
      if (Matches[i].size() > MaxMatches) {
        MaxMatches = Matches[i].size();
      }
      for (std::vector<Match>::const_iterator j(Matches[i].begin()); j != Matches[i].end(); ++j) {
        if (j->Start != NONE) {
          hit.Offset = j->Start;
          hit.Length = j->End - j->Start + 1;
          hit.Label  = i;
          CurHitFn->collect(hit);
        }
      }
    }
  }
  // std::cerr << "MaxMatches = " << MaxMatches << std::endl;
}
