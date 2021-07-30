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

#include "catch.hpp"

#include "stest.h"

TEST_CASE("autoMultipatternStartsWithTest0") {
  STest fixture({"a+?a*?", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest1") {
  STest fixture({"a|aa?", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest2") {
  STest fixture({"a|bb+?", "a+|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest3") {
  STest fixture({"aaa+", "a+?|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest4") {
  STest fixture({"a?|a??", "a|ba+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest5") {
  STest fixture({"a+?|b+?", "a|aa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest6") {
  STest fixture({"a??b+", "a*?a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest7") {
  STest fixture({"a|a|b?", "a+b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest8") {
  STest fixture({"aab+?", "a*aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest9") {
  STest fixture({"ab|b+", "(a)*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest10") {
  STest fixture({"a*?", "a?|a+"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest11") {
  STest fixture({"a+b|c", "ab|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest12") {
  STest fixture({"a?|b|b", "a+|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest13") {
  STest fixture({"a?|a+", "a|b|c|."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest14") {
  STest fixture({"ab|b|b", "aabc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest15") {
  STest fixture({"abab", "ab(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest16") {
  STest fixture({"ab|c|.", "a|bb*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest17") {
  STest fixture({"a+|b", "aa|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest18") {
  STest fixture({"a*?|(b)", "a|ab|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest19") {
  STest fixture({"ab|ba", "a|abb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest20") {
  STest fixture({"a*|ba", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest21") {
  STest fixture({"a|b|cc", "a|bc|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest22") {
  STest fixture({"a|a", "a??|bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest23") {
  STest fixture({"aa|ab", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest24") {
  STest fixture({"a*a?", "a|abb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest25") {
  STest fixture({"aa??", "a*|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest26") {
  STest fixture({"a??a??", "a|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest27") {
  STest fixture({"a|b|c|a", "abb|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest28") {
  STest fixture({"a?|a*", "a?|b+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest29") {
  STest fixture({"a+b|a", "a|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest30") {
  STest fixture({"a*?a", "a??b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest31") {
  STest fixture({"a*|b*?", "a|aa|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest32") {
  STest fixture({R"((a??))", "a|a|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest33") {
  STest fixture({"ab|c|c", "a+|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest34") {
  STest fixture({"a*?a", "a|b|c?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest35") {
  STest fixture({"a+?|aa", "a*|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest36") {
  STest fixture({"abba", "abc|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest37") {
  STest fixture({"a+a+?", "a+aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest38") {
  STest fixture({"a*|b|a", "a|ab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest39") {
  STest fixture({"abc+?", "a*?|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest40") {
  STest fixture({"aa??", "abc+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest41") {
  STest fixture({"abca", "ab|b|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest42") {
  STest fixture({"a??|b*", "a*a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest43") {
  STest fixture({"a+|a", "a|b|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest44") {
  STest fixture({"(a*)", "aaa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest45") {
  STest fixture({"a|aa*", "abb??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest46") {
  STest fixture({"a|bc+?", "a+?ba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 5, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest47") {
  STest fixture({"a??|bc", "a+?|a?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest48") {
  STest fixture({"aa|a|a", "a??a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest49") {
  STest fixture({"a|aab", "a|a|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest50") {
  STest fixture({"a?|a*?", "a|a|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest51") {
  STest fixture({"a|b|c.", "a|ab|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest52") {
  STest fixture({"a??|a*", "a|a|bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest53") {
  STest fixture({"a+?b?", "a??a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest54") {
  STest fixture({"ab|c??", "a|bb+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest55") {
  STest fixture({"abb|a", "aab??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest56") {
  STest fixture({"a+|ab", "a*|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest57") {
  STest fixture({"ab|bc", "a|b|ac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest58") {
  STest fixture({"a+?a*", "aabc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest59") {
  STest fixture({"a|a??", "a|b|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest60") {
  STest fixture({"a|a??", "ab?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest61") {
  STest fixture({"a|b|bc", "a*a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest62") {
  STest fixture({"aa|a??", "a|b|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest63") {
  STest fixture({"ab|c|b", "a|b|c??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest64") {
  STest fixture({"(a|a)", "a+?b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest65") {
  STest fixture({"aaa|b", "a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest66") {
  STest fixture({"a?a?", "a+aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest67") {
  STest fixture({"a+|b*", "a|bb+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest68") {
  STest fixture({"aa|ba", "aa|a*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest69") {
  STest fixture({"ab??", "a?|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest70") {
  STest fixture({"a??|b*?", "a??b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest71") {
  STest fixture({"a??|b*?", "a+?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest72") {
  STest fixture({"ab|a??", "a+b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest73") {
  STest fixture({"a|b|a+?", "a|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest74") {
  STest fixture({"aaa|b", "aab|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest75") {
  STest fixture({"ab|(a)", "a+?|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest76") {
  STest fixture({"a|b|b*?", "a|bc+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest77") {
  STest fixture({"a+|bb", "ab|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest78") {
  STest fixture({"(a?)", "a*a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest79") {
  STest fixture({"a+?|b|c", "a*|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest80") {
  STest fixture({"a*|b|c", "a|aba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest81") {
  STest fixture({"ab|c?", "a+?|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest82") {
  STest fixture({"a|bac", "a|b|a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest83") {
  STest fixture({"a+a*", "a??a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest84") {
  STest fixture({"a+|a|b", "a|b|a|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest85") {
  STest fixture({"a+|b|a", "a*?a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest86") {
  STest fixture({"a*a+", "a?a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest87") {
  STest fixture({"a|bc|b", "a*|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest88") {
  STest fixture({"a+?|b?", "(a)|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest89") {
  STest fixture({"a*a??", "a??|a|a"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest90") {
  STest fixture({"a|a|b*", "a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest91") {
  STest fixture({"a??|a??", "a?|b"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest92") {
  STest fixture({"a|abb", "a|ba??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest93") {
  STest fixture({"a+|a*", "a*?|(a)"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest94") {
  STest fixture({"a|b|(b)", "aa|a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest95") {
  STest fixture({"a??b?", "aaa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest96") {
  STest fixture({"a|a|a?", "a*?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest97") {
  STest fixture({"aa|a|a", "a*|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest98") {
  STest fixture({"a*?|b|c", "a|aa|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest99") {
  STest fixture({"a|b|c*?", "abb|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest100") {
  STest fixture({"abb*", "a??|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest101") {
  STest fixture({"(a?)", "aaa*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest102") {
  STest fixture({"ab|bb", "ab|c."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest103") {
  STest fixture({"a|a??", "a+?|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest104") {
  STest fixture({"a", "aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest105") {
  STest fixture({"aa|a|a", "a+|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest106") {
  STest fixture({"a|ab+", "a|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest107") {
  STest fixture({"a|b|c|.", "a??a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest108") {
  STest fixture({"aa|(a)", "a|b|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest109") {
  STest fixture({"aa|a|b", "a|b|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest110") {
  STest fixture({"a*b", "aa*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest111") {
  STest fixture({"a?aa", "a+a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest112") {
  STest fixture({"aaa*", "a*a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest113") {
  STest fixture({"aa|bb", "ab|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest114") {
  STest fixture({"a+?|ab", "ab+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest115") {
  STest fixture({"a+?", "(a)*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest116") {
  STest fixture({"a|b|ab", "aab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest117") {
  STest fixture({"a??a?", "a*?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest118") {
  STest fixture({"a??|(a)", "a|a|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest119") {
  STest fixture({"a*?|b??", "a|abc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest120") {
  STest fixture({"a*?|b|c", "a+?|a*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest121") {
  STest fixture({"a|b*", "(a)(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest122") {
  STest fixture({"a+?b", "a|aba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest123") {
  STest fixture({"aa(a)", "a|b|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest124") {
  STest fixture({"a|a|ba", "a?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest125") {
  STest fixture({"a|bbc", "ab|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest126") {
  STest fixture({"a|aa*", "abc|."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest127") {
  STest fixture({"aa|ab", "(a)(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest128") {
  STest fixture({"a+?|(b)", "a+?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest129") {
  STest fixture({"a?b|b", "aaba"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest130") {
  STest fixture({"a|ba+", "a+|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest131") {
  STest fixture({"a*|(b)", "a?a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest132") {
  STest fixture({"a+|a*", "a|ba*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest133") {
  STest fixture({"a??|a*?", "abb??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest134") {
  STest fixture({"a+a??", "a+?|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest135") {
  STest fixture({"a*?|b?", "a*?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest136") {
  STest fixture({"aa+", "a+bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest137") {
  STest fixture({"a|a(b)", "a+?|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest138") {
  STest fixture({"a?bc", "a|a|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest139") {
  STest fixture({"a+?b|b", "a+|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest140") {
  STest fixture({"aba+", "aaa+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest141") {
  STest fixture({"a*|b*", "a|aa|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest142") {
  STest fixture({"abb|a", "a?|b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest143") {
  STest fixture({"a+?b+?", "a+|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest144") {
  STest fixture({"a*?a*", "a|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest145") {
  STest fixture({"a|ba", "ab|ca"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest146") {
  STest fixture({"a?|b+?", "ab|bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest147") {
  STest fixture({"aaa*?", "abca"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest148") {
  STest fixture({"a+?|b??", "a*?|a+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest149") {
  STest fixture({"aba*?", "a+?a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest150") {
  STest fixture({"ab|c?", "aaa?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest151") {
  STest fixture({"a|b*", "a|bbc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest152") {
  STest fixture({"a+|b", "a|baa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest153") {
  STest fixture({"a+bb", "a?|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest154") {
  STest fixture({"a|b|bc", "a*?|b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest155") {
  STest fixture({"a|b?", "a+a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest156") {
  STest fixture({"a?|a+?", "a*|b?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest157") {
  STest fixture({"a|b|c+?", "a+|aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest158") {
  STest fixture({"a|b|b*", "aaa+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest159") {
  STest fixture({"a|a(a)", "ab|c."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest160") {
  STest fixture({"a*(b)", "a|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest161") {
  STest fixture({"a+ab", "a?aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest162") {
  STest fixture({"a+|b+?", "(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest163") {
  STest fixture({"a+ba", "a+?ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest164") {
  STest fixture({"ab|c", "a??|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest165") {
  STest fixture({"a|a|b??", "a|b|a*?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest166") {
  STest fixture({"aab*?", "(a|b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest167") {
  STest fixture({"a|ba+?", "aab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest168") {
  STest fixture({"abcc", "a|bc+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest169") {
  STest fixture({"a|a|a+?", "a*?|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest170") {
  STest fixture({"a*?", "a|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest171") {
  STest fixture({"a+bb", "a|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest172") {
  STest fixture({"a+ab", "ab|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest173") {
  STest fixture({"a?b+?", "ab|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest174") {
  STest fixture({"a*a?", "a+|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest175") {
  STest fixture({"a*?(a)", "a|aa|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest176") {
  STest fixture({"a?|aa", "a+b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest177") {
  STest fixture({"aa|a", "aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest178") {
  STest fixture({"a*|ab", "a|b|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest179") {
  STest fixture({"a?|b??", "a*?a?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest180") {
  STest fixture({"a|b|(b)", "a??b*"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest181") {
  STest fixture({"a*?|b+", "a*?|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest182") {
  STest fixture({"ab|ac", "a|a|b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest183") {
  STest fixture({"a|ba?", "a+b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest184") {
  STest fixture({"a|bcc", "a?|ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest185") {
  STest fixture({"ab|(a)", "a*|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest186") {
  STest fixture({"a*?b|a", "aab|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest187") {
  STest fixture({"a|b|b?", "a+?|b|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest188") {
  STest fixture({"ab|aa", "a|b|c|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest189") {
  STest fixture({"a|ba*", "ab|c|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest190") {
  STest fixture({"aaab", "a??b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest191") {
  STest fixture({"a|b|(a)", "a?|b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest192") {
  STest fixture({"a|b|cb", "a|b|c|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest193") {
  STest fixture({"a+|bc", "ab?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest194") {
  STest fixture({"a??|a+?", "a??ab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest195") {
  STest fixture({"a|bc|c", "a+?b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest196") {
  STest fixture({"a+?ba", "a??|a|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest197") {
  STest fixture({"a?|a|b", "a*|a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest198") {
  STest fixture({"aba|b", "a*?a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest199") {
  STest fixture({"a??|a*?", "abcb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest200") {
  STest fixture({"a|baa", "aaa??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest201") {
  STest fixture({"a?|bb", "a|b|b*"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest202") {
  STest fixture({"aa|b|b", "ab(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest203") {
  STest fixture({"a?|a|b", "a?a??"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest204") {
  STest fixture({"ab|b|c", "a+aa"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest205") {
  STest fixture({"a??|bc", "(a+?)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest206") {
  STest fixture({"ab|bb", "a+?|b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest207") {
  STest fixture({"a|aa+?", "ab|a?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest208") {
  STest fixture({"a??|a+", "abb*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest209") {
  STest fixture({"ab??", "a+b?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest210") {
  STest fixture({"a+b+", "a??a+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest211") {
  STest fixture({"(a)(a)", "a+?bc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest212") {
  STest fixture({"a??aa", "a|bca"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest213") {
  STest fixture({"a+?a?", "a|a|b|c"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest214") {
  STest fixture({"a??ba", "a+?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest215") {
  STest fixture({"a|b|aa", "a*bb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest216") {
  STest fixture({"a|aa??", "aaa+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest217") {
  STest fixture({"a?|a?", "a*a|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest218") {
  STest fixture({"ab|a|b", "a|ba+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest219") {
  STest fixture({"aab+?", "a+?a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest220") {
  STest fixture({"a|ab*", "a*b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest221") {
  STest fixture({"a*ab", "ab|ac"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest222") {
  STest fixture({"a|b|b|a", "(a)|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest223") {
  STest fixture({"a?aa", "a|ba+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest224") {
  STest fixture({"ab|c|c", "a|b|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest225") {
  STest fixture({"a?|bb", "a*|b+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest226") {
  STest fixture({"a+|ab", "a?b*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest227") {
  STest fixture({"aab*", "(a*)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest228") {
  STest fixture({"abac", "a|b|a*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest229") {
  STest fixture({"a+|b*?", "a|b|c."});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest230") {
  STest fixture({"aba|c", "a|ab|a"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest231") {
  STest fixture({"a+|ab", "aab+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest232") {
  STest fixture({"aa(b)", "a*?|b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest233") {
  STest fixture({"a|bc.", "a|abc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest234") {
  STest fixture({"a|b(b)", "a|bab"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 1, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest235") {
  STest fixture({"aa|bc", "a?b"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest236") {
  STest fixture({"a|b|(b)", "a|a|a??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest237") {
  STest fixture({"ab|c|a", "(a?)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest238") {
  STest fixture({"((a))", "a+b+?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest239") {
  STest fixture({"a|b|a*?", "a??|a+?"});
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoMultipatternStartsWithTest240") {
  STest fixture({"aab", "a*a?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest241") {
  STest fixture({"a+|b*?", "a+?b+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest242") {
  STest fixture({"a?aa", "a*|(b)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest243") {
  STest fixture({"a|bb+?", "abbc"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest244") {
  STest fixture({"abc|a", "a+|a+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
    {0, 3, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest245") {
  STest fixture({"a+?|a??", "abb"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest246") {
  STest fixture({"ab|a+?", "a?|(a)"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest247") {
  STest fixture({"a+b+", "ab|b??"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest248") {
  STest fixture({"ab|c*", "aab*?"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  const std::vector<SearchHit> expected{
    {0, 2, 1},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoMultipatternStartsWithTest249") {
  STest fixture({"a??bb", "ab|c+"});
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);

  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}
