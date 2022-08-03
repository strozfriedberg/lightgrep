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

#include <catch2/catch_test_macros.hpp>

#include "stest.h"

TEST_CASE("autoPatternStartsWithTest250") {
  STest fixture(R"(aa|b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest251") {
  STest fixture(R"(aa|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest252") {
  STest fixture(R"(aa|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest253") {
  STest fixture(R"(aa|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest254") {
  STest fixture(R"(aa|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest255") {
  STest fixture(R"(aa|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest256") {
  STest fixture(R"(aa|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest257") {
  STest fixture(R"(aa|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest258") {
  STest fixture(R"(aa|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest259") {
  STest fixture(R"(aa|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest260") {
  STest fixture(R"(aa|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest261") {
  STest fixture(R"(aa|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest262") {
  STest fixture(R"(aa|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest263") {
  STest fixture(R"(aa|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest264") {
  STest fixture(R"(ab|b+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest265") {
  STest fixture(R"(ab|b*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest266") {
  STest fixture(R"(ab|b?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest267") {
  STest fixture(R"(ab|b+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest268") {
  STest fixture(R"(ab|b*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest269") {
  STest fixture(R"(ab|b??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest270") {
  STest fixture(R"(ab|b{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest271") {
  STest fixture(R"(ab|b{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest272") {
  STest fixture(R"(ab|b{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest273") {
  STest fixture(R"(ab|b{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest274") {
  STest fixture(R"(ab|b{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest275") {
  STest fixture(R"(ab|b{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest276") {
  STest fixture(R"(ab|b{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest277") {
  STest fixture(R"(ab|b{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest278") {
  STest fixture(R"(ab|c+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest279") {
  STest fixture(R"(ab|c*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest280") {
  STest fixture(R"(ab|c?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest281") {
  STest fixture(R"(ab|c+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest282") {
  STest fixture(R"(ab|c*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest283") {
  STest fixture(R"(ab|c??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest284") {
  STest fixture(R"(ab|c{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest285") {
  STest fixture(R"(ab|c{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest286") {
  STest fixture(R"(ab|c{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest287") {
  STest fixture(R"(ab|c{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest288") {
  STest fixture(R"(ab|c{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest289") {
  STest fixture(R"(ab|c{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest290") {
  STest fixture(R"(ab|c{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest291") {
  STest fixture(R"(ab|c{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest292") {
  STest fixture(R"(aa|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest293") {
  STest fixture(R"(ab|a|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest294") {
  STest fixture(R"(aa|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest295") {
  STest fixture(R"(ab|b|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest296") {
  STest fixture(R"(ab|c|a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest297") {
  STest fixture(R"(aa|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest298") {
  STest fixture(R"(ab|a|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest299") {
  STest fixture(R"(aa|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest300") {
  STest fixture(R"(ab|b|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest301") {
  STest fixture(R"(ab|c|b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest302") {
  STest fixture(R"(ab|a|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest303") {
  STest fixture(R"(aa|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest304") {
  STest fixture(R"(ab|b|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest305") {
  STest fixture(R"(ab|c|c)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest306") {
  STest fixture(R"(ab|c|.)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest307") {
  STest fixture(R"(a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest308") {
  STest fixture(R"(a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest309") {
  STest fixture(R"(a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest310") {
  STest fixture(R"(a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest311") {
  STest fixture(R"(a*?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest312") {
  STest fixture(R"(a??)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest313") {
  STest fixture(R"(a{0,1})");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest314") {
  STest fixture(R"(a{2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest315") {
  STest fixture(R"(a{1,2})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest316") {
  STest fixture(R"(a{2,})");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest317") {
  STest fixture(R"(a{0,1}?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest318") {
  STest fixture(R"(a{2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest319") {
  STest fixture(R"(a{1,2}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest320") {
  STest fixture(R"(a{2,}?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest321") {
  STest fixture(R"(a+(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest322") {
  STest fixture(R"(a*(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest323") {
  STest fixture(R"(a?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest324") {
  STest fixture(R"(a+?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest325") {
  STest fixture(R"(a*?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest326") {
  STest fixture(R"(a??(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest327") {
  STest fixture(R"(a{0,1}(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest328") {
  STest fixture(R"(a{2}(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest329") {
  STest fixture(R"(a{1,2}(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest330") {
  STest fixture(R"(a{2,}(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest331") {
  STest fixture(R"(a{0,1}?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest332") {
  STest fixture(R"(a{2}?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest333") {
  STest fixture(R"(a{1,2}?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest334") {
  STest fixture(R"(a{2,}?(a))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest335") {
  STest fixture(R"(a+(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest336") {
  STest fixture(R"(a*(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest337") {
  STest fixture(R"(a?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest338") {
  STest fixture(R"(a+?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest339") {
  STest fixture(R"(a*?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest340") {
  STest fixture(R"(a??(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest341") {
  STest fixture(R"(a{0,1}(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest342") {
  STest fixture(R"(a{2}(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest343") {
  STest fixture(R"(a{1,2}(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest344") {
  STest fixture(R"(a{2,}(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest345") {
  STest fixture(R"(a{0,1}?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest346") {
  STest fixture(R"(a{2}?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest347") {
  STest fixture(R"(a{1,2}?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest348") {
  STest fixture(R"(a{2,}?(b))");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest349") {
  STest fixture(R"(a+a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest350") {
  STest fixture(R"(a*a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest351") {
  STest fixture(R"(a?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest352") {
  STest fixture(R"(a+?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest353") {
  STest fixture(R"(a*?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest354") {
  STest fixture(R"(a??a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest355") {
  STest fixture(R"(a{0,1}a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest356") {
  STest fixture(R"(a{2}a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest357") {
  STest fixture(R"(a{1,2}a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest358") {
  STest fixture(R"(a{2,}a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest359") {
  STest fixture(R"(a{0,1}?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest360") {
  STest fixture(R"(a{2}?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest361") {
  STest fixture(R"(a{1,2}?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest362") {
  STest fixture(R"(a{2,}?a)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest363") {
  STest fixture(R"(a+b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest364") {
  STest fixture(R"(a*b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest365") {
  STest fixture(R"(a?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest366") {
  STest fixture(R"(a+?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest367") {
  STest fixture(R"(a*?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest368") {
  STest fixture(R"(a??b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest369") {
  STest fixture(R"(a{0,1}b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest370") {
  STest fixture(R"(a{2}b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest371") {
  STest fixture(R"(a{1,2}b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest372") {
  STest fixture(R"(a{2,}b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest373") {
  STest fixture(R"(a{0,1}?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest374") {
  STest fixture(R"(a{2}?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest375") {
  STest fixture(R"(a{1,2}?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest376") {
  STest fixture(R"(a{2,}?b)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest377") {
  STest fixture(R"(a+aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest378") {
  STest fixture(R"(a*aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest379") {
  STest fixture(R"(a?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest380") {
  STest fixture(R"(a+?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest381") {
  STest fixture(R"(a*?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest382") {
  STest fixture(R"(a??aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest383") {
  STest fixture(R"(a{0,1}aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest384") {
  STest fixture(R"(a{2}aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest385") {
  STest fixture(R"(a{1,2}aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest386") {
  STest fixture(R"(a{2,}aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest387") {
  STest fixture(R"(a{0,1}?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest388") {
  STest fixture(R"(a{2}?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest389") {
  STest fixture(R"(a{1,2}?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest390") {
  STest fixture(R"(a{2,}?aa)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest391") {
  STest fixture(R"(a+ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest392") {
  STest fixture(R"(a*ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest393") {
  STest fixture(R"(a?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest394") {
  STest fixture(R"(a+?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest395") {
  STest fixture(R"(a*?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest396") {
  STest fixture(R"(a??ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest397") {
  STest fixture(R"(a{0,1}ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest398") {
  STest fixture(R"(a{2}ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest399") {
  STest fixture(R"(a{1,2}ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest400") {
  STest fixture(R"(a{2,}ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest401") {
  STest fixture(R"(a{0,1}?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest402") {
  STest fixture(R"(a{2}?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest403") {
  STest fixture(R"(a{1,2}?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest404") {
  STest fixture(R"(a{2,}?ba)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest405") {
  STest fixture(R"(a+ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest406") {
  STest fixture(R"(a*ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest407") {
  STest fixture(R"(a?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest408") {
  STest fixture(R"(a+?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest409") {
  STest fixture(R"(a*?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest410") {
  STest fixture(R"(a??ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest411") {
  STest fixture(R"(a{0,1}ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest412") {
  STest fixture(R"(a{2}ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest413") {
  STest fixture(R"(a{1,2}ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest414") {
  STest fixture(R"(a{2,}ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest415") {
  STest fixture(R"(a{0,1}?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest416") {
  STest fixture(R"(a{2}?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest417") {
  STest fixture(R"(a{1,2}?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest418") {
  STest fixture(R"(a{2,}?ab)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest419") {
  STest fixture(R"(a+bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest420") {
  STest fixture(R"(a*bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest421") {
  STest fixture(R"(a?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest422") {
  STest fixture(R"(a+?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest423") {
  STest fixture(R"(a*?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest424") {
  STest fixture(R"(a??bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest425") {
  STest fixture(R"(a{0,1}bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest426") {
  STest fixture(R"(a{2}bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest427") {
  STest fixture(R"(a{1,2}bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest428") {
  STest fixture(R"(a{2,}bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest429") {
  STest fixture(R"(a{0,1}?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest430") {
  STest fixture(R"(a{2}?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest431") {
  STest fixture(R"(a{1,2}?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest432") {
  STest fixture(R"(a{2,}?bb)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest433") {
  STest fixture(R"(a+bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest434") {
  STest fixture(R"(a*bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest435") {
  STest fixture(R"(a?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest436") {
  STest fixture(R"(a+?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest437") {
  STest fixture(R"(a*?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest438") {
  STest fixture(R"(a??bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest439") {
  STest fixture(R"(a{0,1}bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest440") {
  STest fixture(R"(a{2}bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest441") {
  STest fixture(R"(a{1,2}bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest442") {
  STest fixture(R"(a{2,}bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest443") {
  STest fixture(R"(a{0,1}?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest444") {
  STest fixture(R"(a{2}?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest445") {
  STest fixture(R"(a{1,2}?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest446") {
  STest fixture(R"(a{2,}?bc)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest447") {
  STest fixture(R"(a+a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest448") {
  STest fixture(R"(a*a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest449") {
  STest fixture(R"(a?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest450") {
  STest fixture(R"(a+?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest451") {
  STest fixture(R"(a*?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest452") {
  STest fixture(R"(a??a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest453") {
  STest fixture(R"(a{0,1}a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest454") {
  STest fixture(R"(a{2}a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest455") {
  STest fixture(R"(a{1,2}a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest456") {
  STest fixture(R"(a{2,}a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest457") {
  STest fixture(R"(a{0,1}?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest458") {
  STest fixture(R"(a{2}?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest459") {
  STest fixture(R"(a{1,2}?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest460") {
  STest fixture(R"(a{2,}?a+)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest461") {
  STest fixture(R"(a+a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest462") {
  STest fixture(R"(a*a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest463") {
  STest fixture(R"(a?a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest464") {
  STest fixture(R"(a+?a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest465") {
  STest fixture(R"(a*?a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest466") {
  STest fixture(R"(a??a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest467") {
  STest fixture(R"(a{0,1}a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest468") {
  STest fixture(R"(a{2}a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest469") {
  STest fixture(R"(a{1,2}a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest470") {
  STest fixture(R"(a{2,}a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest471") {
  STest fixture(R"(a{0,1}?a*)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest472") {
  STest fixture(R"(a{2}?a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest473") {
  STest fixture(R"(a{1,2}?a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest474") {
  STest fixture(R"(a{2,}?a*)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest475") {
  STest fixture(R"(a+a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest476") {
  STest fixture(R"(a*a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest477") {
  STest fixture(R"(a?a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest478") {
  STest fixture(R"(a+?a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest479") {
  STest fixture(R"(a*?a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest480") {
  STest fixture(R"(a??a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest481") {
  STest fixture(R"(a{0,1}a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest482") {
  STest fixture(R"(a{2}a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest483") {
  STest fixture(R"(a{1,2}a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest484") {
  STest fixture(R"(a{2,}a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest485") {
  STest fixture(R"(a{0,1}?a?)");
  REQUIRE(fixture.parsesButNotValid());
}

TEST_CASE("autoPatternStartsWithTest486") {
  STest fixture(R"(a{2}?a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest487") {
  STest fixture(R"(a{1,2}?a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest488") {
  STest fixture(R"(a{2,}?a?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest489") {
  STest fixture(R"(a+a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest490") {
  STest fixture(R"(a*a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest491") {
  STest fixture(R"(a?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest492") {
  STest fixture(R"(a+?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest493") {
  STest fixture(R"(a*?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest494") {
  STest fixture(R"(a??a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest495") {
  STest fixture(R"(a{0,1}a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest496") {
  STest fixture(R"(a{2}a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest497") {
  STest fixture(R"(a{1,2}a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest498") {
  STest fixture(R"(a{2,}a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("autoPatternStartsWithTest499") {
  STest fixture(R"(a{0,1}?a+?)");
  const char text[] = "aaabaacabbabcacbaccbbbcbccca";
  fixture.startsWith(text, text + 28, 0);
  const std::vector<SearchHit> expected{
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
