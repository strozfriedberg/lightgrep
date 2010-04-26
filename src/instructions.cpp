#include "instructions.h"

#include <stdexcept>

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
