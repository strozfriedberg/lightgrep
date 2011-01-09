#include "vm.h"

#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>

static uint64 UNALLOCATED = std::numeric_limits<uint64>::max();

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

#ifdef LBT_TRACE_ENABLED
uint64 Thread::NextId = 0;

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

void Vm::new_thread_json(std::ostream& out, uint64 offset,
                         const Thread& t, const Instruction* base) {
  thread_json(out, offset, t, base, Thread::BORN);
}

void Vm::kill_thread_json(std::ostream& out, uint64 offset,
                         const Thread& t, const Instruction* base) {
  thread_json(out, offset, t, base, Thread::DEAD);
}

void Vm::run_thread_json(std::ostream& out, uint64 offset,
                         const Thread& t, const Instruction* base) {
  thread_json(out, offset, t, base, Thread::RUNNING);
}

void Vm::thread_json(std::ostream& out, uint64 offset,
                     const Thread& t, const Instruction* base,
                     Thread::ThreadLife state) {
  if (BeginDebug <= offset && offset < EndDebug) {
    // put commas between consecutive threads
    if (first_thread_json) {
      first_thread_json = false;
    }
    else {
      out << ", ";
    }

    t.output_json(out, base, state);
  }
}

void Thread::output_json(std::ostream& out, const Instruction* base, Thread::ThreadLife state) const {
  out << "{ \"Id\":" << Id
      << ", \"PC\":" << (PC ? PC - base: -1)
      << ", \"Label\":" << Label
      << ", \"Start\":" << Start 
      << ", \"End\":" << End
      << ", \"state\":" << state
      << " }";
}
#endif

boost::shared_ptr<VmInterface> VmInterface::create() {
  return boost::shared_ptr<VmInterface>(new Vm);
}

Vm::Vm() : BeginDebug(UNALLOCATED), EndDebug(UNALLOCATED), CurHitFn(0) {}

Vm::Vm(ProgramPtr prog): 
  BeginDebug(UNALLOCATED), EndDebug(UNALLOCATED), CurHitFn(0)
{
  init(prog);
}

void Vm::init(ProgramPtr prog) {
  Prog = prog;
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
  if (_executeEpSequence(&(*Prog)[0], s0, 0)) {
    Next.push_back(s0);
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
  Matches.assign(Matches.size(), std::pair<uint64, uint64>(UNALLOCATED, 0));
  CurHitFn = 0;
}

inline bool Vm::_execute(const Instruction* base, Thread& t, const byte* cur) {
  // std::string instr;
  // std::cerr << t << std::endl;
  // instr = t.PC->toString(); // for some reason, toString() is corrupting the stack... maybe?
  // std::cerr << instr << std::endl;
  // std::cout << t << ": " << *t.PC << std::endl;
  Thread nextT;
  register Instruction instr = *t.PC;
  switch (instr.OpCode) {
    case LIT_OP:
      // std::cerr << "Lit " << t.PC->Op.Literal << std::endl;
      if (*cur == instr.Op.Literal) {
        t.advance();
        return true;
      }
      break;
    case EITHER_OP:
      if (*cur == instr.Op.Range.First || *cur == instr.Op.Range.Last) {
        t.advance();
        return true;
      }
      break;
    case RANGE_OP:
      if (instr.Op.Range.First <= *cur && *cur <= instr.Op.Range.Last) {
        t.advance();
        return true;
      }
      break;
    case BIT_VECTOR_OP:
      {
        const ByteSet* setPtr = reinterpret_cast<const ByteSet*>(t.PC + 1);
        if ((*setPtr)[*cur]) {
          t.advance();
          return true;
        }
      }
      break;
    case JUMP_TABLE_OP:
      if (*(uint32*)(t.PC + 1 + *cur) != 0xffffffff) {
        t.jump(base, *reinterpret_cast<const uint32*>(t.PC + 1 + *cur));
        return true;
      }
      break;
    case JUMP_TABLE_RANGE_OP:
      if (instr.Op.Range.First <= *cur && *cur <= instr.Op.Range.Last) {
        const uint32 addr = *reinterpret_cast<const uint32*>(t.PC + 1 + (*cur - instr.Op.Range.First));
        if (addr != 0xffffffff) {
          t.jump(base, addr);
          return true;
        }
      }
      break;
  }
  t.PC = 0;
  return false;
}

// while base is always == &Program[0], we pass it in because it then should get inlined away
inline bool Vm::_executeEpsilon(const Instruction* base, Thread& t, uint64 offset) {
  register Instruction instr = *t.PC;
  switch (instr.OpCode) {
    case FORK_OP:
      {
        Thread f = t;
        t.advance();
        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          Next.push_back(t);
        }
        // now back up to the fork, and fall through to handle it as a jump
        t = f;

        #ifdef LBT_TRACE_ENABLED
        t.Id = Thread::NextId++;
        new_thread_json(std::cerr, offset, t, base);
        #endif
      }
    case JUMP_OP:
      t.jump(base, instr.Op.Offset);
      return true;
    case LONGFORK_OP:
      {
        Thread f = t;
        t.advance();
        // recurse to keep going in sequence
        if (_executeEpSequence(base, t, offset)) {
          Next.push_back(t);
        }
        // now back up to the fork, and fall through to handle it as a longjump
        t = f;

        #ifdef LBT_TRACE_ENABLED
        t.Id = Thread::NextId++;
        new_thread_json(std::cerr, offset, t, base);
        #endif
      }
    case LONGJUMP_OP:
      t.jump(base, *reinterpret_cast<const uint32*>(t.PC+1));
      return true;
    case CHECK_HALT_OP:
      if (CheckStates[instr.Op.Offset]) {
        t.PC = 0;
        return false;
      }
      else {
        CheckStates[instr.Op.Offset] = true;
        CheckStates[0] = true;
        t.advance();
        return true;
      }
    case LABEL_OP:
      t.Label = instr.Op.Offset;
      t.advance();
      return true;
    case MATCH_OP:
      t.End = offset;
      if (t.Label == std::numeric_limits<uint32>::max()) {
        t.Label = 0;
      }
      t.advance();
      return true;
    case HALT_OP:
      t.PC = 0;

      #ifdef LBT_TRACE_ENABLED
      kill_thread_json(std::cerr, offset, t, base);
      #endif
    default:
      // Next.push_back(t);
      return false;
  }
}

