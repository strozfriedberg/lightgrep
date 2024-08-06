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

#include <algorithm>

#include <catch2/catch_test_macros.hpp>

#include "stest.h"

TEST_CASE("autoMultipatternSearchTest250") {
  STest fixture({"a+|b", "a|a|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest251") {
  STest fixture({"a*?|(b)", "a+|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {3, 4, 1},
    {4, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest252") {
  STest fixture({"aa|b|a", "aba*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {2, 6, 1},
    {3, 4, 0},
    {4, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest253") {
  STest fixture({"a??b", "a*?b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest254") {
  STest fixture({"a??a", "a|ba??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest255") {
  STest fixture({"a*|(b)", "aa|b??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest256") {
  STest fixture({"a*?a|b", "a+|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest257") {
  STest fixture({"a?a*?", "a+?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 10, 1},
    {10, 12, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest258") {
  STest fixture({"a|a|ab", "a+a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 8, 1},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest259") {
  STest fixture({"a??|ab", "a+|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest260") {
  STest fixture({"a*|b|c", "a|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest261") {
  STest fixture({"a+?|a+?", "a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest262") {
  STest fixture({"a+|b", "a*?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
    {3, 4, 0},
    {4, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest263") {
  STest fixture({"a+|(b)", "a?a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest264") {
  STest fixture({"a|a|b*", "a?a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest265") {
  STest fixture({"a|b|c|c", "a|aa+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest266") {
  STest fixture({"a?a*?", "a|b|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest267") {
  STest fixture({"a+?|(a)", "a?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest268") {
  STest fixture({"a|bb|c", "ab*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 0},
    {7, 10, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 21, 0},
    {22, 23, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest269") {
  STest fixture({"a+|b|b", "aa|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest270") {
  STest fixture({"a|b|ab", "ab|c??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest271") {
  STest fixture({"a|b|b+?", "a?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 5, 1},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {9, 11, 1},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {15, 17, 1},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest272") {
  STest fixture({"a??|a|a", "a*(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest273") {
  STest fixture({"a|bc|c", "ab|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {10, 11, 0},
    {11, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {21, 23, 0},
    {23, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest274") {
  STest fixture({"a|b(a)", "a*(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {9, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {15, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest275") {
  STest fixture({"ab|a|b", "a|bc|."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 23, 1},
    {23, 24, 0},
    {23, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest276") {
  STest fixture({"abc+", "a|b|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {10, 13, 0},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest277") {
  STest fixture({"a|aa?", "ab|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest278") {
  STest fixture({"a+?|b+?", "a|a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest279") {
  STest fixture({"a??|b+", "(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest280") {
  STest fixture({"ab|a+", "aa|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
    {2, 3, 1},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest281") {
  STest fixture({"aa*", "abba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {7, 11, 1},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest282") {
  STest fixture({"a*b?", "ab|ac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 1},
    {5, 7, 1},
    {7, 9, 1},
    {10, 12, 1},
    {13, 15, 1},
    {16, 18, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest283") {
  STest fixture({"a*?a+?", "aab?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest284") {
  STest fixture({"a??b*?", "a*|a+"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest285") {
  STest fixture({"a|b|cb", "a|b|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {18, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {22, 24, 0},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest286") {
  STest fixture({"a+a*?", "aa|bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {8, 10, 1},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {19, 21, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest287") {
  STest fixture({"a+?|a|a", "a??bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 10, 1},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {19, 21, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest288") {
  STest fixture({"a*?bb", "(a|a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 10, 0},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {19, 21, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest289") {
  STest fixture({"a??b??", "a??|b|c"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest290") {
  STest fixture({"a+?|a*", "a+bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest291") {
  STest fixture({"a|ab??", "a+b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest292") {
  STest fixture({"((a))", "abac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest293") {
  STest fixture({"a|b|a+?", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest294") {
  STest fixture({"a|baa", "a?a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {3, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest295") {
  STest fixture({"a|aa?", "a*?a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest296") {
  STest fixture({"a+?b?", "a??|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest297") {
  STest fixture({"a??ab", "a|bc+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {1, 4, 0},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 12, 0},
    {11, 13, 1},
    {13, 14, 1},
    {16, 17, 1},
    {21, 23, 1},
    {23, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest298") {
  STest fixture({"a+|b|b", "abb?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {2, 4, 1},
    {3, 4, 0},
    {4, 6, 0},
    {7, 8, 0},
    {7, 10, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest299") {
  STest fixture({"a|b|a??", "a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest300") {
  STest fixture({"a|b|ba", "a+|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest301") {
  STest fixture({"a|aa??", "a+?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest302") {
  STest fixture({"((a))", "a|b|(c)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest303") {
  STest fixture({"ab(c)", "ab|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest304") {
  STest fixture({"a??|a|a", "a?b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest305") {
  STest fixture({"aba|b", "a|b|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {8, 9, 0},
    {9, 10, 0},
    {11, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest306") {
  STest fixture({"a+?a", "a?|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest307") {
  STest fixture({"a|b??", "a|b|c|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest308") {
  STest fixture({"a+a+?", "a+?|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest309") {
  STest fixture({"ab|cb", "a|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 1},
    {14, 16, 0},
    {15, 16, 1},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {18, 20, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {22, 24, 0},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest310") {
  STest fixture({"a*|a??", "a|b|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest311") {
  STest fixture({"a*b*", "a+b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 9, 1},
    {10, 12, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest312") {
  STest fixture({"a??|b", "a|b|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest313") {
  STest fixture({"a|b|c|.", "a+|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest314") {
  STest fixture({"a|bb|c", "ab+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {7, 9, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {12, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 21, 0},
    {22, 23, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest315") {
  STest fixture({"a?|a+?", "a??|b|c"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest316") {
  STest fixture({"a+|aa", "a|bc*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest317") {
  STest fixture({"a??|a+?", "ab|c*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest318") {
  STest fixture({"a??b??", "a?|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest319") {
  STest fixture({"aa(a)", "a|ab+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest320") {
  STest fixture({"a|bb|b", "a+?|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest321") {
  STest fixture({"a*a+?", "a?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest322") {
  STest fixture({"a+?|ba", "a+?b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 4, 1},
    {3, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 9, 1},
    {9, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest323") {
  STest fixture({"a|a|a|b", "a??|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest324") {
  STest fixture({"ab|b", "a+|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {2, 4, 0},
    {4, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {9, 10, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest325") {
  STest fixture({"a?a", "a*?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest326") {
  STest fixture({"a+?|b|c", "a*a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {22, 23, 0},
    {23, 24, 0},
    {23, 24, 1},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest327") {
  STest fixture({"aaa?", "(a)+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest328") {
  STest fixture({"a??a+", "a?b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {2, 4, 1},
    {4, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest329") {
  STest fixture({"a*?a*?", "aba|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 5, 1},
    {8, 9, 1},
    {9, 10, 1},
    {11, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest330") {
  STest fixture({"a*?|a+?", "a+|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest331") {
  STest fixture({"a+?|a*", "abbc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest332") {
  STest fixture({"a*?bc", "a|baa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {10, 13, 0},
    {13, 14, 1},
    {16, 17, 1},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest333") {
  STest fixture({"ab|a*", "a?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 5, 1},
    {9, 11, 1},
    {15, 17, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest334") {
  STest fixture({"a*?b|a", "a??|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest335") {
  STest fixture({"ab|a?", "a+|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest336") {
  STest fixture({"a*?|b??", "a+?|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest337") {
  STest fixture({"a|b(b)", "aa|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 21, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest338") {
  STest fixture({"a+?|(a)", "a|a|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest339") {
  STest fixture({"a|a|ab", "a+?|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest340") {
  STest fixture({"ab|b|c", "a+?bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 7, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {10, 13, 1},
    {12, 13, 0},
    {14, 15, 0},
    {15, 16, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest341") {
  STest fixture({"a??|a+", "a|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest342") {
  STest fixture({"aa|a*?", "a+b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {7, 9, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest343") {
  STest fixture({"a+|a*?", "a|a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest344") {
  STest fixture({"a+?a?", "a+a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 3, 1},
    {2, 3, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest345") {
  STest fixture({"aa|b*", "a+?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest346") {
  STest fixture({"a|bb+?", "a|bb|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 0},
    {8, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 21, 0},
    {19, 21, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest347") {
  STest fixture({"abb", "a+|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest348") {
  STest fixture({"aab", "a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {1, 4, 0},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest349") {
  STest fixture({"a?b*?", "a?|a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest350") {
  STest fixture({"(a)??", "a|aa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest351") {
  STest fixture({"abc?", "a+?a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 13, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest352") {
  STest fixture({"aa|a", "a|aa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest353") {
  STest fixture({"a|b|a|c", "a*b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest354") {
  STest fixture({"abb?", "aab??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {2, 4, 0},
    {4, 6, 1},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest355") {
  STest fixture({"a?|a|a", "a??|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest356") {
  STest fixture({"a+|a*?", "a|b|ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest357") {
  STest fixture({"a??|b+?", "ab|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {2, 4, 1},
    {4, 6, 1},
    {7, 9, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest358") {
  STest fixture({"a+|a+?", "a*?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
    {4, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest359") {
  STest fixture({"a|abb", "a|b|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest360") {
  STest fixture({"a*|a*", "(aa)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest361") {
  STest fixture({"a|b|a|c", "a|bba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 11, 1},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest362") {
  STest fixture({"aaa|a", "a*|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest363") {
  STest fixture({"a*bb", "aa|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {4, 6, 1},
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest364") {
  STest fixture({"(a)?", "aba|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest365") {
  STest fixture({"a+|(b)", "(a)*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {3, 4, 0},
    {4, 6, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest366") {
  STest fixture({"a*a?", "a+b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {4, 6, 1},
    {7, 9, 1},
    {10, 12, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest367") {
  STest fixture({"a??a*", "a*a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest368") {
  STest fixture({"a?a?", "a+?|a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest369") {
  STest fixture({"a?a|a", "ab|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 2, 1},
    {2, 3, 0},
    {2, 4, 1},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {7, 9, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest370") {
  STest fixture({"aa|b*?", "a+b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {7, 9, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest371") {
  STest fixture({"a*|b|c", "ab|c|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 9, 1},
    {10, 12, 1},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 1},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {22, 23, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest372") {
  STest fixture({"a??a|a", "a?|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest373") {
  STest fixture({"a|bb", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 21, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest374") {
  STest fixture({"abba", "a?bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 1},
    {7, 11, 0},
    {19, 21, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest375") {
  STest fixture({"a*b", "a+(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
    {4, 6, 1},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest376") {
  STest fixture({"a|a|b*?", "a?|b*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest377") {
  STest fixture({"abc|c", "abb+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {6, 7, 0},
    {7, 10, 1},
    {10, 13, 0},
    {14, 15, 0},
    {17, 18, 0},
    {18, 19, 0},
    {22, 23, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest378") {
  STest fixture({"a|a|b+?", "a|a|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest379") {
  STest fixture({"a?|b?", "a??bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {10, 13, 1},
    {21, 23, 1},
    {23, 25, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest380") {
  STest fixture({"a?ab", "a|a|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {1, 4, 0},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest381") {
  STest fixture({"ab|c+", "a?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {1, 4, 1},
    {2, 4, 0},
    {6, 7, 0},
    {7, 9, 0},
    {7, 9, 1},
    {10, 12, 0},
    {10, 12, 1},
    {12, 13, 0},
    {14, 15, 0},
    {17, 19, 0},
    {22, 23, 0},
    {24, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest382") {
  STest fixture({"a*?|bb", "a|ba?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest383") {
  STest fixture({"a??|b|c", "abc."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {10, 14, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest384") {
  STest fixture({"a?|b|a", "a*?a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest385") {
  STest fixture({"a?|a+?", "ab|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 1},
    {7, 9, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest386") {
  STest fixture({"a|a|(a)", "a?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest387") {
  STest fixture({"a+a?", "a*?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest388") {
  STest fixture({"a*?|a|b", "a|b|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest389") {
  STest fixture({"a?|bc", "a+|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest390") {
  STest fixture({"a*?|b|c", "aa|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {2, 3, 1},
    {4, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest391") {
  STest fixture({"a+?|aa", "abb*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest392") {
  STest fixture({"a?|(b)", "a|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest393") {
  STest fixture({"ab|c|.", "a*(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 9, 0},
    {7, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 12, 0},
    {10, 12, 1},
    {12, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {22, 23, 0},
    {23, 24, 0},
    {23, 24, 1},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest394") {
  STest fixture({"a*?|ab", "aaa*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest395") {
  STest fixture({"a?b|b", "a*|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest396") {
  STest fixture({"a+?a", "a*|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest397") {
  STest fixture({"aba*", "a+?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {2, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest398") {
  STest fixture({"aaab", "a*|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest399") {
  STest fixture({"a?|a|a", "a?|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest400") {
  STest fixture({"aa|a?", "a*?(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest401") {
  STest fixture({"a*?b*", "a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest402") {
  STest fixture({"a|b|c.", "a|bc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 13, 1},
    {12, 14, 0},
    {13, 14, 1},
    {14, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {21, 23, 1},
    {22, 24, 0},
    {23, 25, 1},
    {24, 26, 0},
    {26, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest403") {
  STest fixture({"a|bca", "a|bb??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {11, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest404") {
  STest fixture({"a+a|b", "a|aa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest405") {
  STest fixture({"aa|b|b", "ab|c??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 4, 0},
    {4, 6, 0},
    {8, 9, 0},
    {9, 10, 0},
    {11, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest406") {
  STest fixture({"(a)(b)", "aa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {2, 4, 0},
    {3, 4, 1},
    {4, 6, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 1},
    {10, 12, 0},
    {11, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest407") {
  STest fixture({"a?|b*?", "ab|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 1},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest408") {
  STest fixture({"a+|a??", "a?b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest409") {
  STest fixture({"a?|b*?", "a|b|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest410") {
  STest fixture({"ab|a", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 4, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 9, 0},
    {7, 9, 1},
    {10, 12, 0},
    {10, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest411") {
  STest fixture({"a+?a", "a+?|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest412") {
  STest fixture({"a+bc", "a*a?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest413") {
  STest fixture({"a+?b*", R"(a??(b))"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 9, 1},
    {7, 10, 0},
    {9, 10, 1},
    {10, 12, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest414") {
  STest fixture({"a+a|b", "a|bb*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 0},
    {8, 10, 1},
    {9, 10, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 0},
    {19, 22, 1},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest415") {
  STest fixture({"a|a|a??", R"(a??(b))"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 1},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest416") {
  STest fixture({"a+|a", "a*(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
    {4, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest417") {
  STest fixture({"a|ab*?", "a+?|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest418") {
  STest fixture({"a|b|(c)", "a|bc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 13, 1},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {21, 23, 1},
    {22, 23, 0},
    {23, 24, 0},
    {23, 25, 1},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest419") {
  STest fixture({"a?a*", "a+?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {7, 9, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest420") {
  STest fixture({"a|b(b)", "a|a|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 21, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest421") {
  STest fixture({"a+b??", "a*?a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest422") {
  STest fixture({"a|a|bc", "a?b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {11, 13, 0},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {21, 23, 0},
    {23, 24, 1},
    {23, 25, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest423") {
  STest fixture({"aab|a", "aaa+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest424") {
  STest fixture({"a??|a*?", "a?|b??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest425") {
  STest fixture({"ab|b+", "a+?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {9, 10, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 1},
    {19, 22, 0},
    {23, 24, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest426") {
  STest fixture({"abba", "a*|a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest427") {
  STest fixture({"ab|c|b", "a?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 7, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {12, 13, 0},
    {14, 15, 0},
    {15, 16, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest428") {
  STest fixture({"a*?b*", "a*?|a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest429") {
  STest fixture({"a+?a?", "a|b|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest430") {
  STest fixture({"a??|a|a", "a|bb|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest431") {
  STest fixture({"a*?aa", "a|b(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {9, 11, 1},
    {13, 14, 1},
    {15, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest432") {
  STest fixture({"a+b*?", "a|b|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest433") {
  STest fixture({"a+?a??", "aa(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest434") {
  STest fixture({"a?b+?", "a+a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {2, 4, 0},
    {4, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {9, 10, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest435") {
  STest fixture({"a+?bb", "a|ba+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 10, 0},
    {9, 11, 1},
    {13, 14, 1},
    {15, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest436") {
  STest fixture({"ab|a+", "a|a|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest437") {
  STest fixture({"a+?|a+", "a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest438") {
  STest fixture({"a|b|c|a", "a|a|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {8, 10, 1},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 12, 1},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {19, 22, 1},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {23, 24, 1},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest439") {
  STest fixture({"a??|b|b", "((a))"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest440") {
  STest fixture({"a*a+", "a??|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest441") {
  STest fixture({"a*b|b", "a??a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 4, 0},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {9, 10, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest442") {
  STest fixture({"a|bc|.", "a|b|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 23, 0},
    {23, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest443") {
  STest fixture({"a+?ab", "a+?a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 4, 0},
    {3, 4, 1},
    {4, 6, 1},
    {8, 9, 1},
    {9, 10, 1},
    {11, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest444") {
  STest fixture({"a+?|bb", "ab|c|."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 0},
    {7, 9, 1},
    {8, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {12, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {19, 21, 0},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest445") {
  STest fixture({"a|a|ba", "a|b(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 1},
    {9, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 17, 0},
    {16, 17, 1},
    {19, 21, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest446") {
  STest fixture({"ab??", "ab|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest447") {
  STest fixture({"aaa", "a??|a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest448") {
  STest fixture({"a|b|c", "aba|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 5, 1},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest449") {
  STest fixture({"a|a|a|b", "ab|a|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 4, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 0},
    {7, 9, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {12, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 1},
    {23, 24, 0},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest450") {
  STest fixture({"a|bc+?", "abc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {10, 11, 0},
    {10, 13, 1},
    {11, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest451") {
  STest fixture({"a|ba?", "a?|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest452") {
  STest fixture({"ab|b+", "a?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest453") {
  STest fixture({"a+?b+?", "a*b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest454") {
  STest fixture({"a|bb+", "aa|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {6, 7, 1},
    {7, 8, 0},
    {8, 9, 1},
    {8, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 0},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 0},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {19, 22, 0},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest455") {
  STest fixture({"a+ab", "a+|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest456") {
  STest fixture({"a+|bb", "abb|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {6, 7, 1},
    {7, 8, 0},
    {7, 10, 1},
    {8, 10, 0},
    {10, 11, 0},
    {12, 13, 1},
    {13, 14, 0},
    {14, 15, 1},
    {16, 17, 0},
    {17, 18, 1},
    {18, 19, 1},
    {19, 21, 0},
    {22, 23, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest457") {
  STest fixture({"ab|a+", "aaa*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 9, 0},
    {10, 12, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest458") {
  STest fixture({"a+", "a*?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
    {4, 6, 0},
    {7, 8, 0},
    {7, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest459") {
  STest fixture({"abbb", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest460") {
  STest fixture({"ab|aa", "aba|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 4, 0},
    {2, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest461") {
  STest fixture({"a*?b|b", "a*?|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest462") {
  STest fixture({"abc?", "a+?b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {10, 11, 1},
    {10, 13, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest463") {
  STest fixture({"(a)*?", "a??|b|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest464") {
  STest fixture({"a+?a+?", "a|ba+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 6, 1},
    {4, 6, 0},
    {7, 8, 1},
    {9, 11, 1},
    {13, 14, 1},
    {15, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest465") {
  STest fixture({"ab|c+?", "(a)??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 7, 0},
    {7, 9, 0},
    {10, 12, 0},
    {12, 13, 0},
    {14, 15, 0},
    {17, 18, 0},
    {18, 19, 0},
    {22, 23, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest466") {
  STest fixture({"a*", "a+|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {3, 4, 1},
    {4, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest467") {
  STest fixture({"ab(c)", "(a*)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest468") {
  STest fixture({"a|a|bb", "a+bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 10, 1},
    {8, 10, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {19, 21, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest469") {
  STest fixture({"a*|bb", "a??|(a)"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest470") {
  STest fixture({"a|a|(a)", "aa|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest471") {
  STest fixture({"a|a(b)", "a+?|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {12, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest472") {
  STest fixture({"a??", "a|bb|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest473") {
  STest fixture({"abb*", "a??b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {2, 4, 1},
    {7, 9, 1},
    {7, 10, 0},
    {9, 10, 1},
    {10, 12, 0},
    {10, 12, 1},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest474") {
  STest fixture({"a|b|b|a", "a*?|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest475") {
  STest fixture({"a|b|ab", "a|bc+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 0},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {11, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {21, 23, 1},
    {23, 24, 0},
    {23, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest476") {
  STest fixture({"a*(b)", "aa|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 4, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest477") {
  STest fixture({"ab|b", "a+b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {2, 4, 0},
    {4, 5, 1},
    {5, 6, 1},
    {7, 9, 0},
    {7, 9, 1},
    {9, 10, 0},
    {10, 12, 0},
    {10, 12, 1},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest478") {
  STest fixture({"a*?|(a)", "a??|b|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest479") {
  STest fixture({"a*b*", "a?|a"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest480") {
  STest fixture({"aa|a??", "a??|ba"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest481") {
  STest fixture({"a+?|(a)", "a?a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {2, 3, 1},
    {4, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 8, 1},
    {10, 11, 0},
    {10, 11, 1},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest482") {
  STest fixture({"a??|b*?", "a+|ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {3, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {9, 11, 1},
    {13, 14, 1},
    {15, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest483") {
  STest fixture({"a*a??", "a|a(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest484") {
  STest fixture({"a*?b+", "a|b|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest485") {
  STest fixture({"a+a+?", "a*|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest486") {
  STest fixture({"a|bb+?", "aba|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 5, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {8, 9, 1},
    {8, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {11, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {19, 21, 0},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest487") {
  STest fixture({"a*?a??", "a*?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest488") {
  STest fixture({"ab|c*", "a*|a|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest489") {
  STest fixture({"a|bc|a", "ab|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {10, 11, 0},
    {10, 12, 1},
    {11, 13, 0},
    {13, 14, 0},
    {16, 17, 0},
    {21, 23, 0},
    {21, 23, 1},
    {23, 25, 0},
    {23, 25, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest490") {
  STest fixture({"(a)*?", "aab*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest491") {
  STest fixture({"a?a", "a|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest492") {
  STest fixture({"a+|b+", "a+a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
    {3, 4, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {19, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest493") {
  STest fixture({"a|b|c|.", "a|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {15, 16, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 0},
    {23, 24, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest494") {
  STest fixture({"a*?|b??", "a+?|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {5, 6, 1},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest495") {
  STest fixture({"a*?|ab", "a*?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 5, 1},
    {9, 11, 1},
    {15, 17, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest496") {
  STest fixture({"a|bc*?", "a*?b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {8, 9, 0},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest497") {
  STest fixture({"a?|a", "a?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest498") {
  STest fixture({"a?a", "a+?b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 4, 1},
    {2, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {16, 17, 0},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest499") {
  STest fixture({"ab|a|b", "a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
    {1, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {3, 4, 1},
    {4, 5, 0},
    {4, 5, 1},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}
