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

#include <algorithm>
#include <memory>
#include <vector>
#include <stdexcept>

#include "lightgrep/util.h"

#include "decoders/decoder.h"

void readWindowTest(
  uint64_t doff,
  const char* enc,
  size_t hbeg,
  size_t hend,
  size_t pre,
  size_t post,
  const std::vector<byte>& data,
  const std::vector<int32_t>& ecp,
  const std::vector<size_t>& eoff,
  size_t edhbeg,
  size_t edhend)
{
  const LG_Window inner{doff + hbeg, doff + hend};
  int32_t* chars = nullptr;
  size_t* offsets = nullptr;
  size_t clen;
  LG_Window adh;

  std::unique_ptr<DecoderHandle, void(*)(DecoderHandle*)> hdec{
    lg_create_decoder(),
    lg_destroy_decoder
  };

  LG_Error* err = nullptr;

  const unsigned int abad = lg_read_window(
    hdec.get(),
    reinterpret_cast<const char*>(data.data()),
    reinterpret_cast<const char*>(data.data()) + data.size(),
    doff,
    &inner,
    enc,
    pre,
    post,
    &chars,
    &offsets,
    &clen,
    &adh,
    &err
  );

  if (err) {
    const std::string msg(err->Message);
    lg_free_error(err);
    throw std::runtime_error(msg);
  }

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    chars, &lg_free_window_characters
  );

  std::unique_ptr<size_t[],void(*)(size_t*)> poff(
    offsets, &lg_free_window_offsets
  );

  const size_t ebad = std::count_if(
    ecp.begin(), ecp.end()-1, [](int32_t v){ return v < 0; }
  );

  REQUIRE(ebad == abad);

  std::vector<int32_t> acp(chars, chars+clen);
  REQUIRE(ecp == acp);

  std::vector<size_t> aoff(offsets, offsets+clen);
  REQUIRE(eoff == aoff);

  REQUIRE(edhbeg == adh.begin);
  REQUIRE(edhend == adh.end);
}

void hitContextTest(
  uint64_t doff,
  const char* enc,
  size_t hbeg,
  size_t hend,
  size_t window,
  uint32_t repl,
  const std::vector<byte>& data,
  const std::string& estr,
  uint32_t ebad,
  size_t wbeg,
  size_t wend,
  size_t edhbeg,
  size_t edhend)
{
  const LG_Window inner{doff + hbeg, doff + hend};
  LG_Window outer, adh;
  const char* utf8 = nullptr;

  std::unique_ptr<DecoderHandle, void(*)(DecoderHandle*)> hdec{
    lg_create_decoder(),
    lg_destroy_decoder
  };

  LG_Error* err = nullptr;

  const unsigned int abad = lg_hit_context(
    hdec.get(),
    reinterpret_cast<const char*>(data.data()),
    reinterpret_cast<const char*>(data.data()) + data.size(),
    doff,
    &inner,
    enc,
    window,
    repl,
    &utf8,
    &outer,
    &adh,
    &err
  );

  if (err) {
    const std::string msg(err->Message);
    lg_free_error(err);
    throw std::runtime_error(msg);
  }

  std::unique_ptr<const char[],void(*)(const char*)> pchars(
    utf8, &lg_free_hit_context_string
  );

  REQUIRE(ebad == abad);
  REQUIRE(estr == utf8);

  REQUIRE(doff + wbeg == outer.begin);
  REQUIRE(doff + wend == outer.end);

  REQUIRE(edhbeg == adh.begin);
  REQUIRE(edhend == adh.end);
}

TEST_CASE("lgReadWindowASCII") {
  readWindowTest(
    42, "ASCII",
    3, 6, // hit is "def"
    2, 2, // window is "bcdefgh"
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    { 'b', 'c', 'd', 'e', 'f', 'g', 'h', Decoder::END },
    { 1, 2, 3, 4, 5, 6, 7, 8 },
    2, 5
  );
}

TEST_CASE("lgReadWindowASCIISmallPrefix") {
  readWindowTest(
    42, "ASCII",
    1, 3, // hit is "bc"
    5, 5, // window is "abcdefgh"
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', Decoder::END },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
    1, 3
  );
}

