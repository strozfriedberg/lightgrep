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
  UNINITIALIZED = 0,
  LIT_OP,
  EITHER_OP,
  RANGE_OP,
  JUMP_TABLE_OP,
  JUMP_OP,
  FORK_OP,
  CHECK_BRANCH_OP,
  MATCH_OP,
  HALT_OP,
  ILLEGAL
};

struct Instruction {
  signed   OpCode : 6;
  unsigned Size   : 2;
  Operand  Op;

  Instruction(): OpCode(ILLEGAL), Size(0) { Op.Offset = 0; }

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

  std::string toString() const;

  bool operator==(const Instruction& x) const { return *((uint32*)this) == *((uint32*)&x); } // total hack

  static Instruction makeLit(byte b);
  static Instruction makeEither(byte one, byte two);
  static Instruction makeRange(byte first, byte last);
  static Instruction makeJump(uint32 relativeOffset);
  static Instruction makeJumpTable();
  static Instruction makeMatch(uint32 label);
  static Instruction makeFork(uint32 index);
  static Instruction makeCheckBranch(uint32 checkIndex);
  static Instruction makeHalt();
};
#pragma pack(pop)

typedef std::vector<Instruction> Program;
typedef boost::shared_ptr<Program> ProgramPtr;

std::ostream& operator<<(std::ostream& out, const Instruction& instr);
std::ostream& operator<<(std::ostream& out, const Program& prog);