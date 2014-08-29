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

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(startsWithTest, STest, STest({"ab..ef", "c[a-z][a-z]", "[aA][bc][bc]"})) {
  const char text[] = "abcdefghijklmnop";
  fixture.startsWith(text, text + 16, 0);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 2), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(startsWithShortTest, STest, STest({"a+"})) {
  const char text[] = "a";
  fixture.startsWith(text, text + 1, 0);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}
