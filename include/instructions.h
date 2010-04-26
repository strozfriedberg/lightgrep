#pragma once

#include "basic.h"

#pragma pack(1)
struct ByteRange {
  byte First, Last;
};

union Operand {
  unsigned  Offset : 24;
  ByteRange Range;
  byte      Literal;
};

enum OpCodes {
  LIT_OP,
  JUMP_OP,
  MATCH_OP
};

struct Instruction {
  unsigned OpCode : 6;
  unsigned Size   : 2;
  Operand  Op;

  byte wordSize() const {
    switch (Size) {
      case 1:
        return 2; // 4 bytes of data after this instruction
      case 2:
        return 5; // 16 bytes of data after this instruction
      case 3:
        return 9; // 32 bytes of data after this instruction
      default:
        return 1; // no additional data after this instruction
    }
  }

  byte byteSize() const { return sizeof(Instruction) * wordSize(); }

  static Instruction makeLit(byte b);
  static Instruction makeJump(uint32 relativeOffset);
  static Instruction makeMatch();
};
#pragma pack(pop)
