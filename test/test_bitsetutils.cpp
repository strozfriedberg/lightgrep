#include <scope/test.h>

#include "basic.h"
#include "bitsetutils.h"

SCOPE_TEST(byteSetLexOrder) {
  // Our usage of memcmp assumes that ByteSet is laid out as a byte[32].
  SCOPE_ASSERT_EQUAL(32, sizeof(ByteSet));

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
