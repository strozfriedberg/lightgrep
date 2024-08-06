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

#include <vector>

#include "decoders/bytesource.h"
#include "decoders/icudecoder.h"

using DecoderPair = std::pair<int32_t, const byte*>;


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

  const std::vector<DecoderPair> exp{
    {'a', buf},
    {'b', buf + 1},
    {'c', buf + 2},
    {0x80, buf + 3},
    {0x81, buf + 4},
    {0xC6, buf + 5},
    {0xFE, buf + 6},
    {Decoder::END, buf + 7}
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

  const std::vector<DecoderPair> exp{
    {'a', buf},
    {'b', buf + 1},
    {'c', buf + 2},
    {0xAD04, buf + 3}, // 2-byte code point
    { -0x100, buf + 5},
    {0xAFCD, buf + 6}, // 2-byte code point
    {Decoder::END, buf + 8}
  };

  for (const DecoderPair& cp : exp) {
    REQUIRE(cp == d.next());
  }
}

TEST_CASE("icuDecoder_GB18030_Next") {
  const byte buf[] = {
    'a', 'b', 'c', 0x90, 0x30, 0x81, 0x31, 0xFF, 0x90
  };
  // a    b    c |        U+10001         | bad | bad

  ICUDecoder d("GB18030", std::unique_ptr<Decoder>(
    new ByteSource(buf, buf + sizeof(buf))
  ));

  const std::vector<DecoderPair> exp{
    {'a', buf},
    {'b', buf + 1},
    {'c', buf + 2},
    {0x10001, buf + 3}, // 4-byte code point
    {-0x100, buf + 7},
    {-0x91, buf + 8},
    {Decoder::END, buf + 9}
  };

  for (const DecoderPair& cp : exp) {
    REQUIRE(cp == d.next());
  }
}
