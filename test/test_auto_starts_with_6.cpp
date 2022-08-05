/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2014, Lightbox Technologies, Inc

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

TEST_CASE("autoPatternStartsWithTest1250") {
  STest fixture(R"(a??|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1251") {
  STest fixture(R"(a{0,1}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1252") {
  STest fixture(R"(a{2}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1253") {
  STest fixture(R"(a{1,2}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1254") {
  STest fixture(R"(a{2,}|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1255") {
  STest fixture(R"(a{0,1}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1256") {
  STest fixture(R"(a{2}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1257") {
  STest fixture(R"(a{1,2}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1258") {
  STest fixture(R"(a{2,}?|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1259") {
  STest fixture(R"(a+|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1260") {
  STest fixture(R"(a*|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1261") {
  STest fixture(R"(a?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1262") {
  STest fixture(R"(a+?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1263") {
  STest fixture(R"(a*?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1264") {
  STest fixture(R"(a??|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1265") {
  STest fixture(R"(a{0,1}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1266") {
  STest fixture(R"(a{2}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1267") {
  STest fixture(R"(a{1,2}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1268") {
  STest fixture(R"(a{2,}|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1269") {
  STest fixture(R"(a{0,1}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1270") {
  STest fixture(R"(a{2}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1271") {
  STest fixture(R"(a{1,2}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1272") {
  STest fixture(R"(a{2,}?|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1273") {
  STest fixture(R"(a+|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1274") {
  STest fixture(R"(a*|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1275") {
  STest fixture(R"(a?|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1276") {
  STest fixture(R"(a+?|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1277") {
  STest fixture(R"(a*?|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1278") {
  STest fixture(R"(a??|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1279") {
  STest fixture(R"(a{0,1}|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1280") {
  STest fixture(R"(a{2}|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1281") {
  STest fixture(R"(a{1,2}|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1282") {
  STest fixture(R"(a{2,}|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1283") {
  STest fixture(R"(a{0,1}?|b+?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1284") {
  STest fixture(R"(a{2}?|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1285") {
  STest fixture(R"(a{1,2}?|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1286") {
  STest fixture(R"(a{2,}?|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1287") {
  STest fixture(R"(a+|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1288") {
  STest fixture(R"(a*|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1289") {
  STest fixture(R"(a?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1290") {
  STest fixture(R"(a+?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1291") {
  STest fixture(R"(a*?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1292") {
  STest fixture(R"(a??|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1293") {
  STest fixture(R"(a{0,1}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1294") {
  STest fixture(R"(a{2}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1295") {
  STest fixture(R"(a{1,2}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1296") {
  STest fixture(R"(a{2,}|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1297") {
  STest fixture(R"(a{0,1}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1298") {
  STest fixture(R"(a{2}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1299") {
  STest fixture(R"(a{1,2}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1300") {
  STest fixture(R"(a{2,}?|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1301") {
  STest fixture(R"(a+|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1302") {
  STest fixture(R"(a*|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1303") {
  STest fixture(R"(a?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1304") {
  STest fixture(R"(a+?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1305") {
  STest fixture(R"(a*?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1306") {
  STest fixture(R"(a??|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1307") {
  STest fixture(R"(a{0,1}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1308") {
  STest fixture(R"(a{2}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1309") {
  STest fixture(R"(a{1,2}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1310") {
  STest fixture(R"(a{2,}|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1311") {
  STest fixture(R"(a{0,1}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1312") {
  STest fixture(R"(a{2}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1313") {
  STest fixture(R"(a{1,2}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1314") {
  STest fixture(R"(a{2,}?|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1315") {
  STest fixture(R"(a+|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1316") {
  STest fixture(R"(a*|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1317") {
  STest fixture(R"(a?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1318") {
  STest fixture(R"(a+?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1319") {
  STest fixture(R"(a*?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1320") {
  STest fixture(R"(a??|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1321") {
  STest fixture(R"(a{0,1}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1322") {
  STest fixture(R"(a{2}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1323") {
  STest fixture(R"(a{1,2}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1324") {
  STest fixture(R"(a{2,}|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1325") {
  STest fixture(R"(a{0,1}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1326") {
  STest fixture(R"(a{2}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1327") {
  STest fixture(R"(a{1,2}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1328") {
  STest fixture(R"(a{2,}?|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1329") {
  STest fixture(R"(a+|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1330") {
  STest fixture(R"(a*|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1331") {
  STest fixture(R"(a?|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1332") {
  STest fixture(R"(a+?|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1333") {
  STest fixture(R"(a*?|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1334") {
  STest fixture(R"(a??|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1335") {
  STest fixture(R"(a{0,1}|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1336") {
  STest fixture(R"(a{2}|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1337") {
  STest fixture(R"(a{1,2}|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1338") {
  STest fixture(R"(a{2,}|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1339") {
  STest fixture(R"(a{0,1}?|b{2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1340") {
  STest fixture(R"(a{2}?|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1341") {
  STest fixture(R"(a{1,2}?|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1342") {
  STest fixture(R"(a{2,}?|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1343") {
  STest fixture(R"(a+|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1344") {
  STest fixture(R"(a*|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1345") {
  STest fixture(R"(a?|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1346") {
  STest fixture(R"(a+?|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1347") {
  STest fixture(R"(a*?|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1348") {
  STest fixture(R"(a??|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1349") {
  STest fixture(R"(a{0,1}|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1350") {
  STest fixture(R"(a{2}|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1351") {
  STest fixture(R"(a{1,2}|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1352") {
  STest fixture(R"(a{2,}|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1353") {
  STest fixture(R"(a{0,1}?|b{1,2})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1354") {
  STest fixture(R"(a{2}?|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1355") {
  STest fixture(R"(a{1,2}?|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1356") {
  STest fixture(R"(a{2,}?|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1357") {
  STest fixture(R"(a+|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1358") {
  STest fixture(R"(a*|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1359") {
  STest fixture(R"(a?|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1360") {
  STest fixture(R"(a+?|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1361") {
  STest fixture(R"(a*?|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1362") {
  STest fixture(R"(a??|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1363") {
  STest fixture(R"(a{0,1}|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1364") {
  STest fixture(R"(a{2}|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1365") {
  STest fixture(R"(a{1,2}|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1366") {
  STest fixture(R"(a{2,}|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1367") {
  STest fixture(R"(a{0,1}?|b{2,})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1368") {
  STest fixture(R"(a{2}?|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1369") {
  STest fixture(R"(a{1,2}?|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1370") {
  STest fixture(R"(a{2,}?|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1371") {
  STest fixture(R"(a+|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1372") {
  STest fixture(R"(a*|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1373") {
  STest fixture(R"(a?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1374") {
  STest fixture(R"(a+?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1375") {
  STest fixture(R"(a*?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1376") {
  STest fixture(R"(a??|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1377") {
  STest fixture(R"(a{0,1}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1378") {
  STest fixture(R"(a{2}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1379") {
  STest fixture(R"(a{1,2}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1380") {
  STest fixture(R"(a{2,}|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1381") {
  STest fixture(R"(a{0,1}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1382") {
  STest fixture(R"(a{2}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1383") {
  STest fixture(R"(a{1,2}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1384") {
  STest fixture(R"(a{2,}?|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1385") {
  STest fixture(R"(a+|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1386") {
  STest fixture(R"(a*|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1387") {
  STest fixture(R"(a?|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1388") {
  STest fixture(R"(a+?|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1389") {
  STest fixture(R"(a*?|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1390") {
  STest fixture(R"(a??|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1391") {
  STest fixture(R"(a{0,1}|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1392") {
  STest fixture(R"(a{2}|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1393") {
  STest fixture(R"(a{1,2}|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1394") {
  STest fixture(R"(a{2,}|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1395") {
  STest fixture(R"(a{0,1}?|b{2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1396") {
  STest fixture(R"(a{2}?|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1397") {
  STest fixture(R"(a{1,2}?|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1398") {
  STest fixture(R"(a{2,}?|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1399") {
  STest fixture(R"(a+|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1400") {
  STest fixture(R"(a*|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1401") {
  STest fixture(R"(a?|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1402") {
  STest fixture(R"(a+?|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1403") {
  STest fixture(R"(a*?|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1404") {
  STest fixture(R"(a??|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1405") {
  STest fixture(R"(a{0,1}|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1406") {
  STest fixture(R"(a{2}|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1407") {
  STest fixture(R"(a{1,2}|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1408") {
  STest fixture(R"(a{2,}|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1409") {
  STest fixture(R"(a{0,1}?|b{1,2}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1410") {
  STest fixture(R"(a{2}?|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1411") {
  STest fixture(R"(a{1,2}?|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1412") {
  STest fixture(R"(a{2,}?|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1413") {
  STest fixture(R"(a+|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1414") {
  STest fixture(R"(a*|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1415") {
  STest fixture(R"(a?|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1416") {
  STest fixture(R"(a+?|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1417") {
  STest fixture(R"(a*?|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1418") {
  STest fixture(R"(a??|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1419") {
  STest fixture(R"(a{0,1}|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1420") {
  STest fixture(R"(a{2}|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1421") {
  STest fixture(R"(a{1,2}|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1422") {
  STest fixture(R"(a{2,}|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1423") {
  STest fixture(R"(a{0,1}?|b{2,}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1424") {
  STest fixture(R"(a{2}?|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1425") {
  STest fixture(R"(a{1,2}?|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1426") {
  STest fixture(R"(a{2,}?|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1427") {
  STest fixture(R"(a+|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1428") {
  STest fixture(R"(a*|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1429") {
  STest fixture(R"(a?|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1430") {
  STest fixture(R"(a+?|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1431") {
  STest fixture(R"(a*?|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1432") {
  STest fixture(R"(a??|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1433") {
  STest fixture(R"(a{0,1}|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1434") {
  STest fixture(R"(a{2}|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1435") {
  STest fixture(R"(a{1,2}|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1436") {
  STest fixture(R"(a{2,}|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1437") {
  STest fixture(R"(a{0,1}?|a|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1438") {
  STest fixture(R"(a{2}?|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1439") {
  STest fixture(R"(a{1,2}?|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1440") {
  STest fixture(R"(a{2,}?|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1441") {
  STest fixture(R"(a+|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1442") {
  STest fixture(R"(a*|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1443") {
  STest fixture(R"(a?|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1444") {
  STest fixture(R"(a+?|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1445") {
  STest fixture(R"(a*?|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1446") {
  STest fixture(R"(a??|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1447") {
  STest fixture(R"(a{0,1}|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1448") {
  STest fixture(R"(a{2}|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1449") {
  STest fixture(R"(a{1,2}|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1450") {
  STest fixture(R"(a{2,}|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1451") {
  STest fixture(R"(a{0,1}?|b|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1452") {
  STest fixture(R"(a{2}?|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1453") {
  STest fixture(R"(a{1,2}?|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1454") {
  STest fixture(R"(a{2,}?|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1455") {
  STest fixture(R"(a+|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1456") {
  STest fixture(R"(a*|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1457") {
  STest fixture(R"(a?|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1458") {
  STest fixture(R"(a+?|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1459") {
  STest fixture(R"(a*?|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1460") {
  STest fixture(R"(a??|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1461") {
  STest fixture(R"(a{0,1}|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1462") {
  STest fixture(R"(a{2}|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1463") {
  STest fixture(R"(a{1,2}|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1464") {
  STest fixture(R"(a{2,}|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1465") {
  STest fixture(R"(a{0,1}?|a|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1466") {
  STest fixture(R"(a{2}?|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1467") {
  STest fixture(R"(a{1,2}?|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1468") {
  STest fixture(R"(a{2,}?|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1469") {
  STest fixture(R"(a+|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1470") {
  STest fixture(R"(a*|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1471") {
  STest fixture(R"(a?|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1472") {
  STest fixture(R"(a+?|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1473") {
  STest fixture(R"(a*?|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1474") {
  STest fixture(R"(a??|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1475") {
  STest fixture(R"(a{0,1}|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1476") {
  STest fixture(R"(a{2}|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1477") {
  STest fixture(R"(a{1,2}|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1478") {
  STest fixture(R"(a{2,}|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1479") {
  STest fixture(R"(a{0,1}?|b|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1480") {
  STest fixture(R"(a{2}?|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1481") {
  STest fixture(R"(a{1,2}?|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1482") {
  STest fixture(R"(a{2,}?|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1483") {
  STest fixture(R"(a+|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1484") {
  STest fixture(R"(a*|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1485") {
  STest fixture(R"(a?|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1486") {
  STest fixture(R"(a+?|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1487") {
  STest fixture(R"(a*?|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1488") {
  STest fixture(R"(a??|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1489") {
  STest fixture(R"(a{0,1}|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1490") {
  STest fixture(R"(a{2}|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1491") {
  STest fixture(R"(a{1,2}|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1492") {
  STest fixture(R"(a{2,}|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1493") {
  STest fixture(R"(a{0,1}?|b|c)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest1494") {
  STest fixture(R"(a{2}?|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1495") {
  STest fixture(R"(a{1,2}?|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1496") {
  STest fixture(R"(a{2,}?|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1497") {
  STest fixture(R"(a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1498") {
  STest fixture(R"(a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest1499") {
  STest fixture(R"(a|a(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
