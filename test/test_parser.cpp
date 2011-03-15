
#include <scope/test.h>

#include "concrete_encodings.h"
#include "graph.h"
#include "parser.h"
#include "states.h"
#include "utility.h"

#include "test_helper.h"

#include <iostream>

void parseOutput(std::string type, Node n) {
  std::cout << type << ": " << n.Val << std::endl;
}

SCOPE_TEST(parseAorB) {
  Parser     p;
  SyntaxTree tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b", false, tree, p));
  SCOPE_ASSERT_EQUAL(3u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
  SCOPE_ASSERT(fsm[1]->IsMatch);
  SCOPE_ASSERT(fsm[2]->IsMatch);
}

SCOPE_TEST(parseAorBorC) {
  Parser     p;
  SyntaxTree tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b|c", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(3u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(1u, calculateLMin(fsm));
  SCOPE_ASSERT(fsm[1]->IsMatch);
  SCOPE_ASSERT(fsm[2]->IsMatch);
  SCOPE_ASSERT(fsm[3]->IsMatch);
}

SCOPE_TEST(parseAB) {
  Parser     p;
  SyntaxTree tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab", false, tree, p));
  SCOPE_ASSERT_EQUAL(3u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
  SCOPE_ASSERT(!fsm[1]->IsMatch);
  SCOPE_ASSERT(fsm[2]->IsMatch);
}

SCOPE_TEST(parseAlternationAndConcatenation) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|bc", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  skip['b'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
  SCOPE_ASSERT(fsm[1]->IsMatch);
  SCOPE_ASSERT(!fsm[2]->IsMatch);
  SCOPE_ASSERT(fsm[3]->IsMatch);
}

SCOPE_TEST(parseGroup) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(b|c)", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
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
  // SCOPE_ASSERT(parse("a?", false, tree boost::bind(&parseOutput, _1, _2)));
  // tree.Store.clear();
  // SCOPE_ASSERT(parse("a?", false, tree boost::bind(&Parser::callback, &p, _1, _2)));
  // SCOPE_ASSERT(!p.good());
  // tree.Store.clear();
  SCOPE_ASSERT(parse("ab?", false, tree, p));
  Graph& fsm(*p.getFsm());

  // both s1 and s2 should be match states... it appears that there's an edge duplication???
  // writeGraphviz(std::cerr, fsm);

  SCOPE_ASSERT_EQUAL(3u, fsm.numVertices());
  // get really invasive with testing here
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseQuestionMarkFirst) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a?b", false, tree, p));
  SCOPE_ASSERT_EQUAL(3u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab?c?d", false, tree, p));
  SCOPE_ASSERT_EQUAL(5u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  // a
  SCOPE_ASSERT_EQUAL(3u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  // b?
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  // c?
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(3));
  // d
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(4));
  SCOPE_ASSERT_EQUAL(3u, fsm.inDegree(4));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("(a|b?)c", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(3u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  // a
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  // b?
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  // c
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(3u, fsm.inDegree(3));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(bc)?d", false, tree, p));
  SCOPE_ASSERT_EQUAL(5u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  // a
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(1));
  // b
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  // c
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(3));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(3));
  // d
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(4));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(4));
  SCOPE_ASSERT_EQUAL(2u, calculateLMin(fsm));
}

SCOPE_TEST(parsePlus) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a+", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  // a+
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(1));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(1u, tbl->l_min());
  std::vector<uint32> skip(256, 1);
  skip['a'] = 0;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseStar) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab*c", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(3));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(bc)*d", false, tree, p));
  SCOPE_ASSERT_EQUAL(5u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  // a
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(1));
  // b
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  // c
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(3));
  // d
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(4));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(4));
  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(fsm);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  skip['c'] = 2; // for clarity; 'c' is beyond l-min
  skip['d'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}

SCOPE_TEST(parseaQuestionQuestionb) {
  Parser p;
  SyntaxTree tree;
  Graph& g(*p.getFsm());
 
  SCOPE_ASSERT(parse("a??b", false, tree, p));

  SCOPE_ASSERT_EQUAL(3u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(g.edgeExists(1, 2));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(2));

  SCOPE_ASSERT(!g[0]);
  SCOPE_ASSERT(!g[1]->IsMatch);
  SCOPE_ASSERT(g[2]->IsMatch);
}

SCOPE_TEST(parseaQuestionQuestionbQuestionQuestionc) {
  Parser p;
  SyntaxTree tree;
  Graph& g(*p.getFsm());

  SCOPE_ASSERT(parse("a??b??c", false, tree, p));

  SCOPE_ASSERT_EQUAL(4u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(g.edgeExists(1, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(g.edgeExists(2, 3));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0]);
  SCOPE_ASSERT(!g[1]->IsMatch);
  SCOPE_ASSERT(!g[2]->IsMatch);
  SCOPE_ASSERT(g[3]->IsMatch);
}

SCOPE_TEST(parseaQQbQc) {
  Parser p;
  SyntaxTree tree;
  Graph& g(*p.getFsm());

  SCOPE_ASSERT(parse("a??b?c", false, tree, p));

  SCOPE_ASSERT_EQUAL(4u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(g.edgeExists(1, 2));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(g.edgeExists(2, 3));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0]);
  SCOPE_ASSERT(!g[1]->IsMatch);
  SCOPE_ASSERT(!g[2]->IsMatch);
  SCOPE_ASSERT(g[3]->IsMatch);
}

