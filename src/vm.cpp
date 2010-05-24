#include "vm.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

void Vm::init(ProgramPtr prog, ByteSet firstBytes, uint32 numCheckedStates) {
  Program = prog;
  Active.resize(Program->size());
  Next.resize(Program->size());
  First = firstBytes;
  CheckStates.resize(numCheckedStates);
  CheckStates.assign(numCheckedStates, false);
}

bool Vm::execute(const Instruction* base, Thread& t, std::vector<bool>& checkStates, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset) {
  // std::string instr;
  // std::cerr << t << std::endl;
  // instr = t.PC->toString(); // for some reason, toString() is corrupting the stack... maybe?
  // std::cerr << instr << std::endl;
  // std::cout << t << ": " << *t.PC << std::endl;
  Thread nextT;
  switch (t.PC->OpCode) {
    case LIT_OP:
      // std::cerr << "Lit " << t.PC->Op.Literal << std::endl;
      if (*cur == t.PC->Op.Literal) {
        t.advance();
        next.push_back(t);
      }
      break;
    case EITHER_OP:
      if (*cur == t.PC->Op.Range.First || *cur == t.PC->Op.Range.Last) {
        t.advance();
        next.push_back(t);
       }
      break;
    case RANGE_OP:
      if (t.PC->Op.Range.First <= *cur && *cur <= t.PC->Op.Range.Last) {
        t.advance();
        next.push_back(t);
      }
      break;
    case JUMP_OP:
      // std::cerr << "Jump " << t.PC->Op.Offset << std::endl;
      t.jump(base, t.PC->Op.Offset);
      return true;
    case JUMP_TABLE_OP:
      nextT.fork(t, t.PC, 1 + *cur);
      next.push_back(nextT);
      break;
    case FORK_OP:
      // std::cerr << "Fork " << t.PC->Op.Offset << std::endl;
      nextT.fork(t, base, t.PC->Op.Offset);
      active.push_back(nextT);
      t.advance();
      return true;
    case CHECK_BRANCH_OP:
      if (checkStates[t.PC->Op.Offset]) {
        t.advance();
      }
      else {
        checkStates[t.PC->Op.Offset] = true;
        checkStates[0] = true;
      }
      t.advance();
      return true;
    case MATCH_OP:
      // std::cerr << "at " << offset << ", " << *t.PC << std::endl;
      t.Label = t.PC->Op.Offset;
      t.End = offset;
      t.advance();
      return true;
    case HALT_OP:
      return false;
  }
  return false;
}

bool executeEpsilons(const Instruction* base, Thread& t, std::vector<bool>& checkStates, Vm::ThreadList& active, Vm::ThreadList& next, uint64 offset) {
  Thread f;
  switch (t.PC->OpCode) {
    case LIT_OP:
    case EITHER_OP:
    case RANGE_OP:
    case JUMP_TABLE_OP:
      next.push_back(t);
      return false;
    case JUMP_OP:
      t.jump(base, t.PC->Op.Offset);
      break;
    case FORK_OP:
      f.fork(t, base, t.PC->Op.Offset);
      active.push_back(f);
      t.advance();
      break;
    case CHECK_BRANCH_OP:
      if (checkStates[t.PC->Op.Offset]) {
        t.advance();
      }
      else {
        checkStates[t.PC->Op.Offset] = true;
        checkStates[0] = true;
      }
      t.advance();
      return true;
    case MATCH_OP:
      t.Label = t.PC->Op.Offset;
      t.End = offset;
      t.advance();
      break;
    case HALT_OP:
      return false;
  }
  return true;
}

bool Vm::search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) {
  const Instruction* base = &(*Program)[0];
  SearchHit  hit;
  uint64     offset = startOffset;
  for (const byte* cur = beg; cur != end; ++cur) {
    // std::cerr << "offset = " << offset << ", " << *cur << std::endl;
    if (First[*cur]) {
      Active.push_back(Thread(base, 0, offset, std::numeric_limits<uint64>::max()));
    }
    for (ThreadList::iterator threadIt(Active.begin()); threadIt != Active.end(); ++threadIt) {
      // std:: cout << i << " threadex " << *threadIt << std::endl;
      while (execute(base, *threadIt, CheckStates, Active, Next, cur, offset)) ;
      // std::cerr << "finished thread" << std::endl;
      if (threadIt->End == offset) {
        hit.Offset = threadIt->Start;
        hit.Length = threadIt->End - threadIt->Start;
        hit.Label = threadIt->Label;
        hitFn.collect(hit);
      }
    }
    ++offset;
    Active.swap(Next);
    Next.clear();
    if (CheckStates[0]) {
      CheckStates.assign(CheckStates.size(), false);
    }
  }
  // this flushes out last char matches
  // and leaves us only with comparison instructions (in next)
  for (ThreadList::iterator threadIt(Active.begin()); threadIt != Active.end(); ++threadIt) {
    while (executeEpsilons(base, *threadIt, CheckStates, Active, Next, offset)) ;
    if (threadIt->End == offset) {
      hit.Offset = threadIt->Start;
      hit.Length = threadIt->End - threadIt->Start;
      hit.Label = threadIt->Label;
      hitFn.collect(hit);
    }
  }
  Active.clear();
  Active.swap(Next);
  if (CheckStates[0]) {
    CheckStates.assign(CheckStates.size(), false);
  }
  return Active.size() > 0; // potential hits, if there's more data
}
