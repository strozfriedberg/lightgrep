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

#include "catch.hpp"

#include <algorithm>
#include <cstring>

#include "stest.h"


TEST_CASE("abSearch") {
  STest fixture("ab");
  fixture.search("abc");
  const std::vector<SearchHit> expected { SearchHit(0, 2, 0) };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbSearch") {
  STest fixture("a|b");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbOrcSearch") {
  STest fixture("a|b|c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbcSearch") {
  STest fixture("a|bc");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aAndbOrcSearch") {
  STest fixture("a(b|c)");
  fixture.search("abac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(2, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("abQuestionSearch") {
  STest fixture("ab?");
  fixture.search("aab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("abQcQdSearch") {
  STest fixture("ab?c?d");
  //                   012345678901234
  fixture.search("ad abcd abd acd", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(3, 7, 0),
    SearchHit(8, 11, 0),
    SearchHit(12, 15, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbQcSearch") {
  STest fixture("(a|b?)c");
  //                   01234567890
  fixture.search("ac bc c abc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(3, 5, 0),
    SearchHit(6, 7, 0),
    SearchHit(9, 11, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbPlusSearch") {
  STest fixture("(a|b)+");
  fixture.search(" abbaaaba ", 0);
  const std::vector<SearchHit> expected {
    SearchHit(1, 9, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbPlusShorterSearch") {
  STest fixture("(a|b)+");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbPlusShorterSearch2") {
  STest fixture("(a|b)+c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("fourKeysSearch") {
  STest fixture({"a(b|c)a", "ac+", "ab?a", "two"});
  //                   01234567890123
  fixture.search("aba aa aca two", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 2),
    SearchHit(0, 3, 0),
    SearchHit(4, 6, 2),
    SearchHit(7, 9, 1),
    SearchHit(7, 10, 0),
    SearchHit(11, 14, 3),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrbStarbPlusSearch") {
  STest fixture("(a|b)*b+");
  //                    01234567890
  fixture.search(" abbaaaba b", 0);
  const std::vector<SearchHit> expected {
    SearchHit(1, 8, 0),
    SearchHit(10, 11, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("dotPlusSearch") {
  STest fixture(".+");
  fixture.search("whatever", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 8, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("pastFourGBSearch") {
  STest fixture("a");
  const uint64_t fourgb = 0x0000000100000000;
  const char text[] = "ba";
  fixture.search(text, text + 2, fourgb);
  const std::vector<SearchHit> expected {
    SearchHit(fourgb + 1, fourgb + 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("zeroDotStarZeroSearch") {
  STest fixture("0.*0");
  fixture.search("00000", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 5, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aDotaPlusSearch") {
  STest fixture("a.a+");
  fixture.search("aaabaaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
    SearchHit(4, 7, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("badLabelingSearch") {
  STest fixture({"x", "x", "yyy"});
  fixture.search("yyy", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 2),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("zeroZeroSearch") {
  STest fixture("00");
  fixture.search("0000", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(2, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaaOraSearch") {
  STest fixture("aaa|a");
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPlusbOraSearch") {
  STest fixture("a+b|a");
  fixture.search("aaab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPlusOrabSearch") {
  STest fixture("a+|ab");
  fixture.search("cab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQuestionQuestionbSearch") {
  STest fixture("a??b");
  fixture.search("abcb", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(3, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQQbQQcSearch") {
  STest fixture("a??b??c");
  fixture.search("abcbc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
    SearchHit(3, 5, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQQbQcSearch") {
  STest fixture("a??b?c");
  fixture.search("abcbcc", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
    SearchHit(3, 5, 0),
    SearchHit(5, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQQOrBQQcSearch") {
  STest fixture(R"((a??|b??)c)");
  fixture.search("c", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrBQaSearch") {
  STest fixture("(a|b?)a");
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrBQQaSearch") {
  STest fixture(R"((a|b??)a)");
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQSearch") {
  STest fixture("a+?");
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaQQSearch") {
  STest fixture("aa??");
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaSQSearch") {
  STest fixture("aa*?");
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQbQSearch") {
  STest fixture("a+?b?");
  fixture.search("aab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQbSSearch") {
  STest fixture("a+?b*");
  fixture.search("aab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrDotOraOraSearch") {
  STest fixture("a|.|a|a");
  fixture.search("b", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aLPaOra0RPSearch") {
  STest fixture("a(a|a{0})");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQaSaSearch") {
  STest fixture("a?a*a");
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQdotQQaSQSearch") {
  STest fixture("a+?.??a*?");
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aadotPQaPQaSSearch") {
  STest fixture("aa.+?a+?a*");
  fixture.search("aaaba", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 5, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aSdotQaSaSearch") {
  STest fixture("a*.?a*a");
  fixture.search("aaabaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPOrDotPSearch") {
  STest fixture("a+|.+");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaaaOraQaSearch") {
  STest fixture("aaaa|a?a");
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaaaOraaOraSearch") {
  STest fixture("aaaa|aa|a");
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaaOraaOraaDotSearch") {
  STest fixture("aaa|aa|aa.");
  fixture.search("aaabaac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
    SearchHit(4, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aSQdotPQdotQaSearch") {
  STest fixture("a*?.+?.?a");
  fixture.search("aaab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaaaOrDotOrDotaDot_aOrDotaaSearch") {
  STest fixture({ "aaaa|.|.a.", "a|.aa" });
  fixture.search("aaab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 1),
    SearchHit(1, 2, 1),
    SearchHit(2, 3, 1),
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(2, 3, 0),
    SearchHit(3, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aDotaOrDotPQaDotSearch") {
  STest fixture("a.a|.+?a.");
  fixture.search("aaabaac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
    SearchHit(3, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("DotPQaDotSearch") {
  STest fixture(".+?a.");
  fixture.search("aaabaac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 0),
    SearchHit(3, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aDotOrDotaOraaSearch") {
  STest fixture("a.|.a|aa");
  fixture.search("aaabaac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 0),
    SearchHit(2, 4, 0),
    SearchHit(4, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("a22Search") {
  STest fixture("(a{2}){2}");
  fixture.search("aaaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("a10000Search") {
  STest fixture("a{10000}");
  char text[10000];
  std::fill(text, text + sizeof(text), 'a');
  fixture.search(text, text + sizeof(text), 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, sizeof(text), 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOraaQ_aOrbSearch") {
  STest fixture({"a|aa?", "a|b"});
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 1),
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 1),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOraa_aOrbSearch") {
  STest fixture({"a|aa", "a|b"});
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 1),
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 1),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPOrDotOraaDot_aaDotPDotDotaQSearch") {
  STest fixture({ "a+|.|aa.", "aa.+..a*" });
  fixture.search("baac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 3, 0),
    SearchHit(3, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPOrDotOraaDot_aaDotPSearch") {
  STest fixture({ "a+|.|aa.", "aa.+" });
  fixture.search("baac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 3, 0),
    SearchHit(3, 4, 0),
    SearchHit(1, 4, 1),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aDotaQQOraOrDotPQ_aQaOrDotPaQQSearch") {
  STest fixture({ "a.a??|a|.+?", "a?a|.+a??" });
  fixture.search("aaab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 1),
    SearchHit(0, 2, 0),
    SearchHit(2, 4, 0),
    SearchHit(2, 3, 1),
    SearchHit(3, 4, 1),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQQa_aaSearch") {
  STest fixture({ "a??a", "aa" });
  fixture.search("aa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(0, 2, 1),
    SearchHit(1, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aQQaOraaPQDot_aaSearch") {
  STest fixture({ "a??a|aa+?.", "aa" });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(0, 2, 1),
    SearchHit(1, 2, 0),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaa_aaaOraSearch") {
  STest fixture({ "aaa", "aaa|a" });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 1),
    SearchHit(0, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQab_aPQaOrbSearch") {
  STest fixture({ "a+?ab", "a+?a|b" });
  fixture.search("aaab", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 1),
    SearchHit(0, 4, 0),
    SearchHit(3, 4, 1),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQa_aPQaSearch") {
  STest fixture({ "a+?a", "a+?a" });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 2, 1),
    SearchHit(0, 2, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aSQaSQDot_aPDotPQSearch") {
  STest fixture({ "a*?a*?.", "a+.+?" });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(2, 3, 0),
    SearchHit(0, 3, 1),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aaaPQDotPOra_aDotaOrDotPQaDotSearch") {
  STest fixture({ "aaa+?.+|a", "a.a|.+?a." });
  fixture.search("aaabaac", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 1),
    SearchHit(3, 6, 1),
    SearchHit(0, 7, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQOrDotPDotDotOrDota_aSDotaaSQOrDotP_DotP_DotDotaaOrDotPQSearch") {
  STest fixture({ "a+?|.+..|.a", "a*.aa*?|.+", ".+", "..aa|.+?" });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(0, 3, 2),
    SearchHit(0, 3, 1),
    SearchHit(0, 1, 3),
    SearchHit(1, 2, 3),
    SearchHit(2, 3, 0),
    SearchHit(2, 3, 3),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aOrDota_DotDotaOrDotSearch") {
  STest fixture({ "a|.a", "..a|." });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(0, 3, 1),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aPQOrDotPDotDot_aSDotaaSQOrDotP_aPQDotaOrDotPSearch") {
  STest fixture({ R"(a+?|.+..)", R"(a*.aa*?|.+)", R"(a+?.a|.+)" });
  fixture.search("aaa", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 3, 2),
    SearchHit(0, 3, 1),
    SearchHit(0, 1, 0),
    SearchHit(1, 2, 0),
    SearchHit(2, 3, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("aSQaSDotaPQ_aPDotaSaSearch") {
  STest fixture({ R"(a*?a*.a+?)", R"(a+.a*a)" });
  fixture.search("aaabaaca", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 5, 0),
    SearchHit(0, 6, 1),
    SearchHit(5, 8, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("metaCCSearch") {
  STest fixture("[|()?+*]+");
  fixture.search("|()?+*", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 6, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("dot4OraQaSearch") {
  STest fixture(R"(.{4}|a?a)");
  fixture.search("aaabaacabbabcacbaccbbbcbccca", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 4, 0),
    SearchHit(4, 8, 0),
    SearchHit(8, 12, 0),
    SearchHit(12, 16, 0),
    SearchHit(16, 20, 0),
    SearchHit(20, 24, 0),
    SearchHit(24, 28, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("nestedAlternationTest") {
  STest fixture(R"(vegeta((ble)|(rian)|(t((ive)|(e)|(ion)))))");
  fixture.search("vegetable vegetarian vegetative vegetate vegetation", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 9, 0),
    SearchHit(10, 20, 0),
    SearchHit(21, 31, 0),
    SearchHit(32, 40, 0),
    SearchHit(41, 51, 0),
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("searchReturnValueTest1") {
  STest fixture(R"(a+b)");
  fixture.search("aaaba", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 4, 0),
  };
  REQUIRE(expected == fixture.Hits);
  REQUIRE(4u == fixture.RetVal);
}

TEST_CASE("searchReturnValueTest2") {
  STest fixture(R"(a+b)");
  fixture.search("aaabaacabbabcacbaccbbbcbccca", 0);
  const std::vector<SearchHit> expected {
    SearchHit(0, 4, 0),
    SearchHit(7, 9, 0),
    SearchHit(10, 12, 0),
  };
  REQUIRE(expected == fixture.Hits);
  REQUIRE(27u == fixture.RetVal);
}

/*
TEST_CASE("hitCaching") {
  STest fixture("[a-zA-Z]+ing");
  // 2011-05-06. This pattern causes Vm to continue buffering hits in the Matches vector until closeOut().
  const char text[] = "ping winging it";
  fixture.Grep->search(text, &text[5], 0); // generates hit, but not emitted
  SCOPE_ASSERT_EQUAL(0u, fixture.Hits.size());
  fixture.Grep->search(&text[5], &text[15], 5); // generates a hit on 'wing', emits hit on 'ping'
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  fixture.Grep->closeOut(fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size()); // flushes last hit
    SearchHit(0, 4, 0),
    SearchHit(5, 12, 0),
}
*/
