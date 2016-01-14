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

#include <scope/test.h>

#include "instructions.h"
#include "byteset.h"

#include <stdexcept>

SCOPE_TEST(makeByte) {
  Instruction i = Instruction::makeByte('a');
  SCOPE_ASSERT_EQUAL(BYTE_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('a', i.Op.T1.Byte);
  SCOPE_ASSERT((!i.Op.T1.Flags) & Instruction::NEGATE);
  SCOPE_ASSERT_EQUAL("Byte 0x61/'a'", i.toString());
}

SCOPE_TEST(makeNotByte) {
  Instruction i = Instruction::makeByte('a', true);
  SCOPE_ASSERT_EQUAL(BYTE_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('a', i.Op.T1.Byte);
  SCOPE_ASSERT(i.Op.T1.Flags & Instruction::NEGATE);
  SCOPE_ASSERT_EQUAL("Byte not 0x61/'a'", i.toString());
}

SCOPE_TEST(makeJump) {
  Instruction i[2];
  i[0] = Instruction::makeJump(i, 16777216);
  SCOPE_ASSERT_EQUAL(JUMP_OP, i[0].OpCode);
  SCOPE_ASSERT_EQUAL(2u, i[0].wordSize());
  SCOPE_ASSERT_EQUAL(0u, i[0].Op.Offset);
  SCOPE_ASSERT_EQUAL(16777216u, *reinterpret_cast<uint32_t*>(i+1));
  SCOPE_ASSERT_EQUAL("Jump 0x01000000/16777216", i[0].toString());
}

SCOPE_TEST(makeMatch) {
  Instruction i = Instruction::makeMatch();
  SCOPE_ASSERT_EQUAL(MATCH_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(0u, i.Op.Offset);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL("Match", i.toString());
}

SCOPE_TEST(makeLabel) {
  Instruction i = Instruction::makeLabel(8);
  SCOPE_ASSERT_EQUAL(LABEL_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(8u, i.Op.Offset);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL("Label 8", i.toString());
}

SCOPE_TEST(makeEither) {
  Instruction i = Instruction::makeEither('a', 'B');
  SCOPE_ASSERT_EQUAL(EITHER_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('a', i.Op.T2.First);
  SCOPE_ASSERT_EQUAL('B', i.Op.T2.Last);
  SCOPE_ASSERT((!i.Op.T2.Flags) & Instruction::NEGATE);
  SCOPE_ASSERT_EQUAL("Either 0x61/'a', 0x42/'B'", i.toString());
}

SCOPE_TEST(makeNeither) {
  Instruction i = Instruction::makeEither('a', 'B', true);
  SCOPE_ASSERT_EQUAL(EITHER_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('a', i.Op.T2.First);
  SCOPE_ASSERT_EQUAL('B', i.Op.T2.Last);
  SCOPE_ASSERT(i.Op.T2.Flags & Instruction::NEGATE);
  SCOPE_ASSERT_EQUAL("Either not 0x61/'a', 0x42/'B'", i.toString());
}

SCOPE_TEST(makeRange) {
  Instruction i = Instruction::makeRange('A', 'Z');
  SCOPE_ASSERT_EQUAL(RANGE_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('A', i.Op.T2.First);
  SCOPE_ASSERT_EQUAL('Z', i.Op.T2.Last);
  SCOPE_ASSERT((!i.Op.T2.Flags) & Instruction::NEGATE);
  SCOPE_ASSERT_EQUAL("Range 0x41/'A'-0x5a/'Z'", i.toString());
  SCOPE_EXPECT(Instruction::makeRange('Z', 'A'), std::range_error);
}

SCOPE_TEST(makeNotRange) {
  Instruction i = Instruction::makeRange('A', 'Z', true);
  SCOPE_ASSERT_EQUAL(RANGE_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('A', i.Op.T2.First);
  SCOPE_ASSERT_EQUAL('Z', i.Op.T2.Last);
  SCOPE_ASSERT(i.Op.T2.Flags & Instruction::NEGATE);
  SCOPE_ASSERT_EQUAL("Range not 0x41/'A'-0x5a/'Z'", i.toString());
  SCOPE_EXPECT(Instruction::makeRange('Z', 'A', true), std::range_error);
}

SCOPE_TEST(makeBitVector) {
  Instruction i = Instruction::makeBitVector();
  SCOPE_ASSERT_EQUAL(BIT_VECTOR_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(9u, i.wordSize());
  SCOPE_ASSERT_EQUAL("BitVector", i.toString());
  SCOPE_ASSERT_EQUAL(32u, sizeof(ByteSet));
}

SCOPE_TEST(makeFork) {
  Instruction i[2];
  i[0] = Instruction::makeFork(i, 16777216);
  SCOPE_ASSERT_EQUAL(FORK_OP, i[0].OpCode);
  SCOPE_ASSERT_EQUAL(2u, i[0].wordSize());
  SCOPE_ASSERT_EQUAL(0u, i[0].Op.Offset);
  SCOPE_ASSERT_EQUAL(16777216u, *reinterpret_cast<uint32_t*>(i+1));
  SCOPE_ASSERT_EQUAL("Fork 0x01000000/16777216", i[0].toString());
}

SCOPE_TEST(makeHalt) {
  Instruction i = Instruction::makeHalt();
  SCOPE_ASSERT_EQUAL(HALT_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL(0u, i.Op.Offset);
  SCOPE_ASSERT_EQUAL("Halt", i.toString());
}

SCOPE_TEST(makeJumpTableRange) {
  Instruction i = Instruction::makeJumpTableRange(33, 45);
  SCOPE_ASSERT_EQUAL(JUMP_TABLE_RANGE_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL(33u, i.Op.T2.First);
  SCOPE_ASSERT_EQUAL(45u, i.Op.T2.Last);
  SCOPE_ASSERT_EQUAL("JmpTblRange 0x21/'!'-0x2d/'-'", i.toString());
  SCOPE_EXPECT(Instruction::makeJumpTableRange(1, 0), std::range_error);
}

SCOPE_TEST(makeAny) {
  Instruction i = Instruction::makeAny();
  SCOPE_ASSERT_EQUAL(ANY_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL(0u, i.Op.Offset);
  SCOPE_ASSERT_EQUAL("Any", i.toString());
}

SCOPE_TEST(makeAdjustStart) {
  Instruction i = Instruction::makeAdjustStart(4);
  SCOPE_ASSERT_EQUAL(ADJUST_START_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL(4u, i.Op.Offset);
  SCOPE_ASSERT_EQUAL("AdjustStart -4", i.toString());
}
