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

#include <catch2/catch_test_macros.hpp>

#include "stest.h"

TEST_CASE("autoPatternSearchTest250") {
  STest fixture(R"(aa|b+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 4, 0},
    {4, 6, 0},
    {8, 10, 0},
    {11, 12, 0},
    {15, 16, 0},
    {19, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest251") {
  STest fixture(R"(aa|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest252") {
  STest fixture(R"(aa|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest253") {
  STest fixture(R"(aa|b+?)");
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

TEST_CASE("autoPatternSearchTest254") {
  STest fixture(R"(aa|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest255") {
  STest fixture(R"(aa|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest256") {
  STest fixture(R"(aa|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest257") {
  STest fixture(R"(aa|b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest258") {
  STest fixture(R"(aa|b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 4, 0},
    {4, 6, 0},
    {8, 10, 0},
    {11, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest259") {
  STest fixture(R"(aa|b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest260") {
  STest fixture(R"(aa|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest261") {
  STest fixture(R"(aa|b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest262") {
  STest fixture(R"(aa|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest263") {
  STest fixture(R"(aa|b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest264") {
  STest fixture(R"(ab|b+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest265") {
  STest fixture(R"(ab|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest266") {
  STest fixture(R"(ab|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest267") {
  STest fixture(R"(ab|b+?)");
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

TEST_CASE("autoPatternSearchTest268") {
  STest fixture(R"(ab|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest269") {
  STest fixture(R"(ab|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest270") {
  STest fixture(R"(ab|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest271") {
  STest fixture(R"(ab|b{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest272") {
  STest fixture(R"(ab|b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
    {15, 16, 0},
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest273") {
  STest fixture(R"(ab|b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest274") {
  STest fixture(R"(ab|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest275") {
  STest fixture(R"(ab|b{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest276") {
  STest fixture(R"(ab|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest277") {
  STest fixture(R"(ab|b{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest278") {
  STest fixture(R"(ab|c+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 7, 0},
    {7, 9, 0},
    {10, 12, 0},
    {12, 13, 0},
    {14, 15, 0},
    {17, 19, 0},
    {22, 23, 0},
    {24, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest279") {
  STest fixture(R"(ab|c*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest280") {
  STest fixture(R"(ab|c?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest281") {
  STest fixture(R"(ab|c+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest282") {
  STest fixture(R"(ab|c*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest283") {
  STest fixture(R"(ab|c??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest284") {
  STest fixture(R"(ab|c{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest285") {
  STest fixture(R"(ab|c{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {17, 19, 0},
    {24, 26, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest286") {
  STest fixture(R"(ab|c{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 7, 0},
    {7, 9, 0},
    {10, 12, 0},
    {12, 13, 0},
    {14, 15, 0},
    {17, 19, 0},
    {22, 23, 0},
    {24, 26, 0},
    {26, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest287") {
  STest fixture(R"(ab|c{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {17, 19, 0},
    {24, 27, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest288") {
  STest fixture(R"(ab|c{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest289") {
  STest fixture(R"(ab|c{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {17, 19, 0},
    {24, 26, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest290") {
  STest fixture(R"(ab|c{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest291") {
  STest fixture(R"(ab|c{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {17, 19, 0},
    {24, 26, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest292") {
  STest fixture(R"(aa|a|a)");
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

TEST_CASE("autoPatternSearchTest293") {
  STest fixture(R"(ab|a|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest294") {
  STest fixture(R"(aa|b|a)");
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

TEST_CASE("autoPatternSearchTest295") {
  STest fixture(R"(ab|b|a)");
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

TEST_CASE("autoPatternSearchTest296") {
  STest fixture(R"(ab|c|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest297") {
  STest fixture(R"(aa|a|b)");
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

TEST_CASE("autoPatternSearchTest298") {
  STest fixture(R"(ab|a|b)");
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

TEST_CASE("autoPatternSearchTest299") {
  STest fixture(R"(aa|b|b)");
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

TEST_CASE("autoPatternSearchTest300") {
  STest fixture(R"(ab|b|b)");
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

TEST_CASE("autoPatternSearchTest301") {
  STest fixture(R"(ab|c|b)");
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

TEST_CASE("autoPatternSearchTest302") {
  STest fixture(R"(ab|a|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest303") {
  STest fixture(R"(aa|b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {3, 4, 0},
    {4, 6, 0},
    {6, 7, 0},
    {8, 9, 0},
    {9, 10, 0},
    {11, 12, 0},
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

TEST_CASE("autoPatternSearchTest304") {
  STest fixture(R"(ab|b|c)");
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

TEST_CASE("autoPatternSearchTest305") {
  STest fixture(R"(ab|c|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest306") {
  STest fixture(R"(ab|c|.)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {6, 7, 0},
    {7, 9, 0},
    {9, 10, 0},
    {10, 12, 0},
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

TEST_CASE("autoPatternSearchTest307") {
  STest fixture(R"(a+)");
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

TEST_CASE("autoPatternSearchTest308") {
  STest fixture(R"(a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest309") {
  STest fixture(R"(a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest310") {
  STest fixture(R"(a+?)");
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

TEST_CASE("autoPatternSearchTest311") {
  STest fixture(R"(a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest312") {
  STest fixture(R"(a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest313") {
  STest fixture(R"(a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest314") {
  STest fixture(R"(a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest315") {
  STest fixture(R"(a{1,2})");
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

TEST_CASE("autoPatternSearchTest316") {
  STest fixture(R"(a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest317") {
  STest fixture(R"(a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest318") {
  STest fixture(R"(a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest319") {
  STest fixture(R"(a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest320") {
  STest fixture(R"(a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest321") {
  STest fixture(R"(a+(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest322") {
  STest fixture(R"(a*(a))");
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

TEST_CASE("autoPatternSearchTest323") {
  STest fixture(R"(a?(a))");
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

TEST_CASE("autoPatternSearchTest324") {
  STest fixture(R"(a+?(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest325") {
  STest fixture(R"(a*?(a))");
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

TEST_CASE("autoPatternSearchTest326") {
  STest fixture(R"(a??(a))");
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

TEST_CASE("autoPatternSearchTest327") {
  STest fixture(R"(a{0,1}(a))");
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

TEST_CASE("autoPatternSearchTest328") {
  STest fixture(R"(a{2}(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest329") {
  STest fixture(R"(a{1,2}(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest330") {
  STest fixture(R"(a{2,}(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest331") {
  STest fixture(R"(a{0,1}?(a))");
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

TEST_CASE("autoPatternSearchTest332") {
  STest fixture(R"(a{2}?(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest333") {
  STest fixture(R"(a{1,2}?(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest334") {
  STest fixture(R"(a{2,}?(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest335") {
  STest fixture(R"(a+(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest336") {
  STest fixture(R"(a*(b))");
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

TEST_CASE("autoPatternSearchTest337") {
  STest fixture(R"(a?(b))");
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

TEST_CASE("autoPatternSearchTest338") {
  STest fixture(R"(a+?(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest339") {
  STest fixture(R"(a*?(b))");
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

TEST_CASE("autoPatternSearchTest340") {
  STest fixture(R"(a??(b))");
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

TEST_CASE("autoPatternSearchTest341") {
  STest fixture(R"(a{0,1}(b))");
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

TEST_CASE("autoPatternSearchTest342") {
  STest fixture(R"(a{2}(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest343") {
  STest fixture(R"(a{1,2}(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest344") {
  STest fixture(R"(a{2,}(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest345") {
  STest fixture(R"(a{0,1}?(b))");
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

TEST_CASE("autoPatternSearchTest346") {
  STest fixture(R"(a{2}?(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest347") {
  STest fixture(R"(a{1,2}?(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest348") {
  STest fixture(R"(a{2,}?(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest349") {
  STest fixture(R"(a+a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest350") {
  STest fixture(R"(a*a)");
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

TEST_CASE("autoPatternSearchTest351") {
  STest fixture(R"(a?a)");
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

TEST_CASE("autoPatternSearchTest352") {
  STest fixture(R"(a+?a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest353") {
  STest fixture(R"(a*?a)");
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

TEST_CASE("autoPatternSearchTest354") {
  STest fixture(R"(a??a)");
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

TEST_CASE("autoPatternSearchTest355") {
  STest fixture(R"(a{0,1}a)");
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

TEST_CASE("autoPatternSearchTest356") {
  STest fixture(R"(a{2}a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest357") {
  STest fixture(R"(a{1,2}a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest358") {
  STest fixture(R"(a{2,}a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest359") {
  STest fixture(R"(a{0,1}?a)");
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

TEST_CASE("autoPatternSearchTest360") {
  STest fixture(R"(a{2}?a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest361") {
  STest fixture(R"(a{1,2}?a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest362") {
  STest fixture(R"(a{2,}?a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest363") {
  STest fixture(R"(a+b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest364") {
  STest fixture(R"(a*b)");
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

TEST_CASE("autoPatternSearchTest365") {
  STest fixture(R"(a?b)");
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

TEST_CASE("autoPatternSearchTest366") {
  STest fixture(R"(a+?b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest367") {
  STest fixture(R"(a*?b)");
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

TEST_CASE("autoPatternSearchTest368") {
  STest fixture(R"(a??b)");
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

TEST_CASE("autoPatternSearchTest369") {
  STest fixture(R"(a{0,1}b)");
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

TEST_CASE("autoPatternSearchTest370") {
  STest fixture(R"(a{2}b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest371") {
  STest fixture(R"(a{1,2}b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest372") {
  STest fixture(R"(a{2,}b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest373") {
  STest fixture(R"(a{0,1}?b)");
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

TEST_CASE("autoPatternSearchTest374") {
  STest fixture(R"(a{2}?b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest375") {
  STest fixture(R"(a{1,2}?b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest376") {
  STest fixture(R"(a{2,}?b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest377") {
  STest fixture(R"(a+aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest378") {
  STest fixture(R"(a*aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest379") {
  STest fixture(R"(a?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest380") {
  STest fixture(R"(a+?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest381") {
  STest fixture(R"(a*?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest382") {
  STest fixture(R"(a??aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest383") {
  STest fixture(R"(a{0,1}aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest384") {
  STest fixture(R"(a{2}aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest385") {
  STest fixture(R"(a{1,2}aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest386") {
  STest fixture(R"(a{2,}aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest387") {
  STest fixture(R"(a{0,1}?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest388") {
  STest fixture(R"(a{2}?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest389") {
  STest fixture(R"(a{1,2}?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest390") {
  STest fixture(R"(a{2,}?aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest391") {
  STest fixture(R"(a+ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest392") {
  STest fixture(R"(a*ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest393") {
  STest fixture(R"(a?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest394") {
  STest fixture(R"(a+?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest395") {
  STest fixture(R"(a*?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest396") {
  STest fixture(R"(a??ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest397") {
  STest fixture(R"(a{0,1}ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest398") {
  STest fixture(R"(a{2}ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest399") {
  STest fixture(R"(a{1,2}ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest400") {
  STest fixture(R"(a{2,}ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest401") {
  STest fixture(R"(a{0,1}?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest402") {
  STest fixture(R"(a{2}?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest403") {
  STest fixture(R"(a{1,2}?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest404") {
  STest fixture(R"(a{2,}?ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest405") {
  STest fixture(R"(a+ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest406") {
  STest fixture(R"(a*ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest407") {
  STest fixture(R"(a?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest408") {
  STest fixture(R"(a+?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest409") {
  STest fixture(R"(a*?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest410") {
  STest fixture(R"(a??ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest411") {
  STest fixture(R"(a{0,1}ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest412") {
  STest fixture(R"(a{2}ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest413") {
  STest fixture(R"(a{1,2}ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest414") {
  STest fixture(R"(a{2,}ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest415") {
  STest fixture(R"(a{0,1}?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest416") {
  STest fixture(R"(a{2}?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest417") {
  STest fixture(R"(a{1,2}?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest418") {
  STest fixture(R"(a{2,}?ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest419") {
  STest fixture(R"(a+bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest420") {
  STest fixture(R"(a*bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest421") {
  STest fixture(R"(a?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest422") {
  STest fixture(R"(a+?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest423") {
  STest fixture(R"(a*?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest424") {
  STest fixture(R"(a??bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest425") {
  STest fixture(R"(a{0,1}bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest426") {
  STest fixture(R"(a{2}bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest427") {
  STest fixture(R"(a{1,2}bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest428") {
  STest fixture(R"(a{2,}bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest429") {
  STest fixture(R"(a{0,1}?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest430") {
  STest fixture(R"(a{2}?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest431") {
  STest fixture(R"(a{1,2}?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest432") {
  STest fixture(R"(a{2,}?bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest433") {
  STest fixture(R"(a+bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest434") {
  STest fixture(R"(a*bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest435") {
  STest fixture(R"(a?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest436") {
  STest fixture(R"(a+?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest437") {
  STest fixture(R"(a*?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest438") {
  STest fixture(R"(a??bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest439") {
  STest fixture(R"(a{0,1}bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest440") {
  STest fixture(R"(a{2}bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest441") {
  STest fixture(R"(a{1,2}bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest442") {
  STest fixture(R"(a{2,}bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest443") {
  STest fixture(R"(a{0,1}?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest444") {
  STest fixture(R"(a{2}?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest445") {
  STest fixture(R"(a{1,2}?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest446") {
  STest fixture(R"(a{2,}?bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest447") {
  STest fixture(R"(a+a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest448") {
  STest fixture(R"(a*a+)");
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

TEST_CASE("autoPatternSearchTest449") {
  STest fixture(R"(a?a+)");
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

TEST_CASE("autoPatternSearchTest450") {
  STest fixture(R"(a+?a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest451") {
  STest fixture(R"(a*?a+)");
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

TEST_CASE("autoPatternSearchTest452") {
  STest fixture(R"(a??a+)");
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

TEST_CASE("autoPatternSearchTest453") {
  STest fixture(R"(a{0,1}a+)");
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

TEST_CASE("autoPatternSearchTest454") {
  STest fixture(R"(a{2}a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest455") {
  STest fixture(R"(a{1,2}a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest456") {
  STest fixture(R"(a{2,}a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest457") {
  STest fixture(R"(a{0,1}?a+)");
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

TEST_CASE("autoPatternSearchTest458") {
  STest fixture(R"(a{2}?a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest459") {
  STest fixture(R"(a{1,2}?a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest460") {
  STest fixture(R"(a{2,}?a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest461") {
  STest fixture(R"(a+a*)");
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

TEST_CASE("autoPatternSearchTest462") {
  STest fixture(R"(a*a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest463") {
  STest fixture(R"(a?a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest464") {
  STest fixture(R"(a+?a*)");
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

TEST_CASE("autoPatternSearchTest465") {
  STest fixture(R"(a*?a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest466") {
  STest fixture(R"(a??a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest467") {
  STest fixture(R"(a{0,1}a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest468") {
  STest fixture(R"(a{2}a*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest469") {
  STest fixture(R"(a{1,2}a*)");
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

TEST_CASE("autoPatternSearchTest470") {
  STest fixture(R"(a{2,}a*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest471") {
  STest fixture(R"(a{0,1}?a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest472") {
  STest fixture(R"(a{2}?a*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest473") {
  STest fixture(R"(a{1,2}?a*)");
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

TEST_CASE("autoPatternSearchTest474") {
  STest fixture(R"(a{2,}?a*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest475") {
  STest fixture(R"(a+a?)");
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

TEST_CASE("autoPatternSearchTest476") {
  STest fixture(R"(a*a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest477") {
  STest fixture(R"(a?a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest478") {
  STest fixture(R"(a+?a?)");
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

TEST_CASE("autoPatternSearchTest479") {
  STest fixture(R"(a*?a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest480") {
  STest fixture(R"(a??a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest481") {
  STest fixture(R"(a{0,1}a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest482") {
  STest fixture(R"(a{2}a?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest483") {
  STest fixture(R"(a{1,2}a?)");
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

TEST_CASE("autoPatternSearchTest484") {
  STest fixture(R"(a{2,}a?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest485") {
  STest fixture(R"(a{0,1}?a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest486") {
  STest fixture(R"(a{2}?a?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest487") {
  STest fixture(R"(a{1,2}?a?)");
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

TEST_CASE("autoPatternSearchTest488") {
  STest fixture(R"(a{2,}?a?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest489") {
  STest fixture(R"(a+a+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest490") {
  STest fixture(R"(a*a+?)");
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

TEST_CASE("autoPatternSearchTest491") {
  STest fixture(R"(a?a+?)");
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

TEST_CASE("autoPatternSearchTest492") {
  STest fixture(R"(a+?a+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest493") {
  STest fixture(R"(a*?a+?)");
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

TEST_CASE("autoPatternSearchTest494") {
  STest fixture(R"(a??a+?)");
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

TEST_CASE("autoPatternSearchTest495") {
  STest fixture(R"(a{0,1}a+?)");
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

TEST_CASE("autoPatternSearchTest496") {
  STest fixture(R"(a{2}a+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest497") {
  STest fixture(R"(a{1,2}a+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest498") {
  STest fixture(R"(a{2,}a+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest499") {
  STest fixture(R"(a{0,1}?a+?)");
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
