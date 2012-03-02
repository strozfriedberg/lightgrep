#include <scope/test.h>

#include <iostream>
#include <random>

#include "basic.h"
#include "rangeset.h"

template <typename T, unsigned long N>
std::ostream& operator<<(std::ostream& o, const RangeSet<T,N>& rs) {
  const typename RangeSet<T,N>::const_iterator end(rs.end());
  for (typename RangeSet<T,N>::const_iterator i(rs.begin()); i != end; ) {
    o << '[' << *i++ << ',';
    o << *i++ << ") ";
  }
  return o;
}

SCOPE_TEST(rangeSetEqualsTest) {
  RangeSet<uint32,256> r, s, u{0,1};
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

template <typename T, unsigned long N>
void bitset_equivalence_tester(const std::bitset<N>& b, RangeSet<T,N>& r) {
  SCOPE_ASSERT_EQUAL(b.any(), r.any());
  SCOPE_ASSERT_EQUAL(b.all(), r.all());
  SCOPE_ASSERT_EQUAL(b.none(), r.none());
  SCOPE_ASSERT_EQUAL(b.size(), r.size());
  SCOPE_ASSERT_EQUAL(b.count(), r.count());

  for (uint32 i = 0; i < N; ++i) {
    SCOPE_ASSERT_EQUAL(b[i], r[i]);
  }

  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT(r == b);
}

SCOPE_TEST(rangeSetNoneTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;

  bitset_equivalence_tester(b, r);

  SCOPE_ASSERT(r.begin() == r.end());
  SCOPE_ASSERT(r.cbegin() == r.cend());
  SCOPE_ASSERT(r.rbegin() == r.rend());
  SCOPE_ASSERT(r.crbegin() == r.crend());
}

SCOPE_TEST(rangeSetSomeTest) {
  RangeSet<uint32,256> r{1,3};

  std::bitset<256> b;
  b[1] = b[2] = true;

  bitset_equivalence_tester(b, r);

  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());
  SCOPE_ASSERT_EQUAL(2, r.cend() - r.cbegin());
  SCOPE_ASSERT_EQUAL(2, r.rend() - r.rbegin());
  SCOPE_ASSERT_EQUAL(2, r.crend() - r.crbegin());
}

SCOPE_TEST(rangeSetAllTest) {
  RangeSet<uint32,256> r{0,256};

  std::bitset<256> b;
  b.set();

  bitset_equivalence_tester(b, r);

  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());
  SCOPE_ASSERT_EQUAL(2, r.cend() - r.cbegin());
  SCOPE_ASSERT_EQUAL(2, r.rend() - r.rbegin());
  SCOPE_ASSERT_EQUAL(2, r.crend() - r.crbegin());
}

SCOPE_TEST(rangeSetSetResetTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;

  SCOPE_ASSERT(b == r);
  b.set();
  r.set();
  SCOPE_ASSERT(b == r);
  b.reset();
  r.reset();
  SCOPE_ASSERT(b == r);
}

SCOPE_TEST(rangeSetFlipAllNoneTest) {
  RangeSet<uint32,256> r;
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
  RangeSet<uint32,256> r{1,13,34,128};
  std::bitset<256> b;
  for (uint32 i = 1; i < 13; ++i) { b[i] = true; }
  for (uint32 i = 34; i < 128; ++i) { b[i] = true; }

  SCOPE_ASSERT(b == r);
  b.flip();
  r.flip();
  SCOPE_ASSERT(b == r);
}

SCOPE_TEST(rangeSetCopyConstructorTest) {
  RangeSet<uint32,256> r{87,93,134,245,250,256};
  RangeSet<uint32,256> s(r);
  SCOPE_ASSERT(r == s);
}

SCOPE_TEST(rangeSetBitsetConstructorTest) {
  std::bitset<256> b;
  for (uint32 i = 0; i < 32; ++i) { b[i] = true; }
  b[38] = b[254] = b[255] = true;
  RangeSet<uint32,256> r(b);
  SCOPE_ASSERT(b == r);
}

SCOPE_TEST(rangeSetInsertDisjointTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(b == r);

  for (uint32 i = 0; i < 5; ++i) { b[i] = true; }
  r.insert(0, 5);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  for (uint32 i = 27; i < 42; ++i) { b[i] = true; }
  r.insert(27, 42);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(4, r.end() - r.begin());

  for (uint32 i = 44; i < 48; ++i) { b[i] = true; }
  r.insert(44, 48);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(6, r.end() - r.begin());

  for (uint32 i = 10; i < 13; ++i) { b[i] = true; }
  r.insert(10, 13);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(8, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertMeetLeftTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(b == r);

  for (uint32 i = 20; i < 25; ++i) { b[i] = true; }
  r.insert(20, 25);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  for (uint32 i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(b == r); 
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertMeetRightTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(b == r);

  for (uint32 i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  for (uint32 i = 20; i < 25; ++i) { b[i] = true; }
  r.insert(20, 25);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertSuperTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(b == r);

  for (uint32 i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  for (uint32 i = 10; i < 25; ++i) { b[i] = true; }
  r.insert(10, 25);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertSubTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(b == r);

  for (uint32 i = 10; i < 25; ++i) { b[i] = true; }
  r.insert(10, 25);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());

  for (uint32 i = 15; i < 20; ++i) { b[i] = true; }
  r.insert(15, 20);
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(2, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertEmpty) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(0, r.end() - r.begin());

  r.insert(42, 42);
  std::cerr << r << std::endl;
  SCOPE_ASSERT(b == r);
  SCOPE_ASSERT_EQUAL(0, r.end() - r.begin());
}

SCOPE_TEST(rangeSetInsertRandomTest) {
  RangeSet<uint32,256> r;
  std::bitset<256> b;

  std::default_random_engine g;
  std::uniform_int_distribution<uint32> u(0,256);

  std::vector<uint32> addends;

  for (uint32 i = 0; i < 1000; ++i) {
    r.reset();
    b.reset();
    SCOPE_ASSERT(b == r);

    addends.clear();

    for (uint32 j = 0; i < 10; ++i) {
      const std::pair<uint32,uint32> range(std::minmax(u(g), u(g)));
      for (uint32 k = range.first; k < range.second; ++k) { b[k] = true; }
      r.insert(range);
      addends.insert(addends.end(), { range.first, range.second });

      if (b != r) {
        std::cerr << "addends: ";
        std::copy(addends.begin(), addends.end(),
                  std::ostream_iterator<uint32>(std::cerr, " "));
        std::cerr << '\n'
                  << "bitset: " << b << '\n'
                  << "rangeset: " << r << std::endl;
        SCOPE_ASSERT(false);
      }
    }
  }
}
