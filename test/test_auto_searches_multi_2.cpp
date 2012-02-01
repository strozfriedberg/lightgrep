#include <algorithm>

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoMultipatternTest250, STest, STest({"a+|b", "a|a|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(35, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[34]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest251, STest, STest({"a*?|(b)", "a+|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest252, STest, STest({"aa|b|a", "aba*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest253, STest, STest({"a??b", "a*?b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest254, STest, STest({"a??a", "a|ba??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest255, STest, STest({"a*|(b)", "aa|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest256, STest, STest({"a*?a|b", "a+|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest257, STest, STest({"a?a*?", "a+?b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest258, STest, STest({"a|a|ab", "a+a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest259, STest, STest({"a??|ab", "a+|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest260, STest, STest({"a*|b|c", "a|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest261, STest, STest({"a+?|a+?", "a|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest262, STest, STest({"a+|b", "a*?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest263, STest, STest({"a+|(b)", "a?a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest264, STest, STest({"a|a|b*", "a?a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest265, STest, STest({"a|b|c|c", "a|aa+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest266, STest, STest({"a?a*?", "a|b|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest267, STest, STest({"a+?|(a)", "a?|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest268, STest, STest({"a|bb|c", "ab*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(31, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[30]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest269, STest, STest({"a+|b|b", "aa|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest270, STest, STest({"a|b|ab", "ab|c??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest271, STest, STest({"a|b|b+?", "a?ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest272, STest, STest({"a??|a|a", "a*(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest273, STest, STest({"a|bc|c", "ab|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest274, STest, STest({"a|b(a)", "a*(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest275, STest, STest({"ab|a|b", "a|bc|."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(41, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[40]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest276, STest, STest({"abc+", "a|b|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest277, STest, STest({"a|aa?", "ab|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest278, STest, STest({"a+?|b+?", "a|a|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest279, STest, STest({"a??|b+", "(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest280, STest, STest({"ab|a+", "aa|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(15, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest281, STest, STest({"aa*", "abba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest282, STest, STest({"a*b?", "ab|ac"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 7, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 15, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 18, 1), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest283, STest, STest({"a*?a+?", "aab?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest284, STest, STest({"a??b*?", "a*|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest285, STest, STest({"a|b|cb", "a|b|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest286, STest, STest({"a+a*?", "aa|bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest287, STest, STest({"a+?|a|a", "a??bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest288, STest, STest({"a*?bb", "(a|a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest289, STest, STest({"a??b??", "a??|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest290, STest, STest({"a+?|a*", "a+bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest291, STest, STest({"a|ab??", "a+b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest292, STest, STest({"((a))", "abac"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest293, STest, STest({"a|b|a+?", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest294, STest, STest({"a|baa", "a?a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest295, STest, STest({"a|aa?", "a*?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest296, STest, STest({"a+?b?", "a??|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest297, STest, STest({"a??ab", "a|bc+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 27, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest298, STest, STest({"a+|b|b", "abb?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest299, STest, STest({"a|b|a??", "a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest300, STest, STest({"a|b|ba", "a+|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest301, STest, STest({"a|aa??", "a+?|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest302, STest, STest({"((a))", "a|b|(c)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest303, STest, STest({"ab(c)", "ab|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest304, STest, STest({"a??|a|a", "a?b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest305, STest, STest({"aba|b", "a|b|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest306, STest, STest({"a+?a", "a?|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest307, STest, STest({"a|b??", "a|b|c|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest308, STest, STest({"a+a+?", "a+?|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest309, STest, STest({"ab|cb", "a|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest310, STest, STest({"a*|a??", "a|b|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest311, STest, STest({"a*b*", "a+b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest312, STest, STest({"a??|b", "a|b|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest313, STest, STest({"a|b|c|.", "a+|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest314, STest, STest({"a|bb|c", "ab+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest315, STest, STest({"a?|a+?", "a??|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest316, STest, STest({"a+|aa", "a|bc*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest317, STest, STest({"a??|a+?", "ab|c*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest318, STest, STest({"a??b??", "a?|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest319, STest, STest({"aa(a)", "a|ab+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest320, STest, STest({"a|bb|b", "a+?|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest321, STest, STest({"a*a+?", "a?b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest322, STest, STest({"a+?|ba", "a+?b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest323, STest, STest({"a|a|a|b", "a??|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest324, STest, STest({"ab|b", "a+|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest325, STest, STest({"a?a", "a*?|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest326, STest, STest({"a+?|b|c", "a*a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(44, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[43]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest327, STest, STest({"aaa?", "(a)+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest328, STest, STest({"a??a+", "a?b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest329, STest, STest({"a*?a*?", "aba|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest330, STest, STest({"a*?|a+?", "a+|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest331, STest, STest({"a+?|a*", "abbc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest332, STest, STest({"a*?bc", "a|baa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest333, STest, STest({"ab|a*", "a?ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest334, STest, STest({"a*?b|a", "a??|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest335, STest, STest({"ab|a?", "a+|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest336, STest, STest({"a*?|b??", "a+?|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest337, STest, STest({"a|b(b)", "aa|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest338, STest, STest({"a+?|(a)", "a|a|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest339, STest, STest({"a|a|ab", "a+?|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest340, STest, STest({"ab|b|c", "a+?bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest341, STest, STest({"a??|a+", "a|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest342, STest, STest({"aa|a*?", "a+b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest343, STest, STest({"a+|a*?", "a|a|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest344, STest, STest({"a+?a?", "a+a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest345, STest, STest({"aa|b*", "a+?|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest346, STest, STest({"a|bb+?", "a|bb|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(24, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest347, STest, STest({"abb", "a+|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest348, STest, STest({"aab", "a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest349, STest, STest({"a?b*?", "a?|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest350, STest, STest({"(a)??", "a|aa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest351, STest, STest({"abc?", "a+?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest352, STest, STest({"aa|a", "a|aa??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest353, STest, STest({"a|b|a|c", "a*b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest354, STest, STest({"abb?", "aab??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest355, STest, STest({"a?|a|a", "a??|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest356, STest, STest({"a+|a*?", "a|b|ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest357, STest, STest({"a??|b+?", "ab|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest358, STest, STest({"a+|a+?", "a*?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest359, STest, STest({"a|abb", "a|b|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest360, STest, STest({"a*|a*", "(aa)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest361, STest, STest({"a|b|a|c", "a|bba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 11, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest362, STest, STest({"aaa|a", "a*|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest363, STest, STest({"a*bb", "aa|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest364, STest, STest({"(a)?", "aba|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest365, STest, STest({"a+|(b)", "(a)*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest366, STest, STest({"a*a?", "a+b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest367, STest, STest({"a??a*", "a*a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest368, STest, STest({"a?a?", "a+?|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest369, STest, STest({"a?a|a", "ab|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest370, STest, STest({"aa|b*?", "a+b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest371, STest, STest({"a*|b|c", "ab|c|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest372, STest, STest({"a??a|a", "a?|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest373, STest, STest({"a|bb", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest374, STest, STest({"abba", "a?bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest375, STest, STest({"a*b", "a+(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest376, STest, STest({"a|a|b*?", "a?|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest377, STest, STest({"abc|c", "abb+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest378, STest, STest({"a|a|b+?", "a|a|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest379, STest, STest({"a?|b?", "a??bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest380, STest, STest({"a?ab", "a|a|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest381, STest, STest({"ab|c+", "a?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 27, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest382, STest, STest({"a*?|bb", "a|ba?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest383, STest, STest({"a??|b|c", "abc."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest384, STest, STest({"a?|b|a", "a*?a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest385, STest, STest({"a?|a+?", "ab|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest386, STest, STest({"a|a|(a)", "a?b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest387, STest, STest({"a+a?", "a*?|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest388, STest, STest({"a*?|a|b", "a|b|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest389, STest, STest({"a?|bc", "a+|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest390, STest, STest({"a*?|b|c", "aa|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest391, STest, STest({"a+?|aa", "abb*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest392, STest, STest({"a?|(b)", "a|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest393, STest, STest({"ab|c|.", "a*(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest394, STest, STest({"a*?|ab", "aaa*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest395, STest, STest({"a?b|b", "a*|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest396, STest, STest({"a+?a", "a*|bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest397, STest, STest({"aba*", "a+?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest398, STest, STest({"aaab", "a*|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest399, STest, STest({"a?|a|a", "a?|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest400, STest, STest({"aa|a?", "a*?(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest401, STest, STest({"a*?b*", "a|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest402, STest, STest({"a|b|c.", "a|bc|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(34, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest403, STest, STest({"a|bca", "a|bb??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest404, STest, STest({"a+a|b", "a|aa??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest405, STest, STest({"aa|b|b", "ab|c??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest406, STest, STest({"(a)(b)", "aa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest407, STest, STest({"a?|b*?", "ab|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest408, STest, STest({"a+|a??", "a?b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest409, STest, STest({"a?|b*?", "a|b|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest410, STest, STest({"ab|a", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest411, STest, STest({"a+?a", "a+?|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest412, STest, STest({"a+bc", "a*a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest413, STest, STest({"a+?b*", R"(a??(b))"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest414, STest, STest({"a+a|b", "a|bb*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(27, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest415, STest, STest({"a|a|a??", R"(a??(b))"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest416, STest, STest({"a+|a", "a*(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest417, STest, STest({"a|ab*?", "a+?|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest418, STest, STest({"a|b|(c)", "a|bc|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(41, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[40]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest419, STest, STest({"a?a*", "a+?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest420, STest, STest({"a|b(b)", "a|a|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest421, STest, STest({"a+b??", "a*?a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest422, STest, STest({"a|a|bc", "a?b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest423, STest, STest({"aab|a", "aaa+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest424, STest, STest({"a??|a*?", "a?|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest425, STest, STest({"ab|b+", "a+?|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest426, STest, STest({"abba", "a*|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest427, STest, STest({"ab|c|b", "a?|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest428, STest, STest({"a*?b*", "a*?|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest429, STest, STest({"a+?a?", "a|b|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest430, STest, STest({"a??|a|a", "a|bb|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest431, STest, STest({"a*?aa", "a|b(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest432, STest, STest({"a+b*?", "a|b|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest433, STest, STest({"a+?a??", "aa(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest434, STest, STest({"a?b+?", "a+a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest435, STest, STest({"a+?bb", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest436, STest, STest({"ab|a+", "a|a|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest437, STest, STest({"a+?|a+", "a|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest438, STest, STest({"a|b|c|a", "a|a|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(44, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[43]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest439, STest, STest({"a??|b|b", "((a))"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest440, STest, STest({"a*a+", "a??|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest441, STest, STest({"a*b|b", "a??a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest442, STest, STest({"a|bc|.", "a|b|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest443, STest, STest({"a+?ab", "a+?a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest444, STest, STest({"a+?|bb", "ab|c|."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(37, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[36]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest445, STest, STest({"a|a|ba", "a|b(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest446, STest, STest({"ab??", "ab|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest447, STest, STest({"aaa", "a??|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest448, STest, STest({"a|b|c", "aba|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(37, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[36]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest449, STest, STest({"a|a|a|b", "ab|a|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest450, STest, STest({"a|bc+?", "abc|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(23, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest451, STest, STest({"a|ba?", "a?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest452, STest, STest({"ab|b+", "a?b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest453, STest, STest({"a+?b+?", "a*b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest454, STest, STest({"a|bb+", "aa|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(32, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[31]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest455, STest, STest({"a+ab", "a+|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest456, STest, STest({"a+|bb", "abb|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest457, STest, STest({"ab|a+", "aaa*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest458, STest, STest({"a+", "a*?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest459, STest, STest({"abbb", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest460, STest, STest({"ab|aa", "aba|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest461, STest, STest({"a*?b|b", "a*?|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest462, STest, STest({"abc?", "a+?b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest463, STest, STest({"(a)*?", "a??|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest464, STest, STest({"a+?a+?", "a|ba+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest465, STest, STest({"ab|c+?", "(a)??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest466, STest, STest({"a*", "a+|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest467, STest, STest({"ab(c)", "(a*)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest468, STest, STest({"a|a|bb", "a+bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest469, STest, STest({"a*|bb", "a??|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest470, STest, STest({"a|a|(a)", "aa|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest471, STest, STest({"a|a(b)", "a+?|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest472, STest, STest({"a??", "a|bb|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest473, STest, STest({"abb*", "a??b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest474, STest, STest({"a|b|b|a", "a*?|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest475, STest, STest({"a|b|ab", "a|bc+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(32, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 27, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[31]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest476, STest, STest({"a*(b)", "aa|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest477, STest, STest({"ab|b", "a+b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest478, STest, STest({"a*?|(a)", "a??|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest479, STest, STest({"a*b*", "a?|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest480, STest, STest({"aa|a??", "a??|ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest481, STest, STest({"a+?|(a)", "a?a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest482, STest, STest({"a??|b*?", "a+|ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest483, STest, STest({"a*a??", "a|a(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest484, STest, STest({"a*?b+", "a|b|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest485, STest, STest({"a+a+?", "a*|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest486, STest, STest({"a|bb+?", "aba|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest487, STest, STest({"a*?a??", "a*?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest488, STest, STest({"ab|c*", "a*|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest489, STest, STest({"a|bc|a", "ab|bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest490, STest, STest({"(a)*?", "aab*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest491, STest, STest({"a?a", "a|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest492, STest, STest({"a+|b+", "a+a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest493, STest, STest({"a|b|c|.", "a|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest494, STest, STest({"a*?|b??", "a+?|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest495, STest, STest({"a*?|ab", "a*?ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest496, STest, STest({"a|bc*?", "a*?b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest497, STest, STest({"a?|a", "a?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest498, STest, STest({"a?a", "a+?b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest499, STest, STest({"ab|a|b", "a|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(35, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 1), fixture.Hits[34]);
}
