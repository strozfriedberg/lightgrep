/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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
