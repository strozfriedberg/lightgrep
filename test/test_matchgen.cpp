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

#include "graph.h"
#include "matchgen.h"
#include "nfabuilder.h"
#include "parser.h"
#include "parsetree.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

void fixture(const char* pattern, const char** expected, uint32_t max_matches, uint32_t max_loops) {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(parse({pattern, false, false}, tree));
  REQUIRE(nfab.build(tree));

  std::set<std::string> aset;
  matchgen(*nfab.getFsm(), aset, max_matches, max_loops);

  std::set<std::string> eset(expected, expected + max_matches);
  REQUIRE(eset == aset);
}

TEST_CASE("aSampleMatches") {
  const char pattern[] = "a";
  const char* expected[] = { "a" };
  fixture(pattern, expected, std::extent_v<decltype(expected)>, 1);
}

/*
TEST_CASE("aOrbSampleMatches") {
  const char pattern[] = "a|b";
  const char* expected[] = { "a", "b" };
  fixture(pattern, expected, std::extent_v<decltype(expected)>, 1);
}
*/

/*
TEST_CASE("LPaOrbRPLPcOrdRPSampleMatches") {
  const char pattern[] = "(a|b)(c|d)";
  const char* expected[] = { "ac", "ad", "bc", "bd" };
  fixture(pattern, expected, std::extent_v<decltype(expected)>, 1);
}
*/

TEST_CASE("aPSampleMatches1") {
  const char pattern[] = "a+";
  const char* expected[] = { "a" };
  fixture(pattern, expected, std::extent_v<decltype(expected)>, 1);
}

/*
TEST_CASE("aPSampleMatches2") {
  const char pattern[] = "a+";
  const char* expected[] = { "a", "aa" };
  fixture(pattern, expected, std::extent_v<decltype(expected)>, 2);
}

TEST_CASE("aPSampleMatches3") {
  const char pattern[] = "a+";
  const char* expected[] = { "a", "aa", "aaa" };
  fixture(pattern, expected, std::extent_v<decltype(expected)>, 3);
}
*/
