/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#include "catch.hpp"

#include "container_out.h"
#include "encoders/utf32.h"

template <bool LE>
void utf32TestFixture(const UTF32Base<LE>& enc) {
  REQUIRE(4u == enc.maxByteLength());

  byte buf[4];
  uint32_t val;
  uint32_t len;

  // too low
  REQUIRE(0u == enc.write(-1, buf));

  // low, valid
  for (uint32_t i = 0; i < 0xD800; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32_t) buf[LE ? 1 : 2]) <<  8) |
          (((uint32_t) buf[LE ? 2 : 1]) << 16) |
          (((uint32_t) buf[LE ? 3 : 0]) << 24);

    REQUIRE(4u == len);
    REQUIRE(i == val);
  }

  // UTF-16 surrogates, invalid
  for (uint32_t i = 0xD800; i < 0xE000; ++i) {
    REQUIRE(0u == enc.write(i, buf));
  }

  // high, valid
  for (uint32_t i = 0xE000; i < 0x110000; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32_t) buf[LE ? 1 : 2]) <<  8) |
          (((uint32_t) buf[LE ? 2 : 1]) << 16) |
          (((uint32_t) buf[LE ? 3 : 0]) << 24);

    REQUIRE(4u == len);
    REQUIRE(i == val);
  }

  // too high
  REQUIRE(0u == enc.write(0x110000, buf));
}

TEST_CASE("testUTF32LE") {
  UTF32LE enc;
  utf32TestFixture(enc);
}

TEST_CASE("testUTF32BE") {
  UTF32BE enc;
  utf32TestFixture(enc);
}

TEST_CASE("testUTF32LERangeFull") {
  UTF32LE enc;

  UnicodeSet us{{0, 0x110000}};

  // all valid UTF-32LE ranges
  std::vector<std::vector<ByteSet>> e{
    { {{0x00,0x100}}, {{0xD8,0xE0}}, {{0x01,0x11}}, 0x00 },
    { {{0x00,0x100}}, {{0x00,0xD8},{0xE0,0x100}}, {{0x00,0x11}}, 0x00 }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

TEST_CASE("testUTF32BERangeFull") {
  UTF32BE enc;

  UnicodeSet us{{0, 0x110000}};

  // all valid UTF-32BE ranges
  std::vector<std::vector<ByteSet>> e{
    { 0x00, 0x00, {{0x00,0xD8},{0xE0,0x100}}, {{0x00,0x100}} },
    { 0x00, {{0x01,0x11}}, {{0x00,0x100}}, {{0x00,0x100}} }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

