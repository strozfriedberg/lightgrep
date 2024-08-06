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

#include "encoders/ascii.h"

TEST_CASE("testASCII") {
  ASCII enc;
  REQUIRE(1u == enc.maxByteLength());

  byte buf[1];
  uint32_t len;

  // too low
  REQUIRE(0u == enc.write(-1, buf));

  // just right
  for (uint32_t i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    REQUIRE(1u == len);
    REQUIRE(i == buf[0]);
  }

  // too high
  REQUIRE(0u == enc.write(0x80, buf));
}
