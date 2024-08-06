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

#include <iostream>
#include <random>

#include "basic.h"
#include "rangeset.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("rangeSetEqualsTest") {
  RangeSet<uint32_t,256> r, s, u{{0,1}};
  // reflexive
  REQUIRE(s == s);
  REQUIRE(r == r);
  REQUIRE(u == u);

  // symmetric
  REQUIRE(r == s);
  REQUIRE(s == r);
  REQUIRE(r != u);
  REQUIRE(u != r);
  REQUIRE(s != u);
  REQUIRE(u != s);
}

template <typename BType, typename RType>
void bitset_equivalence_tester(const BType& b, const RType& r) {
  REQUIRE(b.any() == r.any());
  REQUIRE(b.all() == r.all());
  REQUIRE(b.none() == r.none());
  REQUIRE(b.size() == r.size());
  REQUIRE(b.count() == r.count());

  for (uint32_t i = 0; i < b.size(); ++i) {
    REQUIRE(b[i] == r[i]);
  }
  REQUIRE(r == b);
}

TEST_CASE("rangeSetNoneTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;

  bitset_equivalence_tester(b, r);

  REQUIRE(r.begin() == r.end());
  REQUIRE(r.cbegin() == r.cend());
  REQUIRE(r.rbegin() == r.rend());
  REQUIRE(r.crbegin() == r.crend());
}

TEST_CASE("rangeSetSomeTest") {
  RangeSet<uint32_t,256> r{{1,3}};

  std::bitset<256> b;
  b[1] = b[2] = true;

  bitset_equivalence_tester(b, r);

  REQUIRE(1 == r.end() - r.begin());
  REQUIRE(1 == r.cend() - r.cbegin());
  REQUIRE(1 == r.rend() - r.rbegin());
  REQUIRE(1 == r.crend() - r.crbegin());
}

TEST_CASE("rangeSetAllTest") {
  RangeSet<uint32_t,256> r{{0,256}};

  std::bitset<256> b;
  b.set();

  bitset_equivalence_tester(b, r);

  REQUIRE(1 == r.end() - r.begin());
  REQUIRE(1 == r.cend() - r.cbegin());
  REQUIRE(1 == r.rend() - r.rbegin());
  REQUIRE(1 == r.crend() - r.crbegin());
}

TEST_CASE("rangeSetSetResetTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;

  REQUIRE(r == b);
  b.set();
  r.set();
  REQUIRE(r == b);
  b.reset();
  r.reset();
  REQUIRE(r == b);
}

TEST_CASE("rangeSetFlipAllNoneTest") {
  RangeSet<uint32_t,256> r;
  REQUIRE(!r.all());
  REQUIRE(r.none());
  r.flip();
  REQUIRE(r.all());
  REQUIRE(!r.none());
  r.flip();
  REQUIRE(!r.all());
  REQUIRE(r.none());
}

TEST_CASE("rangeSetFlipIntermediateTest") {
  RangeSet<uint32_t,256> r{{1,13},{34,128}};
  std::bitset<256> b;
  for (uint32_t i = 1; i < 13; ++i) { b[i] = true; }
  for (uint32_t i = 34; i < 128; ++i) { b[i] = true; }

  REQUIRE(r == b);
  b.flip();
  r.flip();
  REQUIRE(r == b);
}

TEST_CASE("rangeSetCopyConstructorTest") {
  RangeSet<uint32_t,256> r{{87,93},{134,245},{250,256}};
  RangeSet<uint32_t,256> s(r);
  REQUIRE(r == s);
}

TEST_CASE("rangeSetBitsetConstructorTest") {
  std::bitset<256> b;
  for (uint32_t i = 0; i < 32; ++i) { b[i] = true; }
  b[38] = b[254] = b[255] = true;
  RangeSet<uint32_t,256> r(b);
  REQUIRE(r == b);
}

TEST_CASE("rangeSetInsertDisjointTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);

  for (uint32_t i = 0; i < 5; ++i) { b[i] = true; }
  r.insert(0, 5);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());

  for (uint32_t i = 27; i < 42; ++i) { b[i] = true; }
  r.insert(27, 42);
  REQUIRE(r == b);
  REQUIRE(2 == r.end() - r.begin());

  for (uint32_t i = 44; i < 48; ++i) { b[i] = true; }
  r.insert(44, 48);
  REQUIRE(r == b);
  REQUIRE(3 == r.end() - r.begin());

  for (uint32_t i = 10; i < 13; ++i) { b[i] = true; }
  r.insert(10, 13);
  REQUIRE(r == b);
  REQUIRE(4 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertMeetLeftTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);

  for (uint32_t i = 20; i < 25; ++i) { b[i] = true; }
  r.insert(20, 25);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertMeetRightTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());

  for (uint32_t i = 20; i < 25; ++i) { b[i] = true; }
  r.insert(20, 25);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertSuperTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());

  for (uint32_t i = 10; i < 25; ++i) { b[i] = true; }
  r.insert(10, 25);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertSubTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);

  for (uint32_t i = 10; i < 25; ++i) { b[i] = true; }
  r.insert(10, 25);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertEmpty") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);
  REQUIRE(0 == r.end() - r.begin());

  r.insert(42, 42);
  std::cerr << r << std::endl;
  REQUIRE(r == b);
  REQUIRE(0 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertOutOfOrderTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  REQUIRE(r == b);

  b[0] = r[0] = true;
  REQUIRE(r == b);
  REQUIRE(1 == r.end() - r.begin());

  b[255] = r[255] = true;
  REQUIRE(r == b);
  REQUIRE(2 == r.end() - r.begin());

  b['A'] = r['A'] = true;
  REQUIRE(r == b);
  REQUIRE(3 == r.end() - r.begin());
}

TEST_CASE("rangeSetInsertRandomTest") {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;

  std::default_random_engine g;
  std::uniform_int_distribution<uint32_t> u(0,256);

  std::vector<uint32_t> addends;

  for (uint32_t i = 0; i < 1000; ++i) {
    r.reset();
    b.reset();
    REQUIRE(r == b);

    addends.clear();

    for (uint32_t j = 0; j < 10; ++j) {
      const std::pair<uint32_t,uint32_t> range(std::minmax(u(g), u(g)));
      for (uint32_t k = range.first; k < range.second; ++k) { b[k] = true; }
      r.insert(range);
      addends.insert(addends.end(), { range.first, range.second });

      if (r != b) {
        std::cerr << "addends: ";
        std::copy(addends.begin(), addends.end(),
                  std::ostream_iterator<uint32_t>(std::cerr, " "));
        std::cerr << '\n'
                  << "bitset: " << b << '\n'
                  << "rangeset: " << r << std::endl;
        REQUIRE(false);
      }
    }
  }
}

TEST_CASE("rangeSetReferenceAssignmentTest") {
  RangeSet<uint32_t,256> r;
  r['a'] = r['b'] = r['c'] = true;

  std::bitset<256> b;
  b['a'] = b['b'] = b['c'] = true;

  REQUIRE(r == b);
}

TEST_CASE("rangeSetIntersectionAssignmentEmptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b(100, 200);
  REQUIRE((a &= b).none());
}

TEST_CASE("rangeSetIntersectionAssignmentNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 101), b(100, 200), c(100);
  REQUIRE(c == (a &= b));
}

TEST_CASE("rangeSetIntersectionAssignmentSelfTest") {
  RangeSet<uint32_t,256> a(0, 101), b(0, 101);
  REQUIRE(b == (a &= a));
}

TEST_CASE("rangeSetIntersectionEmptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b(100, 200);
  REQUIRE((a & b).none());
}

TEST_CASE("rangeSetIntersectionNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 101), b(100, 200), c(100);
  REQUIRE(c == (a & b));
}

TEST_CASE("rangeSetIntersectionSelfTest") {
  RangeSet<uint32_t,256> a(0, 101);
  REQUIRE(a == (a & a));
}

TEST_CASE("rangeSetUnionAssignmentEmptyTest") {
  RangeSet<uint32_t,256> a, b;
  REQUIRE((a |= b).none());
}