inline void Vm::_executeThread(const Instruction* base, Thread& t, const byte* cur, uint64 offset) {
  #ifdef LBT_TRACE_ENABLED
  run_thread_json(std::cerr, offset, t, base);
  #endif

  if (_execute(base, t, cur) && _executeEpSequence(base, t, offset)) {
    Next.push_back(t);
  }
}

inline bool Vm::_executeEpSequence(const Instruction* base, Thread& t, uint64 offset) {
  #ifdef LBT_TRACE_ENABLED
  do {
    run_thread_json(std::cerr, offset, t, base);
  } while (_executeEpsilon(base, t, offset));
  #else
  while (_executeEpsilon(base, t, offset));
  #endif
  
  if (t.End == offset) { // this could be bad at offset 2^32-1, dummy -- JLS
    doMatch(t);
  }
  return t.PC;
}

inline void Vm::_executeFrame(const ByteSet& first, ThreadList::iterator& threadIt, const Instruction* base, const byte* cur, uint64 offset) {
  // run old threads at this offset
  while (threadIt != Active.end()) {
    _executeThread(base, *threadIt, cur, offset);
    ++threadIt;
  }

  // create new threads at this offset
  if (first[*cur]) {
    for (ThreadList::const_iterator it(First.begin()); it != First.end(); ++it) {
      Active.addBack().init(it->PC, std::numeric_limits<uint32>::max(), offset, std::numeric_limits<uint64>::max());

      #ifdef LBT_TRACE_ENABLED
      Active[Active.size()-1].Id = Thread::NextId++;
      new_thread_json(std::cerr, offset, Active[Active.size()-1], base);
      #endif
    }
//    Active.addBack().init(base, offset);

    do {
      _executeThread(base, *threadIt, cur, offset);
    } while (++threadIt != Active.end());
  }
}

bool Vm::execute(Thread& t, const byte* cur) {
  return _execute(&(*Prog)[0], t, cur);
}

bool Vm::executeEpsilon(Thread& t, uint64 offset) {
  return _executeEpsilon(&(*Prog)[0], t, offset);
}

void Vm::executeFrame(const byte* cur, uint64 offset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  ThreadList::iterator threadIt = Active.begin();
  _executeFrame(Prog->First, threadIt, &(*Prog)[0], cur, offset);
}

void Vm::doMatch(const Thread& t) {
  // std::cerr << "had a match" << std::endl;
  SearchHit  hit;
  std::pair< uint64, uint64 > lastHit = Matches[t.Label];
  if (lastHit.first == UNALLOCATED || (lastHit.first == t.Start && lastHit.second < t.End)) {
    Matches[t.Label] = std::make_pair(t.Start, t.End);
  }
  else if (lastHit.second < t.Start) {
    hit.Offset = lastHit.first;
    hit.Length = lastHit.second - lastHit.first + 1;
    hit.Label = t.Label;
    if (CurHitFn) {
      CurHitFn->collect(hit);
    }
    // std::cerr << "emitting hit " << hit << std::endl;
    Matches[t.Label] = std::make_pair(t.Start, t.End);
  }
}

// FIXME: beg is a register, but used only once!
bool Vm::search(register const byte* beg, register const byte* end, uint64 startOffset, HitCallback& hitFn) {
  CurHitFn = &hitFn;
  const Instruction* base = &(*Prog)[0];
  SearchHit hit;
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

  // output the last existing matches
  for (uint32 i = 0; i < Matches.size(); ++i) {
    if (Matches[i].first < UNALLOCATED) {
      hit.Offset = Matches[i].first;
      hit.Length = Matches[i].second - hit.Offset + 1;
      hit.Label = i;
      hitFn.collect(hit);
      Matches[i] = std::make_pair(UNALLOCATED, 0ul);
    }
  }
  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;
  return Active.size() > 0; // potential hits, if there's more data
}
