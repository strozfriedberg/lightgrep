#include <scope/test.h>

#include "nfabuilder.h"
#include "parsetree.h"

#include "stest.h"

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch0, STest, STest("a...b")) {
  const byte* text = (const byte*) "abababbb";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch1, STest, STest("XXXXXX")) {
  const byte* text = (const byte*) "..XXXXXX";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch2, STest, STest("\\)")) {
  const byte* text = (const byte*) "()";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

/*U
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch3, STest, STest("a]")) {
  const byte* text = (const byte*) "a]a";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch4, STest, STest("}")) {
  const byte* text = (const byte*) "}";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch5, STest, STest("\\}")) {
  const byte* text = (const byte*) "}";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch6, STest, STest("\\]")) {
  const byte* text = (const byte*) "]";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch7, STest, STest("]")) {
  const byte* text = (const byte*) "]";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch8, STest, STest("]")) {
  const byte* text = (const byte*) "]";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch9, STest, STest("{")) {
  const byte* text = (const byte*) "{";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch10, STest, STest("}")) {
  const byte* text = (const byte*) "}";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch11) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(..)*(...)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch12) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(..)*(...)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch13, STest, STest("(ab|a)(bc|c)")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch14, STest, STest("(ab)c|abc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch15, STest, STest("a{0}b")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch16, STest, STest("(a*)(b?)(b+)b{3}")) {
  const byte* text = (const byte*) "aaabbbbbbb";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch17, STest, STest("(a*)(b{0,1})(b{1,})b{3}")) {
  const byte* text = (const byte*) "aaabbbbbbb";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch18, STest, STest("a{9876543210}")) {
  const byte* text = (const byte*) "NULL";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch19, STest, STest("((a|a)|a)")) {
  const byte* text = (const byte*) "a";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch20, STest, STest("(a*)(a|aa)")) {
  const byte* text = (const byte*) "aaaa";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch21, STest, STest("a*(a.|aa)")) {
  const byte* text = (const byte*) "aaaa";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch22, STest, STest("a(b)|c(d)|a(e)f")) {
  const byte* text = (const byte*) "aef";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch23) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a|b)?.*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch24, STest, STest("(a|b)c|a(b|c)")) {
  const byte* text = (const byte*) "ac";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch25, STest, STest("(a|b)c|a(b|c)")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch26, STest, STest("(a|b)*c|(a|ab)*c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch27, STest, STest("(a|b)*c|(a|ab)*c")) {
  const byte* text = (const byte*) "xc";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch28, STest, STest("(.a|.b).*|.*(.a|.b)")) {
  const byte* text = (const byte*) "xa";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch29, STest, STest("a?(ab|ba)ab")) {
  const byte* text = (const byte*) "abab";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch30, STest, STest("a?(ac{0}b|ba)ab")) {
  const byte* text = (const byte*) "abab";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch31, STest, STest("ab|abab")) {
  const byte* text = (const byte*) "abbabab";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(3, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 2, 0), fixture.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 2, 0), fixture.Hits[2]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch32, STest, STest("aba|bab|bba")) {
  const byte* text = (const byte*) "baaabbbaba";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(5, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch33, STest, STest("aba|bab")) {
  const byte* text = (const byte*) "baaabbbaba";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 3, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch34) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(aa|aaa)*|(a|aaaaa)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch35) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a.|.a.)*|(a|.a...)", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch36, STest, STest("ab|a")) {
  const byte* text = (const byte*) "xabc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch37, STest, STest("ab|a")) {
  const byte* text = (const byte*) "xxabc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch38) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(Ab|cD)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch39, STest, STest("[^-]")) {
  const byte* text = (const byte*) "--a";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 1, 0), fixture.Hits[0]);
}
*/

/*
SCOPE_TEST(testRegexBasicModifiedSearch40) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("[a-]*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}
*/

SCOPE_TEST(testRegexBasicModifiedSearch41) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("[a-m-]*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch42, STest, STest(":::1:::0:|:::1:1:0:")) {
  const byte* text = (const byte*) ":::0:::1:::1:::0:";
  fixture.search(text, text + 17, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch43, STest, STest(":::1:::0:|:::1:1:1:")) {
  const byte* text = (const byte*) ":::0:::1:::1:::0:";
  fixture.search(text, text + 17, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(8, 9, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch44, STest, STest("[[:upper:]]")) {
  const byte* text = (const byte*) "A";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch45, STest, STest("[[:lower:]]+")) {
  const byte* text = (const byte*) "`az{";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch46, STest, STest("[[:upper:]]+")) {
  const byte* text = (const byte*) "@AZ[";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch47, STest, STest("[[-]]")) {
  const byte* text = (const byte*) "[[-]]";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch48, STest, STest("[[.NIL.]]")) {
  const byte* text = (const byte*) "NULL";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch49, STest, STest("[[=aleph=]]")) {
  const byte* text = (const byte*) "NULL";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch50, STest, STest("\\n")) {
  const byte* text = (const byte*) "\\n";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch51, STest, STest("\\n")) {
  const byte* text = (const byte*) "\\n";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch52, STest, STest("[^a]")) {
  const byte* text = (const byte*) "\\n";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch53, STest, STest("\\na")) {
  const byte* text = (const byte*) "\\na";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch54, STest, STest("(a)(b)(c)")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch55, STest, STest("xxx")) {
  const byte* text = (const byte*) "xxx";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch56, STest, STest("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?")) {
  const byte* text = (const byte*) "feb 6,";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch57, STest, STest("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?")) {
  const byte* text = (const byte*) "2/7";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch58, STest, STest("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?")) {
  const byte* text = (const byte*) "feb 1,Feb 6";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(6, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch59, STest, STest("((((((((((((((((((((((((((((((x))))))))))))))))))))))))))))))")) {
  const byte* text = (const byte*) "x";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch60) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("((((((((((((((((((((((((((((((x))))))))))))))))))))))))))))))*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch61) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?(ab|ba)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch62, STest, STest("abaa|abbaa|abbbaa|abbbbaa")) {
  const byte* text = (const byte*) "ababbabbbabbbabbbbabbbbaa";
  fixture.search(text, text + 25, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(18, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch63, STest, STest("abaa|abbaa|abbbaa|abbbbaa")) {
  const byte* text = (const byte*) "ababbabbbabbbabbbbabaa";
  fixture.search(text, text + 22, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(18, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch64, STest, STest("aaac|aabc|abac|abbc|baac|babc|bbac|bbbc")) {
  const byte* text = (const byte*) "baaabbbabac";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(7, 4, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch65) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(".*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch66, STest, STest("aaaa|bbbb|cccc|ddddd|eeeeee|fffffff|gggg|hhhh|iiiii|jjjjj|kkkkk|llll")) {
  const byte* text = (const byte*) "XaaaXbbbXcccXdddXeeeXfffXgggXhhhXiiiXjjjXkkkXlllXcbaXaaaa";
  fixture.search(text, text + 57, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(53, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch67, STest, STest("aaaa\\nbbbb\\ncccc\\nddddd\\neeeeee\\nfffffff\\ngggg\\nhhhh\\niiiii\\njjjjj\\nkkkkk\\nllll")) {
  const byte* text = (const byte*) "XaaaXbbbXcccXdddXeeeXfffXgggXhhhXiiiXjjjXkkkXlllXcbaXaaaa";
  fixture.search(text, text + 57, 0, fixture);
  SCOPE_ASSERT_EQUAL(0, fixture.Hits.size());
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch68, STest, STest("a*a*a*a*a*b")) {
  const byte* text = (const byte*) "aaaaaaaaab";
  fixture.search(text, text + 10, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 10, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch69, STest, STest("abc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch70, STest, STest("abc")) {
  const byte* text = (const byte*) "xabcy";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch71, STest, STest("abc")) {
  const byte* text = (const byte*) "ababc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch72, STest, STest("ab*c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch73, STest, STest("ab*bc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch74, STest, STest("ab*bc")) {
  const byte* text = (const byte*) "abbc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch75, STest, STest("ab*bc")) {
  const byte* text = (const byte*) "abbbbc";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch76, STest, STest("ab+bc")) {
  const byte* text = (const byte*) "abbc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch77, STest, STest("ab+bc")) {
  const byte* text = (const byte*) "abbbbc";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch78, STest, STest("ab?bc")) {
  const byte* text = (const byte*) "abbc";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch79, STest, STest("ab?bc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch80, STest, STest("ab?c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch81, STest, STest("a.c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch82, STest, STest("a.c")) {
  const byte* text = (const byte*) "axc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch83, STest, STest("a.*c")) {
  const byte* text = (const byte*) "axyzc";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch84, STest, STest("a[bc]d")) {
  const byte* text = (const byte*) "abd";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch85, STest, STest("a[b-d]e")) {
  const byte* text = (const byte*) "ace";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch86, STest, STest("a[b-d]")) {
  const byte* text = (const byte*) "aac";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch87, STest, STest("a[-b]")) {
  const byte* text = (const byte*) "a-";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch88, STest, STest("a[b-]")) {
  const byte* text = (const byte*) "a-";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch89, STest, STest("a]")) {
  const byte* text = (const byte*) "a]";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch90, STest, STest("a[]]b")) {
  const byte* text = (const byte*) "a]b";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch91, STest, STest("a[^bc]d")) {
  const byte* text = (const byte*) "aed";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch92, STest, STest("a[^-b]c")) {
  const byte* text = (const byte*) "adc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch93, STest, STest("a[^]b]c")) {
  const byte* text = (const byte*) "adc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch94, STest, STest("ab|cd")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch95, STest, STest("ab|cd")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch96, STest, STest("a\\(b")) {
  const byte* text = (const byte*) "a(b";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch97, STest, STest("a\\(*b")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch98, STest, STest("a\\(*b")) {
  const byte* text = (const byte*) "a((b";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch99, STest, STest("((a))")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch100, STest, STest("(a)b(c)")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch101, STest, STest("a+b+c")) {
  const byte* text = (const byte*) "aabbabc";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 3, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch102) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch103) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch104) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*)+", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch105) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a*|b)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch106) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a+|b)*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch107, STest, STest("(a+|b)+")) {
  const byte* text = (const byte*) "ab";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch108) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("(a+|b)?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch109) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("[^ab]*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(testRegexBasicModifiedSearch110) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch111, STest, STest("([abc])*d")) {
  const byte* text = (const byte*) "abbbcd";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch112, STest, STest("([abc])*bcd")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch113, STest, STest("a|b|c|d|e")) {
  const byte* text = (const byte*) "e";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch114, STest, STest("(a|b|c|d|e)f")) {
  const byte* text = (const byte*) "ef";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_TEST(testRegexBasicModifiedSearch115) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("((a*|b))*", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch116, STest, STest("abcd*efg")) {
  const byte* text = (const byte*) "abcdefg";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch117, STest, STest("ab*")) {
  const byte* text = (const byte*) "xabyabbbz";
  fixture.search(text, text + 9, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(4, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch118, STest, STest("ab*")) {
  const byte* text = (const byte*) "xayabbbz";
  fixture.search(text, text + 8, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 1, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(3, 4, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch119, STest, STest("(ab|cd)e")) {
  const byte* text = (const byte*) "abcde";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch120, STest, STest("[abhgefdc]ij")) {
  const byte* text = (const byte*) "hij";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch121, STest, STest("(a|b)c*d")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch122, STest, STest("(ab|ab*)bc")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch123, STest, STest("a([bc]*)c*")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch124, STest, STest("a([bc]*)(c*d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch125, STest, STest("a([bc]+)(c*d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch126, STest, STest("a([bc]*)(c+d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch127, STest, STest("a[bcd]*dcdcde")) {
  const byte* text = (const byte*) "adcdcde";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch128, STest, STest("(ab|a)b*c")) {
  const byte* text = (const byte*) "abc";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch129, STest, STest("((a)(b)c)(d)")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch130, STest, STest("[A-Za-z_][A-Za-z0-9_]*")) {
  const byte* text = (const byte*) "alpha";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch131, STest, STest("a(bc+|b[eh])g|.h")) {
  const byte* text = (const byte*) "abh";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch132, STest, STest("(bc+d|ef*g.|h?i(j|k))")) {
  const byte* text = (const byte*) "effgz";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch133, STest, STest("(bc+d|ef*g.|h?i(j|k))")) {
  const byte* text = (const byte*) "ij";
  fixture.search(text, text + 2, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 2, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch134, STest, STest("(bc+d|ef*g.|h?i(j|k))")) {
  const byte* text = (const byte*) "reffgz";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(1, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch135, STest, STest("(((((((((a)))))))))")) {
  const byte* text = (const byte*) "a";
  fixture.search(text, text + 1, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 1, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch136, STest, STest("multiple words")) {
  const byte* text = (const byte*) "multiple words yeah";
  fixture.search(text, text + 19, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch137, STest, STest("(.*)c(.*)")) {
  const byte* text = (const byte*) "abcde";
  fixture.search(text, text + 5, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 5, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch138, STest, STest("abcd")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch139, STest, STest("a(bc)d")) {
  const byte* text = (const byte*) "abcd";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch140, STest, STest("a[-]?c")) {
  const byte* text = (const byte*) "ac";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch141, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Qaddafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch142, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Mo'ammar Gadhafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch143, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Kaddafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch144, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Qadhafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch145, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Gadafi";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch146, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Mu'ammar Qadafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch147, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Moamar Gaddafi";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch148, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Mu'ammar Qadhdhafi";
  fixture.search(text, text + 18, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 18, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch149, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Khaddafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch150, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Ghaddafy";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch151, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Ghadafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch152, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Ghaddafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch153, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muamar Kaddafi";
  fixture.search(text, text + 14, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 14, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch154, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Quathafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch155, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Muammar Gheddafi";
  fixture.search(text, text + 16, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 16, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch156, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Moammar Khadafy";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch157, STest, STest("M[ou]'?am+[ae]r .*([AEae]l[- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]")) {
  const byte* text = (const byte*) "Moammar Qudhafi";
  fixture.search(text, text + 15, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 15, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch158, STest, STest("a+(b|c)*d+")) {
  const byte* text = (const byte*) "aabcdd";
  fixture.search(text, text + 6, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 6, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch159, STest, STest(".+")) {
  const byte* text = (const byte*) "vivi";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch160, STest, STest("(.+)")) {
  const byte* text = (const byte*) "vivi";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

/*
SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch161, STest, STest("([^!.]+).att.com!(.+)")) {
  const byte* text = (const byte*) "gryphon.att.com!eby";
  fixture.search(text, text + 19, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 19, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch162, STest, STest("([^!]+!)?([^!]+)")) {
  const byte* text = (const byte*) "bas";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch163, STest, STest("([^!]+!)?([^!]+)")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch164, STest, STest("([^!]+!)?([^!]+)")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch165, STest, STest(".+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 11, 0), fixture.Hits[0]);
}
*/

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch166, STest, STest("((foo)|(bar))!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch167, STest, STest("((foo)|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch168, STest, STest("((foo)|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch169, STest, STest("((foo)|bar)!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch170, STest, STest("((foo)|bar)!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch171, STest, STest("((foo)|bar)!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch172, STest, STest("(foo|(bar))!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch173, STest, STest("(foo|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch174, STest, STest("(foo|(bar))!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch175, STest, STest("(foo|bar)!bas")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch176, STest, STest("(foo|bar)!bas")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(4, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch177, STest, STest("(foo|bar)!bas")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch178, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch179, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "bas";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch180, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch181, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch182, STest, STest("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch183, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "bas";
  fixture.search(text, text + 3, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 3, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch184, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "bar!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch185, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "foo!bar!bas";
  fixture.search(text, text + 11, 0, fixture);
  SCOPE_ASSERT_EQUAL(2, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(8, 3, 0), fixture.Hits[1]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch186, STest, STest("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))")) {
  const byte* text = (const byte*) "foo!bas";
  fixture.search(text, text + 7, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 7, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch187, STest, STest(".*(/XXX).*")) {
  const byte* text = (const byte*) "/XXX";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch188, STest, STest(".*(\\\\XXX).*")) {
  const byte* text = (const byte*) "\\XXX";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch189, STest, STest("\\\\XXX")) {
  const byte* text = (const byte*) "\\XXX";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch190, STest, STest(".*(/000).*")) {
  const byte* text = (const byte*) "/000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch191, STest, STest(".*(\\\\000).*")) {
  const byte* text = (const byte*) "\\000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

SCOPE_FIXTURE_CTOR(testRegexBasicModifiedSearch192, STest, STest("\\\\000")) {
  const byte* text = (const byte*) "\\000";
  fixture.search(text, text + 4, 0, fixture);
  SCOPE_ASSERT_EQUAL(1, fixture.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(0, 4, 0), fixture.Hits[0]);
}

