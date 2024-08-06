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

#include <catch2/catch_test_macros.hpp>

#include "stest.h"

TEST_CASE("autoPatternStartsWithTest500") {
  STest fixture(R"(a{2}?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest501") {
  STest fixture(R"(a{1,2}?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest502") {
  STest fixture(R"(a{2,}?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest503") {
  STest fixture(R"(a+a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest504") {
  STest fixture(R"(a*a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest505") {
  STest fixture(R"(a?a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest506") {
  STest fixture(R"(a+?a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest507") {
  STest fixture(R"(a*?a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest508") {
  STest fixture(R"(a??a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest509") {
  STest fixture(R"(a{0,1}a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest510") {
  STest fixture(R"(a{2}a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest511") {
  STest fixture(R"(a{1,2}a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest512") {
  STest fixture(R"(a{2,}a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest513") {
  STest fixture(R"(a{0,1}?a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest514") {
  STest fixture(R"(a{2}?a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest515") {
  STest fixture(R"(a{1,2}?a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest516") {
  STest fixture(R"(a{2,}?a*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest517") {
  STest fixture(R"(a+a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest518") {
  STest fixture(R"(a*a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest519") {
  STest fixture(R"(a?a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest520") {
  STest fixture(R"(a+?a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest521") {
  STest fixture(R"(a*?a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest522") {
  STest fixture(R"(a??a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest523") {
  STest fixture(R"(a{0,1}a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest524") {
  STest fixture(R"(a{2}a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest525") {
  STest fixture(R"(a{1,2}a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest526") {
  STest fixture(R"(a{2,}a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest527") {
  STest fixture(R"(a{0,1}?a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest528") {
  STest fixture(R"(a{2}?a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest529") {
  STest fixture(R"(a{1,2}?a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest530") {
  STest fixture(R"(a{2,}?a??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest531") {
  STest fixture(R"(a+a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest532") {
  STest fixture(R"(a*a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest533") {
  STest fixture(R"(a?a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest534") {
  STest fixture(R"(a+?a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest535") {
  STest fixture(R"(a*?a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest536") {
  STest fixture(R"(a??a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest537") {
  STest fixture(R"(a{0,1}a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest538") {
  STest fixture(R"(a{2}a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest539") {
  STest fixture(R"(a{1,2}a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest540") {
  STest fixture(R"(a{2,}a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest541") {
  STest fixture(R"(a{0,1}?a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest542") {
  STest fixture(R"(a{2}?a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest543") {
  STest fixture(R"(a{1,2}?a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest544") {
  STest fixture(R"(a{2,}?a{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest545") {
  STest fixture(R"(a+a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest546") {
  STest fixture(R"(a*a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest547") {
  STest fixture(R"(a?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest548") {
  STest fixture(R"(a+?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest549") {
  STest fixture(R"(a*?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest550") {
  STest fixture(R"(a??a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest551") {
  STest fixture(R"(a{0,1}a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest552") {
  STest fixture(R"(a{2}a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest553") {
  STest fixture(R"(a{1,2}a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest554") {
  STest fixture(R"(a{2,}a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest555") {
  STest fixture(R"(a{0,1}?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest556") {
  STest fixture(R"(a{2}?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest557") {
  STest fixture(R"(a{1,2}?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest558") {
  STest fixture(R"(a{2,}?a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest559") {
  STest fixture(R"(a+a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest560") {
  STest fixture(R"(a*a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest561") {
  STest fixture(R"(a?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest562") {
  STest fixture(R"(a+?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest563") {
  STest fixture(R"(a*?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest564") {
  STest fixture(R"(a??a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest565") {
  STest fixture(R"(a{0,1}a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest566") {
  STest fixture(R"(a{2}a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest567") {
  STest fixture(R"(a{1,2}a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest568") {
  STest fixture(R"(a{2,}a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest569") {
  STest fixture(R"(a{0,1}?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest570") {
  STest fixture(R"(a{2}?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest571") {
  STest fixture(R"(a{1,2}?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest572") {
  STest fixture(R"(a{2,}?a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest573") {
  STest fixture(R"(a+a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest574") {
  STest fixture(R"(a*a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest575") {
  STest fixture(R"(a?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest576") {
  STest fixture(R"(a+?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest577") {
  STest fixture(R"(a*?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest578") {
  STest fixture(R"(a??a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest579") {
  STest fixture(R"(a{0,1}a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest580") {
  STest fixture(R"(a{2}a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest581") {
  STest fixture(R"(a{1,2}a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest582") {
  STest fixture(R"(a{2,}a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest583") {
  STest fixture(R"(a{0,1}?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest584") {
  STest fixture(R"(a{2}?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest585") {
  STest fixture(R"(a{1,2}?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest586") {
  STest fixture(R"(a{2,}?a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest587") {
  STest fixture(R"(a+a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest588") {
  STest fixture(R"(a*a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest589") {
  STest fixture(R"(a?a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest590") {
  STest fixture(R"(a+?a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest591") {
  STest fixture(R"(a*?a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest592") {
  STest fixture(R"(a??a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest593") {
  STest fixture(R"(a{0,1}a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest594") {
  STest fixture(R"(a{2}a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest595") {
  STest fixture(R"(a{1,2}a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest596") {
  STest fixture(R"(a{2,}a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest597") {
  STest fixture(R"(a{0,1}?a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest598") {
  STest fixture(R"(a{2}?a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest599") {
  STest fixture(R"(a{1,2}?a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest600") {
  STest fixture(R"(a{2,}?a{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest601") {
  STest fixture(R"(a+a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest602") {
  STest fixture(R"(a*a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest603") {
  STest fixture(R"(a?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest604") {
  STest fixture(R"(a+?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest605") {
  STest fixture(R"(a*?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest606") {
  STest fixture(R"(a??a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest607") {
  STest fixture(R"(a{0,1}a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest608") {
  STest fixture(R"(a{2}a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest609") {
  STest fixture(R"(a{1,2}a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest610") {
  STest fixture(R"(a{2,}a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest611") {
  STest fixture(R"(a{0,1}?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest612") {
  STest fixture(R"(a{2}?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest613") {
  STest fixture(R"(a{1,2}?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest614") {
  STest fixture(R"(a{2,}?a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest615") {
  STest fixture(R"(a+a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest616") {
  STest fixture(R"(a*a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest617") {
  STest fixture(R"(a?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest618") {
  STest fixture(R"(a+?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest619") {
  STest fixture(R"(a*?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest620") {
  STest fixture(R"(a??a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest621") {
  STest fixture(R"(a{0,1}a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest622") {
  STest fixture(R"(a{2}a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest623") {
  STest fixture(R"(a{1,2}a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest624") {
  STest fixture(R"(a{2,}a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest625") {
  STest fixture(R"(a{0,1}?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest626") {
  STest fixture(R"(a{2}?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest627") {
  STest fixture(R"(a{1,2}?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest628") {
  STest fixture(R"(a{2,}?a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest629") {
  STest fixture(R"(a+a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest630") {
  STest fixture(R"(a*a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest631") {
  STest fixture(R"(a?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest632") {
  STest fixture(R"(a+?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest633") {
  STest fixture(R"(a*?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest634") {
  STest fixture(R"(a??a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest635") {
  STest fixture(R"(a{0,1}a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest636") {
  STest fixture(R"(a{2}a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest637") {
  STest fixture(R"(a{1,2}a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest638") {
  STest fixture(R"(a{2,}a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest639") {
  STest fixture(R"(a{0,1}?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest640") {
  STest fixture(R"(a{2}?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest641") {
  STest fixture(R"(a{1,2}?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest642") {
  STest fixture(R"(a{2,}?a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest643") {
  STest fixture(R"(a+b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest644") {
  STest fixture(R"(a*b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest645") {
  STest fixture(R"(a?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest646") {
  STest fixture(R"(a+?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest647") {
  STest fixture(R"(a*?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest648") {
  STest fixture(R"(a??b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest649") {
  STest fixture(R"(a{0,1}b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest650") {
  STest fixture(R"(a{2}b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest651") {
  STest fixture(R"(a{1,2}b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest652") {
  STest fixture(R"(a{2,}b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest653") {
  STest fixture(R"(a{0,1}?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest654") {
  STest fixture(R"(a{2}?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest655") {
  STest fixture(R"(a{1,2}?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest656") {
  STest fixture(R"(a{2,}?b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest657") {
  STest fixture(R"(a+b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest658") {
  STest fixture(R"(a*b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest659") {
  STest fixture(R"(a?b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest660") {
  STest fixture(R"(a+?b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest661") {
  STest fixture(R"(a*?b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest662") {
  STest fixture(R"(a??b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest663") {
  STest fixture(R"(a{0,1}b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest664") {
  STest fixture(R"(a{2}b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest665") {
  STest fixture(R"(a{1,2}b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest666") {
  STest fixture(R"(a{2,}b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest667") {
  STest fixture(R"(a{0,1}?b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest668") {
  STest fixture(R"(a{2}?b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest669") {
  STest fixture(R"(a{1,2}?b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest670") {
  STest fixture(R"(a{2,}?b*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest671") {
  STest fixture(R"(a+b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest672") {
  STest fixture(R"(a*b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest673") {
  STest fixture(R"(a?b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest674") {
  STest fixture(R"(a+?b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest675") {
  STest fixture(R"(a*?b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest676") {
  STest fixture(R"(a??b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest677") {
  STest fixture(R"(a{0,1}b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest678") {
  STest fixture(R"(a{2}b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest679") {
  STest fixture(R"(a{1,2}b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest680") {
  STest fixture(R"(a{2,}b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest681") {
  STest fixture(R"(a{0,1}?b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest682") {
  STest fixture(R"(a{2}?b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest683") {
  STest fixture(R"(a{1,2}?b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest684") {
  STest fixture(R"(a{2,}?b?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest685") {
  STest fixture(R"(a+b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest686") {
  STest fixture(R"(a*b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest687") {
  STest fixture(R"(a?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest688") {
  STest fixture(R"(a+?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest689") {
  STest fixture(R"(a*?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest690") {
  STest fixture(R"(a??b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest691") {
  STest fixture(R"(a{0,1}b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest692") {
  STest fixture(R"(a{2}b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest693") {
  STest fixture(R"(a{1,2}b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest694") {
  STest fixture(R"(a{2,}b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest695") {
  STest fixture(R"(a{0,1}?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest696") {
  STest fixture(R"(a{2}?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest697") {
  STest fixture(R"(a{1,2}?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest698") {
  STest fixture(R"(a{2,}?b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest699") {
  STest fixture(R"(a+b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest700") {
  STest fixture(R"(a*b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest701") {
  STest fixture(R"(a?b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest702") {
  STest fixture(R"(a+?b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest703") {
  STest fixture(R"(a*?b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest704") {
  STest fixture(R"(a??b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest705") {
  STest fixture(R"(a{0,1}b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest706") {
  STest fixture(R"(a{2}b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest707") {
  STest fixture(R"(a{1,2}b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest708") {
  STest fixture(R"(a{2,}b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest709") {
  STest fixture(R"(a{0,1}?b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest710") {
  STest fixture(R"(a{2}?b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest711") {
  STest fixture(R"(a{1,2}?b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest712") {
  STest fixture(R"(a{2,}?b*?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest713") {
  STest fixture(R"(a+b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest714") {
  STest fixture(R"(a*b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest715") {
  STest fixture(R"(a?b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest716") {
  STest fixture(R"(a+?b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest717") {
  STest fixture(R"(a*?b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest718") {
  STest fixture(R"(a??b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest719") {
  STest fixture(R"(a{0,1}b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest720") {
  STest fixture(R"(a{2}b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest721") {
  STest fixture(R"(a{1,2}b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest722") {
  STest fixture(R"(a{2,}b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest723") {
  STest fixture(R"(a{0,1}?b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest724") {
  STest fixture(R"(a{2}?b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest725") {
  STest fixture(R"(a{1,2}?b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest726") {
  STest fixture(R"(a{2,}?b??)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest727") {
  STest fixture(R"(a+b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest728") {
  STest fixture(R"(a*b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest729") {
  STest fixture(R"(a?b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest730") {
  STest fixture(R"(a+?b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest731") {
  STest fixture(R"(a*?b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest732") {
  STest fixture(R"(a??b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest733") {
  STest fixture(R"(a{0,1}b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest734") {
  STest fixture(R"(a{2}b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest735") {
  STest fixture(R"(a{1,2}b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest736") {
  STest fixture(R"(a{2,}b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest737") {
  STest fixture(R"(a{0,1}?b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest738") {
  STest fixture(R"(a{2}?b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest739") {
  STest fixture(R"(a{1,2}?b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest740") {
  STest fixture(R"(a{2,}?b{0,1})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest741") {
  STest fixture(R"(a+b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest742") {
  STest fixture(R"(a*b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest743") {
  STest fixture(R"(a?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest744") {
  STest fixture(R"(a+?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest745") {
  STest fixture(R"(a*?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest746") {
  STest fixture(R"(a??b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest747") {
  STest fixture(R"(a{0,1}b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest748") {
  STest fixture(R"(a{2}b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest749") {
  STest fixture(R"(a{1,2}b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}
