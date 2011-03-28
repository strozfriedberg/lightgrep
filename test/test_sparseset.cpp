#include <scope/test.h>

#include "sparseset.h"

SCOPE_TEST(basicSparseTest) {
  SparseSet s(5);
  SCOPE_ASSERT_EQUAL(0, s.size());
  for (uint32 i = 0; i < 5; ++i) {
    SCOPE_ASSERT(!s.find(i));
  }
  s.insert(3);
  SCOPE_ASSERT_EQUAL(1, s.size());
  SCOPE_ASSERT(s.find(3));
  SCOPE_ASSERT(!s.find(0));
  SCOPE_ASSERT(!s.find(1));
  SCOPE_ASSERT(!s.find(2));
  SCOPE_ASSERT(!s.find(4));
}

SCOPE_TEST(sparseClear) {
  SparseSet s(5);
  SCOPE_ASSERT_EQUAL(0, s.size());
  s.insert(4);
  s.insert(2);
  SCOPE_ASSERT_EQUAL(2, s.size());
  s.clear();
  SCOPE_ASSERT_EQUAL(0, s.size());
  for (uint32 i = 0; i < 5; ++i) {
    SCOPE_ASSERT(!s.find(i));
  }
}
