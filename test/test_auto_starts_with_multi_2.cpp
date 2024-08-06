/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <algorithm>

#include <catch2/catch_test_macros.hpp>

#include "stest.h"

TEST_CASE("autoMultipatternStartsWithTest250") {
  STest fixture({"a+|b", "a|a|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest251") {
  STest fixture({"a*?|(b)", "a+|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest252") {
  STest fixture({"aa|b|a", "aba*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest253") {
  STest fixture({"a??b", "a*?b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest254") {
  STest fixture({"a??a", "a|ba??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest255") {
  STest fixture({"a*|(b)", "aa|b??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest256") {
  STest fixture({"a*?a|b", "a+|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest257") {
  STest fixture({"a?a*?", "a+?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest258") {
  STest fixture({"a|a|ab", "a+a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest259") {
  STest fixture({"a??|ab", "a+|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest260") {
  STest fixture({"a*|b|c", "a|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest261") {
  STest fixture({"a+?|a+?", "a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest262") {
  STest fixture({"a+|b", "a*?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest263") {
  STest fixture({"a+|(b)", "a?a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest264") {
  STest fixture({"a|a|b*", "a?a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest265") {
  STest fixture({"a|b|c|c", "a|aa+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest266") {
  STest fixture({"a?a*?", "a|b|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest267") {
  STest fixture({"a+?|(a)", "a?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest268") {
  STest fixture({"a|bb|c", "ab*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest269") {
  STest fixture({"a+|b|b", "aa|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest270") {
  STest fixture({"a|b|ab", "ab|c??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest271") {
  STest fixture({"a|b|b+?", "a?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest272") {
  STest fixture({"a??|a|a", "a*(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest273") {
  STest fixture({"a|bc|c", "ab|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest274") {
  STest fixture({"a|b(a)", "a*(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest275") {
  STest fixture({"ab|a|b", "a|bc|."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest276") {
  STest fixture({"abc+", "a|b|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest277") {
  STest fixture({"a|aa?", "ab|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest278") {
  STest fixture({"a+?|b+?", "a|a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest279") {
  STest fixture({"a??|b+", "(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest280") {
  STest fixture({"ab|a+", "aa|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest281") {
  STest fixture({"aa*", "abba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest282") {
  STest fixture({"a*b?", "ab|ac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest283") {
  STest fixture({"a*?a+?", "aab?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest284") {
  STest fixture({"a??b*?", "a*|a+"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest285") {
  STest fixture({"a|b|cb", "a|b|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest286") {
  STest fixture({"a+a*?", "aa|bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest287") {
  STest fixture({"a+?|a|a", "a??bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest288") {
  STest fixture({"a*?bb", "(a|a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest289") {
  STest fixture({"a??b??", "a??|b|c"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest290") {
  STest fixture({"a+?|a*", "a+bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest291") {
  STest fixture({"a|ab??", "a+b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest292") {
  STest fixture({"((a))", "abac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest293") {
  STest fixture({"a|b|a+?", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest294") {
  STest fixture({"a|baa", "a?a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest295") {
  STest fixture({"a|aa?", "a*?a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest296") {
  STest fixture({"a+?b?", "a??|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest297") {
  STest fixture({"a??ab", "a|bc+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest298") {
  STest fixture({"a+|b|b", "abb?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest299") {
  STest fixture({"a|b|a??", "a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest300") {
  STest fixture({"a|b|ba", "a+|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest301") {
  STest fixture({"a|aa??", "a+?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest302") {
  STest fixture({"((a))", "a|b|(c)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest303") {
  STest fixture({"ab(c)", "ab|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest304") {
  STest fixture({"a??|a|a", "a?b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest305") {
  STest fixture({"aba|b", "a|b|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest306") {
  STest fixture({"a+?a", "a?|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest307") {
  STest fixture({"a|b??", "a|b|c|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest308") {
  STest fixture({"a+a+?", "a+?|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest309") {
  STest fixture({"ab|cb", "a|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest310") {
  STest fixture({"a*|a??", "a|b|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest311") {
  STest fixture({"a*b*", "a+b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest312") {
  STest fixture({"a??|b", "a|b|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest313") {
  STest fixture({"a|b|c|.", "a+|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest314") {
  STest fixture({"a|bb|c", "ab+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest315") {
  STest fixture({"a?|a+?", "a??|b|c"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest316") {
  STest fixture({"a+|aa", "a|bc*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest317") {
  STest fixture({"a??|a+?", "ab|c*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest318") {
  STest fixture({"a??b??", "a?|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest319") {
  STest fixture({"aa(a)", "a|ab+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest320") {
  STest fixture({"a|bb|b", "a+?|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest321") {
  STest fixture({"a*a+?", "a?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest322") {
  STest fixture({"a+?|ba", "a+?b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest323") {
  STest fixture({"a|a|a|b", "a??|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest324") {
  STest fixture({"ab|b", "a+|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest325") {
  STest fixture({"a?a", "a*?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest326") {
  STest fixture({"a+?|b|c", "a*a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest327") {
  STest fixture({"aaa?", "(a)+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest328") {
  STest fixture({"a??a+", "a?b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest329") {
  STest fixture({"a*?a*?", "aba|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest330") {
  STest fixture({"a*?|a+?", "a+|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest331") {
  STest fixture({"a+?|a*", "abbc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest332") {
  STest fixture({"a*?bc", "a|baa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest333") {
  STest fixture({"ab|a*", "a?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest334") {
  STest fixture({"a*?b|a", "a??|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest335") {
  STest fixture({"ab|a?", "a+|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest336") {
  STest fixture({"a*?|b??", "a+?|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest337") {
  STest fixture({"a|b(b)", "aa|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest338") {
  STest fixture({"a+?|(a)", "a|a|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest339") {
  STest fixture({"a|a|ab", "a+?|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest340") {
  STest fixture({"ab|b|c", "a+?bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest341") {
  STest fixture({"a??|a+", "a|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest342") {
  STest fixture({"aa|a*?", "a+b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest343") {
  STest fixture({"a+|a*?", "a|a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest344") {
  STest fixture({"a+?a?", "a+a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest345") {
  STest fixture({"aa|b*", "a+?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest346") {
  STest fixture({"a|bb+?", "a|bb|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest347") {
  STest fixture({"abb", "a+|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest348") {
  STest fixture({"aab", "a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest349") {
  STest fixture({"a?b*?", "a?|a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest350") {
  STest fixture({"(a)??", "a|aa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest351") {
  STest fixture({"abc?", "a+?a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest352") {
  STest fixture({"aa|a", "a|aa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest353") {
  STest fixture({"a|b|a|c", "a*b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest354") {
  STest fixture({"abb?", "aab??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest355") {
  STest fixture({"a?|a|a", "a??|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest356") {
  STest fixture({"a+|a*?", "a|b|ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest357") {
  STest fixture({"a??|b+?", "ab|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest358") {
  STest fixture({"a+|a+?", "a*?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest359") {
  STest fixture({"a|abb", "a|b|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest360") {
  STest fixture({"a*|a*", "(aa)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest361") {
  STest fixture({"a|b|a|c", "a|bba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest362") {
  STest fixture({"aaa|a", "a*|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest363") {
  STest fixture({"a*bb", "aa|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest364") {
  STest fixture({"(a)?", "aba|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest365") {
  STest fixture({"a+|(b)", "(a)*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest366") {
  STest fixture({"a*a?", "a+b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest367") {
  STest fixture({"a??a*", "a*a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest368") {
  STest fixture({"a?a?", "a+?|a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest369") {
  STest fixture({"a?a|a", "ab|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest370") {
  STest fixture({"aa|b*?", "a+b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest371") {
  STest fixture({"a*|b|c", "ab|c|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest372") {
  STest fixture({"a??a|a", "a?|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest373") {
  STest fixture({"a|bb", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest374") {
  STest fixture({"abba", "a?bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest375") {
  STest fixture({"a*b", "a+(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest376") {
  STest fixture({"a|a|b*?", "a?|b*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest377") {
  STest fixture({"abc|c", "abb+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest378") {
  STest fixture({"a|a|b+?", "a|a|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest379") {
  STest fixture({"a?|b?", "a??bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest380") {
  STest fixture({"a?ab", "a|a|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest381") {
  STest fixture({"ab|c+", "a?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest382") {
  STest fixture({"a*?|bb", "a|ba?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest383") {
  STest fixture({"a??|b|c", "abc."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest384") {
  STest fixture({"a?|b|a", "a*?a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest385") {
  STest fixture({"a?|a+?", "ab|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest386") {
  STest fixture({"a|a|(a)", "a?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest387") {
  STest fixture({"a+a?", "a*?|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest388") {
  STest fixture({"a*?|a|b", "a|b|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest389") {
  STest fixture({"a?|bc", "a+|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest390") {
  STest fixture({"a*?|b|c", "aa|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest391") {
  STest fixture({"a+?|aa", "abb*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest392") {
  STest fixture({"a?|(b)", "a|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest393") {
  STest fixture({"ab|c|.", "a*(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest394") {
  STest fixture({"a*?|ab", "aaa*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest395") {
  STest fixture({"a?b|b", "a*|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest396") {
  STest fixture({"a+?a", "a*|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest397") {
  STest fixture({"aba*", "a+?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest398") {
  STest fixture({"aaab", "a*|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest399") {
  STest fixture({"a?|a|a", "a?|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest400") {
  STest fixture({"aa|a?", "a*?(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest401") {
  STest fixture({"a*?b*", "a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest402") {
  STest fixture({"a|b|c.", "a|bc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest403") {
  STest fixture({"a|bca", "a|bb??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest404") {
  STest fixture({"a+a|b", "a|aa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest405") {
  STest fixture({"aa|b|b", "ab|c??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest406") {
  STest fixture({"(a)(b)", "aa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest407") {
  STest fixture({"a?|b*?", "ab|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest408") {
  STest fixture({"a+|a??", "a?b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest409") {
  STest fixture({"a?|b*?", "a|b|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest410") {
  STest fixture({"ab|a", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest411") {
  STest fixture({"a+?a", "a+?|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest412") {
  STest fixture({"a+bc", "a*a?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest413") {
  STest fixture({"a+?b*", R"(a??(b))"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest414") {
  STest fixture({"a+a|b", "a|bb*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest415") {
  STest fixture({"a|a|a??", R"(a??(b))"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest416") {
  STest fixture({"a+|a", "a*(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest417") {
  STest fixture({"a|ab*?", "a+?|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest418") {
  STest fixture({"a|b|(c)", "a|bc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest419") {
  STest fixture({"a?a*", "a+?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest420") {
  STest fixture({"a|b(b)", "a|a|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest421") {
  STest fixture({"a+b??", "a*?a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest422") {
  STest fixture({"a|a|bc", "a?b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest423") {
  STest fixture({"aab|a", "aaa+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest424") {
  STest fixture({"a??|a*?", "a?|b??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest425") {
  STest fixture({"ab|b+", "a+?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest426") {
  STest fixture({"abba", "a*|a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest427") {
  STest fixture({"ab|c|b", "a?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest428") {
  STest fixture({"a*?b*", "a*?|a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest429") {
  STest fixture({"a+?a?", "a|b|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest430") {
  STest fixture({"a??|a|a", "a|bb|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest431") {
  STest fixture({"a*?aa", "a|b(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest432") {
  STest fixture({"a+b*?", "a|b|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest433") {
  STest fixture({"a+?a??", "aa(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest434") {
  STest fixture({"a?b+?", "a+a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest435") {
  STest fixture({"a+?bb", "a|ba+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest436") {
  STest fixture({"ab|a+", "a|a|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest437") {
  STest fixture({"a+?|a+", "a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest438") {
  STest fixture({"a|b|c|a", "a|a|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest439") {
  STest fixture({"a??|b|b", "((a))"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest440") {
  STest fixture({"a*a+", "a??|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest441") {
  STest fixture({"a*b|b", "a??a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest442") {
  STest fixture({"a|bc|.", "a|b|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest443") {
  STest fixture({"a+?ab", "a+?a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest444") {
  STest fixture({"a+?|bb", "ab|c|."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest445") {
  STest fixture({"a|a|ba", "a|b(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest446") {
  STest fixture({"ab??", "ab|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest447") {
  STest fixture({"aaa", "a??|a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest448") {
  STest fixture({"a|b|c", "aba|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest449") {
  STest fixture({"a|a|a|b", "ab|a|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest450") {
  STest fixture({"a|bc+?", "abc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest451") {
  STest fixture({"a|ba?", "a?|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest452") {
  STest fixture({"ab|b+", "a?b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest453") {
  STest fixture({"a+?b+?", "a*b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest454") {
  STest fixture({"a|bb+", "aa|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest455") {
  STest fixture({"a+ab", "a+|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest456") {
  STest fixture({"a+|bb", "abb|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest457") {
  STest fixture({"ab|a+", "aaa*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest458") {
  STest fixture({"a+", "a*?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest459") {
  STest fixture({"abbb", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest460") {
  STest fixture({"ab|aa", "aba|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest461") {
  STest fixture({"a*?b|b", "a*?|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest462") {
  STest fixture({"abc?", "a+?b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest463") {
  STest fixture({"(a)*?", "a??|b|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest464") {
  STest fixture({"a+?a+?", "a|ba+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest465") {
  STest fixture({"ab|c+?", "(a)??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest466") {
  STest fixture({"a*", "a+|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest467") {
  STest fixture({"ab(c)", "(a*)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest468") {
  STest fixture({"a|a|bb", "a+bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest469") {
  STest fixture({"a*|bb", "a??|(a)"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest470") {
  STest fixture({"a|a|(a)", "aa|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest471") {
  STest fixture({"a|a(b)", "a+?|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest472") {
  STest fixture({"a??", "a|bb|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest473") {
  STest fixture({"abb*", "a??b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest474") {
  STest fixture({"a|b|b|a", "a*?|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest475") {
  STest fixture({"a|b|ab", "a|bc+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest476") {
  STest fixture({"a*(b)", "aa|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest477") {
  STest fixture({"ab|b", "a+b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest478") {
  STest fixture({"a*?|(a)", "a??|b|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest479") {
  STest fixture({"a*b*", "a?|a"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest480") {
  STest fixture({"aa|a??", "a??|ba"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest481") {
  STest fixture({"a+?|(a)", "a?a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest482") {
  STest fixture({"a??|b*?", "a+|ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest483") {
  STest fixture({"a*a??", "a|a(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest484") {
  STest fixture({"a*?b+", "a|b|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest485") {
  STest fixture({"a+a+?", "a*|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest486") {
  STest fixture({"a|bb+?", "aba|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest487") {
  STest fixture({"a*?a??", "a*?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest488") {
  STest fixture({"ab|c*", "a*|a|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest489") {
  STest fixture({"a|bc|a", "ab|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest490") {
  STest fixture({"(a)*?", "aab*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest491") {
  STest fixture({"a?a", "a|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest492") {
  STest fixture({"a+|b+", "a+a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest493") {
  STest fixture({"a|b|c|.", "a|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest494") {
  STest fixture({"a*?|b??", "a+?|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest495") {
  STest fixture({"a*?|ab", "a*?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 5, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest496") {
  STest fixture({"a|bc*?", "a*?b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest497") {
  STest fixture({"a?|a", "a?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest498") {
  STest fixture({"a?a", "a+?b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest499") {
  STest fixture({"ab|a|b", "a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}
