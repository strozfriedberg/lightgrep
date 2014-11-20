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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1625, STest, STest("a|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1626, STest, STest("a|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1627, STest, STest("a|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1628, STest, STest("a|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1629, STest, STest("a|a|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1630, STest, STest("a|b|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1631, STest, STest("a|a|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1632, STest, STest("a|b|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1633, STest, STest("a|b|ca")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1634, STest, STest("a|a|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1635, STest, STest("a|b|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1636, STest, STest("a|a|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1637, STest, STest("a|b|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1638, STest, STest("a|b|cb")) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1639, STest, STest("a|b|ac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1640, STest, STest("a|a|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1641, STest, STest("a|b|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1642, STest, STest("a|b|cc")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1643, STest, STest("a|b|c.")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1644, STest, STest("a|a|a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1645, STest, STest(R"(a|a|a*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1646, STest, STest(R"(a|a|a?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1647, STest, STest("a|a|a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1648, STest, STest(R"(a|a|a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1649, STest, STest(R"(a|a|a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1650, STest, STest(R"(a|a|a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1651, STest, STest("a|a|a{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1652, STest, STest("a|a|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1653, STest, STest("a|a|a{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1654, STest, STest(R"(a|a|a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1655, STest, STest("a|a|a{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1656, STest, STest("a|a|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1657, STest, STest("a|a|a{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1658, STest, STest("a|b|a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1659, STest, STest(R"(a|b|a*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1660, STest, STest(R"(a|b|a?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1661, STest, STest("a|b|a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1662, STest, STest(R"(a|b|a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1663, STest, STest(R"(a|b|a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1664, STest, STest(R"(a|b|a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1665, STest, STest("a|b|a{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1666, STest, STest("a|b|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1667, STest, STest("a|b|a{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1668, STest, STest(R"(a|b|a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1669, STest, STest("a|b|a{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1670, STest, STest("a|b|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1671, STest, STest("a|b|a{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1672, STest, STest("a|a|b+")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1673, STest, STest(R"(a|a|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1674, STest, STest(R"(a|a|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1675, STest, STest("a|a|b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1676, STest, STest(R"(a|a|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1677, STest, STest(R"(a|a|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1678, STest, STest(R"(a|a|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1679, STest, STest("a|a|b{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1680, STest, STest("a|a|b{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1681, STest, STest("a|a|b{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1682, STest, STest(R"(a|a|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1683, STest, STest("a|a|b{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1684, STest, STest("a|a|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1685, STest, STest("a|a|b{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1686, STest, STest("a|b|b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1687, STest, STest(R"(a|b|b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1688, STest, STest(R"(a|b|b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1689, STest, STest("a|b|b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1690, STest, STest(R"(a|b|b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1691, STest, STest(R"(a|b|b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1692, STest, STest(R"(a|b|b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1693, STest, STest("a|b|b{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1694, STest, STest("a|b|b{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1695, STest, STest("a|b|b{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1696, STest, STest(R"(a|b|b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1697, STest, STest("a|b|b{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1698, STest, STest("a|b|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1699, STest, STest("a|b|b{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1700, STest, STest("a|b|c+")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 27, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1701, STest, STest(R"(a|b|c*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1702, STest, STest(R"(a|b|c?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1703, STest, STest("a|b|c+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1704, STest, STest(R"(a|b|c*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1705, STest, STest(R"(a|b|c??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1706, STest, STest(R"(a|b|c{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1707, STest, STest("a|b|c{2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1708, STest, STest("a|b|c{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1709, STest, STest("a|b|c{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 27, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1710, STest, STest(R"(a|b|c{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1711, STest, STest("a|b|c{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1712, STest, STest("a|b|c{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1713, STest, STest("a|b|c{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1714, STest, STest("a|a|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1715, STest, STest("a|b|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1716, STest, STest("a|a|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1717, STest, STest("a|b|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1718, STest, STest("a|b|c|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1719, STest, STest("a|a|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1720, STest, STest("a|b|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1721, STest, STest("a|a|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1722, STest, STest("a|b|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1723, STest, STest("a|b|c|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1724, STest, STest("a|b|a|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1725, STest, STest("a|a|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1726, STest, STest("a|b|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1727, STest, STest("a|b|c|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest1728, STest, STest("a|b|c|.")) {
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

