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

#include <iostream>
#include <random>

#include "basic.h"
#include "rangeset.h"
#include "pair_out.h"

#include <scope/test.h>

SCOPE_TEST(rangeSetEqualsTest) {
  RangeSet<uint32_t,256> r, s, u{{0,1}};
  // reflexive
  SCOPE_ASSERT(s == s);
  SCOPE_ASSERT(r == r);
  SCOPE_ASSERT(u == u);

  // symmetric
  SCOPE_ASSERT(r == s);
  SCOPE_ASSERT(s == r);
  SCOPE_ASSERT(r != u);
  SCOPE_ASSERT(u != r);
  SCOPE_ASSERT(s != u);
  SCOPE_ASSERT(u != s);
}

template <typename BType, typename RType>
void bitset_equivalence_tester(const BType& b, const RType& r) {
  SCOPE_ASSERT_EQUAL(b.any(), r.any());
  SCOPE_ASSERT_EQUAL(b.all(), r.all());
  SCOPE_ASSERT_EQUAL(b.none(), r.none());
  SCOPE_ASSERT_EQUAL(b.size(), r.size());
  SCOPE_ASSERT_EQUAL(b.count(), r.count());

  for (uint32_t i = 0; i < b.size(); ++i) {
    SCOPE_ASSERT_EQUAL(b[i], r[i]);
  }

  // SCOPE_ASSERT(r == b);
  SCOPE_ASSERT(r == b);
}

SCOPE_TEST(rangeSetNoneTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;

  bitset_equivalence_tester(b, r);

  SCOPE_ASSERT(r.begin() == r.end());
  SCOPE_ASSERT(r.cbegin() == r.cend());
  SCOPE_ASSERT(r.rbegin() == r.rend());
  SCOPE_ASSERT(r.crbegin() == r.crend());
}

SCOPE_TEST(rangeSetSomeTest) {
  RangeSet<uint32_t,256> r{{1,3}};

  std::bitset<256> b;
  b[1] = b[2] = true;

  bitset_equivalence_tester(b, r);

  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());
  SCOPE_ASSERT_EQUAL(1, r.cend() - r.cbegin());
  SCOPE_ASSERT_EQUAL(1, r.rend() - r.rbegin());
  SCOPE_ASSERT_EQUAL(1, r.crend() - r.crbegin());
}

SCOPE_TEST(rangeSetAllTest) {
  RangeSet<uint32_t,256> r{{0,256}};

  std::bitset<256> b;
  b.set();

  bitset_equivalence_tester(b, r);

  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());
  SCOPE_ASSERT_EQUAL(1, r.cend() - r.cbegin());
  SCOPE_ASSERT_EQUAL(1, r.rend() - r.rbegin());
  SCOPE_ASSERT_EQUAL(1, r.crend() - r.crbegin());
}

SCOPE_TEST(rangeSetSetResetTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;

  SCOPE_ASSERT(r == b);
  b.set();
  r.set();
  SCOPE_ASSERT(r == b);
  b.reset();
  r.reset();
  SCOPE_ASSERT(r == b);
}

SCOPE_TEST(rangeSetFlipAllNoneTest) {
  RangeSet<uint32_t,256> r;
  SCOPE_ASSERT(!r.all());
  SCOPE_ASSERT(r.none());
  r.flip();
  SCOPE_ASSERT(r.all());
  SCOPE_ASSERT(!r.none());
  r.flip();
  SCOPE_ASSERT(!r.all());
  SCOPE_ASSERT(r.none());
}

SCOPE_TEST(rangeSetFlipIntermediateTest) {
  RangeSet<uint32_t,256> r{{1,13},{34,128}};
  std::bitset<256> b;
  for (uint32_t i = 1; i < 13; ++i) { b[i] = true; }
  for (uint32_t i = 34; i < 128; ++i) { b[i] = true; }

  SCOPE_ASSERT(r == b);
  b.flip();
  r.flip();
  SCOPE_ASSERT(r == b);
}

SCOPE_TEST(rangeSetCopyConstructorTest) {
  RangeSet<uint32_t,256> r{{87,93},{134,245},{250,256}};
  RangeSet<uint32_t,256> s(r);
  SCOPE_ASSERT(r == s);
}