TEST_CASE("lgReadWindowASCIISmallSuffix") {
  readWindowTest(
    42, "ASCII",
    8, 10, // hit is "ij"
    5, 5,  // window is "defghijk"
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    { 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', Decoder::END },
    { 3, 4, 5, 6, 7, 8, 9, 10, 11 },
    5, 7
  );
}

TEST_CASE("lgHitContextASCII") {
  hitContextTest(
    42, "ASCII",
    3, 6, // hit is "def"
    2,    // window is "bcdefgh"
    0x1F4A9,
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    "bcdefgh",
    0,
    1, 8,
    2, 5
  );
}

TEST_CASE("lgReadWindowUTF8WithBadSpot") {
  readWindowTest(
    42, "UTF-8",
    3, 4, // hit is "c"
    2, 2, // window is b -0xE0 c PILE_OF_POO
    { 'a', 'b', 0xDF, 'c', 0xF0, 0x9F, 0x92, 0xA9 },
    { 'b', -0xE0, 'c', 0x1F4A9, Decoder::END },
    { 1, 2, 3, 4, 8 },
    2, 3
  );
}

TEST_CASE("lgReadWindowUTF16LEWithBadSpotRequiringDecoderRestart") {
  /*
    1) 0x63DF (i.e., 0xDF 'c') is a valid UTF-16LE unit, but decoding
    that would invalidate our hit at 'c'. This test checks that the
    decoder is being run for the hit separately from the preceeding
    context.

    2) 'b' -0xE0 is a better prefix than -0x01 -0xE0, because the length
    of the sequence of good code points adjacent to the hit in each is
    zero, but the former has fewer bad values (1 vs. 2). This test checks
    that the better prefix is produced.
  */

  readWindowTest(
    42, "UTF-16LE",
    5, 6, // hit is "c"
    2, 2, // window is b -0xE0 c d
    { 'a', 0x00, 'b', 0x00, 0xDF, 'c', 0x00, 'd', 0x00 },
    { 'b', -0xE0, 'c', 'd', Decoder::END },
    { 2, 4, 5, 7, 9 },
    2, 3
  );
}

TEST_CASE("lgReadWindowTestUTF8NoBadSpots") {
  readWindowTest(
    0, "UTF-8",
    4, 7, // hit is "abc"
    2, 2,
    { 0xE2, 0x9A, 0xA1, ' ', 'a', 'b', 'c', 0xD0, 0x96 },
    { 0x26A1, ' ', 'a', 'b', 'c', 0x0416, Decoder::END },
    { 0, 3, 4, 5, 6, 7, 9 },
    2, 5
  );
}

TEST_CASE("lgHitContextUTF8NoBadSpots") {
  hitContextTest(
    0, "UTF-8",
    4, 7, // hit is "abc"
    2,
    0xFFFD,
    { 0xE2, 0x9A, 0xA1, ' ', 'a', 'b', 'c', 0xD0, 0x96 },
    u8"⚡ abcЖ",
    0,
    0, 9,
    4, 7
  );
}

TEST_CASE("lgReadWindowTestUTF8LeadingJunk") {
  readWindowTest(
    0, "UTF-8",
    4, 7, // hit is "abc"
    2, 2,
    { 0xFF, 0xFF, 0xFF, ' ', 'a', 'b', 'c', 0xD0, 0x96 },
    { -0x100, ' ', 'a', 'b', 'c', 0x0416, Decoder::END },
    { 2, 3, 4, 5, 6, 7, 9 },
    2, 5
  );
}

TEST_CASE("lgHitContextUTF8LeadingJunk") {
  hitContextTest(
    0, "UTF-8",
    5, 8, // hit is "abc"
    2,
    0xFFFD,
    { 0xFF, 0xFF, 0xFF, 0xFF, ' ', 'a', 'b', 'c', 0xD0, 0x96 },
    u8"� abcЖ",
    1,
    3, 10,
    4, 7
  );
}

TEST_CASE("lgReadWindowTestLeadingUTF8JunkUTF8Again") {
  readWindowTest(
    0, "UTF-8",
    3, 6, // hit is "abc"
    3, 2,
    { 'x', 0xFF, 'y', 'a', 'b', 'c', 0xD0, 0x96 },
    { 'x', -0x100, 'y', 'a', 'b', 'c', 0x0416, Decoder::END },
    { 0, 1, 2, 3, 4, 5, 6, 8 },
    3, 6
  );
}
