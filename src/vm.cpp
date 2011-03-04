#include "vm.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

static uint32 NOLABEL = std::numeric_limits<uint32>::max();
static uint64 NONE = std::numeric_limits<uint64>::max();

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC
      << ", \"Label\":" << std::dec << t.Label
      << ", \"Id\":" << t.Id
      << ", \"Start\":" << t.Start
      << ", \"End\":" << t.End << " }";
  return out;
}

#ifdef LBT_TRACE_ENABLED
std::set<uint64> new_thread_json;

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

bool Vm::atEpsilon(const Thread& t) const {
  switch (t.PC->OpCode) {
    case FORK_OP:
    case JUMP_OP:
    case LONGFORK_OP:
    case LONGJUMP_OP:
    case CHECK_HALT_OP:
    case MATCH_OP:
    case HALT_OP:
      return true;
    default:
      return false;
  }
}
#endif

boost::shared_ptr<VmInterface> VmInterface::create() {
  return boost::shared_ptr<VmInterface>(new Vm);
}

Vm::Vm() :
  #ifdef LBT_TRACE_ENABLED
  BeginDebug(NONE), EndDebug(NONE),
  #endif
  NextId(0), CurHitFn(0) {}

Vm::Vm(ProgramPtr prog): 
  #ifdef LBT_TRACE_ENABLED
  BeginDebug(NONE), EndDebug(NONE),
  #endif
  NextId(0), CurHitFn(0)
{
  init(prog);
}

void Vm::init(ProgramPtr prog) {
  Prog = prog;
  Prog->push_back(Instruction::makeHalt()); // a special halt; killed threads will be set to here
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
  numCheckedStates += 2; // bit 0 reserved for whether any bits were flipped
  Matches.resize(numPatterns);
  CheckStates.resize(numCheckedStates);

  Thread s0(&(*Prog)[0]);
  ThreadList::iterator t = &s0;

  #ifdef LBT_TRACE_ENABLED
  if (atEpsilon(s0)) {
    open_init_epsilon_json(std::cerr);
    new_thread_json.insert(s0.Id = 0);
    pre_run_thread_json(std::cerr, 0, s0, &(*Prog)[0]);
  }
  #endif

  if (_executeEpSequence(&(*Prog)[0], t, 0)) {
    Next.push_back(s0);

    #ifdef LBT_TRACE_ENABLED
    post_run_thread_json(std::cerr, 0, s0, &(*Prog)[0]);
    close_init_epsilon_json(std::cerr);
    #endif
  }

  First.resize(Next.size());
  for (uint32 i = 0; i < Next.size(); ++i) {
    First.push_back(Next[i]);
  }

  reset();
}

void Vm::reset() {
  Active.clear();
  Next.clear();
  CheckStates.assign(CheckStates.size(), false);
  Matches.assign(Matches.size(), std::pair<uint64, uint64>(NONE, 0));
  CurHitFn = 0;
}

