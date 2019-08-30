#include <scope/test.h>

#include "pattern_map.h"

SCOPE_TEST(testPatternMapSerialization) {
  PatternMap p1(3);
  p1.addPattern("foo", "bar", 0);
  p1.addPattern(".+", "UTF-8", 1);
  p1.addPattern("a|b|c", "ASCII,ISO-8859", 2);

  std::vector<char> buf = p1.marshall();

  std::unique_ptr<PatternMap> p2 = PatternMap::unmarshall(buf.data(), buf.size());
  SCOPE_ASSERT(p2);
  SCOPE_ASSERT(p1 == *p2);
}
