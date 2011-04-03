#include <scope/test.h>

#include "nfabuilder.h"
#include "parsetree.h"

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
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest6) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest7, STest, STest("a+?")) {
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

SCOPE_TEST(autoPatternTest8) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest9) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest10, STest, STest("a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest11, STest, STest("a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest12, STest, STest("(aa)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest13, STest, STest("(ab)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest14, STest, STest("(a+)")) {
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

SCOPE_TEST(autoPatternTest15) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest16) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest17, STest, STest("(a+?)")) {
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

SCOPE_TEST(autoPatternTest18) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest19) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a??)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest20, STest, STest("(a|a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest21, STest, STest("(a|b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest22, STest, STest("((a))")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest23, STest, STest("(a)(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest24, STest, STest("(a)(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest25, STest, STest("(a)+")) {
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

SCOPE_TEST(autoPatternTest26) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest27) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest28, STest, STest("(a)+?")) {
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

SCOPE_TEST(autoPatternTest29) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest30) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest31, STest, STest("(a)|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest32, STest, STest("(a)|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest33, STest, STest("aa(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest34, STest, STest("ab(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest35, STest, STest("aa(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest36, STest, STest("ab(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest37, STest, STest("ab(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest38, STest, STest("aaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest39, STest, STest("aba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest40, STest, STest("aab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest41, STest, STest("abb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest42, STest, STest("abc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest43, STest, STest("aaaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest44, STest, STest("abaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest45, STest, STest("aaba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest46, STest, STest("abba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest47, STest, STest("abca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest48, STest, STest("aaab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest49, STest, STest("abab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest50, STest, STest("aabb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest51, STest, STest("abbb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest52, STest, STest("abcb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest53, STest, STest("abac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest54, STest, STest("aabc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest55, STest, STest("abbc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest56, STest, STest("abcc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest57, STest, STest("abc.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest58, STest, STest("aaa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest59, STest, STest("aaa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest60, STest, STest("aaa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest61, STest, STest("aaa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest62, STest, STest("aaa*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest63, STest, STest("aaa??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest64, STest, STest("aba+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest65, STest, STest("aba*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest66, STest, STest("aba?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest67, STest, STest("aba+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest68, STest, STest("aba*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest69, STest, STest("aba??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest70, STest, STest("aab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest71, STest, STest("aab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest72, STest, STest("aab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest73, STest, STest("aab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest74, STest, STest("aab*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest75, STest, STest("aab??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest76, STest, STest("abb+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest77, STest, STest("abb*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest78, STest, STest("abb?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest79, STest, STest("abb+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest80, STest, STest("abb*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest81, STest, STest("abb??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest82, STest, STest("abc+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest83, STest, STest("abc*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest84, STest, STest("abc?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest85, STest, STest("abc+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest86, STest, STest("abc*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest87, STest, STest("abc??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest88, STest, STest("aaa|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest89, STest, STest("aba|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest90, STest, STest("aab|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest91, STest, STest("abb|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest92, STest, STest("abc|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest93, STest, STest("aaa|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest94, STest, STest("aba|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest95, STest, STest("aab|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest96, STest, STest("abb|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest97, STest, STest("abc|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest98, STest, STest("aba|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest99, STest, STest("aab|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest100, STest, STest("abb|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest101, STest, STest("abc|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest102, STest, STest("abc|.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest103, STest, STest("aa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest104, STest, STest("aa*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest105, STest, STest("aa?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest106, STest, STest("aa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest107, STest, STest("aa*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest108, STest, STest("aa??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest109, STest, STest("ab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest110, STest, STest("ab*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest111, STest, STest("ab?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest112, STest, STest("ab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest113, STest, STest("ab*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest114, STest, STest("ab??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest115, STest, STest("aa|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest116, STest, STest("ab|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest117, STest, STest("aa|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest118, STest, STest("ab|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest119, STest, STest("ab|(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest120, STest, STest("aa|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest121, STest, STest("ab|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest122, STest, STest("aa|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest123, STest, STest("ab|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest124, STest, STest("ab|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest125, STest, STest("aa|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest126, STest, STest("ab|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest127, STest, STest("aa|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest128, STest, STest("ab|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest129, STest, STest("ab|ca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest130, STest, STest("aa|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest131, STest, STest("ab|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest132, STest, STest("aa|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest133, STest, STest("ab|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest134, STest, STest("ab|cb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest135, STest, STest("ab|ac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest136, STest, STest("aa|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest137, STest, STest("ab|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest138, STest, STest("ab|cc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest139, STest, STest("ab|c.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest140, STest, STest("aa|a+")) {
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

SCOPE_TEST(autoPatternTest141) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest142) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest143, STest, STest("aa|a+?")) {
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

SCOPE_TEST(autoPatternTest144) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest145) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest146, STest, STest("ab|a+")) {
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

SCOPE_TEST(autoPatternTest147) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest148) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest149, STest, STest("ab|a+?")) {
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

SCOPE_TEST(autoPatternTest150) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest151) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest152, STest, STest("aa|b+")) {
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

SCOPE_TEST(autoPatternTest153) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest154) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest155, STest, STest("aa|b+?")) {
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

SCOPE_TEST(autoPatternTest156) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest157) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest158, STest, STest("ab|b+")) {
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

SCOPE_TEST(autoPatternTest159) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest160) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest161, STest, STest("ab|b+?")) {
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

SCOPE_TEST(autoPatternTest162) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest163) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest164, STest, STest("ab|c+")) {
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

SCOPE_TEST(autoPatternTest165) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest166) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest167, STest, STest("ab|c+?")) {
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

SCOPE_TEST(autoPatternTest168) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest169) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest170, STest, STest("aa|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest171, STest, STest("ab|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest172, STest, STest("aa|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest173, STest, STest("ab|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest174, STest, STest("ab|c|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest175, STest, STest("aa|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest176, STest, STest("ab|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest177, STest, STest("aa|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest178, STest, STest("ab|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest179, STest, STest("ab|c|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest180, STest, STest("ab|a|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest181, STest, STest("aa|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest182, STest, STest("ab|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest183, STest, STest("ab|c|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest184, STest, STest("ab|c|.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest185, STest, STest("a+(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest186, STest, STest("a*(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest187, STest, STest("a?(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest188, STest, STest("a+?(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest189, STest, STest("a*?(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest190, STest, STest("a??(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest191, STest, STest("a+(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest192, STest, STest("a*(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest193, STest, STest("a?(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest194, STest, STest("a+?(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest195, STest, STest("a*?(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest196, STest, STest("a??(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest197, STest, STest("a+a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest198, STest, STest("a*a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest199, STest, STest("a?a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest200, STest, STest("a+?a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest201, STest, STest("a*?a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest202, STest, STest("a??a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest203, STest, STest("a+b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest204, STest, STest("a*b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest205, STest, STest("a?b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest206, STest, STest("a+?b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest207, STest, STest("a*?b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest208, STest, STest("a??b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest209, STest, STest("a+aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest210, STest, STest("a*aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest211, STest, STest("a?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest212, STest, STest("a+?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest213, STest, STest("a*?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest214, STest, STest("a??aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest215, STest, STest("a+ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest216, STest, STest("a*ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest217, STest, STest("a?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest218, STest, STest("a+?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest219, STest, STest("a*?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest220, STest, STest("a??ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest221, STest, STest("a+ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest222, STest, STest("a*ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest223, STest, STest("a?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest224, STest, STest("a+?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest225, STest, STest("a*?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest226, STest, STest("a??ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest227, STest, STest("a+bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest228, STest, STest("a*bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest229, STest, STest("a?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest230, STest, STest("a+?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest231, STest, STest("a*?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest232, STest, STest("a??bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest233, STest, STest("a+bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest234, STest, STest("a*bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest235, STest, STest("a?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest236, STest, STest("a+?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest237, STest, STest("a*?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest238, STest, STest("a??bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest239, STest, STest("a+a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest240, STest, STest("a*a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest241, STest, STest("a?a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest242, STest, STest("a+?a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest243, STest, STest("a*?a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest244, STest, STest("a??a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest245, STest, STest("a+a*")) {
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
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest247) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest248, STest, STest("a+?a*")) {
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

SCOPE_TEST(autoPatternTest249) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest250) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest251, STest, STest("a+a?")) {
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

SCOPE_TEST(autoPatternTest252) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest253) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest254, STest, STest("a+?a?")) {
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

SCOPE_TEST(autoPatternTest255) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest256) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest257, STest, STest("a+a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest258, STest, STest("a*a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest259, STest, STest("a?a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest260, STest, STest("a+?a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest261, STest, STest("a*?a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest262, STest, STest("a??a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest263, STest, STest("a+a*?")) {
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

SCOPE_TEST(autoPatternTest264) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest265) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest266, STest, STest("a+?a*?")) {
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

SCOPE_TEST(autoPatternTest267) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest268) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest269, STest, STest("a+a??")) {
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

SCOPE_TEST(autoPatternTest270) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest271) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest272, STest, STest("a+?a??")) {
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

SCOPE_TEST(autoPatternTest273) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest274) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest275, STest, STest("a+b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest276, STest, STest("a*b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest277, STest, STest("a?b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest278, STest, STest("a+?b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest279, STest, STest("a*?b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest280, STest, STest("a??b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest281, STest, STest("a+b*")) {
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

SCOPE_TEST(autoPatternTest282) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest283) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest284, STest, STest("a+?b*")) {
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

SCOPE_TEST(autoPatternTest285) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest286) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest287, STest, STest("a+b?")) {
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

SCOPE_TEST(autoPatternTest288) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest289) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest290, STest, STest("a+?b?")) {
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

SCOPE_TEST(autoPatternTest291) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest292) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest293, STest, STest("a+b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest294, STest, STest("a*b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest295, STest, STest("a?b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest296, STest, STest("a+?b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest297, STest, STest("a*?b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest298, STest, STest("a??b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest299, STest, STest("a+b*?")) {
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

SCOPE_TEST(autoPatternTest300) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest301) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest302, STest, STest("a+?b*?")) {
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

SCOPE_TEST(autoPatternTest303) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest304) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest305, STest, STest("a+b??")) {
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

SCOPE_TEST(autoPatternTest306) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest307) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest308, STest, STest("a+?b??")) {
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

SCOPE_TEST(autoPatternTest309) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest310) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest311, STest, STest("a+a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest312, STest, STest("a*a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest313, STest, STest("a?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest314, STest, STest("a+?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest315, STest, STest("a*?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest316, STest, STest("a??a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest317, STest, STest("a+b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest318, STest, STest("a*b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest319, STest, STest("a?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest320, STest, STest("a+?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest321, STest, STest("a*?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest322, STest, STest("a??b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest323, STest, STest("a+a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest324, STest, STest("a*a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest325, STest, STest("a?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest326, STest, STest("a+?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest327, STest, STest("a*?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest328, STest, STest("a??a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest329, STest, STest("a+b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest330, STest, STest("a*b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest331, STest, STest("a?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest332, STest, STest("a+?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest333, STest, STest("a*?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest334, STest, STest("a??b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest335, STest, STest("a+b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest336, STest, STest("a*b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest337, STest, STest("a?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest338, STest, STest("a+?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest339, STest, STest("a*?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest340, STest, STest("a??b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest341, STest, STest("a+|(a)")) {
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

SCOPE_TEST(autoPatternTest342) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest343) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest344, STest, STest("a+?|(a)")) {
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

SCOPE_TEST(autoPatternTest345) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest346) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest347, STest, STest("a+|(b)")) {
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

SCOPE_TEST(autoPatternTest348) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest349) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest350, STest, STest("a+?|(b)")) {
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

SCOPE_TEST(autoPatternTest351) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest352) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest353, STest, STest("a+|a")) {
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

SCOPE_TEST(autoPatternTest354) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest355) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest356, STest, STest("a+?|a")) {
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

SCOPE_TEST(autoPatternTest357) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest358) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest359, STest, STest("a+|b")) {
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

SCOPE_TEST(autoPatternTest360) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest361) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest362, STest, STest("a+?|b")) {
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

SCOPE_TEST(autoPatternTest363) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest364) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest365, STest, STest("a+|aa")) {
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

SCOPE_TEST(autoPatternTest366) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest367) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest368, STest, STest("a+?|aa")) {
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

SCOPE_TEST(autoPatternTest369) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest370) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest371, STest, STest("a+|ba")) {
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

SCOPE_TEST(autoPatternTest372) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest373) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest374, STest, STest("a+?|ba")) {
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

SCOPE_TEST(autoPatternTest375) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest376) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest377, STest, STest("a+|ab")) {
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

SCOPE_TEST(autoPatternTest378) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest379) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest380, STest, STest("a+?|ab")) {
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

SCOPE_TEST(autoPatternTest381) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest382) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest383, STest, STest("a+|bb")) {
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

SCOPE_TEST(autoPatternTest384) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest385) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest386, STest, STest("a+?|bb")) {
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

SCOPE_TEST(autoPatternTest387) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest388) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest389, STest, STest("a+|bc")) {
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

SCOPE_TEST(autoPatternTest390) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest391) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest392, STest, STest("a+?|bc")) {
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

SCOPE_TEST(autoPatternTest393) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest394) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest395, STest, STest("a+|a+")) {
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

SCOPE_TEST(autoPatternTest396) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest397) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest398, STest, STest("a+?|a+")) {
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

SCOPE_TEST(autoPatternTest399) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest400) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest401) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest402) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest403) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest404) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest405) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest406) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest407) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest408) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest409) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest410) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest411) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest412) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest413, STest, STest("a+|a+?")) {
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

SCOPE_TEST(autoPatternTest414) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest415) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest416, STest, STest("a+?|a+?")) {
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

SCOPE_TEST(autoPatternTest417) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest418) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest419) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest420) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest421) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest422) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest423) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest424) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest425) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest426) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest427) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest428) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest429) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest430) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest431, STest, STest("a+|b+")) {
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

SCOPE_TEST(autoPatternTest432) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest433) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest434, STest, STest("a+?|b+")) {
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

SCOPE_TEST(autoPatternTest435) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest436) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest437) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest438) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest439) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest440) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest441) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest442) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest443) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest444) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest445) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest446) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest447) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest448) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest449, STest, STest("a+|b+?")) {
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

SCOPE_TEST(autoPatternTest450) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest451) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest452, STest, STest("a+?|b+?")) {
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

SCOPE_TEST(autoPatternTest453) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest454) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest455) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest456) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest457) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest458) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest459) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest460) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest461) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest462) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest463) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest464) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest465) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest466) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest467, STest, STest("a+|a|a")) {
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

SCOPE_TEST(autoPatternTest468) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest469) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest470, STest, STest("a+?|a|a")) {
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

SCOPE_TEST(autoPatternTest471) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest472) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest473, STest, STest("a+|b|a")) {
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

SCOPE_TEST(autoPatternTest474) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest475) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest476, STest, STest("a+?|b|a")) {
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

SCOPE_TEST(autoPatternTest477) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest478) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest479, STest, STest("a+|a|b")) {
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

SCOPE_TEST(autoPatternTest480) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest481) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest482, STest, STest("a+?|a|b")) {
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

SCOPE_TEST(autoPatternTest483) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest484) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest485, STest, STest("a+|b|b")) {
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

SCOPE_TEST(autoPatternTest486) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest487) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest488, STest, STest("a+?|b|b")) {
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

SCOPE_TEST(autoPatternTest489) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest490) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest491, STest, STest("a+|b|c")) {
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

SCOPE_TEST(autoPatternTest492) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest493) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest494, STest, STest("a+?|b|c")) {
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

SCOPE_TEST(autoPatternTest495) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest496) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest497, STest, STest("a|a(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest498, STest, STest("a|b(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest499, STest, STest("a|a(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest500, STest, STest("a|b(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest501, STest, STest("a|b(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest502, STest, STest("a|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest503, STest, STest("a|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest504, STest, STest("a|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest505, STest, STest("a|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest506, STest, STest("a|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest507, STest, STest("a|aaa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest508, STest, STest("a|baa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest509, STest, STest("a|aba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest510, STest, STest("a|bba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest511, STest, STest("a|bca")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest512, STest, STest("a|aab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest513, STest, STest("a|bab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest514, STest, STest("a|abb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest515, STest, STest("a|bbb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest516, STest, STest("a|bcb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest517, STest, STest("a|bac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest518, STest, STest("a|abc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest519, STest, STest("a|bbc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest520, STest, STest("a|bcc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest521, STest, STest("a|bc.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest522, STest, STest("a|aa+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest523, STest, STest("a|aa*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest524, STest, STest("a|aa?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest525, STest, STest("a|aa+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest526, STest, STest("a|aa*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest527, STest, STest("a|aa??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest528, STest, STest("a|ba+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest529, STest, STest("a|ba*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest530, STest, STest("a|ba?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest531, STest, STest("a|ba+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest532, STest, STest("a|ba*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest533, STest, STest("a|ba??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest534, STest, STest("a|ab+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest535, STest, STest("a|ab*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest536, STest, STest("a|ab?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest537, STest, STest("a|ab+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest538, STest, STest("a|ab*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest539, STest, STest("a|ab??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest540, STest, STest("a|bb+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest541, STest, STest("a|bb*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest542, STest, STest("a|bb?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest543, STest, STest("a|bb+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest544, STest, STest("a|bb*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest545, STest, STest("a|bb??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest546, STest, STest("a|bc+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest547, STest, STest("a|bc*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest548, STest, STest("a|bc?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest549, STest, STest("a|bc+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest550, STest, STest("a|bc*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest551, STest, STest("a|bc??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest552, STest, STest("a|aa|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest553, STest, STest("a|ba|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest554, STest, STest("a|ab|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest555, STest, STest("a|bb|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest556, STest, STest("a|bc|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest557, STest, STest("a|aa|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest558, STest, STest("a|ba|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest559, STest, STest("a|ab|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest560, STest, STest("a|bb|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest561, STest, STest("a|bc|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest562, STest, STest("a|ba|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest563, STest, STest("a|ab|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest564, STest, STest("a|bb|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest565, STest, STest("a|bc|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest566, STest, STest("a|bc|.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest567, STest, STest("a|a+")) {
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

SCOPE_TEST(autoPatternTest568) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest569) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest570, STest, STest("a|a+?")) {
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

SCOPE_TEST(autoPatternTest571) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest572) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest573, STest, STest("a|b+")) {
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

SCOPE_TEST(autoPatternTest574) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest575) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest576, STest, STest("a|b+?")) {
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

SCOPE_TEST(autoPatternTest577) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest578) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest579, STest, STest("a|a|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest580, STest, STest("a|b|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest581, STest, STest("a|a|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest582, STest, STest("a|b|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest583, STest, STest("a|b|(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest584, STest, STest("a|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest585, STest, STest("a|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest586, STest, STest("a|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest587, STest, STest("a|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest588, STest, STest("a|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest589, STest, STest("a|a|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest590, STest, STest("a|b|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest591, STest, STest("a|a|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest592, STest, STest("a|b|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest593, STest, STest("a|b|ca")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest594, STest, STest("a|a|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest595, STest, STest("a|b|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest596, STest, STest("a|a|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest597, STest, STest("a|b|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest598, STest, STest("a|b|cb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest599, STest, STest("a|b|ac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest600, STest, STest("a|a|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest601, STest, STest("a|b|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest602, STest, STest("a|b|cc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest603, STest, STest("a|b|c.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest604, STest, STest("a|a|a+")) {
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

SCOPE_TEST(autoPatternTest605) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest606) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest607, STest, STest("a|a|a+?")) {
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

SCOPE_TEST(autoPatternTest608) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest609) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest610, STest, STest("a|b|a+")) {
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

SCOPE_TEST(autoPatternTest611) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest612) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest613, STest, STest("a|b|a+?")) {
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

SCOPE_TEST(autoPatternTest614) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest615) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest616, STest, STest("a|a|b+")) {
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

SCOPE_TEST(autoPatternTest617) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest618) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest619, STest, STest("a|a|b+?")) {
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

SCOPE_TEST(autoPatternTest620) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest621) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|a|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest622, STest, STest("a|b|b+")) {
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

SCOPE_TEST(autoPatternTest623) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest624) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest625, STest, STest("a|b|b+?")) {
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

SCOPE_TEST(autoPatternTest626) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest627) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest628, STest, STest("a|b|c+")) {
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

SCOPE_TEST(autoPatternTest629) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest630) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest631, STest, STest("a|b|c+?")) {
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

SCOPE_TEST(autoPatternTest632) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest633) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest634, STest, STest("a|a|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest635, STest, STest("a|b|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest636, STest, STest("a|a|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest637, STest, STest("a|b|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest638, STest, STest("a|b|c|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest639, STest, STest("a|a|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest640, STest, STest("a|b|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest641, STest, STest("a|a|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest642, STest, STest("a|b|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest643, STest, STest("a|b|c|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest644, STest, STest("a|b|a|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest645, STest, STest("a|a|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest646, STest, STest("a|b|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest647, STest, STest("a|b|c|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest648, STest, STest("a|b|c|.")) {
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

