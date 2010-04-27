#include "instructions.h"

#include <stdexcept>
#include <iomanip>

std::string Instruction::toString() const {
  std::stringstream buf;
  switch (OpCode) {
    case LIT_OP:
      buf << "Literal 0x" << std::hex << (unsigned short)Op.Literal << "/'" << Op.Literal << '\'';
      break;
    case JUMP_OP:
      buf << "Jump 0x" << std::hex << std::setfill('0') << std::setw(8) << Op.Offset << '/' << std::dec << Op.Offset;
      break;
    case MATCH_OP:
      buf << "Match";
      break;
    case SAVE_LABEL_OP:
      buf << "SaveLabel " << Op.Offset;
      break;
    default:
      buf << "* UNRECOGNIZED *";
  };
  return buf.str();
}

Instruction Instruction::makeLit(byte b) {
  Instruction i;
  i.OpCode = LIT_OP;
  i.Size = 0;
  i.Op.Literal = b;
  return i;
}

Instruction Instruction::makeJump(uint32 relativeOffset) {
  // we should have a two-word version for if relativeOffset >= 2^24
  // for now, we'll just throw a runtime error
  if (relativeOffset >= (1 << 24)) {
    THROW_WITH_OUTPUT(std::overflow_error, "jump offsets are 24 bit; specified offset was " << relativeOffset);
  }
  Instruction i;
  i.OpCode = JUMP_OP;
  i.Size = 0;
  i.Op.Offset = relativeOffset;
  return i;
}

Instruction Instruction::makeMatch() {
  Instruction i;
  i.OpCode = MATCH_OP;
  i.Size = 0;
  return i;
}

Instruction Instruction::makeSaveLabel(uint32 label) {
  Instruction i = makeJump(label);
  i.OpCode = SAVE_LABEL_OP;
  return i;
}
