#include <catch2/catch_test_macros.hpp>

#include <cstring>

#include "pattern_map.h"

TEST_CASE("testPatternMapCopyCtor") {
  PatternMap p1(3);
  p1.addPattern("foo", "bar", 0);
  p1.addPattern(".+", "UTF-8", 1);
  p1.addPattern("a|b|c", "ASCII,ISO-8859", 2);

  PatternMap p2(p1);

  REQUIRE(p1 == p2);
}

TEST_CASE("testPatternMapSerialization") {
  PatternMap p1(3);
  p1.addPattern("foo", "bar", 0);
  p1.addPattern(".+", "UTF-8", 1);
  p1.addPattern("a|b|c", "ASCII,ISO-8859", 2);
  const size_t pcount = p1.count();

  std::vector<char> buf = p1.marshall();
  REQUIRE(buf.size() == p1.bufSize());

  // first copy
  std::unique_ptr<PatternMap> p2 = PatternMap::unmarshall(buf.data(), buf.size());
  REQUIRE(p2);
  REQUIRE(p1 == *p2);

  // second copy, shares buffer with first copy
  std::unique_ptr<PatternMap> p3 = PatternMap::unmarshall(buf.data(), buf.size());
  REQUIRE(p3);
  REQUIRE(p1 == *p3);

  // p2 and p3 should point to the same strings
  for (size_t i = 0; i < pcount; ++i) {
    REQUIRE(!std::memcmp(&(*p2)[i], &(*p3)[i], sizeof(LG_PatternInfo)));
  }

  // p1 and p2 should NOT point to the same strings
  for (size_t i = 0; i < pcount; ++i) {
    REQUIRE(std::memcmp(&p1[i], &(*p2)[i], sizeof(LG_PatternInfo)));
  }

  // p1 and p3 should NOT point to the same strings
  // we should already know this due to the transitivity of equality, but
  // it's only three items and wouldn't it be interesting if equality stopped
  // being transitive
  for (size_t i = 0; i < pcount; ++i) {
    REQUIRE(std::memcmp(&p1[i], &(*p3)[i], sizeof(LG_PatternInfo)));
  }
}
