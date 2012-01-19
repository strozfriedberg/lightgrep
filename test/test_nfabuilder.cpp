
#include <scope/test.h>

#include "automata.h"
#include "concrete_encodings.h"
#include "nfabuilder.h"
#include "parser.h"
#include "parsetree.h"
#include "states.h"
#include "utility.h"

#include "test_helper.h"

#include <iostream>

void parseOutput(std::string type, ParseNode n) {
  std::cout << type << ": " << n.Val << std::endl;
}

SCOPE_TEST(parseAorB) {
  NFABuilder nfab;
  NFA& fsm(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT(fsm[1].trans->IsMatch);
  SCOPE_ASSERT(fsm[2].trans->IsMatch);
}

SCOPE_TEST(parseAorBorC) {
  NFABuilder nfab;
  NFA& fsm(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(3u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  SCOPE_ASSERT(fsm[1].trans->IsMatch);
  SCOPE_ASSERT(fsm[2].trans->IsMatch);
  SCOPE_ASSERT(fsm[3].trans->IsMatch);
}

SCOPE_TEST(parseAB) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT(!fsm[1].trans->IsMatch);
  SCOPE_ASSERT(fsm[2].trans->IsMatch);
}

SCOPE_TEST(parseAlternationAndConcatenation) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("a|bc", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  SCOPE_ASSERT(fsm[1].trans->IsMatch);
  SCOPE_ASSERT(!fsm[2].trans->IsMatch);
  SCOPE_ASSERT(fsm[3].trans->IsMatch);
}

SCOPE_TEST(parseGroup) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("a(b|c)", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
}

SCOPE_TEST(parseQuestionMark) {
  NFABuilder nfab;
  ParseTree tree;
  // SCOPE_ASSERT(parse("a?", false, tree boost::bind(&parseOutput, _1, _2)));
  // tree.Store.clear();
  // SCOPE_ASSERT(parse("a?", false, tree boost::bind(&Parser::callback, &p, _1, _2)));
  // SCOPE_ASSERT(!p.good());
  // tree.Store.clear();
  SCOPE_ASSERT(parse("ab?", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  NFA& fsm(*nfab.getFsm());

  // both s1 and s2 should be match states... it appears that there's an edge duplication???
  // writeGraphviz(std::cerr, fsm);

  SCOPE_ASSERT_EQUAL(3u, fsm.verticesSize());
  // get really invasive with testing here
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
}

SCOPE_TEST(parseQuestionMarkFirst) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("a?b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
}

SCOPE_TEST(parseTwoQuestionMarks) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("ab?c?d", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(5u, fsm.verticesSize());
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
}

SCOPE_TEST(parseQuestionWithAlternation) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("(a|b?)c", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, fsm.verticesSize());
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
}

SCOPE_TEST(parseQuestionWithGrouping) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("a(bc)?d", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(5u, fsm.verticesSize());
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
}

SCOPE_TEST(parsePlus) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("a+", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  // a+
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(1));
}

SCOPE_TEST(parseaPQb) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("a+?b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(2));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(g[2].trans->IsMatch);
}

SCOPE_TEST(parseStar) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("ab*c", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(3));
}

SCOPE_TEST(parseStarWithGrouping) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("a(bc)*d", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(5u, fsm.verticesSize());
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
}

SCOPE_TEST(parseaQQb) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("a??b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(edgeExists(g, 1, 2));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(2));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(g[2].trans->IsMatch);
}

SCOPE_TEST(parseaQQbQQc) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("a??b??c", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(edgeExists(g, 2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(g[3].trans->IsMatch);
}

SCOPE_TEST(parseaQQbQc) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("a??b?c", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(edgeExists(g, 2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(g[3].trans->IsMatch);
}

SCOPE_TEST(parseaQQOrbQQc) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("(a??|b??)c", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(edgeExists(g, 1, 3));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(edgeExists(g, 2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(g[3].trans->IsMatch);
}

SCOPE_TEST(parseaOrbQa) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("(a|b?)a", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(edgeExists(g, 1, 3));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(edgeExists(g, 2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(g[3].trans->IsMatch);
}

SCOPE_TEST(parseaOrbQQa) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("(a|b??)a", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT(edgeExists(g, 1, 3));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT(edgeExists(g, 2, 3));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(g[3].trans->IsMatch);
}

SCOPE_TEST(parseaSQb) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  SCOPE_ASSERT(parse("a*?b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(2));

  SCOPE_ASSERT(!g[0].trans);
  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(g[2].trans->IsMatch);
}

SCOPE_TEST(parseDot) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse(".+", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(1));

  ByteSet set;
  set.reset();
  fsm[1].trans->getBits(set);
  SCOPE_ASSERT_EQUAL(256u, set.count());
}

SCOPE_TEST(parseHexCode) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("\\x20", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));

  ByteSet set;
  set.reset();
  fsm[1].trans->getBits(set);
  SCOPE_ASSERT_EQUAL(1u, set.count());
  SCOPE_ASSERT(set[' ']);
}

SCOPE_TEST(parseHexDotPlus) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("\\x20\\xFF.+\\x20", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(5u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(4));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(4));
}

SCOPE_TEST(parse2ByteUnicode) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  nfab.setEncoding(boost::shared_ptr<Encoding>(new UCS16));
  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(5u, fsm.verticesSize());
}

SCOPE_TEST(parseHighHex) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("\\xe5", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  expected.set(0xe5);
  fsm[1].trans->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseSimpleCharClass) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("[AaBb]", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));

  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  expected.set('A');
  expected.set('a');
  expected.set('B');
  expected.set('b');
  fsm[1].trans->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
  SCOPE_ASSERT_EQUAL("ABab/0", fsm[1].trans->label());
}

SCOPE_TEST(parseUnprintableCharClass) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("[A\\xFF\\x00]", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));

  ByteSet expected,
          actual;
  expected.reset();
  actual.reset();
  expected.set('A');
  expected.set(0x00);
  expected.set(0xFF);
  fsm[1].trans->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
  SCOPE_ASSERT_EQUAL("\\x00A\\xFF/0", fsm[1].trans->label());
}

SCOPE_TEST(parseNegatedRanges) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  SCOPE_ASSERT(parse("[^a-zA-Z0-9]", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(2u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(1));
 
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
  fsm[1].trans->getBits(actual);
  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCaseInsensitive) {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  nfab.setCaseSensitive(false);
  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, fsm.verticesSize());
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(2));
  Instruction i;
  SCOPE_ASSERT(fsm[1].trans->toInstruction(&i));
  SCOPE_ASSERT_EQUAL(Instruction::makeEither('A', 'a'), i);
  SCOPE_ASSERT(fsm[2].trans->toInstruction(&i));
  SCOPE_ASSERT_EQUAL(Instruction::makeEither('B', 'b'), i);
}

