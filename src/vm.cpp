#include "vm.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

void Vm::init(ProgramPtr prog, ByteSet firstBytes) {
  Program = prog;
  Active.resize(Program->size());
  Next.resize(Program->size());
  First = firstBytes;
}

bool Vm::execute(const Instruction* base, Thread& t, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset) {
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
    case FORK_OP:
      // std::cerr << "Fork " << t.PC->Op.Offset << std::endl;
      nextT.fork(t, base, t.PC->Op.Offset);
      active.push_back(nextT);
      t.advance();
      return true;
    case SAVE_LABEL_OP:
      // std::cerr << "SaveLabel " << t.PC->Op.Offset << std::endl;
      t.Label = t.PC->Op.Offset;
      t.advance();
      return true;
    case MATCH_OP:
      // std::cerr << "Match" << std::endl;
      t.End = offset;
      break;
  }
  return false;
}

bool executeEpsilons(const Instruction* base, Thread& t, Vm::ThreadList& active, Vm::ThreadList& next, uint64 offset) {
  Thread f;
  switch (t.PC->OpCode) {
    case LIT_OP:
    case EITHER_OP:
    case RANGE_OP:
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
    case SAVE_LABEL_OP:
      t.Label = t.PC->Op.Offset;
      t.advance();
      break;
    case MATCH_OP:
      t.End = offset;
      return false;
  }
  return true;
}

bool Vm::search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) {
  const Instruction* base = &(*Program)[0];
  SearchHit  hit;
  uint64     offset = startOffset;
  Thread     t;
  for (const byte* cur = beg; cur != end; ++cur) {
    // std::cerr << "offset = " << offset << ", " << *cur << std::endl;
    if (First[*cur]) {
      Active.push_back(Thread(base, 0, offset, std::numeric_limits<uint64>::max()));
    }
    for (uint32 i = 0; i < Active.size(); ++i) {
      t = Active[i];
      // std::cerr << i << std::endl;
      // std:: cout << i << " threadex " << t << std::endl;
      while (execute(base, t, Active, Next, cur, offset)) ;
      // std::cerr << "finished thread" << std::endl;
      if (t.End == offset) {
        hit.Offset = t.Start;
        hit.Length = t.End - t.Start;
        hit.Label = t.Label;
        hitFn.collect(hit);
      }
    }
    ++offset;
    Active.swap(Next);
    Next.clear();
  }
  // this flushes out last char matches
  // and leaves us only with comparison instructions (in next)
  for (uint32 i = 0; i < Active.size(); ++i) {
    t = Active[i];
    while (executeEpsilons(base, t, Active, Next, offset)) ;
    if (t.End == offset) {
      hit.Offset = t.Start;
      hit.Length = t.End - t.Start;
      hit.Label = t.Label;
      hitFn.collect(hit);
    }
  }
  Active.clear();
  Active.swap(Next);
  return Active.size() > 0; // potential hits, if there's more data
}
