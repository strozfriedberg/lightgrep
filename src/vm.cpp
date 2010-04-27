#include "vm.h"

std::ostream& operator<<(std::ostream& out, const Thread& t) {
  out << "{ \"pc\":" << std::hex << t.PC << ", \"Label\":" << std::dec << t.Label << ", \"Start\":" << t.Start << ", \"End\":"
    << t.End << " }";
  return out;
}

bool Vm::execute(const Instruction* base, const Instruction* pc, Thread& t, ThreadList& next, const byte* cur, uint64 offset) {
  switch (pc->OpCode) {
    case LIT_OP:
      if (*cur == pc->Op.Literal) {
        next.push_back(Thread(pc+1, 0, 0, 0));
        return true;
      }
      else {
        return false;
      }
    case JUMP_OP:
      t.PC = base + pc->Op.Offset;
      return true;
    case MATCH_OP:
      t.End = offset;
  }
  return false;
}
