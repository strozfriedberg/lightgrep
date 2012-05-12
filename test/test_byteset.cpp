#include <scope/test.h>

#include "basic.h"
#include "byteset.h"

#include <iostream>

SCOPE_TEST(byteSetSizeTest) {
  // Our usage of memcmp assumes that ByteSet is laid out as a byte[32].
  SCOPE_ASSERT_EQUAL(32, sizeof(ByteSet));
}

SCOPE_TEST(byteSetDWordComparisionTest) {
  // This tests that we are getting comparision per dword, instead of a
  // lexicographical order. It's not essential that this be the case, but
  // we want to know if there's an unexpected change.
  ByteSet a(1), b(2);
  SCOPE_ASSERT(a < b);
}

SCOPE_TEST(fastByteSetOrderTest) {
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

SCOPE_TEST(byteSetRangeSetTest) {
  ByteSet a, b;

  // set true ranges on false bits
  for (uint32 i = 0; i <= 256; ++i) {
    for (uint32 j = i; j <= 256; ++j) {
      // do a range set
      a.reset();
      a.set(i, j, true);

      // do a standard, one-at-a-time set
      b.reset();
      for (uint32 k = i; k < j; ++k) {
        b.set(k, true);
      }

      SCOPE_ASSERT_EQUAL(b, a);
    }
  }

  // set false ranges on true bits
  for (uint32 i = 0; i <= 256; ++i) {
    for (uint32 j = i; j <= 256; ++j) {
      // do a range set
      a.reset().flip();
      a.set(i, j, false);

      // do a standard, one-at-a-time set
      b.reset().flip();
      for (uint32 k = i; k < j; ++k) {
        b.set(k, false);
      }

      SCOPE_ASSERT_EQUAL(b, a);
    }
  }
}
