#include <scope/test.h>

#include "concrete_encodings.h"

SCOPE_TEST(testASCII) {
  ASCII a;
  SCOPE_ASSERT_EQUAL(1u, a.maxByteLength());
  byte buf[1];
  uint32 len;
  for (uint32 i = 0; i < 300; ++i) {
    len = a.write(i, buf);
    if (i < 256) {
      SCOPE_ASSERT_EQUAL(1u, len);
      SCOPE_ASSERT_EQUAL(i, buf[0]);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, len);
      SCOPE_ASSERT_EQUAL(255, buf[0]); // doesn't modify buffer
    }
  }
}

SCOPE_TEST(testUTF8) {
  UTF8 enc;

  SCOPE_ASSERT_EQUAL(4, enc.maxByteLength());

/*
  byte buf[4];
  uint32 len;
  for (uint32 i = 0; i < 0x110000; ++i) {
    len = enc.write(i, buf);
  }
*/  
}

SCOPE_TEST(testUTF16) {
  UTF16 twofer;
  SCOPE_ASSERT_EQUAL(2u, twofer.maxByteLength());
  byte buf[2];
  unsigned short val;
  uint32 len;
  for (uint32 i = 0; i < 70000; ++i) {
    len = twofer.write(i, buf);
    val = buf[1];
    val <<= 8;
    val += buf[0];
    if (i < 65536) {
      SCOPE_ASSERT_EQUAL(2u, len);
      SCOPE_ASSERT_EQUAL(i, val);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, len);
      SCOPE_ASSERT_EQUAL(65535, val);
    }
  }
  twofer.write(-1, buf);
  val = buf[1];
  val <<= 8;
  val += buf[0];
  SCOPE_ASSERT_EQUAL(0u, len);
  SCOPE_ASSERT_EQUAL(65535, val);
}

