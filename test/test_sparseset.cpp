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

#include "sparseset.h"

TEST_CASE("basicSparseTest") {
  SparseSet s(5);
  REQUIRE(0u == s.size());
  for (uint32_t i = 0; i < 5; ++i) {
    REQUIRE(!s.find(i));
  }
  s.insert(3);
  REQUIRE(1u == s.size());
  REQUIRE(s.find(3));
  REQUIRE(!s.find(0));
  REQUIRE(!s.find(1));
  REQUIRE(!s.find(2));
  REQUIRE(!s.find(4));
}

TEST_CASE("sparseClear") {
  SparseSet s(5);
  REQUIRE(0u == s.size());
  s.insert(4);
  s.insert(2);
  REQUIRE(2u == s.size());
  s.clear();
  REQUIRE(0u == s.size());
  for (uint32_t i = 0; i < 5; ++i) {
    REQUIRE(!s.find(i));
  }
}
