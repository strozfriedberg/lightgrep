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

TEST_CASE("autoPatternStartsWithTest750") {
  STest fixture(R"(a{2,}b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest751") {
  STest fixture(R"(a{0,1}?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest752") {
  STest fixture(R"(a{2}?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest753") {
  STest fixture(R"(a{1,2}?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest754") {
  STest fixture(R"(a{2,}?b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest755") {
  STest fixture(R"(a+b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest756") {
  STest fixture(R"(a*b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest757") {
  STest fixture(R"(a?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest758") {
  STest fixture(R"(a+?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest759") {
  STest fixture(R"(a*?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest760") {
  STest fixture(R"(a??b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest761") {
  STest fixture(R"(a{0,1}b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest762") {
  STest fixture(R"(a{2}b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest763") {
  STest fixture(R"(a{1,2}b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest764") {
  STest fixture(R"(a{2,}b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest765") {
  STest fixture(R"(a{0,1}?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest766") {
  STest fixture(R"(a{2}?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest767") {
  STest fixture(R"(a{1,2}?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest768") {
  STest fixture(R"(a{2,}?b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest769") {
  STest fixture(R"(a+b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest770") {
  STest fixture(R"(a*b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest771") {
  STest fixture(R"(a?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest772") {
  STest fixture(R"(a+?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest773") {
  STest fixture(R"(a*?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest774") {
  STest fixture(R"(a??b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest775") {
  STest fixture(R"(a{0,1}b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest776") {
  STest fixture(R"(a{2}b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest777") {
  STest fixture(R"(a{1,2}b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest778") {
  STest fixture(R"(a{2,}b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest779") {
  STest fixture(R"(a{0,1}?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest780") {
  STest fixture(R"(a{2}?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest781") {
  STest fixture(R"(a{1,2}?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest782") {
  STest fixture(R"(a{2,}?b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest783") {
  STest fixture(R"(a+b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest784") {
  STest fixture(R"(a*b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest785") {
  STest fixture(R"(a?b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest786") {
  STest fixture(R"(a+?b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest787") {
  STest fixture(R"(a*?b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest788") {
  STest fixture(R"(a??b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest789") {
  STest fixture(R"(a{0,1}b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest790") {
  STest fixture(R"(a{2}b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest791") {
  STest fixture(R"(a{1,2}b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest792") {
  STest fixture(R"(a{2,}b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest793") {
  STest fixture(R"(a{0,1}?b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest794") {
  STest fixture(R"(a{2}?b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest795") {
  STest fixture(R"(a{1,2}?b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest796") {
  STest fixture(R"(a{2,}?b{0,1}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest797") {
  STest fixture(R"(a+b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest798") {
  STest fixture(R"(a*b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest799") {
  STest fixture(R"(a?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest800") {
  STest fixture(R"(a+?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest801") {
  STest fixture(R"(a*?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest802") {
  STest fixture(R"(a??b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest803") {
  STest fixture(R"(a{0,1}b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest804") {
  STest fixture(R"(a{2}b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest805") {
  STest fixture(R"(a{1,2}b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest806") {
  STest fixture(R"(a{2,}b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest807") {
  STest fixture(R"(a{0,1}?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest808") {
  STest fixture(R"(a{2}?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest809") {
  STest fixture(R"(a{1,2}?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest810") {
  STest fixture(R"(a{2,}?b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest811") {
  STest fixture(R"(a+b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest812") {
  STest fixture(R"(a*b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest813") {
  STest fixture(R"(a?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest814") {
  STest fixture(R"(a+?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest815") {
  STest fixture(R"(a*?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest816") {
  STest fixture(R"(a??b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest817") {
  STest fixture(R"(a{0,1}b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest818") {
  STest fixture(R"(a{2}b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest819") {
  STest fixture(R"(a{1,2}b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest820") {
  STest fixture(R"(a{2,}b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest821") {
  STest fixture(R"(a{0,1}?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest822") {
  STest fixture(R"(a{2}?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest823") {
  STest fixture(R"(a{1,2}?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest824") {
  STest fixture(R"(a{2,}?b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest825") {
  STest fixture(R"(a+b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest826") {
  STest fixture(R"(a*b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest827") {
  STest fixture(R"(a?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest828") {
  STest fixture(R"(a+?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest829") {
  STest fixture(R"(a*?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest830") {
  STest fixture(R"(a??b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest831") {
  STest fixture(R"(a{0,1}b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest832") {
  STest fixture(R"(a{2}b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest833") {
  STest fixture(R"(a{1,2}b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest834") {
  STest fixture(R"(a{2,}b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest835") {
  STest fixture(R"(a{0,1}?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest836") {
  STest fixture(R"(a{2}?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest837") {
  STest fixture(R"(a{1,2}?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest838") {
  STest fixture(R"(a{2,}?b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest839") {
  STest fixture(R"(a+a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest840") {
  STest fixture(R"(a*a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest841") {
  STest fixture(R"(a?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest842") {
  STest fixture(R"(a+?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest843") {
  STest fixture(R"(a*?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest844") {
  STest fixture(R"(a??a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest845") {
  STest fixture(R"(a{0,1}a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest846") {
  STest fixture(R"(a{2}a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest847") {
  STest fixture(R"(a{1,2}a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest848") {
  STest fixture(R"(a{2,}a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest849") {
  STest fixture(R"(a{0,1}?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest850") {
  STest fixture(R"(a{2}?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest851") {
  STest fixture(R"(a{1,2}?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest852") {
  STest fixture(R"(a{2,}?a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest853") {
  STest fixture(R"(a+b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest854") {
  STest fixture(R"(a*b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest855") {
  STest fixture(R"(a?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest856") {
  STest fixture(R"(a+?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest857") {
  STest fixture(R"(a*?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest858") {
  STest fixture(R"(a??b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest859") {
  STest fixture(R"(a{0,1}b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest860") {
  STest fixture(R"(a{2}b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest861") {
  STest fixture(R"(a{1,2}b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest862") {
  STest fixture(R"(a{2,}b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest863") {
  STest fixture(R"(a{0,1}?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest864") {
  STest fixture(R"(a{2}?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest865") {
  STest fixture(R"(a{1,2}?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest866") {
  STest fixture(R"(a{2,}?b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest867") {
  STest fixture(R"(a+a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest868") {
  STest fixture(R"(a*a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest869") {
  STest fixture(R"(a?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest870") {
  STest fixture(R"(a+?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest871") {
  STest fixture(R"(a*?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest872") {
  STest fixture(R"(a??a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest873") {
  STest fixture(R"(a{0,1}a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest874") {
  STest fixture(R"(a{2}a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest875") {
  STest fixture(R"(a{1,2}a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest876") {
  STest fixture(R"(a{2,}a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest877") {
  STest fixture(R"(a{0,1}?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest878") {
  STest fixture(R"(a{2}?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest879") {
  STest fixture(R"(a{1,2}?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest880") {
  STest fixture(R"(a{2,}?a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest881") {
  STest fixture(R"(a+b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest882") {
  STest fixture(R"(a*b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest883") {
  STest fixture(R"(a?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest884") {
  STest fixture(R"(a+?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest885") {
  STest fixture(R"(a*?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest886") {
  STest fixture(R"(a??b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest887") {
  STest fixture(R"(a{0,1}b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest888") {
  STest fixture(R"(a{2}b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest889") {
  STest fixture(R"(a{1,2}b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest890") {
  STest fixture(R"(a{2,}b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest891") {
  STest fixture(R"(a{0,1}?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest892") {
  STest fixture(R"(a{2}?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest893") {
  STest fixture(R"(a{1,2}?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest894") {
  STest fixture(R"(a{2,}?b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest895") {
  STest fixture(R"(a+b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest896") {
  STest fixture(R"(a*b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest897") {
  STest fixture(R"(a?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest898") {
  STest fixture(R"(a+?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest899") {
  STest fixture(R"(a*?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest900") {
  STest fixture(R"(a??b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest901") {
  STest fixture(R"(a{0,1}b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest902") {
  STest fixture(R"(a{2}b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest903") {
  STest fixture(R"(a{1,2}b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest904") {
  STest fixture(R"(a{2,}b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest905") {
  STest fixture(R"(a{0,1}?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest906") {
  STest fixture(R"(a{2}?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest907") {
  STest fixture(R"(a{1,2}?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest908") {
  STest fixture(R"(a{2,}?b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest909") {
  STest fixture(R"(a+|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest910") {
  STest fixture(R"(a*|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest911") {
  STest fixture(R"(a?|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest912") {
  STest fixture(R"(a+?|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest913") {
  STest fixture(R"(a*?|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest914") {
  STest fixture(R"(a??|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest915") {
  STest fixture(R"(a{0,1}|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest916") {
  STest fixture(R"(a{2}|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest917") {
  STest fixture(R"(a{1,2}|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest918") {
  STest fixture(R"(a{2,}|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest919") {
  STest fixture(R"(a{0,1}?|(a))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest920") {
  STest fixture(R"(a{2}?|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest921") {
  STest fixture(R"(a{1,2}?|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest922") {
  STest fixture(R"(a{2,}?|(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest923") {
  STest fixture(R"(a+|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest924") {
  STest fixture(R"(a*|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest925") {
  STest fixture(R"(a?|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest926") {
  STest fixture(R"(a+?|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest927") {
  STest fixture(R"(a*?|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest928") {
  STest fixture(R"(a??|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest929") {
  STest fixture(R"(a{0,1}|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest930") {
  STest fixture(R"(a{2}|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest931") {
  STest fixture(R"(a{1,2}|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest932") {
  STest fixture(R"(a{2,}|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest933") {
  STest fixture(R"(a{0,1}?|(b))");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest934") {
  STest fixture(R"(a{2}?|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest935") {
  STest fixture(R"(a{1,2}?|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest936") {
  STest fixture(R"(a{2,}?|(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest937") {
  STest fixture(R"(a+|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest938") {
  STest fixture(R"(a*|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest939") {
  STest fixture(R"(a?|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest940") {
  STest fixture(R"(a+?|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest941") {
  STest fixture(R"(a*?|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest942") {
  STest fixture(R"(a??|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest943") {
  STest fixture(R"(a{0,1}|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest944") {
  STest fixture(R"(a{2}|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest945") {
  STest fixture(R"(a{1,2}|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest946") {
  STest fixture(R"(a{2,}|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest947") {
  STest fixture(R"(a{0,1}?|a)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest948") {
  STest fixture(R"(a{2}?|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest949") {
  STest fixture(R"(a{1,2}?|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest950") {
  STest fixture(R"(a{2,}?|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest951") {
  STest fixture(R"(a+|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest952") {
  STest fixture(R"(a*|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest953") {
  STest fixture(R"(a?|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest954") {
  STest fixture(R"(a+?|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest955") {
  STest fixture(R"(a*?|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest956") {
  STest fixture(R"(a??|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest957") {
  STest fixture(R"(a{0,1}|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest958") {
  STest fixture(R"(a{2}|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest959") {
  STest fixture(R"(a{1,2}|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest960") {
  STest fixture(R"(a{2,}|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest961") {
  STest fixture(R"(a{0,1}?|b)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest962") {
  STest fixture(R"(a{2}?|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest963") {
  STest fixture(R"(a{1,2}?|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest964") {
  STest fixture(R"(a{2,}?|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest965") {
  STest fixture(R"(a+|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest966") {
  STest fixture(R"(a*|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest967") {
  STest fixture(R"(a?|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest968") {
  STest fixture(R"(a+?|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest969") {
  STest fixture(R"(a*?|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest970") {
  STest fixture(R"(a??|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest971") {
  STest fixture(R"(a{0,1}|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest972") {
  STest fixture(R"(a{2}|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest973") {
  STest fixture(R"(a{1,2}|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest974") {
  STest fixture(R"(a{2,}|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest975") {
  STest fixture(R"(a{0,1}?|aa)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest976") {
  STest fixture(R"(a{2}?|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest977") {
  STest fixture(R"(a{1,2}?|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest978") {
  STest fixture(R"(a{2,}?|aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest979") {
  STest fixture(R"(a+|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest980") {
  STest fixture(R"(a*|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest981") {
  STest fixture(R"(a?|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest982") {
  STest fixture(R"(a+?|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest983") {
  STest fixture(R"(a*?|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest984") {
  STest fixture(R"(a??|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest985") {
  STest fixture(R"(a{0,1}|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest986") {
  STest fixture(R"(a{2}|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest987") {
  STest fixture(R"(a{1,2}|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest988") {
  STest fixture(R"(a{2,}|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest989") {
  STest fixture(R"(a{0,1}?|ba)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest990") {
  STest fixture(R"(a{2}?|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest991") {
  STest fixture(R"(a{1,2}?|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest992") {
  STest fixture(R"(a{2,}?|ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest993") {
  STest fixture(R"(a+|ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest994") {
  STest fixture(R"(a*|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest995") {
  STest fixture(R"(a?|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest996") {
  STest fixture(R"(a+?|ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest997") {
  STest fixture(R"(a*?|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest998") {
  STest fixture(R"(a??|ab)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest999") {
  STest fixture(R"(a{0,1}|ab)");
  REQUIRE(fixture.parsesButNotValid());
}
