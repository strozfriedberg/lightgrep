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

#include <algorithm>
#include <cstring>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "stest.h"

TEST_CASE("ai_switches_Search") {
  STest fixture({
    {"(?i)x((?-i)x)x", false, false, true, "UTF-8"},
    {"(?i)k(?-i)k(?ai)k+", false, false, true, "UTF-8"},
    {"(?i)k(?-i)k(?i)k+", false, false, true, "UTF-8"}
  });
  fixture.search("XXX XxX xxx Kkkk Kk\xE2\x84\xAAK", 0);
  const std::vector<SearchHit> expected {
    {4, 7, 0},
    {8, 11, 0},
    {12, 16, 2},
    {12, 16, 1},
#ifdef HAVE_ICU
    {17, 23, 2},
#endif
  };
  REQUIRE(expected == fixture.Hits);
}
