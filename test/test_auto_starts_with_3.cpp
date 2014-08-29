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

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest500, STest, STest(R"(a{2}?a+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest501, STest, STest(R"(a{1,2}?a+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest502, STest, STest(R"(a{2,}?a+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest503, STest, STest(R"(a+a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest504, STest, STest(R"(a*a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest505, STest, STest(R"(a?a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest506, STest, STest(R"(a+?a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest507, STest, STest(R"(a*?a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest508, STest, STest(R"(a??a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest509, STest, STest(R"(a{0,1}a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest510, STest, STest(R"(a{2}a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest511, STest, STest(R"(a{1,2}a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest512, STest, STest(R"(a{2,}a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest513, STest, STest(R"(a{0,1}?a*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest514, STest, STest(R"(a{2}?a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest515, STest, STest(R"(a{1,2}?a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest516, STest, STest(R"(a{2,}?a*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest517, STest, STest(R"(a+a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest518, STest, STest(R"(a*a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest519, STest, STest(R"(a?a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest520, STest, STest(R"(a+?a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest521, STest, STest(R"(a*?a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest522, STest, STest(R"(a??a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest523, STest, STest(R"(a{0,1}a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest524, STest, STest(R"(a{2}a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest525, STest, STest(R"(a{1,2}a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest526, STest, STest(R"(a{2,}a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest527, STest, STest(R"(a{0,1}?a??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest528, STest, STest(R"(a{2}?a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest529, STest, STest(R"(a{1,2}?a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest530, STest, STest(R"(a{2,}?a??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest531, STest, STest(R"(a+a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest532, STest, STest(R"(a*a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest533, STest, STest(R"(a?a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest534, STest, STest(R"(a+?a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest535, STest, STest(R"(a*?a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest536, STest, STest(R"(a??a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest537, STest, STest(R"(a{0,1}a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest538, STest, STest(R"(a{2}a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest539, STest, STest(R"(a{1,2}a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest540, STest, STest(R"(a{2,}a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest541, STest, STest(R"(a{0,1}?a{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest542, STest, STest(R"(a{2}?a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest543, STest, STest(R"(a{1,2}?a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest544, STest, STest(R"(a{2,}?a{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest545, STest, STest(R"(a+a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest546, STest, STest(R"(a*a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest547, STest, STest(R"(a?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest548, STest, STest(R"(a+?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest549, STest, STest(R"(a*?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest550, STest, STest(R"(a??a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest551, STest, STest(R"(a{0,1}a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest552, STest, STest(R"(a{2}a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest553, STest, STest(R"(a{1,2}a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest554, STest, STest(R"(a{2,}a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest555, STest, STest(R"(a{0,1}?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest556, STest, STest(R"(a{2}?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest557, STest, STest(R"(a{1,2}?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest558, STest, STest(R"(a{2,}?a{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest559, STest, STest(R"(a+a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest560, STest, STest(R"(a*a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest561, STest, STest(R"(a?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest562, STest, STest(R"(a+?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest563, STest, STest(R"(a*?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest564, STest, STest(R"(a??a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest565, STest, STest(R"(a{0,1}a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest566, STest, STest(R"(a{2}a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest567, STest, STest(R"(a{1,2}a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest568, STest, STest(R"(a{2,}a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest569, STest, STest(R"(a{0,1}?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest570, STest, STest(R"(a{2}?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest571, STest, STest(R"(a{1,2}?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest572, STest, STest(R"(a{2,}?a{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest573, STest, STest(R"(a+a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest574, STest, STest(R"(a*a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest575, STest, STest(R"(a?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest576, STest, STest(R"(a+?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest577, STest, STest(R"(a*?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest578, STest, STest(R"(a??a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest579, STest, STest(R"(a{0,1}a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest580, STest, STest(R"(a{2}a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest581, STest, STest(R"(a{1,2}a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest582, STest, STest(R"(a{2,}a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest583, STest, STest(R"(a{0,1}?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest584, STest, STest(R"(a{2}?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest585, STest, STest(R"(a{1,2}?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest586, STest, STest(R"(a{2,}?a{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest587, STest, STest(R"(a+a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest588, STest, STest(R"(a*a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest589, STest, STest(R"(a?a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest590, STest, STest(R"(a+?a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest591, STest, STest(R"(a*?a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest592, STest, STest(R"(a??a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest593, STest, STest(R"(a{0,1}a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest594, STest, STest(R"(a{2}a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest595, STest, STest(R"(a{1,2}a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest596, STest, STest(R"(a{2,}a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest597, STest, STest(R"(a{0,1}?a{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest598, STest, STest(R"(a{2}?a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest599, STest, STest(R"(a{1,2}?a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest600, STest, STest(R"(a{2,}?a{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest601, STest, STest(R"(a+a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest602, STest, STest(R"(a*a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest603, STest, STest(R"(a?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest604, STest, STest(R"(a+?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest605, STest, STest(R"(a*?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest606, STest, STest(R"(a??a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest607, STest, STest(R"(a{0,1}a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest608, STest, STest(R"(a{2}a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest609, STest, STest(R"(a{1,2}a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest610, STest, STest(R"(a{2,}a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest611, STest, STest(R"(a{0,1}?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest612, STest, STest(R"(a{2}?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest613, STest, STest(R"(a{1,2}?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest614, STest, STest(R"(a{2,}?a{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest615, STest, STest(R"(a+a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest616, STest, STest(R"(a*a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest617, STest, STest(R"(a?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest618, STest, STest(R"(a+?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest619, STest, STest(R"(a*?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest620, STest, STest(R"(a??a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest621, STest, STest(R"(a{0,1}a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest622, STest, STest(R"(a{2}a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest623, STest, STest(R"(a{1,2}a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest624, STest, STest(R"(a{2,}a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest625, STest, STest(R"(a{0,1}?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest626, STest, STest(R"(a{2}?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest627, STest, STest(R"(a{1,2}?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest628, STest, STest(R"(a{2,}?a{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest629, STest, STest(R"(a+a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest630, STest, STest(R"(a*a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest631, STest, STest(R"(a?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest632, STest, STest(R"(a+?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest633, STest, STest(R"(a*?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest634, STest, STest(R"(a??a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest635, STest, STest(R"(a{0,1}a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest636, STest, STest(R"(a{2}a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest637, STest, STest(R"(a{1,2}a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest638, STest, STest(R"(a{2,}a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest639, STest, STest(R"(a{0,1}?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest640, STest, STest(R"(a{2}?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest641, STest, STest(R"(a{1,2}?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest642, STest, STest(R"(a{2,}?a{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest643, STest, STest(R"(a+b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest644, STest, STest(R"(a*b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest645, STest, STest(R"(a?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest646, STest, STest(R"(a+?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest647, STest, STest(R"(a*?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest648, STest, STest(R"(a??b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest649, STest, STest(R"(a{0,1}b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest650, STest, STest(R"(a{2}b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest651, STest, STest(R"(a{1,2}b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest652, STest, STest(R"(a{2,}b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest653, STest, STest(R"(a{0,1}?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest654, STest, STest(R"(a{2}?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest655, STest, STest(R"(a{1,2}?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest656, STest, STest(R"(a{2,}?b+)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest657, STest, STest(R"(a+b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest658, STest, STest(R"(a*b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest659, STest, STest(R"(a?b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest660, STest, STest(R"(a+?b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest661, STest, STest(R"(a*?b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest662, STest, STest(R"(a??b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest663, STest, STest(R"(a{0,1}b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest664, STest, STest(R"(a{2}b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest665, STest, STest(R"(a{1,2}b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest666, STest, STest(R"(a{2,}b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest667, STest, STest(R"(a{0,1}?b*)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest668, STest, STest(R"(a{2}?b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest669, STest, STest(R"(a{1,2}?b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest670, STest, STest(R"(a{2,}?b*)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest671, STest, STest(R"(a+b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest672, STest, STest(R"(a*b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest673, STest, STest(R"(a?b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest674, STest, STest(R"(a+?b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest675, STest, STest(R"(a*?b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest676, STest, STest(R"(a??b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest677, STest, STest(R"(a{0,1}b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest678, STest, STest(R"(a{2}b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest679, STest, STest(R"(a{1,2}b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest680, STest, STest(R"(a{2,}b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest681, STest, STest(R"(a{0,1}?b?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest682, STest, STest(R"(a{2}?b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest683, STest, STest(R"(a{1,2}?b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest684, STest, STest(R"(a{2,}?b?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest685, STest, STest(R"(a+b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest686, STest, STest(R"(a*b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest687, STest, STest(R"(a?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest688, STest, STest(R"(a+?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest689, STest, STest(R"(a*?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest690, STest, STest(R"(a??b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest691, STest, STest(R"(a{0,1}b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest692, STest, STest(R"(a{2}b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest693, STest, STest(R"(a{1,2}b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest694, STest, STest(R"(a{2,}b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest695, STest, STest(R"(a{0,1}?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest696, STest, STest(R"(a{2}?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest697, STest, STest(R"(a{1,2}?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest698, STest, STest(R"(a{2,}?b+?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest699, STest, STest(R"(a+b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest700, STest, STest(R"(a*b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest701, STest, STest(R"(a?b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest702, STest, STest(R"(a+?b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest703, STest, STest(R"(a*?b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest704, STest, STest(R"(a??b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest705, STest, STest(R"(a{0,1}b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest706, STest, STest(R"(a{2}b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest707, STest, STest(R"(a{1,2}b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest708, STest, STest(R"(a{2,}b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest709, STest, STest(R"(a{0,1}?b*?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest710, STest, STest(R"(a{2}?b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest711, STest, STest(R"(a{1,2}?b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest712, STest, STest(R"(a{2,}?b*?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest713, STest, STest(R"(a+b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest714, STest, STest(R"(a*b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest715, STest, STest(R"(a?b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest716, STest, STest(R"(a+?b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest717, STest, STest(R"(a*?b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest718, STest, STest(R"(a??b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest719, STest, STest(R"(a{0,1}b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest720, STest, STest(R"(a{2}b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest721, STest, STest(R"(a{1,2}b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest722, STest, STest(R"(a{2,}b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest723, STest, STest(R"(a{0,1}?b??)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest724, STest, STest(R"(a{2}?b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest725, STest, STest(R"(a{1,2}?b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest726, STest, STest(R"(a{2,}?b??)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest727, STest, STest(R"(a+b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest728, STest, STest(R"(a*b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest729, STest, STest(R"(a?b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest730, STest, STest(R"(a+?b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest731, STest, STest(R"(a*?b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest732, STest, STest(R"(a??b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest733, STest, STest(R"(a{0,1}b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest734, STest, STest(R"(a{2}b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest735, STest, STest(R"(a{1,2}b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest736, STest, STest(R"(a{2,}b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest737, STest, STest(R"(a{0,1}?b{0,1})")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest738, STest, STest(R"(a{2}?b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest739, STest, STest(R"(a{1,2}?b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest740, STest, STest(R"(a{2,}?b{0,1})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest741, STest, STest(R"(a+b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest742, STest, STest(R"(a*b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest743, STest, STest(R"(a?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest744, STest, STest(R"(a+?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest745, STest, STest(R"(a*?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest746, STest, STest(R"(a??b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest747, STest, STest(R"(a{0,1}b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest748, STest, STest(R"(a{2}b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest749, STest, STest(R"(a{1,2}b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

