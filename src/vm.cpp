#include "vm.h"

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

// TODO: there's no need to pass in PC separately, since it's part of the thread
bool Vm::execute(const Instruction* base, const Instruction* pc, Thread& t, ThreadList& next, const byte* cur, uint64 offset) {
  switch (pc->OpCode) {
    case LIT_OP:
      if (*cur == pc->Op.Literal) {
        next.push_back(Thread(pc+pc->wordSize(), 0, 0, 0));
      }
      break;
    case JUMP_OP:
      t.PC = base + pc->Op.Offset;
      return true;
    case MATCH_OP:
      t.End = offset;
      break;
    case SAVE_LABEL_OP:
      t.Label = pc->Op.Offset;
      t.Start = offset;
      t.PC += pc->wordSize();
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
      while (execute(base, t->PC, *t, next, cur, offset)) ;
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
