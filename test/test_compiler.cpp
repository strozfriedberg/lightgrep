#include <scope/test.h>

#include "codegen.h"
#include "compiler.h"
#include "states.h"

#include "test_helper.h"

ByteSet getBits(Transition& t) {
  ByteSet b;
  t.getBits(b);
  return b;
}

SCOPE_TEST(testMerge_aaOrab_toEmpty) {
  Compiler comp;
  Graph dst(1), src(5);

  // aa|ab
  edge(0, 1, src, new LitState('a'));
  boost::shared_ptr<LitState> a(new LitState('a'));
  edge(1, 2, src, a);
  edge(0, 3, src, new LitState('a'));
  boost::shared_ptr<LitState> b(new LitState('b'));
  edge(3, 4, src, b);

  comp.mergeIntoFSM(dst, src);

  SCOPE_ASSERT_EQUAL(4u, dst.numVertices());

  SCOPE_ASSERT_EQUAL(0u, dst.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, dst.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, dst.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, dst.inDegree(1));
  SCOPE_ASSERT_EQUAL(2u, dst.outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, dst.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(3u, dst.outVertex(1, 1));

  SCOPE_ASSERT_EQUAL(1u, dst.inDegree(2));
  SCOPE_ASSERT_EQUAL(0u, dst.outDegree(2));

  SCOPE_ASSERT_EQUAL(1u, dst.inDegree(3));
  SCOPE_ASSERT_EQUAL(0u, dst.outDegree(3));

  SCOPE_ASSERT_EQUAL(getBits(*a), getBits(*dst[2]));
  SCOPE_ASSERT_EQUAL(getBits(*b), getBits(*dst[3]));
}

SCOPE_TEST(testMerge) {
  Compiler comp;
  Graph fsm, key(5);

  // a(b|c)d+
  edge(0, 1, key, new LitState('a'));
  edge(1, 2, key, new LitState('b'));
  edge(1, 3, key, new LitState('c'));
  boost::shared_ptr<LitState> d(new LitState('d', 2));
  edge(2, 4, key, d);
  edge(3, 4, key, d);
  edge(4, 4, key, d);

  // ace
  // azy
  edge(0, 1, fsm, new LitState('a'));
  edge(1, 2, fsm, new LitState('c'));
  edge(2, 3, fsm, new LitState('e', 0));
  edge(1, 4, fsm, new LitState('z'));
  edge(4, 5, fsm, new LitState('y', 1));

  comp.mergeIntoFSM(fsm, key);

  const uint32 NOLABEL = std::numeric_limits<uint32>::max();

  SCOPE_ASSERT_EQUAL(8u, fsm.numVertices());

  SCOPE_ASSERT(!fsm[0]);
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[1]->Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(3u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(6u, fsm.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outVertex(1, 1));
  SCOPE_ASSERT_EQUAL(4u, fsm.outVertex(1, 2));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[2]->Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, fsm.inVertex(2, 0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(3u, fsm.outVertex(2, 0));
  SCOPE_ASSERT_EQUAL(7u, fsm.outVertex(2, 1));

  SCOPE_ASSERT_EQUAL(0u, fsm[3]->Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inVertex(3, 0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[4]->Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(4));
  SCOPE_ASSERT_EQUAL(1u, fsm.inVertex(4, 0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(4));
  SCOPE_ASSERT_EQUAL(5u, fsm.outVertex(4, 0));

  SCOPE_ASSERT_EQUAL(1u, fsm[5]->Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(5));
  SCOPE_ASSERT_EQUAL(4u, fsm.inVertex(5, 0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(5));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[6]->Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(6));
  SCOPE_ASSERT_EQUAL(1u, fsm.inVertex(6, 0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(6));
  SCOPE_ASSERT_EQUAL(7u, fsm.outVertex(6, 0));

  SCOPE_ASSERT_EQUAL(2u, fsm[7]->Label);
  SCOPE_ASSERT_EQUAL(3u, fsm.inDegree(7));
  SCOPE_ASSERT_EQUAL(6u, fsm.inVertex(7, 0));
  SCOPE_ASSERT_EQUAL(7u, fsm.inVertex(7, 1));
  SCOPE_ASSERT_EQUAL(2u, fsm.inVertex(7, 2));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(7));
  SCOPE_ASSERT_EQUAL(7u, fsm.outVertex(7, 0));
}

SCOPE_TEST(testMergeLabelsSimple) {
  Compiler c;
  Graph src(3), dst(3), exp(4);

  // ab
  edge(0, 1, src, new LitState('a'));
  edge(1, 2, src, new LitState('b'));

  src[2]->Label = 1;
  src[2]->IsMatch = true;

  // ac
  edge(0, 1, dst, new LitState('a'));
  edge(1, 2, dst, new LitState('c'));

  dst[2]->Label = 0;
  dst[2]->IsMatch = true;

  c.mergeIntoFSM(dst, src);

  // ab + ac
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('c'));
  edge(1, 3, exp, new LitState('b'));

  exp[1]->Label = NONE;
  exp[2]->Label = 0;
  exp[3]->Label = 1;

  exp[2]->IsMatch = true;
  exp[3]->IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

SCOPE_TEST(testMergeLabelsComplex) {
  Compiler c;
  Graph src(4), dst(4), exp(6);

  // abd
  edge(0, 1, src, new LitState('a'));
  edge(1, 2, src, new LitState('b'));
  edge(2, 3, src, new LitState('d'));

  src[3]->Label = 0;
  src[3]->IsMatch = true;

  // acd
  edge(0, 1, dst, new LitState('a'));
  edge(1, 2, dst, new LitState('c'));
  edge(2, 3, dst, new LitState('d'));

  dst[3]->Label = 1;
  dst[3]->IsMatch = true;

  c.mergeIntoFSM(dst, src);
  c.labelGuardStates(dst);

  // abd + acd
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('c'));
  edge(2, 3, exp, new LitState('d'));
  edge(1, 4, exp, new LitState('b'));
  edge(4, 5, exp, new LitState('d'));

  exp[1]->Label = NONE;
  exp[2]->Label = 1;
  exp[3]->Label = NONE;
  exp[4]->Label = 0;
  exp[5]->Label = NONE;

  exp[3]->IsMatch = true;
  exp[5]->IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

SCOPE_TEST(testGuardLabelsFourKeys) {
  Compiler comp;
  Graph key[4], exp;

  // a(b|c)a
  edge(0, 1, key[0], new LitState('a'));
  edge(1, 2, key[0], new LitState('b'));
  edge(1, 3, key[0], new LitState('c'));
  boost::shared_ptr<LitState> a(new LitState('a'));
  edge(2, 4, key[0], a);
  edge(3, 4, key[0], a);

  key[0][4]->Label = 0;
  key[0][4]->IsMatch = true;

  // ac+
  edge(0, 1, key[1], new LitState('a'));
  boost::shared_ptr<LitState> c(new LitState('c'));
  edge(1, 2, key[1], c);
  edge(2, 2, key[1], c);

  key[1][2]->Label = 1;
  key[1][2]->IsMatch = true;

  // ab?a
  edge(0, 1, key[2], new LitState('a'));
  edge(1, 2, key[2], new LitState('b'));
  boost::shared_ptr<LitState> a2(new LitState('a'));
  edge(1, 3, key[2], a2);
  edge(2, 3, key[2], a2);

  key[2][3]->Label = 2;
  key[2][3]->IsMatch = true;

  // two
  edge(0, 1, key[3], new LitState('t'));
  edge(1, 2, key[3], new LitState('w'));
  edge(2, 3, key[3], new LitState('o', 3));

  key[3][3]->Label = 3;
  key[3][3]->IsMatch = true;

  // merge
  for (uint32 i = 1; i < 4; ++i) {
    comp.mergeIntoFSM(key[0], key[i]);
  }

  comp.labelGuardStates(key[0]);

  // expected merged NFA
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('b'));
  edge(1, 3, exp, new LitState('c'));
  boost::shared_ptr<LitState> ae(new LitState('a'));
  edge(2, 4, exp, ae);
  edge(3, 4, exp, ae);

  exp[4]->Label = 0;
  exp[4]->IsMatch = true;

  boost::shared_ptr<LitState> ce(new LitState('c'));
  edge(1, 5, exp, ce);
  edge(5, 5, exp, ce);

  exp[5]->Label = 1;
  exp[5]->IsMatch = true;

  boost::shared_ptr<LitState> a2e(new LitState('a'));
  edge(2, 6, exp, a2e);
  edge(1, 6, exp, a2e);

  exp[6]->Label = 2;
  exp[6]->IsMatch = true;

  edge(0, 7, exp, new LitState('t'));
  edge(7, 8, exp, new LitState('w'));
  edge(8, 9, exp, new LitState('o'));

  exp[9]->Label = 3;
  exp[9]->IsMatch = true;

  exp[1]->Label = NONE;
  exp[2]->Label = NONE;
  exp[3]->Label = 0;
  exp[4]->Label = 0;
  exp[5]->Label = 1;
  exp[6]->Label = 2;
  exp[7]->Label = 3;
  exp[8]->Label = NONE;
  exp[9]->Label = NONE;

  ASSERT_EQUAL_GRAPHS(exp, key[0]);
  ASSERT_EQUAL_LABELS(exp, key[0]);
  ASSERT_EQUAL_MATCHES(exp, key[0]);
}

SCOPE_TEST(testPropagateMatchLabels) {
  Compiler comp;
  Graph g;

  edge(0, 1, g, new LitState('x'));
  edge(0, 2, g, new LitState('x'));
  edge(0, 3, g, new LitState('y'));
  edge(3, 4, g, new LitState('y'));
  edge(4, 5, g, new LitState('y'));

  g[1]->Label = 0;
  g[2]->Label = 1;
  g[5]->Label = 2;

  g[1]->IsMatch = true;
  g[2]->IsMatch = true;
  g[5]->IsMatch = true;

  comp.propagateMatchLabels(g);

  SCOPE_ASSERT_EQUAL(0, g[1]->Label);
  SCOPE_ASSERT_EQUAL(1, g[2]->Label);
  SCOPE_ASSERT_EQUAL(2, g[3]->Label);
  SCOPE_ASSERT_EQUAL(2, g[4]->Label);
  SCOPE_ASSERT_EQUAL(2, g[5]->Label);
}

SCOPE_TEST(testRemoveNonMinimalLabels) {
  Compiler comp;
  Graph g;

  edge(0, 1, g, new LitState('x'));
  edge(0, 2, g, new LitState('x'));
  edge(0, 3, g, new LitState('y'));
  edge(3, 4, g, new LitState('y'));
  edge(4, 5, g, new LitState('y'));

  g[1]->Label = 0;
  g[2]->Label = 1;
  g[3]->Label = 2;
  g[4]->Label = 2;
  g[5]->Label = 2;

  g[1]->IsMatch = true;
  g[2]->IsMatch = true;
  g[5]->IsMatch = true;

  comp.removeNonMinimalLabels(g);

  SCOPE_ASSERT_EQUAL(0, g[1]->Label);
  SCOPE_ASSERT_EQUAL(1, g[2]->Label);
  SCOPE_ASSERT_EQUAL(2, g[3]->Label);
  SCOPE_ASSERT_EQUAL(NONE, g[4]->Label);
  SCOPE_ASSERT_EQUAL(NONE, g[5]->Label);
}

SCOPE_TEST(testLabelGuardStates) {
  Compiler comp;
  Graph g;

  edge(0, 1, g, new LitState('x'));
  edge(0, 2, g, new LitState('x'));
  edge(0, 3, g, new LitState('y'));
  edge(3, 4, g, new LitState('y'));
  edge(4, 5, g, new LitState('y'));

  g[1]->Label = 0;
  g[1]->IsMatch = true;

  g[2]->Label = 1;
  g[2]->IsMatch = true;

  g[5]->Label = 2;
  g[5]->IsMatch = true;

  comp.propagateMatchLabels(g);
  comp.removeNonMinimalLabels(g);

  SCOPE_ASSERT_EQUAL(0, g[1]->Label);
  SCOPE_ASSERT_EQUAL(1, g[2]->Label);
  SCOPE_ASSERT_EQUAL(2, g[3]->Label);
  SCOPE_ASSERT_EQUAL(NONE, g[4]->Label);
  SCOPE_ASSERT_EQUAL(NONE, g[5]->Label);
}

SCOPE_TEST(testSubstringKey) {
  Compiler comp;
  Graph k0, k1, exp;

  // an
  edge(0, 1, k0, new LitState('a'));
  edge(1, 2, k0, new LitState('n', 0));
  k0[2]->IsMatch = true;

  // a
  edge(0, 1, k1, new LitState('a', 1));
  k1[1]->IsMatch = true;

  // merge
  comp.mergeIntoFSM(k0, k1);
  comp.labelGuardStates(k0);

  // expected merged NFA
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('n', 0));
  edge(0, 3, exp, new LitState('a', 1));

  exp[1]->Label = 0;
  exp[2]->Label = NONE;
  exp[3]->Label = 1;

  exp[2]->IsMatch = true;
  exp[3]->IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, k0);
  ASSERT_EQUAL_LABELS(exp, k0);
  ASSERT_EQUAL_MATCHES(exp, k0);
}

SCOPE_TEST(testCreateXXYYY) {
  std::vector<Pattern> kws;
  kws.push_back(Pattern("x"));
  kws.push_back(Pattern("x"));
  kws.push_back(Pattern("yyy"));

  GraphPtr gp(createGraph(kws, CP_ASCII, true, false));
  Graph& g = *gp;

  Graph exp;
  edge(0, 1, exp, new LitState('x'));
  edge(0, 2, exp, new LitState('x'));
  edge(0, 3, exp, new LitState('y'));
  edge(3, 4, exp, new LitState('y'));
  edge(4, 5, exp, new LitState('y'));

  exp[1]->Label = 1;
  exp[2]->Label = 0;
  exp[3]->Label = 2;
  exp[4]->Label = NONE;
  exp[5]->Label = NONE;

  exp[1]->IsMatch = true;
  exp[2]->IsMatch = true;
  exp[5]->IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, g);
  ASSERT_EQUAL_LABELS(exp, g);
  ASSERT_EQUAL_MATCHES(exp, g);
}

SCOPE_TEST(testDeterminize0) {
  Graph g(7);
  edge(0, 1, g, new LitState('a'));
  edge(1, 2, g, new LitState('1'));
  edge(1, 3, g, new LitState('2'));
  edge(0, 4, g, new EitherState('a', 'b'));
  edge(4, 5, g, new LitState('3'));
  edge(4, 6, g, new LitState('4'));

  Graph h(1);

  Compiler comp;
  comp.subsetDFA(h, g);

  Graph exp;
  edge(0, 1, exp, new LitState('a'));
  edge(0, 2, exp, new LitState('b'));
  edge(2, 3, exp, new LitState('3'));
  edge(2, 4, exp, new LitState('4'));
  edge(1, 5, exp, new LitState('1'));
  edge(1, 6, exp, new LitState('2'));
  edge(1, 3, exp, new LitState('3'));
  edge(1, 4, exp, new LitState('4'));

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize1) {
  Graph g(5);
  edge(0, 2, g, new LitState('a'));
  edge(0, 1, g, new LitState('a'));
  edge(1, 2, g, new LitState('a'));
  edge(2, 3, g, new LitState('a'));
  edge(3, 4, g, new LitState('a'));

  g[4]->IsMatch = true;
  g[4]->Label = 0;

  Graph h(1);
  Compiler comp;
  comp.subsetDFA(h, g);

  Graph exp(5);
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('a'));
  edge(2, 3, exp, new LitState('a'));
  edge(2, 4, exp, new LitState('a')); 
  edge(4, 3, exp, new LitState('a'));

  exp[3]->IsMatch = true;
  exp[3]->Label = 0; 

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize2) {
  Graph g(3);
  edge(0, 1, g, new LitState('a'));
  edge(0, 2, g, new LitState('a'));
  edge(1, 3, g, new LitState('a'));
  edge(2, 3, g, new LitState('a'));

  g[3]->IsMatch = true;
  g[3]->Label = 0;

  Graph h(1);
  Compiler comp;
  comp.subsetDFA(h, g);

  Graph exp(2);
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('a'));

  exp[2]->IsMatch = true;
  exp[2]->Label = 0; 

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize3) {
  Graph g(2);
  edge(0, 1, g, new LitState('a'));
  edge(1, 1, g, new LitState('a'));

  g[1]->IsMatch = true;
  g[1]->Label = 0;

  Graph h(1);
  Compiler comp;
  comp.subsetDFA(h, g);

  ASSERT_EQUAL_GRAPHS(g, h);
  ASSERT_EQUAL_LABELS(g, h);
  ASSERT_EQUAL_MATCHES(g, h);
}

