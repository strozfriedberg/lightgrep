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

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest250, STest, STest({"a+|b", "a|a|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(35u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[34]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest251, STest, STest({"a*?|(b)", "a+|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest252, STest, STest({"aa|b|a", "aba*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest253, STest, STest({"a??b", "a*?b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest254, STest, STest({"a??a", "a|ba??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest255, STest, STest({"a*|(b)", "aa|b??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest256, STest, STest({"a*?a|b", "a+|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest257, STest, STest({"a?a*?", "a+?b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest258, STest, STest({"a|a|ab", "a+a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest259, STest, STest({"a??|ab", "a+|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest260, STest, STest({"a*|b|c", "a|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest261, STest, STest({"a+?|a+?", "a|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest262, STest, STest({"a+|b", "a*?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest263, STest, STest({"a+|(b)", "a?a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest264, STest, STest({"a|a|b*", "a?a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest265, STest, STest({"a|b|c|c", "a|aa+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest266, STest, STest({"a?a*?", "a|b|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest267, STest, STest({"a+?|(a)", "a?|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest268, STest, STest({"a|bb|c", "ab*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(31u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[30]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest269, STest, STest({"a+|b|b", "aa|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest270, STest, STest({"a|b|ab", "ab|c??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest271, STest, STest({"a|b|b+?", "a?ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest272, STest, STest({"a??|a|a", "a*(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest273, STest, STest({"a|bc|c", "ab|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest274, STest, STest({"a|b(a)", "a*(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest275, STest, STest({"ab|a|b", "a|bc|."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(41u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[40]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest276, STest, STest({"abc+", "a|b|a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest277, STest, STest({"a|aa?", "ab|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest278, STest, STest({"a+?|b+?", "a|a|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest279, STest, STest({"a??|b+", "(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest280, STest, STest({"ab|a+", "aa|a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(15u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest281, STest, STest({"aa*", "abba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest282, STest, STest({"a*b?", "ab|ac"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 7, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 15, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 18, 1), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest283, STest, STest({"a*?a+?", "aab?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest284, STest, STest({"a??b*?", "a*|a+"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest285, STest, STest({"a|b|cb", "a|b|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest286, STest, STest({"a+a*?", "aa|bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest287, STest, STest({"a+?|a|a", "a??bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest288, STest, STest({"a*?bb", "(a|a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest289, STest, STest({"a??b??", "a??|b|c"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest290, STest, STest({"a+?|a*", "a+bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest291, STest, STest({"a|ab??", "a+b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest292, STest, STest({"((a))", "abac"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest293, STest, STest({"a|b|a+?", "ab|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest294, STest, STest({"a|baa", "a?a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest295, STest, STest({"a|aa?", "a*?a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest296, STest, STest({"a+?b?", "a??|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest297, STest, STest({"a??ab", "a|bc+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 27, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest298, STest, STest({"a+|b|b", "abb?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest299, STest, STest({"a|b|a??", "a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest300, STest, STest({"a|b|ba", "a+|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest301, STest, STest({"a|aa??", "a+?|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest302, STest, STest({"((a))", "a|b|(c)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest303, STest, STest({"ab(c)", "ab|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest304, STest, STest({"a??|a|a", "a?b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest305, STest, STest({"aba|b", "a|b|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest306, STest, STest({"a+?a", "a?|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest307, STest, STest({"a|b??", "a|b|c|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest308, STest, STest({"a+a+?", "a+?|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest309, STest, STest({"ab|cb", "a|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest310, STest, STest({"a*|a??", "a|b|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest311, STest, STest({"a*b*", "a+b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest312, STest, STest({"a??|b", "a|b|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest313, STest, STest({"a|b|c|.", "a+|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest314, STest, STest({"a|bb|c", "ab+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest315, STest, STest({"a?|a+?", "a??|b|c"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest316, STest, STest({"a+|aa", "a|bc*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest317, STest, STest({"a??|a+?", "ab|c*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest318, STest, STest({"a??b??", "a?|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest319, STest, STest({"aa(a)", "a|ab+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest320, STest, STest({"a|bb|b", "a+?|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest321, STest, STest({"a*a+?", "a?b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest322, STest, STest({"a+?|ba", "a+?b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest323, STest, STest({"a|a|a|b", "a??|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest324, STest, STest({"ab|b", "a+|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest325, STest, STest({"a?a", "a*?|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest326, STest, STest({"a+?|b|c", "a*a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(44u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[43]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest327, STest, STest({"aaa?", "(a)+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest328, STest, STest({"a??a+", "a?b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest329, STest, STest({"a*?a*?", "aba|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest330, STest, STest({"a*?|a+?", "a+|a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest331, STest, STest({"a+?|a*", "abbc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest332, STest, STest({"a*?bc", "a|baa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest333, STest, STest({"ab|a*", "a?ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest334, STest, STest({"a*?b|a", "a??|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest335, STest, STest({"ab|a?", "a+|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest336, STest, STest({"a*?|b??", "a+?|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest337, STest, STest({"a|b(b)", "aa|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest338, STest, STest({"a+?|(a)", "a|a|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest339, STest, STest({"a|a|ab", "a+?|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest340, STest, STest({"ab|b|c", "a+?bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest341, STest, STest({"a??|a+", "a|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest342, STest, STest({"aa|a*?", "a+b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest343, STest, STest({"a+|a*?", "a|a|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest344, STest, STest({"a+?a?", "a+a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest345, STest, STest({"aa|b*", "a+?|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest346, STest, STest({"a|bb+?", "a|bb|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest347, STest, STest({"abb", "a+|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest348, STest, STest({"aab", "a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest349, STest, STest({"a?b*?", "a?|a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest350, STest, STest({"(a)??", "a|aa|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest351, STest, STest({"abc?", "a+?a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest352, STest, STest({"aa|a", "a|aa??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest353, STest, STest({"a|b|a|c", "a*b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest354, STest, STest({"abb?", "aab??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest355, STest, STest({"a?|a|a", "a??|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest356, STest, STest({"a+|a*?", "a|b|ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest357, STest, STest({"a??|b+?", "ab|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest358, STest, STest({"a+|a+?", "a*?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest359, STest, STest({"a|abb", "a|b|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest360, STest, STest({"a*|a*", "(aa)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest361, STest, STest({"a|b|a|c", "a|bba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest362, STest, STest({"aaa|a", "a*|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest363, STest, STest({"a*bb", "aa|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest364, STest, STest({"(a)?", "aba|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest365, STest, STest({"a+|(b)", "(a)*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest366, STest, STest({"a*a?", "a+b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest367, STest, STest({"a??a*", "a*a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest368, STest, STest({"a?a?", "a+?|a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest369, STest, STest({"a?a|a", "ab|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest370, STest, STest({"aa|b*?", "a+b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest371, STest, STest({"a*|b|c", "ab|c|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest372, STest, STest({"a??a|a", "a?|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest373, STest, STest({"a|bb", "ab|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest374, STest, STest({"abba", "a?bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest375, STest, STest({"a*b", "a+(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest376, STest, STest({"a|a|b*?", "a?|b*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest377, STest, STest({"abc|c", "abb+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest378, STest, STest({"a|a|b+?", "a|a|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest379, STest, STest({"a?|b?", "a??bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest380, STest, STest({"a?ab", "a|a|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest381, STest, STest({"ab|c+", "a?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 27, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest382, STest, STest({"a*?|bb", "a|ba?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest383, STest, STest({"a??|b|c", "abc."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest384, STest, STest({"a?|b|a", "a*?a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest385, STest, STest({"a?|a+?", "ab|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest386, STest, STest({"a|a|(a)", "a?b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest387, STest, STest({"a+a?", "a*?|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest388, STest, STest({"a*?|a|b", "a|b|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest389, STest, STest({"a?|bc", "a+|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest390, STest, STest({"a*?|b|c", "aa|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest391, STest, STest({"a+?|aa", "abb*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest392, STest, STest({"a?|(b)", "a|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest393, STest, STest({"ab|c|.", "a*(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest394, STest, STest({"a*?|ab", "aaa*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest395, STest, STest({"a?b|b", "a*|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest396, STest, STest({"a+?a", "a*|bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest397, STest, STest({"aba*", "a+?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest398, STest, STest({"aaab", "a*|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest399, STest, STest({"a?|a|a", "a?|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest400, STest, STest({"aa|a?", "a*?(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest401, STest, STest({"a*?b*", "a|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest402, STest, STest({"a|b|c.", "a|bc|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest403, STest, STest({"a|bca", "a|bb??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest404, STest, STest({"a+a|b", "a|aa??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest405, STest, STest({"aa|b|b", "ab|c??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest406, STest, STest({"(a)(b)", "aa|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest407, STest, STest({"a?|b*?", "ab|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest408, STest, STest({"a+|a??", "a?b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest409, STest, STest({"a?|b*?", "a|b|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest410, STest, STest({"ab|a", "ab|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest411, STest, STest({"a+?a", "a+?|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest412, STest, STest({"a+bc", "a*a?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest413, STest, STest({"a+?b*", R"(a??(b))"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest414, STest, STest({"a+a|b", "a|bb*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest415, STest, STest({"a|a|a??", R"(a??(b))"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest416, STest, STest({"a+|a", "a*(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest417, STest, STest({"a|ab*?", "a+?|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest418, STest, STest({"a|b|(c)", "a|bc|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(41u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[40]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest419, STest, STest({"a?a*", "a+?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest420, STest, STest({"a|b(b)", "a|a|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest421, STest, STest({"a+b??", "a*?a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest422, STest, STest({"a|a|bc", "a?b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest423, STest, STest({"aab|a", "aaa+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest424, STest, STest({"a??|a*?", "a?|b??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest425, STest, STest({"ab|b+", "a+?|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest426, STest, STest({"abba", "a*|a*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest427, STest, STest({"ab|c|b", "a?|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest428, STest, STest({"a*?b*", "a*?|a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest429, STest, STest({"a+?a?", "a|b|b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest430, STest, STest({"a??|a|a", "a|bb|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest431, STest, STest({"a*?aa", "a|b(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest432, STest, STest({"a+b*?", "a|b|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest433, STest, STest({"a+?a??", "aa(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest434, STest, STest({"a?b+?", "a+a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest435, STest, STest({"a+?bb", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest436, STest, STest({"ab|a+", "a|a|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest437, STest, STest({"a+?|a+", "a|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest438, STest, STest({"a|b|c|a", "a|a|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(44u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[43]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest439, STest, STest({"a??|b|b", "((a))"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest440, STest, STest({"a*a+", "a??|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest441, STest, STest({"a*b|b", "a??a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest442, STest, STest({"a|bc|.", "a|b|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest443, STest, STest({"a+?ab", "a+?a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest444, STest, STest({"a+?|bb", "ab|c|."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(37u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[36]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest445, STest, STest({"a|a|ba", "a|b(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest446, STest, STest({"ab??", "ab|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest447, STest, STest({"aaa", "a??|a*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest448, STest, STest({"a|b|c", "aba|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(37u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[36]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest449, STest, STest({"a|a|a|b", "ab|a|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest450, STest, STest({"a|bc+?", "abc|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(23u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest451, STest, STest({"a|ba?", "a?|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest452, STest, STest({"ab|b+", "a?b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest453, STest, STest({"a+?b+?", "a*b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest454, STest, STest({"a|bb+", "aa|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(32u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[31]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest455, STest, STest({"a+ab", "a+|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest456, STest, STest({"a+|bb", "abb|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest457, STest, STest({"ab|a+", "aaa*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest458, STest, STest({"a+", "a*?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest459, STest, STest({"abbb", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest460, STest, STest({"ab|aa", "aba|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest461, STest, STest({"a*?b|b", "a*?|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest462, STest, STest({"abc?", "a+?b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest463, STest, STest({"(a)*?", "a??|b|b"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest464, STest, STest({"a+?a+?", "a|ba+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest465, STest, STest({"ab|c+?", "(a)??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest466, STest, STest({"a*", "a+|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest467, STest, STest({"ab(c)", "(a*)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest468, STest, STest({"a|a|bb", "a+bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest469, STest, STest({"a*|bb", "a??|(a)"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest470, STest, STest({"a|a|(a)", "aa|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest471, STest, STest({"a|a(b)", "a+?|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest472, STest, STest({"a??", "a|bb|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest473, STest, STest({"abb*", "a??b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest474, STest, STest({"a|b|b|a", "a*?|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest475, STest, STest({"a|b|ab", "a|bc+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(32u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 27, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[31]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest476, STest, STest({"a*(b)", "aa|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest477, STest, STest({"ab|b", "a+b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest478, STest, STest({"a*?|(a)", "a??|b|b"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest479, STest, STest({"a*b*", "a?|a"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest480, STest, STest({"aa|a??", "a??|ba"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest481, STest, STest({"a+?|(a)", "a?a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest482, STest, STest({"a??|b*?", "a+|ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest483, STest, STest({"a*a??", "a|a(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest484, STest, STest({"a*?b+", "a|b|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest485, STest, STest({"a+a+?", "a*|b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest486, STest, STest({"a|bb+?", "aba|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest487, STest, STest({"a*?a??", "a*?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest488, STest, STest({"ab|c*", "a*|a|b"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest489, STest, STest({"a|bc|a", "ab|bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest490, STest, STest({"(a)*?", "aab*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest491, STest, STest({"a?a", "a|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest492, STest, STest({"a+|b+", "a+a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest493, STest, STest({"a|b|c|.", "a|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest494, STest, STest({"a*?|b??", "a+?|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest495, STest, STest({"a*?|ab", "a*?ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest496, STest, STest({"a|bc*?", "a*?b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest497, STest, STest({"a?|a", "a?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest498, STest, STest({"a?a", "a+?b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest499, STest, STest({"ab|a|b", "a|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(35u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[34]);
}
