#include <scope/test.h>

#include "basic.h"

SCOPE_TEST(basicTypeSizes) {
  SCOPE_ASSERT_EQUAL(1u, sizeof(byte));
  SCOPE_ASSERT_EQUAL(4u, sizeof(uint32));
  SCOPE_ASSERT_EQUAL(8u, sizeof(uint64));
  SCOPE_ASSERT_EQUAL(8u, sizeof(int64));
}
