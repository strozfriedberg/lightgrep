#include "vm.h"

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

bool Vm::execute(const Instruction* base, Thread& t, ThreadList& next, const byte* cur, uint64 offset) {
  switch (t.PC->OpCode) {
    case LIT_OP:
      if (*cur == t.PC->Op.Literal) {
        next.push_back(Thread(t.PC + t.PC->wordSize(), t));
      }
      break;
    case EITHER_OP:
      if (*cur == t.PC->Op.Range.First || *cur == t.PC->Op.Range.Last) {
        next.push_back(Thread(t.PC + t.PC->wordSize(), t));
      }
      break;
    case RANGE_OP:
      if (t.PC->Op.Range.First <= *cur && *cur <= t.PC->Op.Range.Last) {
        next.push_back(Thread(t.PC + t.PC->wordSize(), t));
      }
      break;
    case JUMP_OP:
      t.PC = base + t.PC->Op.Offset;
      return true;
    case FORK_OP:
      next.push_back(Thread(base + t.PC->Op.Offset, t));
      return true;
    case MATCH_OP:
      t.End = offset;
      break;
    case SAVE_LABEL_OP:
      t.Label = t.PC->Op.Offset;
      t.PC += t.PC->wordSize();
      return true;
  }
  return false;
}

bool Vm::search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) {
  const Instruction* base = &(*Program)[0];
  SearchHit  hit;
  uint32     num = Program->size();
  uint64     offset = startOffset;
  Thread     t(base, 0, startOffset, 0);
  ThreadList active,
             next;
  active.push_back(t);
  for (const byte* cur = beg; cur != end; ++cur) {
    for (ThreadList::iterator t(active.begin()); t != active.end(); ++t) {
      while (execute(base, *t, next, cur, offset)) ;
      if (t->End == offset) {
        hit.Offset = t->Start;
        hit.Length = t->End - t->Start;
        hitFn.collect(hit);
        return true;
      }
    }
    ++offset;
    active.swap(next);
    next.clear();
  }
  return false;
}
