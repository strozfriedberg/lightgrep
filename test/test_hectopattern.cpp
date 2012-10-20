/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

#include <algorithm>

#include "stest.h"

SCOPE_FIXTURE_CTOR(hundredPatternSearch, STest, STest({
  "a|a??.|.|a?",
  "a?|aa|a??a+?",
  "a*(a)|a*?|.+",
  "a??a+.+?(a)",
  "a+(.).*?a.",
  "a??|.|.|aa|aa",
  "a+?|.?aa|a*",
  "a|a|.|.|.+.+",
  "a?|.?|.??.|a",
  "a+a+?|.+|.*?",
  "a+?|.+..|.a",
  "a?a+|a?|.|.",
  "a|a|aa.*|a+?",
  "a*a?a??|.+",
  "a+|a|.|.|(a)",
  "aa|.?.+?|.+?",
  "aa+?a*(a)",
  "a?|a|.a|a.",
  "(a)|(.)a|.a*?",
  "a*?|a*?|a*?|.|a",
  "a|.+?|a|a.+",
  "a*.aa*?|.+",
  "a??|(.).*.+?",
  "a+?|.?|.?a*",
  "a?.*..|a?",
  "a*?|.+(.)",
  "a*|aa|aa|.a",
  "a+?...a|.+",
  "a|.(.)aa|.+?",
  "a+?|a|.|a|.a.",
  "a?.?|.|.|a*",
  R"(a|a.??(a.))",
  "a.|(a)|(.*?)",
  "a.aaa??a.",
  "a??.*.??a+?",
  "a.(.)(a|.)",
  "a+.?|.|.(.)",
  "a*?a??a*?|a?",
  "a*?a.|.?a?",
  "a+aa..|a+",
  "a?|a+?|a|.(.)",
  "a|a.+|a*?a|a",
  "a+?|a|aa??|(.)",
  "a|.??a*|.a",
  "a??|.??..|.*",
  "a+?|a?.?a.",
  "aa(a).|a|.",
  "a|.|.+a|.",
  "aa.*.a.+",
  "a*.+?|.*|.*",
  "a+?a?|a|a|.*?",
  "aaaa|a|.|a|.",
  "aaaa*.a",
  "a?|a+?|a|a|aa",
  "aa*|.*|.+?",
  "a*.+?(a)*",
  "a+?(a)|a.a?",
  "a.a?a+(a)",
  "a+|(a)..|.",
  "a+?|a*?a|.|a",
  "a+?|a|.|a|(a)",
  "(a)|(a)|.a*?",
  "a|aa?a|.|.*?",
  "a|a|(a).*a+?",
  "a?|..|a.*?",
  "a+a+?|.|.|a*?",
  "a?|.+|(.)+",
  "a+..|.*|a*?",
  "a*?|.|a|a+?|.|.",
  "a*?a*?..|.",
  "a??|a*|a.+?",
  "a?a+.|.(a)",
  "a+.+?|a*?aa",
  "a?.*aa(.)",
  "a*?|a*|a.|a|a",
  "a?|(.).?|a+?",
  "a|.|.*|.aa*?",
  "a|a|.*|.?a??",
  "a*?.*|aa|a",
  "a+a|a.|.|a|.",
  "a.a|..|(.)",
  "a|.aaa|.a+",
  "a*?|a?..|(a)",
  "a*a|.|a*?|.*?",
  "a*?.+?.?(a)",
  "a|.(.)..",
  "a|..+|.*.a",
  "a+|.|a*?|.|a",
  "a|a(a).a|.*?",
  "a*?|a*.|.|.+",
  "a?|.?.*?.",
  "a??a.|a?aa",
  "a|..|..|a|(a)",
  "a*?.|.|.?.|.",
  "a??a*|a+|a+",
  "a..a|..|a??",
  "a??|a.|.??|.|a",
  "a??a?a*.?",
  "a.|.*a*?|.|a",
  "a*|..|.|..*?"
})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  std::vector<SearchHit>& actual = fixture.Hits;
  SCOPE_ASSERT_EQUAL(661, actual.size());

  std::vector<SearchHit> expected;
  expected.reserve(661);
  expected.emplace_back(0, 1, 7);
  expected.emplace_back(0, 1, 10);
  expected.emplace_back(0, 1, 12);
  expected.emplace_back(0, 1, 18);
  expected.emplace_back(0, 1, 20);
  expected.emplace_back(0, 1, 28);
  expected.emplace_back(0, 1, 29);
  expected.emplace_back(0, 1, 31);
  expected.emplace_back(0, 1, 41);
  expected.emplace_back(0, 1, 42);
  expected.emplace_back(0, 1, 45);
  expected.emplace_back(0, 1, 47);
  expected.emplace_back(0, 1, 51);
  expected.emplace_back(0, 1, 59);
  expected.emplace_back(0, 1, 60);
  expected.emplace_back(0, 1, 61);
  expected.emplace_back(0, 1, 63);
  expected.emplace_back(0, 1, 81);
  expected.emplace_back(0, 1, 85);
  expected.emplace_back(0, 1, 86);
  expected.emplace_back(0, 1, 92);
  expected.emplace_back(0, 1, 93);
  expected.emplace_back(0, 2, 15);
  expected.emplace_back(0, 2, 56);
  expected.emplace_back(0, 2, 69);
  expected.emplace_back(0, 2, 91);
  expected.emplace_back(0, 3, 14);
  expected.emplace_back(0, 3, 16);
  expected.emplace_back(0, 3, 58);
  expected.emplace_back(0, 3, 79);
  expected.emplace_back(0, 3, 80);
  expected.emplace_back(0, 3, 84);
  expected.emplace_back(0, 4, 35);
  expected.emplace_back(0, 4, 36);
  expected.emplace_back(0, 4, 46);
  expected.emplace_back(0, 4, 71);
  expected.emplace_back(0, 4, 72);
  expected.emplace_back(0, 5, 3);
  expected.emplace_back(0, 5, 21);
  expected.emplace_back(0, 5, 27);
  expected.emplace_back(0, 5, 39);
  expected.emplace_back(0, 5, 52);
  expected.emplace_back(0, 6, 4);
  expected.emplace_back(0, 6, 55);
  expected.emplace_back(0, 7, 73);
  expected.emplace_back(0, 28, 34);
  expected.emplace_back(0, 28, 48);
  expected.emplace_back(1, 2, 7);
  expected.emplace_back(1, 2, 10);
  expected.emplace_back(1, 2, 12);
  expected.emplace_back(1, 2, 18);
  expected.emplace_back(1, 2, 20);
  expected.emplace_back(1, 2, 28);
  expected.emplace_back(1, 2, 29);
  expected.emplace_back(1, 2, 31);
  expected.emplace_back(1, 2, 41);
  expected.emplace_back(1, 2, 42);
  expected.emplace_back(1, 2, 45);
  expected.emplace_back(1, 2, 47);
  expected.emplace_back(1, 2, 51);
  expected.emplace_back(1, 2, 59);
  expected.emplace_back(1, 2, 60);
  expected.emplace_back(1, 2, 61);
  expected.emplace_back(1, 2, 63);
  expected.emplace_back(1, 2, 81);
  expected.emplace_back(1, 2, 85);
  expected.emplace_back(1, 2, 86);
  expected.emplace_back(1, 2, 92);
  expected.emplace_back(1, 2, 93);
  expected.emplace_back(2, 3, 7);
  expected.emplace_back(2, 3, 10);
  expected.emplace_back(2, 3, 12);
  expected.emplace_back(2, 3, 18);
  expected.emplace_back(2, 3, 20);
  expected.emplace_back(2, 3, 28);
  expected.emplace_back(2, 3, 29);
  expected.emplace_back(2, 3, 31);
  expected.emplace_back(2, 3, 41);
  expected.emplace_back(2, 3, 42);
  expected.emplace_back(2, 3, 45);
  expected.emplace_back(2, 3, 47);
  expected.emplace_back(2, 3, 51);
  expected.emplace_back(2, 3, 59);
  expected.emplace_back(2, 3, 60);
  expected.emplace_back(2, 3, 61);
  expected.emplace_back(2, 3, 63);
  expected.emplace_back(2, 3, 81);
  expected.emplace_back(2, 3, 85);
  expected.emplace_back(2, 3, 86);
  expected.emplace_back(2, 3, 92);
  expected.emplace_back(2, 3, 93);
  expected.emplace_back(2, 4, 15);
  expected.emplace_back(2, 4, 69);
  expected.emplace_back(2, 4, 91);
  expected.emplace_back(2, 5, 56);
  expected.emplace_back(2, 6, 57);
  expected.emplace_back(3, 4, 7);
  expected.emplace_back(3, 4, 14);
  expected.emplace_back(3, 4, 20);
  expected.emplace_back(3, 4, 28);
  expected.emplace_back(3, 4, 29);
  expected.emplace_back(3, 4, 42);
  expected.emplace_back(3, 4, 47);
  expected.emplace_back(3, 4, 51);
  expected.emplace_back(3, 4, 58);
  expected.emplace_back(3, 4, 59);
  expected.emplace_back(3, 4, 60);
  expected.emplace_back(3, 4, 61);
  expected.emplace_back(3, 4, 79);
  expected.emplace_back(3, 4, 93);
  expected.emplace_back(3, 5, 18);
  expected.emplace_back(3, 5, 80);
  expected.emplace_back(3, 5, 92);
  expected.emplace_back(3, 6, 45);
  expected.emplace_back(3, 6, 81);
  expected.emplace_back(3, 6, 84);
  expected.emplace_back(3, 7, 85);
  expected.emplace_back(3, 28, 10);
  expected.emplace_back(3, 28, 86);
  expected.emplace_back(4, 5, 7);
  expected.emplace_back(4, 5, 12);
  expected.emplace_back(4, 5, 20);
  expected.emplace_back(4, 5, 28);
  expected.emplace_back(4, 5, 29);
  expected.emplace_back(4, 5, 31);
  expected.emplace_back(4, 5, 41);
  expected.emplace_back(4, 5, 42);
  expected.emplace_back(4, 5, 46);
  expected.emplace_back(4, 5, 47);
  expected.emplace_back(4, 5, 51);
  expected.emplace_back(4, 5, 59);
  expected.emplace_back(4, 5, 60);
  expected.emplace_back(4, 5, 61);
  expected.emplace_back(4, 5, 63);
  expected.emplace_back(4, 5, 93);
  expected.emplace_back(4, 6, 14);
  expected.emplace_back(4, 6, 15);
  expected.emplace_back(4, 6, 58);
  expected.emplace_back(4, 6, 69);
  expected.emplace_back(4, 6, 79);
  expected.emplace_back(4, 6, 91);
  expected.emplace_back(4, 7, 36);
  expected.emplace_back(4, 7, 71);
  expected.emplace_back(4, 7, 72);
  expected.emplace_back(4, 8, 35);
  expected.emplace_back(5, 6, 7);
  expected.emplace_back(5, 6, 12);
  expected.emplace_back(5, 6, 18);
  expected.emplace_back(5, 6, 20);
  expected.emplace_back(5, 6, 28);
  expected.emplace_back(5, 6, 29);
  expected.emplace_back(5, 6, 31);
  expected.emplace_back(5, 6, 39);
  expected.emplace_back(5, 6, 41);
  expected.emplace_back(5, 6, 42);
  expected.emplace_back(5, 6, 46);
  expected.emplace_back(5, 6, 47);
  expected.emplace_back(5, 6, 51);
  expected.emplace_back(5, 6, 59);
  expected.emplace_back(5, 6, 60);
  expected.emplace_back(5, 6, 61);
  expected.emplace_back(5, 6, 63);
  expected.emplace_back(5, 6, 92);
  expected.emplace_back(5, 6, 93);
  expected.emplace_back(5, 8, 3);
  expected.emplace_back(5, 8, 21);
  expected.emplace_back(5, 8, 56);
  expected.emplace_back(5, 8, 80);
  expected.emplace_back(5, 28, 27);
  expected.emplace_back(6, 7, 7);
  expected.emplace_back(6, 7, 14);
  expected.emplace_back(6, 7, 20);
  expected.emplace_back(6, 7, 28);
  expected.emplace_back(6, 7, 29);
  expected.emplace_back(6, 7, 42);
  expected.emplace_back(6, 7, 46);
  expected.emplace_back(6, 7, 47);
  expected.emplace_back(6, 7, 51);
  expected.emplace_back(6, 7, 58);
  expected.emplace_back(6, 7, 59);
  expected.emplace_back(6, 7, 60);
  expected.emplace_back(6, 7, 61);
  expected.emplace_back(6, 7, 79);
  expected.emplace_back(6, 7, 93);
  expected.emplace_back(6, 8, 15);
  expected.emplace_back(6, 8, 18);
  expected.emplace_back(6, 8, 55);
  expected.emplace_back(6, 8, 69);
  expected.emplace_back(6, 8, 81);
  expected.emplace_back(6, 8, 84);
  expected.emplace_back(6, 8, 92);
  expected.emplace_back(6, 9, 45);
  expected.emplace_back(7, 8, 7);
  expected.emplace_back(7, 8, 12);
  expected.emplace_back(7, 8, 14);
  expected.emplace_back(7, 8, 20);
  expected.emplace_back(7, 8, 28);
  expected.emplace_back(7, 8, 29);
  expected.emplace_back(7, 8, 31);
  expected.emplace_back(7, 8, 39);
  expected.emplace_back(7, 8, 41);
  expected.emplace_back(7, 8, 42);
  expected.emplace_back(7, 8, 46);
  expected.emplace_back(7, 8, 47);
  expected.emplace_back(7, 8, 51);
  expected.emplace_back(7, 8, 58);
  expected.emplace_back(7, 8, 59);
  expected.emplace_back(7, 8, 60);
  expected.emplace_back(7, 8, 61);
  expected.emplace_back(7, 8, 63);
  expected.emplace_back(7, 8, 85);
  expected.emplace_back(7, 8, 93);
  expected.emplace_back(7, 9, 36);
  expected.emplace_back(7, 9, 71);
  expected.emplace_back(7, 9, 72);
  expected.emplace_back(7, 9, 79);
  expected.emplace_back(7, 9, 91);
  expected.emplace_back(7, 12, 4);
  expected.emplace_back(8, 9, 7);
  expected.emplace_back(8, 9, 14);
  expected.emplace_back(8, 9, 18);
  expected.emplace_back(8, 9, 20);
  expected.emplace_back(8, 9, 28);
  expected.emplace_back(8, 9, 29);
  expected.emplace_back(8, 9, 42);
  expected.emplace_back(8, 9, 46);
  expected.emplace_back(8, 9, 47);
  expected.emplace_back(8, 9, 51);
  expected.emplace_back(8, 9, 55);
  expected.emplace_back(8, 9, 58);
  expected.emplace_back(8, 9, 59);
  expected.emplace_back(8, 9, 60);
  expected.emplace_back(8, 9, 61);
  expected.emplace_back(8, 9, 93);
  expected.emplace_back(8, 10, 15);
  expected.emplace_back(8, 10, 69);
  expected.emplace_back(8, 10, 80);
  expected.emplace_back(8, 10, 92);
  expected.emplace_back(8, 11, 84);
  expected.emplace_back(8, 12, 85);
  expected.emplace_back(8, 28, 21);
  expected.emplace_back(9, 10, 7);
  expected.emplace_back(9, 10, 14);
  expected.emplace_back(9, 10, 20);
  expected.emplace_back(9, 10, 28);
  expected.emplace_back(9, 10, 29);
  expected.emplace_back(9, 10, 36);
  expected.emplace_back(9, 10, 42);
  expected.emplace_back(9, 10, 46);
  expected.emplace_back(9, 10, 47);
  expected.emplace_back(9, 10, 51);
  expected.emplace_back(9, 10, 58);
  expected.emplace_back(9, 10, 59);
  expected.emplace_back(9, 10, 60);
  expected.emplace_back(9, 10, 61);
  expected.emplace_back(9, 10, 79);
  expected.emplace_back(9, 10, 93);
  expected.emplace_back(9, 11, 18);
  expected.emplace_back(9, 11, 55);
  expected.emplace_back(9, 11, 71);
  expected.emplace_back(9, 11, 81);
  expected.emplace_back(9, 12, 45);
  expected.emplace_back(10, 11, 7);
  expected.emplace_back(10, 11, 12);
  expected.emplace_back(10, 11, 14);
  expected.emplace_back(10, 11, 20);
  expected.emplace_back(10, 11, 28);
  expected.emplace_back(10, 11, 29);
  expected.emplace_back(10, 11, 31);
  expected.emplace_back(10, 11, 39);
  expected.emplace_back(10, 11, 41);
  expected.emplace_back(10, 11, 42);
  expected.emplace_back(10, 11, 46);
  expected.emplace_back(10, 11, 47);
  expected.emplace_back(10, 11, 51);
  expected.emplace_back(10, 11, 58);
  expected.emplace_back(10, 11, 59);
  expected.emplace_back(10, 11, 60);
  expected.emplace_back(10, 11, 61);
  expected.emplace_back(10, 11, 63);
  expected.emplace_back(10, 11, 92);
  expected.emplace_back(10, 11, 93);
  expected.emplace_back(10, 12, 15);
  expected.emplace_back(10, 12, 36);
  expected.emplace_back(10, 12, 56);
  expected.emplace_back(10, 12, 69);
  expected.emplace_back(10, 12, 72);
  expected.emplace_back(10, 12, 79);
  expected.emplace_back(10, 12, 80);
  expected.emplace_back(10, 12, 91);
  expected.emplace_back(10, 14, 3);
  expected.emplace_back(10, 14, 35);
  expected.emplace_back(11, 12, 7);
  expected.emplace_back(11, 12, 14);
  expected.emplace_back(11, 12, 18);
  expected.emplace_back(11, 12, 20);
  expected.emplace_back(11, 12, 28);
  expected.emplace_back(11, 12, 29);
  expected.emplace_back(11, 12, 42);
  expected.emplace_back(11, 12, 46);
  expected.emplace_back(11, 12, 47);
  expected.emplace_back(11, 12, 51);
  expected.emplace_back(11, 12, 55);
  expected.emplace_back(11, 12, 58);
  expected.emplace_back(11, 12, 59);
  expected.emplace_back(11, 12, 60);
  expected.emplace_back(11, 12, 61);
  expected.emplace_back(11, 12, 93);
  expected.emplace_back(11, 13, 92);
  expected.emplace_back(11, 14, 84);
  expected.emplace_back(12, 13, 7);
  expected.emplace_back(12, 13, 14);
  expected.emplace_back(12, 13, 20);
  expected.emplace_back(12, 13, 28);
  expected.emplace_back(12, 13, 29);
  expected.emplace_back(12, 13, 36);
  expected.emplace_back(12, 13, 42);
  expected.emplace_back(12, 13, 46);
  expected.emplace_back(12, 13, 47);
  expected.emplace_back(12, 13, 51);
  expected.emplace_back(12, 13, 58);
  expected.emplace_back(12, 13, 59);
  expected.emplace_back(12, 13, 60);
  expected.emplace_back(12, 13, 61);
  expected.emplace_back(12, 13, 79);
  expected.emplace_back(12, 13, 93);
  expected.emplace_back(12, 14, 15);
  expected.emplace_back(12, 14, 18);
  expected.emplace_back(12, 14, 55);
  expected.emplace_back(12, 14, 69);
  expected.emplace_back(12, 14, 71);
  expected.emplace_back(12, 14, 80);
  expected.emplace_back(12, 14, 81);
  expected.emplace_back(12, 15, 45);
  expected.emplace_back(12, 16, 85);
  expected.emplace_back(13, 14, 7);
  expected.emplace_back(13, 14, 12);
  expected.emplace_back(13, 14, 14);
  expected.emplace_back(13, 14, 20);
  expected.emplace_back(13, 14, 28);
  expected.emplace_back(13, 14, 29);
  expected.emplace_back(13, 14, 31);
  expected.emplace_back(13, 14, 39);
  expected.emplace_back(13, 14, 41);
  expected.emplace_back(13, 14, 42);
  expected.emplace_back(13, 14, 46);
  expected.emplace_back(13, 14, 47);
  expected.emplace_back(13, 14, 51);
  expected.emplace_back(13, 14, 58);
  expected.emplace_back(13, 14, 59);
  expected.emplace_back(13, 14, 60);
  expected.emplace_back(13, 14, 61);
  expected.emplace_back(13, 14, 63);
  expected.emplace_back(13, 14, 92);
  expected.emplace_back(13, 14, 93);
  expected.emplace_back(13, 15, 36);
  expected.emplace_back(13, 15, 56);
  expected.emplace_back(13, 15, 72);
  expected.emplace_back(13, 15, 79);
  expected.emplace_back(13, 15, 91);
  expected.emplace_back(13, 18, 4);
  expected.emplace_back(14, 15, 7);
  expected.emplace_back(14, 15, 14);
  expected.emplace_back(14, 15, 18);
  expected.emplace_back(14, 15, 20);
  expected.emplace_back(14, 15, 28);
  expected.emplace_back(14, 15, 29);
  expected.emplace_back(14, 15, 42);
  expected.emplace_back(14, 15, 46);
  expected.emplace_back(14, 15, 47);
  expected.emplace_back(14, 15, 51);
  expected.emplace_back(14, 15, 55);
  expected.emplace_back(14, 15, 58);
  expected.emplace_back(14, 15, 59);
  expected.emplace_back(14, 15, 60);
  expected.emplace_back(14, 15, 61);
  expected.emplace_back(14, 15, 93);
  expected.emplace_back(14, 16, 15);
  expected.emplace_back(14, 16, 69);
  expected.emplace_back(14, 16, 80);
  expected.emplace_back(14, 16, 92);
  expected.emplace_back(14, 17, 84);
  expected.emplace_back(15, 16, 7);
  expected.emplace_back(15, 16, 14);
  expected.emplace_back(15, 16, 20);
  expected.emplace_back(15, 16, 28);
  expected.emplace_back(15, 16, 29);
  expected.emplace_back(15, 16, 36);
  expected.emplace_back(15, 16, 42);
  expected.emplace_back(15, 16, 46);
  expected.emplace_back(15, 16, 47);
  expected.emplace_back(15, 16, 51);
  expected.emplace_back(15, 16, 58);
  expected.emplace_back(15, 16, 59);
  expected.emplace_back(15, 16, 60);
  expected.emplace_back(15, 16, 61);
  expected.emplace_back(15, 16, 79);
  expected.emplace_back(15, 16, 93);
  expected.emplace_back(15, 17, 18);
  expected.emplace_back(15, 17, 55);
  expected.emplace_back(15, 17, 71);
  expected.emplace_back(15, 17, 81);
  expected.emplace_back(15, 18, 45);
  expected.emplace_back(16, 17, 7);
  expected.emplace_back(16, 17, 12);
  expected.emplace_back(16, 17, 14);
  expected.emplace_back(16, 17, 20);
  expected.emplace_back(16, 17, 28);
  expected.emplace_back(16, 17, 29);
  expected.emplace_back(16, 17, 31);
  expected.emplace_back(16, 17, 39);
  expected.emplace_back(16, 17, 41);
  expected.emplace_back(16, 17, 42);
  expected.emplace_back(16, 17, 46);
  expected.emplace_back(16, 17, 47);
  expected.emplace_back(16, 17, 51);
  expected.emplace_back(16, 17, 58);
  expected.emplace_back(16, 17, 59);
  expected.emplace_back(16, 17, 60);
  expected.emplace_back(16, 17, 61);
  expected.emplace_back(16, 17, 63);
  expected.emplace_back(16, 17, 85);
  expected.emplace_back(16, 17, 92);
  expected.emplace_back(16, 17, 93);
  expected.emplace_back(16, 18, 15);
  expected.emplace_back(16, 18, 36);
  expected.emplace_back(16, 18, 56);
  expected.emplace_back(16, 18, 69);
  expected.emplace_back(16, 18, 72);
  expected.emplace_back(16, 18, 79);
  expected.emplace_back(16, 18, 80);
  expected.emplace_back(16, 18, 91);
  expected.emplace_back(16, 20, 35);
  expected.emplace_back(16, 28, 3);
  expected.emplace_back(17, 18, 7);
  expected.emplace_back(17, 18, 14);
  expected.emplace_back(17, 18, 18);
  expected.emplace_back(17, 18, 20);
  expected.emplace_back(17, 18, 28);
  expected.emplace_back(17, 18, 29);
  expected.emplace_back(17, 18, 42);
  expected.emplace_back(17, 18, 46);
  expected.emplace_back(17, 18, 47);
  expected.emplace_back(17, 18, 51);
  expected.emplace_back(17, 18, 55);
  expected.emplace_back(17, 18, 58);
  expected.emplace_back(17, 18, 59);
  expected.emplace_back(17, 18, 60);
  expected.emplace_back(17, 18, 61);
  expected.emplace_back(17, 18, 93);
  expected.emplace_back(17, 19, 92);
  expected.emplace_back(17, 21, 85);
  expected.emplace_back(17, 28, 84);
  expected.emplace_back(18, 19, 7);
  expected.emplace_back(18, 19, 14);
  expected.emplace_back(18, 19, 18);
  expected.emplace_back(18, 19, 20);
  expected.emplace_back(18, 19, 28);
  expected.emplace_back(18, 19, 29);
  expected.emplace_back(18, 19, 36);
  expected.emplace_back(18, 19, 42);
  expected.emplace_back(18, 19, 46);
  expected.emplace_back(18, 19, 47);
  expected.emplace_back(18, 19, 51);
  expected.emplace_back(18, 19, 55);
  expected.emplace_back(18, 19, 58);
  expected.emplace_back(18, 19, 59);
  expected.emplace_back(18, 19, 60);
  expected.emplace_back(18, 19, 61);
  expected.emplace_back(18, 19, 79);
  expected.emplace_back(18, 19, 93);
  expected.emplace_back(18, 20, 15);
  expected.emplace_back(18, 20, 69);
  expected.emplace_back(18, 20, 80);
  expected.emplace_back(19, 20, 7);
  expected.emplace_back(19, 20, 14);
  expected.emplace_back(19, 20, 18);
  expected.emplace_back(19, 20, 20);
  expected.emplace_back(19, 20, 28);
  expected.emplace_back(19, 20, 29);
  expected.emplace_back(19, 20, 36);
  expected.emplace_back(19, 20, 42);
  expected.emplace_back(19, 20, 46);
  expected.emplace_back(19, 20, 47);
  expected.emplace_back(19, 20, 51);
  expected.emplace_back(19, 20, 55);
  expected.emplace_back(19, 20, 58);
  expected.emplace_back(19, 20, 59);
  expected.emplace_back(19, 20, 60);
  expected.emplace_back(19, 20, 61);
  expected.emplace_back(19, 20, 79);
  expected.emplace_back(19, 20, 93);
  expected.emplace_back(19, 21, 92);
  expected.emplace_back(20, 21, 7);
  expected.emplace_back(20, 21, 14);
  expected.emplace_back(20, 21, 18);
  expected.emplace_back(20, 21, 20);
  expected.emplace_back(20, 21, 28);
  expected.emplace_back(20, 21, 29);
  expected.emplace_back(20, 21, 36);
  expected.emplace_back(20, 21, 42);
  expected.emplace_back(20, 21, 46);
  expected.emplace_back(20, 21, 47);
  expected.emplace_back(20, 21, 51);
  expected.emplace_back(20, 21, 55);
  expected.emplace_back(20, 21, 58);
  expected.emplace_back(20, 21, 59);
  expected.emplace_back(20, 21, 60);
  expected.emplace_back(20, 21, 61);
  expected.emplace_back(20, 21, 79);
  expected.emplace_back(20, 21, 93);
  expected.emplace_back(20, 22, 15);
  expected.emplace_back(20, 22, 69);
  expected.emplace_back(20, 22, 80);
  expected.emplace_back(21, 22, 7);
  expected.emplace_back(21, 22, 14);
  expected.emplace_back(21, 22, 18);
  expected.emplace_back(21, 22, 20);
  expected.emplace_back(21, 22, 28);
  expected.emplace_back(21, 22, 29);
  expected.emplace_back(21, 22, 36);
  expected.emplace_back(21, 22, 42);
  expected.emplace_back(21, 22, 46);
  expected.emplace_back(21, 22, 47);
  expected.emplace_back(21, 22, 51);
  expected.emplace_back(21, 22, 55);
  expected.emplace_back(21, 22, 58);
  expected.emplace_back(21, 22, 59);
  expected.emplace_back(21, 22, 60);
  expected.emplace_back(21, 22, 61);
  expected.emplace_back(21, 22, 79);
  expected.emplace_back(21, 22, 93);
  expected.emplace_back(21, 23, 92);
  expected.emplace_back(21, 25, 85);
  expected.emplace_back(22, 23, 7);
  expected.emplace_back(22, 23, 14);
  expected.emplace_back(22, 23, 18);
  expected.emplace_back(22, 23, 20);
  expected.emplace_back(22, 23, 28);
  expected.emplace_back(22, 23, 29);
  expected.emplace_back(22, 23, 36);
  expected.emplace_back(22, 23, 42);
  expected.emplace_back(22, 23, 46);
  expected.emplace_back(22, 23, 47);
  expected.emplace_back(22, 23, 51);
  expected.emplace_back(22, 23, 55);
  expected.emplace_back(22, 23, 58);
  expected.emplace_back(22, 23, 59);
  expected.emplace_back(22, 23, 60);
  expected.emplace_back(22, 23, 61);
  expected.emplace_back(22, 23, 79);
  expected.emplace_back(22, 23, 93);
  expected.emplace_back(22, 24, 15);
  expected.emplace_back(22, 24, 69);
  expected.emplace_back(22, 24, 80);
  expected.emplace_back(23, 24, 7);
  expected.emplace_back(23, 24, 14);
  expected.emplace_back(23, 24, 18);
  expected.emplace_back(23, 24, 20);
  expected.emplace_back(23, 24, 28);
  expected.emplace_back(23, 24, 29);
  expected.emplace_back(23, 24, 36);
  expected.emplace_back(23, 24, 42);
  expected.emplace_back(23, 24, 46);
  expected.emplace_back(23, 24, 47);
  expected.emplace_back(23, 24, 51);
  expected.emplace_back(23, 24, 55);
  expected.emplace_back(23, 24, 58);
  expected.emplace_back(23, 24, 59);
  expected.emplace_back(23, 24, 60);
  expected.emplace_back(23, 24, 61);
  expected.emplace_back(23, 24, 79);
  expected.emplace_back(23, 24, 93);
  expected.emplace_back(23, 25, 92);
  expected.emplace_back(24, 25, 7);
  expected.emplace_back(24, 25, 14);
  expected.emplace_back(24, 25, 18);
  expected.emplace_back(24, 25, 20);
  expected.emplace_back(24, 25, 28);
  expected.emplace_back(24, 25, 29);
  expected.emplace_back(24, 25, 36);
  expected.emplace_back(24, 25, 42);
  expected.emplace_back(24, 25, 46);
  expected.emplace_back(24, 25, 47);
  expected.emplace_back(24, 25, 51);
  expected.emplace_back(24, 25, 55);
  expected.emplace_back(24, 25, 58);
  expected.emplace_back(24, 25, 59);
  expected.emplace_back(24, 25, 60);
  expected.emplace_back(24, 25, 61);
  expected.emplace_back(24, 25, 79);
  expected.emplace_back(24, 25, 93);
  expected.emplace_back(24, 26, 15);
  expected.emplace_back(24, 26, 69);
  expected.emplace_back(24, 26, 80);
  expected.emplace_back(25, 26, 7);
  expected.emplace_back(25, 26, 14);
  expected.emplace_back(25, 26, 18);
  expected.emplace_back(25, 26, 20);
  expected.emplace_back(25, 26, 28);
  expected.emplace_back(25, 26, 29);
  expected.emplace_back(25, 26, 36);
  expected.emplace_back(25, 26, 42);
  expected.emplace_back(25, 26, 46);
  expected.emplace_back(25, 26, 47);
  expected.emplace_back(25, 26, 51);
  expected.emplace_back(25, 26, 55);
  expected.emplace_back(25, 26, 58);
  expected.emplace_back(25, 26, 59);
  expected.emplace_back(25, 26, 60);
  expected.emplace_back(25, 26, 61);
  expected.emplace_back(25, 26, 79);
  expected.emplace_back(25, 26, 93);
  expected.emplace_back(25, 27, 92);
  expected.emplace_back(26, 27, 7);
  expected.emplace_back(26, 27, 14);
  expected.emplace_back(26, 27, 20);
  expected.emplace_back(26, 27, 28);
  expected.emplace_back(26, 27, 29);
  expected.emplace_back(26, 27, 36);
  expected.emplace_back(26, 27, 42);
  expected.emplace_back(26, 27, 46);
  expected.emplace_back(26, 27, 47);
  expected.emplace_back(26, 27, 51);
  expected.emplace_back(26, 27, 58);
  expected.emplace_back(26, 27, 59);
  expected.emplace_back(26, 27, 60);
  expected.emplace_back(26, 27, 61);
  expected.emplace_back(26, 27, 79);
  expected.emplace_back(26, 27, 93);
  expected.emplace_back(26, 28, 15);
  expected.emplace_back(26, 28, 18);
  expected.emplace_back(26, 28, 55);
  expected.emplace_back(26, 28, 69);
  expected.emplace_back(26, 28, 71);
  expected.emplace_back(26, 28, 80);
  expected.emplace_back(26, 28, 81);
  expected.emplace_back(27, 28, 7);
  expected.emplace_back(27, 28, 12);
  expected.emplace_back(27, 28, 14);
  expected.emplace_back(27, 28, 20);
  expected.emplace_back(27, 28, 28);
  expected.emplace_back(27, 28, 29);
  expected.emplace_back(27, 28, 31);
  expected.emplace_back(27, 28, 36);
  expected.emplace_back(27, 28, 39);
  expected.emplace_back(27, 28, 41);
  expected.emplace_back(27, 28, 42);
  expected.emplace_back(27, 28, 45);
  expected.emplace_back(27, 28, 46);
  expected.emplace_back(27, 28, 47);
  expected.emplace_back(27, 28, 51);
  expected.emplace_back(27, 28, 58);
  expected.emplace_back(27, 28, 59);
  expected.emplace_back(27, 28, 60);
  expected.emplace_back(27, 28, 61);
  expected.emplace_back(27, 28, 63);
  expected.emplace_back(27, 28, 79);
  expected.emplace_back(27, 28, 85);
  expected.emplace_back(27, 28, 92);
  expected.emplace_back(27, 28, 93);

  std::sort(actual.begin(), actual.end());
  std::sort(expected.begin(), expected.begin());

  std::pair<std::vector<SearchHit>::iterator,
            std::vector<SearchHit>::iterator> mis(
    std::mismatch(expected.begin(), expected.end(), actual.begin())
  );

  if (mis.first != expected.end()) {
    SCOPE_ASSERT_EQUAL(*mis.first, *mis.second);
  }
}
