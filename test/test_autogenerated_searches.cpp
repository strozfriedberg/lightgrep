#include <scope/test.h>

#include "nfabuilder.h"
#include "parsetree.h"

#include "stest.h"

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

SCOPE_TEST(autoPatternTest10) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest11, STest, STest("a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest12, STest, STest("a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest13, STest, STest("a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest14) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest15, STest, STest("a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest16, STest, STest("a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest17, STest, STest("a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest18, STest, STest("a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest19, STest, STest("a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest20, STest, STest("(aa)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest21, STest, STest("(ab)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest22, STest, STest("(a+)")) {
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

SCOPE_TEST(autoPatternTest23) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest24) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest25, STest, STest("(a+?)")) {
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

SCOPE_TEST(autoPatternTest26) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest27) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a??)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest28) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a{0,1})", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest29, STest, STest("(a{2})")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest30, STest, STest("(a{1,2})")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest31, STest, STest("(a{2,})")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest32) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a{0,1}?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest33, STest, STest("(a{2}?)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest34, STest, STest("(a{1,2}?)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest35, STest, STest("(a{2,}?)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest36, STest, STest("(a|a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest37, STest, STest("(a|b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest38, STest, STest("((a))")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest39, STest, STest("(a)(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest40, STest, STest("(a)(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest41, STest, STest("(a)+")) {
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

SCOPE_TEST(autoPatternTest42) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest43) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest44, STest, STest("(a)+?")) {
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

SCOPE_TEST(autoPatternTest45) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest46) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest47) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a){0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest48, STest, STest("(a){2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest49, STest, STest("(a){1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest50, STest, STest("(a){2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest51) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a){0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest52, STest, STest("(a){2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest53, STest, STest("(a){1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest54, STest, STest("(a){2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest55, STest, STest("(a)|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest56, STest, STest("(a)|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest57, STest, STest("aa(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest58, STest, STest("ab(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest59, STest, STest("aa(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest60, STest, STest("ab(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest61, STest, STest("ab(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest62, STest, STest("aaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest63, STest, STest("aba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest64, STest, STest("aab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest65, STest, STest("abb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest66, STest, STest("abc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest67, STest, STest("aaaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest68, STest, STest("abaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest69, STest, STest("aaba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest70, STest, STest("abba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest71, STest, STest("abca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest72, STest, STest("aaab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest73, STest, STest("abab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest74, STest, STest("aabb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest75, STest, STest("abbb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest76, STest, STest("abcb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest77, STest, STest("abac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest78, STest, STest("aabc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest79, STest, STest("abbc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest80, STest, STest("abcc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest81, STest, STest("abc.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest82, STest, STest("aaa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest83, STest, STest("aaa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest84, STest, STest("aaa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest85, STest, STest("aaa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest86, STest, STest("aaa*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest87, STest, STest("aaa??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest88, STest, STest("aaa{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest89, STest, STest("aaa{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest90, STest, STest("aaa{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest91, STest, STest("aaa{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest92, STest, STest("aaa{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest93, STest, STest("aaa{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest94, STest, STest("aaa{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest95, STest, STest("aaa{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest96, STest, STest("aba+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest97, STest, STest("aba*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest98, STest, STest("aba?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest99, STest, STest("aba+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest100, STest, STest("aba*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest101, STest, STest("aba??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest102, STest, STest("aba{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest103, STest, STest("aba{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest104, STest, STest("aba{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest105, STest, STest("aba{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest106, STest, STest("aba{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest107, STest, STest("aba{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest108, STest, STest("aba{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest109, STest, STest("aba{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest110, STest, STest("aab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest111, STest, STest("aab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest112, STest, STest("aab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest113, STest, STest("aab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest114, STest, STest("aab*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest115, STest, STest("aab??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest116, STest, STest("aab{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest117, STest, STest("aab{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest118, STest, STest("aab{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest119, STest, STest("aab{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest120, STest, STest("aab{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest121, STest, STest("aab{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest122, STest, STest("aab{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest123, STest, STest("aab{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest124, STest, STest("abb+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest125, STest, STest("abb*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest126, STest, STest("abb?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest127, STest, STest("abb+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest128, STest, STest("abb*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest129, STest, STest("abb??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest130, STest, STest("abb{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest131, STest, STest("abb{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest132, STest, STest("abb{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest133, STest, STest("abb{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest134, STest, STest("abb{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest135, STest, STest("abb{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest136, STest, STest("abb{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest137, STest, STest("abb{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest138, STest, STest("abc+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest139, STest, STest("abc*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest140, STest, STest("abc?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest141, STest, STest("abc+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest142, STest, STest("abc*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest143, STest, STest("abc??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest144, STest, STest("abc{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest145, STest, STest("abc{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest146, STest, STest("abc{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest147, STest, STest("abc{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest148, STest, STest("abc{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest149, STest, STest("abc{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest150, STest, STest("abc{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest151, STest, STest("abc{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest152, STest, STest("aaa|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest153, STest, STest("aba|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest154, STest, STest("aab|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest155, STest, STest("abb|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest156, STest, STest("abc|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest157, STest, STest("aaa|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest158, STest, STest("aba|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest159, STest, STest("aab|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest160, STest, STest("abb|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest161, STest, STest("abc|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest162, STest, STest("aba|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest163, STest, STest("aab|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest164, STest, STest("abb|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest165, STest, STest("abc|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest166, STest, STest("abc|.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest167, STest, STest("aa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest168, STest, STest("aa*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest169, STest, STest("aa?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest170, STest, STest("aa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest171, STest, STest("aa*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest172, STest, STest("aa??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest173, STest, STest("aa{0,1}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest174, STest, STest("aa{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest175, STest, STest("aa{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest176, STest, STest("aa{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest177, STest, STest("aa{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest178, STest, STest("aa{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest179, STest, STest("aa{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest180, STest, STest("aa{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest181, STest, STest("ab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest182, STest, STest("ab*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest183, STest, STest("ab?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest184, STest, STest("ab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest185, STest, STest("ab*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest186, STest, STest("ab??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest187, STest, STest("ab{0,1}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest188, STest, STest("ab{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest189, STest, STest("ab{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest190, STest, STest("ab{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest191, STest, STest("ab{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest192, STest, STest("ab{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest193, STest, STest("ab{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest194, STest, STest("ab{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest195, STest, STest("aa|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest196, STest, STest("ab|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest197, STest, STest("aa|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest198, STest, STest("ab|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest199, STest, STest("ab|(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest200, STest, STest("aa|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest201, STest, STest("ab|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest202, STest, STest("aa|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest203, STest, STest("ab|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest204, STest, STest("ab|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest205, STest, STest("aa|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest206, STest, STest("ab|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest207, STest, STest("aa|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest208, STest, STest("ab|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest209, STest, STest("ab|ca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest210, STest, STest("aa|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest211, STest, STest("ab|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest212, STest, STest("aa|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest213, STest, STest("ab|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest214, STest, STest("ab|cb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest215, STest, STest("ab|ac")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest216, STest, STest("aa|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest217, STest, STest("ab|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest218, STest, STest("ab|cc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest219, STest, STest("ab|c.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest220, STest, STest("aa|a+")) {
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

SCOPE_TEST(autoPatternTest221) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest222) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest223, STest, STest("aa|a+?")) {
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

SCOPE_TEST(autoPatternTest224) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest225) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest226) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest227, STest, STest("aa|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest228, STest, STest("aa|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest229, STest, STest("aa|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest230) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest231, STest, STest("aa|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest232, STest, STest("aa|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest233, STest, STest("aa|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest234, STest, STest("ab|a+")) {
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

SCOPE_TEST(autoPatternTest235) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest236) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest237, STest, STest("ab|a+?")) {
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

SCOPE_TEST(autoPatternTest238) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest239) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest240) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest241, STest, STest("ab|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest242, STest, STest("ab|a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest243, STest, STest("ab|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest244) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest245, STest, STest("ab|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest246, STest, STest("ab|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest247, STest, STest("ab|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest248, STest, STest("aa|b+")) {
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

SCOPE_TEST(autoPatternTest249) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest250) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest251, STest, STest("aa|b+?")) {
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

SCOPE_TEST(autoPatternTest252) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest253) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest254) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest255, STest, STest("aa|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest256, STest, STest("aa|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest257, STest, STest("aa|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest258) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest259, STest, STest("aa|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest260, STest, STest("aa|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest261, STest, STest("aa|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest262, STest, STest("ab|b+")) {
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

SCOPE_TEST(autoPatternTest263) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest264) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest265, STest, STest("ab|b+?")) {
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

SCOPE_TEST(autoPatternTest266) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest267) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest268) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest269, STest, STest("ab|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest270, STest, STest("ab|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest271, STest, STest("ab|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest272) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest273, STest, STest("ab|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest274, STest, STest("ab|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest275, STest, STest("ab|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest276, STest, STest("ab|c+")) {
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

SCOPE_TEST(autoPatternTest277) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest278) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest279, STest, STest("ab|c+?")) {
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

SCOPE_TEST(autoPatternTest280) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest281) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest282) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest283, STest, STest("ab|c{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest284, STest, STest("ab|c{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest285, STest, STest("ab|c{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 3, 0), fixture.Hits[4]);
}

SCOPE_TEST(autoPatternTest286) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|c{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest287, STest, STest("ab|c{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest288, STest, STest("ab|c{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest289, STest, STest("ab|c{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest290, STest, STest("aa|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest291, STest, STest("ab|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest292, STest, STest("aa|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest293, STest, STest("ab|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest294, STest, STest("ab|c|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest295, STest, STest("aa|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest296, STest, STest("ab|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest297, STest, STest("aa|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest298, STest, STest("ab|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest299, STest, STest("ab|c|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest300, STest, STest("ab|a|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest301, STest, STest("aa|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest302, STest, STest("ab|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest303, STest, STest("ab|c|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest304, STest, STest("ab|c|.")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest305, STest, STest("a+(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest306, STest, STest("a*(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest307, STest, STest("a?(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest308, STest, STest("a+?(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest309, STest, STest("a*?(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest310, STest, STest("a??(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest311, STest, STest("a{0,1}(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest312, STest, STest("a{2}(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest313, STest, STest("a{1,2}(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest314, STest, STest("a{2,}(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest315, STest, STest("a{0,1}?(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest316, STest, STest("a{2}?(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest317, STest, STest("a{1,2}?(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest318, STest, STest("a{2,}?(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest319, STest, STest("a+(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest320, STest, STest("a*(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest321, STest, STest("a?(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest322, STest, STest("a+?(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest323, STest, STest("a*?(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest324, STest, STest("a??(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest325, STest, STest("a{0,1}(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest326, STest, STest("a{2}(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest327, STest, STest("a{1,2}(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest328, STest, STest("a{2,}(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest329, STest, STest("a{0,1}?(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest330, STest, STest("a{2}?(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest331, STest, STest("a{1,2}?(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest332, STest, STest("a{2,}?(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest333, STest, STest("a+a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest334, STest, STest("a*a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest335, STest, STest("a?a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest336, STest, STest("a+?a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest337, STest, STest("a*?a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest338, STest, STest("a??a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest339, STest, STest("a{0,1}a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest340, STest, STest("a{2}a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest341, STest, STest("a{1,2}a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest342, STest, STest("a{2,}a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest343, STest, STest("a{0,1}?a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest344, STest, STest("a{2}?a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest345, STest, STest("a{1,2}?a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest346, STest, STest("a{2,}?a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest347, STest, STest("a+b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest348, STest, STest("a*b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest349, STest, STest("a?b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest350, STest, STest("a+?b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest351, STest, STest("a*?b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest352, STest, STest("a??b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest353, STest, STest("a{0,1}b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest354, STest, STest("a{2}b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest355, STest, STest("a{1,2}b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest356, STest, STest("a{2,}b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest357, STest, STest("a{0,1}?b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest358, STest, STest("a{2}?b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest359, STest, STest("a{1,2}?b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest360, STest, STest("a{2,}?b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest361, STest, STest("a+aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest362, STest, STest("a*aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest363, STest, STest("a?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest364, STest, STest("a+?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest365, STest, STest("a*?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest366, STest, STest("a??aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest367, STest, STest("a{0,1}aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest368, STest, STest("a{2}aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest369, STest, STest("a{1,2}aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest370, STest, STest("a{2,}aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest371, STest, STest("a{0,1}?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest372, STest, STest("a{2}?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest373, STest, STest("a{1,2}?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest374, STest, STest("a{2,}?aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest375, STest, STest("a+ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest376, STest, STest("a*ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest377, STest, STest("a?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest378, STest, STest("a+?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest379, STest, STest("a*?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest380, STest, STest("a??ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest381, STest, STest("a{0,1}ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest382, STest, STest("a{2}ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest383, STest, STest("a{1,2}ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest384, STest, STest("a{2,}ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest385, STest, STest("a{0,1}?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest386, STest, STest("a{2}?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest387, STest, STest("a{1,2}?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest388, STest, STest("a{2,}?ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest389, STest, STest("a+ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest390, STest, STest("a*ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest391, STest, STest("a?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest392, STest, STest("a+?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest393, STest, STest("a*?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest394, STest, STest("a??ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest395, STest, STest("a{0,1}ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest396, STest, STest("a{2}ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest397, STest, STest("a{1,2}ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest398, STest, STest("a{2,}ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest399, STest, STest("a{0,1}?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest400, STest, STest("a{2}?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest401, STest, STest("a{1,2}?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest402, STest, STest("a{2,}?ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest403, STest, STest("a+bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest404, STest, STest("a*bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest405, STest, STest("a?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest406, STest, STest("a+?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest407, STest, STest("a*?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest408, STest, STest("a??bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest409, STest, STest("a{0,1}bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest410, STest, STest("a{2}bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest411, STest, STest("a{1,2}bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest412, STest, STest("a{2,}bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest413, STest, STest("a{0,1}?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest414, STest, STest("a{2}?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest415, STest, STest("a{1,2}?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest416, STest, STest("a{2,}?bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest417, STest, STest("a+bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest418, STest, STest("a*bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest419, STest, STest("a?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest420, STest, STest("a+?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest421, STest, STest("a*?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest422, STest, STest("a??bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest423, STest, STest("a{0,1}bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest424, STest, STest("a{2}bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest425, STest, STest("a{1,2}bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest426, STest, STest("a{2,}bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest427, STest, STest("a{0,1}?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest428, STest, STest("a{2}?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest429, STest, STest("a{1,2}?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest430, STest, STest("a{2,}?bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest431, STest, STest("a+a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest432, STest, STest("a*a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest433, STest, STest("a?a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest434, STest, STest("a+?a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest435, STest, STest("a*?a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest436, STest, STest("a??a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest437, STest, STest("a{0,1}a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest438, STest, STest("a{2}a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest439, STest, STest("a{1,2}a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest440, STest, STest("a{2,}a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest441, STest, STest("a{0,1}?a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest442, STest, STest("a{2}?a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest443, STest, STest("a{1,2}?a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest444, STest, STest("a{2,}?a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest445, STest, STest("a+a*")) {
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

SCOPE_TEST(autoPatternTest446) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest447) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest448, STest, STest("a+?a*")) {
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

SCOPE_TEST(autoPatternTest449) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest450) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest451) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest452, STest, STest("a{2}a*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest453, STest, STest("a{1,2}a*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest454, STest, STest("a{2,}a*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest455) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest456, STest, STest("a{2}?a*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest457, STest, STest("a{1,2}?a*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest458, STest, STest("a{2,}?a*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest459, STest, STest("a+a?")) {
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

SCOPE_TEST(autoPatternTest460) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest461) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest462, STest, STest("a+?a?")) {
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

SCOPE_TEST(autoPatternTest463) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest464) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest465) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest466, STest, STest("a{2}a?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest467, STest, STest("a{1,2}a?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest468, STest, STest("a{2,}a?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest469) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest470, STest, STest("a{2}?a?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest471, STest, STest("a{1,2}?a?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest472, STest, STest("a{2,}?a?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest473, STest, STest("a+a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest474, STest, STest("a*a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest475, STest, STest("a?a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest476, STest, STest("a+?a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest477, STest, STest("a*?a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest478, STest, STest("a??a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest479, STest, STest("a{0,1}a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest480, STest, STest("a{2}a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest481, STest, STest("a{1,2}a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest482, STest, STest("a{2,}a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest483, STest, STest("a{0,1}?a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest484, STest, STest("a{2}?a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest485, STest, STest("a{1,2}?a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest486, STest, STest("a{2,}?a+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest487, STest, STest("a+a*?")) {
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

SCOPE_TEST(autoPatternTest488) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest489) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest490, STest, STest("a+?a*?")) {
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

SCOPE_TEST(autoPatternTest491) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest492) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest493) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest494, STest, STest("a{2}a*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest495, STest, STest("a{1,2}a*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest496, STest, STest("a{2,}a*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest497) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest498, STest, STest("a{2}?a*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest499, STest, STest("a{1,2}?a*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest500, STest, STest("a{2,}?a*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest501, STest, STest("a+a??")) {
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

SCOPE_TEST(autoPatternTest502) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest503) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest504, STest, STest("a+?a??")) {
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

SCOPE_TEST(autoPatternTest505) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest506) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest507) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest508, STest, STest("a{2}a??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest509, STest, STest("a{1,2}a??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest510, STest, STest("a{2,}a??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest511) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest512, STest, STest("a{2}?a??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest513, STest, STest("a{1,2}?a??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest514, STest, STest("a{2,}?a??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest515, STest, STest("a+a{0,1}")) {
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

SCOPE_TEST(autoPatternTest516) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest517) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest518, STest, STest("a+?a{0,1}")) {
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

SCOPE_TEST(autoPatternTest519) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest520) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest521) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest522, STest, STest("a{2}a{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest523, STest, STest("a{1,2}a{0,1}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest524, STest, STest("a{2,}a{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest525) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest526, STest, STest("a{2}?a{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest527, STest, STest("a{1,2}?a{0,1}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest528, STest, STest("a{2,}?a{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest529, STest, STest("a+a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest530, STest, STest("a*a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest531, STest, STest("a?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest532, STest, STest("a+?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest533, STest, STest("a*?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest534, STest, STest("a??a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest535, STest, STest("a{0,1}a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest536, STest, STest("a{2}a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest537, STest, STest("a{1,2}a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest538, STest, STest("a{2,}a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest539, STest, STest("a{0,1}?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest540, STest, STest("a{2}?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest541, STest, STest("a{1,2}?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest542, STest, STest("a{2,}?a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest543, STest, STest("a+a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest544, STest, STest("a*a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest545, STest, STest("a?a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest546, STest, STest("a+?a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest547, STest, STest("a*?a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest548, STest, STest("a??a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest549, STest, STest("a{0,1}a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest550, STest, STest("a{2}a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest551, STest, STest("a{1,2}a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest552, STest, STest("a{2,}a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest553, STest, STest("a{0,1}?a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest554, STest, STest("a{2}?a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest555, STest, STest("a{1,2}?a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest556, STest, STest("a{2,}?a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest557, STest, STest("a+a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest558, STest, STest("a*a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest559, STest, STest("a?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest560, STest, STest("a+?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest561, STest, STest("a*?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest562, STest, STest("a??a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest563, STest, STest("a{0,1}a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest564, STest, STest("a{2}a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest565, STest, STest("a{1,2}a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest566, STest, STest("a{2,}a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest567, STest, STest("a{0,1}?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest568, STest, STest("a{2}?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest569, STest, STest("a{1,2}?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest570, STest, STest("a{2,}?a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest571, STest, STest("a+a{0,1}?")) {
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

SCOPE_TEST(autoPatternTest572) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest573) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest574, STest, STest("a+?a{0,1}?")) {
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

SCOPE_TEST(autoPatternTest575) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest576) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest577) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest578, STest, STest("a{2}a{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest579, STest, STest("a{1,2}a{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest580, STest, STest("a{2,}a{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest581) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest582, STest, STest("a{2}?a{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest583, STest, STest("a{1,2}?a{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest584, STest, STest("a{2,}?a{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest585, STest, STest("a+a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest586, STest, STest("a*a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest587, STest, STest("a?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest588, STest, STest("a+?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest589, STest, STest("a*?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest590, STest, STest("a??a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest591, STest, STest("a{0,1}a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest592, STest, STest("a{2}a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest593, STest, STest("a{1,2}a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest594, STest, STest("a{2,}a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest595, STest, STest("a{0,1}?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest596, STest, STest("a{2}?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest597, STest, STest("a{1,2}?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest598, STest, STest("a{2,}?a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest599, STest, STest("a+a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest600, STest, STest("a*a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest601, STest, STest("a?a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest602, STest, STest("a+?a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest603, STest, STest("a*?a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest604, STest, STest("a??a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest605, STest, STest("a{0,1}a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest606, STest, STest("a{2}a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest607, STest, STest("a{1,2}a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest608, STest, STest("a{2,}a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest609, STest, STest("a{0,1}?a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest610, STest, STest("a{2}?a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest611, STest, STest("a{1,2}?a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest612, STest, STest("a{2,}?a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest613, STest, STest("a+a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest614, STest, STest("a*a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest615, STest, STest("a?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest616, STest, STest("a+?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest617, STest, STest("a*?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest618, STest, STest("a??a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest619, STest, STest("a{0,1}a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest620, STest, STest("a{2}a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest621, STest, STest("a{1,2}a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest622, STest, STest("a{2,}a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest623, STest, STest("a{0,1}?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest624, STest, STest("a{2}?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest625, STest, STest("a{1,2}?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest626, STest, STest("a{2,}?a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest627, STest, STest("a+b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest628, STest, STest("a*b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest629, STest, STest("a?b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest630, STest, STest("a+?b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest631, STest, STest("a*?b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest632, STest, STest("a??b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest633, STest, STest("a{0,1}b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest634, STest, STest("a{2}b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest635, STest, STest("a{1,2}b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest636, STest, STest("a{2,}b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest637, STest, STest("a{0,1}?b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest638, STest, STest("a{2}?b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest639, STest, STest("a{1,2}?b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest640, STest, STest("a{2,}?b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest641, STest, STest("a+b*")) {
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

SCOPE_TEST(autoPatternTest642) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest643) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest644, STest, STest("a+?b*")) {
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

SCOPE_TEST(autoPatternTest645) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest646) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest647) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest648, STest, STest("a{2}b*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest649, STest, STest("a{1,2}b*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest650, STest, STest("a{2,}b*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest651) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest652, STest, STest("a{2}?b*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest653, STest, STest("a{1,2}?b*")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest654, STest, STest("a{2,}?b*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest655, STest, STest("a+b?")) {
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

SCOPE_TEST(autoPatternTest656) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest657) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest658, STest, STest("a+?b?")) {
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

SCOPE_TEST(autoPatternTest659) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest660) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest661) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest662, STest, STest("a{2}b?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest663, STest, STest("a{1,2}b?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest664, STest, STest("a{2,}b?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest665) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest666, STest, STest("a{2}?b?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest667, STest, STest("a{1,2}?b?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest668, STest, STest("a{2,}?b?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest669, STest, STest("a+b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest670, STest, STest("a*b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest671, STest, STest("a?b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest672, STest, STest("a+?b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest673, STest, STest("a*?b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest674, STest, STest("a??b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest675, STest, STest("a{0,1}b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest676, STest, STest("a{2}b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest677, STest, STest("a{1,2}b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest678, STest, STest("a{2,}b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest679, STest, STest("a{0,1}?b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest680, STest, STest("a{2}?b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest681, STest, STest("a{1,2}?b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest682, STest, STest("a{2,}?b+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest683, STest, STest("a+b*?")) {
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

SCOPE_TEST(autoPatternTest684) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest685) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest686, STest, STest("a+?b*?")) {
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

SCOPE_TEST(autoPatternTest687) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest688) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest689) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest690, STest, STest("a{2}b*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest691, STest, STest("a{1,2}b*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest692, STest, STest("a{2,}b*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest693) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest694, STest, STest("a{2}?b*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest695, STest, STest("a{1,2}?b*?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest696, STest, STest("a{2,}?b*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest697, STest, STest("a+b??")) {
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

SCOPE_TEST(autoPatternTest698) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest699) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest700, STest, STest("a+?b??")) {
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

SCOPE_TEST(autoPatternTest701) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest702) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest703) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest704, STest, STest("a{2}b??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest705, STest, STest("a{1,2}b??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest706, STest, STest("a{2,}b??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest707) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest708, STest, STest("a{2}?b??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest709, STest, STest("a{1,2}?b??")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest710, STest, STest("a{2,}?b??")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest711, STest, STest("a+b{0,1}")) {
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

SCOPE_TEST(autoPatternTest712) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest713) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest714, STest, STest("a+?b{0,1}")) {
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

SCOPE_TEST(autoPatternTest715) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest716) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest717) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest718, STest, STest("a{2}b{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest719, STest, STest("a{1,2}b{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest720, STest, STest("a{2,}b{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest721) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest722, STest, STest("a{2}?b{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest723, STest, STest("a{1,2}?b{0,1}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest724, STest, STest("a{2,}?b{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest725, STest, STest("a+b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest726, STest, STest("a*b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest727, STest, STest("a?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest728, STest, STest("a+?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest729, STest, STest("a*?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest730, STest, STest("a??b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest731, STest, STest("a{0,1}b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest732, STest, STest("a{2}b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest733, STest, STest("a{1,2}b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest734, STest, STest("a{2,}b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest735, STest, STest("a{0,1}?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest736, STest, STest("a{2}?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest737, STest, STest("a{1,2}?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest738, STest, STest("a{2,}?b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest739, STest, STest("a+b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest740, STest, STest("a*b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest741, STest, STest("a?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest742, STest, STest("a+?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest743, STest, STest("a*?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest744, STest, STest("a??b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest745, STest, STest("a{0,1}b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest746, STest, STest("a{2}b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest747, STest, STest("a{1,2}b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest748, STest, STest("a{2,}b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest749, STest, STest("a{0,1}?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest750, STest, STest("a{2}?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest751, STest, STest("a{1,2}?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest752, STest, STest("a{2,}?b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest753, STest, STest("a+b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest754, STest, STest("a*b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest755, STest, STest("a?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest756, STest, STest("a+?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest757, STest, STest("a*?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest758, STest, STest("a??b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest759, STest, STest("a{0,1}b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest760, STest, STest("a{2}b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest761, STest, STest("a{1,2}b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest762, STest, STest("a{2,}b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest763, STest, STest("a{0,1}?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest764, STest, STest("a{2}?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest765, STest, STest("a{1,2}?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest766, STest, STest("a{2,}?b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest767, STest, STest("a+b{0,1}?")) {
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

SCOPE_TEST(autoPatternTest768) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest769) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest770, STest, STest("a+?b{0,1}?")) {
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

SCOPE_TEST(autoPatternTest771) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest772) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest773) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest774, STest, STest("a{2}b{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest775, STest, STest("a{1,2}b{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest776, STest, STest("a{2,}b{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest777) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest778, STest, STest("a{2}?b{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest779, STest, STest("a{1,2}?b{0,1}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest780, STest, STest("a{2,}?b{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest781, STest, STest("a+b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest782, STest, STest("a*b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest783, STest, STest("a?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest784, STest, STest("a+?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest785, STest, STest("a*?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest786, STest, STest("a??b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest787, STest, STest("a{0,1}b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest788, STest, STest("a{2}b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest789, STest, STest("a{1,2}b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest790, STest, STest("a{2,}b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest791, STest, STest("a{0,1}?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest792, STest, STest("a{2}?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest793, STest, STest("a{1,2}?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest794, STest, STest("a{2,}?b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest795, STest, STest("a+b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest796, STest, STest("a*b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest797, STest, STest("a?b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest798, STest, STest("a+?b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest799, STest, STest("a*?b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest800, STest, STest("a??b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest801, STest, STest("a{0,1}b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest802, STest, STest("a{2}b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest803, STest, STest("a{1,2}b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest804, STest, STest("a{2,}b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest805, STest, STest("a{0,1}?b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest806, STest, STest("a{2}?b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest807, STest, STest("a{1,2}?b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest808, STest, STest("a{2,}?b{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest809, STest, STest("a+b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest810, STest, STest("a*b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest811, STest, STest("a?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest812, STest, STest("a+?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest813, STest, STest("a*?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest814, STest, STest("a??b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest815, STest, STest("a{0,1}b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest816, STest, STest("a{2}b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest817, STest, STest("a{1,2}b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest818, STest, STest("a{2,}b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest819, STest, STest("a{0,1}?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest820, STest, STest("a{2}?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest821, STest, STest("a{1,2}?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest822, STest, STest("a{2,}?b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest823, STest, STest("a+a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest824, STest, STest("a*a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest825, STest, STest("a?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest826, STest, STest("a+?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest827, STest, STest("a*?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest828, STest, STest("a??a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest829, STest, STest("a{0,1}a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest830, STest, STest("a{2}a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest831, STest, STest("a{1,2}a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest832, STest, STest("a{2,}a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest833, STest, STest("a{0,1}?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest834, STest, STest("a{2}?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest835, STest, STest("a{1,2}?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest836, STest, STest("a{2,}?a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest837, STest, STest("a+b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest838, STest, STest("a*b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest839, STest, STest("a?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest840, STest, STest("a+?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest841, STest, STest("a*?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest842, STest, STest("a??b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest843, STest, STest("a{0,1}b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest844, STest, STest("a{2}b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest845, STest, STest("a{1,2}b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest846, STest, STest("a{2,}b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest847, STest, STest("a{0,1}?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest848, STest, STest("a{2}?b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest849, STest, STest("a{1,2}?b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest850, STest, STest("a{2,}?b|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest851, STest, STest("a+a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest852, STest, STest("a*a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest853, STest, STest("a?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest854, STest, STest("a+?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest855, STest, STest("a*?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest856, STest, STest("a??a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest857, STest, STest("a{0,1}a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest858, STest, STest("a{2}a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest859, STest, STest("a{1,2}a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest860, STest, STest("a{2,}a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest861, STest, STest("a{0,1}?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest862, STest, STest("a{2}?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest863, STest, STest("a{1,2}?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest864, STest, STest("a{2,}?a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest865, STest, STest("a+b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest866, STest, STest("a*b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest867, STest, STest("a?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest868, STest, STest("a+?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest869, STest, STest("a*?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest870, STest, STest("a??b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest871, STest, STest("a{0,1}b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest872, STest, STest("a{2}b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest873, STest, STest("a{1,2}b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest874, STest, STest("a{2,}b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest875, STest, STest("a{0,1}?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest876, STest, STest("a{2}?b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest877, STest, STest("a{1,2}?b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest878, STest, STest("a{2,}?b|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest879, STest, STest("a+b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest880, STest, STest("a*b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest881, STest, STest("a?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest882, STest, STest("a+?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest883, STest, STest("a*?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest884, STest, STest("a??b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest885, STest, STest("a{0,1}b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest886, STest, STest("a{2}b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest887, STest, STest("a{1,2}b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternTest888, STest, STest("a{2,}b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternTest889, STest, STest("a{0,1}?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest890, STest, STest("a{2}?b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest891, STest, STest("a{1,2}?b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternTest892, STest, STest("a{2,}?b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
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

SCOPE_FIXTURE_CTOR(autoPatternTest893, STest, STest("a+|(a)")) {
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

SCOPE_TEST(autoPatternTest894) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest895) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest896, STest, STest("a+?|(a)")) {
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

SCOPE_TEST(autoPatternTest897) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest898) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest899) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest900, STest, STest("a{2}|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest901, STest, STest("a{1,2}|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest902, STest, STest("a{2,}|(a)")) {
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

SCOPE_TEST(autoPatternTest903) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|(a)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest904, STest, STest("a{2}?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest905, STest, STest("a{1,2}?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest906, STest, STest("a{2,}?|(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest907, STest, STest("a+|(b)")) {
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

SCOPE_TEST(autoPatternTest908) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest909) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest910, STest, STest("a+?|(b)")) {
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

SCOPE_TEST(autoPatternTest911) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest912) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest913) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest914, STest, STest("a{2}|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest915, STest, STest("a{1,2}|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest916, STest, STest("a{2,}|(b)")) {
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

SCOPE_TEST(autoPatternTest917) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|(b)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest918, STest, STest("a{2}?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest919, STest, STest("a{1,2}?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest920, STest, STest("a{2,}?|(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest921, STest, STest("a+|a")) {
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

SCOPE_TEST(autoPatternTest922) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest923) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest924, STest, STest("a+?|a")) {
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

SCOPE_TEST(autoPatternTest925) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest926) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest927) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest928, STest, STest("a{2}|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest929, STest, STest("a{1,2}|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest930, STest, STest("a{2,}|a")) {
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

SCOPE_TEST(autoPatternTest931) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest932, STest, STest("a{2}?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest933, STest, STest("a{1,2}?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest934, STest, STest("a{2,}?|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest935, STest, STest("a+|b")) {
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

SCOPE_TEST(autoPatternTest936) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest937) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest938, STest, STest("a+?|b")) {
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

SCOPE_TEST(autoPatternTest939) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest940) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest941) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest942, STest, STest("a{2}|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest943, STest, STest("a{1,2}|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest944, STest, STest("a{2,}|b")) {
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

SCOPE_TEST(autoPatternTest945) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest946, STest, STest("a{2}?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest947, STest, STest("a{1,2}?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest948, STest, STest("a{2,}?|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest949, STest, STest("a+|aa")) {
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

SCOPE_TEST(autoPatternTest950) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest951) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest952, STest, STest("a+?|aa")) {
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

SCOPE_TEST(autoPatternTest953) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest954) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest955) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest956, STest, STest("a{2}|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest957, STest, STest("a{1,2}|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest958, STest, STest("a{2,}|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest959) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|aa", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest960, STest, STest("a{2}?|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest961, STest, STest("a{1,2}?|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest962, STest, STest("a{2,}?|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest963, STest, STest("a+|ba")) {
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

SCOPE_TEST(autoPatternTest964) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest965) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest966, STest, STest("a+?|ba")) {
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

SCOPE_TEST(autoPatternTest967) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest968) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest969) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest970, STest, STest("a{2}|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest971, STest, STest("a{1,2}|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest972, STest, STest("a{2,}|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest973) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|ba", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest974, STest, STest("a{2}?|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest975, STest, STest("a{1,2}?|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest976, STest, STest("a{2,}?|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest977, STest, STest("a+|ab")) {
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

SCOPE_TEST(autoPatternTest978) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest979) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest980, STest, STest("a+?|ab")) {
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

SCOPE_TEST(autoPatternTest981) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest982) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest983) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest984, STest, STest("a{2}|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest985, STest, STest("a{1,2}|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest986, STest, STest("a{2,}|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest987) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|ab", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest988, STest, STest("a{2}?|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest989, STest, STest("a{1,2}?|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest990, STest, STest("a{2,}?|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest991, STest, STest("a+|bb")) {
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

SCOPE_TEST(autoPatternTest992) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest993) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest994, STest, STest("a+?|bb")) {
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

SCOPE_TEST(autoPatternTest995) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest996) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest997) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest998, STest, STest("a{2}|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest999, STest, STest("a{1,2}|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1000, STest, STest("a{2,}|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest1001) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|bb", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1002, STest, STest("a{2}?|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1003, STest, STest("a{1,2}?|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1004, STest, STest("a{2,}?|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1005, STest, STest("a+|bc")) {
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

SCOPE_TEST(autoPatternTest1006) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1007) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1008, STest, STest("a+?|bc")) {
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

SCOPE_TEST(autoPatternTest1009) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1010) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1011) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1012, STest, STest("a{2}|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1013, STest, STest("a{1,2}|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[10]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1014, STest, STest("a{2,}|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_TEST(autoPatternTest1015) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|bc", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1016, STest, STest("a{2}?|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1017, STest, STest("a{1,2}?|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1018, STest, STest("a{2,}?|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 2, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1019, STest, STest("a+|a+")) {
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

SCOPE_TEST(autoPatternTest1020) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1021) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1022, STest, STest("a+?|a+")) {
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

SCOPE_TEST(autoPatternTest1023) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1024) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1025) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1026, STest, STest("a{2}|a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1027, STest, STest("a{1,2}|a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1028, STest, STest("a{2,}|a+")) {
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

SCOPE_TEST(autoPatternTest1029) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1030, STest, STest("a{2}?|a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1031, STest, STest("a{1,2}?|a+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1032, STest, STest("a{2,}?|a+")) {
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

SCOPE_TEST(autoPatternTest1033) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1034) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1035) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1036) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1037) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1038) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1039) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1040) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1041) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1042) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1043) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1044) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1045) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1046) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1047) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1048) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1049) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1050) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1051) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1052) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1053) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1054) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1055) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1056) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1057) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1058) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1059) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1060) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1061, STest, STest("a+|a+?")) {
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

SCOPE_TEST(autoPatternTest1062) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1063) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1064, STest, STest("a+?|a+?")) {
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

SCOPE_TEST(autoPatternTest1065) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1066) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1067) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1068, STest, STest("a{2}|a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1069, STest, STest("a{1,2}|a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1070, STest, STest("a{2,}|a+?")) {
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

SCOPE_TEST(autoPatternTest1071) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1072, STest, STest("a{2}?|a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1073, STest, STest("a{1,2}?|a+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1074, STest, STest("a{2,}?|a+?")) {
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

SCOPE_TEST(autoPatternTest1075) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1076) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1077) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1078) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1079) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1080) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1081) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1082) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1083) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1084) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1085) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1086) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1087) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1088) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1089) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1090) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1091) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1092) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1093) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1094) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1095) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1096) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1097) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1098) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1099) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1100) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1101) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1102) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|a??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1103) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1104) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1105) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1106) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1107) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1108) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1109) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1110) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1111) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1112) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1113) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1114) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1115) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1116) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|a{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1117, STest, STest("a+|a{2}")) {
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

SCOPE_TEST(autoPatternTest1118) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1119) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1120, STest, STest("a+?|a{2}")) {
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

SCOPE_TEST(autoPatternTest1121) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1122) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1123) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1124, STest, STest("a{2}|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1125, STest, STest("a{1,2}|a{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1126, STest, STest("a{2,}|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest1127) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1128, STest, STest("a{2}?|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1129, STest, STest("a{1,2}?|a{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1130, STest, STest("a{2,}?|a{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1131, STest, STest("a+|a{1,2}")) {
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

SCOPE_TEST(autoPatternTest1132) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1133) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1134, STest, STest("a+?|a{1,2}")) {
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

SCOPE_TEST(autoPatternTest1135) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1136) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1137) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1138, STest, STest("a{2}|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1139, STest, STest("a{1,2}|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1140, STest, STest("a{2,}|a{1,2}")) {
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

SCOPE_TEST(autoPatternTest1141) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1142, STest, STest("a{2}?|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1143, STest, STest("a{1,2}?|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1144, STest, STest("a{2,}?|a{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1145, STest, STest("a+|a{2,}")) {
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

SCOPE_TEST(autoPatternTest1146) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1147) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1148, STest, STest("a+?|a{2,}")) {
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

SCOPE_TEST(autoPatternTest1149) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1150) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1151) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1152, STest, STest("a{2}|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1153, STest, STest("a{1,2}|a{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1154, STest, STest("a{2,}|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest1155) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1156, STest, STest("a{2}?|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1157, STest, STest("a{1,2}?|a{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1158, STest, STest("a{2,}?|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest1159) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1160) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1161) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1162) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1163) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1164) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1165) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1166) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1167) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1168) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1169) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1170) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1171) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1172) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1173, STest, STest("a+|a{2}?")) {
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

SCOPE_TEST(autoPatternTest1174) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1175) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1176, STest, STest("a+?|a{2}?")) {
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

SCOPE_TEST(autoPatternTest1177) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1178) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1179) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1180, STest, STest("a{2}|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1181, STest, STest("a{1,2}|a{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1182, STest, STest("a{2,}|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest1183) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1184, STest, STest("a{2}?|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1185, STest, STest("a{1,2}?|a{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1186, STest, STest("a{2,}?|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1187, STest, STest("a+|a{1,2}?")) {
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

SCOPE_TEST(autoPatternTest1188) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1189) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1190, STest, STest("a+?|a{1,2}?")) {
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

SCOPE_TEST(autoPatternTest1191) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1192) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1193) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1194, STest, STest("a{2}|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1195, STest, STest("a{1,2}|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1196, STest, STest("a{2,}|a{1,2}?")) {
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

SCOPE_TEST(autoPatternTest1197) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1198, STest, STest("a{2}?|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1199, STest, STest("a{1,2}?|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1200, STest, STest("a{2,}?|a{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1201, STest, STest("a+|a{2,}?")) {
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

SCOPE_TEST(autoPatternTest1202) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1203) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1204, STest, STest("a+?|a{2,}?")) {
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

SCOPE_TEST(autoPatternTest1205) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1206) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1207) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1208, STest, STest("a{2}|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1209, STest, STest("a{1,2}|a{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1210, STest, STest("a{2,}|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest1211) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1212, STest, STest("a{2}?|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1213, STest, STest("a{1,2}?|a{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1214, STest, STest("a{2,}?|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1215, STest, STest("a+|b+")) {
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

SCOPE_TEST(autoPatternTest1216) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1217) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1218, STest, STest("a+?|b+")) {
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

SCOPE_TEST(autoPatternTest1219) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1220) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1221) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1222, STest, STest("a{2}|b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1223, STest, STest("a{1,2}|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[13]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1224, STest, STest("a{2,}|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[7]);
}

SCOPE_TEST(autoPatternTest1225) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1226, STest, STest("a{2}?|b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1227, STest, STest("a{1,2}?|b+")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1228, STest, STest("a{2,}?|b+")) {
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

SCOPE_TEST(autoPatternTest1229) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1230) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1231) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1232) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1233) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1234) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1235) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1236) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1237) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1238) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1239) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1240) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1241) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1242) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1243) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1244) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1245) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1246) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1247) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1248) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1249) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1250) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1251) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1252) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1253) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1254) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1255) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1256) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|b?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1257, STest, STest("a+|b+?")) {
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

SCOPE_TEST(autoPatternTest1258) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1259) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1260, STest, STest("a+?|b+?")) {
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

SCOPE_TEST(autoPatternTest1261) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1262) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1263) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1264, STest, STest("a{2}|b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1265, STest, STest("a{1,2}|b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1266, STest, STest("a{2,}|b+?")) {
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

SCOPE_TEST(autoPatternTest1267) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b+?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1268, STest, STest("a{2}?|b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1269, STest, STest("a{1,2}?|b+?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1270, STest, STest("a{2,}?|b+?")) {
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

SCOPE_TEST(autoPatternTest1271) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1272) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1273) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1274) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1275) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1276) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1277) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1278) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1279) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1280) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1281) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1282) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1283) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1284) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|b*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1285) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1286) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1287) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1288) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1289) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1290) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1291) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1292) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1293) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1294) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1295) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1296) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1297) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1298) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|b??", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1299) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1300) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1301) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1302) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1303) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1304) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1305) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1306) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1307) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1308) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1309) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1310) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1311) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1312) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|b{0,1}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1313, STest, STest("a+|b{2}")) {
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

SCOPE_TEST(autoPatternTest1314) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1315) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1316, STest, STest("a+?|b{2}")) {
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

SCOPE_TEST(autoPatternTest1317) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1318) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1319) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1320, STest, STest("a{2}|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1321, STest, STest("a{1,2}|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1322, STest, STest("a{2,}|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest1323) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1324, STest, STest("a{2}?|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1325, STest, STest("a{1,2}?|b{2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1326, STest, STest("a{2,}?|b{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1327, STest, STest("a+|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(14, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[13]);
}

SCOPE_TEST(autoPatternTest1328) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1329) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1330, STest, STest("a+?|b{1,2}")) {
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

SCOPE_TEST(autoPatternTest1331) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1332) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1333) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1334, STest, STest("a{2}|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1335, STest, STest("a{1,2}|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(15, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[14]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1336, STest, STest("a{2,}|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_TEST(autoPatternTest1337) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{1,2}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1338, STest, STest("a{2}?|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1339, STest, STest("a{1,2}?|b{1,2}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1340, STest, STest("a{2,}?|b{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 1, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1341, STest, STest("a+|b{2,}")) {
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
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[8]);
}

SCOPE_TEST(autoPatternTest1342) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1343) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1344, STest, STest("a+?|b{2,}")) {
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

SCOPE_TEST(autoPatternTest1345) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1346) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1347) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1348, STest, STest("a{2}|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1349, STest, STest("a{1,2}|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1350, STest, STest("a{2,}|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest1351) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{2,}", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1352, STest, STest("a{2}?|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1353, STest, STest("a{1,2}?|b{2,}")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1354, STest, STest("a{2,}?|b{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 3, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest1355) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1356) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1357) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1358) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1359) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1360) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1361) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1362) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1363) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1364) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1365) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1366) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1367) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1368) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2,}?|b{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1369, STest, STest("a+|b{2}?")) {
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

SCOPE_TEST(autoPatternTest1370) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1371) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1372, STest, STest("a+?|b{2}?")) {
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

SCOPE_TEST(autoPatternTest1373) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1374) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1375) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1376, STest, STest("a{2}|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1377, STest, STest("a{1,2}|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1378, STest, STest("a{2,}|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest1379) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1380, STest, STest("a{2}?|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1381, STest, STest("a{1,2}?|b{2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1382, STest, STest("a{2,}?|b{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1383, STest, STest("a+|b{1,2}?")) {
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

SCOPE_TEST(autoPatternTest1384) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1385) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1386, STest, STest("a+?|b{1,2}?")) {
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

SCOPE_TEST(autoPatternTest1387) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1388) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1389) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1390, STest, STest("a{2}|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1391, STest, STest("a{1,2}|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1392, STest, STest("a{2,}|b{1,2}?")) {
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

SCOPE_TEST(autoPatternTest1393) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{1,2}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1394, STest, STest("a{2}?|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1395, STest, STest("a{1,2}?|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1396, STest, STest("a{2,}?|b{1,2}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1397, STest, STest("a+|b{2,}?")) {
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

SCOPE_TEST(autoPatternTest1398) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1399) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1400, STest, STest("a+?|b{2,}?")) {
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

SCOPE_TEST(autoPatternTest1401) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1402) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1403) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1404, STest, STest("a{2}|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1405, STest, STest("a{1,2}|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 1, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1406, STest, STest("a{2,}|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest1407) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b{2,}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1408, STest, STest("a{2}?|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1409, STest, STest("a{1,2}?|b{2,}?")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1410, STest, STest("a{2,}?|b{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest1411, STest, STest("a+|a|a")) {
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

SCOPE_TEST(autoPatternTest1412) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1413) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1414, STest, STest("a+?|a|a")) {
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

SCOPE_TEST(autoPatternTest1415) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1416) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1417) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1418, STest, STest("a{2}|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1419, STest, STest("a{1,2}|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1420, STest, STest("a{2,}|a|a")) {
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

SCOPE_TEST(autoPatternTest1421) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1422, STest, STest("a{2}?|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1423, STest, STest("a{1,2}?|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1424, STest, STest("a{2,}?|a|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1425, STest, STest("a+|b|a")) {
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

SCOPE_TEST(autoPatternTest1426) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1427) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1428, STest, STest("a+?|b|a")) {
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

SCOPE_TEST(autoPatternTest1429) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1430) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1431) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1432, STest, STest("a{2}|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1433, STest, STest("a{1,2}|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1434, STest, STest("a{2,}|b|a")) {
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

SCOPE_TEST(autoPatternTest1435) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b|a", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1436, STest, STest("a{2}?|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1437, STest, STest("a{1,2}?|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1438, STest, STest("a{2,}?|b|a")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1439, STest, STest("a+|a|b")) {
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

SCOPE_TEST(autoPatternTest1440) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1441) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1442, STest, STest("a+?|a|b")) {
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

SCOPE_TEST(autoPatternTest1443) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1444) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1445) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1446, STest, STest("a{2}|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1447, STest, STest("a{1,2}|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1448, STest, STest("a{2,}|a|b")) {
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

SCOPE_TEST(autoPatternTest1449) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|a|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1450, STest, STest("a{2}?|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1451, STest, STest("a{1,2}?|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1452, STest, STest("a{2,}?|a|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1453, STest, STest("a+|b|b")) {
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

SCOPE_TEST(autoPatternTest1454) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1455) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1456, STest, STest("a+?|b|b")) {
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

SCOPE_TEST(autoPatternTest1457) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1458) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1459) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1460, STest, STest("a{2}|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1461, STest, STest("a{1,2}|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1462, STest, STest("a{2,}|b|b")) {
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

SCOPE_TEST(autoPatternTest1463) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b|b", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1464, STest, STest("a{2}?|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1465, STest, STest("a{1,2}?|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1466, STest, STest("a{2,}?|b|b")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1467, STest, STest("a+|b|c")) {
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

SCOPE_TEST(autoPatternTest1468) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1469) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1470, STest, STest("a+?|b|c")) {
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

SCOPE_TEST(autoPatternTest1471) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1472) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a??|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest1473) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1474, STest, STest("a{2}|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1475, STest, STest("a{1,2}|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 1, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 1, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 1, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), fixture.Hits[9]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 0), fixture.Hits[10]);
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

SCOPE_FIXTURE_CTOR(autoPatternTest1476, STest, STest("a{2,}|b|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  SCOPE_ASSERT_EQUAL(20, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
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

SCOPE_TEST(autoPatternTest1477) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?|b|c", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest1478, STest, STest("a{2}?|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1479, STest, STest("a{1,2}?|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1480, STest, STest("a{2,}?|b|c")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1481, STest, STest("a|a(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1482, STest, STest("a|b(a)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1483, STest, STest("a|a(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1484, STest, STest("a|b(b)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1485, STest, STest("a|b(c)")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1486, STest, STest("a|aa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1487, STest, STest("a|ba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1488, STest, STest("a|ab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1489, STest, STest("a|bb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1490, STest, STest("a|bc")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1491, STest, STest("a|aaa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1492, STest, STest("a|baa")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1493, STest, STest("a|aba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1494, STest, STest("a|bba")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1495, STest, STest("a|bca")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1496, STest, STest("a|aab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1497, STest, STest("a|bab")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1498, STest, STest("a|abb")) {
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

SCOPE_FIXTURE_CTOR(autoPatternTest1499, STest, STest("a|bbb")) {
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

