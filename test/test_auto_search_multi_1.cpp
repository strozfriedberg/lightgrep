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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest0, STest, STest({"a+?a*?", "ab|a+"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest1, STest, STest({"a|aa?", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[14]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest2, STest, STest({"a|bb+?", "a+|b??"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest3, STest, STest({"aaa+", "a+?|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest4, STest, STest({"a?|a??", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest5, STest, STest({"a+?|b+?", "a|aa|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest6, STest, STest({"a??b+", "a*?a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest7, STest, STest({"a|a|b?", "a+b?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest8, STest, STest({"aab+?", "a*aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest9, STest, STest({"ab|b+", "(a)*?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest10, STest, STest({"a*?", "a?|a+"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest11, STest, STest({"a+b|c", "ab|b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest12, STest, STest({"a?|b|b", "a+|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest13, STest, STest({"a?|a+", "a|b|c|."})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest14, STest, STest({"ab|b|b", "aabc"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest15, STest, STest({"abab", "ab(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest16, STest, STest({"ab|c|.", "a|bb*"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[40]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest17, STest, STest({"a+|b", "aa|bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest18, STest, STest({"a*?|(b)", "a|ab|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest19, STest, STest({"ab|ba", "a|abb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest20, STest, STest({"a*|ba", "ab|a|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest21, STest, STest({"a|b|cc", "a|bc|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(40u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[39]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest22, STest, STest({"a|a", "a??|bc"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest23, STest, STest({"aa|ab", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest24, STest, STest({"a*a?", "a|abb"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest25, STest, STest({"aa??", "a*|a*?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest26, STest, STest({"a??a??", "a|b|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest27, STest, STest({"a|b|c|a", "abb|a"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[13]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest28, STest, STest({"a?|a*", "a?|b+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest29, STest, STest({"a+b|a", "a|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest30, STest, STest({"a*?a", "a??b+?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest31, STest, STest({"a*|b*?", "a|aa|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest32, STest, STest({R"((a??))", "a|a|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest33, STest, STest({"ab|c|c", "a+|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(37u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[36]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest34, STest, STest({"a*?a", "a|b|c?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest35, STest, STest({"a+?|aa", "a*|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest36, STest, STest({"abba", "abc|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest37, STest, STest({"a+a+?", "a+aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest38, STest, STest({"a*|b|a", "a|ab+"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest39, STest, STest({"abc+?", "a*?|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest40, STest, STest({"aa??", "abc+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest41, STest, STest({"abca", "ab|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest42, STest, STest({"a??|b*", "a*a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest43, STest, STest({"a+|a", "a|b|a|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest44, STest, STest({"(a*)", "aaa??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest45, STest, STest({"a|aa*", "abb??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest46, STest, STest({"a|bc+?", "a+?ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest47, STest, STest({"a??|bc", "a+?|a?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest48, STest, STest({"aa|a|a", "a??a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest49, STest, STest({"a|aab", "a|a|a+"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest50, STest, STest({"a?|a*?", "a|a|aa"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest51, STest, STest({"a|b|c.", "a|ab|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(40u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[39]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest52, STest, STest({"a??|a*", "a|a|bb"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest53, STest, STest({"a+?b?", "a??a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest54, STest, STest({"ab|c??", "a|bb+"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest55, STest, STest({"abb|a", "aab??"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest56, STest, STest({"a+|ab", "a*|(a)"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest57, STest, STest({"ab|bc", "a|b|ac"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest58, STest, STest({"a+?a*", "aabc"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest59, STest, STest({"a|a??", "a|b|a|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest60, STest, STest({"a|a??", "ab?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest61, STest, STest({"a|b|bc", "a*a+"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest62, STest, STest({"aa|a??", "a|b|aa"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest63, STest, STest({"ab|c|b", "a|b|c??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest64, STest, STest({"(a|a)", "a+?b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest65, STest, STest({"aaa|b", "a*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest66, STest, STest({"a?a?", "a+aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest67, STest, STest({"a+|b*", "a|bb+"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest68, STest, STest({"aa|ba", "aa|a*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest69, STest, STest({"ab??", "a?|b?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest70, STest, STest({"a??|b*?", "a??b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest71, STest, STest({"a??|b*?", "a+?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest72, STest, STest({"ab|a??", "a+b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest73, STest, STest({"a|b|a+?", "a|ab"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest74, STest, STest({"aaa|b", "aab|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest75, STest, STest({"ab|(a)", "a+?|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[17]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest76, STest, STest({"a|b|b*?", "a|bc+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest77, STest, STest({"a+|bb", "ab|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest78, STest, STest({"(a?)", "a*a+"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest79, STest, STest({"a+?|b|c", "a*|ab"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest80, STest, STest({"a*|b|c", "a|aba"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest81, STest, STest({"ab|c?", "a+?|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest82, STest, STest({"a|bac", "a|b|a+?"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(15, 18, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest83, STest, STest({"a+a*", "a??a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest84, STest, STest({"a+|a|b", "a|b|a|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(44u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[9]);
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
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[43]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest85, STest, STest({"a+|b|a", "a*?a|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest86, STest, STest({"a*a+", "a?a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest87, STest, STest({"a|bc|b", "a*|b*"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest88, STest, STest({"a+?|b?", "(a)|(b)"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest89, STest, STest({"a*a??", "a??|a|a"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest90, STest, STest({"a|a|b*", "a|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest91, STest, STest({"a??|a??", "a?|b"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest92, STest, STest({"a|abb", "a|ba??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest93, STest, STest({"a+|a*", "a*?|(a)"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest94, STest, STest({"a|b|(b)", "aa|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest95, STest, STest({"a??b?", "aaa|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest96, STest, STest({"a|a|a?", "a*?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest97, STest, STest({"aa|a|a", "a*|b+?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest98, STest, STest({"a*?|b|c", "a|aa|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest99, STest, STest({"a|b|c*?", "abb|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest100, STest, STest({"abb*", "a??|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest101, STest, STest({"(a?)", "aaa*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest102, STest, STest({"ab|bb", "ab|c."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest103, STest, STest({"a|a??", "a+?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest104, STest, STest({"a", "aa"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest105, STest, STest({"aa|a|a", "a+|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(15u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest106, STest, STest({"a|ab+", "a|a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest107, STest, STest({"a|b|c|.", "a??a+?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest108, STest, STest({"aa|(a)", "a|b|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest109, STest, STest({"aa|a|b", "a|b|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest110, STest, STest({"a*b", "aa*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest111, STest, STest({"a?aa", "a+a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest112, STest, STest({"aaa*", "a*a+"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest113, STest, STest({"aa|bb", "ab|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest114, STest, STest({"a+?|ab", "ab+?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest115, STest, STest({"a+?", "(a)*"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest116, STest, STest({"a|b|ab", "aab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest117, STest, STest({"a??a?", "a*?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest118, STest, STest({"a??|(a)", "a|a|b+?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest119, STest, STest({"a*?|b??", "a|abc"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest120, STest, STest({"a*?|b|c", "a+?|a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest121, STest, STest({"a|b*", "(a)(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest122, STest, STest({"a+?b", "a|aba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest123, STest, STest({"aa(a)", "a|b|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest124, STest, STest({"a|a|ba", "a?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest125, STest, STest({"a|bbc", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 23, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest126, STest, STest({"a|aa*", "abc|."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(36u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[35]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest127, STest, STest({"aa|ab", "(a)(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest128, STest, STest({"a+?|(b)", "a+?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest129, STest, STest({"a?b|b", "aaba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest130, STest, STest({"a|ba+", "a+|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest131, STest, STest({"a*|(b)", "a?a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest132, STest, STest({"a+|a*", "a|ba*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(15u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest133, STest, STest({"a??|a*?", "abb??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest134, STest, STest({"a+a??", "a+?|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest135, STest, STest({"a*?|b?", "a*?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest136, STest, STest({"aa+", "a+bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest137, STest, STest({"a|a(b)", "a+?|b|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest138, STest, STest({"a?bc", "a|a|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest139, STest, STest({"a+?b|b", "a+|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest140, STest, STest({"aba+", "aaa+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest141, STest, STest({"a*|b*", "a|aa|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest142, STest, STest({"abb|a", "a?|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest143, STest, STest({"a+?b+?", "a+|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest144, STest, STest({"a*?a*", "a|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest145, STest, STest({"a|ba", "ab|ca"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(15u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest146, STest, STest({"a?|b+?", "ab|bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest147, STest, STest({"aaa*?", "abca"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest148, STest, STest({"a+?|b??", "a*?|a+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest149, STest, STest({"aba*?", "a+?a??"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest150, STest, STest({"ab|c?", "aaa?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest151, STest, STest({"a|b*", "a|bbc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(20, 23, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest152, STest, STest({"a+|b", "a|baa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest153, STest, STest({"a+bb", "a?|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest154, STest, STest({"a|b|bc", "a*?|b?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest155, STest, STest({"a|b?", "a+a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest156, STest, STest({"a?|a+?", "a*|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest157, STest, STest({"a|b|c+?", "a+|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(35u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[34]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest158, STest, STest({"a|b|b*", "aaa+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest159, STest, STest({"a|a(a)", "ab|c."})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest160, STest, STest({"a*(b)", "a|a*?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest161, STest, STest({"a+ab", "a?aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest162, STest, STest({"a+|b+?", "(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest163, STest, STest({"a+ba", "a+?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest164, STest, STest({"ab|c", "a??|b|c"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest165, STest, STest({"a|a|b??", "a|b|a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest166, STest, STest({"aab*?", "(a|b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest167, STest, STest({"a|ba+?", "aab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest168, STest, STest({"abcc", "a|bc+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest169, STest, STest({"a|a|a+?", "a*?|b+?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest170, STest, STest({"a*?", "a|ab"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest171, STest, STest({"a+bb", "a|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest172, STest, STest({"a+ab", "ab|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest173, STest, STest({"a?b+?", "ab|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest174, STest, STest({"a*a?", "a+|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest175, STest, STest({"a*?(a)", "a|aa|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest176, STest, STest({"a?|aa", "a+b??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest177, STest, STest({"aa|a", "aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest178, STest, STest({"a*|ab", "a|b|(a)"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest179, STest, STest({"a?|b??", "a*?a?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest180, STest, STest({"a|b|(b)", "a??b*"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest181, STest, STest({"a*?|b+", "a*?|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest182, STest, STest({"ab|ac", "a|a|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 7, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 15, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 18, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest183, STest, STest({"a|ba?", "a+b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(23u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest184, STest, STest({"a|bcc", "a?|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(23, 26, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest185, STest, STest({"ab|(a)", "a*|(b)"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest186, STest, STest({"a*?b|a", "aab|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(23u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest187, STest, STest({"a|b|b?", "a+?|b|b"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest188, STest, STest({"ab|aa", "a|b|c|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(33u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[32]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest189, STest, STest({"a|ba*", "ab|c|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest190, STest, STest({"aaab", "a??b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest191, STest, STest({"a|b|(a)", "a?|b*?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest192, STest, STest({"a|b|cb", "a|b|c|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(47u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[43]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[44]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[45]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[46]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest193, STest, STest({"a+|bc", "ab?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest194, STest, STest({"a??|a+?", "a??ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest195, STest, STest({"a|bc|c", "a+?b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest196, STest, STest({"a+?ba", "a??|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest197, STest, STest({"a?|a|b", "a*|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest198, STest, STest({"aba|b", "a*?a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest199, STest, STest({"a??|a*?", "abcb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest200, STest, STest({"a|baa", "aaa??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest201, STest, STest({"a?|bb", "a|b|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest202, STest, STest({"aa|b|b", "ab(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest203, STest, STest({"a?|a|b", "a?a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest204, STest, STest({"ab|b|c", "a+aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest205, STest, STest({"a??|bc", "(a+?)"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest206, STest, STest({"ab|bb", "a+?|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(23u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest207, STest, STest({"a|aa+?", "ab|a?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest208, STest, STest({"a??|a+", "abb*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest209, STest, STest({"ab??", "a+b?"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest210, STest, STest({"a+b+", "a??a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest211, STest, STest({"(a)(a)", "a+?bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest212, STest, STest({"a??aa", "a|bca"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest213, STest, STest({"a+?a?", "a|a|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(36u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[16]);
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
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[35]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest214, STest, STest({"a??ba", "a+?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest215, STest, STest({"a|b|aa", "a*bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest216, STest, STest({"a|aa??", "aaa+"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest217, STest, STest({"a?|a?", "a*a|a"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest218, STest, STest({"ab|a|b", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest219, STest, STest({"aab+?", "a+?a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest220, STest, STest({"a|ab*", "a*b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest221, STest, STest({"a*ab", "ab|ac"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 7, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 15, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 18, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest222, STest, STest({"a|b|b|a", "(a)|(a)"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest223, STest, STest({"a?aa", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest224, STest, STest({"ab|c|c", "a|b|a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest225, STest, STest({"a?|bb", "a*|b+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest226, STest, STest({"a+|ab", "a?b*?"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest227, STest, STest({"aab*", "(a*)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest228, STest, STest({"abac", "a|b|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest229, STest, STest({"a+|b*?", "a|b|c."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest230, STest, STest({"aba|c", "a|ab|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest231, STest, STest({"a+|ab", "aab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest232, STest, STest({"aa(b)", "a*?|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest233, STest, STest({"a|bc.", "a|abc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21u, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(11, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest234, STest, STest({"a|b(b)", "a|bab"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(9, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest235, STest, STest({"aa|bc", "a?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest236, STest, STest({"a|b|(b)", "a|a|a??"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest237, STest, STest({"ab|c|a", "(a?)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest238, STest, STest({"((a))", "a+b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest239, STest, STest({"a|b|a*?", "a??|a+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest240, STest, STest({"aab", "a*a?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest241, STest, STest({"a+|b*?", "a+?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest242, STest, STest({"a?aa", "a*|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest243, STest, STest({"a|bb+?", "abbc"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest244, STest, STest({"abc|a", "a+|a+"})) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest245, STest, STest({"a+?|a??", "abb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest246, STest, STest({"ab|a+?", "a?|(a)"})) {
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

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest247, STest, STest({"a+b+", "ab|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest248, STest, STest({"ab|c*", "aab*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternSearchTest249, STest, STest({"a??bb", "ab|c+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 27, 1), fixture.Hits[10]);
}
