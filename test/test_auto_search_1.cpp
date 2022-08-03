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

TEST_CASE("autoPatternSearchTest0") {
  STest fixture(R"(a)");
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

TEST_CASE("autoPatternSearchTest1") {
  STest fixture(R"((a))");
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

TEST_CASE("autoPatternSearchTest2") {
  STest fixture(R"(aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest3") {
  STest fixture(R"(ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest4") {
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

TEST_CASE("autoPatternSearchTest5") {
  STest fixture(R"(a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest6") {
  STest fixture(R"(a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest7") {
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

TEST_CASE("autoPatternSearchTest8") {
  STest fixture(R"(a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest9") {
  STest fixture(R"(a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest10") {
  STest fixture(R"(a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest11") {
  STest fixture(R"(a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest12") {
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

TEST_CASE("autoPatternSearchTest13") {
  STest fixture(R"(a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest14") {
  STest fixture(R"(a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest15") {
  STest fixture(R"(a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest16") {
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

TEST_CASE("autoPatternSearchTest17") {
  STest fixture(R"(a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest18") {
  STest fixture(R"(a|a)");
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

TEST_CASE("autoPatternSearchTest19") {
  STest fixture(R"(a|b)");
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

TEST_CASE("autoPatternSearchTest20") {
  STest fixture(R"((aa))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest21") {
  STest fixture(R"((ab))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest22") {
  STest fixture(R"((a+))");
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

TEST_CASE("autoPatternSearchTest23") {
  STest fixture(R"((a*))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest24") {
  STest fixture(R"((a?))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest25") {
  STest fixture(R"((a+?))");
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

TEST_CASE("autoPatternSearchTest26") {
  STest fixture(R"((a*?))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest27") {
  STest fixture(R"((a??))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest28") {
  STest fixture(R"((a{0,1}))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest29") {
  STest fixture(R"((a{2}))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest30") {
  STest fixture(R"((a{1,2}))");
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

TEST_CASE("autoPatternSearchTest31") {
  STest fixture(R"((a{2,}))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest32") {
  STest fixture(R"((a{0,1}?))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest33") {
  STest fixture(R"((a{2}?))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest34") {
  STest fixture(R"((a{1,2}?))");
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

TEST_CASE("autoPatternSearchTest35") {
  STest fixture(R"((a{2,}?))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest36") {
  STest fixture(R"((a|a))");
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

TEST_CASE("autoPatternSearchTest37") {
  STest fixture(R"((a|b))");
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

TEST_CASE("autoPatternSearchTest38") {
  STest fixture(R"(((a)))");
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

TEST_CASE("autoPatternSearchTest39") {
  STest fixture(R"((a)(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest40") {
  STest fixture(R"((a)(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest41") {
  STest fixture(R"((a)+)");
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

TEST_CASE("autoPatternSearchTest42") {
  STest fixture(R"((a)*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest43") {
  STest fixture(R"((a)?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest44") {
  STest fixture(R"((a)+?)");
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

TEST_CASE("autoPatternSearchTest45") {
  STest fixture(R"((a)*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest46") {
  STest fixture(R"((a)??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest47") {
  STest fixture(R"((a){0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest48") {
  STest fixture(R"((a){2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest49") {
  STest fixture(R"((a){1,2})");
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

TEST_CASE("autoPatternSearchTest50") {
  STest fixture(R"((a){2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest51") {
  STest fixture(R"((a){0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest52") {
  STest fixture(R"((a){2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest53") {
  STest fixture(R"((a){1,2}?)");
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

TEST_CASE("autoPatternSearchTest54") {
  STest fixture(R"((a){2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest55") {
  STest fixture(R"((a)|(a))");
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

TEST_CASE("autoPatternSearchTest56") {
  STest fixture(R"((a)|(b))");
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

TEST_CASE("autoPatternSearchTest57") {
  STest fixture(R"(aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest58") {
  STest fixture(R"(ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest59") {
  STest fixture(R"(aa(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest60") {
  STest fixture(R"(ab(a))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest61") {
  STest fixture(R"(aa(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest62") {
  STest fixture(R"(ab(b))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest63") {
  STest fixture(R"(ab(c))");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest64") {
  STest fixture(R"(aaa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest65") {
  STest fixture(R"(aba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest66") {
  STest fixture(R"(aab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest67") {
  STest fixture(R"(abb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest68") {
  STest fixture(R"(abc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest69") {
  STest fixture(R"(aaaa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest70") {
  STest fixture(R"(abaa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest71") {
  STest fixture(R"(aaba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest72") {
  STest fixture(R"(abba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest73") {
  STest fixture(R"(abca)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 14, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest74") {
  STest fixture(R"(aaab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest75") {
  STest fixture(R"(abab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest76") {
  STest fixture(R"(aabb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest77") {
  STest fixture(R"(abbb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest78") {
  STest fixture(R"(abcb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest79") {
  STest fixture(R"(abac)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest80") {
  STest fixture(R"(aabc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest81") {
  STest fixture(R"(abbc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest82") {
  STest fixture(R"(abcc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest83") {
  STest fixture(R"(abc.)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 14, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest84") {
  STest fixture(R"(aaa+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest85") {
  STest fixture(R"(aaa*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest86") {
  STest fixture(R"(aaa?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest87") {
  STest fixture(R"(aaa+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest88") {
  STest fixture(R"(aaa*?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest89") {
  STest fixture(R"(aaa??)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest90") {
  STest fixture(R"(aaa{0,1})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest91") {
  STest fixture(R"(aaa{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest92") {
  STest fixture(R"(aaa{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest93") {
  STest fixture(R"(aaa{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest94") {
  STest fixture(R"(aaa{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest95") {
  STest fixture(R"(aaa{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest96") {
  STest fixture(R"(aaa{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest97") {
  STest fixture(R"(aaa{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest98") {
  STest fixture(R"(aba+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest99") {
  STest fixture(R"(aba*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest100") {
  STest fixture(R"(aba?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest101") {
  STest fixture(R"(aba+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest102") {
  STest fixture(R"(aba*?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest103") {
  STest fixture(R"(aba??)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest104") {
  STest fixture(R"(aba{0,1})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest105") {
  STest fixture(R"(aba{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest106") {
  STest fixture(R"(aba{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest107") {
  STest fixture(R"(aba{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest108") {
  STest fixture(R"(aba{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest109") {
  STest fixture(R"(aba{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest110") {
  STest fixture(R"(aba{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest111") {
  STest fixture(R"(aba{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest112") {
  STest fixture(R"(aab+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest113") {
  STest fixture(R"(aab*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest114") {
  STest fixture(R"(aab?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest115") {
  STest fixture(R"(aab+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest116") {
  STest fixture(R"(aab*?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest117") {
  STest fixture(R"(aab??)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest118") {
  STest fixture(R"(aab{0,1})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest119") {
  STest fixture(R"(aab{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest120") {
  STest fixture(R"(aab{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest121") {
  STest fixture(R"(aab{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest122") {
  STest fixture(R"(aab{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest123") {
  STest fixture(R"(aab{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest124") {
  STest fixture(R"(aab{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest125") {
  STest fixture(R"(aab{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest126") {
  STest fixture(R"(abb+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest127") {
  STest fixture(R"(abb*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest128") {
  STest fixture(R"(abb?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest129") {
  STest fixture(R"(abb+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest130") {
  STest fixture(R"(abb*?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest131") {
  STest fixture(R"(abb??)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest132") {
  STest fixture(R"(abb{0,1})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest133") {
  STest fixture(R"(abb{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest134") {
  STest fixture(R"(abb{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest135") {
  STest fixture(R"(abb{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest136") {
  STest fixture(R"(abb{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest137") {
  STest fixture(R"(abb{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest138") {
  STest fixture(R"(abb{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest139") {
  STest fixture(R"(abb{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest140") {
  STest fixture(R"(abc+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest141") {
  STest fixture(R"(abc*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest142") {
  STest fixture(R"(abc?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest143") {
  STest fixture(R"(abc+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest144") {
  STest fixture(R"(abc*?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest145") {
  STest fixture(R"(abc??)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest146") {
  STest fixture(R"(abc{0,1})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest147") {
  STest fixture(R"(abc{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest148") {
  STest fixture(R"(abc{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest149") {
  STest fixture(R"(abc{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest150") {
  STest fixture(R"(abc{0,1}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest151") {
  STest fixture(R"(abc{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest152") {
  STest fixture(R"(abc{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {10, 13, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest153") {
  STest fixture(R"(abc{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest154") {
  STest fixture(R"(aaa|a)");
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

TEST_CASE("autoPatternSearchTest155") {
  STest fixture(R"(aba|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 11, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest156") {
  STest fixture(R"(aab|a)");
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

TEST_CASE("autoPatternSearchTest157") {
  STest fixture(R"(abb|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest158") {
  STest fixture(R"(abc|a)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 3, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 8, 0},
    {10, 13, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest159") {
  STest fixture(R"(aaa|b)");
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

TEST_CASE("autoPatternSearchTest160") {
  STest fixture(R"(aba|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest161") {
  STest fixture(R"(aab|b)");
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

TEST_CASE("autoPatternSearchTest162") {
  STest fixture(R"(abb|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {3, 4, 0},
    {7, 10, 0},
    {11, 12, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest163") {
  STest fixture(R"(abc|b)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {3, 4, 0},
    {8, 9, 0},
    {9, 10, 0},
    {10, 13, 0},
    {15, 16, 0},
    {19, 20, 0},
    {20, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest164") {
  STest fixture(R"(aba|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 5, 0},
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

TEST_CASE("autoPatternSearchTest165") {
  STest fixture(R"(aab|c)");
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

TEST_CASE("autoPatternSearchTest166") {
  STest fixture(R"(abb|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {6, 7, 0},
    {7, 10, 0},
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

TEST_CASE("autoPatternSearchTest167") {
  STest fixture(R"(abc|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {6, 7, 0},
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

TEST_CASE("autoPatternSearchTest168") {
  STest fixture(R"(abc|.)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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
    {10, 13, 0},
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

TEST_CASE("autoPatternSearchTest169") {
  STest fixture(R"(aa+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest170") {
  STest fixture(R"(aa*)");
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

TEST_CASE("autoPatternSearchTest171") {
  STest fixture(R"(aa?)");
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

TEST_CASE("autoPatternSearchTest172") {
  STest fixture(R"(aa+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest173") {
  STest fixture(R"(aa*?)");
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

TEST_CASE("autoPatternSearchTest174") {
  STest fixture(R"(aa??)");
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

TEST_CASE("autoPatternSearchTest175") {
  STest fixture(R"(aa{0,1})");
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

TEST_CASE("autoPatternSearchTest176") {
  STest fixture(R"(aa{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest177") {
  STest fixture(R"(aa{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest178") {
  STest fixture(R"(aa{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest179") {
  STest fixture(R"(aa{0,1}?)");
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

TEST_CASE("autoPatternSearchTest180") {
  STest fixture(R"(aa{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest181") {
  STest fixture(R"(aa{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest182") {
  STest fixture(R"(aa{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest183") {
  STest fixture(R"(ab+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest184") {
  STest fixture(R"(ab*)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {1, 2, 0},
    {2, 4, 0},
    {4, 5, 0},
    {5, 6, 0},
    {7, 10, 0},
    {10, 12, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest185") {
  STest fixture(R"(ab?)");
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

TEST_CASE("autoPatternSearchTest186") {
  STest fixture(R"(ab+?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest187") {
  STest fixture(R"(ab*?)");
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

TEST_CASE("autoPatternSearchTest188") {
  STest fixture(R"(ab??)");
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

TEST_CASE("autoPatternSearchTest189") {
  STest fixture(R"(ab{0,1})");
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

TEST_CASE("autoPatternSearchTest190") {
  STest fixture(R"(ab{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest191") {
  STest fixture(R"(ab{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 10, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest192") {
  STest fixture(R"(ab{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest193") {
  STest fixture(R"(ab{0,1}?)");
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

TEST_CASE("autoPatternSearchTest194") {
  STest fixture(R"(ab{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest195") {
  STest fixture(R"(ab{1,2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest196") {
  STest fixture(R"(ab{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {7, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest197") {
  STest fixture(R"(aa|(a))");
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

TEST_CASE("autoPatternSearchTest198") {
  STest fixture(R"(ab|(a))");
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

TEST_CASE("autoPatternSearchTest199") {
  STest fixture(R"(aa|(b))");
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

TEST_CASE("autoPatternSearchTest200") {
  STest fixture(R"(ab|(b))");
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

TEST_CASE("autoPatternSearchTest201") {
  STest fixture(R"(ab|(c))");
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

TEST_CASE("autoPatternSearchTest202") {
  STest fixture(R"(aa|a)");
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

TEST_CASE("autoPatternSearchTest203") {
  STest fixture(R"(ab|a)");
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

TEST_CASE("autoPatternSearchTest204") {
  STest fixture(R"(aa|b)");
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

TEST_CASE("autoPatternSearchTest205") {
  STest fixture(R"(ab|b)");
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

TEST_CASE("autoPatternSearchTest206") {
  STest fixture(R"(ab|c)");
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

TEST_CASE("autoPatternSearchTest207") {
  STest fixture(R"(aa|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest208") {
  STest fixture(R"(ab|aa)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest209") {
  STest fixture(R"(aa|ba)");
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

TEST_CASE("autoPatternSearchTest210") {
  STest fixture(R"(ab|ba)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {9, 11, 0},
    {15, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest211") {
  STest fixture(R"(ab|ca)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 8, 0},
    {10, 12, 0},
    {12, 14, 0},
    {26, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest212") {
  STest fixture(R"(aa|ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest213") {
  STest fixture(R"(ab|ab)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest214") {
  STest fixture(R"(aa|bb)");
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

TEST_CASE("autoPatternSearchTest215") {
  STest fixture(R"(ab|bb)");
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

TEST_CASE("autoPatternSearchTest216") {
  STest fixture(R"(ab|cb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {14, 16, 0},
    {18, 20, 0},
    {22, 24, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest217") {
  STest fixture(R"(ab|ac)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {5, 7, 0},
    {7, 9, 0},
    {10, 12, 0},
    {13, 15, 0},
    {16, 18, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest218") {
  STest fixture(R"(aa|bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
    {11, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest219") {
  STest fixture(R"(ab|bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {7, 9, 0},
    {10, 12, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest220") {
  STest fixture(R"(ab|cc)");
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

TEST_CASE("autoPatternSearchTest221") {
  STest fixture(R"(ab|c.)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {2, 4, 0},
    {6, 8, 0},
    {10, 12, 0},
    {12, 14, 0},
    {14, 16, 0},
    {17, 19, 0},
    {22, 24, 0},
    {24, 26, 0},
    {26, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest222") {
  STest fixture(R"(aa|a+)");
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

TEST_CASE("autoPatternSearchTest223") {
  STest fixture(R"(aa|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest224") {
  STest fixture(R"(aa|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest225") {
  STest fixture(R"(aa|a+?)");
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

TEST_CASE("autoPatternSearchTest226") {
  STest fixture(R"(aa|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest227") {
  STest fixture(R"(aa|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest228") {
  STest fixture(R"(aa|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest229") {
  STest fixture(R"(aa|a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest230") {
  STest fixture(R"(aa|a{1,2})");
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

TEST_CASE("autoPatternSearchTest231") {
  STest fixture(R"(aa|a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest232") {
  STest fixture(R"(aa|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest233") {
  STest fixture(R"(aa|a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest234") {
  STest fixture(R"(aa|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest235") {
  STest fixture(R"(aa|a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest236") {
  STest fixture(R"(ab|a+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest237") {
  STest fixture(R"(ab|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest238") {
  STest fixture(R"(ab|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest239") {
  STest fixture(R"(ab|a+?)");
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

TEST_CASE("autoPatternSearchTest240") {
  STest fixture(R"(ab|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest241") {
  STest fixture(R"(ab|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest242") {
  STest fixture(R"(ab|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest243") {
  STest fixture(R"(ab|a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest244") {
  STest fixture(R"(ab|a{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
    {13, 14, 0},
    {16, 17, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest245") {
  STest fixture(R"(ab|a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest246") {
  STest fixture(R"(ab|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest247") {
  STest fixture(R"(ab|a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest248") {
  STest fixture(R"(ab|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest249") {
  STest fixture(R"(ab|a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 4, 0},
    {4, 6, 0},
    {7, 9, 0},
    {10, 12, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
