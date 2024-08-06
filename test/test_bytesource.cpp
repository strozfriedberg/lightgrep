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

#include "decoders/bytesource.h"

TEST_CASE("byteSourceName") {
  const byte buf[] = "x";
  ByteSource bs(buf, buf);
  REQUIRE("" == bs.name());
}

TEST_CASE("byteSourceNext") {
  const byte buf[] = "abcdefghijklmnopqrstuvwxyz\n\t";
  ByteSource bs(buf, buf + sizeof(buf));
  for (size_t i = 0; i < sizeof(buf); ++i) {
    REQUIRE(std::make_pair((int32_t) buf[i], buf+i) == bs.next());
  }
  REQUIRE(std::make_pair(Decoder::END, buf+sizeof(buf)) == bs.next());
}
