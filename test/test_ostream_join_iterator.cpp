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

#include "ostream_join_iterator.h"

#include <algorithm>
#include <sstream>

SCOPE_TEST(joinEmpty) {
  const int *a = 0;
  std::stringstream ss;
  std::copy(a, a, ostream_join_iterator<int>(ss, ", "));
  SCOPE_ASSERT_EQUAL("", ss.str());
}

SCOPE_TEST(joinSingleton) {
  const int a[] = { 1 };
  std::stringstream ss;
  std::copy(a, a + 1, ostream_join_iterator<int>(ss, ", "));
  SCOPE_ASSERT_EQUAL("1", ss.str());
}

SCOPE_TEST(joinMultiple) {
  const int a[] = { 1, 2, 3 };
  std::stringstream ss;
  std::copy(a, a + 3, ostream_join_iterator<int>(ss, ", "));
  SCOPE_ASSERT_EQUAL("1, 2, 3", ss.str());
}
