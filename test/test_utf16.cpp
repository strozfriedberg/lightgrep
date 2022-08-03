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

#include <catch2/catch_test_macros.hpp>

#include "container_out.h"
#include "encoders/utf16.h"

template <bool LE>
void utf16TestFixture(const UTF16Base<LE>& enc) {
  REQUIRE(4u == enc.maxByteLength());

  byte buf[4];
  uint32_t val;
  uint32_t len;

  // too low
  REQUIRE(0u == enc.write(-1, buf));

  // low direct representations
  for (uint32_t i = 0; i < 0xD800; ++i) {
    len = enc.write(i, buf);
    val = buf[LE ? 1 : 0];
    val <<= 8;
    val += buf[LE ? 0 : 1];
    REQUIRE(2u == len);
    REQUIRE(i == val);
  }

  // UTF-16 surrogates, invalid
  for (uint32_t i = 0xD800; i < 0xE000; ++i) {
    REQUIRE(0u == enc.write(i, buf));
  }

  // high direct representations
  for (uint32_t i = 0xE000; i < 0x10000; ++i) {
    len = enc.write(i, buf);
    val = buf[LE ? 1 : 0];
    val <<= 8;
    val += buf[LE ? 0 : 1];
    REQUIRE(2u == len);
    REQUIRE(i == val);
  }

  uint32_t lead, trail;

  // surrogate pair representations
  for (uint32_t i = 0x10000; i < 0x110000; ++i) {
    len = enc.write(i, buf);

    lead = buf[LE ? 0 : 1] | (((uint16_t) buf[LE ? 1 : 0]) << 8);
    trail = buf[LE ? 2 : 3] | (((uint16_t) buf[LE ? 3 : 2]) << 8);

    val = (lead << 10) + trail + 0x10000 - (0xD800 << 10) - 0xDC00;

    REQUIRE(4u == len);
    REQUIRE(i == val);
  }

  // too high
  REQUIRE(0u == enc.write(0x110000, buf));
}

TEST_CASE("testUTF16LE") {
  UTF16LE enc;
  utf16TestFixture(enc);
}

TEST_CASE("testUTF16BE") {
  UTF16BE enc;
  utf16TestFixture(enc);
}

TEST_CASE("testUTF16LERangeFull") {
  UTF16LE enc;

  UnicodeSet us{{0, 0x110000}};

  // all valid UTF-16LE ranges
  std::vector<std::vector<ByteSet>> e{
    { {{0x00,0x100}}, {{0x00,0xD8}, {0xE0,0x100}} },
    { {{0x00,0x100}}, {{0xD8,0xDC}}, {{0x00,0x100}}, {{0xDC,0xE0}} }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

TEST_CASE("testUTF16BERangeFull") {
  UTF16BE enc;

  UnicodeSet us{{0, 0x110000}};

  // all valid UTF-16BE ranges
  std::vector<std::vector<ByteSet>> e{
    { {{0x00,0xD8}, {0xE0,0x100}}, {{0x00,0x100}} },
    { {{0xD8,0xDC}}, {{0x00,0x100}}, {{0xDC,0xE0}}, {{0x00,0x100}} }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}
