#include "vm.h"

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

// TODO: there's no need to pass in PC separately, since it's part of the thread
bool Vm::execute(const Instruction* base, Thread& t, ThreadList& next, const byte* cur, uint64 offset) {
  switch (t.PC->OpCode) {
    case LIT_OP:
      if (*cur == t.PC->Op.Literal) {
        next.push_back(Thread(t.PC + t.PC->wordSize(), 0, 0, 0));
      }
      break;
    case EITHER_OP:
      if (*cur == t.PC->Op.Range.First || *cur == t.PC->Op.Range.Last) {
        next.push_back(Thread(t.PC + t.PC->wordSize(), 0, 0, 0));
      }
      break;
    case RANGE_OP:
      if (t.PC->Op.Range.First <= *cur && *cur <= t.PC->Op.Range.Last) {
        next.push_back(Thread(t.PC + t.PC->wordSize(), 0, 0, 0));
      }
      break;
    case JUMP_OP:
      t.PC = base + t.PC->Op.Offset;
      return true;
    case MATCH_OP:
      t.End = offset;
      break;
    case SAVE_LABEL_OP:
      t.Label = t.PC->Op.Offset;
      t.Start = offset;
      t.PC += t.PC->wordSize();
      return true;
  }
  return false;
}

bool Vm::run(const Instruction* base, uint32 num, const byte* beg, const byte* end, uint64 startOffset) {
  // this will likely need to become a member function  
  uint64     offset = startOffset;
  Thread     t(base, 0, 0, 0);
  ThreadList active,
             next;
  active.push_back(t);
  for (const byte* cur = beg; cur != end; ++cur) {
    for (ThreadList::iterator t(active.begin()); t != active.end(); ++t) {
      while (execute(base, *t, next, cur, offset)) ;
      if (t->End == offset) {
        return true;
      }
    }
    ++offset;
    active.swap(next);
    next.clear();
  }
  return false;
}
