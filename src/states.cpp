#include "states.h"

#include "instructions.h"

bool   LitState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeLit(Lit);
  return true;
}

std::string LitState::label() const {
  std::string ret;
  ret += Lit;
  return ret;
}

bool   EitherState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeEither(Lit1, Lit2);
  return true;
}

std::string EitherState::label() const {
  std::string ret;
  ret += '[';
  ret += Lit1;
  ret += Lit2;
  ret += ']';
  return ret;
}

bool   RangeState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeRange(First, Last);
  return true;
}

std::string RangeState::label() const {
  std::string ret;
  ret += '[';
  ret += First;
  ret += '-';
  ret += Last;
  ret += ']';
  return ret;
}