TEST_CASE("rangeSetUnionAssignmentNonemptyDisjointTest") {
  RangeSet<uint32_t,256> a(0, 10), b(20, 30), c{{0, 10}, {20, 30}};
  REQUIRE(c == (a |= b));
}

TEST_CASE("rangeSetUnionAssignmentNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 10), b(8, 20), c(0, 20);
  REQUIRE(c == (a |= b));
}

TEST_CASE("rangeSetUnionAssignmentSelfTest") {
  RangeSet<uint32_t,256> a(0, 101), b(0, 101);
  REQUIRE(b == (a |= a));
}

TEST_CASE("rangeSetUnionEmptyTest") {
  RangeSet<uint32_t,256> a, b;
  REQUIRE((a | b).none());
}

TEST_CASE("rangeSetUnionNonemptyDisjointTest") {
  RangeSet<uint32_t,256> a(0, 10), b(20, 30), c{{0, 10},{20, 30}};
  REQUIRE(c == (a | b));
}

TEST_CASE("rangeSetUnionNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 10), b(8, 20), c(0, 20);
  REQUIRE(c == (a | b));
}

TEST_CASE("rangeSetUnionSelfTest") {
  RangeSet<uint32_t,256> a(0, 101);
  REQUIRE(a == (a | a));
}

TEST_CASE("rangeSetDifferenceAssignmentEmptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b(0, 200);
  REQUIRE((a -= b).none());
}

TEST_CASE("rangeSetDifferenceAssignmentNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b{{0, 10}, {50,200}}, c(10, 50);
  REQUIRE(c == (a -= b));
}

TEST_CASE("rangeSetDifferenceAssignmentSelfTest") {
  RangeSet<uint32_t,256> a(0, 101);
  REQUIRE((a -= a).none());
}

TEST_CASE("rangeSetDifferenceEmptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b(0, 200);
  REQUIRE((a - b).none());
}

TEST_CASE("rangeSetDifferenceNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 101), b(100, 200), c(0, 100);
  REQUIRE(c == a - b);
}

TEST_CASE("rangeSetDifferenceSelfTest") {
  RangeSet<uint32_t,256> a(0, 101);
  REQUIRE((a - a).none());
}

TEST_CASE("rangeSetSymmetricDifferenceAssignmentEmptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b(0, 100);
  REQUIRE((a ^= b).none());
}

TEST_CASE("rangeSetSymmetricDifferenceAssignmentNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b{{0,10}, {50,200}}, c{{10,50}, {100,200}};
  REQUIRE(c == (a ^= b));
}

TEST_CASE("rangeSetSymmetricDifferenceAssignmentSelfTest") {
  RangeSet<uint32_t,256> a(0, 101);
  REQUIRE((a ^= a).none());
}

TEST_CASE("rangeSetSymmetricDifferenceEmptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b(0, 100);
  REQUIRE((a ^ b).none());
}

TEST_CASE("rangeSetSymmetricDifferenceNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 100), b{{0,10}, {50,200}}, c{{10,50}, {100,200}};
  REQUIRE(c == (a ^ b));
}

TEST_CASE("rangeSetSymmetricDifferenceSelfTest") {
  RangeSet<uint32_t,256> a(0, 101);
  REQUIRE((a ^ a).none());
}

TEST_CASE("rangeSetComplementNonemptyTest") {
  RangeSet<uint32_t,256> a(0, 128), b(128, 256);
  REQUIRE(b == ~a);
}

TEST_CASE("rangeSetComplementEmptyTest") {
  RangeSet<uint32_t,256> a(0, 256);
  REQUIRE((~a).none());
}

TEST_CASE("rangeSetComplementComplementTest") {
  RangeSet<uint32_t,256> a{{0, 5}, {42,43}};
  REQUIRE(a == ~~a);
}

TEST_CASE("rangeSetDeMorganTest") {
  RangeSet<uint32_t,256> a{{0, 5}, {42, 43}}, b{{4, 7},{28,96}};

  REQUIRE((a & b) == ~(~a | ~b));
  REQUIRE((a | b) == ~(~a & ~b));
  REQUIRE((~a & ~b) == ~(a | b));
  REQUIRE((~a | ~b) == ~(a & b));
}
