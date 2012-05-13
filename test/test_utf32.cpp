#include <scope/test.h>

#include "container_out.h"
#include "utf32.h"

template <bool LE>
void utf32TestFixture(const UTF32Base<LE>& enc) {
  SCOPE_ASSERT_EQUAL(4u, enc.maxByteLength());

  byte buf[4];
  uint32 val;
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0, enc.write(-1, buf));

  // low, valid
  for (uint32 i = 0; i < 0xD800; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32) buf[LE ? 1 : 2]) <<  8) |
          (((uint32) buf[LE ? 2 : 1]) << 16) |
          (((uint32) buf[LE ? 3 : 0]) << 24);

    SCOPE_ASSERT_EQUAL(4, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // UTF-16 surrogates, invalid
  for (uint32 i = 0xD800; i < 0xE000; ++i) {
    SCOPE_ASSERT_EQUAL(0, enc.write(i, buf));
  }

  // high, valid
  for (uint32 i = 0xE000; i < 0x110000; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32) buf[LE ? 1 : 2]) <<  8) |
          (((uint32) buf[LE ? 2 : 1]) << 16) |
          (((uint32) buf[LE ? 3 : 0]) << 24);

    SCOPE_ASSERT_EQUAL(4, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0, enc.write(0x110000, buf));
}

SCOPE_TEST(testUTF32LE) {
  UTF32LE enc;
  utf32TestFixture(enc);
}

SCOPE_TEST(testUTF32BE) {
  UTF32BE enc;
  utf32TestFixture(enc);
}

SCOPE_TEST(testUTF32LERangeFull) {
  UTF32LE enc;

  UnicodeSet us{{0, 0x110000}};
  
  // all valid UTF-32LE ranges
  std::vector<std::vector<ByteSet>> e{
    { {{0x00,0x100}}, {{0xD8,0xE0}}, {{0x01,0x11}}, 0x00 },
    { {{0x00,0x100}}, {{0x00,0xD8},{0xE0,0x100}}, {{0x00,0x11}}, 0x00 }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  SCOPE_ASSERT_EQUAL(e, a);
}

SCOPE_TEST(testUTF32BERangeFull) {
  UTF32BE enc;

  UnicodeSet us{{0, 0x110000}};
  
  // all valid UTF-32BE ranges
  std::vector<std::vector<ByteSet>> e{
    { 0x00, 0x00, {{0x00,0xD8},{0xE0,0x100}}, {{0x00,0x100}} },
    { 0x00, {{0x01,0x11}}, {{0x00,0x100}}, {{0x00,0x100}} } 
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  SCOPE_ASSERT_EQUAL(e, a);
}

