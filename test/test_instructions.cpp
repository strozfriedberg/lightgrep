
#include <scope/test.h>

#include "instructions.h"

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
