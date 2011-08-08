#include <scope/test.h>

#include "nfabuilder.h"
#include "parsetree.h"

#include "stest.h"

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch0, STest, STest("a...b")) {
  const byte* text = (const byte*) "abababbb";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch1, STest, STest("XXXXXX")) {
  const byte* text = (const byte*) "..XXXXXX";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch2, STest, STest("\\)")) {
  const byte* text = (const byte*) "()";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch3, STest, STest("a]")) {
  const byte* text = (const byte*) "a]a";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch4, STest, STest("}")) {
  const byte* text = (const byte*) "}";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch5, STest, STest("\\}")) {
  const byte* text = (const byte*) "}";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch6, STest, STest("\\]")) {
  const byte* text = (const byte*) "]";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch7, STest, STest("]")) {
  const byte* text = (const byte*) "]";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch8, STest, STest("{")) {
  const byte* text = (const byte*) "{";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch9, STest, STest("}")) {
  const byte* text = (const byte*) "}";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch10) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(..)*(...)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch11) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(..)*(...)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch12, STest, STest("(ab|a)(bc|c)")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch13, STest, STest("(ab)c|abc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch14, STest, STest("a{0}b")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch15, STest, STest("(a*)(b?)(b+)b{3}")) {
  const byte* text = (const byte*) "aaabbbbbbb";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch16, STest, STest("(a*)(b{0,1})(b{1,})b{3}")) {
  const byte* text = (const byte*) "aaabbbbbbb";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch17, STest, STest("a{9876543210}")) {
  const byte* text = (const byte*) "NULL";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}
