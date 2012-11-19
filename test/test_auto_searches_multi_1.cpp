/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest0, STest, STest({"a+?a*?", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest1, STest, STest({"a|aa?", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest2, STest, STest({"a|bb+?", "a+|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest3, STest, STest({"aaa+", "a+?|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest4, STest, STest({"a?|a??", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest5, STest, STest({"a+?|b+?", "a|aa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest6, STest, STest({"a??b+", "a*?a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest7, STest, STest({"a|a|b?", "a+b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest8, STest, STest({"aab+?", "a*aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest9, STest, STest({"ab|b+", "(a)*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest10, STest, STest({"a*?", "a?|a+"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest11, STest, STest({"a+b|c", "ab|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest12, STest, STest({"a?|b|b", "a+|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest13, STest, STest({"a?|a+", "a|b|c|."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest14, STest, STest({"ab|b|b", "aabc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest15, STest, STest({"abab", "ab(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest16, STest, STest({"ab|c|.", "a|bb*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest17, STest, STest({"a+|b", "aa|bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest18, STest, STest({"a*?|(b)", "a|ab|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest19, STest, STest({"ab|ba", "a|abb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest20, STest, STest({"a*|ba", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest21, STest, STest({"a|b|cc", "a|bc|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest22, STest, STest({"a|a", "a??|bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest23, STest, STest({"aa|ab", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest24, STest, STest({"a*a?", "a|abb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest25, STest, STest({"aa??", "a*|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest26, STest, STest({"a??a??", "a|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest27, STest, STest({"a|b|c|a", "abb|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest28, STest, STest({"a?|a*", "a?|b+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest29, STest, STest({"a+b|a", "a|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest30, STest, STest({"a*?a", "a??b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest31, STest, STest({"a*|b*?", "a|aa|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest32, STest, STest({R"((a??))", "a|a|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest33, STest, STest({"ab|c|c", "a+|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest34, STest, STest({"a*?a", "a|b|c?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest35, STest, STest({"a+?|aa", "a*|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest36, STest, STest({"abba", "abc|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest37, STest, STest({"a+a+?", "a+aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest38, STest, STest({"a*|b|a", "a|ab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest39, STest, STest({"abc+?", "a*?|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest40, STest, STest({"aa??", "abc+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest41, STest, STest({"abca", "ab|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest42, STest, STest({"a??|b*", "a*a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest43, STest, STest({"a+|a", "a|b|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest44, STest, STest({"(a*)", "aaa??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest45, STest, STest({"a|aa*", "abb??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest46, STest, STest({"a|bc+?", "a+?ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest47, STest, STest({"a??|bc", "a+?|a?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest48, STest, STest({"aa|a|a", "a??a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest49, STest, STest({"a|aab", "a|a|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest50, STest, STest({"a?|a*?", "a|a|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest51, STest, STest({"a|b|c.", "a|ab|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest52, STest, STest({"a??|a*", "a|a|bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest53, STest, STest({"a+?b?", "a??a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest54, STest, STest({"ab|c??", "a|bb+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest55, STest, STest({"abb|a", "aab??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest56, STest, STest({"a+|ab", "a*|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest57, STest, STest({"ab|bc", "a|b|ac"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest58, STest, STest({"a+?a*", "aabc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest59, STest, STest({"a|a??", "a|b|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest60, STest, STest({"a|a??", "ab?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest61, STest, STest({"a|b|bc", "a*a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest62, STest, STest({"aa|a??", "a|b|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest63, STest, STest({"ab|c|b", "a|b|c??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest64, STest, STest({"(a|a)", "a+?b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest65, STest, STest({"aaa|b", "a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest66, STest, STest({"a?a?", "a+aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest67, STest, STest({"a+|b*", "a|bb+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest68, STest, STest({"aa|ba", "aa|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest69, STest, STest({"ab??", "a?|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest70, STest, STest({"a??|b*?", "a??b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest71, STest, STest({"a??|b*?", "a+?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest72, STest, STest({"ab|a??", "a+b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest73, STest, STest({"a|b|a+?", "a|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest74, STest, STest({"aaa|b", "aab|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest75, STest, STest({"ab|(a)", "a+?|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest76, STest, STest({"a|b|b*?", "a|bc+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest77, STest, STest({"a+|bb", "ab|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest78, STest, STest({"(a?)", "a*a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest79, STest, STest({"a+?|b|c", "a*|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest80, STest, STest({"a*|b|c", "a|aba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest81, STest, STest({"ab|c?", "a+?|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest82, STest, STest({"a|bac", "a|b|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest83, STest, STest({"a+a*", "a??a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest84, STest, STest({"a+|a|b", "a|b|a|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest85, STest, STest({"a+|b|a", "a*?a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest86, STest, STest({"a*a+", "a?a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest87, STest, STest({"a|bc|b", "a*|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest88, STest, STest({"a+?|b?", "(a)|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest89, STest, STest({"a*a??", "a??|a|a"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest90, STest, STest({"a|a|b*", "a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest91, STest, STest({"a??|a??", "a?|b"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest92, STest, STest({"a|abb", "a|ba??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest93, STest, STest({"a+|a*", "a*?|(a)"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest94, STest, STest({"a|b|(b)", "aa|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest95, STest, STest({"a??b?", "aaa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest96, STest, STest({"a|a|a?", "a*?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest97, STest, STest({"aa|a|a", "a*|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest98, STest, STest({"a*?|b|c", "a|aa|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest99, STest, STest({"a|b|c*?", "abb|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest100, STest, STest({"abb*", "a??|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest101, STest, STest({"(a?)", "aaa*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest102, STest, STest({"ab|bb", "ab|c."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest103, STest, STest({"a|a??", "a+?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest104, STest, STest({"a", "aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest105, STest, STest({"aa|a|a", "a+|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest106, STest, STest({"a|ab+", "a|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest107, STest, STest({"a|b|c|.", "a??a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest108, STest, STest({"aa|(a)", "a|b|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest109, STest, STest({"aa|a|b", "a|b|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest110, STest, STest({"a*b", "aa*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest111, STest, STest({"a?aa", "a+a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest112, STest, STest({"aaa*", "a*a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest113, STest, STest({"aa|bb", "ab|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest114, STest, STest({"a+?|ab", "ab+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest115, STest, STest({"a+?", "(a)*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest116, STest, STest({"a|b|ab", "aab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest117, STest, STest({"a??a?", "a*?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest118, STest, STest({"a??|(a)", "a|a|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest119, STest, STest({"a*?|b??", "a|abc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest120, STest, STest({"a*?|b|c", "a+?|a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest121, STest, STest({"a|b*", "(a)(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest122, STest, STest({"a+?b", "a|aba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest123, STest, STest({"aa(a)", "a|b|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest124, STest, STest({"a|a|ba", "a?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest125, STest, STest({"a|bbc", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest126, STest, STest({"a|aa*", "abc|."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest127, STest, STest({"aa|ab", "(a)(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest128, STest, STest({"a+?|(b)", "a+?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest129, STest, STest({"a?b|b", "aaba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest130, STest, STest({"a|ba+", "a+|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest131, STest, STest({"a*|(b)", "a?a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest132, STest, STest({"a+|a*", "a|ba*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest133, STest, STest({"a??|a*?", "abb??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest134, STest, STest({"a+a??", "a+?|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest135, STest, STest({"a*?|b?", "a*?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest136, STest, STest({"aa+", "a+bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest137, STest, STest({"a|a(b)", "a+?|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest138, STest, STest({"a?bc", "a|a|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest139, STest, STest({"a+?b|b", "a+|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest140, STest, STest({"aba+", "aaa+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest141, STest, STest({"a*|b*", "a|aa|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest142, STest, STest({"abb|a", "a?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest143, STest, STest({"a+?b+?", "a+|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest144, STest, STest({"a*?a*", "a|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest145, STest, STest({"a|ba", "ab|ca"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest146, STest, STest({"a?|b+?", "ab|bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest147, STest, STest({"aaa*?", "abca"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest148, STest, STest({"a+?|b??", "a*?|a+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest149, STest, STest({"aba*?", "a+?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest150, STest, STest({"ab|c?", "aaa?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest151, STest, STest({"a|b*", "a|bbc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest152, STest, STest({"a+|b", "a|baa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest153, STest, STest({"a+bb", "a?|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest154, STest, STest({"a|b|bc", "a*?|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest155, STest, STest({"a|b?", "a+a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest156, STest, STest({"a?|a+?", "a*|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest157, STest, STest({"a|b|c+?", "a+|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest158, STest, STest({"a|b|b*", "aaa+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest159, STest, STest({"a|a(a)", "ab|c."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest160, STest, STest({"a*(b)", "a|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest161, STest, STest({"a+ab", "a?aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest162, STest, STest({"a+|b+?", "(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest163, STest, STest({"a+ba", "a+?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest164, STest, STest({"ab|c", "a??|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest165, STest, STest({"a|a|b??", "a|b|a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest166, STest, STest({"aab*?", "(a|b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest167, STest, STest({"a|ba+?", "aab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest168, STest, STest({"abcc", "a|bc+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest169, STest, STest({"a|a|a+?", "a*?|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest170, STest, STest({"a*?", "a|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest171, STest, STest({"a+bb", "a|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest172, STest, STest({"a+ab", "ab|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest173, STest, STest({"a?b+?", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest174, STest, STest({"a*a?", "a+|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest175, STest, STest({"a*?(a)", "a|aa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest176, STest, STest({"a?|aa", "a+b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest177, STest, STest({"aa|a", "aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest178, STest, STest({"a*|ab", "a|b|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest179, STest, STest({"a?|b??", "a*?a?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest180, STest, STest({"a|b|(b)", "a??b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest181, STest, STest({"a*?|b+", "a*?|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest182, STest, STest({"ab|ac", "a|a|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest183, STest, STest({"a|ba?", "a+b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest184, STest, STest({"a|bcc", "a?|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest185, STest, STest({"ab|(a)", "a*|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest186, STest, STest({"a*?b|a", "aab|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest187, STest, STest({"a|b|b?", "a+?|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest188, STest, STest({"ab|aa", "a|b|c|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest189, STest, STest({"a|ba*", "ab|c|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest190, STest, STest({"aaab", "a??b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest191, STest, STest({"a|b|(a)", "a?|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest192, STest, STest({"a|b|cb", "a|b|c|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest193, STest, STest({"a+|bc", "ab?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest194, STest, STest({"a??|a+?", "a??ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest195, STest, STest({"a|bc|c", "a+?b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest196, STest, STest({"a+?ba", "a??|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest197, STest, STest({"a?|a|b", "a*|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest198, STest, STest({"aba|b", "a*?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest199, STest, STest({"a??|a*?", "abcb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest200, STest, STest({"a|baa", "aaa??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest201, STest, STest({"a?|bb", "a|b|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest202, STest, STest({"aa|b|b", "ab(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest203, STest, STest({"a?|a|b", "a?a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest204, STest, STest({"ab|b|c", "a+aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest205, STest, STest({"a??|bc", "(a+?)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest206, STest, STest({"ab|bb", "a+?|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest207, STest, STest({"a|aa+?", "ab|a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest208, STest, STest({"a??|a+", "abb*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest209, STest, STest({"ab??", "a+b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest210, STest, STest({"a+b+", "a??a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest211, STest, STest({"(a)(a)", "a+?bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest212, STest, STest({"a??aa", "a|bca"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest213, STest, STest({"a+?a?", "a|a|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest214, STest, STest({"a??ba", "a+?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest215, STest, STest({"a|b|aa", "a*bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest216, STest, STest({"a|aa??", "aaa+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest217, STest, STest({"a?|a?", "a*a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest218, STest, STest({"ab|a|b", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest219, STest, STest({"aab+?", "a+?a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest220, STest, STest({"a|ab*", "a*b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest221, STest, STest({"a*ab", "ab|ac"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest222, STest, STest({"a|b|b|a", "(a)|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest223, STest, STest({"a?aa", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest224, STest, STest({"ab|c|c", "a|b|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest225, STest, STest({"a?|bb", "a*|b+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest226, STest, STest({"a+|ab", "a?b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest227, STest, STest({"aab*", "(a*)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest228, STest, STest({"abac", "a|b|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest229, STest, STest({"a+|b*?", "a|b|c."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest230, STest, STest({"aba|c", "a|ab|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest231, STest, STest({"a+|ab", "aab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest232, STest, STest({"aa(b)", "a*?|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest233, STest, STest({"a|bc.", "a|abc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest234, STest, STest({"a|b(b)", "a|bab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest235, STest, STest({"aa|bc", "a?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest236, STest, STest({"a|b|(b)", "a|a|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest237, STest, STest({"ab|c|a", "(a?)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest238, STest, STest({"((a))", "a+b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest239, STest, STest({"a|b|a*?", "a??|a+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest240, STest, STest({"aab", "a*a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest241, STest, STest({"a+|b*?", "a+?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest242, STest, STest({"a?aa", "a*|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest243, STest, STest({"a|bb+?", "abbc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest244, STest, STest({"abc|a", "a+|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest245, STest, STest({"a+?|a??", "abb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest246, STest, STest({"ab|a+?", "a?|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest247, STest, STest({"a+b+", "ab|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest248, STest, STest({"ab|c*", "aab*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest249, STest, STest({"a??bb", "ab|c+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
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
