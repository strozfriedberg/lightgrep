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

