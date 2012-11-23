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

#include "sparseset.h"

SCOPE_TEST(basicSparseTest) {
  SparseSet s(5);
  SCOPE_ASSERT_EQUAL(0u, s.size());
  for (uint32_t i = 0; i < 5; ++i) {
    SCOPE_ASSERT(!s.find(i));
  }
  s.insert(3);
  SCOPE_ASSERT_EQUAL(1u, s.size());
  SCOPE_ASSERT(s.find(3));
  SCOPE_ASSERT(!s.find(0));
  SCOPE_ASSERT(!s.find(1));
  SCOPE_ASSERT(!s.find(2));
  SCOPE_ASSERT(!s.find(4));
}

SCOPE_TEST(sparseClear) {
  SparseSet s(5);
  SCOPE_ASSERT_EQUAL(0u, s.size());
  s.insert(4);
  s.insert(2);
  SCOPE_ASSERT_EQUAL(2u, s.size());
  s.clear();
  SCOPE_ASSERT_EQUAL(0u, s.size());
  for (uint32_t i = 0; i < 5; ++i) {
    SCOPE_ASSERT(!s.find(i));
  }
}
