#include "states.h"

#include "instructions.h"

#include <sstream>
#include <cctype>
#include <iomanip>

void printHex(std::ostream& out, byte b) {
  out << "0x" << std::setfill('0') << std::setw(2) << std::hex
      << (uint32)b << std::dec;
}

bool   LitState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeLit(Lit);
  return true;
}

LitState* LitState::clone(void* buffer) const {
  return buffer == 0 ? new LitState(Lit): new(buffer) LitState(Lit);
}

std::string printLabel(const Transition& t) {
  std::stringstream buf;
  if (t.Label != 0xffffffff) {
    buf << "/" << t.Label;
  }
  return buf.str();
}

std::string LitState::label() const {
  std::stringstream buf;
  if (std::isgraph(Lit)) {
    buf << Lit;
  }
  else {
    printHex(buf, Lit);
  }
  buf << printLabel(*this);
  return buf.str();
}

bool   EitherState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeEither(Lit1, Lit2);
  return true;
}

EitherState* EitherState::clone(void* buffer) const {
  return buffer == 0 ? new EitherState(Lit1, Lit2): new(buffer) EitherState(Lit1, Lit2);
}

std::string EitherState::label() const {
  std::stringstream buf;
  if (std::isgraph(Lit1)) {
    buf << Lit1;
  }
  else {
    printHex(buf, Lit1);
  }
  if (std::isgraph(Lit2)) {
    buf << Lit2;
  }
  else {
    printHex(buf, Lit2);
  }
  buf << printLabel(*this);
  return buf.str();
}

bool   RangeState::toInstruction(Instruction* addr) const {
  *addr = (First == 0 && Last == 255) ? Instruction::makeAny(): Instruction::makeRange(First, Last);
  return true;
}

RangeState* RangeState::clone(void* buffer) const {
  return 0 == buffer ? new RangeState(First, Last): new(buffer) RangeState(First, Last);
}

std::string RangeState::label() const {
  std::stringstream buf;
  if (std::isgraph(First)) {
    buf << First;
  }
  else {
    printHex(buf, First);
  }
  buf << '-';
  if (std::isgraph(First)) {
    buf << Last;
  }
  else {
    printHex(buf, Last);
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

CharClassState* CharClassState::clone(void* buffer) const {
  return 0 == buffer ? new CharClassState(Allowed, Label): new(buffer) CharClassState(Allowed, Label);
}

std::string CharClassState::label() const {
  // std::stringstream buf;
  // for (uint32 i = 0; i < 8; ++i) {
  //   buf << std::hex << std::setfill('0') << std::setw(8) << *((uint32*)(&Allowed)+i);
  // }
  // return buf.str();
  return Label + printLabel(*this);
}
