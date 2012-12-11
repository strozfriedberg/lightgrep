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

#include <cstring>
#include <memory>

#include "decoders/decoder.h"
#include "lightgrep/util.h"

SCOPE_TEST(lgReadWindowASCII) {
  const uint64_t doff = 42;
  const char* buf = "abcdefghijk";  
  const LG_Window inner{doff + 3, doff + 6}; // hit is "def"
  int32_t* chars;
  const char** offsets;
  size_t clen;

  const unsigned int ret = lg_read_window(
    buf,
    buf + std::strlen(buf), 
    doff,
    &inner,
    "ASCII",
    2,
    &chars,
    &offsets,
    &clen
  );

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    chars, lg_free_window_characters
  );

  std::unique_ptr<const char*[],void(*)(const char**)> poff(
    offsets, lg_free_window_offsets
  );

  SCOPE_ASSERT_EQUAL(0u, ret);

  const int32_t echars[] = { 'b', 'c', 'd', 'e', 'f', 'g', 'h', Decoder::END };
  const char* eoff[] = {
    buf+1, buf+2, buf+3, buf+4, buf+5, buf+6, buf+7, buf+8
  };
  const size_t elen = sizeof(echars)/sizeof(echars[0]);

  SCOPE_ASSERT_EQUAL(elen, clen);

  for (size_t i = 0; i < elen; ++i) {
    SCOPE_ASSERT_EQUAL(echars[i], chars[i]);
    SCOPE_ASSERT_EQUAL(eoff[i], offsets[i]);
  }
}

SCOPE_TEST(lgReadWindowASCIISmallPrefix) {
  const uint64_t doff = 42;
  const char* buf = "abcdefghijk";
  const LG_Window inner{doff + 1, doff + 3}; // hit is "bc"
  int32_t* chars;
  const char** offsets;
  size_t clen;

  const unsigned int ret = lg_read_window(
    buf,
    buf + std::strlen(buf), 
    doff,
    &inner,
    "ASCII",
    5,
    &chars,
    &offsets,
    &clen
  );

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    chars, lg_free_window_characters
  );

  std::unique_ptr<const char*[],void(*)(const char**)> poff(
    offsets, lg_free_window_offsets
  );

  SCOPE_ASSERT_EQUAL(0u, ret);

  const int32_t echars[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', Decoder::END
  };
  const char* eoff[] = {
    buf, buf+1, buf+2, buf+3, buf+4, buf+5, buf+6, buf+7, buf+8
  };
  const size_t elen = sizeof(echars)/sizeof(echars[0]);

  SCOPE_ASSERT_EQUAL(elen, clen);

  for (size_t i = 0; i < elen; ++i) {
    SCOPE_ASSERT_EQUAL(echars[i], chars[i]);
    SCOPE_ASSERT_EQUAL(eoff[i], offsets[i]);
  }
}
SCOPE_TEST(lgReadWindowASCIISmallSuffix) {
  const uint64_t doff = 42;
  const char* buf = "abcdefghijk";  
  const LG_Window inner{doff + 8, doff + 10}; // hit is "ij"
  int32_t* chars;
  const char** offsets;
  size_t clen;

  const unsigned int ret = lg_read_window(
    buf,
    buf + std::strlen(buf), 
    doff,
    &inner,
    "ASCII",
    5,
    &chars,
    &offsets,
    &clen
  );

  std::unique_ptr<int32_t[],void(*)(int32_t*)> pchars(
    chars, lg_free_window_characters
  );

  std::unique_ptr<const char*[],void(*)(const char**)> poff(
    offsets, lg_free_window_offsets
  );

  SCOPE_ASSERT_EQUAL(0u, ret);

  const int32_t echars[] = {
    'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', Decoder::END
  };
  const char* eoff[] = {
    buf+3, buf+4, buf+5, buf+6, buf+7, buf+8, buf+9, buf+10, buf+11
  };
  const size_t elen = sizeof(echars)/sizeof(echars[0]);

  SCOPE_ASSERT_EQUAL(elen, clen);

  for (size_t i = 0; i < elen; ++i) {
    SCOPE_ASSERT_EQUAL(echars[i], chars[i]);
    SCOPE_ASSERT_EQUAL(eoff[i], offsets[i]);
  }
}
