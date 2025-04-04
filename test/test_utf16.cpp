/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <catch2/catch_test_macros.hpp>

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
