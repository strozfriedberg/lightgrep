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

TEST_CASE("autoPatternSearchTest1250") {
  STest fixture(R"(a??|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1251") {
  STest fixture(R"(a{0,1}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1252") {
  STest fixture(R"(a{2}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1253") {
  STest fixture(R"(a{1,2}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1254") {
  STest fixture(R"(a{2,}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1255") {
  STest fixture(R"(a{0,1}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1256") {
  STest fixture(R"(a{2}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1257") {
  STest fixture(R"(a{1,2}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1258") {
  STest fixture(R"(a{2,}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1259") {
  STest fixture(R"(a+|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1260") {
  STest fixture(R"(a*|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1261") {
  STest fixture(R"(a?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1262") {
  STest fixture(R"(a+?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1263") {
  STest fixture(R"(a*?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1264") {
  STest fixture(R"(a??|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1265") {
  STest fixture(R"(a{0,1}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1266") {
  STest fixture(R"(a{2}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1267") {
  STest fixture(R"(a{1,2}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1268") {
  STest fixture(R"(a{2,}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1269") {
  STest fixture(R"(a{0,1}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1270") {
  STest fixture(R"(a{2}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1271") {
  STest fixture(R"(a{1,2}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1272") {
  STest fixture(R"(a{2,}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1273") {
  STest fixture(R"(a+|b+?)");
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

TEST_CASE("autoPatternSearchTest1274") {
  STest fixture(R"(a*|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1275") {
  STest fixture(R"(a?|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1276") {
  STest fixture(R"(a+?|b+?)");
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

TEST_CASE("autoPatternSearchTest1277") {
  STest fixture(R"(a*?|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1278") {
  STest fixture(R"(a??|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1279") {
  STest fixture(R"(a{0,1}|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1280") {
  STest fixture(R"(a{2}|b+?)");
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

TEST_CASE("autoPatternSearchTest1281") {
  STest fixture(R"(a{1,2}|b+?)");
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

TEST_CASE("autoPatternSearchTest1282") {
  STest fixture(R"(a{2,}|b+?)");
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

TEST_CASE("autoPatternSearchTest1283") {
  STest fixture(R"(a{0,1}?|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1284") {
  STest fixture(R"(a{2}?|b+?)");
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

TEST_CASE("autoPatternSearchTest1285") {
  STest fixture(R"(a{1,2}?|b+?)");
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

TEST_CASE("autoPatternSearchTest1286") {
  STest fixture(R"(a{2,}?|b+?)");
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

TEST_CASE("autoPatternSearchTest1287") {
  STest fixture(R"(a+|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1288") {
  STest fixture(R"(a*|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1289") {
  STest fixture(R"(a?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1290") {
  STest fixture(R"(a+?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1291") {
  STest fixture(R"(a*?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1292") {
  STest fixture(R"(a??|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1293") {
  STest fixture(R"(a{0,1}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1294") {
  STest fixture(R"(a{2}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1295") {
  STest fixture(R"(a{1,2}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1296") {
  STest fixture(R"(a{2,}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1297") {
  STest fixture(R"(a{0,1}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1298") {
  STest fixture(R"(a{2}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1299") {
  STest fixture(R"(a{1,2}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1300") {
  STest fixture(R"(a{2,}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1301") {
  STest fixture(R"(a+|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1302") {
  STest fixture(R"(a*|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1303") {
  STest fixture(R"(a?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1304") {
  STest fixture(R"(a+?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1305") {
  STest fixture(R"(a*?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1306") {
  STest fixture(R"(a??|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1307") {
  STest fixture(R"(a{0,1}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1308") {
  STest fixture(R"(a{2}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1309") {
  STest fixture(R"(a{1,2}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1310") {
  STest fixture(R"(a{2,}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1311") {
  STest fixture(R"(a{0,1}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1312") {
  STest fixture(R"(a{2}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1313") {
  STest fixture(R"(a{1,2}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1314") {
  STest fixture(R"(a{2,}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1315") {
  STest fixture(R"(a+|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1316") {
  STest fixture(R"(a*|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1317") {
  STest fixture(R"(a?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1318") {
  STest fixture(R"(a+?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1319") {
  STest fixture(R"(a*?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1320") {
  STest fixture(R"(a??|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1321") {
  STest fixture(R"(a{0,1}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1322") {
  STest fixture(R"(a{2}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1323") {
  STest fixture(R"(a{1,2}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1324") {
  STest fixture(R"(a{2,}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1325") {
  STest fixture(R"(a{0,1}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1326") {
  STest fixture(R"(a{2}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1327") {
  STest fixture(R"(a{1,2}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1328") {
  STest fixture(R"(a{2,}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1329") {
  STest fixture(R"(a+|b{2})");
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

TEST_CASE("autoPatternSearchTest1330") {
  STest fixture(R"(a*|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1331") {
  STest fixture(R"(a?|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1332") {
  STest fixture(R"(a+?|b{2})");
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

TEST_CASE("autoPatternSearchTest1333") {
  STest fixture(R"(a*?|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1334") {
  STest fixture(R"(a??|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1335") {
  STest fixture(R"(a{0,1}|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1336") {
  STest fixture(R"(a{2}|b{2})");
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

TEST_CASE("autoPatternSearchTest1337") {
  STest fixture(R"(a{1,2}|b{2})");
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

TEST_CASE("autoPatternSearchTest1338") {
  STest fixture(R"(a{2,}|b{2})");
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

TEST_CASE("autoPatternSearchTest1339") {
  STest fixture(R"(a{0,1}?|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1340") {
  STest fixture(R"(a{2}?|b{2})");
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

TEST_CASE("autoPatternSearchTest1341") {
  STest fixture(R"(a{1,2}?|b{2})");
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

TEST_CASE("autoPatternSearchTest1342") {
  STest fixture(R"(a{2,}?|b{2})");
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

TEST_CASE("autoPatternSearchTest1343") {
  STest fixture(R"(a+|b{1,2})");
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
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1344") {
  STest fixture(R"(a*|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1345") {
  STest fixture(R"(a?|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1346") {
  STest fixture(R"(a+?|b{1,2})");
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
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1347") {
  STest fixture(R"(a*?|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1348") {
  STest fixture(R"(a??|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1349") {
  STest fixture(R"(a{0,1}|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1350") {
  STest fixture(R"(a{2}|b{1,2})");
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

TEST_CASE("autoPatternSearchTest1351") {
  STest fixture(R"(a{1,2}|b{1,2})");
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
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1352") {
  STest fixture(R"(a{2,}|b{1,2})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest1353") {
  STest fixture(R"(a{0,1}?|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1354") {
  STest fixture(R"(a{2}?|b{1,2})");
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

TEST_CASE("autoPatternSearchTest1355") {
  STest fixture(R"(a{1,2}?|b{1,2})");
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
    {19, 21, 0},
    {21, 22, 0},
    {23, 24, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1356") {
  STest fixture(R"(a{2,}?|b{1,2})");
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

TEST_CASE("autoPatternSearchTest1357") {
  STest fixture(R"(a+|b{2,})");
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
    {19, 22, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1358") {
  STest fixture(R"(a*|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1359") {
  STest fixture(R"(a?|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1360") {
  STest fixture(R"(a+?|b{2,})");
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
    {19, 22, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1361") {
  STest fixture(R"(a*?|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1362") {
  STest fixture(R"(a??|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1363") {
  STest fixture(R"(a{0,1}|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1364") {
  STest fixture(R"(a{2}|b{2,})");
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

TEST_CASE("autoPatternSearchTest1365") {
  STest fixture(R"(a{1,2}|b{2,})");
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
    {19, 22, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1366") {
  STest fixture(R"(a{2,}|b{2,})");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {4, 6, 0},
    {8, 10, 0},
    {19, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1367") {
  STest fixture(R"(a{0,1}?|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1368") {
  STest fixture(R"(a{2}?|b{2,})");
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

TEST_CASE("autoPatternSearchTest1369") {
  STest fixture(R"(a{1,2}?|b{2,})");
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
    {19, 22, 0},
    {27, 28, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternSearchTest1370") {
  STest fixture(R"(a{2,}?|b{2,})");
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

TEST_CASE("autoPatternSearchTest1371") {
  STest fixture(R"(a+|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1372") {
  STest fixture(R"(a*|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1373") {
  STest fixture(R"(a?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1374") {
  STest fixture(R"(a+?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1375") {
  STest fixture(R"(a*?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1376") {
  STest fixture(R"(a??|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1377") {
  STest fixture(R"(a{0,1}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1378") {
  STest fixture(R"(a{2}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1379") {
  STest fixture(R"(a{1,2}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1380") {
  STest fixture(R"(a{2,}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1381") {
  STest fixture(R"(a{0,1}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1382") {
  STest fixture(R"(a{2}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1383") {
  STest fixture(R"(a{1,2}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1384") {
  STest fixture(R"(a{2,}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1385") {
  STest fixture(R"(a+|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1386") {
  STest fixture(R"(a*|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1387") {
  STest fixture(R"(a?|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1388") {
  STest fixture(R"(a+?|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1389") {
  STest fixture(R"(a*?|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1390") {
  STest fixture(R"(a??|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1391") {
  STest fixture(R"(a{0,1}|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1392") {
  STest fixture(R"(a{2}|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1393") {
  STest fixture(R"(a{1,2}|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1394") {
  STest fixture(R"(a{2,}|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1395") {
  STest fixture(R"(a{0,1}?|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1396") {
  STest fixture(R"(a{2}?|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1397") {
  STest fixture(R"(a{1,2}?|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1398") {
  STest fixture(R"(a{2,}?|b{2}?)");
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

TEST_CASE("autoPatternSearchTest1399") {
  STest fixture(R"(a+|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1400") {
  STest fixture(R"(a*|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1401") {
  STest fixture(R"(a?|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1402") {
  STest fixture(R"(a+?|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1403") {
  STest fixture(R"(a*?|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1404") {
  STest fixture(R"(a??|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1405") {
  STest fixture(R"(a{0,1}|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1406") {
  STest fixture(R"(a{2}|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1407") {
  STest fixture(R"(a{1,2}|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1408") {
  STest fixture(R"(a{2,}|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1409") {
  STest fixture(R"(a{0,1}?|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1410") {
  STest fixture(R"(a{2}?|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1411") {
  STest fixture(R"(a{1,2}?|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1412") {
  STest fixture(R"(a{2,}?|b{1,2}?)");
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

TEST_CASE("autoPatternSearchTest1413") {
  STest fixture(R"(a+|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1414") {
  STest fixture(R"(a*|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1415") {
  STest fixture(R"(a?|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1416") {
  STest fixture(R"(a+?|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1417") {
  STest fixture(R"(a*?|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1418") {
  STest fixture(R"(a??|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1419") {
  STest fixture(R"(a{0,1}|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1420") {
  STest fixture(R"(a{2}|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1421") {
  STest fixture(R"(a{1,2}|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1422") {
  STest fixture(R"(a{2,}|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1423") {
  STest fixture(R"(a{0,1}?|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1424") {
  STest fixture(R"(a{2}?|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1425") {
  STest fixture(R"(a{1,2}?|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1426") {
  STest fixture(R"(a{2,}?|b{2,}?)");
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

TEST_CASE("autoPatternSearchTest1427") {
  STest fixture(R"(a+|a|a)");
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

TEST_CASE("autoPatternSearchTest1428") {
  STest fixture(R"(a*|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1429") {
  STest fixture(R"(a?|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1430") {
  STest fixture(R"(a+?|a|a)");
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

TEST_CASE("autoPatternSearchTest1431") {
  STest fixture(R"(a*?|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1432") {
  STest fixture(R"(a??|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1433") {
  STest fixture(R"(a{0,1}|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1434") {
  STest fixture(R"(a{2}|a|a)");
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

TEST_CASE("autoPatternSearchTest1435") {
  STest fixture(R"(a{1,2}|a|a)");
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

TEST_CASE("autoPatternSearchTest1436") {
  STest fixture(R"(a{2,}|a|a)");
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

TEST_CASE("autoPatternSearchTest1437") {
  STest fixture(R"(a{0,1}?|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1438") {
  STest fixture(R"(a{2}?|a|a)");
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

TEST_CASE("autoPatternSearchTest1439") {
  STest fixture(R"(a{1,2}?|a|a)");
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

TEST_CASE("autoPatternSearchTest1440") {
  STest fixture(R"(a{2,}?|a|a)");
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

TEST_CASE("autoPatternSearchTest1441") {
  STest fixture(R"(a+|b|a)");
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

TEST_CASE("autoPatternSearchTest1442") {
  STest fixture(R"(a*|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1443") {
  STest fixture(R"(a?|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1444") {
  STest fixture(R"(a+?|b|a)");
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

TEST_CASE("autoPatternSearchTest1445") {
  STest fixture(R"(a*?|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1446") {
  STest fixture(R"(a??|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1447") {
  STest fixture(R"(a{0,1}|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1448") {
  STest fixture(R"(a{2}|b|a)");
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

TEST_CASE("autoPatternSearchTest1449") {
  STest fixture(R"(a{1,2}|b|a)");
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

TEST_CASE("autoPatternSearchTest1450") {
  STest fixture(R"(a{2,}|b|a)");
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

TEST_CASE("autoPatternSearchTest1451") {
  STest fixture(R"(a{0,1}?|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1452") {
  STest fixture(R"(a{2}?|b|a)");
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

TEST_CASE("autoPatternSearchTest1453") {
  STest fixture(R"(a{1,2}?|b|a)");
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

TEST_CASE("autoPatternSearchTest1454") {
  STest fixture(R"(a{2,}?|b|a)");
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

TEST_CASE("autoPatternSearchTest1455") {
  STest fixture(R"(a+|a|b)");
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

TEST_CASE("autoPatternSearchTest1456") {
  STest fixture(R"(a*|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1457") {
  STest fixture(R"(a?|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1458") {
  STest fixture(R"(a+?|a|b)");
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

TEST_CASE("autoPatternSearchTest1459") {
  STest fixture(R"(a*?|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1460") {
  STest fixture(R"(a??|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1461") {
  STest fixture(R"(a{0,1}|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1462") {
  STest fixture(R"(a{2}|a|b)");
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

TEST_CASE("autoPatternSearchTest1463") {
  STest fixture(R"(a{1,2}|a|b)");
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

TEST_CASE("autoPatternSearchTest1464") {
  STest fixture(R"(a{2,}|a|b)");
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

TEST_CASE("autoPatternSearchTest1465") {
  STest fixture(R"(a{0,1}?|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1466") {
  STest fixture(R"(a{2}?|a|b)");
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

TEST_CASE("autoPatternSearchTest1467") {
  STest fixture(R"(a{1,2}?|a|b)");
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

TEST_CASE("autoPatternSearchTest1468") {
  STest fixture(R"(a{2,}?|a|b)");
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

TEST_CASE("autoPatternSearchTest1469") {
  STest fixture(R"(a+|b|b)");
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

TEST_CASE("autoPatternSearchTest1470") {
  STest fixture(R"(a*|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1471") {
  STest fixture(R"(a?|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1472") {
  STest fixture(R"(a+?|b|b)");
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

TEST_CASE("autoPatternSearchTest1473") {
  STest fixture(R"(a*?|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1474") {
  STest fixture(R"(a??|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1475") {
  STest fixture(R"(a{0,1}|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1476") {
  STest fixture(R"(a{2}|b|b)");
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

TEST_CASE("autoPatternSearchTest1477") {
  STest fixture(R"(a{1,2}|b|b)");
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

TEST_CASE("autoPatternSearchTest1478") {
  STest fixture(R"(a{2,}|b|b)");
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

TEST_CASE("autoPatternSearchTest1479") {
  STest fixture(R"(a{0,1}?|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1480") {
  STest fixture(R"(a{2}?|b|b)");
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

TEST_CASE("autoPatternSearchTest1481") {
  STest fixture(R"(a{1,2}?|b|b)");
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

TEST_CASE("autoPatternSearchTest1482") {
  STest fixture(R"(a{2,}?|b|b)");
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

TEST_CASE("autoPatternSearchTest1483") {
  STest fixture(R"(a+|b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {3, 4, 0},
    {4, 6, 0},
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

TEST_CASE("autoPatternSearchTest1484") {
  STest fixture(R"(a*|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1485") {
  STest fixture(R"(a?|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1486") {
  STest fixture(R"(a+?|b|c)");
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

TEST_CASE("autoPatternSearchTest1487") {
  STest fixture(R"(a*?|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1488") {
  STest fixture(R"(a??|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1489") {
  STest fixture(R"(a{0,1}|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1490") {
  STest fixture(R"(a{2}|b|c)");
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

TEST_CASE("autoPatternSearchTest1491") {
  STest fixture(R"(a{1,2}|b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {2, 3, 0},
    {3, 4, 0},
    {4, 6, 0},
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

TEST_CASE("autoPatternSearchTest1492") {
  STest fixture(R"(a{2,}|b|c)");
  const char text[] = R"(aaabaacabbabcacbaccbbbcbccca)";
  fixture.search(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
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

TEST_CASE("autoPatternSearchTest1493") {
  STest fixture(R"(a{0,1}?|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternSearchTest1494") {
  STest fixture(R"(a{2}?|b|c)");
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

TEST_CASE("autoPatternSearchTest1495") {
  STest fixture(R"(a{1,2}?|b|c)");
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

TEST_CASE("autoPatternSearchTest1496") {
  STest fixture(R"(a{2,}?|b|c)");
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

TEST_CASE("autoPatternSearchTest1497") {
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

TEST_CASE("autoPatternSearchTest1498") {
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

TEST_CASE("autoPatternSearchTest1499") {
  STest fixture(R"(a|a(a))");
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
