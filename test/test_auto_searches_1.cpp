#include <scope/test.h>

#include "nfabuilder.h"
#include "parsetree.h"

#include "stest.h"

SCOPE_FIXTURE_CTOR(autoPatternTest0, STest, STest("a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest1, STest, STest("(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest2, STest, STest("aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest3, STest, STest("ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest4, STest, STest("a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_TEST(autoPatternTest8) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest9) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(R"(a??)", false, tree));
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest12, STest, STest("a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest13, STest, STest("a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest14) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest15, STest, STest("a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest16, STest, STest("a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest17, STest, STest("a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest18, STest, STest("a|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest19, STest, STest("a|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest20, STest, STest("(aa)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest21, STest, STest("(ab)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest22, STest, STest("(a+)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_TEST(autoPatternTest26) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest27) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(R"((a??))", false, tree));
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest30, STest, STest("(a{1,2})")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest31, STest, STest("(a{2,})")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest32) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a{0,1}?)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest33, STest, STest("(a{2}?)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest34, STest, STest("(a{1,2}?)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest35, STest, STest("(a{2,}?)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest36, STest, STest("(a|a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest37, STest, STest("(a|b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest38, STest, STest("((a))")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest39, STest, STest("(a)(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest40, STest, STest("(a)(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest41, STest, STest("(a)+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_TEST(autoPatternTest45) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest46) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(R"((a)??)", false, tree));
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest49, STest, STest("(a){1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest50, STest, STest("(a){2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest51) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a){0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest52, STest, STest("(a){2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest53, STest, STest("(a){1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest54, STest, STest("(a){2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest55, STest, STest("(a)|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest56, STest, STest("(a)|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(19, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest57, STest, STest("aa(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest58, STest, STest("ab(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest59, STest, STest("aa(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest60, STest, STest("ab(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest61, STest, STest("ab(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest62, STest, STest("aaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest63, STest, STest("aba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest64, STest, STest("aab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest65, STest, STest("abb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest66, STest, STest("abc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest67, STest, STest("aaaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest68, STest, STest("abaa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest69, STest, STest("aaba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest70, STest, STest("abba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 11, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest71, STest, STest("abca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest72, STest, STest("aaab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest73, STest, STest("abab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest74, STest, STest("aabb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest75, STest, STest("abbb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest76, STest, STest("abcb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest77, STest, STest("abac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest78, STest, STest("aabc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest79, STest, STest("abbc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest80, STest, STest("abcc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest81, STest, STest("abc.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest82, STest, STest("aaa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest83, STest, STest("aaa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest84, STest, STest("aaa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest85, STest, STest("aaa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest86, STest, STest("aaa*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest87, STest, STest(R"(aaa??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest88, STest, STest("aaa{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest89, STest, STest("aaa{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest90, STest, STest("aaa{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest91, STest, STest("aaa{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest92, STest, STest("aaa{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest93, STest, STest("aaa{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest94, STest, STest("aaa{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest95, STest, STest("aaa{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest96, STest, STest("aba+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest97, STest, STest("aba*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest98, STest, STest("aba?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest99, STest, STest("aba+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest100, STest, STest("aba*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest101, STest, STest(R"(aba??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest102, STest, STest("aba{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest103, STest, STest("aba{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest104, STest, STest("aba{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest105, STest, STest("aba{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest106, STest, STest("aba{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest107, STest, STest("aba{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest108, STest, STest("aba{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest109, STest, STest("aba{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest110, STest, STest("aab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest111, STest, STest("aab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest112, STest, STest("aab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest113, STest, STest("aab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest114, STest, STest("aab*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest115, STest, STest(R"(aab??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest116, STest, STest("aab{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest117, STest, STest("aab{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest118, STest, STest("aab{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest119, STest, STest("aab{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest120, STest, STest("aab{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest121, STest, STest("aab{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest122, STest, STest("aab{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest123, STest, STest("aab{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest124, STest, STest("abb+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest125, STest, STest("abb*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest126, STest, STest("abb?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest127, STest, STest("abb+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest128, STest, STest("abb*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest129, STest, STest(R"(abb??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest130, STest, STest("abb{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest131, STest, STest("abb{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest132, STest, STest("abb{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest133, STest, STest("abb{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest134, STest, STest("abb{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest135, STest, STest("abb{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest136, STest, STest("abb{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest137, STest, STest("abb{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest138, STest, STest("abc+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest139, STest, STest("abc*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest140, STest, STest("abc?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest141, STest, STest("abc+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest142, STest, STest("abc*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest143, STest, STest(R"(abc??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest144, STest, STest("abc{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest145, STest, STest("abc{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest146, STest, STest("abc{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest147, STest, STest("abc{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest148, STest, STest("abc{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest149, STest, STest("abc{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest150, STest, STest("abc{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest151, STest, STest("abc{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(autoPatternTest152, STest, STest("aaa|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest153, STest, STest("aba|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest154, STest, STest("aab|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest155, STest, STest("abb|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest156, STest, STest("abc|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest157, STest, STest("aaa|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest158, STest, STest("aba|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest159, STest, STest("aab|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest160, STest, STest("abb|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest161, STest, STest("abc|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest162, STest, STest("aba|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest163, STest, STest("aab|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest164, STest, STest("abb|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest165, STest, STest("abc|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest166, STest, STest("abc|.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(26, fixture.Hits.size());
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
  SCOPE_ASSERT_EQUAL(SearchHit(10, 13, 0), fixture.Hits[10]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[11]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 15, 0), fixture.Hits[12]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[13]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[14]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 18, 0), fixture.Hits[15]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 19, 0), fixture.Hits[16]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 20, 0), fixture.Hits[17]);
  SCOPE_ASSERT_EQUAL(SearchHit(20, 21, 0), fixture.Hits[18]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 22, 0), fixture.Hits[19]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 23, 0), fixture.Hits[20]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[21]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 25, 0), fixture.Hits[22]);
  SCOPE_ASSERT_EQUAL(SearchHit(25, 26, 0), fixture.Hits[23]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 27, 0), fixture.Hits[24]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[25]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest167, STest, STest("aa+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest168, STest, STest("aa*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest169, STest, STest("aa?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest170, STest, STest("aa+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest171, STest, STest("aa*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest172, STest, STest(R"(aa??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest173, STest, STest("aa{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest174, STest, STest("aa{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest175, STest, STest("aa{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest176, STest, STest("aa{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest177, STest, STest("aa{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest178, STest, STest("aa{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest179, STest, STest("aa{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest180, STest, STest("aa{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest181, STest, STest("ab+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest182, STest, STest("ab*")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 5, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 6, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[8]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[9]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest183, STest, STest("ab?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest184, STest, STest("ab+?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest185, STest, STest("ab*?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest186, STest, STest(R"(ab??)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest187, STest, STest("ab{0,1}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest188, STest, STest("ab{2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest189, STest, STest("ab{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest190, STest, STest("ab{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest191, STest, STest("ab{0,1}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest192, STest, STest("ab{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest193, STest, STest("ab{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest194, STest, STest("ab{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest195, STest, STest("aa|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest196, STest, STest("ab|(a)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest197, STest, STest("aa|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest198, STest, STest("ab|(b)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest199, STest, STest("ab|(c)")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest200, STest, STest("aa|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest201, STest, STest("ab|a")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest202, STest, STest("aa|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(11, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest203, STest, STest("ab|b")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest204, STest, STest("ab|c")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(12, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest205, STest, STest("aa|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest206, STest, STest("ab|aa")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest207, STest, STest("aa|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 5, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest208, STest, STest("ab|ba")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 11, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 17, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest209, STest, STest("ab|ca")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest210, STest, STest("aa|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest211, STest, STest("ab|ab")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest212, STest, STest("aa|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest213, STest, STest("ab|bb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 21, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest214, STest, STest("ab|cb")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(18, 20, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest215, STest, STest("ab|ac")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(6, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 7, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 15, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 18, 0), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest216, STest, STest("aa|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 13, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest217, STest, STest("ab|bc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(21, 23, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 25, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest218, STest, STest("ab|cc")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest219, STest, STest("ab|c.")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(9, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 8, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(14, 16, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(17, 19, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(22, 24, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(24, 26, 0), fixture.Hits[7]);
  SCOPE_ASSERT_EQUAL(SearchHit(26, 28, 0), fixture.Hits[8]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest220, STest, STest("aa|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
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
  SCOPE_ASSERT(parse(R"(aa|a??)", false, tree));
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest228, STest, STest("aa|a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest229, STest, STest("aa|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_TEST(autoPatternTest230) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest231, STest, STest("aa|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest232, STest, STest("aa|a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 8, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 11, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest233, STest, STest("aa|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest234, STest, STest("ab|a+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(7, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[6]);
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_TEST(autoPatternTest238) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a*?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(autoPatternTest239) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(R"(ab|a??)", false, tree));
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
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest242, STest, STest("ab|a{1,2}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(13, 14, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(16, 17, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(27, 28, 0), fixture.Hits[7]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest243, STest, STest("ab|a{2,}")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[3]);
}

SCOPE_TEST(autoPatternTest244) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|a{0,1}?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(autoPatternTest245, STest, STest("ab|a{2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest246, STest, STest("ab|a{1,2}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(10, fixture.Hits.size());
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

SCOPE_FIXTURE_CTOR(autoPatternTest247, STest, STest("ab|a{2,}?")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 9, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 12, 0), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(autoPatternTest248, STest, STest("aa|b+")) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0);
  SCOPE_ASSERT_EQUAL(8, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 6, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 10, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(15, 16, 0), fixture.Hits[5]);
  SCOPE_ASSERT_EQUAL(SearchHit(19, 22, 0), fixture.Hits[6]);
  SCOPE_ASSERT_EQUAL(SearchHit(23, 24, 0), fixture.Hits[7]);
}

SCOPE_TEST(autoPatternTest249) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("aa|b*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}
