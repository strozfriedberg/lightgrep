/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <scope/test.h>

#include "container_out.h"
#include "encoders/utf32.h"

template <bool LE>
void utf32TestFixture(const UTF32Base<LE>& enc) {
  SCOPE_ASSERT_EQUAL(4u, enc.maxByteLength());

  byte buf[4];
  uint32_t val;
  uint32_t len;

  // too low
  SCOPE_ASSERT_EQUAL(0u, enc.write(-1, buf));

  // low, valid
  for (uint32_t i = 0; i < 0xD800; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32_t) buf[LE ? 1 : 2]) <<  8) |
          (((uint32_t) buf[LE ? 2 : 1]) << 16) |
          (((uint32_t) buf[LE ? 3 : 0]) << 24);

    SCOPE_ASSERT_EQUAL(4u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // UTF-16 surrogates, invalid
  for (uint32_t i = 0xD800; i < 0xE000; ++i) {
    SCOPE_ASSERT_EQUAL(0u, enc.write(i, buf));
  }

  // high, valid
  for (uint32_t i = 0xE000; i < 0x110000; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32_t) buf[LE ? 1 : 2]) <<  8) |
          (((uint32_t) buf[LE ? 2 : 1]) << 16) |
          (((uint32_t) buf[LE ? 3 : 0]) << 24);

    SCOPE_ASSERT_EQUAL(4u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0u, enc.write(0x110000, buf));
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

