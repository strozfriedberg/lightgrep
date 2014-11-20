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

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1250, STest, STest(R"(a{2}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1251, STest, STest(R"(a{1,2}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1252, STest, STest(R"(a{2,}|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1253, STest, STest(R"(a{0,1}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1254, STest, STest(R"(a{2}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1255, STest, STest(R"(a{1,2}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1256, STest, STest(R"(a{2,}?|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1257, STest, STest("a+|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1258, STest, STest(R"(a*|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1259, STest, STest(R"(a?|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1260, STest, STest("a+?|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1261, STest, STest(R"(a*?|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1262, STest, STest(R"(a??|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1263, STest, STest(R"(a{0,1}|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1264, STest, STest("a{2}|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1265, STest, STest("a{1,2}|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1266, STest, STest("a{2,}|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1267, STest, STest(R"(a{0,1}?|b+?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1268, STest, STest("a{2}?|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1269, STest, STest("a{1,2}?|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1270, STest, STest("a{2,}?|b+?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1271, STest, STest(R"(a+|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1272, STest, STest(R"(a*|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1273, STest, STest(R"(a?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1274, STest, STest(R"(a+?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1275, STest, STest(R"(a*?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1276, STest, STest(R"(a??|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1277, STest, STest(R"(a{0,1}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1278, STest, STest(R"(a{2}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1279, STest, STest(R"(a{1,2}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1280, STest, STest(R"(a{2,}|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1281, STest, STest(R"(a{0,1}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1282, STest, STest(R"(a{2}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1283, STest, STest(R"(a{1,2}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1284, STest, STest(R"(a{2,}?|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1285, STest, STest(R"(a+|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1286, STest, STest(R"(a*|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1287, STest, STest(R"(a?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1288, STest, STest(R"(a+?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1289, STest, STest(R"(a*?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1290, STest, STest(R"(a??|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1291, STest, STest(R"(a{0,1}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1292, STest, STest(R"(a{2}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1293, STest, STest(R"(a{1,2}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1294, STest, STest(R"(a{2,}|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1295, STest, STest(R"(a{0,1}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1296, STest, STest(R"(a{2}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1297, STest, STest(R"(a{1,2}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1298, STest, STest(R"(a{2,}?|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1299, STest, STest(R"(a+|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1300, STest, STest(R"(a*|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1301, STest, STest(R"(a?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1302, STest, STest(R"(a+?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1303, STest, STest(R"(a*?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1304, STest, STest(R"(a??|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1305, STest, STest(R"(a{0,1}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1306, STest, STest(R"(a{2}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1307, STest, STest(R"(a{1,2}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1308, STest, STest(R"(a{2,}|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1309, STest, STest(R"(a{0,1}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1310, STest, STest(R"(a{2}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1311, STest, STest(R"(a{1,2}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1312, STest, STest(R"(a{2,}?|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1313, STest, STest("a+|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1314, STest, STest(R"(a*|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1315, STest, STest(R"(a?|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1316, STest, STest("a+?|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1317, STest, STest(R"(a*?|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1318, STest, STest(R"(a??|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1319, STest, STest(R"(a{0,1}|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1320, STest, STest("a{2}|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1321, STest, STest("a{1,2}|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1322, STest, STest("a{2,}|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1323, STest, STest(R"(a{0,1}?|b{2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1324, STest, STest("a{2}?|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1325, STest, STest("a{1,2}?|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1326, STest, STest("a{2,}?|b{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1327, STest, STest("a+|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1328, STest, STest(R"(a*|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1329, STest, STest(R"(a?|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1330, STest, STest("a+?|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1331, STest, STest(R"(a*?|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1332, STest, STest(R"(a??|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1333, STest, STest(R"(a{0,1}|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1334, STest, STest("a{2}|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1335, STest, STest("a{1,2}|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(15u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1336, STest, STest("a{2,}|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1337, STest, STest(R"(a{0,1}?|b{1,2})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1338, STest, STest("a{2}?|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1339, STest, STest("a{1,2}?|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1340, STest, STest("a{2,}?|b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1341, STest, STest("a+|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1342, STest, STest(R"(a*|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1343, STest, STest(R"(a?|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1344, STest, STest("a+?|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1345, STest, STest(R"(a*?|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1346, STest, STest(R"(a??|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1347, STest, STest(R"(a{0,1}|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1348, STest, STest("a{2}|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1349, STest, STest("a{1,2}|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1350, STest, STest("a{2,}|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1351, STest, STest(R"(a{0,1}?|b{2,})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1352, STest, STest("a{2}?|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1353, STest, STest("a{1,2}?|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1354, STest, STest("a{2,}?|b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1355, STest, STest(R"(a+|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1356, STest, STest(R"(a*|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1357, STest, STest(R"(a?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1358, STest, STest(R"(a+?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1359, STest, STest(R"(a*?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1360, STest, STest(R"(a??|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1361, STest, STest(R"(a{0,1}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1362, STest, STest(R"(a{2}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1363, STest, STest(R"(a{1,2}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1364, STest, STest(R"(a{2,}|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1365, STest, STest(R"(a{0,1}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1366, STest, STest(R"(a{2}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1367, STest, STest(R"(a{1,2}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1368, STest, STest(R"(a{2,}?|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1369, STest, STest("a+|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1370, STest, STest(R"(a*|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1371, STest, STest(R"(a?|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1372, STest, STest("a+?|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1373, STest, STest(R"(a*?|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1374, STest, STest(R"(a??|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1375, STest, STest(R"(a{0,1}|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1376, STest, STest("a{2}|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1377, STest, STest("a{1,2}|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1378, STest, STest("a{2,}|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1379, STest, STest(R"(a{0,1}?|b{2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1380, STest, STest("a{2}?|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1381, STest, STest("a{1,2}?|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1382, STest, STest("a{2,}?|b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1383, STest, STest("a+|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1384, STest, STest(R"(a*|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1385, STest, STest(R"(a?|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1386, STest, STest("a+?|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1387, STest, STest(R"(a*?|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1388, STest, STest(R"(a??|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1389, STest, STest(R"(a{0,1}|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1390, STest, STest("a{2}|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1391, STest, STest("a{1,2}|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1392, STest, STest("a{2,}|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1393, STest, STest(R"(a{0,1}?|b{1,2}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1394, STest, STest("a{2}?|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1395, STest, STest("a{1,2}?|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1396, STest, STest("a{2,}?|b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1397, STest, STest("a+|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1398, STest, STest(R"(a*|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1399, STest, STest(R"(a?|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1400, STest, STest("a+?|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1401, STest, STest(R"(a*?|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1402, STest, STest(R"(a??|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1403, STest, STest(R"(a{0,1}|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1404, STest, STest("a{2}|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1405, STest, STest("a{1,2}|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1406, STest, STest("a{2,}|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1407, STest, STest(R"(a{0,1}?|b{2,}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1408, STest, STest("a{2}?|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1409, STest, STest("a{1,2}?|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1410, STest, STest("a{2,}?|b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1411, STest, STest("a+|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1412, STest, STest(R"(a*|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1413, STest, STest(R"(a?|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1414, STest, STest("a+?|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1415, STest, STest(R"(a*?|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1416, STest, STest(R"(a??|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1417, STest, STest(R"(a{0,1}|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1418, STest, STest("a{2}|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1419, STest, STest("a{1,2}|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1420, STest, STest("a{2,}|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1421, STest, STest(R"(a{0,1}?|a|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1422, STest, STest("a{2}?|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1423, STest, STest("a{1,2}?|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1424, STest, STest("a{2,}?|a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1425, STest, STest("a+|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1426, STest, STest(R"(a*|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1427, STest, STest(R"(a?|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1428, STest, STest("a+?|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1429, STest, STest(R"(a*?|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1430, STest, STest(R"(a??|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1431, STest, STest(R"(a{0,1}|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1432, STest, STest("a{2}|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1433, STest, STest("a{1,2}|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1434, STest, STest("a{2,}|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1435, STest, STest(R"(a{0,1}?|b|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1436, STest, STest("a{2}?|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1437, STest, STest("a{1,2}?|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1438, STest, STest("a{2,}?|b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1439, STest, STest("a+|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1440, STest, STest(R"(a*|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1441, STest, STest(R"(a?|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1442, STest, STest("a+?|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1443, STest, STest(R"(a*?|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1444, STest, STest(R"(a??|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1445, STest, STest(R"(a{0,1}|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1446, STest, STest("a{2}|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1447, STest, STest("a{1,2}|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1448, STest, STest("a{2,}|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1449, STest, STest(R"(a{0,1}?|a|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1450, STest, STest("a{2}?|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1451, STest, STest("a{1,2}?|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1452, STest, STest("a{2,}?|a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1453, STest, STest("a+|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1454, STest, STest(R"(a*|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1455, STest, STest(R"(a?|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1456, STest, STest("a+?|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1457, STest, STest(R"(a*?|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1458, STest, STest(R"(a??|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1459, STest, STest(R"(a{0,1}|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1460, STest, STest("a{2}|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1461, STest, STest("a{1,2}|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1462, STest, STest("a{2,}|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1463, STest, STest(R"(a{0,1}?|b|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1464, STest, STest("a{2}?|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1465, STest, STest("a{1,2}?|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1466, STest, STest("a{2,}?|b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1467, STest, STest("a+|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1468, STest, STest(R"(a*|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1469, STest, STest(R"(a?|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1470, STest, STest("a+?|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1471, STest, STest(R"(a*?|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1472, STest, STest(R"(a??|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1473, STest, STest(R"(a{0,1}|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1474, STest, STest("a{2}|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1475, STest, STest("a{1,2}|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1476, STest, STest("a{2,}|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1477, STest, STest(R"(a{0,1}?|b|c)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1478, STest, STest("a{2}?|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1479, STest, STest("a{1,2}?|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1480, STest, STest("a{2,}?|b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1481, STest, STest("a|a(a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1482, STest, STest("a|b(a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1483, STest, STest("a|a(b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1484, STest, STest("a|b(b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1485, STest, STest("a|b(c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1486, STest, STest("a|aa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1487, STest, STest("a|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1488, STest, STest("a|ab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1489, STest, STest("a|bb")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1490, STest, STest("a|bc")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1491, STest, STest("a|aaa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1492, STest, STest("a|baa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1493, STest, STest("a|aba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1494, STest, STest("a|bba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1495, STest, STest("a|bca")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1496, STest, STest("a|aab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1497, STest, STest("a|bab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1498, STest, STest("a|abb")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1499, STest, STest("a|bbb")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}
