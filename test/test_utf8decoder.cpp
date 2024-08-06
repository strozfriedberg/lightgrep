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

#include <vector>

#include "decoders/bytesource.h"
#include "decoders/utf8decoder.h"

TEST_CASE("utf8DecoderName") {
  const byte buf[] = "x";
  UTF8Decoder d(std::unique_ptr<Decoder>(new ByteSource(buf, buf)));
  REQUIRE("UTF-8" == d.name());
}

TEST_CASE("utf8DecoderNext") {
  const byte buf[] = {
    'a', 'b', 'c', 0x80, 0x81, 0xF0, 0x9F, 0x92, 0xA9
  };
  // a    b    c  | invalid  | PILE_OF_POO

  UTF8Decoder d(std::unique_ptr<Decoder>(
    new ByteSource(buf, buf + sizeof(buf))
  ));

  const std::vector<std::pair<int32_t,const byte*>> exp{
    {'a', buf}, {'b', buf+1}, {'c', buf+2},
    {-0x81, buf+3}, {-0x82, buf+4},
    {0x1F4A9, buf+5},
    {Decoder::END, buf+9}
  };

  for (const std::pair<int32_t,const byte*>& cp : exp) {
    REQUIRE(cp == d.next());
  }
}
