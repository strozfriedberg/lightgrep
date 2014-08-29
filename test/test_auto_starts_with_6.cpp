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

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1250, STest, STest(R"(a??|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1251, STest, STest(R"(a{0,1}|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1252, STest, STest(R"(a{2}|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1253, STest, STest(R"(a{1,2}|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1254, STest, STest(R"(a{2,}|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1255, STest, STest(R"(a{0,1}?|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1256, STest, STest(R"(a{2}?|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1257, STest, STest(R"(a{1,2}?|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1258, STest, STest(R"(a{2,}?|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1259, STest, STest(R"(a+|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1260, STest, STest(R"(a*|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1261, STest, STest(R"(a?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1262, STest, STest(R"(a+?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1263, STest, STest(R"(a*?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1264, STest, STest(R"(a??|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1265, STest, STest(R"(a{0,1}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1266, STest, STest(R"(a{2}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1267, STest, STest(R"(a{1,2}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1268, STest, STest(R"(a{2,}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1269, STest, STest(R"(a{0,1}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1270, STest, STest(R"(a{2}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1271, STest, STest(R"(a{1,2}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1272, STest, STest(R"(a{2,}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1273, STest, STest(R"(a+|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1274, STest, STest(R"(a*|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1275, STest, STest(R"(a?|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1276, STest, STest(R"(a+?|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1277, STest, STest(R"(a*?|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1278, STest, STest(R"(a??|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1279, STest, STest(R"(a{0,1}|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1280, STest, STest(R"(a{2}|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1281, STest, STest(R"(a{1,2}|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1282, STest, STest(R"(a{2,}|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1283, STest, STest(R"(a{0,1}?|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1284, STest, STest(R"(a{2}?|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1285, STest, STest(R"(a{1,2}?|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1286, STest, STest(R"(a{2,}?|b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1287, STest, STest(R"(a+|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1288, STest, STest(R"(a*|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1289, STest, STest(R"(a?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1290, STest, STest(R"(a+?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1291, STest, STest(R"(a*?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1292, STest, STest(R"(a??|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1293, STest, STest(R"(a{0,1}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1294, STest, STest(R"(a{2}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1295, STest, STest(R"(a{1,2}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1296, STest, STest(R"(a{2,}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1297, STest, STest(R"(a{0,1}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1298, STest, STest(R"(a{2}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1299, STest, STest(R"(a{1,2}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1300, STest, STest(R"(a{2,}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1301, STest, STest(R"(a+|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1302, STest, STest(R"(a*|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1303, STest, STest(R"(a?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1304, STest, STest(R"(a+?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1305, STest, STest(R"(a*?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1306, STest, STest(R"(a??|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1307, STest, STest(R"(a{0,1}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1308, STest, STest(R"(a{2}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1309, STest, STest(R"(a{1,2}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1310, STest, STest(R"(a{2,}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1311, STest, STest(R"(a{0,1}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1312, STest, STest(R"(a{2}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1313, STest, STest(R"(a{1,2}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1314, STest, STest(R"(a{2,}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1315, STest, STest(R"(a+|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1316, STest, STest(R"(a*|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1317, STest, STest(R"(a?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1318, STest, STest(R"(a+?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1319, STest, STest(R"(a*?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1320, STest, STest(R"(a??|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1321, STest, STest(R"(a{0,1}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1322, STest, STest(R"(a{2}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1323, STest, STest(R"(a{1,2}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1324, STest, STest(R"(a{2,}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1325, STest, STest(R"(a{0,1}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1326, STest, STest(R"(a{2}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1327, STest, STest(R"(a{1,2}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1328, STest, STest(R"(a{2,}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1329, STest, STest(R"(a+|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1330, STest, STest(R"(a*|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1331, STest, STest(R"(a?|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1332, STest, STest(R"(a+?|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1333, STest, STest(R"(a*?|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1334, STest, STest(R"(a??|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1335, STest, STest(R"(a{0,1}|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1336, STest, STest(R"(a{2}|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1337, STest, STest(R"(a{1,2}|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1338, STest, STest(R"(a{2,}|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1339, STest, STest(R"(a{0,1}?|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1340, STest, STest(R"(a{2}?|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1341, STest, STest(R"(a{1,2}?|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1342, STest, STest(R"(a{2,}?|b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1343, STest, STest(R"(a+|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1344, STest, STest(R"(a*|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1345, STest, STest(R"(a?|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1346, STest, STest(R"(a+?|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1347, STest, STest(R"(a*?|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1348, STest, STest(R"(a??|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1349, STest, STest(R"(a{0,1}|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1350, STest, STest(R"(a{2}|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1351, STest, STest(R"(a{1,2}|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1352, STest, STest(R"(a{2,}|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1353, STest, STest(R"(a{0,1}?|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1354, STest, STest(R"(a{2}?|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1355, STest, STest(R"(a{1,2}?|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1356, STest, STest(R"(a{2,}?|b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1357, STest, STest(R"(a+|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1358, STest, STest(R"(a*|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1359, STest, STest(R"(a?|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1360, STest, STest(R"(a+?|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1361, STest, STest(R"(a*?|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1362, STest, STest(R"(a??|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1363, STest, STest(R"(a{0,1}|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1364, STest, STest(R"(a{2}|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1365, STest, STest(R"(a{1,2}|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1366, STest, STest(R"(a{2,}|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1367, STest, STest(R"(a{0,1}?|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1368, STest, STest(R"(a{2}?|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1369, STest, STest(R"(a{1,2}?|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1370, STest, STest(R"(a{2,}?|b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1371, STest, STest(R"(a+|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1372, STest, STest(R"(a*|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1373, STest, STest(R"(a?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1374, STest, STest(R"(a+?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1375, STest, STest(R"(a*?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1376, STest, STest(R"(a??|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1377, STest, STest(R"(a{0,1}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1378, STest, STest(R"(a{2}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1379, STest, STest(R"(a{1,2}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1380, STest, STest(R"(a{2,}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1381, STest, STest(R"(a{0,1}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1382, STest, STest(R"(a{2}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1383, STest, STest(R"(a{1,2}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1384, STest, STest(R"(a{2,}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1385, STest, STest(R"(a+|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1386, STest, STest(R"(a*|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1387, STest, STest(R"(a?|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1388, STest, STest(R"(a+?|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1389, STest, STest(R"(a*?|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1390, STest, STest(R"(a??|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1391, STest, STest(R"(a{0,1}|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1392, STest, STest(R"(a{2}|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1393, STest, STest(R"(a{1,2}|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1394, STest, STest(R"(a{2,}|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1395, STest, STest(R"(a{0,1}?|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1396, STest, STest(R"(a{2}?|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1397, STest, STest(R"(a{1,2}?|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1398, STest, STest(R"(a{2,}?|b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1399, STest, STest(R"(a+|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1400, STest, STest(R"(a*|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1401, STest, STest(R"(a?|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1402, STest, STest(R"(a+?|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1403, STest, STest(R"(a*?|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1404, STest, STest(R"(a??|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1405, STest, STest(R"(a{0,1}|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1406, STest, STest(R"(a{2}|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1407, STest, STest(R"(a{1,2}|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1408, STest, STest(R"(a{2,}|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1409, STest, STest(R"(a{0,1}?|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1410, STest, STest(R"(a{2}?|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1411, STest, STest(R"(a{1,2}?|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1412, STest, STest(R"(a{2,}?|b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1413, STest, STest(R"(a+|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1414, STest, STest(R"(a*|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1415, STest, STest(R"(a?|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1416, STest, STest(R"(a+?|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1417, STest, STest(R"(a*?|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1418, STest, STest(R"(a??|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1419, STest, STest(R"(a{0,1}|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1420, STest, STest(R"(a{2}|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1421, STest, STest(R"(a{1,2}|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1422, STest, STest(R"(a{2,}|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1423, STest, STest(R"(a{0,1}?|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1424, STest, STest(R"(a{2}?|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1425, STest, STest(R"(a{1,2}?|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1426, STest, STest(R"(a{2,}?|b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1427, STest, STest(R"(a+|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1428, STest, STest(R"(a*|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1429, STest, STest(R"(a?|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1430, STest, STest(R"(a+?|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1431, STest, STest(R"(a*?|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1432, STest, STest(R"(a??|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1433, STest, STest(R"(a{0,1}|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1434, STest, STest(R"(a{2}|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1435, STest, STest(R"(a{1,2}|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1436, STest, STest(R"(a{2,}|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1437, STest, STest(R"(a{0,1}?|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1438, STest, STest(R"(a{2}?|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1439, STest, STest(R"(a{1,2}?|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1440, STest, STest(R"(a{2,}?|a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1441, STest, STest(R"(a+|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1442, STest, STest(R"(a*|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1443, STest, STest(R"(a?|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1444, STest, STest(R"(a+?|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1445, STest, STest(R"(a*?|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1446, STest, STest(R"(a??|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1447, STest, STest(R"(a{0,1}|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1448, STest, STest(R"(a{2}|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1449, STest, STest(R"(a{1,2}|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1450, STest, STest(R"(a{2,}|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1451, STest, STest(R"(a{0,1}?|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1452, STest, STest(R"(a{2}?|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1453, STest, STest(R"(a{1,2}?|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1454, STest, STest(R"(a{2,}?|b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1455, STest, STest(R"(a+|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1456, STest, STest(R"(a*|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1457, STest, STest(R"(a?|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1458, STest, STest(R"(a+?|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1459, STest, STest(R"(a*?|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1460, STest, STest(R"(a??|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1461, STest, STest(R"(a{0,1}|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1462, STest, STest(R"(a{2}|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1463, STest, STest(R"(a{1,2}|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1464, STest, STest(R"(a{2,}|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1465, STest, STest(R"(a{0,1}?|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1466, STest, STest(R"(a{2}?|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1467, STest, STest(R"(a{1,2}?|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1468, STest, STest(R"(a{2,}?|a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1469, STest, STest(R"(a+|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1470, STest, STest(R"(a*|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1471, STest, STest(R"(a?|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1472, STest, STest(R"(a+?|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1473, STest, STest(R"(a*?|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1474, STest, STest(R"(a??|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1475, STest, STest(R"(a{0,1}|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1476, STest, STest(R"(a{2}|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1477, STest, STest(R"(a{1,2}|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1478, STest, STest(R"(a{2,}|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1479, STest, STest(R"(a{0,1}?|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1480, STest, STest(R"(a{2}?|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1481, STest, STest(R"(a{1,2}?|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1482, STest, STest(R"(a{2,}?|b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1483, STest, STest(R"(a+|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1484, STest, STest(R"(a*|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1485, STest, STest(R"(a?|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1486, STest, STest(R"(a+?|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1487, STest, STest(R"(a*?|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1488, STest, STest(R"(a??|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1489, STest, STest(R"(a{0,1}|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1490, STest, STest(R"(a{2}|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1491, STest, STest(R"(a{1,2}|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1492, STest, STest(R"(a{2,}|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1493, STest, STest(R"(a{0,1}?|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1494, STest, STest(R"(a{2}?|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1495, STest, STest(R"(a{1,2}?|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1496, STest, STest(R"(a{2,}?|b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1497, STest, STest(R"(a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1498, STest, STest(R"(a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest1499, STest, STest(R"(a|a(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

