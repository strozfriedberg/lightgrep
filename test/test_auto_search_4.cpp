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

#include "catch.hpp" 

#include "stest.h"

TEST_CASE("autoPatternSearchTest750") {
  STest fixture(R"(a{2,}b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest751") {
  STest fixture(R"(a{0,1}?b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest752") {
  STest fixture(R"(a{2}?b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest753") {
  STest fixture(R"(a{1,2}?b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest754") {
  STest fixture(R"(a{2,}?b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest755") {
  STest fixture(R"(a+b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest756") {
  STest fixture(R"(a*b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest757") {
  STest fixture(R"(a?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest758") {
  STest fixture(R"(a+?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest759") {
  STest fixture(R"(a*?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest760") {
  STest fixture(R"(a??b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest761") {
  STest fixture(R"(a{0,1}b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest762") {
  STest fixture(R"(a{2}b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest763") {
  STest fixture(R"(a{1,2}b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest764") {
  STest fixture(R"(a{2,}b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest765") {
  STest fixture(R"(a{0,1}?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest766") {
  STest fixture(R"(a{2}?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest767") {
  STest fixture(R"(a{1,2}?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest768") {
  STest fixture(R"(a{2,}?b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest769") {
  STest fixture(R"(a+b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest770") {
  STest fixture(R"(a*b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest771") {
  STest fixture(R"(a?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest772") {
  STest fixture(R"(a+?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest773") {
  STest fixture(R"(a*?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest774") {
  STest fixture(R"(a??b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest775") {
  STest fixture(R"(a{0,1}b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest776") {
  STest fixture(R"(a{2}b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest777") {
  STest fixture(R"(a{1,2}b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest778") {
  STest fixture(R"(a{2,}b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest779") {
  STest fixture(R"(a{0,1}?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest780") {
  STest fixture(R"(a{2}?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest781") {
  STest fixture(R"(a{1,2}?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest782") {
  STest fixture(R"(a{2,}?b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest783") {
  STest fixture(R"(a+b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest784") {
  STest fixture(R"(a*b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest785") {
  STest fixture(R"(a?b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest786") {
  STest fixture(R"(a+?b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest787") {
  STest fixture(R"(a*?b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest788") {
  STest fixture(R"(a??b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest789") {
  STest fixture(R"(a{0,1}b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest790") {
  STest fixture(R"(a{2}b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest791") {
  STest fixture(R"(a{1,2}b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest792") {
  STest fixture(R"(a{2,}b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest793") {
  STest fixture(R"(a{0,1}?b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest794") {
  STest fixture(R"(a{2}?b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest795") {
  STest fixture(R"(a{1,2}?b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest796") {
  STest fixture(R"(a{2,}?b{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest797") {
  STest fixture(R"(a+b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest798") {
  STest fixture(R"(a*b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest799") {
  STest fixture(R"(a?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest800") {
  STest fixture(R"(a+?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest801") {
  STest fixture(R"(a*?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest802") {
  STest fixture(R"(a??b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest803") {
  STest fixture(R"(a{0,1}b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest804") {
  STest fixture(R"(a{2}b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest805") {
  STest fixture(R"(a{1,2}b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest806") {
  STest fixture(R"(a{2,}b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest807") {
  STest fixture(R"(a{0,1}?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest808") {
  STest fixture(R"(a{2}?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest809") {
  STest fixture(R"(a{1,2}?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest810") {
  STest fixture(R"(a{2,}?b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest811") {
  STest fixture(R"(a+b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest812") {
  STest fixture(R"(a*b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest813") {
  STest fixture(R"(a?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest814") {
  STest fixture(R"(a+?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest815") {
  STest fixture(R"(a*?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest816") {
  STest fixture(R"(a??b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest817") {
  STest fixture(R"(a{0,1}b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest818") {
  STest fixture(R"(a{2}b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest819") {
  STest fixture(R"(a{1,2}b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest820") {
  STest fixture(R"(a{2,}b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest821") {
  STest fixture(R"(a{0,1}?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest822") {
  STest fixture(R"(a{2}?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest823") {
  STest fixture(R"(a{1,2}?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest824") {
  STest fixture(R"(a{2,}?b{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest825") {
  STest fixture(R"(a+b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest826") {
  STest fixture(R"(a*b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest827") {
  STest fixture(R"(a?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest828") {
  STest fixture(R"(a+?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest829") {
  STest fixture(R"(a*?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest830") {
  STest fixture(R"(a??b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest831") {
  STest fixture(R"(a{0,1}b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest832") {
  STest fixture(R"(a{2}b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest833") {
  STest fixture(R"(a{1,2}b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest834") {
  STest fixture(R"(a{2,}b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest835") {
  STest fixture(R"(a{0,1}?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest836") {
  STest fixture(R"(a{2}?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest837") {
  STest fixture(R"(a{1,2}?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest838") {
  STest fixture(R"(a{2,}?b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest839") {
  STest fixture(R"(a+a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest840") {
  STest fixture(R"(a*a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest841") {
  STest fixture(R"(a?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest842") {
  STest fixture(R"(a+?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest843") {
  STest fixture(R"(a*?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest844") {
  STest fixture(R"(a??a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest845") {
  STest fixture(R"(a{0,1}a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest846") {
  STest fixture(R"(a{2}a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest847") {
  STest fixture(R"(a{1,2}a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest848") {
  STest fixture(R"(a{2,}a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest849") {
  STest fixture(R"(a{0,1}?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest850") {
  STest fixture(R"(a{2}?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest851") {
  STest fixture(R"(a{1,2}?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest852") {
  STest fixture(R"(a{2,}?a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest853") {
  STest fixture(R"(a+b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest854") {
  STest fixture(R"(a*b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest855") {
  STest fixture(R"(a?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
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

TEST_CASE("autoPatternSearchTest856") {
  STest fixture(R"(a+?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest857") {
  STest fixture(R"(a*?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest858") {
  STest fixture(R"(a??b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
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

TEST_CASE("autoPatternSearchTest859") {
  STest fixture(R"(a{0,1}b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
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

TEST_CASE("autoPatternSearchTest860") {
  STest fixture(R"(a{2}b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
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

TEST_CASE("autoPatternSearchTest861") {
  STest fixture(R"(a{1,2}b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest862") {
  STest fixture(R"(a{2,}b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoPatternSearchTest863") {
  STest fixture(R"(a{0,1}?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
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

TEST_CASE("autoPatternSearchTest864") {
  STest fixture(R"(a{2}?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
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

TEST_CASE("autoPatternSearchTest865") {
  STest fixture(R"(a{1,2}?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest866") {
  STest fixture(R"(a{2,}?b|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoPatternSearchTest867") {
  STest fixture(R"(a+a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest868") {
  STest fixture(R"(a*a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest869") {
  STest fixture(R"(a?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest870") {
  STest fixture(R"(a+?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest871") {
  STest fixture(R"(a*?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest872") {
  STest fixture(R"(a??a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest873") {
  STest fixture(R"(a{0,1}a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest874") {
  STest fixture(R"(a{2}a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest875") {
  STest fixture(R"(a{1,2}a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest876") {
  STest fixture(R"(a{2,}a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest877") {
  STest fixture(R"(a{0,1}?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest878") {
  STest fixture(R"(a{2}?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest879") {
  STest fixture(R"(a{1,2}?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest880") {
  STest fixture(R"(a{2,}?a|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest881") {
  STest fixture(R"(a+b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest882") {
  STest fixture(R"(a*b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest883") {
  STest fixture(R"(a?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest884") {
  STest fixture(R"(a+?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest885") {
  STest fixture(R"(a*?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest886") {
  STest fixture(R"(a??b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest887") {
  STest fixture(R"(a{0,1}b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest888") {
  STest fixture(R"(a{2}b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest889") {
  STest fixture(R"(a{1,2}b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest890") {
  STest fixture(R"(a{2,}b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoPatternSearchTest891") {
  STest fixture(R"(a{0,1}?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest892") {
  STest fixture(R"(a{2}?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest893") {
  STest fixture(R"(a{1,2}?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest894") {
  STest fixture(R"(a{2,}?b|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoPatternSearchTest895") {
  STest fixture(R"(a+b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest896") {
  STest fixture(R"(a*b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoPatternSearchTest897") {
  STest fixture(R"(a?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest898") {
  STest fixture(R"(a+?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest899") {
  STest fixture(R"(a*?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
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

TEST_CASE("autoPatternSearchTest900") {
  STest fixture(R"(a??b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest901") {
  STest fixture(R"(a{0,1}b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest902") {
  STest fixture(R"(a{2}b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {6, 7, 0},
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

TEST_CASE("autoPatternSearchTest903") {
  STest fixture(R"(a{1,2}b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest904") {
  STest fixture(R"(a{2,}b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {6, 7, 0},
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

TEST_CASE("autoPatternSearchTest905") {
  STest fixture(R"(a{0,1}?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest906") {
  STest fixture(R"(a{2}?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {6, 7, 0},
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

TEST_CASE("autoPatternSearchTest907") {
  STest fixture(R"(a{1,2}?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
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

TEST_CASE("autoPatternSearchTest908") {
  STest fixture(R"(a{2,}?b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {6, 7, 0},
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

TEST_CASE("autoPatternSearchTest909") {
  STest fixture(R"(a+|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest910") {
  STest fixture(R"(a*|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest911") {
  STest fixture(R"(a?|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest912") {
  STest fixture(R"(a+?|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest913") {
  STest fixture(R"(a*?|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest914") {
  STest fixture(R"(a??|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest915") {
  STest fixture(R"(a{0,1}|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest916") {
  STest fixture(R"(a{2}|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest917") {
  STest fixture(R"(a{1,2}|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest918") {
  STest fixture(R"(a{2,}|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest919") {
  STest fixture(R"(a{0,1}?|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest920") {
  STest fixture(R"(a{2}?|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest921") {
  STest fixture(R"(a{1,2}?|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest922") {
  STest fixture(R"(a{2,}?|(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest923") {
  STest fixture(R"(a+|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest924") {
  STest fixture(R"(a*|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest925") {
  STest fixture(R"(a?|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest926") {
  STest fixture(R"(a+?|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest927") {
  STest fixture(R"(a*?|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest928") {
  STest fixture(R"(a??|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest929") {
  STest fixture(R"(a{0,1}|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest930") {
  STest fixture(R"(a{2}|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest931") {
  STest fixture(R"(a{1,2}|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest932") {
  STest fixture(R"(a{2,}|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest933") {
  STest fixture(R"(a{0,1}?|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest934") {
  STest fixture(R"(a{2}?|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest935") {
  STest fixture(R"(a{1,2}?|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest936") {
  STest fixture(R"(a{2,}?|(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest937") {
  STest fixture(R"(a+|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest938") {
  STest fixture(R"(a*|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest939") {
  STest fixture(R"(a?|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest940") {
  STest fixture(R"(a+?|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest941") {
  STest fixture(R"(a*?|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest942") {
  STest fixture(R"(a??|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest943") {
  STest fixture(R"(a{0,1}|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest944") {
  STest fixture(R"(a{2}|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest945") {
  STest fixture(R"(a{1,2}|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest946") {
  STest fixture(R"(a{2,}|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest947") {
  STest fixture(R"(a{0,1}?|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest948") {
  STest fixture(R"(a{2}?|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest949") {
  STest fixture(R"(a{1,2}?|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest950") {
  STest fixture(R"(a{2,}?|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest951") {
  STest fixture(R"(a+|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest952") {
  STest fixture(R"(a*|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest953") {
  STest fixture(R"(a?|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest954") {
  STest fixture(R"(a+?|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest955") {
  STest fixture(R"(a*?|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest956") {
  STest fixture(R"(a??|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest957") {
  STest fixture(R"(a{0,1}|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest958") {
  STest fixture(R"(a{2}|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest959") {
  STest fixture(R"(a{1,2}|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest960") {
  STest fixture(R"(a{2,}|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest961") {
  STest fixture(R"(a{0,1}?|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest962") {
  STest fixture(R"(a{2}?|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest963") {
  STest fixture(R"(a{1,2}?|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest964") {
  STest fixture(R"(a{2,}?|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest965") {
  STest fixture(R"(a+|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest966") {
  STest fixture(R"(a*|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest967") {
  STest fixture(R"(a?|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest968") {
  STest fixture(R"(a+?|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest969") {
  STest fixture(R"(a*?|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest970") {
  STest fixture(R"(a??|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest971") {
  STest fixture(R"(a{0,1}|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest972") {
  STest fixture(R"(a{2}|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest973") {
  STest fixture(R"(a{1,2}|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest974") {
  STest fixture(R"(a{2,}|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest975") {
  STest fixture(R"(a{0,1}?|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest976") {
  STest fixture(R"(a{2}?|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest977") {
  STest fixture(R"(a{1,2}?|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest978") {
  STest fixture(R"(a{2,}?|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest979") {
  STest fixture(R"(a+|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest980") {
  STest fixture(R"(a*|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest981") {
  STest fixture(R"(a?|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest982") {
  STest fixture(R"(a+?|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
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

TEST_CASE("autoPatternSearchTest983") {
  STest fixture(R"(a*?|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest984") {
  STest fixture(R"(a??|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest985") {
  STest fixture(R"(a{0,1}|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest986") {
  STest fixture(R"(a{2}|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest987") {
  STest fixture(R"(a{1,2}|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
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

TEST_CASE("autoPatternSearchTest988") {
  STest fixture(R"(a{2,}|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {3, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest989") {
  STest fixture(R"(a{0,1}?|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest990") {
  STest fixture(R"(a{2}?|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest991") {
  STest fixture(R"(a{1,2}?|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
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

TEST_CASE("autoPatternSearchTest992") {
  STest fixture(R"(a{2,}?|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest993") {
  STest fixture(R"(a+|ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest994") {
  STest fixture(R"(a*|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest995") {
  STest fixture(R"(a?|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest996") {
  STest fixture(R"(a+?|ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest997") {
  STest fixture(R"(a*?|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest998") {
  STest fixture(R"(a??|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest999") {
  STest fixture(R"(a{0,1}|ab)");
  REQUIRE(fixture.parsesButNotValid());
}
