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

#include "encoders/ascii.h"

TEST_CASE("testASCII") {
  ASCII enc;
  REQUIRE(1u == enc.maxByteLength());

  byte buf[1];
  uint32_t len;

  // too low
  REQUIRE(0u == enc.write(-1, buf));

  // just right
  for (uint32_t i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    REQUIRE(1u == len);
    REQUIRE(i == buf[0]);
  }

  // too high
  REQUIRE(0u == enc.write(0x80, buf));
}