SCOPE_TEST(parseaQQOrbQQc) {
  Parser p;
  SyntaxTree tree;
  Graph& g(*p.getFsm());
 
  SCOPE_ASSERT(parse("(a??|b??)c", false, tree, p));

  SCOPE_ASSERT_EQUAL(4u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(g.edgeExists(1, 3));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(g.edgeExists(2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0]);
  SCOPE_ASSERT(!g[1]->IsMatch);
  SCOPE_ASSERT(!g[2]->IsMatch);
  SCOPE_ASSERT(g[3]->IsMatch);
}

SCOPE_TEST(parseaOrbQQa) {
  Parser p;
  SyntaxTree tree;
  Graph& g(*p.getFsm());
 
  SCOPE_ASSERT(parse("(a|b??)a", false, tree, p));

  SCOPE_ASSERT_EQUAL(4u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(g.edgeExists(1, 3));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(g.edgeExists(2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0]);
  SCOPE_ASSERT(!g[1]->IsMatch);
  SCOPE_ASSERT(!g[2]->IsMatch);
  SCOPE_ASSERT(g[3]->IsMatch);
}
/*
SCOPE_TEST(parseStarQuestion) {
  Parser p;
  SyntaxTree tree;
  Graph& g(*p.getFsm());
  
  SCOPE_ASSERT(parse("ab*?c", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT(g.edgeExists(0, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT(g.edgeExists(1, 2));
  SCOPE_ASSERT(g.edgeExists(1, 3));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(2));
  SCOPE_ASSERT(g.edgeExists(2, 3));
  SCOPE_ASSERT(g.edgeExists(2, 2));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  boost::shared_ptr<SkipTable> tbl = calculateSkipTable(g);
  SCOPE_ASSERT_EQUAL(2u, tbl->l_min());
  std::vector<uint32> skip(256, 2);
  skip['a'] = 0;
  skip['b'] = 1;
  skip['c'] = 1;
  SCOPE_ASSERT_EQUAL(skip, tbl->skipVec());
}
*/

SCOPE_TEST(parseDot) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse(".+", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(1));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("#", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("\\x20", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("\\x20\\xFF.+\\x20", false, tree, p));
  SCOPE_ASSERT_EQUAL(5u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(4));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(4));
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
  Graph& fsm(*p.getFsm());
  p.setEncoding(boost::shared_ptr<Encoding>(new UCS16));
  SCOPE_ASSERT(parse("ab", false, tree, p));
  SCOPE_ASSERT_EQUAL(5u, fsm.numVertices());
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("\\xe5", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("[AaBb]", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("[^#]", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
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
  Graph& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("[^a-zA-Z0-9]", false, tree, p));
  SCOPE_ASSERT_EQUAL(2u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
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

SCOPE_TEST(parseCaseInsensitive) {
  Parser      p;
  SyntaxTree  tree;
  Graph& fsm(*p.getFsm());
  p.setCaseSensitive(false);
  SCOPE_ASSERT(parse("ab", false, tree, p));
  SCOPE_ASSERT_EQUAL(3u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  Instruction i;
  SCOPE_ASSERT(fsm[1]->toInstruction(&i));
  SCOPE_ASSERT_EQUAL(Instruction::makeEither('A', 'a'), i);
  SCOPE_ASSERT(fsm[2]->toInstruction(&i));
  SCOPE_ASSERT_EQUAL(Instruction::makeEither('B', 'b'), i);
}

SCOPE_TEST(parseSZeroMatchState) {
  Parser      p;
  SyntaxTree  tree;
  SCOPE_ASSERT(parse("a?", false, tree, p));
  SCOPE_ASSERT(!p.good());
}

SCOPE_TEST(parseRepeatedSkippables) {
  // we'll simulate a?b*
  Parser      p;
  SyntaxTree  tree;
  SCOPE_ASSERT_EQUAL(1, p.stack().size());
  p.callback("", Node(Node::LITERAL, 0, 0, 'a'));
  SCOPE_ASSERT_EQUAL(2, p.stack().size());
  SCOPE_ASSERT(!p.stack().top().Skippable);
  p.callback("", Node(Node::QUESTION, 0, 0, 0));
  SCOPE_ASSERT_EQUAL(2, p.stack().size());
  SCOPE_ASSERT(p.stack().top().Skippable);
  p.callback("", Node(Node::LITERAL, 0, 0, 'b'));
  SCOPE_ASSERT_EQUAL(3, p.stack().size());
  SCOPE_ASSERT(!p.stack().top().Skippable);
  p.callback("", Node(Node::STAR, 0, 0, 0));
  SCOPE_ASSERT_EQUAL(3, p.stack().size());
  SCOPE_ASSERT(p.stack().top().Skippable);
  p.callback("", Node(Node::CONCATENATION, 0, 0, 0));
  SCOPE_ASSERT_EQUAL(2, p.stack().size());
  SCOPE_ASSERT(p.stack().top().Skippable);
  p.callback("", Node(Node::CONCATENATION, 0, 0, 0));
  SCOPE_ASSERT_EQUAL(1, p.stack().size());
  SCOPE_ASSERT(!p.stack().top().Skippable);
}

SCOPE_TEST(verifyEdgeOrderZeroDotStarZero) {
  Parser      p;
  SyntaxTree  tree;
  Graph& g(*p.getFsm());
  SCOPE_ASSERT(parse("0.*0", false, tree, p));
  SCOPE_ASSERT_EQUAL(4u, g.numVertices());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(2, g.inVertex(2, 0));
  SCOPE_ASSERT_EQUAL(1, g.inVertex(2, 1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(2));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(2, 0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(2, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(1, g.inVertex(3, 0));
  SCOPE_ASSERT_EQUAL(2, g.inVertex(3, 1));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));  
}
