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
#include "byteset.h"

#include <iostream>

TEST_CASE("byteSetSizeTest") {
  // Our usage of memcmp assumes that ByteSet is laid out as a byte[32].
  REQUIRE(32u == sizeof(ByteSet));
}

TEST_CASE("byteSetDWordComparisionTest") {
  // This tests that we are getting comparision per dword, instead of a
  // lexicographical order. It's not essential that this be the case, but
  // we want to know if there's an unexpected change.
  ByteSet a(0), b(1);
  REQUIRE(a < b);
}

TEST_CASE("fastByteSetOrderTest") {
  REQUIRE(ByteSet(0xFE) < ByteSet(0xFF));

  ByteSet none, test(1), all;
  all.set();

  do {
    REQUIRE(none < test);
    REQUIRE(!(test < none));
    REQUIRE(test < all);
    REQUIRE(!(all < test));
    REQUIRE(!(test < test));
  } while ((test <<= 1).any());
}

TEST_CASE("byteSetRangeSetTest") {
  ByteSet a, b;

  // set true ranges on false bits
  for (uint32_t i = 0; i <= 256; ++i) {
    for (uint32_t j = i; j <= 256; ++j) {
      // do a range set
      a.reset();
      a.set(i, j, true);

      // do a standard, one-at-a-time set
      b.reset();
      for (uint32_t k = i; k < j; ++k) {
        b.set(k, true);
      }

      REQUIRE(b == a);
    }
  }

  // set false ranges on true bits
  for (uint32_t i = 0; i <= 256; ++i) {
    for (uint32_t j = i; j <= 256; ++j) {
      // do a range set
      a.set();
      a.set(i, j, false);

      // do a standard, one-at-a-time set
      b.set();
      for (uint32_t k = i; k < j; ++k) {
        b.set(k, false);
      }

      REQUIRE(b == a);
    }
  }
}

TEST_CASE("byteSetDifferenceAssignmentEmptyTest") {
  ByteSet a{0,5,17}, b{0,5,17,42};
  REQUIRE((a -= b).none());
}

TEST_CASE("byteSetDifferenceAssignmentNonemptyTest") {
  ByteSet a{0,5,17}, b{0,5}, c{17};
  a -= b;
  REQUIRE(c == a);
}

TEST_CASE("byteSetDifferenceAssignmentSelfTest") {
  ByteSet a{0,5,17};
  REQUIRE((a -= a).none());
}

TEST_CASE("byteSetDifferenceEmptyTest") {
  ByteSet a{0,5,17}, b{0,5,17,42};
  REQUIRE((a - b).none());
}

TEST_CASE("byteSetDifferenceNonemptyTest") {
  ByteSet a{0,5,17}, b{0,5}, c{17};
  REQUIRE(c == a - b);
}

TEST_CASE("byteSetDifferenceSelfTest") {
  ByteSet a{0,5,17};
  REQUIRE((a - a).none());
}
