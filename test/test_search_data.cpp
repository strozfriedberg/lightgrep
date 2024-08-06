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

#include "config.h"
#include "dtest.h"

TEST_CASE("hundredPatternSearch") {
  DTest fixture(LG_TEST_DATA_DIR "/hectotest.dat");
  REQUIRE(fixture);
}

TEST_CASE("thousandPatternSearch") {
  DTest fixture(LG_TEST_DATA_DIR "/kilotest.dat");
  REQUIRE(fixture);
}