SCOPE_TEST(rangeSetBitsetConstructorTest) {
  std::bitset<256> b;
  for (uint32_t i = 0; i < 32; ++i) { b[i] = true; }
  b[38] = b[254] = b[255] = true;
  RangeSet<uint32_t,256> r(b);
  SCOPE_ASSERT(r == b);
}

SCOPE_TEST(rangeSetInsertDisjointTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);

  for (uint32_t i = 0; i < 5; ++i) { b[i] = true; }
  r.insert(0, 5);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());

  for (uint32_t i = 27; i < 42; ++i) { b[i] = true; }
  r.insert(27, 42);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  for (uint32_t i = 44; i < 48; ++i) { b[i] = true; }
  r.insert(44, 48);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(3, r.end() - r.begin());

  for (uint32_t i = 10; i < 13; ++i) { b[i] = true; }
  r.insert(10, 13);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(4, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertMeetLeftTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);

  for (uint32_t i = 20; i < 25; ++i) { b[i] = true; }
  r.insert(20, 25);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertMeetRightTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());

  for (uint32_t i = 20; i < 25; ++i) { b[i] = true; }
  r.insert(20, 25);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertSuperTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());

  for (uint32_t i = 10; i < 25; ++i) { b[i] = true; }
  r.insert(10, 25);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertSubTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);

  for (uint32_t i = 10; i < 25; ++i) { b[i] = true; }
  r.insert(10, 25);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());

  for (uint32_t i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertEmpty) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(0, r.end() - r.begin());

  r.insert(42, 42);
  std::cerr << r << std::endl;
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(0, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertOutOfOrderTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(r == b);

  b[0] = r[0] = true;
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(1, r.end() - r.begin());

  b[255] = r[255] = true;
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  b['A'] = r['A'] = true;
  SCOPE_ASSERT(r == b);
  SCOPE_ASSERT_EQUAL(3, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertRandomTest) {
  RangeSet<uint32_t,256> r;
  std::bitset<256> b;

  std::default_random_engine g;
  std::uniform_int_distribution<uint32_t> u(0,256);

  std::vector<uint32_t> addends;

  for (uint32_t i = 0; i < 1000; ++i) {
    r.reset();
    b.reset();
    SCOPE_ASSERT(r == b);

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
        SCOPE_ASSERT(false);
      }
    }
  }
}

SCOPE_TEST(rangeSetReferenceAssignmentTest) {
  RangeSet<uint32_t,256> r;
  r['a'] = r['b'] = r['c'] = true;

  std::bitset<256> b;
  b['a'] = b['b'] = b['c'] = true;

  SCOPE_ASSERT(r == b);
}

SCOPE_TEST(rangeSetIntersectionAssignmentEmptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b(100, 200);
  SCOPE_ASSERT((a &= b).none());
}

SCOPE_TEST(rangeSetIntersectionAssignmentNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 101), b(100, 200), c(100);
  SCOPE_ASSERT_EQUAL(c, a &= b);
}

SCOPE_TEST(rangeSetIntersectionAssignmentSelfTest) {
  RangeSet<uint32_t,256> a(0, 101), b(0, 101);
  SCOPE_ASSERT_EQUAL(b, a &= a);
}

SCOPE_TEST(rangeSetIntersectionEmptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b(100, 200);
  SCOPE_ASSERT((a & b).none());
}

SCOPE_TEST(rangeSetIntersectionNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 101), b(100, 200), c(100);
  SCOPE_ASSERT_EQUAL(c, a & b);
}

SCOPE_TEST(rangeSetIntersectionSelfTest) {
  RangeSet<uint32_t,256> a(0, 101);
  SCOPE_ASSERT_EQUAL(a, a & a);
}

SCOPE_TEST(rangeSetUnionAssignmentEmptyTest) {
  RangeSet<uint32_t,256> a, b;
  SCOPE_ASSERT((a |= b).none());
}

SCOPE_TEST(rangeSetUnionAssignmentNonemptyDisjointTest) {
  RangeSet<uint32_t,256> a(0, 10), b(20, 30), c{{0, 10}, {20, 30}};
  SCOPE_ASSERT_EQUAL(c, a |= b);
}

SCOPE_TEST(rangeSetUnionAssignmentNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 10), b(8, 20), c(0, 20);
  SCOPE_ASSERT_EQUAL(c, a |= b);
}

