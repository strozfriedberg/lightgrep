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

#include "basic.h"

#include <catch2/catch_test_macros.hpp>

#include <set>

#include <unicode/ucnv.h>

TEST_CASE("testICUStandards") {
  // check that ICU is defining exactly the standards we expect

  std::set<std::string> expected{
    "UTR22", "IANA", "MIME", "IBM", "WINDOWS", "JAVA", ""
  };

  std::set<std::string> actual;
  UErrorCode err = U_ZERO_ERROR;
  const uint32_t slen = ucnv_countStandards();
  for (uint32_t i = 0; i < slen; ++i) {
    actual.insert(ucnv_getStandard(i, &err));
    REQUIRE(!U_FAILURE(err));
  }

  REQUIRE(expected == actual);
}
