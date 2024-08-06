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

#include "ostream_join_iterator.h"

#include <algorithm>
#include <sstream>

TEST_CASE("joinEmpty") {
  const int *a = 0;
  std::ostringstream ss;
  std::copy(a, a, ostream_join_iterator<int>(ss, ", "));
  REQUIRE("" == ss.str());
}

TEST_CASE("joinSingleton") {
  const int a[] = { 1 };
  std::ostringstream ss;
  std::copy(a, a + 1, ostream_join_iterator<int>(ss, ", "));
  REQUIRE("1" == ss.str());
}

TEST_CASE("joinMultiple") {
  const int a[] = { 1, 2, 3 };
  std::ostringstream ss;
  std::copy(a, a + 3, ostream_join_iterator<int>(ss, ", "));
  REQUIRE("1, 2, 3" == ss.str());
}
