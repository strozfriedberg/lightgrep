#include "states.h"

#include "instructions.h"

#include <sstream>
#include <cctype>

bool   LitState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeLit(Lit);
  return true;
}

std::string printLabel(const Transition& t) {
  std::stringstream buf;
  if (t.Label != 0xffffffff) {
    buf << "/" << t.Label;
  }
  return buf.str();
}

std::string LitState::label() const {
  std::string ret;
  ret += Lit;
  ret += printLabel(*this);
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
  ret += printLabel(*this);
  return ret;
}

bool   RangeState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeRange(First, Last);
  return true;
}

std::string RangeState::label() const {
  std::stringstream buf;
  if (std::isalnum(First)) {
    buf << First;
  }
  else {
    buf << (uint32)First;
  }
  buf << '-';
  if (std::isalnum(First)) {
    buf << Last;
  }
  else {
    buf << (uint32)Last;
  }
  buf << printLabel(*this);
  return buf.str();
}
