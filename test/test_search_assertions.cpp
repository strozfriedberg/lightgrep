/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2015, Lightbox Technologies, Inc

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

/*
SCOPE_FIXTURE_CTOR(poorMansTokenizerSearch, STest, STest(R"(\b\w+\b)")) {
  const char text[] = "tokenizing with a regex the horror the horror";
  fixture.search(text, text + 45, 0);
  SCOPE_ASSERT_EQUAL(8u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 15, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 23, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 27, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(28, 34, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(35, 38, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(39, 45, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(nonWordBreakTest, STest, STest(R"(\B\w+\B)")) {
  // NB: 'a' drops out due to being too short. :)
  const char text[] = "tokenizing with a regex the horror the horror";
  fixture.search(text, text + 45, 0);
  SCOPE_ASSERT_EQUAL(7u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 9, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(29, 33, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(36, 37, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(40, 44, 0), fixture.Hits[6]);
}

// William Carlos Williams, 1883-1963
const char wcw[] = R"(This Is Just To Say

I have eaten
the plums
that were in
the icebox

and which
you were probably
saving
for breakfast

Forgive me
they were delicious
so sweet
and so cold)";

SCOPE_FIXTURE_CTOR(firstWordOnLineSearch, STest, STest(R"(^\w+)")) {
  fixture.search(wcw, wcw + 170, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(34, 37, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(44, 48, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(57, 60, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(69, 72, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(79, 82, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(97, 103, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(104, 107, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(119, 126, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(130, 134, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(150, 152, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(159, 162, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(lastWordOnLineSearch, STest, STest(R"(\w+$)")) {
  fixture.search(wcw, wcw + 170, 0);
  SCOPE_ASSERT_EQUAL(13u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(16, 19, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(28, 33, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(38, 43, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(54, 56, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(61, 67, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(73, 78, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(88, 96, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(97, 103, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(108, 117, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(127, 129, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(140, 149, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(153, 158, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(166, 170, 0), fixture.Hits[12]);  
}

SCOPE_FIXTURE_CTOR(firstWordSearch, STest, STest(R"(\A\w+)")) {
  fixture.search(wcw, wcw + 170, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(lastWordSearch, STest, STest(R"(\w+\Z)")) {
  fixture.search(wcw, wcw + 170, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(166, 170, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(whackAwhackZSearch, STest, STest(R"(\A\Z)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(whackZwhackASearch, STest, STest(R"(\Z\A)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(caretDollarSignSearch, STest, STest(R"(^$)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(dollarSignCaretSearch, STest, STest(R"($^)")) {
  SCOPE_ASSERT(fixture.parsesButNotValid());
}

SCOPE_FIXTURE_CTOR(paperSizeSearch, STest, STest(R"(PC LOAD \K\w+)")) {
  const char text[] = "PC LOAD LETTER";
  fixture.search(text, text + 14, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(8, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(lookBackInAngerTest, STest, STest(R"((?<=in Anger).*)")) {
  const char text[] = "_Look Back in Anger_, by John Osborne";
  fixture.search(text, text + 37, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(19, 37, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(dontLookBackInAngerTest, STest, STest(R"((?<!in Anger)\w+)")) {
  const char text[] = "Oasis";
  fixture.search(text, text + 5, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(sixteenDigitCreditCardNumberSearch, STest, STest(R"((?<!\d)\d{16}(?!\d))")) {
  const char text[] = "4012888888881881 41111111111111114 411111111111111 4111111111111111 510510510510510051051051051051005105105105105100 5105105105105100";
  fixture.search(text, text + 133, 0);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(51, 67, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(117, 133, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(forwardLookingSearch, STest, STest(R"(pro(?=active))")) {
  const char text[] = "professor pro bono proactive prolix";
  fixture.search(text, text + 35, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(crossedEyesSearch, STest, STest(R"((?=ii)i(?<=ii))")) {
  const char text[] = "xixixiiixiiiiixii";
  fixture.search(text, text + 17, 0);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(killPrecedence1Search, STest, STest(R"(a\Kb|c)")) {
  const char text[] = "abc";
  fixture.search(text, text + 3, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(killPrecedence2Search, STest, STest(R"(a\K(b|c))")) {
  const char text[] = "abc";
  fixture.search(text, text + 3, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

*/
