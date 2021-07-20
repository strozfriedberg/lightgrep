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

#include "catch.hpp"

#include "instructions.h"
#include "byteset.h"

#include <stdexcept>

TEST_CASE("makeByte") {
  Instruction i = Instruction::makeByte('a');
  REQUIRE(BYTE_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE('a' == i.Op.T1.Byte);
  REQUIRE((!i.Op.T1.Flags) & Instruction::NEGATE);
  REQUIRE("Byte 0x61/'a'" == i.toString());
}

TEST_CASE("makeNotByte") {
  Instruction i = Instruction::makeByte('a', true);
  REQUIRE(BYTE_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE('a' == i.Op.T1.Byte);
  REQUIRE(i.Op.T1.Flags & Instruction::NEGATE);
  REQUIRE("Byte not 0x61/'a'" == i.toString());
}

TEST_CASE("makeJump") {
  Instruction i[2];
  i[0] = Instruction::makeJump(i, 16777216);
  REQUIRE(JUMP_OP == i[0].OpCode);
  REQUIRE(2u == i[0].wordSize());
  REQUIRE(0u == i[0].Op.Offset);
  REQUIRE(16777216u == *reinterpret_cast<uint32_t*>(i+1));
  REQUIRE("Jump 0x01000000/16777216" == i[0].toString());
}

TEST_CASE("makeMatch") {
  Instruction i = Instruction::makeMatch();
  REQUIRE(MATCH_OP == i.OpCode);
  REQUIRE(0u == i.Op.Offset);
  REQUIRE(1u == i.wordSize());
  REQUIRE("Match" == i.toString());
}

TEST_CASE("makeLabel") {
  Instruction i = Instruction::makeLabel(8);
  REQUIRE(LABEL_OP == i.OpCode);
  REQUIRE(8u == i.Op.Offset);
  REQUIRE(1u == i.wordSize());
  REQUIRE("Label 8" == i.toString());
}

TEST_CASE("makeEither") {
  Instruction i = Instruction::makeEither('a', 'B');
  REQUIRE(EITHER_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE('a' == i.Op.T2.First);
  REQUIRE('B' == i.Op.T2.Last);
  REQUIRE((!i.Op.T2.Flags) & Instruction::NEGATE);
  REQUIRE("Either 0x61/'a', 0x42/'B'" == i.toString());
}

TEST_CASE("makeNeither") {
  Instruction i = Instruction::makeEither('a', 'B', true);
  REQUIRE(EITHER_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE('a' == i.Op.T2.First);
  REQUIRE('B' == i.Op.T2.Last);
  REQUIRE(i.Op.T2.Flags & Instruction::NEGATE);
  REQUIRE("Either not 0x61/'a', 0x42/'B'" == i.toString());
}

TEST_CASE("makeRange") {
  Instruction i = Instruction::makeRange('A', 'Z');
  REQUIRE(RANGE_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE('A' == i.Op.T2.First);
  REQUIRE('Z' == i.Op.T2.Last);
  REQUIRE((!i.Op.T2.Flags) & Instruction::NEGATE);
  REQUIRE("Range 0x41/'A'-0x5a/'Z'" == i.toString());
  REQUIRE_THROWS_AS(Instruction::makeRange('Z', 'A'), std::range_error);
}

TEST_CASE("makeNotRange") {
  Instruction i = Instruction::makeRange('A', 'Z', true);
  REQUIRE(RANGE_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE('A' == i.Op.T2.First);
  REQUIRE('Z' == i.Op.T2.Last);
  REQUIRE(i.Op.T2.Flags & Instruction::NEGATE);
  REQUIRE("Range not 0x41/'A'-0x5a/'Z'" == i.toString());
  REQUIRE_THROWS_AS(Instruction::makeRange('Z', 'A', true), std::range_error);
}

TEST_CASE("makeBitVector") {
  Instruction i = Instruction::makeBitVector();
  REQUIRE(BIT_VECTOR_OP == i.OpCode);
  REQUIRE(9u == i.wordSize());
  REQUIRE("BitVector" == i.toString());
  REQUIRE(32u == sizeof(ByteSet));
}

TEST_CASE("makeFork") {
  Instruction i[2];
  i[0] = Instruction::makeFork(i, 16777216);
  REQUIRE(FORK_OP == i[0].OpCode);
  REQUIRE(2u == i[0].wordSize());
  REQUIRE(0u == i[0].Op.Offset);
  REQUIRE(16777216u == *reinterpret_cast<uint32_t*>(i+1));
  REQUIRE("Fork 0x01000000/16777216" == i[0].toString());
}

TEST_CASE("makeHalt") {
  Instruction i = Instruction::makeHalt();
  REQUIRE(HALT_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE(0u == i.Op.Offset);
  REQUIRE("Halt" == i.toString());
}

TEST_CASE("makeJumpTableRange") {
  Instruction i = Instruction::makeJumpTableRange(33, 45);
  REQUIRE(JUMP_TABLE_RANGE_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE(33u == i.Op.T2.First);
  REQUIRE(45u == i.Op.T2.Last);
  REQUIRE("JmpTblRange 0x21/'!'-0x2d/'-'" == i.toString());
  REQUIRE_THROWS_AS(Instruction::makeJumpTableRange(1, 0), std::range_error);
}

TEST_CASE("makeAny") {
  Instruction i = Instruction::makeAny();
  REQUIRE(ANY_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE(0u == i.Op.Offset);
  REQUIRE("Any" == i.toString());
}

TEST_CASE("makeAdjustStart") {
  Instruction i = Instruction::makeAdjustStart(4);
  REQUIRE(ADJUST_START_OP == i.OpCode);
  REQUIRE(1u == i.wordSize());
  REQUIRE(4u == i.Op.Offset);
  REQUIRE("AdjustStart -4" == i.toString());
}
