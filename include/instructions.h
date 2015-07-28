/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "basic.h"

#include <iosfwd>

enum OpCodes {
  JUMP_TABLE_RANGE_OP = 0,
  BYTE_OP,
  BIT_VECTOR_OP,
  EITHER_OP,
  RANGE_OP,
  ANY_OP,
  FINISH_OP,
  FORK_OP,
  JUMP_OP,
  CHECK_HALT_OP,
  LABEL_OP,
  MATCH_OP,
  HALT_OP,
  ADJUST_START_OP
};

template<int OPCODE> struct InstructionSize { enum { VAL = 1 }; };

template<> struct InstructionSize<BIT_VECTOR_OP> { enum { VAL = 9 }; };
template<> struct InstructionSize<FORK_OP> { enum { VAL = 2 }; };
template<> struct InstructionSize<JUMP_OP> { enum { VAL = 2 }; };

#pragma pack(push, 1)
struct InstructionType1 {
  byte Flags;
  byte Byte;
};

struct InstructionType2 {
  byte Flags;
  byte First, Last;
};

union Operand {
  unsigned  Offset : 24;

  InstructionType1 T1;
  InstructionType2 T2;
};

struct Instruction {
  enum Flags {
    NEGATE       = 1 << 0,
    HALT_ON_FAIL = 1 << 1
  };

  unsigned char OpCode;
  Operand  Op;

  Instruction(): OpCode(HALT_OP) { Op.Offset = 0; }

  byte wordSize() const {
    switch (OpCode) {
    case BIT_VECTOR_OP:
      return InstructionSize<BIT_VECTOR_OP>::VAL;
    case FORK_OP:
    case JUMP_OP:
      return InstructionSize<FORK_OP>::VAL;
    default:
      return InstructionSize<HALT_OP>::VAL;
    }
  }

  byte byteSize() const { return sizeof(Instruction) * wordSize(); }

  std::string toString() const;

  bool operator==(const Instruction& x) const {
    // total hack
    return *reinterpret_cast<const uint32_t*>(this) ==
           *reinterpret_cast<const uint32_t*>(&x);
  }

  static Instruction makeByte(byte b, bool negate = false);
  static Instruction makeEither(byte one, byte two, bool negate = false);
  static Instruction makeRange(byte first, byte last, bool negate = false);
  static Instruction makeAny();
  static Instruction makeBitVector();
  static Instruction makeJump(Instruction* ptr, uint32_t offset);
  static Instruction makeJumpTableRange(byte first, byte last);
  static Instruction makeLabel(uint32_t label);
  static Instruction makeMatch();
  static Instruction makeFork(Instruction* ptr, uint32_t offset);
  static Instruction makeCheckHalt(uint32_t checkIndex);
  static Instruction makeAdjustStart(uint32_t offset);
  static Instruction makeHalt();
  static Instruction makeFinish();
  static Instruction makeRaw32(uint32_t val);
  static Instruction makeRaw24(uint32_t val);
};
#pragma pack(pop)

std::ostream& operator<<(std::ostream& out, const Instruction& instr);
std::istream& operator>>(std::istream& in, Instruction& instr);