*/

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch18, STest, STest("((a|a)|a)")) {
  const byte* text = (const byte*) "a";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch19, STest, STest("(a*)(a|aa)")) {
  const byte* text = (const byte*) "aaaa";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch20, STest, STest("a*(a.|aa)")) {
  const byte* text = (const byte*) "aaaa";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch21, STest, STest("a(b)|c(d)|a(e)f")) {
  const byte* text = (const byte*) "aef";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch22) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a|b)?.*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch23, STest, STest("(a|b)c|a(b|c)")) {
  const byte* text = (const byte*) "ac";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch24, STest, STest("(a|b)c|a(b|c)")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch25, STest, STest("(a|b)*c|(a|ab)*c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch26, STest, STest("(a|b)*c|(a|ab)*c")) {
  const byte* text = (const byte*) "xc";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch27, STest, STest("(.a|.b).*|.*(.a|.b)")) {
  const byte* text = (const byte*) "xa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch28, STest, STest("a?(ab|ba)ab")) {
  const byte* text = (const byte*) "abab";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch29, STest, STest("a?(ac{0}b|ba)ab")) {
  const byte* text = (const byte*) "abab";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch30, STest, STest("ab|abab")) {
  const byte* text = (const byte*) "abbabab";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch31, STest, STest("aba|bab|bba")) {
  const byte* text = (const byte*) "baaabbbaba";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(5, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch32, STest, STest("aba|bab")) {
  const byte* text = (const byte*) "baaabbbaba";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 3, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch33) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(aa|aaa)*|(a|aaaaa)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch34) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a.|.a.)*|(a|.a...)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch35, STest, STest("ab|a")) {
  const byte* text = (const byte*) "xabc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch36, STest, STest("ab|a")) {
  const byte* text = (const byte*) "xxabc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch37) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(Ab|cD)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

/*
SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch38, STest, STest("[^-]")) {
  const byte* text = (const byte*) "--a";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[0]);
}
*/

/*
SCOPE_TEST(testregexBasicModifiedSearch39) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("[a-]*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}
*/

SCOPE_TEST(testregexBasicModifiedSearch40) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("[a-m-]*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch41, STest, STest(":::1:::0:|:::1:1:0:")) {
  const byte* text = (const byte*) ":::0:::1:::1:::0:";
  fixture.search(text, text + 17, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch42, STest, STest(":::1:::0:|:::1:1:1:")) {
  const byte* text = (const byte*) ":::0:::1:::1:::0:";
  fixture.search(text, text + 17, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch43, STest, STest("[[:upper:]]")) {
  const byte* text = (const byte*) "A";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch44, STest, STest("[[:lower:]]+")) {
  const byte* text = (const byte*) "`az{";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch45, STest, STest("[[:upper:]]+")) {
  const byte* text = (const byte*) "@AZ[";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch46, STest, STest("[[-]]")) {
  const byte* text = (const byte*) "[[-]]";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch47, STest, STest("[[.NIL.]]")) {
  const byte* text = (const byte*) "NULL";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch48, STest, STest("[[=aleph=]]")) {
  const byte* text = (const byte*) "NULL";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}
*/

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch49, STest, STest("\\n")) {
  const byte* text = (const byte*) "\\n";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch50, STest, STest("\\n")) {
  const byte* text = (const byte*) "\\n";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch51, STest, STest("[^a]")) {
  const byte* text = (const byte*) "\\n";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch52, STest, STest("\\na")) {
  const byte* text = (const byte*) "\\na";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch53, STest, STest("(a)(b)(c)")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch54, STest, STest("xxx")) {
  const byte* text = (const byte*) "xxx";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch55, STest, STest("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?")) {
  const byte* text = (const byte*) "feb 6,";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch56, STest, STest("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?")) {
  const byte* text = (const byte*) "2/7";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch57, STest, STest("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?")) {
  const byte* text = (const byte*) "feb 1,Feb 6";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch58, STest, STest("((((((((((((((((((((((((((((((x))))))))))))))))))))))))))))))")) {
  const byte* text = (const byte*) "x";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch59) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("((((((((((((((((((((((((((((((x))))))))))))))))))))))))))))))*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch60) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?(ab|ba)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch61, STest, STest("abaa|abbaa|abbbaa|abbbbaa")) {
  const byte* text = (const byte*) "ababbabbbabbbabbbbabbbbaa";
  fixture.search(text, text + 25, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(18, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch62, STest, STest("abaa|abbaa|abbbaa|abbbbaa")) {
  const byte* text = (const byte*) "ababbabbbabbbabbbbabaa";
  fixture.search(text, text + 22, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(18, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch63, STest, STest("aaac|aabc|abac|abbc|baac|babc|bbac|bbbc")) {
  const byte* text = (const byte*) "baaabbbabac";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 4, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch64) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(".*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch65, STest, STest("aaaa|bbbb|cccc|ddddd|eeeeee|fffffff|gggg|hhhh|iiiii|jjjjj|kkkkk|llll")) {
  const byte* text = (const byte*) "XaaaXbbbXcccXdddXeeeXfffXgggXhhhXiiiXjjjXkkkXlllXcbaXaaaa";
  fixture.search(text, text + 57, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(53, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch66, STest, STest("aaaa\\nbbbb\\ncccc\\nddddd\\neeeeee\\nfffffff\\ngggg\\nhhhh\\niiiii\\njjjjj\\nkkkkk\\nllll")) {
  const byte* text = (const byte*) "XaaaXbbbXcccXdddXeeeXfffXgggXhhhXiiiXjjjXkkkXlllXcbaXaaaa";
  fixture.search(text, text + 57, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch67, STest, STest("a*a*a*a*a*b")) {
  const byte* text = (const byte*) "aaaaaaaaab";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch68, STest, STest("abc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch69, STest, STest("abc")) {
  const byte* text = (const byte*) "xabcy";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch70, STest, STest("abc")) {
  const byte* text = (const byte*) "ababc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch71, STest, STest("ab*c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch72, STest, STest("ab*bc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch73, STest, STest("ab*bc")) {
  const byte* text = (const byte*) "abbc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch74, STest, STest("ab*bc")) {
  const byte* text = (const byte*) "abbbbc";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch75, STest, STest("ab+bc")) {
  const byte* text = (const byte*) "abbc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch76, STest, STest("ab+bc")) {
  const byte* text = (const byte*) "abbbbc";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch77, STest, STest("ab?bc")) {
  const byte* text = (const byte*) "abbc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch78, STest, STest("ab?bc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch79, STest, STest("ab?c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch80, STest, STest("a.c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch81, STest, STest("a.c")) {
  const byte* text = (const byte*) "axc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch82, STest, STest("a.*c")) {
  const byte* text = (const byte*) "axyzc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch83, STest, STest("a[bc]d")) {
  const byte* text = (const byte*) "abd";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch84, STest, STest("a[b-d]e")) {
  const byte* text = (const byte*) "ace";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch85, STest, STest("a[b-d]")) {
  const byte* text = (const byte*) "aac";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch86, STest, STest("a[-b]")) {
  const byte* text = (const byte*) "a-";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch87, STest, STest("a[b-]")) {
  const byte* text = (const byte*) "a-";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch88, STest, STest("a]")) {
  const byte* text = (const byte*) "a]";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch89, STest, STest("a[]]b")) {
  const byte* text = (const byte*) "a]b";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch90, STest, STest("a[^bc]d")) {
  const byte* text = (const byte*) "aed";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch91, STest, STest("a[^-b]c")) {
  const byte* text = (const byte*) "adc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch92, STest, STest("a[^]b]c")) {
  const byte* text = (const byte*) "adc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch93, STest, STest("ab|cd")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch94, STest, STest("ab|cd")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch95, STest, STest("a\\(b")) {
  const byte* text = (const byte*) "a(b";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch96, STest, STest("a\\(*b")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch97, STest, STest("a\\(*b")) {
  const byte* text = (const byte*) "a((b";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch98, STest, STest("((a))")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch99, STest, STest("(a)b(c)")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch100, STest, STest("a+b+c")) {
  const byte* text = (const byte*) "aabbabc";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 3, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch101) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch102) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch103) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*)+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch104) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*|b)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch105) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a+|b)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch106, STest, STest("(a+|b)+")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch107) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a+|b)?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch108) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("[^ab]*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testregexBasicModifiedSearch109) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch110, STest, STest("([abc])*d")) {
  const byte* text = (const byte*) "abbbcd";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch111, STest, STest("([abc])*bcd")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch112, STest, STest("a|b|c|d|e")) {
  const byte* text = (const byte*) "e";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch113, STest, STest("(a|b|c|d|e)f")) {
  const byte* text = (const byte*) "ef";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_TEST(testregexBasicModifiedSearch114) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("((a*|b))*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch115, STest, STest("abcd*efg")) {
  const byte* text = (const byte*) "abcdefg";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch116, STest, STest("ab*")) {
  const byte* text = (const byte*) "xabyabbbz";
  fixture.search(text, text + 9, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch117, STest, STest("ab*")) {
  const byte* text = (const byte*) "xayabbbz";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch118, STest, STest("(ab|cd)e")) {
  const byte* text = (const byte*) "abcde";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch119, STest, STest("[abhgefdc]ij")) {
  const byte* text = (const byte*) "hij";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch120, STest, STest("(a|b)c*d")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch121, STest, STest("(ab|ab*)bc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch122, STest, STest("a([bc]*)c*")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch123, STest, STest("a([bc]*)(c*d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch124, STest, STest("a([bc]+)(c*d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch125, STest, STest("a([bc]*)(c+d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch126, STest, STest("a[bcd]*dcdcde")) {
  const byte* text = (const byte*) "adcdcde";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch127, STest, STest("(ab|a)b*c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch128, STest, STest("((a)(b)c)(d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch129, STest, STest("[A-Za-z_][A-Za-z0-9_]*")) {
  const byte* text = (const byte*) "alpha";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch130, STest, STest("a(bc+|b[eh])g|.h")) {
  const byte* text = (const byte*) "abh";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch131, STest, STest("(bc+d|ef*g.|h?i(j|k))")) {
  const byte* text = (const byte*) "effgz";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch132, STest, STest("(bc+d|ef*g.|h?i(j|k))")) {
  const byte* text = (const byte*) "ij";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch133, STest, STest("(bc+d|ef*g.|h?i(j|k))")) {
  const byte* text = (const byte*) "reffgz";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch134, STest, STest("(((((((((a)))))))))")) {
  const byte* text = (const byte*) "a";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch135, STest, STest("multiple words")) {
  const byte* text = (const byte*) "multiple words yeah";
  fixture.search(text, text + 19, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch136, STest, STest("(.*)c(.*)")) {
  const byte* text = (const byte*) "abcde";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch137, STest, STest("abcd")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch138, STest, STest("a(bc)d")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch139, STest, STest("a[-]?c")) {
  const byte* text = (const byte*) "ac";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch140, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Qaddafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch141, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Mo'ammar Gadhafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch142, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Kaddafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch143, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Qadhafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch144, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Gadafi";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch145, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Mu'ammar Qadafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch146, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Moamar Gaddafi";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch147, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Mu'ammar Qadhdhafi";
  fixture.search(text, text + 18, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 18, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch148, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Khaddafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch149, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Ghaddafy";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch150, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Ghadafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch151, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Ghaddafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch152, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muamar Kaddafi";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch153, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Quathafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch154, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Gheddafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch155, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Moammar Khadafy";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch156, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Moammar Qudhafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch157, STest, STest("a+(b|c)*d+")) {
  const byte* text = (const byte*) "aabcdd";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch158, STest, STest(".+")) {
  const byte* text = (const byte*) "vivi";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch159, STest, STest("(.+)")) {
  const byte* text = (const byte*) "vivi";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch160, STest, STest("([^!.]+).att.com!(.+)")) {
  const byte* text = (const byte*) "gryphon.att.com!eby";
  fixture.search(text, text + 19, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 19, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch161, STest, STest("([^!]+!)?([^!]+)")) {
  const byte* text = (const byte*) "bas";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch162, STest, STest("([^!]+!)?([^!]+)")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch163, STest, STest("([^!]+!)?([^!]+)")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch164, STest, STest(".+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 11, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch165, STest, STest("((foo)|(bar))!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch166, STest, STest("((foo)|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch167, STest, STest("((foo)|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch168, STest, STest("((foo)|bar)!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch169, STest, STest("((foo)|bar)!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch170, STest, STest("((foo)|bar)!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch171, STest, STest("(foo|(bar))!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch172, STest, STest("(foo|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch173, STest, STest("(foo|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch174, STest, STest("(foo|bar)!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch175, STest, STest("(foo|bar)!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch176, STest, STest("(foo|bar)!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch177, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch178, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "bas";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch179, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch180, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch181, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch182, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "bas";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch183, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch184, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch185, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch186, STest, STest(".*(/XXX).*")) {
  const byte* text = (const byte*) "/XXX";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch187, STest, STest(".*(\\\\XXX).*")) {
  const byte* text = (const byte*) "\\XXX";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch188, STest, STest("\\\\XXX")) {
  const byte* text = (const byte*) "\\XXX";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch189, STest, STest(".*(/000).*")) {
  const byte* text = (const byte*) "/000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch190, STest, STest(".*(\\\\000).*")) {
  const byte* text = (const byte*) "\\000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testregexBasicModifiedSearch191, STest, STest("\\\\000")) {
  const byte* text = (const byte*) "\\000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

