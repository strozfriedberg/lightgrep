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

void Thread::output(std::ostream& out, const Instruction* base) const {
  out << "{ \"pc\":" << (PC ? PC - base: -1) << ", \"Label\":" << Label << ", \"Start\":" << Start << ", \"End\":" << End << " }";
}

Vm::Vm() : SkipTblPtr(0), BeginDebug(UNALLOCATED), EndDebug(UNALLOCATED) {}

void Vm::init(ProgramPtr prog, ByteSet firstBytes, uint32 numCheckedStates, boost::shared_ptr<SkipTable> skip) {
  Prog = prog;
  Skip = skip;
  Active.resize(Prog->size());
  Next.resize(Prog->size());
  First = firstBytes;
  CheckStates.resize(numCheckedStates);
  CheckStates.assign(numCheckedStates, false);
  uint32 numPatterns = 0;
  Program& p(*Prog);
  for (uint32 i = 0; i < p.size(); ++i) {
    if (p[i].OpCode == MATCH_OP && numPatterns < p[i].Op.Offset) {
      numPatterns = p[i].Op.Offset;
    }
  }
  ++numPatterns;
  Matches.resize(numPatterns);
  Matches.assign(numPatterns, std::pair<uint64, uint64>(UNALLOCATED, 0));
}

inline bool _execute(const Instruction* base, Thread& t, std::vector<bool>& checkStates, Vm::ThreadList& active, Vm::ThreadList& next, const byte* cur, uint64 offset) {
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
        next.push_back(t);
      }
      else {
        t.PC = 0;
      }
      return false;
    case EITHER_OP:
      if (*cur == instr.Op.Range.First || *cur == instr.Op.Range.Last) {
        t.advance();
        next.push_back(t);
      }
      else {
        t.PC = 0;
      }
      return false;
    case RANGE_OP:
      if (instr.Op.Range.First <= *cur && *cur <= instr.Op.Range.Last) {
        t.advance();
        next.push_back(t);
      }
      else {
        t.PC = 0;
      }
      return false;
    case BIT_VECTOR_OP:
      {
        const ByteSet* setPtr = reinterpret_cast<const ByteSet*>(t.PC + 1);
        if ((*setPtr)[*cur]) {
          t.advance();
          next.push_back(t);
        }
        else {
          t.PC = 0;
        }
      }
      return false;
    case JUMP_TABLE_OP:
      nextT.fork(t, t.PC, 1 + *cur);
      if (nextT.PC->OpCode != HALT_OP) {
        next.push_back(nextT);
      }
      else {
        t.PC = 0;
      }
      return false;
    case JUMP_OP:
      // std::cerr << "Jump " << t.PC->Op.Offset << std::endl;
      t.jump(base, instr.Op.Offset);
      return true;
    case FORK_OP:
      // std::cerr << "Fork " << t.PC->Op.Offset << std::endl;
      nextT.fork(t, base, instr.Op.Offset);
      active.push_back(nextT);
      t.advance();
      return true;
    case CHECK_BRANCH_OP:
      if (checkStates[instr.Op.Offset]) {
        t.advance();
      }
      else {
        checkStates[instr.Op.Offset] = true;
        checkStates[0] = true;
      }
      t.advance();
      return true;
    case CHECK_HALT_OP:
      if (checkStates[instr.Op.Offset]) {
        t.PC = 0;
        return false;
      }
      else {
        checkStates[instr.Op.Offset] = true;
        checkStates[0] = true;
        t.advance();
        return true;
      }
    case MATCH_OP:
      // std::cerr << "at " << offset << ", " << *t.PC << std::endl;
      t.Label = instr.Op.Offset;
      t.End = offset;
      t.advance();
      return true;
    case HALT_OP:
      t.PC = 0;
      return false;
  }
  return false;
}

inline bool _executeEpsilons(const Instruction* base, Thread& t, std::vector<bool>& checkStates, Vm::ThreadList& active, Vm::ThreadList& next, uint64 offset) {
  Thread f;
  register Instruction instr = *t.PC;
  switch (instr.OpCode) {
    case LIT_OP:
    case EITHER_OP:
    case RANGE_OP:
    case BIT_VECTOR_OP:
    case JUMP_TABLE_OP:
      next.push_back(t);
      return false;
    case JUMP_OP:
      t.jump(base, instr.Op.Offset);
      return true;
    case FORK_OP:
      f.fork(t, base, instr.Op.Offset);
      active.push_back(f);
      t.advance();
      return true;
    case CHECK_BRANCH_OP:
      if (checkStates[instr.Op.Offset]) {
        t.advance();
      }
      else {
        checkStates[instr.Op.Offset] = true;
        checkStates[0] = true;
      }
      t.advance();
      return true;
    case CHECK_HALT_OP:
      if (checkStates[instr.Op.Offset]) {
        t.PC = 0;
        return false;
      }
      else {
        checkStates[instr.Op.Offset] = true;
        checkStates[0] = true;
        t.advance();
        return true;
      }
    case MATCH_OP:
      t.Label = instr.Op.Offset;
      t.End = offset;
      t.advance();
      return true;
    case HALT_OP:
      t.PC = 0;
      return false;
  }
  return true;
}

