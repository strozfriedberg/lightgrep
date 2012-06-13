#include <scope/test.h>

#include "ascii.h"

SCOPE_TEST(testASCII) {
  ASCII enc;
  SCOPE_ASSERT_EQUAL(1u, enc.maxByteLength());

  byte buf[1];
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0, enc.write(-1, buf));

  // just right
  for (uint32 i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0, enc.write(0x80, buf));
}
