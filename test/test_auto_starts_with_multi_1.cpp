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

#include <algorithm>

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest0, STest, STest({"a+?a*?", "ab|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest1, STest, STest({"a|aa?", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest2, STest, STest({"a|bb+?", "a+|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest3, STest, STest({"aaa+", "a+?|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest4, STest, STest({"a?|a??", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest5, STest, STest({"a+?|b+?", "a|aa|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest6, STest, STest({"a??b+", "a*?a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest7, STest, STest({"a|a|b?", "a+b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest8, STest, STest({"aab+?", "a*aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest9, STest, STest({"ab|b+", "(a)*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest10, STest, STest({"a*?", "a?|a+"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest11, STest, STest({"a+b|c", "ab|b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest12, STest, STest({"a?|b|b", "a+|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest13, STest, STest({"a?|a+", "a|b|c|."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest14, STest, STest({"ab|b|b", "aabc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest15, STest, STest({"abab", "ab(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest16, STest, STest({"ab|c|.", "a|bb*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest17, STest, STest({"a+|b", "aa|bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest18, STest, STest({"a*?|(b)", "a|ab|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest19, STest, STest({"ab|ba", "a|abb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest20, STest, STest({"a*|ba", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest21, STest, STest({"a|b|cc", "a|bc|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest22, STest, STest({"a|a", "a??|bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest23, STest, STest({"aa|ab", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest24, STest, STest({"a*a?", "a|abb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest25, STest, STest({"aa??", "a*|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest26, STest, STest({"a??a??", "a|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest27, STest, STest({"a|b|c|a", "abb|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest28, STest, STest({"a?|a*", "a?|b+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest29, STest, STest({"a+b|a", "a|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest30, STest, STest({"a*?a", "a??b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest31, STest, STest({"a*|b*?", "a|aa|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest32, STest, STest({R"((a??))", "a|a|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest33, STest, STest({"ab|c|c", "a+|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest34, STest, STest({"a*?a", "a|b|c?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest35, STest, STest({"a+?|aa", "a*|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest36, STest, STest({"abba", "abc|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest37, STest, STest({"a+a+?", "a+aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest38, STest, STest({"a*|b|a", "a|ab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest39, STest, STest({"abc+?", "a*?|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest40, STest, STest({"aa??", "abc+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest41, STest, STest({"abca", "ab|b|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest42, STest, STest({"a??|b*", "a*a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest43, STest, STest({"a+|a", "a|b|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest44, STest, STest({"(a*)", "aaa??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest45, STest, STest({"a|aa*", "abb??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest46, STest, STest({"a|bc+?", "a+?ba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest47, STest, STest({"a??|bc", "a+?|a?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest48, STest, STest({"aa|a|a", "a??a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest49, STest, STest({"a|aab", "a|a|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest50, STest, STest({"a?|a*?", "a|a|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest51, STest, STest({"a|b|c.", "a|ab|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest52, STest, STest({"a??|a*", "a|a|bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest53, STest, STest({"a+?b?", "a??a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest54, STest, STest({"ab|c??", "a|bb+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest55, STest, STest({"abb|a", "aab??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest56, STest, STest({"a+|ab", "a*|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest57, STest, STest({"ab|bc", "a|b|ac"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest58, STest, STest({"a+?a*", "aabc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest59, STest, STest({"a|a??", "a|b|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest60, STest, STest({"a|a??", "ab?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest61, STest, STest({"a|b|bc", "a*a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest62, STest, STest({"aa|a??", "a|b|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest63, STest, STest({"ab|c|b", "a|b|c??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest64, STest, STest({"(a|a)", "a+?b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest65, STest, STest({"aaa|b", "a*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest66, STest, STest({"a?a?", "a+aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest67, STest, STest({"a+|b*", "a|bb+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest68, STest, STest({"aa|ba", "aa|a*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest69, STest, STest({"ab??", "a?|b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest70, STest, STest({"a??|b*?", "a??b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest71, STest, STest({"a??|b*?", "a+?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest72, STest, STest({"ab|a??", "a+b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest73, STest, STest({"a|b|a+?", "a|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest74, STest, STest({"aaa|b", "aab|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest75, STest, STest({"ab|(a)", "a+?|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest76, STest, STest({"a|b|b*?", "a|bc+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest77, STest, STest({"a+|bb", "ab|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest78, STest, STest({"(a?)", "a*a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest79, STest, STest({"a+?|b|c", "a*|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest80, STest, STest({"a*|b|c", "a|aba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest81, STest, STest({"ab|c?", "a+?|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest82, STest, STest({"a|bac", "a|b|a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest83, STest, STest({"a+a*", "a??a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest84, STest, STest({"a+|a|b", "a|b|a|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest85, STest, STest({"a+|b|a", "a*?a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest86, STest, STest({"a*a+", "a?a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest87, STest, STest({"a|bc|b", "a*|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest88, STest, STest({"a+?|b?", "(a)|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest89, STest, STest({"a*a??", "a??|a|a"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest90, STest, STest({"a|a|b*", "a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest91, STest, STest({"a??|a??", "a?|b"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest92, STest, STest({"a|abb", "a|ba??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest93, STest, STest({"a+|a*", "a*?|(a)"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest94, STest, STest({"a|b|(b)", "aa|a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest95, STest, STest({"a??b?", "aaa|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest96, STest, STest({"a|a|a?", "a*?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest97, STest, STest({"aa|a|a", "a*|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest98, STest, STest({"a*?|b|c", "a|aa|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest99, STest, STest({"a|b|c*?", "abb|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest100, STest, STest({"abb*", "a??|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest101, STest, STest({"(a?)", "aaa*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest102, STest, STest({"ab|bb", "ab|c."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest103, STest, STest({"a|a??", "a+?|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest104, STest, STest({"a", "aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest105, STest, STest({"aa|a|a", "a+|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest106, STest, STest({"a|ab+", "a|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest107, STest, STest({"a|b|c|.", "a??a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest108, STest, STest({"aa|(a)", "a|b|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest109, STest, STest({"aa|a|b", "a|b|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest110, STest, STest({"a*b", "aa*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest111, STest, STest({"a?aa", "a+a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest112, STest, STest({"aaa*", "a*a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest113, STest, STest({"aa|bb", "ab|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest114, STest, STest({"a+?|ab", "ab+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest115, STest, STest({"a+?", "(a)*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest116, STest, STest({"a|b|ab", "aab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest117, STest, STest({"a??a?", "a*?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest118, STest, STest({"a??|(a)", "a|a|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest119, STest, STest({"a*?|b??", "a|abc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest120, STest, STest({"a*?|b|c", "a+?|a*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest121, STest, STest({"a|b*", "(a)(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest122, STest, STest({"a+?b", "a|aba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest123, STest, STest({"aa(a)", "a|b|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest124, STest, STest({"a|a|ba", "a?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest125, STest, STest({"a|bbc", "ab|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest126, STest, STest({"a|aa*", "abc|."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest127, STest, STest({"aa|ab", "(a)(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest128, STest, STest({"a+?|(b)", "a+?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest129, STest, STest({"a?b|b", "aaba"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest130, STest, STest({"a|ba+", "a+|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest131, STest, STest({"a*|(b)", "a?a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest132, STest, STest({"a+|a*", "a|ba*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest133, STest, STest({"a??|a*?", "abb??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest134, STest, STest({"a+a??", "a+?|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest135, STest, STest({"a*?|b?", "a*?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest136, STest, STest({"aa+", "a+bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest137, STest, STest({"a|a(b)", "a+?|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest138, STest, STest({"a?bc", "a|a|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest139, STest, STest({"a+?b|b", "a+|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest140, STest, STest({"aba+", "aaa+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest141, STest, STest({"a*|b*", "a|aa|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest142, STest, STest({"abb|a", "a?|b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest143, STest, STest({"a+?b+?", "a+|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest144, STest, STest({"a*?a*", "a|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest145, STest, STest({"a|ba", "ab|ca"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest146, STest, STest({"a?|b+?", "ab|bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest147, STest, STest({"aaa*?", "abca"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest148, STest, STest({"a+?|b??", "a*?|a+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest149, STest, STest({"aba*?", "a+?a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest150, STest, STest({"ab|c?", "aaa?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest151, STest, STest({"a|b*", "a|bbc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest152, STest, STest({"a+|b", "a|baa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest153, STest, STest({"a+bb", "a?|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest154, STest, STest({"a|b|bc", "a*?|b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest155, STest, STest({"a|b?", "a+a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest156, STest, STest({"a?|a+?", "a*|b?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest157, STest, STest({"a|b|c+?", "a+|aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest158, STest, STest({"a|b|b*", "aaa+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest159, STest, STest({"a|a(a)", "ab|c."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest160, STest, STest({"a*(b)", "a|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest161, STest, STest({"a+ab", "a?aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest162, STest, STest({"a+|b+?", "(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest163, STest, STest({"a+ba", "a+?ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest164, STest, STest({"ab|c", "a??|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest165, STest, STest({"a|a|b??", "a|b|a*?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest166, STest, STest({"aab*?", "(a|b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest167, STest, STest({"a|ba+?", "aab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest168, STest, STest({"abcc", "a|bc+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest169, STest, STest({"a|a|a+?", "a*?|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest170, STest, STest({"a*?", "a|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest171, STest, STest({"a+bb", "a|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest172, STest, STest({"a+ab", "ab|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest173, STest, STest({"a?b+?", "ab|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest174, STest, STest({"a*a?", "a+|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest175, STest, STest({"a*?(a)", "a|aa|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest176, STest, STest({"a?|aa", "a+b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest177, STest, STest({"aa|a", "aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest178, STest, STest({"a*|ab", "a|b|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest179, STest, STest({"a?|b??", "a*?a?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest180, STest, STest({"a|b|(b)", "a??b*"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest181, STest, STest({"a*?|b+", "a*?|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest182, STest, STest({"ab|ac", "a|a|b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest183, STest, STest({"a|ba?", "a+b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest184, STest, STest({"a|bcc", "a?|ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest185, STest, STest({"ab|(a)", "a*|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest186, STest, STest({"a*?b|a", "aab|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest187, STest, STest({"a|b|b?", "a+?|b|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest188, STest, STest({"ab|aa", "a|b|c|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest189, STest, STest({"a|ba*", "ab|c|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest190, STest, STest({"aaab", "a??b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest191, STest, STest({"a|b|(a)", "a?|b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest192, STest, STest({"a|b|cb", "a|b|c|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest193, STest, STest({"a+|bc", "ab?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest194, STest, STest({"a??|a+?", "a??ab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest195, STest, STest({"a|bc|c", "a+?b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest196, STest, STest({"a+?ba", "a??|a|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest197, STest, STest({"a?|a|b", "a*|a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest198, STest, STest({"aba|b", "a*?a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest199, STest, STest({"a??|a*?", "abcb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest200, STest, STest({"a|baa", "aaa??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest201, STest, STest({"a?|bb", "a|b|b*"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest202, STest, STest({"aa|b|b", "ab(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest203, STest, STest({"a?|a|b", "a?a??"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest204, STest, STest({"ab|b|c", "a+aa"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest205, STest, STest({"a??|bc", "(a+?)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest206, STest, STest({"ab|bb", "a+?|b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest207, STest, STest({"a|aa+?", "ab|a?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest208, STest, STest({"a??|a+", "abb*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest209, STest, STest({"ab??", "a+b?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest210, STest, STest({"a+b+", "a??a+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest211, STest, STest({"(a)(a)", "a+?bc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest212, STest, STest({"a??aa", "a|bca"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest213, STest, STest({"a+?a?", "a|a|b|c"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest214, STest, STest({"a??ba", "a+?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest215, STest, STest({"a|b|aa", "a*bb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest216, STest, STest({"a|aa??", "aaa+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest217, STest, STest({"a?|a?", "a*a|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest218, STest, STest({"ab|a|b", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest219, STest, STest({"aab+?", "a+?a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest220, STest, STest({"a|ab*", "a*b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest221, STest, STest({"a*ab", "ab|ac"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest222, STest, STest({"a|b|b|a", "(a)|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest223, STest, STest({"a?aa", "a|ba+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest224, STest, STest({"ab|c|c", "a|b|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest225, STest, STest({"a?|bb", "a*|b+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest226, STest, STest({"a+|ab", "a?b*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest227, STest, STest({"aab*", "(a*)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest228, STest, STest({"abac", "a|b|a*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest229, STest, STest({"a+|b*?", "a|b|c."})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest230, STest, STest({"aba|c", "a|ab|a"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest231, STest, STest({"a+|ab", "aab+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest232, STest, STest({"aa(b)", "a*?|b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest233, STest, STest({"a|bc.", "a|abc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest234, STest, STest({"a|b(b)", "a|bab"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest235, STest, STest({"aa|bc", "a?b"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest236, STest, STest({"a|b|(b)", "a|a|a??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest237, STest, STest({"ab|c|a", "(a?)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest238, STest, STest({"((a))", "a+b+?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest239, STest, STest({"a|b|a*?", "a??|a+?"})) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest240, STest, STest({"aab", "a*a?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest241, STest, STest({"a+|b*?", "a+?b+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest242, STest, STest({"a?aa", "a*|(b)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest243, STest, STest({"a|bb+?", "abbc"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest244, STest, STest({"abc|a", "a+|a+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest245, STest, STest({"a+?|a??", "abb"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest246, STest, STest({"ab|a+?", "a?|(a)"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest247, STest, STest({"a+b+", "ab|b??"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest248, STest, STest({"ab|c*", "aab*?"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternStartsWithTest249, STest, STest({"a??bb", "ab|c+"})) {
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
}
