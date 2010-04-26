
#include <scope/test.h>

#include "instructions.h"

SCOPE_TEST(basicInstructions) {
  SCOPE_ASSERT_EQUAL(4u, sizeof(Instruction));
}