SCOPE_TEST(parseSZeroMatchState) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse("a?", false, tree));
  SCOPE_ASSERT(!nfab.build(tree));
}

SCOPE_TEST(parseRepeatedSkippables) {
  // we'll simulate a?b*
  NFABuilder nfab;
  SCOPE_ASSERT_EQUAL(1, nfab.stack().size());
  nfab.callback(ParseNode(ParseNode::LITERAL, 0, 0, 'a'));
  SCOPE_ASSERT_EQUAL(2, nfab.stack().size());
  SCOPE_ASSERT_EQUAL(NOSKIP, nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::REPETITION, 0, 0, 1));
  SCOPE_ASSERT_EQUAL(2, nfab.stack().size());
  SCOPE_ASSERT_EQUAL(1, nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::LITERAL, 0, 0, 'b'));
  SCOPE_ASSERT_EQUAL(3, nfab.stack().size());
  SCOPE_ASSERT_EQUAL(NOSKIP, nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::REPETITION, 0, 0, UNBOUNDED));
  SCOPE_ASSERT_EQUAL(3, nfab.stack().size());
  SCOPE_ASSERT_EQUAL(1, nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::CONCATENATION, 0, 0, 0));
  SCOPE_ASSERT_EQUAL(2, nfab.stack().size());
  SCOPE_ASSERT_EQUAL(2, nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::CONCATENATION, 0, 0, 0));
  SCOPE_ASSERT_EQUAL(1, nfab.stack().size());
  SCOPE_ASSERT_EQUAL(NOSKIP, nfab.stack().top().Skippable);
}

