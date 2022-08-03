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

TEST_CASE("autoPatternSearchTest1000") {
  STest fixture(R"(a{2}|ab)");
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

TEST_CASE("autoPatternSearchTest1001") {
  STest fixture(R"(a{1,2}|ab)");
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

TEST_CASE("autoPatternSearchTest1002") {
  STest fixture(R"(a{2,}|ab)");
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

TEST_CASE("autoPatternSearchTest1003") {
  STest fixture(R"(a{0,1}?|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1004") {
  STest fixture(R"(a{2}?|ab)");
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

TEST_CASE("autoPatternSearchTest1005") {
  STest fixture(R"(a{1,2}?|ab)");
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

TEST_CASE("autoPatternSearchTest1006") {
  STest fixture(R"(a{2,}?|ab)");
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

TEST_CASE("autoPatternSearchTest1007") {
  STest fixture(R"(a+|bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest1008") {
  STest fixture(R"(a*|bb)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1009") {
  STest fixture(R"(a?|bb)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1010") {
  STest fixture(R"(a+?|bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest1011") {
  STest fixture(R"(a*?|bb)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1012") {
  STest fixture(R"(a??|bb)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1013") {
  STest fixture(R"(a{0,1}|bb)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1014") {
  STest fixture(R"(a{2}|bb)");
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

TEST_CASE("autoPatternSearchTest1015") {
  STest fixture(R"(a{1,2}|bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
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

TEST_CASE("autoPatternSearchTest1016") {
  STest fixture(R"(a{2,}|bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 21, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1017") {
  STest fixture(R"(a{0,1}?|bb)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1018") {
  STest fixture(R"(a{2}?|bb)");
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

TEST_CASE("autoPatternSearchTest1019") {
  STest fixture(R"(a{1,2}?|bb)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
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

TEST_CASE("autoPatternSearchTest1020") {
  STest fixture(R"(a{2,}?|bb)");
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

TEST_CASE("autoPatternSearchTest1021") {
  STest fixture(R"(a+|bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
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

TEST_CASE("autoPatternSearchTest1022") {
  STest fixture(R"(a*|bc)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1023") {
  STest fixture(R"(a?|bc)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1024") {
  STest fixture(R"(a+?|bc)");
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
    {11, 13, 0},
    {13, 14, 0},
    {16, 17, 0},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1025") {
  STest fixture(R"(a*?|bc)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1026") {
  STest fixture(R"(a??|bc)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1027") {
  STest fixture(R"(a{0,1}|bc)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1028") {
  STest fixture(R"(a{2}|bc)");
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

TEST_CASE("autoPatternSearchTest1029") {
  STest fixture(R"(a{1,2}|bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {4, 6, 0},
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

TEST_CASE("autoPatternSearchTest1030") {
  STest fixture(R"(a{2,}|bc)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {11, 13, 0},
    {21, 23, 0},
    {23, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1031") {
  STest fixture(R"(a{0,1}?|bc)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1032") {
  STest fixture(R"(a{2}?|bc)");
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

TEST_CASE("autoPatternSearchTest1033") {
  STest fixture(R"(a{1,2}?|bc)");
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
    {11, 13, 0},
    {13, 14, 0},
    {16, 17, 0},
    {21, 23, 0},
    {23, 25, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1034") {
  STest fixture(R"(a{2,}?|bc)");
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

TEST_CASE("autoPatternSearchTest1035") {
  STest fixture(R"(a+|a+)");
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

TEST_CASE("autoPatternSearchTest1036") {
  STest fixture(R"(a*|a+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1037") {
  STest fixture(R"(a?|a+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1038") {
  STest fixture(R"(a+?|a+)");
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

TEST_CASE("autoPatternSearchTest1039") {
  STest fixture(R"(a*?|a+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1040") {
  STest fixture(R"(a??|a+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1041") {
  STest fixture(R"(a{0,1}|a+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1042") {
  STest fixture(R"(a{2}|a+)");
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

TEST_CASE("autoPatternSearchTest1043") {
  STest fixture(R"(a{1,2}|a+)");
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

TEST_CASE("autoPatternSearchTest1044") {
  STest fixture(R"(a{2,}|a+)");
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

TEST_CASE("autoPatternSearchTest1045") {
  STest fixture(R"(a{0,1}?|a+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1046") {
  STest fixture(R"(a{2}?|a+)");
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

TEST_CASE("autoPatternSearchTest1047") {
  STest fixture(R"(a{1,2}?|a+)");
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

TEST_CASE("autoPatternSearchTest1048") {
  STest fixture(R"(a{2,}?|a+)");
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

TEST_CASE("autoPatternSearchTest1049") {
  STest fixture(R"(a+|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1050") {
  STest fixture(R"(a*|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1051") {
  STest fixture(R"(a?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1052") {
  STest fixture(R"(a+?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1053") {
  STest fixture(R"(a*?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1054") {
  STest fixture(R"(a??|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1055") {
  STest fixture(R"(a{0,1}|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1056") {
  STest fixture(R"(a{2}|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1057") {
  STest fixture(R"(a{1,2}|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1058") {
  STest fixture(R"(a{2,}|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1059") {
  STest fixture(R"(a{0,1}?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1060") {
  STest fixture(R"(a{2}?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1061") {
  STest fixture(R"(a{1,2}?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1062") {
  STest fixture(R"(a{2,}?|a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1063") {
  STest fixture(R"(a+|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1064") {
  STest fixture(R"(a*|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1065") {
  STest fixture(R"(a?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1066") {
  STest fixture(R"(a+?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1067") {
  STest fixture(R"(a*?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1068") {
  STest fixture(R"(a??|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1069") {
  STest fixture(R"(a{0,1}|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1070") {
  STest fixture(R"(a{2}|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1071") {
  STest fixture(R"(a{1,2}|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1072") {
  STest fixture(R"(a{2,}|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1073") {
  STest fixture(R"(a{0,1}?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1074") {
  STest fixture(R"(a{2}?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1075") {
  STest fixture(R"(a{1,2}?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1076") {
  STest fixture(R"(a{2,}?|a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1077") {
  STest fixture(R"(a+|a+?)");
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

TEST_CASE("autoPatternSearchTest1078") {
  STest fixture(R"(a*|a+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1079") {
  STest fixture(R"(a?|a+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1080") {
  STest fixture(R"(a+?|a+?)");
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

TEST_CASE("autoPatternSearchTest1081") {
  STest fixture(R"(a*?|a+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1082") {
  STest fixture(R"(a??|a+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1083") {
  STest fixture(R"(a{0,1}|a+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1084") {
  STest fixture(R"(a{2}|a+?)");
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

TEST_CASE("autoPatternSearchTest1085") {
  STest fixture(R"(a{1,2}|a+?)");
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

TEST_CASE("autoPatternSearchTest1086") {
  STest fixture(R"(a{2,}|a+?)");
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

TEST_CASE("autoPatternSearchTest1087") {
  STest fixture(R"(a{0,1}?|a+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1088") {
  STest fixture(R"(a{2}?|a+?)");
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

TEST_CASE("autoPatternSearchTest1089") {
  STest fixture(R"(a{1,2}?|a+?)");
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

TEST_CASE("autoPatternSearchTest1090") {
  STest fixture(R"(a{2,}?|a+?)");
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

TEST_CASE("autoPatternSearchTest1091") {
  STest fixture(R"(a+|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1092") {
  STest fixture(R"(a*|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1093") {
  STest fixture(R"(a?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1094") {
  STest fixture(R"(a+?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1095") {
  STest fixture(R"(a*?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1096") {
  STest fixture(R"(a??|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1097") {
  STest fixture(R"(a{0,1}|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1098") {
  STest fixture(R"(a{2}|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1099") {
  STest fixture(R"(a{1,2}|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1100") {
  STest fixture(R"(a{2,}|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1101") {
  STest fixture(R"(a{0,1}?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1102") {
  STest fixture(R"(a{2}?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1103") {
  STest fixture(R"(a{1,2}?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1104") {
  STest fixture(R"(a{2,}?|a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1105") {
  STest fixture(R"(a+|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1106") {
  STest fixture(R"(a*|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1107") {
  STest fixture(R"(a?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1108") {
  STest fixture(R"(a+?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1109") {
  STest fixture(R"(a*?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1110") {
  STest fixture(R"(a??|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1111") {
  STest fixture(R"(a{0,1}|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1112") {
  STest fixture(R"(a{2}|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1113") {
  STest fixture(R"(a{1,2}|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1114") {
  STest fixture(R"(a{2,}|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1115") {
  STest fixture(R"(a{0,1}?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1116") {
  STest fixture(R"(a{2}?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1117") {
  STest fixture(R"(a{1,2}?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1118") {
  STest fixture(R"(a{2,}?|a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1119") {
  STest fixture(R"(a+|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1120") {
  STest fixture(R"(a*|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1121") {
  STest fixture(R"(a?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1122") {
  STest fixture(R"(a+?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1123") {
  STest fixture(R"(a*?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1124") {
  STest fixture(R"(a??|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1125") {
  STest fixture(R"(a{0,1}|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1126") {
  STest fixture(R"(a{2}|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1127") {
  STest fixture(R"(a{1,2}|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1128") {
  STest fixture(R"(a{2,}|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1129") {
  STest fixture(R"(a{0,1}?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1130") {
  STest fixture(R"(a{2}?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1131") {
  STest fixture(R"(a{1,2}?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1132") {
  STest fixture(R"(a{2,}?|a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1133") {
  STest fixture(R"(a+|a{2})");
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

TEST_CASE("autoPatternSearchTest1134") {
  STest fixture(R"(a*|a{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1135") {
  STest fixture(R"(a?|a{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1136") {
  STest fixture(R"(a+?|a{2})");
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

TEST_CASE("autoPatternSearchTest1137") {
  STest fixture(R"(a*?|a{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1138") {
  STest fixture(R"(a??|a{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1139") {
  STest fixture(R"(a{0,1}|a{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1140") {
  STest fixture(R"(a{2}|a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1141") {
  STest fixture(R"(a{1,2}|a{2})");
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

TEST_CASE("autoPatternSearchTest1142") {
  STest fixture(R"(a{2,}|a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1143") {
  STest fixture(R"(a{0,1}?|a{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1144") {
  STest fixture(R"(a{2}?|a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1145") {
  STest fixture(R"(a{1,2}?|a{2})");
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

TEST_CASE("autoPatternSearchTest1146") {
  STest fixture(R"(a{2,}?|a{2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1147") {
  STest fixture(R"(a+|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1148") {
  STest fixture(R"(a*|a{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1149") {
  STest fixture(R"(a?|a{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1150") {
  STest fixture(R"(a+?|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1151") {
  STest fixture(R"(a*?|a{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1152") {
  STest fixture(R"(a??|a{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1153") {
  STest fixture(R"(a{0,1}|a{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1154") {
  STest fixture(R"(a{2}|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1155") {
  STest fixture(R"(a{1,2}|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1156") {
  STest fixture(R"(a{2,}|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1157") {
  STest fixture(R"(a{0,1}?|a{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1158") {
  STest fixture(R"(a{2}?|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1159") {
  STest fixture(R"(a{1,2}?|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1160") {
  STest fixture(R"(a{2,}?|a{1,2})");
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

TEST_CASE("autoPatternSearchTest1161") {
  STest fixture(R"(a+|a{2,})");
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

TEST_CASE("autoPatternSearchTest1162") {
  STest fixture(R"(a*|a{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1163") {
  STest fixture(R"(a?|a{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1164") {
  STest fixture(R"(a+?|a{2,})");
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

TEST_CASE("autoPatternSearchTest1165") {
  STest fixture(R"(a*?|a{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1166") {
  STest fixture(R"(a??|a{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1167") {
  STest fixture(R"(a{0,1}|a{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1168") {
  STest fixture(R"(a{2}|a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1169") {
  STest fixture(R"(a{1,2}|a{2,})");
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

TEST_CASE("autoPatternSearchTest1170") {
  STest fixture(R"(a{2,}|a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1171") {
  STest fixture(R"(a{0,1}?|a{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1172") {
  STest fixture(R"(a{2}?|a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1173") {
  STest fixture(R"(a{1,2}?|a{2,})");
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

TEST_CASE("autoPatternSearchTest1174") {
  STest fixture(R"(a{2,}?|a{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1175") {
  STest fixture(R"(a+|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1176") {
  STest fixture(R"(a*|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1177") {
  STest fixture(R"(a?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1178") {
  STest fixture(R"(a+?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1179") {
  STest fixture(R"(a*?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1180") {
  STest fixture(R"(a??|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1181") {
  STest fixture(R"(a{0,1}|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1182") {
  STest fixture(R"(a{2}|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1183") {
  STest fixture(R"(a{1,2}|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1184") {
  STest fixture(R"(a{2,}|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1185") {
  STest fixture(R"(a{0,1}?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1186") {
  STest fixture(R"(a{2}?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1187") {
  STest fixture(R"(a{1,2}?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1188") {
  STest fixture(R"(a{2,}?|a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1189") {
  STest fixture(R"(a+|a{2}?)");
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

TEST_CASE("autoPatternSearchTest1190") {
  STest fixture(R"(a*|a{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1191") {
  STest fixture(R"(a?|a{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1192") {
  STest fixture(R"(a+?|a{2}?)");
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

TEST_CASE("autoPatternSearchTest1193") {
  STest fixture(R"(a*?|a{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1194") {
  STest fixture(R"(a??|a{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1195") {
  STest fixture(R"(a{0,1}|a{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1196") {
  STest fixture(R"(a{2}|a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1197") {
  STest fixture(R"(a{1,2}|a{2}?)");
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

TEST_CASE("autoPatternSearchTest1198") {
  STest fixture(R"(a{2,}|a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1199") {
  STest fixture(R"(a{0,1}?|a{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1200") {
  STest fixture(R"(a{2}?|a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1201") {
  STest fixture(R"(a{1,2}?|a{2}?)");
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

TEST_CASE("autoPatternSearchTest1202") {
  STest fixture(R"(a{2,}?|a{2}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1203") {
  STest fixture(R"(a+|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1204") {
  STest fixture(R"(a*|a{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1205") {
  STest fixture(R"(a?|a{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1206") {
  STest fixture(R"(a+?|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1207") {
  STest fixture(R"(a*?|a{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1208") {
  STest fixture(R"(a??|a{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1209") {
  STest fixture(R"(a{0,1}|a{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1210") {
  STest fixture(R"(a{2}|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1211") {
  STest fixture(R"(a{1,2}|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1212") {
  STest fixture(R"(a{2,}|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1213") {
  STest fixture(R"(a{0,1}?|a{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1214") {
  STest fixture(R"(a{2}?|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1215") {
  STest fixture(R"(a{1,2}?|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1216") {
  STest fixture(R"(a{2,}?|a{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1217") {
  STest fixture(R"(a+|a{2,}?)");
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

TEST_CASE("autoPatternSearchTest1218") {
  STest fixture(R"(a*|a{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1219") {
  STest fixture(R"(a?|a{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1220") {
  STest fixture(R"(a+?|a{2,}?)");
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

TEST_CASE("autoPatternSearchTest1221") {
  STest fixture(R"(a*?|a{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1222") {
  STest fixture(R"(a??|a{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1223") {
  STest fixture(R"(a{0,1}|a{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1224") {
  STest fixture(R"(a{2}|a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1225") {
  STest fixture(R"(a{1,2}|a{2,}?)");
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

TEST_CASE("autoPatternSearchTest1226") {
  STest fixture(R"(a{2,}|a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1227") {
  STest fixture(R"(a{0,1}?|a{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1228") {
  STest fixture(R"(a{2}?|a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1229") {
  STest fixture(R"(a{1,2}?|a{2,}?)");
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

TEST_CASE("autoPatternSearchTest1230") {
  STest fixture(R"(a{2,}?|a{2,}?)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {4, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1231") {
  STest fixture(R"(a+|b+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {3, 4, 0},
    {4, 6, 0},
    {7, 8, 0},
    {8, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1232") {
  STest fixture(R"(a*|b+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1233") {
  STest fixture(R"(a?|b+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1234") {
  STest fixture(R"(a+?|b+)");
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
    {8, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1235") {
  STest fixture(R"(a*?|b+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1236") {
  STest fixture(R"(a??|b+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1237") {
  STest fixture(R"(a{0,1}|b+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1238") {
  STest fixture(R"(a{2}|b+)");
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

TEST_CASE("autoPatternSearchTest1239") {
  STest fixture(R"(a{1,2}|b+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 6, 0},
    {7, 8, 0},
    {8, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1240") {
  STest fixture(R"(a{2,}|b+)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest1241") {
  STest fixture(R"(a{0,1}?|b+)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1242") {
  STest fixture(R"(a{2}?|b+)");
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

TEST_CASE("autoPatternSearchTest1243") {
  STest fixture(R"(a{1,2}?|b+)");
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
    {8, 10, 0},
    {10, 11, 0},
    {11, 12, 0},
    {13, 14, 0},
    {15, 16, 0},
    {16, 17, 0},
    {19, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1244") {
  STest fixture(R"(a{2,}?|b+)");
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

TEST_CASE("autoPatternSearchTest1245") {
  STest fixture(R"(a+|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1246") {
  STest fixture(R"(a*|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1247") {
  STest fixture(R"(a?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1248") {
  STest fixture(R"(a+?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1249") {
  STest fixture(R"(a*?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}
