#include <scope/test.h>

#include <cstring>

#include "stest.h"

SCOPE_FIXTURE_CTOR(abSearch, STest, STest("ab")) {
  const byte* text = (const byte*)"abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 2u, 0u), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aOrbSearch, STest, STest("a|b")) {
  const byte* text = (const byte*)"abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 1u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aOrbOrcSearch, STest, STest("a|b|c")) {
  const byte* text = (const byte*)"abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 1u, 0u), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2u, 1u, 0u), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(aOrbcSearch, STest, STest("a|bc")) {
  const byte* text = (const byte*)"abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 2u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aAndbOrcSearch, STest, STest("a(b|c)")) {
  const byte* text = (const byte*)"abac";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 2u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2u, 2u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(abQuestionSearch, STest, STest("ab?")) {
  const byte* text = (const byte*)"aab";
  fixture.search(text, text+3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 1u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1u, 2u, 0u), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(abQcQdSearch, STest, STest("ab?c?d")) {
  //                               012345678901234
  const byte* text = (const byte*)"ad abcd abd acd";
  fixture.search(text, text+15, 0, fixture);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0u, 2u, 0u), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3u, 4u, 0u), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(8u, 3u, 0u), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(12u, 3u, 0u), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aOrbQcSearch, STest, STest("(a|b?)c")) {
  //                               01234567890
  const byte* text = (const byte*)"ac bc c abc";
  fixture.search(text, text + std::strlen((const char*)text), 0, fixture);
  SCOPE_ASSERT_EQUAL(4u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(6, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(9, 2, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aOrbPlusSearch, STest, STest("(a|b)+")) {
  const byte* text = (const byte*)" abbaaaba ";
  fixture.search(text, text+10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 8, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aOrbPlusShorterSearch, STest, STest("(a|b)+")) {
  const byte* text = (const byte*)"ab";
  fixture.search(text, text+2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aOrbPlusShorterSearch2, STest, STest("(a|b)+c")) {
  const byte* text = (const byte*)"abc";
  fixture.search(text, text+3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(fourKeysSearch, STest, STest(4, (const char*[]){"a(b|c)a", "ac+", "ab?a", "two"})) {
  //                               01234567890123
  const byte* text = (const byte*)"aba aa aca two";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(6u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 2), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 2), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 3, 0), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(7, 2, 1), fixture.Hits[4]);
  SCOPE_ASSERT_EQUAL(SearchHit(11, 3, 3), fixture.Hits[5]);
}

SCOPE_FIXTURE_CTOR(aOrbStarbPlusSearch, STest, STest("(a|b)*b+")) {
  //                               01234567890
  const byte* text = (const byte*)" abbaaaba b";
  fixture.search(text, text+11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(10, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(dotPlusSearch, STest, STest(".+")) {
  const byte* text = (const byte*)"whatever";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 8, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(pastFourGBSearch, STest, STest("a")) {
  const byte* text = (const byte*)"ba";
  fixture.search(text, text + 2, 0x0000000100000000, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0x0000000100000001, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(zeroDotStarZeroSearch, STest, STest("0.*0")) {
  const byte* text = (const byte*)"00000";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aDotaPlusSearch, STest, STest("a.a+")) {
  const byte* text = (const byte*)"aaabaaa";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(badLabelingSearch, STest,
                   STest(3, (const char*[]){"x", "x", "yyy"})) {
  const byte* text = (const byte*)"yyy";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 2), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(zeroZeroSearch, STest, STest("00")) {
  const byte* text = (const byte*)"0000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aaaOraSearch, STest, STest("aaa|a")) {
  const byte* text = (const byte*)"aaa";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aPlusbOraSearch, STest, STest("a+b|a")) {
  const byte* text = (const byte*)"aaab";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aPlusOrabSearch, STest, STest("a+|ab")) {
  const byte* text = (const byte*)"cab";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aQuestionQuestionbSearch, STest, STest("a??b")) {
  const byte* text = (const byte*)"abcb";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aQQbQQcSearch, STest, STest("a??b??c")) {
  const byte* text = (const byte*)"abcbc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(2u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aQQbQcSearch, STest, STest("a??b?c")) {
  const byte* text = (const byte*)"abcbcc";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(3u, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 1, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(aQQOrBQQcSearch, STest, STest("(a??|b??)c")) {
  const byte* text = (const byte*) "c";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aOrBQaSearch, STest, STest("(a|b?)a")) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aOrBQQaSearch, STest, STest("(a|b??)a")) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aPQSearch, STest, STest("a+?")) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aaQQSearch, STest, STest("aa??")) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aaSQSearch, STest, STest("aa*?")) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aPQbQSearch, STest, STest("a+?b?")) {
  const byte* text = (const byte*) "aab";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aPQbSSearch, STest, STest("a+?b*")) {
  const byte* text = (const byte*) "aab";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aOrDotOraOraSearch, STest, STest("a|.|a|a")) {
  const byte* text = (const byte*) "b";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aLPaOra0RPSearch, STest, STest("a(a|a{0})")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aQaSaSearch, STest, STest("a?a*a")) {
  const byte* text = (const byte*) "aaa";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aPQdotQQaSQSearch, STest, STest("a+?.??a*?")) {
  const byte* text = (const byte*) "aaa";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(aadotPQaPQaSSearch, STest, STest("aa.+?a+?a*")) {
  const byte* text = (const byte*) "aaaba";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aSdotQaSaSearch, STest, STest("a*.?a*a")) {
  const byte* text = (const byte*) "aaabaa";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(aPOrDotPSearch, STest, STest("a+|.+")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aaaaOraQaSearch, STest, STest("aaaa|a?a")) {
  const byte* text = (const byte*) "aaa";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aaaOraaOraaDotSearch, STest, STest("aaa|aa|aa.")) {
  const byte* text = (const byte*) "aaabaac";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(aOraaQ_aOrbSearch, STest, STest(2, (const char*[]){"a|aa?", "a|b"})) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aOraa_aOrbSearch, STest, STest(2, (const char*[]){"a|aa", "a|b"})) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 1), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aPOrDotOraaDot_aaDotPDotDotaQSearch, STest, STest(2, (const char *[]){ "a+|.|aa.", "aa.+..a*" })) {
  const byte* text = (const byte*) "baac";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(aPOrDotOraaDot_aaDotPSearch, STest, STest(2, (const char *[]){ "a+|.|aa.", "aa.+" })) {
  const byte* text = (const byte*) "baac";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 1), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aDotaQQOraOrDotPQ_aQaOrDotPaQQSearch, STest, STest(2, (const char *[]){ "a.a??|a|.+?", "a?a|.+a??" })) {
  const byte* text = (const byte*) "aaab";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(5, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 1), fixture.Hits[3]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 1, 1), fixture.Hits[4]);
}

SCOPE_FIXTURE_CTOR(aQQa_aaSearch, STest, STest(2, (const char *[]){ "a??a", "aa" })) {
  const byte* text = (const byte*) "aa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(aQQaOraaPQDot_aaSearch, STest, STest(2, (const char *[]){ "a??a|aa+?.", "aa" })) {
  const byte* text = (const byte*) "aaa";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(4, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 1), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[2]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[3]);
}

SCOPE_FIXTURE_CTOR(aaa_aaaOraSearch, STest, STest(2, (const char *[]){ "aaa", "aaa|a" })) {
  const byte* text = (const byte*) "aaa";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 1), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(metaCCSearch, STest, STest("[|()?+*]+")) {
  const byte* text = (const byte*) "|()?+*";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(startsWithTest, STest, STest(3, (const char*[]){"ab..ef", "c[a-z][a-z]", "[aA][bc][bc]"})) {
  const byte* text = (const byte*)"abcdefghijklmnop";
  fixture.startsWith(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 2), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[1]);
}

/*
SCOPE_FIXTURE_CTOR(hitCaching, STest, STest("[a-zA-Z]+ing")) {
  // 2011-05-06. This pattern causes Vm to continue buffering hits in the Matches vector until closeOut().
  const byte* text = (const byte*)"ping winging it";
  fixture.Grep->search(text, &text[5], 0, fixture); // generates hit, but not emitted
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
  fixture.Grep->search(&text[5], &text[15], 5, fixture); // generates a hit on 'wing', emits hit on 'ping'
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  fixture.Grep->closeOut(fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size()); // flushes last hit
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 7, 0), fixture.Hits[1]);
}
*/