SCOPE_TEST(parseZeroDotStarZero) {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("0.*0", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

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

#define TEST_REPETITION_N(pattern, n) \
  std::stringstream ss; \
  ss << pattern << '{' << n << '}'; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  SCOPE_ASSERT(parse(ss.str(), false, tree)); \
  SCOPE_ASSERT(nfab.build(tree)); \
\
  SCOPE_ASSERT_EQUAL(n + 1, g.verticesSize()); \
\
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0)); \
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0)); \
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0)); \
\
  for (uint32 i = 1; i < n; ++i) { \
    SCOPE_ASSERT_EQUAL(1u, g.inDegree(i)); \
    SCOPE_ASSERT_EQUAL(1u, g.outDegree(i)); \
    SCOPE_ASSERT_EQUAL(i+1, g.outVertex(i, 0)); \
    SCOPE_ASSERT(!g[i].trans->IsMatch); \
  } \
\
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(n)); \
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(n)); \
  SCOPE_ASSERT(g[n].trans->IsMatch);

SCOPE_TEST(parse_aLCnRC) {
  for (uint32 c = 1; c < 100; ++c) {
    TEST_REPETITION_N("a", c);
  }
}

#define TEST_REPETITION_N_U(pattern, n) \
  std::stringstream ss; \
  ss << pattern << '{' << n << ",}"; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  SCOPE_ASSERT(parse(ss.str(), false, tree)); \
  SCOPE_ASSERT(nfab.build(tree)); \
\
  SCOPE_ASSERT_EQUAL(n + 1, g.verticesSize()); \
\
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0)); \
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0)); \
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0)); \
\
  for (uint32 i = 1; i < n; ++i) { \
    SCOPE_ASSERT_EQUAL(1u, g.inDegree(i)); \
    SCOPE_ASSERT_EQUAL(1u, g.outDegree(i)); \
    SCOPE_ASSERT_EQUAL(i+1, g.outVertex(i, 0)); \
    SCOPE_ASSERT(!g[i].trans->IsMatch); \
  } \
\
  SCOPE_ASSERT_EQUAL(2u, g.inDegree(n)); \
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(n)); \
  SCOPE_ASSERT_EQUAL(n, g.outVertex(n, 0)); \
  SCOPE_ASSERT(g[n].trans->IsMatch);

SCOPE_TEST(parse_aLCn_RC) {
  for (uint32 n = 1; n < 100; ++n) {
    TEST_REPETITION_N_U("a", n);
  }
}

SCOPE_TEST(parse_aLC0_RCQb) {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,}?b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 1));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(1, 1));
  SCOPE_ASSERT(!g[1].trans->IsMatch);

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(2));
  SCOPE_ASSERT(g[2].trans->IsMatch);
}

#define TEST_REPETITION_NG_N_U(pattern, n) \
  std::stringstream ss; \
  ss << pattern << '{' << n << ",}?b"; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  SCOPE_ASSERT(parse(ss.str(), false, tree)); \
  SCOPE_ASSERT(nfab.build(tree)); \
\
  SCOPE_ASSERT_EQUAL(n + 2, g.verticesSize()); \
