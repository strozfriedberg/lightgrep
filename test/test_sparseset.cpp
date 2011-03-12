#include <scope/test.h>

#include "sparseset.h"

SCOPE_TEST(basicSparseTest) {
  SparseSet s(5);
  SCOPE_ASSERT_EQUAL(0, s.size());
  s.add(3);
  SCOPE_ASSERT_EQUAL(1, s.size());
  SCOPE_ASSERT(s.find(3));
}
