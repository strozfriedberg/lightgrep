
#include <scope/test.h>

#include "instructions.h"

#include <stdexcept>

SCOPE_TEST(instructionSizes) {
  SCOPE_ASSERT_EQUAL(4u, sizeof(Instruction));

  Instruction i;
  i.Size = 0;
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL(4u, i.byteSize());
  i.Size = 1;
  SCOPE_ASSERT_EQUAL(2u, i.wordSize());
  SCOPE_ASSERT_EQUAL(8u, i.byteSize());
  i.Size = 2;
  SCOPE_ASSERT_EQUAL(5u, i.wordSize());
  SCOPE_ASSERT_EQUAL(20u, i.byteSize());
  i.Size = 3;
  SCOPE_ASSERT_EQUAL(9u, i.wordSize());
  SCOPE_ASSERT_EQUAL(36u, i.byteSize());
}

SCOPE_TEST(makeLit) {
  Instruction i = Instruction::makeLit('a');
  SCOPE_ASSERT_EQUAL(LIT_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL('a', i.Op.Literal);
}

SCOPE_TEST(makeJump) {
  Instruction i = Instruction::makeJump(5);
  SCOPE_ASSERT_EQUAL(JUMP_OP, i.OpCode);
  SCOPE_ASSERT_EQUAL(1u, i.wordSize());
  SCOPE_ASSERT_EQUAL(5u, i.Op.Offset);
  SCOPE_EXPECT(Instruction::makeJump(1 << 24), std::overflow_error);
}
