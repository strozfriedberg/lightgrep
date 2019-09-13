#include <scope/test.h>

#include <cstring>

#include "pattern_map.h"

SCOPE_TEST(testPatternMapSerialization) {
  PatternMap p1(3);
  p1.addPattern("foo", "bar", 0);
  p1.addPattern(".+", "UTF-8", 1);
  p1.addPattern("a|b|c", "ASCII,ISO-8859", 2);

  std::vector<char> buf = p1.marshall();
  SCOPE_ASSERT_EQUAL(buf.size(), p1.bufSize());

  std::unique_ptr<PatternMap> p2 = PatternMap::unmarshall(buf.data(), buf.size());
  SCOPE_ASSERT(p2);
  SCOPE_ASSERT_EQUAL(p1, *p2);
}

SCOPE_TEST(testPatternMapSerializationShared) {
  PatternMap p1(3);
  p1.addPattern("foo", "bar", 0);
  p1.addPattern(".+", "UTF-8", 1);
  p1.addPattern("a|b|c", "ASCII,ISO-8859", 2);

  std::vector<char> buf = p1.marshall();
  SCOPE_ASSERT_EQUAL(buf.size(), p1.bufSize());

  // first copy
  std::unique_ptr<PatternMap> p2 = PatternMap::unmarshall_shared(buf.data(), buf.size());
  SCOPE_ASSERT(p2);
  SCOPE_ASSERT_EQUAL(p1, *p2);

  // second copy, shares buffer with first copy
  std::unique_ptr<PatternMap> p3 = PatternMap::unmarshall_shared(buf.data(), buf.size());
  SCOPE_ASSERT(p3);
  SCOPE_ASSERT_EQUAL(p1, *p3);

  // p2 and p3 should point to the same strings
  SCOPE_ASSERT(!std::memcmp(
    p2->Patterns.data(),
    p3->Patterns.data(),
    p2->Patterns.size()*sizeof(decltype(p2->Patterns)::value_type))
  );

  // p1 and p2 should NOT point to the same strings
  SCOPE_ASSERT(std::memcmp(
    p1.Patterns.data(),
    p2->Patterns.data(),
    p1.Patterns.size()*sizeof(decltype(p1.Patterns)::value_type))
  );
}
