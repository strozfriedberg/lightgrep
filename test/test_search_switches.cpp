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

#include <algorithm>
#include <cstring>

#include "stest.h"

SCOPE_FIXTURE_CTOR(ai_switches_Search, STest, STest({
  {"(?i)x((?-i)x)x", false, false, false, "UTF-8"},
  {"(?i)k(?-i)k(?ai)k+", false, false, false, "UTF-8"},
  {"(?i)k(?-i)k(?i)k+", false, false, false, "UTF-8"}
})) {
  const char text[] = "XXX XxX xxx Kkkk Kk\xE2\x84\xAAK";
  fixture.search(text, text + 23, 0);
  SCOPE_ASSERT_EQUAL(5u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 11, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 16, 2), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 16, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 23, 2), fixture.Hits[4]);
}
