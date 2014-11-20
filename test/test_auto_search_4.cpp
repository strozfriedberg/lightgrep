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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest750, STest, STest("a{2}?b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest751, STest, STest("a{1,2}?b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest752, STest, STest("a{2,}?b{1,2}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest753, STest, STest("a+b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest754, STest, STest("a*b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest755, STest, STest("a?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest756, STest, STest("a+?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest757, STest, STest("a*?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest758, STest, STest("a??b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest759, STest, STest("a{0,1}b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest760, STest, STest("a{2}b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest761, STest, STest("a{1,2}b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest762, STest, STest("a{2,}b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest763, STest, STest("a{0,1}?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest764, STest, STest("a{2}?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest765, STest, STest("a{1,2}?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest766, STest, STest("a{2,}?b{2,}")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest767, STest, STest("a+b{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest768, STest, STest(R"(a*b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest769, STest, STest(R"(a?b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest770, STest, STest("a+?b{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest771, STest, STest(R"(a*?b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest772, STest, STest(R"(a??b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest773, STest, STest(R"(a{0,1}b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest774, STest, STest("a{2}b{0,1}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest775, STest, STest("a{1,2}b{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest776, STest, STest("a{2,}b{0,1}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest777, STest, STest(R"(a{0,1}?b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest778, STest, STest("a{2}?b{0,1}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest779, STest, STest("a{1,2}?b{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest780, STest, STest("a{2,}?b{0,1}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest781, STest, STest("a+b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest782, STest, STest("a*b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest783, STest, STest("a?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest784, STest, STest("a+?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest785, STest, STest("a*?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest786, STest, STest("a??b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest787, STest, STest("a{0,1}b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest788, STest, STest("a{2}b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest789, STest, STest("a{1,2}b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest790, STest, STest("a{2,}b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest791, STest, STest("a{0,1}?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest792, STest, STest("a{2}?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest793, STest, STest("a{1,2}?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest794, STest, STest("a{2,}?b{2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest795, STest, STest("a+b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest796, STest, STest("a*b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest797, STest, STest("a?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest798, STest, STest("a+?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest799, STest, STest("a*?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest800, STest, STest("a??b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest801, STest, STest("a{0,1}b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest802, STest, STest("a{2}b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest803, STest, STest("a{1,2}b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest804, STest, STest("a{2,}b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest805, STest, STest("a{0,1}?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest806, STest, STest("a{2}?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest807, STest, STest("a{1,2}?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest808, STest, STest("a{2,}?b{1,2}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest809, STest, STest("a+b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest810, STest, STest("a*b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest811, STest, STest("a?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest812, STest, STest("a+?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest813, STest, STest("a*?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest814, STest, STest("a??b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest815, STest, STest("a{0,1}b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest816, STest, STest("a{2}b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest817, STest, STest("a{1,2}b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest818, STest, STest("a{2,}b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest819, STest, STest("a{0,1}?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest820, STest, STest("a{2}?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest821, STest, STest("a{1,2}?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest822, STest, STest("a{2,}?b{2,}?")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest823, STest, STest("a+a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest824, STest, STest("a*a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest825, STest, STest("a?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest826, STest, STest("a+?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest827, STest, STest("a*?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest828, STest, STest("a??a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest829, STest, STest("a{0,1}a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest830, STest, STest("a{2}a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest831, STest, STest("a{1,2}a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest832, STest, STest("a{2,}a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest833, STest, STest("a{0,1}?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest834, STest, STest("a{2}?a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest835, STest, STest("a{1,2}?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest836, STest, STest("a{2,}?a|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest837, STest, STest("a+b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest838, STest, STest("a*b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest839, STest, STest("a?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest840, STest, STest("a+?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest841, STest, STest("a*?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest842, STest, STest("a??b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest843, STest, STest("a{0,1}b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest844, STest, STest("a{2}b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest845, STest, STest("a{1,2}b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest846, STest, STest("a{2,}b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest847, STest, STest("a{0,1}?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest848, STest, STest("a{2}?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest849, STest, STest("a{1,2}?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest850, STest, STest("a{2,}?b|a")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest851, STest, STest("a+a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest852, STest, STest("a*a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest853, STest, STest("a?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest854, STest, STest("a+?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest855, STest, STest("a*?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest856, STest, STest("a??a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest857, STest, STest("a{0,1}a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest858, STest, STest("a{2}a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest859, STest, STest("a{1,2}a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest860, STest, STest("a{2,}a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest861, STest, STest("a{0,1}?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest862, STest, STest("a{2}?a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest863, STest, STest("a{1,2}?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest864, STest, STest("a{2,}?a|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest865, STest, STest("a+b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest866, STest, STest("a*b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest867, STest, STest("a?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest868, STest, STest("a+?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest869, STest, STest("a*?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest870, STest, STest("a??b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest871, STest, STest("a{0,1}b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest872, STest, STest("a{2}b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest873, STest, STest("a{1,2}b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest874, STest, STest("a{2,}b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest875, STest, STest("a{0,1}?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest876, STest, STest("a{2}?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest877, STest, STest("a{1,2}?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest878, STest, STest("a{2,}?b|b")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest879, STest, STest("a+b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest880, STest, STest("a*b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest881, STest, STest("a?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest882, STest, STest("a+?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest883, STest, STest("a*?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest884, STest, STest("a??b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest885, STest, STest("a{0,1}b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest886, STest, STest("a{2}b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest887, STest, STest("a{1,2}b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest888, STest, STest("a{2,}b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest889, STest, STest("a{0,1}?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18u, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest890, STest, STest("a{2}?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest891, STest, STest("a{1,2}?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest892, STest, STest("a{2,}?b|c")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest893, STest, STest("a+|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest894, STest, STest(R"(a*|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest895, STest, STest(R"(a?|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest896, STest, STest("a+?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest897, STest, STest(R"(a*?|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest898, STest, STest(R"(a??|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest899, STest, STest(R"(a{0,1}|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest900, STest, STest("a{2}|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest901, STest, STest("a{1,2}|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest902, STest, STest("a{2,}|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest903, STest, STest(R"(a{0,1}?|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest904, STest, STest("a{2}?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest905, STest, STest("a{1,2}?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest906, STest, STest("a{2,}?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest907, STest, STest("a+|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest908, STest, STest(R"(a*|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest909, STest, STest(R"(a?|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest910, STest, STest("a+?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest911, STest, STest(R"(a*?|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest912, STest, STest(R"(a??|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest913, STest, STest(R"(a{0,1}|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest914, STest, STest("a{2}|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest915, STest, STest("a{1,2}|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest916, STest, STest("a{2,}|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest917, STest, STest(R"(a{0,1}?|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest918, STest, STest("a{2}?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest919, STest, STest("a{1,2}?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest920, STest, STest("a{2,}?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest921, STest, STest("a+|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest922, STest, STest(R"(a*|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest923, STest, STest(R"(a?|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest924, STest, STest("a+?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest925, STest, STest(R"(a*?|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest926, STest, STest(R"(a??|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest927, STest, STest(R"(a{0,1}|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest928, STest, STest("a{2}|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest929, STest, STest("a{1,2}|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest930, STest, STest("a{2,}|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest931, STest, STest(R"(a{0,1}?|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest932, STest, STest("a{2}?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest933, STest, STest("a{1,2}?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest934, STest, STest("a{2,}?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest935, STest, STest("a+|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest936, STest, STest(R"(a*|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest937, STest, STest(R"(a?|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest938, STest, STest("a+?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest939, STest, STest(R"(a*?|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest940, STest, STest(R"(a??|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest941, STest, STest(R"(a{0,1}|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest942, STest, STest("a{2}|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest943, STest, STest("a{1,2}|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest944, STest, STest("a{2,}|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest945, STest, STest(R"(a{0,1}?|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest946, STest, STest("a{2}?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest947, STest, STest("a{1,2}?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest948, STest, STest("a{2,}?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest949, STest, STest("a+|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest950, STest, STest(R"(a*|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest951, STest, STest(R"(a?|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest952, STest, STest("a+?|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest953, STest, STest(R"(a*?|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest954, STest, STest(R"(a??|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest955, STest, STest(R"(a{0,1}|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest956, STest, STest("a{2}|aa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest957, STest, STest("a{1,2}|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest958, STest, STest("a{2,}|aa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest959, STest, STest(R"(a{0,1}?|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest960, STest, STest("a{2}?|aa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest961, STest, STest("a{1,2}?|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest962, STest, STest("a{2,}?|aa")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest963, STest, STest("a+|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest964, STest, STest(R"(a*|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest965, STest, STest(R"(a?|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest966, STest, STest("a+?|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest967, STest, STest(R"(a*?|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest968, STest, STest(R"(a??|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest969, STest, STest(R"(a{0,1}|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest970, STest, STest("a{2}|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest971, STest, STest("a{1,2}|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest972, STest, STest("a{2,}|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest973, STest, STest(R"(a{0,1}?|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest974, STest, STest("a{2}?|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest975, STest, STest("a{1,2}?|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest976, STest, STest("a{2,}?|ba")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest977, STest, STest("a+|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest978, STest, STest(R"(a*|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest979, STest, STest(R"(a?|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest980, STest, STest("a+?|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest981, STest, STest(R"(a*?|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest982, STest, STest(R"(a??|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest983, STest, STest(R"(a{0,1}|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest984, STest, STest("a{2}|ab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest985, STest, STest("a{1,2}|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest986, STest, STest("a{2,}|ab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest987, STest, STest(R"(a{0,1}?|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest988, STest, STest("a{2}?|ab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest989, STest, STest("a{1,2}?|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest990, STest, STest("a{2,}?|ab")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest991, STest, STest("a+|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest992, STest, STest(R"(a*|bb)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest993, STest, STest(R"(a?|bb)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest994, STest, STest("a+?|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternSearchTest995, STest, STest(R"(a*?|bb)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest996, STest, STest(R"(a??|bb)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest997, STest, STest(R"(a{0,1}|bb)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest998, STest, STest("a{2}|bb")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternSearchTest999, STest, STest("a{1,2}|bb")) {
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

