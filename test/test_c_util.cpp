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

/*
#include <iostream>
#include "container_out.h"
*/

#include <algorithm>
#include <memory>
#include <vector>

#include "decoders/decoder.h"
#include "lightgrep/util.h"

void readWindowTest(
  uint64_t doff,
  const char* enc,
  size_t hbeg,
  size_t hend, 
  size_t pre,
  size_t post,
  const std::vector<byte>& data,
  const std::vector<int32_t>& ecp,
  const std::vector<size_t>& eoff)
{
  const LG_Window inner{doff + hbeg, doff + hend};
  int32_t* chars;
  size_t* offsets;
  size_t clen;

  const unsigned int abad = lg_read_window(
    reinterpret_cast<const char*>(data.data()),
    reinterpret_cast<const char*>(data.data()) + data.size(), 
    doff,
    &inner,
    enc,
    pre,
    post,
    &chars,
    &offsets,
    &clen
  );

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    chars, lg_free_window_characters
  );

  std::unique_ptr<size_t[],void(*)(size_t*)> poff(
    offsets, lg_free_window_offsets
  );

  const size_t ebad = std::count_if(
    ecp.begin(), ecp.end()-1, [](int32_t v){ return v < 0; }
  );

  SCOPE_ASSERT_EQUAL(ebad, abad);

  std::vector<int32_t> acp(chars, chars+clen);
  SCOPE_ASSERT_EQUAL(ecp, acp);

  std::vector<size_t> aoff(offsets, offsets+clen);
  SCOPE_ASSERT_EQUAL(eoff, aoff);
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
  size_t wend)
{
  const LG_Window inner{doff + hbeg, doff + hend};
  LG_Window outer;
  const char* utf8;

  const unsigned int abad = lg_hit_context(
    reinterpret_cast<const char*>(data.data()),
    reinterpret_cast<const char*>(data.data()) + data.size(),
    doff,
    &inner,
    enc,
    window,
    repl,
    &utf8,
    &outer
  );

  std::unique_ptr<const char[],void(*)(const char*)> pchars(
    utf8, lg_free_hit_context_string
  );

  SCOPE_ASSERT_EQUAL(ebad, abad);
  SCOPE_ASSERT_EQUAL(estr, utf8);

  SCOPE_ASSERT_EQUAL(doff + wbeg, outer.begin);
  SCOPE_ASSERT_EQUAL(doff + wend, outer.end);
} 

SCOPE_TEST(lgReadWindowASCII) {
  readWindowTest(
    42, "ASCII",
    3, 6, // hit is "def"
    2, 2, // window is "bcdefgh"
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    { 'b', 'c', 'd', 'e', 'f', 'g', 'h', Decoder::END },
    { 1, 2, 3, 4, 5, 6, 7, 8 }
  );
}

SCOPE_TEST(lgReadWindowASCIISmallPrefix) {
  readWindowTest(
    42, "ASCII",
    1, 3, // hit is "bc"
    5, 5, // window is "bcdefgh"
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', Decoder::END },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8 }
  );
}

SCOPE_TEST(lgReadWindowASCIISmallSuffix) {
  readWindowTest(
    42, "ASCII",
    8, 10, // hit is "ij"
    5, 5,  // window is "defghijk" 
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    { 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', Decoder::END },
    { 3, 4, 5, 6, 7, 8, 9, 10, 11 }
  );
}

SCOPE_TEST(lgHitContextASCII) {
  hitContextTest(
    42, "ASCII",
    3, 6, // hit is "def"
    2,    // window is "bcdefgh"
    0x1F4A9,
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    "bcdefgh",
    0,
    1, 8
  );
}

SCOPE_TEST(lgReadWindowUTF8WithBadSpot) {
  readWindowTest(
    42, "UTF-8",
    3, 4, // hit is "c"
    2, 2, // window is b -0xE0 c PILE_OF_POO
    { 'a', 'b', 0xDF, 'c', 0xF0, 0x9F, 0x92, 0xA9 },
    { 'b', -0xE0, 'c', 0x1F4A9, Decoder::END },
    { 1, 2, 3, 4, 8 }
  );
}

SCOPE_TEST(lgReadWindowUTF16LEWithBadSpotRequiringDecoderRestart) {
  // 0x62DF (i.e., 0xDF 'c') a valid UTF-16LE unit, but decoding
  // that would invalidate our hit at 'c'. This test checks that
  // the decoder is being run for the hit separately from the
  // preceeding context.

  readWindowTest(
    42, "UTF-16LE",
    5, 6, // hit is "c"
    2, 2, // window is b -0xE0 c d
    { 'a', 0x00, 'b', 0x00, 0xDF, 'c', 0x00, 'd', 0x00 },
    { 'b', -0xE0, 'c', 'd', Decoder::END },
    { 2, 4, 5, 7, 9 }
  );
}
