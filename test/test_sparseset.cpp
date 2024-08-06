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

#include "sparseset.h"

TEST_CASE("basicSparseTest") {
  SparseSet s(5);
  REQUIRE(0u == s.size());
  for (uint32_t i = 0; i < 5; ++i) {
    REQUIRE(!s.find(i));
  }
  s.insert(3);
  REQUIRE(1u == s.size());
  REQUIRE(s.find(3));
  REQUIRE(!s.find(0));
  REQUIRE(!s.find(1));
  REQUIRE(!s.find(2));
  REQUIRE(!s.find(4));
}

TEST_CASE("sparseClear") {
  SparseSet s(5);
  REQUIRE(0u == s.size());
  s.insert(4);
  s.insert(2);
  REQUIRE(2u == s.size());
  s.clear();
  REQUIRE(0u == s.size());
  for (uint32_t i = 0; i < 5; ++i) {
    REQUIRE(!s.find(i));
  }
}
