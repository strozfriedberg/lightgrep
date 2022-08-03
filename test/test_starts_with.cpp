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

#include <catch2/catch_test_macros.hpp>

#include "stest.h"

TEST_CASE("startsWithTest") {
  STest fixture({"ab..ef", "c[a-z][a-z]", "[aA][bc][bc]"});
  fixture.startsWith("abcdefghijklmnop", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 2},
    {0, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("startsWithShortTest") {
  STest fixture({"a+"});
  fixture.startsWith("a", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
