#pragma once

#include "basic.h"

enum OpCodes {
  UNINITIALIZED = 0,
  LIT_OP,
  EITHER_OP,
  RANGE_OP,
  ANY_OP,
  BIT_VECTOR_OP,
  JUMP_TABLE_OP,
  JUMP_TABLE_RANGE_OP,
  JUMP_OP,
  FORK_OP,
  CHECK_HALT_OP,
  LABEL_OP,
  MATCH_OP,
  HALT_OP,
  FINISH_OP,
  ILLEGAL
};

template<int OPCODE>
struct InstructionSize {
  enum {
    VAL = 1
  };
};

template<> struct InstructionSize<BIT_VECTOR_OP> { enum { VAL = 9 }; };
template<> struct InstructionSize<JUMP_OP> { enum { VAL = 2 }; };
template<> struct InstructionSize<FORK_OP> { enum { VAL = 2 }; };

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
  unsigned char OpCode;
  Operand  Op;

  Instruction(): OpCode(ILLEGAL) { Op.Offset = 0; }

  byte wordSize() const {
    switch (OpCode) {
      case BIT_VECTOR_OP:
        return InstructionSize<BIT_VECTOR_OP>::VAL;
      case JUMP_OP:
        return InstructionSize<JUMP_OP>::VAL;
      case FORK_OP:
        return InstructionSize<FORK_OP>::VAL;
      default:
        return InstructionSize<UNINITIALIZED>::VAL;
    }
  }

  byte byteSize() const { return sizeof(Instruction) * wordSize(); }

  std::string toString() const;

  bool operator==(const Instruction& x) const { return *((uint32*)this) == *((uint32*)&x); } // total hack

  static Instruction makeLit(byte b);
  static Instruction makeEither(byte one, byte two);
  static Instruction makeRange(byte first, byte last);
  static Instruction makeAny();
  static Instruction makeBitVector();
  static Instruction makeJump(Instruction* ptr, uint32 offset);
  static Instruction makeJumpTable();
  static Instruction makeJumpTableRange(byte first, byte last);
  static Instruction makeLabel(uint32 label);
  static Instruction makeMatch();
  static Instruction makeFork(Instruction* ptr, uint32 offset);
  static Instruction makeCheckHalt(uint32 checkIndex);
  static Instruction makeHalt();
  static Instruction makeFinish();
  static Instruction makeRaw32(uint32 val);
  static Instruction makeRaw24(uint32 val);
};
#pragma pack()

std::ostream& operator<<(std::ostream& out, const Instruction& instr);
