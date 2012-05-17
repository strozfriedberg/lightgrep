#include "instructions.h"
#include "states.h"

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

bool ByteState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeByte(Byte);
  return true;
}

ByteState* ByteState::clone(void* buffer) const {
  return buffer == 0 ? new ByteState(*this): new(buffer) ByteState(*this);
}

std::string ByteState::label() const {
  std::stringstream buf;
  printByte(buf, Byte);
  return buf.str();
}

bool EitherState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeEither(Byte1, Byte2);
  return true;
}

EitherState* EitherState::clone(void* buffer) const {
  return buffer == 0 ? new EitherState(*this): new(buffer) EitherState(*this);
}

std::string EitherState::label() const {
  std::stringstream buf;
  printByte(buf, Byte1);
  printByte(buf, Byte2);
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
  return buf.str();
}

bool ByteSetState::toInstruction(Instruction* addr) const {
  *addr = Instruction::makeBitVector();
  ByteSet* setPtr = reinterpret_cast<ByteSet*>(addr+1);
  *setPtr = Allowed;
  return true;
}

ByteSetState* ByteSetState::clone(void* buffer) const {
  return 0 == buffer ? new ByteSetState(*this): new(buffer) ByteSetState(*this);
}

std::string ByteSetState::label() const {
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

  return ss.str();
}
