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

#include "basic.h"

TEST_CASE("basicTypeSizes") {
  REQUIRE(1u == sizeof(byte));
  REQUIRE(4u == sizeof(uint32_t));
  REQUIRE(8u == sizeof(uint64_t));
  REQUIRE(8u == sizeof(int64_t));
}
