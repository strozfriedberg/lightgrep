
#include <scope/test.h>

#include "parser.h"
#include "dynamicFSM.h"
#include "utility.h"
#include "concrete_encodings.h"

#include <iostream>
#include <stack>

void parseOutput(std::string type, Node n) {
  std::cout << type << ": " << n.Val << std::endl;
}

SCOPE_TEST(parseAorB) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b", tree, p));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
}

SCOPE_TEST(parseAorBorC) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b|c", tree, p));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(3u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
}

SCOPE_TEST(parseAB) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab", tree, p));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseAlternationAndConcatenation) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|bc", tree, p));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  skip['b'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseGroup) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(b|c)", tree, p));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  skip['c'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseQuestionMark) {
  Parser      p;
  SyntaxTree  tree;
  // SCOPE_ASSERT(parse("a?", tree, boost::bind(&parseOutput, _1, _2)));
  // tree.Store.clear();
  // SCOPE_ASSERT(parse("a?", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  // SCOPE_ASSERT(!p.good());
  // tree.Store.clear();
  SCOPE_ASSERT(parse("ab?", tree, p));
  DynamicFSM& fsm(*p.getFsm());

  // both s1 and s2 should be match states... it appears that there's an edge duplication???
  // writeGraphviz(std::cerr, fsm);

  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  // get really invasive with testing here
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseQuestionMarkFirst) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a?b", tree, p));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  skip['b'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseTwoQuestionMarks) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab?c?d", tree, p));
  SCOPE_ASSERT_EQUAL(5u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::in_degree(0, fsm));
  // a
  SCOPE_ASSERT_EQUAL(3u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(1, fsm));
  // b?
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(2, fsm));
  // c?
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(3, fsm));
  // d
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(4, fsm));
  SCOPE_ASSERT_EQUAL(3u, boost::in_degree(4, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  skip['c'] = 1;
  skip['d'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseQuestionWithAlternation) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("(a|b?)c", tree, p));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(3u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::in_degree(0, fsm));
  // a
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(1, fsm));
  // b?
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(2, fsm));
  // c
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(3u, boost::in_degree(3, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  skip['b'] = 0;
  skip['c'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseQuestionWithGrouping) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(bc)?d", tree, p));
  SCOPE_ASSERT_EQUAL(5u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  // a
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  // b
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  // c
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(3, fsm));
  // d
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(4, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(4, fsm));
  SCOPE_ASSERT_EQUAL(2u, calculateLMin(fsm));
}

SCOPE_TEST(parsePlus) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a+", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::in_degree(0, fsm));
  // a+
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(1, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseStar) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab*c", tree, p));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(3, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  skip['c'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseStarWithGrouping) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(bc)*d", tree, p));
  SCOPE_ASSERT_EQUAL(5u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  // a
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  // b
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  // c
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(3, fsm));
  // d
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(4, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(4, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  skip['c'] = 2; // for clarity; 'c' is beyond l-min
  skip['d'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}


SCOPE_TEST(parseDot) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse(".+", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(1, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 0);
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
  ByteSet set;
  set.reset();
  fsm[1]->getBits(set);
  SCOPE_ASSERT_EQUAL(256u, set.count());
}

SCOPE_TEST(parsePound) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("#", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  for (uint32 i = '0'; i <= '9'; ++i) {
    skip[i] = 0;
  }
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
  ByteSet set;
  set.reset();
  fsm[1]->getBits(set);
  SCOPE_ASSERT_EQUAL(10u, set.count());
  for (byte b = '0'; b <= '9'; ++b) {
    SCOPE_ASSERT(set[b]);
  }
}

SCOPE_TEST(parseHexCode) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("\\x20", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip[0x20] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
  ByteSet set;
  set.reset();
  fsm[1]->getBits(set);
  SCOPE_ASSERT_EQUAL(1u, set.count());
  SCOPE_ASSERT(set[' ']);
}

SCOPE_TEST(parseHexDotPlus) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("\\x20\\xFF.+\\x20", tree, p));
  SCOPE_ASSERT_EQUAL(5u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(4, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::in_degree(4, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(4u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip[0x20] = 0;
  skip[0xff] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parse2ByteUnicode) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  p.setEncoding(boost::shared_ptr<Encoding>(new UCS16));
  SCOPE_ASSERT(parse("ab", tree, p));
  SCOPE_ASSERT_EQUAL(5u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(4u, calculateLMin(fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(4u, tbl->l_min());
  std::vector<uint32> skip(256, 4);
  skip['a'] = 0;
  skip[0] = 1;
  skip['b'] = 2;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseHighHex) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("\\xe5", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  expected.set(0xe5);
  fsm[1]->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseSimpleCharClass) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("[AaBb]", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  skip['b'] = 0;
  skip['A'] = 0;
  skip['B'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  expected.set('A');
  expected.set('a');
  expected.set('B');
  expected.set('b');
  fsm[1]->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegatedClass) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("[^#]", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  expected.set('0');
  expected.set('1');
  expected.set('2');
  expected.set('3');
  expected.set('4');
  expected.set('5');
  expected.set('6');
  expected.set('7');
  expected.set('8');
  expected.set('9');
  expected = ~expected;
  fsm[1]->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegatedRanges) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("[^a-zA-Z0-9]", tree, p));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  for (uint32 i = 0; i < 256; ++i) {
    if (('a' <= i && i <= 'z')
      || ('A' <= i && i <= 'Z')
      || ('0' <= i && i <= '9')) 
    {
      expected.set(i, false);
    }
    else {
      expected.set(i, true);
    }
  }
  fsm[1]->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
}
