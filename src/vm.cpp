#include "vm.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

bool Vm::execute(const Instruction* base, Thread& t, ThreadList& active, ThreadList& next, const byte* cur, uint64 offset) {
  std::string instr;
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
    case MATCH_OP:
      // std::cerr << "Match" << std::endl;
      t.End = offset;
      break;
    case SAVE_LABEL_OP:
      // std::cerr << "SaveLabel " << t.PC->Op.Offset << std::endl;
      t.Label = t.PC->Op.Offset;
      t.advance();
      return true;
  }
  return false;
}

bool Vm::search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) {
  bool ret = false;
  const Instruction* base = &(*Program)[0];
  SearchHit  hit;
  // uint32     num = Program->size();
  uint64     offset = startOffset;
  ThreadList active,
             next;
  for (const byte* cur = beg; cur != end; ++cur) {
    // std::cerr << "offset = " << offset << ", " << *cur << std::endl;
    active.push_back(Thread(base, 0, offset, 0));
    for (uint32 i = 0; i < active.size(); ++i) {
      Thread* t = &active[i];
      // std::cerr << i << std::endl;
      // std:: cout << i << " threadex " << *t << std::endl;
      while (execute(base, *t, active, next, cur, offset)) ;
      // std::cerr << "finished thread" << std::endl;
      if (t->End == offset) {
        hit.Offset = t->Start;
        hit.Length = t->End - t->Start;
        hit.Label = t->Label;
        hitFn.collect(hit);
        ret = true;
      }
    }
    ++offset;
    active.swap(next);
    next.clear();
  }
  // BUG: need to evaluate any epsilon instructions at the end, in case there was a match
  return ret;
}
