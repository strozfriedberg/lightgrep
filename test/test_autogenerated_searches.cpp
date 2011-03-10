#include <scope/test.h>

#include "test_helper.h"

SCOPE_FIXTURE_CTOR(autoPatternTest0, STest, STest("a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1, STest, STest("(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest2, STest, STest("aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest3, STest, STest("ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest4, STest, STest("a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest5) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest6) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest7, STest, STest("a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest8, STest, STest("a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest9, STest, STest("(aa)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest10, STest, STest("(ab)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest11, STest, STest("(a+)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest12) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("(a*)", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest13) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("(a?)", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest14, STest, STest("(a|a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest15, STest, STest("(a|b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest16, STest, STest("((a))")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest17, STest, STest("(a)(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest18, STest, STest("(a)(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest19, STest, STest("(a)+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest20) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("(a)*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest21) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("(a)?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest22, STest, STest("(a)|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest23, STest, STest("(a)|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest24, STest, STest("aa(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest25, STest, STest("ab(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest26, STest, STest("aa(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest27, STest, STest("ab(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest28, STest, STest("ab(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest29, STest, STest("aaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest30, STest, STest("aba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest31, STest, STest("aab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest32, STest, STest("abb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest33, STest, STest("abc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest34, STest, STest("aaaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest35, STest, STest("abaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest36, STest, STest("aaba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest37, STest, STest("abba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest38, STest, STest("abca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest39, STest, STest("aaab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest40, STest, STest("abab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest41, STest, STest("aabb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest42, STest, STest("abbb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest43, STest, STest("abcb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest44, STest, STest("abac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest45, STest, STest("aabc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest46, STest, STest("abbc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest47, STest, STest("abcc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest48, STest, STest("abc.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest49, STest, STest("aaa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest50, STest, STest("aaa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest51, STest, STest("aaa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest52, STest, STest("aba+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest53, STest, STest("aba*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest54, STest, STest("aba?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest55, STest, STest("aab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest56, STest, STest("aab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest57, STest, STest("aab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest58, STest, STest("abb+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest59, STest, STest("abb*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest60, STest, STest("abb?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest61, STest, STest("abc+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest62, STest, STest("abc*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest63, STest, STest("abc?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest64, STest, STest("aaa|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest65, STest, STest("aba|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest66, STest, STest("aab|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest67, STest, STest("abb|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest68, STest, STest("abc|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest69, STest, STest("aaa|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest70, STest, STest("aba|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest71, STest, STest("aab|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest72, STest, STest("abb|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest73, STest, STest("abc|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest74, STest, STest("aba|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest75, STest, STest("aab|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest76, STest, STest("abb|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest77, STest, STest("abc|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest78, STest, STest("abc|.")) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest79, STest, STest("aa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest80, STest, STest("aa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest81, STest, STest("aa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest82, STest, STest("ab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest83, STest, STest("ab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest84, STest, STest("ab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest85, STest, STest("aa|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest86, STest, STest("ab|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest87, STest, STest("aa|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest88, STest, STest("ab|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest89, STest, STest("ab|(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest90, STest, STest("aa|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest91, STest, STest("ab|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest92, STest, STest("aa|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest93, STest, STest("ab|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest94, STest, STest("ab|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest95, STest, STest("aa|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest96, STest, STest("ab|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest97, STest, STest("aa|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest98, STest, STest("ab|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest99, STest, STest("ab|ca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest100, STest, STest("aa|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest101, STest, STest("ab|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest102, STest, STest("aa|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest103, STest, STest("ab|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest104, STest, STest("ab|cb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest105, STest, STest("ab|ac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 2, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest106, STest, STest("aa|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest107, STest, STest("ab|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest108, STest, STest("ab|cc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest109, STest, STest("ab|c.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest110, STest, STest("aa|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_TEST(autoPatternTest111) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("aa|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest112) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("aa|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest113, STest, STest("ab|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest114) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("ab|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest115) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("ab|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest116, STest, STest("aa|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[7]);
}

SCOPE_TEST(autoPatternTest117) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("aa|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest118) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("aa|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest119, STest, STest("ab|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest120) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("ab|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest121) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("ab|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest122, STest, STest("ab|c+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 3, 0), fixture.Hits[8]);
}

SCOPE_TEST(autoPatternTest123) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("ab|c*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest124) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("ab|c?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest125, STest, STest("aa|a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest126, STest, STest("ab|a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest127, STest, STest("aa|b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest128, STest, STest("ab|b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest129, STest, STest("ab|c|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest130, STest, STest("aa|a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest131, STest, STest("ab|a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest132, STest, STest("aa|b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest133, STest, STest("ab|b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest134, STest, STest("ab|c|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest135, STest, STest("ab|a|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest136, STest, STest("aa|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[19]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest137, STest, STest("ab|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest138, STest, STest("ab|c|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest139, STest, STest("ab|c|.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest140, STest, STest("a+(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest141, STest, STest("a*(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest142, STest, STest("a?(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest143, STest, STest("a+(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest144, STest, STest("a*(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest145, STest, STest("a?(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest146, STest, STest("a+a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest147, STest, STest("a*a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest148, STest, STest("a?a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest149, STest, STest("a+b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest150, STest, STest("a*b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest151, STest, STest("a?b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest152, STest, STest("a+aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest153, STest, STest("a*aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest154, STest, STest("a?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest155, STest, STest("a+ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest156, STest, STest("a*ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest157, STest, STest("a?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest158, STest, STest("a+ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest159, STest, STest("a*ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest160, STest, STest("a?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest161, STest, STest("a+bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest162, STest, STest("a*bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest163, STest, STest("a?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest164, STest, STest("a+bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest165, STest, STest("a*bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest166, STest, STest("a?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest167, STest, STest("a+a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest168, STest, STest("a*a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest169, STest, STest("a?a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest170, STest, STest("a+a*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest171) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest172) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest173, STest, STest("a+a?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest174) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest175) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest176, STest, STest("a+b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest177, STest, STest("a*b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest178, STest, STest("a?b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest179, STest, STest("a+b*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest180) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest181) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest182, STest, STest("a+b?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest183) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest184) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest185, STest, STest("a+a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest186, STest, STest("a*a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest187, STest, STest("a?a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest188, STest, STest("a+b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest189, STest, STest("a*b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest190, STest, STest("a?b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest191, STest, STest("a+a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest192, STest, STest("a*a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest193, STest, STest("a?a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(17, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest194, STest, STest("a+b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest195, STest, STest("a*b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest196, STest, STest("a?b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest197, STest, STest("a+b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest198, STest, STest("a*b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternTest199, STest, STest("a?b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(18, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest200, STest, STest("a+|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest201) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|(a)", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest202) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|(a)", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest203, STest, STest("a+|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest204) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|(b)", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest205) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|(b)", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest206, STest, STest("a+|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest207) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|a", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest208) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|a", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest209, STest, STest("a+|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest210) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest211) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest212, STest, STest("a+|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest213) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|aa", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest214) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|aa", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest215, STest, STest("a+|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_TEST(autoPatternTest216) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|ba", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest217) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|ba", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest218, STest, STest("a+|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest219) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|ab", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest220) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|ab", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest221, STest, STest("a+|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_TEST(autoPatternTest222) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|bb", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest223) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|bb", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest224, STest, STest("a+|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_TEST(autoPatternTest225) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|bc", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest226) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|bc", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest227, STest, STest("a+|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest228) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|a+", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest229) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|a+", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest230) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a+|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest231) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest232) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest233) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a+|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest234) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest235) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest236, STest, STest("a+|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(13, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[12]);
}

SCOPE_TEST(autoPatternTest237) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b+", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest238) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b+", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest239) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a+|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest240) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest241) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest242) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a+|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest243) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest244) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest245, STest, STest("a+|a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[6]);
}

SCOPE_TEST(autoPatternTest246) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|a|a", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest247) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|a|a", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest248, STest, STest("a+|b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest249) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b|a", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest250) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b|a", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest251, STest, STest("a+|a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest252) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|a|b", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest253) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|a|b", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest254, STest, STest("a+|b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(16, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[15]);
}

SCOPE_TEST(autoPatternTest255) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b|b", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest256) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b|b", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest257, STest, STest("a+|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(25, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 1, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 1, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 1, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 1, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[24]);
}

SCOPE_TEST(autoPatternTest258) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a*|b|c", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest259) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a?|b|c", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest260, STest, STest("a|a(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest261, STest, STest("a|b(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest262, STest, STest("a|a(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest263, STest, STest("a|b(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest264, STest, STest("a|b(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest265, STest, STest("a|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest266, STest, STest("a|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest267, STest, STest("a|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest268, STest, STest("a|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest269, STest, STest("a|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest270, STest, STest("a|aaa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest271, STest, STest("a|baa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest272, STest, STest("a|aba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest273, STest, STest("a|bba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest274, STest, STest("a|bca")) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(11, 3, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest275, STest, STest("a|aab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest276, STest, STest("a|bab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 3, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest277, STest, STest("a|abb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest278, STest, STest("a|bbb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest279, STest, STest("a|bcb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest280, STest, STest("a|bac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest281, STest, STest("a|abc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest282, STest, STest("a|bbc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest283, STest, STest("a|bcc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest284, STest, STest("a|bc.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest285, STest, STest("a|aa+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest286, STest, STest("a|aa*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest287, STest, STest("a|aa?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest288, STest, STest("a|ba+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest289, STest, STest("a|ba*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest290, STest, STest("a|ba?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest291, STest, STest("a|ab+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest292, STest, STest("a|ab*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest293, STest, STest("a|ab?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest294, STest, STest("a|bb+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest295, STest, STest("a|bb*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest296, STest, STest("a|bb?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest297, STest, STest("a|bc+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest298, STest, STest("a|bc*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest299, STest, STest("a|bc?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest300, STest, STest("a|aa|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest301, STest, STest("a|ba|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest302, STest, STest("a|ab|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest303, STest, STest("a|bb|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest304, STest, STest("a|bc|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest305, STest, STest("a|aa|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest306, STest, STest("a|ba|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest307, STest, STest("a|ab|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest308, STest, STest("a|bb|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest309, STest, STest("a|bc|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest310, STest, STest("a|ba|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest311, STest, STest("a|ab|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest312, STest, STest("a|bb|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest313, STest, STest("a|bc|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest314, STest, STest("a|bc|.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest315, STest, STest("a|a+")) {
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

SCOPE_TEST(autoPatternTest316) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest317) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest318, STest, STest("a|b+")) {
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

SCOPE_TEST(autoPatternTest319) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest320) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest321, STest, STest("a|a|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest322, STest, STest("a|b|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest323, STest, STest("a|a|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest324, STest, STest("a|b|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest325, STest, STest("a|b|(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest326, STest, STest("a|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest327, STest, STest("a|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest328, STest, STest("a|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest329, STest, STest("a|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest330, STest, STest("a|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest331, STest, STest("a|a|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest332, STest, STest("a|b|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest333, STest, STest("a|a|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest334, STest, STest("a|b|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest335, STest, STest("a|b|ca")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest336, STest, STest("a|a|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest337, STest, STest("a|b|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest338, STest, STest("a|a|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest339, STest, STest("a|b|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest340, STest, STest("a|b|cb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest341, STest, STest("a|b|ac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest342, STest, STest("a|a|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest343, STest, STest("a|b|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest344, STest, STest("a|b|cc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest345, STest, STest("a|b|c.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest346, STest, STest("a|a|a+")) {
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

SCOPE_TEST(autoPatternTest347) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|a|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest348) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|a|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest349, STest, STest("a|b|a+")) {
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

SCOPE_TEST(autoPatternTest350) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|a*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest351) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest352, STest, STest("a|a|b+")) {
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

SCOPE_TEST(autoPatternTest353) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|a|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest354) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|a|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest355, STest, STest("a|b|b+")) {
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

SCOPE_TEST(autoPatternTest356) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|b*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest357) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|b?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest358, STest, STest("a|b|c+")) {
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

SCOPE_TEST(autoPatternTest359) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|c*", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(autoPatternTest360) {
  Parser p;
  SyntaxTree tree;
  SCOPE_ASSERT(parse("a|b|c?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_FIXTURE_CTOR(autoPatternTest361, STest, STest("a|a|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest362, STest, STest("a|b|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest363, STest, STest("a|a|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest364, STest, STest("a|b|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest365, STest, STest("a|b|c|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest366, STest, STest("a|a|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest367, STest, STest("a|b|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest368, STest, STest("a|a|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest369, STest, STest("a|b|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest370, STest, STest("a|b|c|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest371, STest, STest("a|b|a|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest372, STest, STest("a|a|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest373, STest, STest("a|b|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest374, STest, STest("a|b|c|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest375, STest, STest("a|b|c|.")) {
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