SCOPE_TEST(testDeterminize4) {
  Graph g(2);
  edge(0, 1, g, new EitherState('a', 'b'));

  g[1]->IsMatch = true;
  g[1]->Label = 0;

  Graph h(1);
  Compiler comp;
  comp.subsetDFA(h, g);

  Graph exp(2);
  ByteSet bytes;
  bytes['a'] = bytes['b'] = true;
  edge(0, 1, exp, new CharClassState(bytes));

  exp[1]->IsMatch = true;
  exp[1]->Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize5) {
  Graph g(4);
  edge(0, 1, g, new LitState('d'));
  edge(1, 2, g, new LitState('d'));
  edge(1, 1, g, new LitState('d'));
  edge(1, 3, g, new LitState('x'));
  edge(2, 1, g, new LitState('d'));
  edge(2, 3, g, new LitState('x'));

  g[3]->IsMatch = true;
  g[3]->Label = 0;

  Graph h(1);
  Compiler comp;
  comp.subsetDFA(h, g);

  Graph exp(5);
  edge(0, 1, exp, new LitState('d'));
  edge(1, 2, exp, new LitState('d'));
  edge(1, 3, exp, new LitState('x'));
  edge(2, 4, exp, new LitState('d'));
  edge(2, 3, exp, new LitState('x'));
  edge(4, 2, exp, new LitState('d'));
  edge(4, 3, exp, new LitState('x'));

  exp[3]->IsMatch = true;
  exp[3]->Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testPruneBranches) {
  Graph g(3);
  edge(0, 1, g, new LitState('a'));
  edge(0, 2, g, new LitState('a'));

  g[1]->IsMatch = true;
  g[1]->Label = 0;

  Compiler comp;
  comp.pruneBranches(g);

  Graph exp(3);
  edge(0, 1, exp, new LitState('a'));

  exp.setTran(2, new LitState('a'));

  exp[1]->IsMatch = true;
  exp[1]->Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, g);
  ASSERT_EQUAL_LABELS(exp, g);
  ASSERT_EQUAL_MATCHES(exp, g);
}
