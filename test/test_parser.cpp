
#include <scope/test.h>

#include "parser.h"
#include "dynamicFSM.h"
#include "utility.h"

#include <iostream>
#include <stack>
#include <boost/bind.hpp>

void parseOutput(std::string type, Node n) {
  std::cout << type << ": " << n.Val << std::endl;
}

SCOPE_TEST(parseAorB) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
}

SCOPE_TEST(parseAorBorC) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|b|c", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(3u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
}

SCOPE_TEST(parseAB) {
  Parser     p;
  SyntaxTree tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
}

SCOPE_TEST(parseAlternationAndConcatenation) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a|bc", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
}

SCOPE_TEST(parseGroup) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a(b|c)", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
}

SCOPE_TEST(parseQuestionMark) {
  Parser      p;
  SyntaxTree  tree;
  // SCOPE_ASSERT(parse("a?", tree, boost::bind(&parseOutput, _1, _2)));
  // tree.Store.clear();
  // SCOPE_ASSERT(parse("a?", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  // SCOPE_ASSERT(!p.good());
  // tree.Store.clear();
  SCOPE_ASSERT(parse("ab?", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  DynamicFSM& fsm(*p.getFsm());

  // both s1 and s2 should be match states... it appears that there's an edge duplication???
  // writeGraphviz(std::cerr, fsm);

  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  // get really invasive with testing here
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
}

SCOPE_TEST(parseQuestionMarkFirst) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a?b", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(3u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(2, fsm));
}

SCOPE_TEST(parseTwoQuestionMarks) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab?c?d", tree, boost::bind(&Parser::callback, &p, _1, _2)));
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
}

SCOPE_TEST(parseQuestionWithAlternation) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("(a|b?)c", tree, boost::bind(&Parser::callback, &p, _1, _2)));
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
}

SCOPE_TEST(parsePlus) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("a+", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::in_degree(0, fsm));
  // a+
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(1, fsm));
}

SCOPE_TEST(parseStar) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("ab*c", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(4u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::out_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(2, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(3, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(3, fsm));
}

SCOPE_TEST(parseDot) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse(".+", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(1, fsm));
  SCOPE_ASSERT_EQUAL(2u, boost::in_degree(1, fsm));
  ByteSet set;
  set.reset();
  fsm[1]->getBits(set);
  SCOPE_ASSERT_EQUAL(256u, set.count());
}

SCOPE_TEST(parsePound) {
  Parser      p;
  SyntaxTree  tree;
  DynamicFSM& fsm(*p.getFsm());
  SCOPE_ASSERT(parse("#", tree, boost::bind(&Parser::callback, &p, _1, _2)));
  SCOPE_ASSERT_EQUAL(2u, boost::num_vertices(fsm));
  SCOPE_ASSERT_EQUAL(1u, boost::out_degree(0, fsm));
  SCOPE_ASSERT_EQUAL(0u, boost::out_degree(1, fsm));
  ByteSet set;
  set.reset();
  fsm[1]->getBits(set);
  SCOPE_ASSERT_EQUAL(10u, set.count());
  for (byte b = '0'; b <= '9'; ++b) {
    SCOPE_ASSERT(set[b]);
  }
}
