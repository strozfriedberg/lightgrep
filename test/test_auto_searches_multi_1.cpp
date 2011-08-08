#include <algorithm>

#include <scope/test.h>

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoMultipatternTest0, STest, STest(2, (const char*[]){"a+?a*?", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest1, STest, STest(2, (const char*[]){"a|aa?", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest2, STest, STest(2, (const char*[]){"a|bb+?", "a+|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest3, STest, STest(2, (const char*[]){"aaa+", "a+?|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest4, STest, STest(2, (const char*[]){"a?|a??", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest5, STest, STest(2, (const char*[]){"a+?|b+?", "a|aa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest6, STest, STest(2, (const char*[]){"a??b+", "a*?a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest7, STest, STest(2, (const char*[]){"a|a|b?", "a+b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest8, STest, STest(2, (const char*[]){"aab+?", "a*aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest9, STest, STest(2, (const char*[]){"ab|b+", "(a)*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest10, STest, STest(2, (const char*[]){"a*?", "a?|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest11, STest, STest(2, (const char*[]){"a+b|c", "ab|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest12, STest, STest(2, (const char*[]){"a?|b|b", "a+|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest13, STest, STest(2, (const char*[]){"a?|a+", "a|b|c|."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[27]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest14, STest, STest(2, (const char*[]){"ab|b|b", "aabc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest15, STest, STest(2, (const char*[]){"abab", "ab(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest16, STest, STest(2, (const char*[]){"ab|c|.", "a|bb*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(41, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[40]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest17, STest, STest(2, (const char*[]){"a+|b", "aa|bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest18, STest, STest(2, (const char*[]){"a*?|(b)", "a|ab|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest19, STest, STest(2, (const char*[]){"ab|ba", "a|abb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest20, STest, STest(2, (const char*[]){"a*|ba", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest21, STest, STest(2, (const char*[]){"a|b|cc", "a|bc|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(40, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[39]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest22, STest, STest(2, (const char*[]){"a|a", "a??|bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest23, STest, STest(2, (const char*[]){"aa|ab", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest24, STest, STest(2, (const char*[]){"a*a?", "a|abb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest25, STest, STest(2, (const char*[]){"aa??", "a*|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest26, STest, STest(2, (const char*[]){"a??a??", "a|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest27, STest, STest(2, (const char*[]){"a|b|c|a", "abb|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest28, STest, STest(2, (const char*[]){"a?|a*", "a?|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest29, STest, STest(2, (const char*[]){"a+b|a", "a|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest30, STest, STest(2, (const char*[]){"a*?a", "a??b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest31, STest, STest(2, (const char*[]){"a*|b*?", "a|aa|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest32, STest, STest(2, (const char*[]){"(a??)", "a|a|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest33, STest, STest(2, (const char*[]){"ab|c|c", "a+|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(37, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[36]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest34, STest, STest(2, (const char*[]){"a*?a", "a|b|c?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest35, STest, STest(2, (const char*[]){"a+?|aa", "a*|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest36, STest, STest(2, (const char*[]){"abba", "abc|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 4, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest37, STest, STest(2, (const char*[]){"a+a+?", "a+aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest38, STest, STest(2, (const char*[]){"a*|b|a", "a|ab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest39, STest, STest(2, (const char*[]){"abc+?", "a*?|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest40, STest, STest(2, (const char*[]){"aa??", "abc+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest41, STest, STest(2, (const char*[]){"abca", "ab|b|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest42, STest, STest(2, (const char*[]){"a??|b*", "a*a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest43, STest, STest(2, (const char*[]){"a+|a", "a|b|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest44, STest, STest(2, (const char*[]){"(a*)", "aaa??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest45, STest, STest(2, (const char*[]){"a|aa*", "abb??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest46, STest, STest(2, (const char*[]){"a|bc+?", "a+?ba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest47, STest, STest(2, (const char*[]){"a??|bc", "a+?|a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest48, STest, STest(2, (const char*[]){"aa|a|a", "a??a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest49, STest, STest(2, (const char*[]){"a|aab", "a|a|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest50, STest, STest(2, (const char*[]){"a?|a*?", "a|a|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest51, STest, STest(2, (const char*[]){"a|b|c.", "a|ab|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(40, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[39]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest52, STest, STest(2, (const char*[]){"a??|a*", "a|a|bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest53, STest, STest(2, (const char*[]){"a+?b?", "a??a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest54, STest, STest(2, (const char*[]){"ab|c??", "a|bb+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest55, STest, STest(2, (const char*[]){"abb|a", "aab??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest56, STest, STest(2, (const char*[]){"a+|ab", "a*|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest57, STest, STest(2, (const char*[]){"ab|bc", "a|b|ac"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(24, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[23]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest58, STest, STest(2, (const char*[]){"a+?a*", "aabc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest59, STest, STest(2, (const char*[]){"a|a??", "a|b|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest60, STest, STest(2, (const char*[]){"a|a??", "ab?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest61, STest, STest(2, (const char*[]){"a|b|bc", "a*a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest62, STest, STest(2, (const char*[]){"aa|a??", "a|b|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest63, STest, STest(2, (const char*[]){"ab|c|b", "a|b|c??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[17]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest64, STest, STest(2, (const char*[]){"(a|a)", "a+?b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest65, STest, STest(2, (const char*[]){"aaa|b", "a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest66, STest, STest(2, (const char*[]){"a?a?", "a+aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest67, STest, STest(2, (const char*[]){"a+|b*", "a|bb+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest68, STest, STest(2, (const char*[]){"aa|ba", "aa|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest69, STest, STest(2, (const char*[]){"ab??", "a?|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest70, STest, STest(2, (const char*[]){"a??|b*?", "a??b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest71, STest, STest(2, (const char*[]){"a??|b*?", "a+?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest72, STest, STest(2, (const char*[]){"ab|a??", "a+b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest73, STest, STest(2, (const char*[]){"a|b|a+?", "a|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest74, STest, STest(2, (const char*[]){"aaa|b", "aab|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest75, STest, STest(2, (const char*[]){"ab|(a)", "a+?|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest76, STest, STest(2, (const char*[]){"a|b|b*?", "a|bc+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest77, STest, STest(2, (const char*[]){"a+|bb", "ab|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest78, STest, STest(2, (const char*[]){"(a?)", "a*a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest79, STest, STest(2, (const char*[]){"a+?|b|c", "a*|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(28, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest80, STest, STest(2, (const char*[]){"a*|b|c", "a|aba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest81, STest, STest(2, (const char*[]){"ab|c?", "a+?|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest82, STest, STest(2, (const char*[]){"a|bac", "a|b|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 3, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest83, STest, STest(2, (const char*[]){"a+a*", "a??a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest84, STest, STest(2, (const char*[]){"a+|a|b", "a|b|a|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(44, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[43]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest85, STest, STest(2, (const char*[]){"a+|b|a", "a*?a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(35, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[34]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest86, STest, STest(2, (const char*[]){"a*a+", "a?a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest87, STest, STest(2, (const char*[]){"a|bc|b", "a*|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest88, STest, STest(2, (const char*[]){"a+?|b?", "(a)|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest89, STest, STest(2, (const char*[]){"a*a??", "a??|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest90, STest, STest(2, (const char*[]){"a|a|b*", "a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest91, STest, STest(2, (const char*[]){"a??|a??", "a?|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest92, STest, STest(2, (const char*[]){"a|abb", "a|ba??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest93, STest, STest(2, (const char*[]){"a+|a*", "a*?|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest94, STest, STest(2, (const char*[]){"a|b|(b)", "aa|a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(27, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest95, STest, STest(2, (const char*[]){"a??b?", "aaa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest96, STest, STest(2, (const char*[]){"a|a|a?", "a*?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest97, STest, STest(2, (const char*[]){"aa|a|a", "a*|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest98, STest, STest(2, (const char*[]){"a*?|b|c", "a|aa|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest99, STest, STest(2, (const char*[]){"a|b|c*?", "abb|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest100, STest, STest(2, (const char*[]){"abb*", "a??|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest101, STest, STest(2, (const char*[]){"(a?)", "aaa*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest102, STest, STest(2, (const char*[]){"ab|bb", "ab|c."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest103, STest, STest(2, (const char*[]){"a|a??", "a+?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest104, STest, STest(2, (const char*[]){"a", "aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest105, STest, STest(2, (const char*[]){"aa|a|a", "a+|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(15, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest106, STest, STest(2, (const char*[]){"a|ab+", "a|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest107, STest, STest(2, (const char*[]){"a|b|c|.", "a??a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(38, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[37]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest108, STest, STest(2, (const char*[]){"aa|(a)", "a|b|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(27, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest109, STest, STest(2, (const char*[]){"aa|a|b", "a|b|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest110, STest, STest(2, (const char*[]){"a*b", "aa*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest111, STest, STest(2, (const char*[]){"a?aa", "a+a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest112, STest, STest(2, (const char*[]){"aaa*", "a*a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest113, STest, STest(2, (const char*[]){"aa|bb", "ab|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest114, STest, STest(2, (const char*[]){"a+?|ab", "ab+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest115, STest, STest(2, (const char*[]){"a+?", "(a)*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest116, STest, STest(2, (const char*[]){"a|b|ab", "aab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest117, STest, STest(2, (const char*[]){"a??a?", "a*?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest118, STest, STest(2, (const char*[]){"a??|(a)", "a|a|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest119, STest, STest(2, (const char*[]){"a*?|b??", "a|abc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest120, STest, STest(2, (const char*[]){"a*?|b|c", "a+?|a*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest121, STest, STest(2, (const char*[]){"a|b*", "(a)(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest122, STest, STest(2, (const char*[]){"a+?b", "a|aba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest123, STest, STest(2, (const char*[]){"aa(a)", "a|b|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest124, STest, STest(2, (const char*[]){"a|a|ba", "a?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest125, STest, STest(2, (const char*[]){"a|bbc", "ab|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(27, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 3, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[26]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest126, STest, STest(2, (const char*[]){"a|aa*", "abc|."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(36, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[35]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest127, STest, STest(2, (const char*[]){"aa|ab", "(a)(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest128, STest, STest(2, (const char*[]){"a+?|(b)", "a+?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest129, STest, STest(2, (const char*[]){"a?b|b", "aaba"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest130, STest, STest(2, (const char*[]){"a|ba+", "a+|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest131, STest, STest(2, (const char*[]){"a*|(b)", "a?a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest132, STest, STest(2, (const char*[]){"a+|a*", "a|ba*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(15, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest133, STest, STest(2, (const char*[]){"a??|a*?", "abb??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest134, STest, STest(2, (const char*[]){"a+a??", "a+?|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest135, STest, STest(2, (const char*[]){"a*?|b?", "a*?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest136, STest, STest(2, (const char*[]){"aa+", "a+bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest137, STest, STest(2, (const char*[]){"a|a(b)", "a+?|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest138, STest, STest(2, (const char*[]){"a?bc", "a|a|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest139, STest, STest(2, (const char*[]){"a+?b|b", "a+|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest140, STest, STest(2, (const char*[]){"aba+", "aaa+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest141, STest, STest(2, (const char*[]){"a*|b*", "a|aa|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest142, STest, STest(2, (const char*[]){"abb|a", "a?|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest143, STest, STest(2, (const char*[]){"a+?b+?", "a+|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest144, STest, STest(2, (const char*[]){"a*?a*", "a|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest145, STest, STest(2, (const char*[]){"a|ba", "ab|ca"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(15, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest146, STest, STest(2, (const char*[]){"a?|b+?", "ab|bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 1), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest147, STest, STest(2, (const char*[]){"aaa*?", "abca"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest148, STest, STest(2, (const char*[]){"a+?|b??", "a*?|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest149, STest, STest(2, (const char*[]){"aba*?", "a+?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest150, STest, STest(2, (const char*[]){"ab|c?", "aaa?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest151, STest, STest(2, (const char*[]){"a|b*", "a|bbc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 3, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest152, STest, STest(2, (const char*[]){"a+|b", "a|baa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest153, STest, STest(2, (const char*[]){"a+bb", "a?|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest154, STest, STest(2, (const char*[]){"a|b|bc", "a*?|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest155, STest, STest(2, (const char*[]){"a|b?", "a+a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest156, STest, STest(2, (const char*[]){"a?|a+?", "a*|b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest157, STest, STest(2, (const char*[]){"a|b|c+?", "a+|aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(35, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[34]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest158, STest, STest(2, (const char*[]){"a|b|b*", "aaa+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest159, STest, STest(2, (const char*[]){"a|a(a)", "ab|c."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest160, STest, STest(2, (const char*[]){"a*(b)", "a|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest161, STest, STest(2, (const char*[]){"a+ab", "a?aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest162, STest, STest(2, (const char*[]){"a+|b+?", "(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest163, STest, STest(2, (const char*[]){"a+ba", "a+?ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest164, STest, STest(2, (const char*[]){"ab|c", "a??|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest165, STest, STest(2, (const char*[]){"a|a|b??", "a|b|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest166, STest, STest(2, (const char*[]){"aab*?", "(a|b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest167, STest, STest(2, (const char*[]){"a|ba+?", "aab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest168, STest, STest(2, (const char*[]){"abcc", "a|bc+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest169, STest, STest(2, (const char*[]){"a|a|a+?", "a*?|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest170, STest, STest(2, (const char*[]){"a*?", "a|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest171, STest, STest(2, (const char*[]){"a+bb", "a|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest172, STest, STest(2, (const char*[]){"a+ab", "ab|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest173, STest, STest(2, (const char*[]){"a?b+?", "ab|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest174, STest, STest(2, (const char*[]){"a*a?", "a+|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest175, STest, STest(2, (const char*[]){"a*?(a)", "a|aa|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest176, STest, STest(2, (const char*[]){"a?|aa", "a+b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest177, STest, STest(2, (const char*[]){"aa|a", "aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest178, STest, STest(2, (const char*[]){"a*|ab", "a|b|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest179, STest, STest(2, (const char*[]){"a?|b??", "a*?a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest180, STest, STest(2, (const char*[]){"a|b|(b)", "a??b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest181, STest, STest(2, (const char*[]){"a*?|b+", "a*?|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest182, STest, STest(2, (const char*[]){"ab|ac", "a|a|b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 2, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 2, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest183, STest, STest(2, (const char*[]){"a|ba?", "a+b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(23, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest184, STest, STest(2, (const char*[]){"a|bcc", "a?|ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest185, STest, STest(2, (const char*[]){"ab|(a)", "a*|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest186, STest, STest(2, (const char*[]){"a*?b|a", "aab|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(23, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest187, STest, STest(2, (const char*[]){"a|b|b?", "a+?|b|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest188, STest, STest(2, (const char*[]){"ab|aa", "a|b|c|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(33, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[32]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest189, STest, STest(2, (const char*[]){"a|ba*", "ab|c|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(34, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[33]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest190, STest, STest(2, (const char*[]){"aaab", "a??b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest191, STest, STest(2, (const char*[]){"a|b|(a)", "a?|b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest192, STest, STest(2, (const char*[]){"a|b|cb", "a|b|c|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(47, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 2, 0), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[35]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[36]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[37]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[38]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[39]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 0), fixture.Hits[40]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[41]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[42]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[43]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[44]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[45]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[46]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest193, STest, STest(2, (const char*[]){"a+|bc", "ab?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest194, STest, STest(2, (const char*[]){"a??|a+?", "a??ab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest195, STest, STest(2, (const char*[]){"a|bc|c", "a+?b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest196, STest, STest(2, (const char*[]){"a+?ba", "a??|a|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest197, STest, STest(2, (const char*[]){"a?|a|b", "a*|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest198, STest, STest(2, (const char*[]){"aba|b", "a*?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest199, STest, STest(2, (const char*[]){"a??|a*?", "abcb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest200, STest, STest(2, (const char*[]){"a|baa", "aaa??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest201, STest, STest(2, (const char*[]){"a?|bb", "a|b|b*"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest202, STest, STest(2, (const char*[]){"aa|b|b", "ab(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest203, STest, STest(2, (const char*[]){"a?|a|b", "a?a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest204, STest, STest(2, (const char*[]){"ab|b|c", "a+aa"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[18]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest205, STest, STest(2, (const char*[]){"a??|bc", "(a+?)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest206, STest, STest(2, (const char*[]){"ab|bb", "a+?|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(23, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[22]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest207, STest, STest(2, (const char*[]){"a|aa+?", "ab|a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest208, STest, STest(2, (const char*[]){"a??|a+", "abb*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest209, STest, STest(2, (const char*[]){"ab??", "a+b?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest210, STest, STest(2, (const char*[]){"a+b+", "a??a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest211, STest, STest(2, (const char*[]){"(a)(a)", "a+?bc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest212, STest, STest(2, (const char*[]){"a??aa", "a|bca"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 3, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest213, STest, STest(2, (const char*[]){"a+?a?", "a|a|b|c"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(36, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 1), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 1), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[28]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[29]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[30]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 1), fixture.Hits[31]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 1), fixture.Hits[32]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 1), fixture.Hits[33]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[34]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[35]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest214, STest, STest(2, (const char*[]){"a??ba", "a+?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest215, STest, STest(2, (const char*[]){"a|b|aa", "a*bb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest216, STest, STest(2, (const char*[]){"a|aa??", "aaa+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest217, STest, STest(2, (const char*[]){"a?|a?", "a*a|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest218, STest, STest(2, (const char*[]){"ab|a|b", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest219, STest, STest(2, (const char*[]){"aab+?", "a+?a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest220, STest, STest(2, (const char*[]){"a|ab*", "a*b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest221, STest, STest(2, (const char*[]){"a*ab", "ab|ac"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 2, 1), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest222, STest, STest(2, (const char*[]){"a|b|b|a", "(a)|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(29, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[25]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[26]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[27]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[28]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest223, STest, STest(2, (const char*[]){"a?aa", "a|ba+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest224, STest, STest(2, (const char*[]){"ab|c|c", "a|b|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[11]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest225, STest, STest(2, (const char*[]){"a?|bb", "a*|b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest226, STest, STest(2, (const char*[]){"a+|ab", "a?b*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest227, STest, STest(2, (const char*[]){"aab*", "(a*)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest228, STest, STest(2, (const char*[]){"abac", "a|b|a*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest229, STest, STest(2, (const char*[]){"a+|b*?", "a|b|c."})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 1), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest230, STest, STest(2, (const char*[]){"aba|c", "a|ab|a"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest231, STest, STest(2, (const char*[]){"a+|ab", "aab+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest232, STest, STest(2, (const char*[]){"aa(b)", "a*?|b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest233, STest, STest(2, (const char*[]){"a|bc.", "a|abc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(21, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 3, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 3, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[20]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest234, STest, STest(2, (const char*[]){"a|b(b)", "a|bab"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(22, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 3, 1), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[21]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest235, STest, STest(2, (const char*[]){"aa|bc", "a?b"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 1), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest236, STest, STest(2, (const char*[]){"a|b|(b)", "a|a|a??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest237, STest, STest(2, (const char*[]){"ab|c|a", "(a?)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[7]);
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

SCOPE_FIXTURE_CTOR(autoMultipatternTest238, STest, STest(2, (const char*[]){"((a))", "a+b+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest239, STest, STest(2, (const char*[]){"a|b|a*?", "a??|a+?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

}

SCOPE_FIXTURE_CTOR(autoMultipatternTest240, STest, STest(2, (const char*[]){"aab", "a*a?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest241, STest, STest(2, (const char*[]){"a+|b*?", "a+?b+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest242, STest, STest(2, (const char*[]){"a?aa", "a*|(b)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest243, STest, STest(2, (const char*[]){"a|bb+?", "abbc"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

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

SCOPE_FIXTURE_CTOR(autoMultipatternTest244, STest, STest(2, (const char*[]){"abc|a", "a+|a+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 1), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 1), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 1), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 1), fixture.Hits[16]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest245, STest, STest(2, (const char*[]){"a+?|a??", "abb"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 1), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest246, STest, STest(2, (const char*[]){"ab|a+?", "a?|(a)"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest247, STest, STest(2, (const char*[]){"a+b+", "ab|b??"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest248, STest, STest(2, (const char*[]){"ab|c*", "aab*?"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoMultipatternTest249, STest, STest(2, (const char*[]){"a??bb", "ab|c+"})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  std::sort(fixture.Hits.begin(), fixture.Hits.end());

  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 1), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 1), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 1), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 1), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 3, 1), fixture.Hits[10]);
}