inline bool Vm::_execute(const Instruction* base, ThreadList::iterator t, const byte* cur) {
  Thread nextT;
  register Instruction instr = *t->PC;
  switch (instr.OpCode) {
    case LIT_OP:
      // std::cerr << "Lit " << t->PC->Op.Literal << std::endl;
      if (*cur == instr.Op.Literal) {
        t->advance();
        return true;
      }
      break;
    case EITHER_OP:
      if (*cur == instr.Op.Range.First || *cur == instr.Op.Range.Last) {
        t->advance();
        return true;
      }
      break;
    case RANGE_OP:
      if (instr.Op.Range.First <= *cur && *cur <= instr.Op.Range.Last) {
        t->advance();
        return true;
      }
      break;
    case BIT_VECTOR_OP:
      {
        const ByteSet* setPtr = reinterpret_cast<const ByteSet*>(t->PC + 1);
        if ((*setPtr)[*cur]) {
          t->advance();
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
        t->advance();
        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          Next.push_back(*t);
        }
        // now back up to the fork, and fall through to handle it as a jump
        *t = f;
        t->Id = NextId++;

        #ifdef LBT_TRACE_ENABLED
        new_thread_json.insert(t->Id = Thread::NextId++);
        #endif
      }
    case JUMP_OP:
      t->jump(base, instr.Op.Offset);
      return true;
    case LONGFORK_OP:
      {
        Thread f = *t;
        t->advance();
        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          Next.push_back(*t);
        }
        // now back up to the fork, and fall through to handle it as a longjump
        *t = f;
        t->Id = NextId++;

        #ifdef LBT_TRACE_ENABLED
        new_thread_json.insert(t->Id = Thread::NextId++);
        #endif
      }
    case LONGJUMP_OP:
      t->jump(base, *reinterpret_cast<const uint32*>(t->PC+1));
      return true;
    case CHECK_HALT_OP:
      if (CheckStates[instr.Op.Offset]) { // read sync point
        t->PC = 0;
        return false;
      }
      else {
        CheckStates[instr.Op.Offset] = true; // write sync point
        CheckStates[0] = true;
        t->advance();
        return true;
      }
    case LABEL_OP:
      {
        std::pair<uint64, uint64> lastHit(Matches[instr.Op.Offset]);
        if (lastHit.first == NONE ||
    			lastHit.first == t->Start ||
    			lastHit.second < t->Start)
    		{
          t->Label = instr.Op.Offset;
          t->advance();
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
      t->advance();

      // makr same-labeled threads after us for death, due to overlap
//      Kill.push_back(std::make_pair(t+1, t->Label));

      // kill all same-labeled threads after us, due to overlap
      for (ThreadList::iterator it = t+1; it != Active.end(); ++it) {
        if (it->Label == t->Label) {
          it->End = NONE;
          it->PC = &Prog->back(); // DIE. Last instruction is always a halt
        }
      }
      return true;
    case HALT_OP:
      t->PC = 0;
    default:
      // Next.push_back(t);
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
  while (_executeEpsilon(base, t, offset));
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
      Active.addBack().init(it->PC, NOLABEL, NextId++, offset, NONE);

      #ifdef LBT_TRACE_ENABLED
      new_thread_json.insert(Active[Active.size()-1].Id = Thread::NextId++);
      #endif
    }

    do {
      _executeThread(base, threadIt, cur, offset);
    } while (++threadIt != Active.end());
  }

/*
  // kill threads overlapping higher-priority matchers
  for (std::vector< std::pair< ThreadList::iterator, uint32 > >::iterator i(Kill.begin()); i != Kill.end(); ++i) {
    for (ThreadList::iterator it(i->first); it != Active.end(); ++it) {
      if (it->Label == i->second) {
        it->End = NONE;
        it->PC = &Prog->back(); // DIE. Last instruction is always a halt
      }
    }
  }

  Kill.clear();
*/
}

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
  // std::cerr << "had a match" << std::endl;
  std::pair< uint64, uint64 > lastHit = Matches[t.Label];
  
  if (lastHit.first != NONE && lastHit.second < t.Start) {
    if (CurHitFn) {
      SearchHit hit(lastHit.first, lastHit.second - lastHit.first + 1, t.Label);
      CurHitFn->collect(hit);
    }
  }

  Matches[t.Label] = std::make_pair(t.Start, t.End);

  #ifdef LBT_TRACE_ENABLED
  if (lastHit.first < t.Start && t.Start <= lastHit.second) {
    std::cerr << "** Replaced overlapping hit! (" << lastHit.first
      << ", " << lastHit.second << "), thread: " << t << std::endl;
  }
  #endif
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
      cleanup();
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
      std::pair<uint64, uint64> lastHit = Matches[i];
      if (lastHit.first != NONE) {
        hit.Offset = lastHit.first;
        hit.Length = lastHit.second - lastHit.first + 1;
        hit.Label  = i;
        CurHitFn->collect(hit);
      }
    }
  }
}