SCOPE_TEST(rangeSetUnionAssignmentSelfTest) {
  RangeSet<uint32_t,256> a(0, 101), b(0, 101);
  SCOPE_ASSERT_EQUAL(b, a |= a);
}

SCOPE_TEST(rangeSetUnionEmptyTest) {
  RangeSet<uint32_t,256> a, b;
  SCOPE_ASSERT((a | b).none());
}

SCOPE_TEST(rangeSetUnionNonemptyDisjointTest) {
  RangeSet<uint32_t,256> a(0, 10), b(20, 30), c{{0, 10},{20, 30}};
  SCOPE_ASSERT_EQUAL(c, a | b);
}

SCOPE_TEST(rangeSetUnionNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 10), b(8, 20), c(0, 20);
  SCOPE_ASSERT_EQUAL(c, a | b);
}

SCOPE_TEST(rangeSetUnionSelfTest) {
  RangeSet<uint32_t,256> a(0, 101);
  SCOPE_ASSERT_EQUAL(a, a | a);
}

SCOPE_TEST(rangeSetDifferenceAssignmentEmptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b(0, 200);
  SCOPE_ASSERT((a -= b).none());
}

SCOPE_TEST(rangeSetDifferenceAssignmentNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b{{0, 10}, {50,200}}, c(10, 50);
  SCOPE_ASSERT_EQUAL(c, a -= b);
}

SCOPE_TEST(rangeSetDifferenceAssignmentSelfTest) {
  RangeSet<uint32_t,256> a(0, 101);
  SCOPE_ASSERT((a -= a).none());
}

SCOPE_TEST(rangeSetDifferenceEmptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b(0, 200);
  SCOPE_ASSERT((a - b).none());
}

SCOPE_TEST(rangeSetDifferenceNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 101), b(100, 200), c(0, 100);
  SCOPE_ASSERT_EQUAL(c, a - b);
}

SCOPE_TEST(rangeSetDifferenceSelfTest) {
  RangeSet<uint32_t,256> a(0, 101);
  SCOPE_ASSERT((a - a).none());
}

SCOPE_TEST(rangeSetSymmetricDifferenceAssignmentEmptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b(0, 100);
  SCOPE_ASSERT((a ^= b).none());
}

SCOPE_TEST(rangeSetSymmetricDifferenceAssignmentNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b{{0,10}, {50,200}}, c{{10,50}, {100,200}};
  SCOPE_ASSERT_EQUAL(c, a ^= b);
}

SCOPE_TEST(rangeSetSymmetricDifferenceAssignmentSelfTest) {
  RangeSet<uint32_t,256> a(0, 101);
  SCOPE_ASSERT((a ^= a).none());
}

SCOPE_TEST(rangeSetSymmetricDifferenceEmptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b(0, 100);
  SCOPE_ASSERT((a ^ b).none());
}

SCOPE_TEST(rangeSetSymmetricDifferenceNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 100), b{{0,10}, {50,200}}, c{{10,50}, {100,200}};
  SCOPE_ASSERT_EQUAL(c, a ^ b);
}

SCOPE_TEST(rangeSetSymmetricDifferenceSelfTest) {
  RangeSet<uint32_t,256> a(0, 101);
  SCOPE_ASSERT((a ^ a).none());
}

SCOPE_TEST(rangeSetComplementNonemptyTest) {
  RangeSet<uint32_t,256> a(0, 128), b(128, 256);
  SCOPE_ASSERT_EQUAL(b, ~a);
}

SCOPE_TEST(rangeSetComplementEmptyTest) {
  RangeSet<uint32_t,256> a(0, 256);
  SCOPE_ASSERT((~a).none());
}

SCOPE_TEST(rangeSetComplementComplementTest) {
  RangeSet<uint32_t,256> a{{0, 5}, {42,43}};
  SCOPE_ASSERT_EQUAL(a, ~~a);
}

SCOPE_TEST(rangeSetDeMorganTest) {
  RangeSet<uint32_t,256> a{{0, 5}, {42, 43}}, b{{4, 7},{28,96}};

  SCOPE_ASSERT_EQUAL(a & b, ~(~a | ~b));
  SCOPE_ASSERT_EQUAL(a | b, ~(~a & ~b));
  SCOPE_ASSERT_EQUAL(~a & ~b, ~(a | b));
  SCOPE_ASSERT_EQUAL(~a | ~b, ~(a & b));
}
