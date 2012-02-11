#include <scope/test.h>

#include "byteset.h"

SCOPE_TEST(byteSetSize) {
  // Our usage of memcmp assumes that ByteSet is laid out as a byte[32].
  SCOPE_ASSERT_EQUAL(32, sizeof(ByteSet));
}

SCOPE_TEST(byteSetDWordComparision) {
  // This tests that we are getting comparision per dword, instead of a
  // lexicographical order. It's not essential that this be the case, but
  // we want to know if there's an unexpected change.
  ByteSet a(1), b(2);
  SCOPE_ASSERT(a < b);
}

SCOPE_TEST(fastByteSetOrder) {
  SCOPE_ASSERT(ByteSet(0xFE) < ByteSet(0xFF));

  ByteSet none(0), test(1), all;
  all.flip();

  do {
    SCOPE_ASSERT(none < test);
    SCOPE_ASSERT(!(test < none));
    SCOPE_ASSERT(test < all);
    SCOPE_ASSERT(!(all < test));
    SCOPE_ASSERT(!(test < test));
  } while ((test <<= 1).any());
}
