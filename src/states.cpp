#include "states.h"

#include "instructions.h"

#include <sstream>
#include <cctype>
#include <iomanip>

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
  std::stringstream buf;
  if (std::isalnum(Lit1)) {
    buf << Lit1;
  }
  else {
    buf << (uint32)Lit1;
  }
  if (std::isalnum(Lit2)) {
    buf << Lit2;
  }
  else {
    buf << (uint32)Lit2;
  }
  buf << printLabel(*this);
  return buf.str();
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

bool   CharClassState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeBitVector();
  ByteSet* setPtr = reinterpret_cast<ByteSet*>(addr+1);
  *setPtr = Allowed;
  return true;
}

std::string CharClassState::label() const {
  std::stringstream buf;
  for (uint32 i = 0; i < 8; ++i) {
    buf << std::hex << std::setfill('0') << std::setw(8) << *((uint32*)(&Allowed)+i);
  }
  return buf.str();
}