\
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0)); \
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0)); \
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0)); \
\
  for (uint32 i = 1; i < n-1; ++i) { \
    SCOPE_ASSERT_EQUAL(1u, g.inDegree(i)); \
    SCOPE_ASSERT_EQUAL(1u, g.outDegree(i)); \
    SCOPE_ASSERT_EQUAL(i+1, g.outVertex(i, 0)); \
    SCOPE_ASSERT(!g[i].trans->IsMatch); \
  } \
\
  SCOPE_ASSERT_EQUAL(2u, g.inDegree(n)); \
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(n)); \
  SCOPE_ASSERT_EQUAL(n+1, g.outVertex(n, 0)); \
  SCOPE_ASSERT_EQUAL(n, g.outVertex(n, 1)); \
  SCOPE_ASSERT(!g[n].trans->IsMatch); \
\
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(n+1)); \
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(n+1)); \
  SCOPE_ASSERT(g[n].trans->IsMatch);

SCOPE_TEST(parse_aLCn_RCQb) {
  for (uint32 n = 1; n < 100; ++n) {
    TEST_REPETITION_N_U("a", n);
  }
}

SCOPE_TEST(parse_xa0_) {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("xa{0,}", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(3u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(2, 0));

  SCOPE_ASSERT(g[1].trans->IsMatch);
  SCOPE_ASSERT(g[2].trans->IsMatch);
}

#define TEST_REPETITION_N_M(pattern, n, m) \
  std::stringstream ss; \
  ss << pattern << '{' << n << ',' << m << '}'; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  SCOPE_ASSERT(parse(ss.str(), false, tree)); \
  SCOPE_ASSERT(nfab.build(tree)); \
\
  SCOPE_ASSERT_EQUAL(m + 1, g.verticesSize()); \
\
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0)); \
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0)); \
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0)); \
\
  for (uint32 i = 1; i < n; ++i) { \
    SCOPE_ASSERT_EQUAL(1u, g.inDegree(i)); \
    SCOPE_ASSERT_EQUAL(1u, g.outDegree(i)); \
    SCOPE_ASSERT_EQUAL(i+1, g.outVertex(i, 0)); \
    SCOPE_ASSERT(!g[i].trans->IsMatch); \
  } \
\
  for (uint32 i = n; i < m; ++i) { \
    SCOPE_ASSERT_EQUAL(1u, g.inDegree(i)); \
    SCOPE_ASSERT_EQUAL(1u, g.outDegree(i)); \
    SCOPE_ASSERT_EQUAL(i+1, g.outVertex(i, 0)); \
    SCOPE_ASSERT(g[i].trans->IsMatch); \
  } \
\
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(m)); \
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(m)); \
  SCOPE_ASSERT(g[m].trans->IsMatch);

SCOPE_TEST(parse_aLCn_mRC) {
  for (uint32 n = 1; n < 5; ++n) {
    for (uint32 m = n; m < 5; ++m) {
      TEST_REPETITION_N_M("a", n, m);
    }
  }
}

SCOPE_TEST(parse_aaQQb) {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("aa??b", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(4u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(2, 0));

  SCOPE_ASSERT_EQUAL(2u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(3));

  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(g[3].trans->IsMatch);
}

SCOPE_TEST(parse_xLPaORaQQRPy) {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  SCOPE_ASSERT(parse("x(a|a??)y", false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  SCOPE_ASSERT_EQUAL(5u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(3u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(4, g.outVertex(1, 1));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(1, 2));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(2));
  SCOPE_ASSERT_EQUAL(4, g.outVertex(2, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(3));
  SCOPE_ASSERT_EQUAL(4, g.outVertex(3, 0));

  SCOPE_ASSERT_EQUAL(3u, g.inDegree(4));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(4));

  SCOPE_ASSERT(!g[1].trans->IsMatch);
  SCOPE_ASSERT(!g[2].trans->IsMatch);
  SCOPE_ASSERT(!g[3].trans->IsMatch);
  SCOPE_ASSERT(g[4].trans->IsMatch);
}
