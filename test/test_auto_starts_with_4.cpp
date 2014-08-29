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

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest750, STest, STest(R"(a{2,}b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest751, STest, STest(R"(a{0,1}?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest752, STest, STest(R"(a{2}?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest753, STest, STest(R"(a{1,2}?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest754, STest, STest(R"(a{2,}?b{2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest755, STest, STest(R"(a+b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest756, STest, STest(R"(a*b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest757, STest, STest(R"(a?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest758, STest, STest(R"(a+?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest759, STest, STest(R"(a*?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest760, STest, STest(R"(a??b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest761, STest, STest(R"(a{0,1}b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest762, STest, STest(R"(a{2}b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest763, STest, STest(R"(a{1,2}b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest764, STest, STest(R"(a{2,}b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest765, STest, STest(R"(a{0,1}?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest766, STest, STest(R"(a{2}?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest767, STest, STest(R"(a{1,2}?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest768, STest, STest(R"(a{2,}?b{1,2})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest769, STest, STest(R"(a+b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest770, STest, STest(R"(a*b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest771, STest, STest(R"(a?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest772, STest, STest(R"(a+?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest773, STest, STest(R"(a*?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest774, STest, STest(R"(a??b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest775, STest, STest(R"(a{0,1}b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest776, STest, STest(R"(a{2}b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest777, STest, STest(R"(a{1,2}b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest778, STest, STest(R"(a{2,}b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest779, STest, STest(R"(a{0,1}?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest780, STest, STest(R"(a{2}?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest781, STest, STest(R"(a{1,2}?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest782, STest, STest(R"(a{2,}?b{2,})")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest783, STest, STest(R"(a+b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest784, STest, STest(R"(a*b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest785, STest, STest(R"(a?b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest786, STest, STest(R"(a+?b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest787, STest, STest(R"(a*?b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest788, STest, STest(R"(a??b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest789, STest, STest(R"(a{0,1}b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest790, STest, STest(R"(a{2}b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest791, STest, STest(R"(a{1,2}b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest792, STest, STest(R"(a{2,}b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest793, STest, STest(R"(a{0,1}?b{0,1}?)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest794, STest, STest(R"(a{2}?b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest795, STest, STest(R"(a{1,2}?b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest796, STest, STest(R"(a{2,}?b{0,1}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest797, STest, STest(R"(a+b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest798, STest, STest(R"(a*b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest799, STest, STest(R"(a?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest800, STest, STest(R"(a+?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest801, STest, STest(R"(a*?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest802, STest, STest(R"(a??b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest803, STest, STest(R"(a{0,1}b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest804, STest, STest(R"(a{2}b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest805, STest, STest(R"(a{1,2}b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest806, STest, STest(R"(a{2,}b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest807, STest, STest(R"(a{0,1}?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest808, STest, STest(R"(a{2}?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest809, STest, STest(R"(a{1,2}?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest810, STest, STest(R"(a{2,}?b{2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest811, STest, STest(R"(a+b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest812, STest, STest(R"(a*b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest813, STest, STest(R"(a?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest814, STest, STest(R"(a+?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest815, STest, STest(R"(a*?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest816, STest, STest(R"(a??b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest817, STest, STest(R"(a{0,1}b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest818, STest, STest(R"(a{2}b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest819, STest, STest(R"(a{1,2}b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest820, STest, STest(R"(a{2,}b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest821, STest, STest(R"(a{0,1}?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest822, STest, STest(R"(a{2}?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest823, STest, STest(R"(a{1,2}?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest824, STest, STest(R"(a{2,}?b{1,2}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest825, STest, STest(R"(a+b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest826, STest, STest(R"(a*b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest827, STest, STest(R"(a?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest828, STest, STest(R"(a+?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest829, STest, STest(R"(a*?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest830, STest, STest(R"(a??b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest831, STest, STest(R"(a{0,1}b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest832, STest, STest(R"(a{2}b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest833, STest, STest(R"(a{1,2}b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest834, STest, STest(R"(a{2,}b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest835, STest, STest(R"(a{0,1}?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest836, STest, STest(R"(a{2}?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest837, STest, STest(R"(a{1,2}?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest838, STest, STest(R"(a{2,}?b{2,}?)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest839, STest, STest(R"(a+a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest840, STest, STest(R"(a*a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest841, STest, STest(R"(a?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest842, STest, STest(R"(a+?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest843, STest, STest(R"(a*?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest844, STest, STest(R"(a??a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest845, STest, STest(R"(a{0,1}a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest846, STest, STest(R"(a{2}a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest847, STest, STest(R"(a{1,2}a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest848, STest, STest(R"(a{2,}a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest849, STest, STest(R"(a{0,1}?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest850, STest, STest(R"(a{2}?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest851, STest, STest(R"(a{1,2}?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest852, STest, STest(R"(a{2,}?a|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest853, STest, STest(R"(a+b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest854, STest, STest(R"(a*b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest855, STest, STest(R"(a?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest856, STest, STest(R"(a+?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest857, STest, STest(R"(a*?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest858, STest, STest(R"(a??b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest859, STest, STest(R"(a{0,1}b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest860, STest, STest(R"(a{2}b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest861, STest, STest(R"(a{1,2}b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest862, STest, STest(R"(a{2,}b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest863, STest, STest(R"(a{0,1}?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest864, STest, STest(R"(a{2}?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest865, STest, STest(R"(a{1,2}?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest866, STest, STest(R"(a{2,}?b|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest867, STest, STest(R"(a+a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest868, STest, STest(R"(a*a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest869, STest, STest(R"(a?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest870, STest, STest(R"(a+?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest871, STest, STest(R"(a*?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest872, STest, STest(R"(a??a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest873, STest, STest(R"(a{0,1}a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest874, STest, STest(R"(a{2}a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest875, STest, STest(R"(a{1,2}a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest876, STest, STest(R"(a{2,}a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest877, STest, STest(R"(a{0,1}?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest878, STest, STest(R"(a{2}?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest879, STest, STest(R"(a{1,2}?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest880, STest, STest(R"(a{2,}?a|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest881, STest, STest(R"(a+b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest882, STest, STest(R"(a*b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest883, STest, STest(R"(a?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest884, STest, STest(R"(a+?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest885, STest, STest(R"(a*?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest886, STest, STest(R"(a??b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest887, STest, STest(R"(a{0,1}b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest888, STest, STest(R"(a{2}b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest889, STest, STest(R"(a{1,2}b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest890, STest, STest(R"(a{2,}b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest891, STest, STest(R"(a{0,1}?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest892, STest, STest(R"(a{2}?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest893, STest, STest(R"(a{1,2}?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest894, STest, STest(R"(a{2,}?b|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest895, STest, STest(R"(a+b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest896, STest, STest(R"(a*b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest897, STest, STest(R"(a?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest898, STest, STest(R"(a+?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest899, STest, STest(R"(a*?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest900, STest, STest(R"(a??b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest901, STest, STest(R"(a{0,1}b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest902, STest, STest(R"(a{2}b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest903, STest, STest(R"(a{1,2}b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest904, STest, STest(R"(a{2,}b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest905, STest, STest(R"(a{0,1}?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest906, STest, STest(R"(a{2}?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest907, STest, STest(R"(a{1,2}?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest908, STest, STest(R"(a{2,}?b|c)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest909, STest, STest(R"(a+|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest910, STest, STest(R"(a*|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest911, STest, STest(R"(a?|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest912, STest, STest(R"(a+?|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest913, STest, STest(R"(a*?|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest914, STest, STest(R"(a??|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest915, STest, STest(R"(a{0,1}|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest916, STest, STest(R"(a{2}|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest917, STest, STest(R"(a{1,2}|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest918, STest, STest(R"(a{2,}|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest919, STest, STest(R"(a{0,1}?|(a))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest920, STest, STest(R"(a{2}?|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest921, STest, STest(R"(a{1,2}?|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest922, STest, STest(R"(a{2,}?|(a))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest923, STest, STest(R"(a+|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest924, STest, STest(R"(a*|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest925, STest, STest(R"(a?|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest926, STest, STest(R"(a+?|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest927, STest, STest(R"(a*?|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest928, STest, STest(R"(a??|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest929, STest, STest(R"(a{0,1}|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest930, STest, STest(R"(a{2}|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest931, STest, STest(R"(a{1,2}|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest932, STest, STest(R"(a{2,}|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest933, STest, STest(R"(a{0,1}?|(b))")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest934, STest, STest(R"(a{2}?|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest935, STest, STest(R"(a{1,2}?|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest936, STest, STest(R"(a{2,}?|(b))")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest937, STest, STest(R"(a+|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest938, STest, STest(R"(a*|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest939, STest, STest(R"(a?|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest940, STest, STest(R"(a+?|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest941, STest, STest(R"(a*?|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest942, STest, STest(R"(a??|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest943, STest, STest(R"(a{0,1}|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest944, STest, STest(R"(a{2}|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest945, STest, STest(R"(a{1,2}|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest946, STest, STest(R"(a{2,}|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest947, STest, STest(R"(a{0,1}?|a)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest948, STest, STest(R"(a{2}?|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest949, STest, STest(R"(a{1,2}?|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest950, STest, STest(R"(a{2,}?|a)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest951, STest, STest(R"(a+|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest952, STest, STest(R"(a*|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest953, STest, STest(R"(a?|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest954, STest, STest(R"(a+?|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest955, STest, STest(R"(a*?|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest956, STest, STest(R"(a??|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest957, STest, STest(R"(a{0,1}|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest958, STest, STest(R"(a{2}|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest959, STest, STest(R"(a{1,2}|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest960, STest, STest(R"(a{2,}|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest961, STest, STest(R"(a{0,1}?|b)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest962, STest, STest(R"(a{2}?|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest963, STest, STest(R"(a{1,2}?|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest964, STest, STest(R"(a{2,}?|b)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest965, STest, STest(R"(a+|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest966, STest, STest(R"(a*|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest967, STest, STest(R"(a?|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest968, STest, STest(R"(a+?|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest969, STest, STest(R"(a*?|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest970, STest, STest(R"(a??|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest971, STest, STest(R"(a{0,1}|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest972, STest, STest(R"(a{2}|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest973, STest, STest(R"(a{1,2}|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest974, STest, STest(R"(a{2,}|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest975, STest, STest(R"(a{0,1}?|aa)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest976, STest, STest(R"(a{2}?|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest977, STest, STest(R"(a{1,2}?|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest978, STest, STest(R"(a{2,}?|aa)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest979, STest, STest(R"(a+|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest980, STest, STest(R"(a*|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest981, STest, STest(R"(a?|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest982, STest, STest(R"(a+?|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest983, STest, STest(R"(a*?|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest984, STest, STest(R"(a??|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest985, STest, STest(R"(a{0,1}|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest986, STest, STest(R"(a{2}|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest987, STest, STest(R"(a{1,2}|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest988, STest, STest(R"(a{2,}|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest989, STest, STest(R"(a{0,1}?|ba)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest990, STest, STest(R"(a{2}?|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest991, STest, STest(R"(a{1,2}?|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest992, STest, STest(R"(a{2,}?|ba)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest993, STest, STest(R"(a+|ab)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest994, STest, STest(R"(a*|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest995, STest, STest(R"(a?|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest996, STest, STest(R"(a+?|ab)")) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest997, STest, STest(R"(a*?|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest998, STest, STest(R"(a??|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoPatternStartsWithTest999, STest, STest(R"(a{0,1}|ab)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

