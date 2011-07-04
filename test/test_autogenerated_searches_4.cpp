#include <scope/test.h>

#include "nfabuilder.h"
#include "parsetree.h"

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoPatternTest1500, STest, STest("a|bcb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1501, STest, STest("a|bac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 3, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1502, STest, STest("a|abc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1503, STest, STest("a|bbc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1504, STest, STest("a|bcc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1505, STest, STest("a|bc.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 3, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1506, STest, STest("a|aa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1507, STest, STest("a|aa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1508, STest, STest("a|aa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1509, STest, STest("a|aa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1510, STest, STest("a|aa*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1511, STest, STest("a|aa??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1512, STest, STest("a|aa{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1513, STest, STest("a|aa{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1514, STest, STest("a|aa{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1515, STest, STest("a|aa{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1516, STest, STest("a|aa{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1517, STest, STest("a|aa{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1518, STest, STest("a|aa{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1519, STest, STest("a|aa{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1520, STest, STest("a|ba+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1521, STest, STest("a|ba*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(15, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1522, STest, STest("a|ba?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1523, STest, STest("a|ba+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1524, STest, STest("a|ba*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1525, STest, STest("a|ba??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1526, STest, STest("a|ba{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1527, STest, STest("a|ba{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1528, STest, STest("a|ba{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1529, STest, STest("a|ba{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1530, STest, STest("a|ba{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1531, STest, STest("a|ba{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1532, STest, STest("a|ba{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1533, STest, STest("a|ba{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1534, STest, STest("a|ab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1535, STest, STest("a|ab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1536, STest, STest("a|ab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1537, STest, STest("a|ab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1538, STest, STest("a|ab*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1539, STest, STest("a|ab??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1540, STest, STest("a|ab{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1541, STest, STest("a|ab{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1542, STest, STest("a|ab{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1543, STest, STest("a|ab{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1544, STest, STest("a|ab{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1545, STest, STest("a|ab{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1546, STest, STest("a|ab{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1547, STest, STest("a|ab{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1548, STest, STest("a|bb+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1549, STest, STest("a|bb*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1550, STest, STest("a|bb?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1551, STest, STest("a|bb+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1552, STest, STest("a|bb*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1553, STest, STest("a|bb??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1554, STest, STest("a|bb{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1555, STest, STest("a|bb{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1556, STest, STest("a|bb{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1557, STest, STest("a|bb{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1558, STest, STest("a|bb{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1559, STest, STest("a|bb{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1560, STest, STest("a|bb{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1561, STest, STest("a|bb{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1562, STest, STest("a|bc+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 4, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1563, STest, STest("a|bc*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 4, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1564, STest, STest("a|bc?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1565, STest, STest("a|bc+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1566, STest, STest("a|bc*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1567, STest, STest("a|bc??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1568, STest, STest("a|bc{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1569, STest, STest("a|bc{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1570, STest, STest("a|bc{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 3, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1571, STest, STest("a|bc{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 4, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1572, STest, STest("a|bc{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1573, STest, STest("a|bc{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1574, STest, STest("a|bc{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1575, STest, STest("a|bc{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 3, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1576, STest, STest("a|aa|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1577, STest, STest("a|ba|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1578, STest, STest("a|ab|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1579, STest, STest("a|bb|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1580, STest, STest("a|bc|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1581, STest, STest("a|aa|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1582, STest, STest("a|ba|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1583, STest, STest("a|ab|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1584, STest, STest("a|bb|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1585, STest, STest("a|bc|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1586, STest, STest("a|ba|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1587, STest, STest("a|ab|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1588, STest, STest("a|bb|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1589, STest, STest("a|bc|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1590, STest, STest("a|bc|.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1591, STest, STest("a|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest1592) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1593) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1594, STest, STest("a|a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest1595) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1596) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1597) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1598, STest, STest("a|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1599, STest, STest("a|a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1600, STest, STest("a|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest1601) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1602, STest, STest("a|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1603, STest, STest("a|a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1604, STest, STest("a|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1605, STest, STest("a|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest1606) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1607) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1608, STest, STest("a|b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1609) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1610) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1611) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1612, STest, STest("a|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1613, STest, STest("a|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1614, STest, STest("a|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_TEST(autoPatternTest1615) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1616, STest, STest("a|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1617, STest, STest("a|b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1618, STest, STest("a|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1619, STest, STest("a|a|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1620, STest, STest("a|b|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1621, STest, STest("a|a|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1622, STest, STest("a|b|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1623, STest, STest("a|b|(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1624, STest, STest("a|a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1625, STest, STest("a|b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1626, STest, STest("a|a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1627, STest, STest("a|b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1628, STest, STest("a|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1629, STest, STest("a|a|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1630, STest, STest("a|b|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1631, STest, STest("a|a|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1632, STest, STest("a|b|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1633, STest, STest("a|b|ca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1634, STest, STest("a|a|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1635, STest, STest("a|b|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1636, STest, STest("a|a|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1637, STest, STest("a|b|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1638, STest, STest("a|b|cb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1639, STest, STest("a|b|ac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1640, STest, STest("a|a|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1641, STest, STest("a|b|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1642, STest, STest("a|b|cc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1643, STest, STest("a|b|c.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1644, STest, STest("a|a|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest1645) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1646) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1647, STest, STest("a|a|a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest1648) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1649) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1650) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1651, STest, STest("a|a|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1652, STest, STest("a|a|a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1653, STest, STest("a|a|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest1654) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1655, STest, STest("a|a|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1656, STest, STest("a|a|a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1657, STest, STest("a|a|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1658, STest, STest("a|b|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1659) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1660) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1661, STest, STest("a|b|a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1662) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1663) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1664) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1665, STest, STest("a|b|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1666, STest, STest("a|b|a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1667, STest, STest("a|b|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1668) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1669, STest, STest("a|b|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1670, STest, STest("a|b|a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1671, STest, STest("a|b|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1672, STest, STest("a|a|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest1673) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1674) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1675, STest, STest("a|a|b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1676) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1677) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1678) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1679, STest, STest("a|a|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1680, STest, STest("a|a|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1681, STest, STest("a|a|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_TEST(autoPatternTest1682) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1683, STest, STest("a|a|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1684, STest, STest("a|a|b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1685, STest, STest("a|a|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1686, STest, STest("a|b|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1687) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1688) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1689, STest, STest("a|b|b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1690) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1691) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1692) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1693, STest, STest("a|b|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1694, STest, STest("a|b|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1695, STest, STest("a|b|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_TEST(autoPatternTest1696) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1697, STest, STest("a|b|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1698, STest, STest("a|b|b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1699, STest, STest("a|b|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1700, STest, STest("a|b|c+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 3, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
}

SCOPE_TEST(autoPatternTest1701) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1702) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1703, STest, STest("a|b|c+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_TEST(autoPatternTest1704) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1705) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1706) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1707, STest, STest("a|b|c{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1708, STest, STest("a|b|c{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1709, STest, STest("a|b|c{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 3, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_TEST(autoPatternTest1710) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1711, STest, STest("a|b|c{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1712, STest, STest("a|b|c{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1713, STest, STest("a|b|c{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1714, STest, STest("a|a|a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1715, STest, STest("a|b|a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1716, STest, STest("a|a|b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1717, STest, STest("a|b|b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1718, STest, STest("a|b|c|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1719, STest, STest("a|a|a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1720, STest, STest("a|b|a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1721, STest, STest("a|a|b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1722, STest, STest("a|b|b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1723, STest, STest("a|b|c|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1724, STest, STest("a|b|a|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1725, STest, STest("a|a|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1726, STest, STest("a|b|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1727, STest, STest("a|b|c|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1728, STest, STest("a|b|c|.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
}

