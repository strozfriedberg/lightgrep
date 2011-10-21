#include "states.h"

#include "instructions.h"

#include <cctype>
#include <iomanip>
#include <sstream>

void printByte(std::ostream& out, byte b) {
  if (std::isgraph(b)) {
    out << (char) b;
  }
  else {
    out << "\\x" << std::setfill('0') << std::setw(2)
        << std::hex << std::uppercase << (uint32) b << std::dec;
  }
}

void printRange(std::ostream& out, byte beg, byte end) {
  printByte(out, beg);

  if (end - beg > 1) {
    out << '-';
  }

  if (end != beg) {
    printByte(out, end);
  }
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
  printByte(buf, Lit);
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
  printByte(buf, Lit1);
  printByte(buf, Lit2);
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
  printRange(buf, First, Last);
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

  int32 beg = -1, end;

  for (uint32 i = 0; i < 256; ++i) {
    if (Allowed.test(i)) {
      if (beg == -1) {
        beg = i;
      }

      end = i;
    }
    else if (beg != -1) {
      printRange(ss, beg, end);
      beg = -1;
    }
  }

  if (beg != -1) {
    printRange(ss, beg, end);
  }

  return ss.str() + printLabel(*this);
}
