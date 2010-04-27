#include "states.h"

#include "instructions.h"

bool   LitState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeLit(Lit);
  return true;
}

bool   EitherState::toInstruction(Instruction* addr) const {
  *addr = Instruction();
  return true;
}

bool   RangeState::toInstruction(Instruction* addr) const {
  *addr = Instruction();
  return true;
}
