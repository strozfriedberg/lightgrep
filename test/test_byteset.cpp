/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <catch2/catch_test_macros.hpp>

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