bool Vm::execute(const Instruction* base, Thread& t, std::vector<bool>& checkStates, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset) {
  return _execute(base, t, checkStates, active, next, cur, offset);
}

void Vm::doMatch(register ThreadList::iterator threadIt, HitCallback& hitFn) {
  // std::cerr << "had a match" << std::endl;
  SearchHit  hit;
  std::pair< uint64, uint64 > lastHit = Matches[threadIt->Label];
  if (lastHit.first == UNALLOCATED || (lastHit.first == threadIt->Start && lastHit.second < threadIt->End)) {
    Matches[threadIt->Label] = std::make_pair(threadIt->Start, threadIt->End);
  }
  else if (lastHit.second <= threadIt->Start) {
    hit.Offset = lastHit.first;
    hit.Length = lastHit.second - lastHit.first;
    hit.Label = threadIt->Label;
    hitFn.collect(hit);
    // std::cerr << "emitting hit " << hit << std::endl;
    Matches[threadIt->Label] = std::make_pair(threadIt->Start, threadIt->End);
  }
}

inline void Vm::cleanup() {
  Active.swap(Next);
  Next.clear();
  if (CheckStates[0]) {
    CheckStates.assign(CheckStates.size(), false);
  }
}

bool Vm::search(register const byte* beg, register const byte* end, uint64 startOffset, HitCallback& hitFn) {
  const Instruction* base = &(*Prog)[0];
  Thread     newThread;
  SearchHit  hit;
  register uint64     offset = startOffset;
  register ThreadList::iterator threadIt;
  // uint32     lminOffset = Skip ? Skip->l_min() - 1: 0;
  // std::vector<uint32>* skipTbl = Skip ? &Skip->skipVec(): SkipTblPtr.get();
  // uint32     skipAmount;
  // if (!skipTbl) {
  //   SkipTblPtr.reset(new std::vector<uint32>(256, 0));
  //   skipTbl = SkipTblPtr.get();
  // }
  // uint32   maxActive = 0;
  // double   total = 0;
  for (register const byte* cur = beg; cur != end; ++cur) {
    // std::cerr << "offset = " << offset << ", ";
    // if (std::isprint(*cur)) {
    //   std::cerr << *cur;
    // }
    // else {
    //   std::cerr << std::hex << std::setfill('0') << std::setw(2) << (unsigned short)(*cur);
    // }
    // std::cerr << std::dec << ", " << Active.size() << " active threads" << std::endl;
    // total += Active.size();
    for (threadIt = Active.begin(); threadIt != Active.end(); ++threadIt) {
      while (_execute(base, *threadIt, CheckStates, Active, Next, cur, offset)) ;
      if (threadIt->End == offset) {
        doMatch(threadIt, hitFn);
      }
    }
    if (First[*cur]) {
      newThread.init(base, offset);
      Active.push_back(newThread);
      do {
        while (_execute(base, *threadIt, CheckStates, Active, Next, cur, offset)) ;
        if (threadIt->End == offset) {
          doMatch(threadIt, hitFn);
        }
      } while (++threadIt != Active.end());
    }
    if (threadIt != Active.begin()) {
      #ifdef LBT_TRACE_ENABLED
      if (BeginDebug <= offset && offset < EndDebug) {
        std::cerr << "{\"offset\":" << offset << ", \"num\":" << Active.size() << ", \"list\":[";
        threadIt = Active.begin();
        threadIt->output(std::cerr, base);
        while (++threadIt != Active.end()) {
          std::cerr << ", ";
          threadIt->output(std::cerr, base);
        }
        std::cerr << "]}\n";
      }
      #endif
      cleanup();
    }
    ++offset;
  }
  // this flushes out last char matches
  // and leaves us only with comparison instructions (in next)
  for (threadIt = Active.begin(); threadIt != Active.end(); ++threadIt) {
    while (_executeEpsilons(base, *threadIt, CheckStates, Active, Next, offset)) ;
    if (threadIt->End == offset) {
      doMatch(threadIt, hitFn);
    }
  }
  for (uint32 i = 0; i < Matches.size(); ++i) {
    if (Matches[i].first < UNALLOCATED) {
      hit.Offset = Matches[i].first;
      hit.Length = Matches[i].second - hit.Offset;
      hit.Label = i;
      hitFn.collect(hit);
      Matches[i] = std::make_pair(UNALLOCATED, 0ul);
    }
  }
  cleanup();
  // std::cerr << "Max number of active threads was " << maxActive << ", average was " << total/(end - beg) << std::endl;
  return Active.size() > 0; // potential hits, if there's more data
}
