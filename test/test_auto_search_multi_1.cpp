/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <algorithm>

#include "catch.hpp"

#include "stest.h"

TEST_CASE("autoMultipatternSearchTest0") {
  STest fixture({"a+?a*?", "ab|a+"});
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

TEST_CASE("autoMultipatternSearchTest1") {
  STest fixture({"a|aa?", "ab|a|b"});
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
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
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

TEST_CASE("autoMultipatternSearchTest2") {
  STest fixture({"a|bb+?", "a+|b??"});
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
    {8, 10, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {19, 21, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest3") {
  STest fixture({"aaa+", "a+?|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest4") {
  STest fixture({"a?|a??", "a|ba+?"});
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
    {9, 11, 1},
    {13, 14, 1},
    {15, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest5") {
  STest fixture({"a+?|b+?", "a|aa|b"});
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

TEST_CASE("autoMultipatternSearchTest6") {
  STest fixture({"a??b+", "a*?a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest7") {
  STest fixture({"a|a|b?", "a+b?"});
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

TEST_CASE("autoMultipatternSearchTest8") {
  STest fixture({"aab+?", "a*aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {1, 4, 0},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest9") {
  STest fixture({"ab|b+", "(a)*?"});
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

TEST_CASE("autoMultipatternSearchTest10") {
  STest fixture({"a*?", "a?|a+"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest11") {
  STest fixture({"a+b|c", "ab|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest12") {
  STest fixture({"a?|b|b", "a+|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest13") {
  STest fixture({"a?|a+", "a|b|c|."});
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

TEST_CASE("autoMultipatternSearchTest14") {
  STest fixture({"ab|b|b", "aabc"});
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

TEST_CASE("autoMultipatternSearchTest15") {
  STest fixture({"abab", "ab(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest16") {
  STest fixture({"ab|c|.", "a|bb*"});
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
    {6, 7, 0},
    {7, 8, 1},
    {7, 9, 0},
    {8, 10, 1},
    {9, 10, 0},
    {10, 11, 1},
    {10, 12, 0},
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

TEST_CASE("autoMultipatternSearchTest17") {
  STest fixture({"a+|b", "aa|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
    {3, 4, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {11, 13, 1},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {21, 23, 1},
    {23, 24, 0},
    {23, 25, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest18") {
  STest fixture({"a*?|(b)", "a|ab|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 1},
    {10, 11, 1},
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

TEST_CASE("autoMultipatternSearchTest19") {
  STest fixture({"ab|ba", "a|abb"});
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
    {9, 11, 0},
    {10, 11, 1},
    {13, 14, 1},
    {15, 17, 0},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest20") {
  STest fixture({"a*|ba", "ab|a|b"});
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

TEST_CASE("autoMultipatternSearchTest21") {
  STest fixture({"a|b|cc", "a|bc|b"});
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
    {11, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 19, 0},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 23, 1},
    {23, 24, 0},
    {23, 25, 1},
    {24, 26, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest22") {
  STest fixture({"a|a", "a??|bc"});
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

TEST_CASE("autoMultipatternSearchTest23") {
  STest fixture({"aa|ab", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 4, 0},
    {2, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 9, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 0},
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

TEST_CASE("autoMultipatternSearchTest24") {
  STest fixture({"a*a?", "a|abb"});
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

TEST_CASE("autoMultipatternSearchTest25") {
  STest fixture({"aa??", "a*|a*?"});
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

TEST_CASE("autoMultipatternSearchTest26") {
  STest fixture({"a??a??", "a|b|b"});
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

TEST_CASE("autoMultipatternSearchTest27") {
  STest fixture({"a|b|c|a", "abb|a"});
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
    {7, 10, 1},
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

TEST_CASE("autoMultipatternSearchTest28") {
  STest fixture({"a?|a*", "a?|b+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest29") {
  STest fixture({"a+b|a", "a|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest30") {
  STest fixture({"a*?a", "a??b+?"});
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

TEST_CASE("autoMultipatternSearchTest31") {
  STest fixture({"a*|b*?", "a|aa|a"});
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

TEST_CASE("autoMultipatternSearchTest32") {
  STest fixture({R"((a??))", "a|a|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest33") {
  STest fixture({"ab|c|c", "a+|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {2, 4, 0},
    {3, 4, 1},
    {4, 6, 1},
    {6, 7, 0},
    {6, 7, 1},
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {12, 13, 0},
    {12, 13, 1},
    {13, 14, 1},
    {14, 15, 0},
    {14, 15, 1},
    {15, 16, 1},
    {16, 17, 1},
    {17, 18, 0},
    {17, 18, 1},
    {18, 19, 0},
    {18, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 23, 0},
    {22, 23, 1},
    {23, 24, 1},
    {24, 25, 0},
    {24, 25, 1},
    {25, 26, 0},
    {25, 26, 1},
    {26, 27, 0},
    {26, 27, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest34") {
  STest fixture({"a*?a", "a|b|c?"});
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

TEST_CASE("autoMultipatternSearchTest35") {
  STest fixture({"a+?|aa", "a*|a"});
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

TEST_CASE("autoMultipatternSearchTest36") {
  STest fixture({"abba", "abc|a"});
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
    {7, 11, 0},
    {10, 13, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest37") {
  STest fixture({"a+a+?", "a+aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest38") {
  STest fixture({"a*|b|a", "a|ab+"});
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

TEST_CASE("autoMultipatternSearchTest39") {
  STest fixture({"abc+?", "a*?|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest40") {
  STest fixture({"aa??", "abc+"});
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
    {10, 13, 1},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest41") {
  STest fixture({"abca", "ab|b|a"});
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
    {10, 14, 0},
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

TEST_CASE("autoMultipatternSearchTest42") {
  STest fixture({"a??|b*", "a*a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest43") {
  STest fixture({"a+|a", "a|b|a|b"});
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

TEST_CASE("autoMultipatternSearchTest44") {
  STest fixture({"(a*)", "aaa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest45") {
  STest fixture({"a|aa*", "abb??"});
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

TEST_CASE("autoMultipatternSearchTest46") {
  STest fixture({"a|bc+?", "a+?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 5, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {11, 13, 0},
    {13, 14, 0},
    {16, 17, 0},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest47") {
  STest fixture({"a??|bc", "a+?|a?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest48") {
  STest fixture({"aa|a|a", "a??a??"});
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

TEST_CASE("autoMultipatternSearchTest49") {
  STest fixture({"a|aab", "a|a|a+"});
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

TEST_CASE("autoMultipatternSearchTest50") {
  STest fixture({"a?|a*?", "a|a|aa"});
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

TEST_CASE("autoMultipatternSearchTest51") {
  STest fixture({"a|b|c.", "a|ab|c"});
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
    {6, 7, 1},
    {6, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {12, 13, 1},
    {12, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {14, 16, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {17, 19, 0},
    {18, 19, 1},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {22, 23, 1},
    {22, 24, 0},
    {24, 25, 1},
    {24, 26, 0},
    {25, 26, 1},
    {26, 27, 1},
    {26, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest52") {
  STest fixture({"a??|a*", "a|a|bb"});
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
    {8, 10, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {19, 21, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest53") {
  STest fixture({"a+?b?", "a??a??"});
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

TEST_CASE("autoMultipatternSearchTest54") {
  STest fixture({"ab|c??", "a|bb+"});
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
    {8, 10, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {19, 22, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest55") {
  STest fixture({"abb|a", "aab??"});
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
    {7, 10, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest56") {
  STest fixture({"a+|ab", "a*|(a)"});
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

TEST_CASE("autoMultipatternSearchTest57") {
  STest fixture({"ab|bc", "a|b|ac"});
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
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {21, 23, 0},
    {23, 24, 1},
    {23, 25, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest58") {
  STest fixture({"a+?a*", "aabc"});
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

TEST_CASE("autoMultipatternSearchTest59") {
  STest fixture({"a|a??", "a|b|a|a"});
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

TEST_CASE("autoMultipatternSearchTest60") {
  STest fixture({"a|a??", "ab?"});
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
    {10, 12, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest61") {
  STest fixture({"a|b|bc", "a*a+"});
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

TEST_CASE("autoMultipatternSearchTest62") {
  STest fixture({"aa|a??", "a|b|aa"});
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

TEST_CASE("autoMultipatternSearchTest63") {
  STest fixture({"ab|c|b", "a|b|c??"});
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

TEST_CASE("autoMultipatternSearchTest64") {
  STest fixture({"(a|a)", "a+?b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 3, 0},
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

TEST_CASE("autoMultipatternSearchTest65") {
  STest fixture({"aaa|b", "a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {3, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest66") {
  STest fixture({"a?a?", "a+aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest67") {
  STest fixture({"a+|b*", "a|bb+"});
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
    {8, 10, 1},
    {10, 11, 1},
    {13, 14, 1},
    {16, 17, 1},
    {19, 22, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest68") {
  STest fixture({"aa|ba", "aa|a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest69") {
  STest fixture({"ab??", "a?|b?"});
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

TEST_CASE("autoMultipatternSearchTest70") {
  STest fixture({"a??|b*?", "a??b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest71") {
  STest fixture({"a??|b*?", "a+?b"});
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

TEST_CASE("autoMultipatternSearchTest72") {
  STest fixture({"ab|a??", "a+b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {4, 6, 1},
    {7, 10, 1},
    {10, 12, 1},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest73") {
  STest fixture({"a|b|a+?", "a|ab"});
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

TEST_CASE("autoMultipatternSearchTest74") {
  STest fixture({"aaa|b", "aab|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {1, 4, 1},
    {3, 4, 0},
    {8, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {11, 12, 0},
    {11, 12, 1},
    {15, 16, 0},
    {15, 16, 1},
    {19, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {23, 24, 0},
    {23, 24, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest75") {
  STest fixture({"ab|(a)", "a+?|b|c"});
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
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
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

TEST_CASE("autoMultipatternSearchTest76") {
  STest fixture({"a|b|b*?", "a|bc+?"});
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
    {11, 13, 1},
    {13, 14, 1},
    {16, 17, 1},
    {21, 23, 1},
    {23, 25, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest77") {
  STest fixture({"a+|bb", "ab|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 8, 0},
    {8, 10, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {19, 21, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest78") {
  STest fixture({"(a?)", "a*a+"});
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

TEST_CASE("autoMultipatternSearchTest79") {
  STest fixture({"a+?|b|c", "a*|ab"});
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

TEST_CASE("autoMultipatternSearchTest80") {
  STest fixture({"a*|b|c", "a|aba"});
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

TEST_CASE("autoMultipatternSearchTest81") {
  STest fixture({"ab|c?", "a+?|a"});
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

TEST_CASE("autoMultipatternSearchTest82") {
  STest fixture({"a|bac", "a|b|a+?"});
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
    {15, 18, 0},
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

TEST_CASE("autoMultipatternSearchTest83") {
  STest fixture({"a+a*", "a??a??"});
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

TEST_CASE("autoMultipatternSearchTest84") {
  STest fixture({"a+|a|b", "a|b|a|c"});
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
    {6, 7, 1},
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
    {12, 13, 1},
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
    {21, 22, 1},
    {22, 23, 1},
    {23, 24, 0},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest85") {
  STest fixture({"a+|b|a", "a*?a|b"});
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

TEST_CASE("autoMultipatternSearchTest86") {
  STest fixture({"a*a+", "a?a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
    {4, 6, 0},
    {4, 6, 1},
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

TEST_CASE("autoMultipatternSearchTest87") {
  STest fixture({"a|bc|b", "a*|b*"});
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
    {11, 13, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest88") {
  STest fixture({"a+?|b?", "(a)|(b)"});
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

TEST_CASE("autoMultipatternSearchTest89") {
  STest fixture({"a*a??", "a??|a|a"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest90") {
  STest fixture({"a|a|b*", "a|b"});
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

TEST_CASE("autoMultipatternSearchTest91") {
  STest fixture({"a??|a??", "a?|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest92") {
  STest fixture({"a|abb", "a|ba??"});
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

TEST_CASE("autoMultipatternSearchTest93") {
  STest fixture({"a+|a*", "a*?|(a)"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest94") {
  STest fixture({"a|b|(b)", "aa|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {2, 3, 1},
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

TEST_CASE("autoMultipatternSearchTest95") {
  STest fixture({"a??b?", "aaa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {3, 4, 1},
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

TEST_CASE("autoMultipatternSearchTest96") {
  STest fixture({"a|a|a?", "a*?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest97") {
  STest fixture({"aa|a|a", "a*|b+?"});
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

TEST_CASE("autoMultipatternSearchTest98") {
  STest fixture({"a*?|b|c", "a|aa|a"});
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

TEST_CASE("autoMultipatternSearchTest99") {
  STest fixture({"a|b|c*?", "abb|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {6, 7, 1},
    {7, 10, 1},
    {12, 13, 1},
    {14, 15, 1},
    {17, 18, 1},
    {18, 19, 1},
    {22, 23, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest100") {
  STest fixture({"abb*", "a??|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest101") {
  STest fixture({"(a?)", "aaa*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest102") {
  STest fixture({"ab|bb", "ab|c."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {2, 4, 1},
    {6, 8, 1},
    {7, 9, 0},
    {10, 12, 0},
    {10, 12, 1},
    {12, 14, 1},
    {14, 16, 1},
    {17, 19, 1},
    {19, 21, 0},
    {22, 24, 1},
    {24, 26, 1},
    {26, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest103") {
  STest fixture({"a|a??", "a+?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest104") {
  STest fixture({"a", "aa"});
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

TEST_CASE("autoMultipatternSearchTest105") {
  STest fixture({"aa|a|a", "a+|a"});
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

TEST_CASE("autoMultipatternSearchTest106") {
  STest fixture({"a|ab+", "a|a??"});
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

TEST_CASE("autoMultipatternSearchTest107") {
  STest fixture({"a|b|c|.", "a??a+?"});
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

TEST_CASE("autoMultipatternSearchTest108") {
  STest fixture({"aa|(a)", "a|b|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
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

TEST_CASE("autoMultipatternSearchTest109") {
  STest fixture({"aa|a|b", "a|b|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
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

TEST_CASE("autoMultipatternSearchTest110") {
  STest fixture({"a*b", "aa*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest111") {
  STest fixture({"a?aa", "a+a??"});
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

TEST_CASE("autoMultipatternSearchTest112") {
  STest fixture({"aaa*", "a*a+"});
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

TEST_CASE("autoMultipatternSearchTest113") {
  STest fixture({"aa|bb", "ab|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest114") {
  STest fixture({"a+?|ab", "ab+?"});
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

TEST_CASE("autoMultipatternSearchTest115") {
  STest fixture({"a+?", "(a)*"});
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

TEST_CASE("autoMultipatternSearchTest116") {
  STest fixture({"a|b|ab", "aab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {1, 4, 1},
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

TEST_CASE("autoMultipatternSearchTest117") {
  STest fixture({"a??a?", "a*?ab"});
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

TEST_CASE("autoMultipatternSearchTest118") {
  STest fixture({"a??|(a)", "a|a|b+?"});
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

TEST_CASE("autoMultipatternSearchTest119") {
  STest fixture({"a*?|b??", "a|abc"});
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

TEST_CASE("autoMultipatternSearchTest120") {
  STest fixture({"a*?|b|c", "a+?|a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest121") {
  STest fixture({"a|b*", "(a)(b)"});
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

TEST_CASE("autoMultipatternSearchTest122") {
  STest fixture({"a+?b", "a|aba"});
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
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest123") {
  STest fixture({"aa(a)", "a|b|a|b"});
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

TEST_CASE("autoMultipatternSearchTest124") {
  STest fixture({"a|a|ba", "a?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {3, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {7, 10, 1},
    {9, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {15, 16, 1},
    {15, 17, 0},
    {19, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest125") {
  STest fixture({"a|bbc", "ab|a|b"});
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
    {7, 8, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 11, 0},
    {10, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {19, 20, 1},
    {20, 21, 1},
    {20, 23, 0},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest126") {
  STest fixture({"a|aa*", "abc|."});
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
    {10, 13, 1},
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

TEST_CASE("autoMultipatternSearchTest127") {
  STest fixture({"aa|ab", "(a)(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 2, 1},
    {2, 4, 0},
    {4, 6, 0},
    {4, 6, 1},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest128") {
  STest fixture({"a+?|(b)", "a+?b"});
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

TEST_CASE("autoMultipatternSearchTest129") {
  STest fixture({"a?b|b", "aaba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {1, 5, 1},
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

TEST_CASE("autoMultipatternSearchTest130") {
  STest fixture({"a|ba+", "a+|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 4, 1},
    {3, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {9, 11, 0},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 1},
    {15, 17, 0},
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

TEST_CASE("autoMultipatternSearchTest131") {
  STest fixture({"a*|(b)", "a?a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest132") {
  STest fixture({"a+|a*", "a|ba*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {3, 6, 1},
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

TEST_CASE("autoMultipatternSearchTest133") {
  STest fixture({"a??|a*?", "abb??"});
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

TEST_CASE("autoMultipatternSearchTest134") {
  STest fixture({"a+a??", "a+?|a"});
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

TEST_CASE("autoMultipatternSearchTest135") {
  STest fixture({"a*?|b?", "a*?ab"});
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

TEST_CASE("autoMultipatternSearchTest136") {
  STest fixture({"aa+", "a+bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 10, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest137") {
  STest fixture({"a|a(b)", "a+?|b|b"});
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

TEST_CASE("autoMultipatternSearchTest138") {
  STest fixture({"a?bc", "a|a|a+"});
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
    {10, 13, 0},
    {13, 14, 1},
    {16, 17, 1},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest139") {
  STest fixture({"a+?b|b", "a+|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest140") {
  STest fixture({"aba+", "aaa+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest141") {
  STest fixture({"a*|b*", "a|aa|a"});
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

TEST_CASE("autoMultipatternSearchTest142") {
  STest fixture({"abb|a", "a?|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 10, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest143") {
  STest fixture({"a+?b+?", "a+|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
    {4, 6, 1},
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

TEST_CASE("autoMultipatternSearchTest144") {
  STest fixture({"a*?a*", "a|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest145") {
  STest fixture({"a|ba", "ab|ca"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {2, 4, 1},
    {3, 5, 0},
    {5, 6, 0},
    {6, 8, 1},
    {7, 8, 0},
    {9, 11, 0},
    {10, 12, 1},
    {12, 14, 1},
    {13, 14, 0},
    {15, 17, 0},
    {26, 28, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest146") {
  STest fixture({"a?|b+?", "ab|bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 1},
    {7, 9, 1},
    {10, 12, 1},
    {19, 21, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest147") {
  STest fixture({"aaa*?", "abca"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {10, 14, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest148") {
  STest fixture({"a+?|b??", "a*?|a+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest149") {
  STest fixture({"aba*?", "a+?a??"});
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
    {10, 12, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest150") {
  STest fixture({"ab|c?", "aaa?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest151") {
  STest fixture({"a|b*", "a|bbc"});
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
    {20, 23, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest152") {
  STest fixture({"a+|b", "a|baa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 0},
    {3, 6, 1},
    {4, 6, 0},
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

TEST_CASE("autoMultipatternSearchTest153") {
  STest fixture({"a+bb", "a?|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest154") {
  STest fixture({"a|b|bc", "a*?|b?"});
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

TEST_CASE("autoMultipatternSearchTest155") {
  STest fixture({"a|b?", "a+a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
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

TEST_CASE("autoMultipatternSearchTest156") {
  STest fixture({"a?|a+?", "a*|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest157") {
  STest fixture({"a|b|c+?", "a+|aa"});
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

TEST_CASE("autoMultipatternSearchTest158") {
  STest fixture({"a|b|b*", "aaa+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest159") {
  STest fixture({"a|a(a)", "ab|c."});
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
    {6, 8, 1},
    {7, 8, 0},
    {10, 11, 0},
    {10, 12, 1},
    {12, 14, 1},
    {13, 14, 0},
    {14, 16, 1},
    {16, 17, 0},
    {17, 19, 1},
    {22, 24, 1},
    {24, 26, 1},
    {26, 28, 1},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest160") {
  STest fixture({"a*(b)", "a|a*?"});
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

TEST_CASE("autoMultipatternSearchTest161") {
  STest fixture({"a+ab", "a?aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest162") {
  STest fixture({"a+|b+?", "(a)"});
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

TEST_CASE("autoMultipatternSearchTest163") {
  STest fixture({"a+ba", "a+?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest164") {
  STest fixture({"ab|c", "a??|b|c"});
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

TEST_CASE("autoMultipatternSearchTest165") {
  STest fixture({"a|a|b??", "a|b|a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest166") {
  STest fixture({"aab*?", "(a|b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
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

TEST_CASE("autoMultipatternSearchTest167") {
  STest fixture({"a|ba+?", "aab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {1, 4, 1},
    {2, 3, 0},
    {3, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {9, 11, 0},
    {13, 14, 0},
    {15, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest168") {
  STest fixture({"abcc", "a|bc+?"});
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
    {11, 13, 1},
    {13, 14, 1},
    {16, 17, 1},
    {21, 23, 1},
    {23, 25, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest169") {
  STest fixture({"a|a|a+?", "a*?|b+?"});
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

TEST_CASE("autoMultipatternSearchTest170") {
  STest fixture({"a*?", "a|ab"});
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

TEST_CASE("autoMultipatternSearchTest171") {
  STest fixture({"a+bb", "a|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest172") {
  STest fixture({"a+ab", "ab|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest173") {
  STest fixture({"a?b+?", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {2, 4, 0},
    {4, 6, 1},
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

TEST_CASE("autoMultipatternSearchTest174") {
  STest fixture({"a*a?", "a+|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {3, 4, 1},
    {4, 6, 1},
    {7, 8, 1},
    {8, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest175") {
  STest fixture({"a*?(a)", "a|aa|b"});
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

TEST_CASE("autoMultipatternSearchTest176") {
  STest fixture({"a?|aa", "a+b??"});
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

TEST_CASE("autoMultipatternSearchTest177") {
  STest fixture({"aa|a", "aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 2, 1},
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

TEST_CASE("autoMultipatternSearchTest178") {
  STest fixture({"a*|ab", "a|b|(a)"});
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

TEST_CASE("autoMultipatternSearchTest179") {
  STest fixture({"a?|b??", "a*?a?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest180") {
  STest fixture({"a|b|(b)", "a??b*"});
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

TEST_CASE("autoMultipatternSearchTest181") {
  STest fixture({"a*?|b+", "a*?|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest182") {
  STest fixture({"ab|ac", "a|a|b+"});
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
    {5, 7, 0},
    {7, 8, 1},
    {7, 9, 0},
    {8, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {13, 14, 1},
    {13, 15, 0},
    {15, 16, 1},
    {16, 17, 1},
    {16, 18, 0},
    {19, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest183") {
  STest fixture({"a|ba?", "a+b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 5, 0},
    {4, 6, 1},
    {5, 6, 0},
    {7, 8, 0},
    {7, 8, 1},
    {8, 9, 0},
    {9, 11, 0},
    {10, 11, 1},
    {11, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 17, 0},
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

TEST_CASE("autoMultipatternSearchTest184") {
  STest fixture({"a|bcc", "a?|ab"});
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
    {23, 26, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest185") {
  STest fixture({"ab|(a)", "a*|(b)"});
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

TEST_CASE("autoMultipatternSearchTest186") {
  STest fixture({"a*?b|a", "aab|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {1, 4, 1},
    {4, 5, 0},
    {5, 6, 0},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 0},
    {9, 10, 1},
    {10, 12, 0},
    {11, 12, 1},
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

TEST_CASE("autoMultipatternSearchTest187") {
  STest fixture({"a|b|b?", "a+?|b|b"});
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

TEST_CASE("autoMultipatternSearchTest188") {
  STest fixture({"ab|aa", "a|b|c|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {2, 4, 0},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
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

TEST_CASE("autoMultipatternSearchTest189") {
  STest fixture({"a|ba*", "ab|c|a"});
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
    {3, 6, 0},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 1},
    {7, 8, 0},
    {7, 9, 1},
    {8, 9, 0},
    {9, 11, 0},
    {10, 12, 1},
    {11, 12, 0},
    {12, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {15, 17, 0},
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

TEST_CASE("autoMultipatternSearchTest190") {
  STest fixture({"aaab", "a??b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoMultipatternSearchTest191") {
  STest fixture({"a|b|(a)", "a?|b*?"});
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

TEST_CASE("autoMultipatternSearchTest192") {
  STest fixture({"a|b|cb", "a|b|c|b"});
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
    {6, 7, 1},
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
    {12, 13, 1},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 1},
    {14, 16, 0},
    {15, 16, 1},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 1},
    {18, 19, 1},
    {18, 20, 0},
    {19, 20, 1},
    {20, 21, 0},
    {20, 21, 1},
    {21, 22, 0},
    {21, 22, 1},
    {22, 23, 1},
    {22, 24, 0},
    {23, 24, 1},
    {24, 25, 1},
    {25, 26, 1},
    {26, 27, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest193") {
  STest fixture({"a+|bc", "ab?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
    {1, 2, 1},
    {2, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 0},
    {7, 9, 1},
    {10, 11, 0},
    {10, 12, 1},
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

TEST_CASE("autoMultipatternSearchTest194") {
  STest fixture({"a??|a+?", "a??ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {1, 4, 1},
    {7, 9, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest195") {
  STest fixture({"a|bc|c", "a+?b?"});
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
    {7, 9, 1},
    {10, 11, 0},
    {10, 12, 1},
    {11, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {14, 15, 0},
    {16, 17, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {21, 23, 0},
    {23, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest196") {
  STest fixture({"a+?ba", "a??|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest197") {
  STest fixture({"a?|a|b", "a*|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest198") {
  STest fixture({"aba|b", "a*?a??"});
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

TEST_CASE("autoMultipatternSearchTest199") {
  STest fixture({"a??|a*?", "abcb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest200") {
  STest fixture({"a|baa", "aaa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
    {1, 2, 0},
    {2, 3, 0},
    {3, 6, 0},
    {4, 6, 1},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest201") {
  STest fixture({"a?|bb", "a|b|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest202") {
  STest fixture({"aa|b|b", "ab(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 5, 1},
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

TEST_CASE("autoMultipatternSearchTest203") {
  STest fixture({"a?|a|b", "a?a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest204") {
  STest fixture({"ab|b|c", "a+aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
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

TEST_CASE("autoMultipatternSearchTest205") {
  STest fixture({"a??|bc", "(a+?)"});
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

TEST_CASE("autoMultipatternSearchTest206") {
  STest fixture({"ab|bb", "a+?|b+?"});
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
    {7, 8, 1},
    {7, 9, 0},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {10, 12, 0},
    {11, 12, 1},
    {13, 14, 1},
    {15, 16, 1},
    {16, 17, 1},
    {19, 20, 1},
    {19, 21, 0},
    {20, 21, 1},
    {21, 22, 1},
    {23, 24, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest207") {
  STest fixture({"a|aa+?", "ab|a?"});
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

TEST_CASE("autoMultipatternSearchTest208") {
  STest fixture({"a??|a+", "abb*?"});
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

TEST_CASE("autoMultipatternSearchTest209") {
  STest fixture({"ab??", "a+b?"});
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
    {7, 9, 1},
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

TEST_CASE("autoMultipatternSearchTest210") {
  STest fixture({"a+b+", "a??a+?"});
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
    {7, 10, 0},
    {10, 11, 1},
    {10, 12, 0},
    {13, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest211") {
  STest fixture({"(a)(a)", "a+?bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {10, 13, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest212") {
  STest fixture({"a??aa", "a|bca"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 1},
    {4, 5, 1},
    {4, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {10, 11, 1},
    {11, 14, 1},
    {16, 17, 1},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest213") {
  STest fixture({"a+?a?", "a|a|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
    {1, 2, 1},
    {2, 3, 0},
    {2, 3, 1},
    {3, 4, 1},
    {4, 5, 1},
    {4, 6, 0},
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

TEST_CASE("autoMultipatternSearchTest214") {
  STest fixture({"a??ba", "a+?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {2, 5, 0},
    {7, 10, 1},
    {9, 11, 0},
    {10, 12, 1},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest215") {
  STest fixture({"a|b|aa", "a*bb"});
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
    {7, 10, 1},
    {8, 9, 0},
    {9, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 20, 0},
    {19, 21, 1},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest216") {
  STest fixture({"a|aa??", "aaa+"});
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

TEST_CASE("autoMultipatternSearchTest217") {
  STest fixture({"a?|a?", "a*a|a"});
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

TEST_CASE("autoMultipatternSearchTest218") {
  STest fixture({"ab|a|b", "a|ba+?"});
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
    {3, 5, 1},
    {4, 5, 0},
    {5, 6, 0},
    {5, 6, 1},
    {7, 8, 1},
    {7, 9, 0},
    {9, 10, 0},
    {9, 11, 1},
    {10, 12, 0},
    {13, 14, 0},
    {13, 14, 1},
    {15, 16, 0},
    {15, 17, 1},
    {16, 17, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest219") {
  STest fixture({"aab+?", "a+?a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {1, 4, 0},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest220") {
  STest fixture({"a|ab*", "a*b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
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

TEST_CASE("autoMultipatternSearchTest221") {
  STest fixture({"a*ab", "ab|ac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {2, 4, 1},
    {5, 7, 1},
    {7, 9, 0},
    {7, 9, 1},
    {10, 12, 0},
    {10, 12, 1},
    {13, 15, 1},
    {16, 18, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest222") {
  STest fixture({"a|b|b|a", "(a)|(a)"});
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

TEST_CASE("autoMultipatternSearchTest223") {
  STest fixture({"a?aa", "a|ba+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
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

TEST_CASE("autoMultipatternSearchTest224") {
  STest fixture({"ab|c|c", "a|b|a??"});
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

TEST_CASE("autoMultipatternSearchTest225") {
  STest fixture({"a?|bb", "a*|b+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest226") {
  STest fixture({"a+|ab", "a?b*?"});
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

TEST_CASE("autoMultipatternSearchTest227") {
  STest fixture({"aab*", "(a*)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest228") {
  STest fixture({"abac", "a|b|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest229") {
  STest fixture({"a+|b*?", "a|b|c."});
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
    {6, 8, 1},
    {8, 9, 1},
    {9, 10, 1},
    {10, 11, 1},
    {11, 12, 1},
    {12, 14, 1},
    {14, 16, 1},
    {16, 17, 1},
    {17, 19, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {22, 24, 1},
    {24, 26, 1},
    {26, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest230") {
  STest fixture({"aba|c", "a|ab|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {1, 2, 1},
    {2, 3, 1},
    {2, 5, 0},
    {4, 5, 1},
    {5, 6, 1},
    {6, 7, 0},
    {7, 8, 1},
    {10, 11, 1},
    {12, 13, 0},
    {13, 14, 1},
    {14, 15, 0},
    {16, 17, 1},
    {17, 18, 0},
    {18, 19, 0},
    {22, 23, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest231") {
  STest fixture({"a+|ab", "aab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {1, 4, 1},
    {4, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest232") {
  STest fixture({"aa(b)", "a*?|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest233") {
  STest fixture({"a|bc.", "a|abc"});
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
    {11, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {21, 24, 0},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest234") {
  STest fixture({"a|b(b)", "a|bab"});
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
    {9, 12, 1},
    {10, 11, 0},
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

TEST_CASE("autoMultipatternSearchTest235") {
  STest fixture({"aa|bc", "a?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 1},
    {4, 6, 0},
    {7, 9, 1},
    {9, 10, 1},
    {10, 12, 1},
    {11, 13, 0},
    {15, 16, 1},
    {19, 20, 1},
    {20, 21, 1},
    {21, 22, 1},
    {21, 23, 0},
    {23, 24, 1},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest236") {
  STest fixture({"a|b|(b)", "a|a|a??"});
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

TEST_CASE("autoMultipatternSearchTest237") {
  STest fixture({"ab|c|a", "(a?)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 9, 0},
    {10, 12, 0},
    {12, 13, 0},
    {13, 14, 0},
    {14, 15, 0},
    {16, 17, 0},
    {17, 18, 0},
    {18, 19, 0},
    {22, 23, 0},
    {24, 25, 0},
    {25, 26, 0},
    {26, 27, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest238") {
  STest fixture({"((a))", "a+b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
    {1, 2, 0},
    {2, 3, 0},
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

TEST_CASE("autoMultipatternSearchTest239") {
  STest fixture({"a|b|a*?", "a??|a+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternSearchTest240") {
  STest fixture({"aab", "a*a?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest241") {
  STest fixture({"a+|b*?", "a+?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {7, 10, 1},
    {10, 12, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest242") {
  STest fixture({"a?aa", "a*|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest243") {
  STest fixture({"a|bb+?", "abbc"});
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
    {8, 10, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {19, 21, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest244") {
  STest fixture({"abc|a", "a+|a+"});
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
    {10, 11, 1},
    {10, 13, 0},
    {13, 14, 0},
    {13, 14, 1},
    {16, 17, 0},
    {16, 17, 1},
    {27, 28, 0},
    {27, 28, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest245") {
  STest fixture({"a+?|a??", "abb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {7, 10, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest246") {
  STest fixture({"ab|a+?", "a?|(a)"});
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

TEST_CASE("autoMultipatternSearchTest247") {
  STest fixture({"a+b+", "ab|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest248") {
  STest fixture({"ab|c*", "aab*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {4, 6, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternSearchTest249") {
  STest fixture({"a??bb", "ab|c+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {2, 4, 1},
    {6, 7, 1},
    {7, 9, 1},
    {7, 10, 0},
    {10, 12, 1},
    {12, 13, 1},
    {14, 15, 1},
    {17, 19, 1},
    {19, 21, 0},
    {22, 23, 1},
    {24, 27, 1},
  };
  REQUIRE(expected == fixture.Hits);
}
