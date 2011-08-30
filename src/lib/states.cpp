#include "states.h"

#include "instructions.h"

#include <cctype>
#include <iomanip>
#include <sstream>

void printHex(std::ostream& out, byte b) {
  out << "0x" << std::setfill('0') << std::setw(2)
      << std::hex << std::uppercase << (uint32)b << std::dec;
}

bool LitState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeLit(Lit);
  return true;
}

LitState* LitState::clone(void* buffer) const {
  return buffer == 0 ? new LitState(*this): new(buffer) LitState(*this);
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

bool EitherState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeEither(Lit1, Lit2);
  return true;
}

EitherState* EitherState::clone(void* buffer) const {
  return buffer == 0 ? new EitherState(*this): new(buffer) EitherState(*this);
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

bool RangeState::toInstruction(Instruction* addr) const {
  *addr = (First == 0 && Last == 255) ? Instruction::makeAny(): Instruction::makeRange(First, Last);
  return true;
}

RangeState* RangeState::clone(void* buffer) const {
  return 0 == buffer ? new RangeState(*this): new(buffer) RangeState(*this);
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

bool CharClassState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeBitVector();
  ByteSet* setPtr = reinterpret_cast<ByteSet*>(addr+1);
  *setPtr = Allowed;
  return true;
}

CharClassState* CharClassState::clone(void* buffer) const {
  return 0 == buffer ? new CharClassState(*this): new(buffer) CharClassState(*this);
}

std::string CharClassState::label() const {
  // make the label string
  std::stringstream ss;
  for (uint32 i = 0; i < 256; ++i) {
    if (Allowed.test(i)) {
      if (std::isgraph(i)) {
        ss << (char) i;
      }
      else {
        ss << "\\x" << std::hex << std::uppercase <<
                       std::setfill('0') << std::setw(2) << i;
      }
    }
  }

  return ss.str() + printLabel(*this);
}
