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

#include <vector>

#include "decoders/bytesource.h"
#include "decoders/icudecoder.h"

using DecoderPair = std::pair<int32_t, const byte*>;

std::ostream& operator<<(std::ostream& out, const DecoderPair& dp) {
  out << '{' << dp.first << ", " << *dp.second << '}' << '\n';
  return out;
}

#include <catch2/catch_test_macros.hpp>

TEST_CASE("icuDecoderName") {
  const char name[] = "ISO-8859-1";
  const byte buf[] = "x";
  ICUDecoder d(name, std::unique_ptr<Decoder>(new ByteSource(buf, buf)));
  REQUIRE(name == d.name());
}

TEST_CASE("icuDecoder_ISO_8859_1_Next") {
  const byte buf[] = {
    'a', 'b', 'c', 0x80, 0x81, 0xC6, 0xFE
  };
  // a    b    c                Æ     þ

  ICUDecoder d("ISO-8859-1", std::unique_ptr<Decoder>(
    new ByteSource(buf, buf + sizeof(buf))
  ));

  const std::vector<std::pair<int32_t,const byte*>> exp{
    {'a', buf},
    {'b', buf+1},
    {'c', buf+2},
    {0x80, buf+3}, {0x81, buf+4},
    {0xC6, buf+5}, {0xFE, buf+6},
    {Decoder::END, buf+7}
  };

  for (const DecoderPair& cp : exp) {
    REQUIRE(cp == d.next());
  }
}

TEST_CASE("icuDecoder_EUC_KR_Next") {
  const byte buf[] = {
    'a', 'b', 'c', 0xB0, 0xFD, 0xFF, 0xB2, 0xE1
  };
  // a    b    c |     괄    | bad |    꿍

  ICUDecoder d("EUC-KR", std::unique_ptr<Decoder>(
    new ByteSource(buf, buf + sizeof(buf))
  ));

  const std::vector<std::pair<int32_t,const byte*>> exp{
    {'a', buf},
    {'b', buf+1},
    {'c', buf+2},
    {0xAD04, buf+3},
    { -0x100, buf+5},
    {0xAFCD, buf+6},
    {Decoder::END, buf+8}
  };

  for (const DecoderPair& cp : exp) {
    REQUIRE(cp == d.next());
  }
}

TEST_CASE("icuDecoder_GB18030_Next") {
  const byte buf[] = {
    'a', 'b', 'c', 0x90, 0x30, 0x81, 0x31, 0x80, 0xFF, 0x90
  };
  // a    b    c |        U+10001        | euro | bad | bad

  ICUDecoder d("GB18030", std::unique_ptr<Decoder>(
    new ByteSource(buf, buf + sizeof(buf))
  ));

  const std::vector<DecoderPair> exp{
    {'a', buf},
    {'b', buf+1},
    {'c', buf+2},
    {0x10001, buf+3},
    {0x20ac, buf+7},
    {-0x100, buf+8},
    {-0x91, buf+9},
    {Decoder::END, buf+10}
  };

  for (const DecoderPair& cp : exp) {
    REQUIRE(cp == d.next());
  }
}
