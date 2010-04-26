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

struct Instruction {
  unsigned OpCode : 6;
  unsigned Size   : 2;
  Operand  Op;
};
#pragma pack(pop)
