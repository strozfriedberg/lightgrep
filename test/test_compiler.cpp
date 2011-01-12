#include <scope/test.h>

#include "compiler.h"
#include "states.h"
#include "utility_impl.h"

#include "test_helper.h"

SCOPE_TEST(testMerge) {
  Compiler comp;
  Graph fsm,
             key(5);

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
  edge(0, 4, fsm, new LitState('z'));
  edge(4, 5, fsm, new LitState('y', 1));
  comp.mergeIntoFSM(fsm, key);

  SCOPE_ASSERT_EQUAL(8u, fsm.numVertices());
  SCOPE_ASSERT_EQUAL(2u, (fsm).outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, (fsm).outDegree(1));
  SCOPE_ASSERT_EQUAL(2u, (fsm).outDegree(2));
  SCOPE_ASSERT_EQUAL(1u, (fsm).outDegree(6));
  SCOPE_ASSERT_EQUAL(1u, (fsm).outDegree(7));
  SCOPE_ASSERT_EQUAL(3u, (fsm).inDegree(7));
}

SCOPE_TEST(testMergeLabelsSimple) {
  Compiler c;
  Graph src(3), dst(3), exp(4);

  // ab
  edge(0, 1, src, new LitState('a'));
  edge(1, 2, src, new LitState('b', 0));

  src[2]->Label = 1; 
  src[2]->IsMatch = true;

  // ac
  edge(0, 1, dst, new LitState('a'));
  edge(1, 2, dst, new LitState('c', 1));

  dst[2]->Label = 0; 
  dst[2]->IsMatch = true;

  c.mergeIntoFSM(dst, src);
  
  // ab + ac
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('c', 1));
  edge(1, 3, exp, new LitState('b', 2));

  exp[1]->Label = UNALLOCATED;
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
  edge(2, 3, src, new LitState('d', 0));

  src[3]->IsMatch = true;

  // acd
  edge(0, 1, dst, new LitState('a'));
  edge(1, 2, dst, new LitState('c'));
  edge(2, 3, dst, new LitState('d', 1));

  dst[3]->IsMatch = true;

  c.mergeIntoFSM(dst, src);
  c.labelGuardStates(dst); 
 
  // abd + acd
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('c'));
  edge(2, 3, exp, new LitState('d', 1));
  edge(1, 4, exp, new LitState('b'));
  edge(4, 5, exp, new LitState('d', 0));

  exp[1]->Label = UNALLOCATED;
  exp[2]->Label = 1;
  exp[3]->Label = UNALLOCATED;
  exp[4]->Label = 0; 
  exp[5]->Label = UNALLOCATED;

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
  boost::shared_ptr<LitState> a(new LitState('a', 0));
  edge(2, 4, key[0], a);
  edge(3, 4, key[0], a);
  key[0][4]->IsMatch = true;

  // ac+
  edge(0, 1, key[1], new LitState('a'));
  boost::shared_ptr<LitState> c(new LitState('c', 1));
  edge(1, 2, key[1], c);
  edge(2, 2, key[1], c);
  key[1][2]->IsMatch = true;

  // ab?a
  edge(0, 1, key[2], new LitState('a'));
  edge(1, 2, key[2], new LitState('b'));
  boost::shared_ptr<LitState> a2(new LitState('a', 2));
  edge(1, 3, key[2], a2);
  edge(2, 3, key[2], a2);
  key[2][3]->IsMatch = true;
  
  // two
  edge(0, 1, key[3], new LitState('t'));
  edge(1, 2, key[3], new LitState('w'));
  edge(2, 3, key[3], new LitState('o', 3));
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
  boost::shared_ptr<LitState> ae(new LitState('a', 0));
  edge(2, 4, exp, ae);
  edge(3, 4, exp, ae);
  exp[4]->IsMatch = true;

  boost::shared_ptr<LitState> ce(new LitState('c', 1));
  edge(1, 5, exp, ce);
  edge(5, 5, exp, ce);
  exp[5]->IsMatch = true;

  boost::shared_ptr<LitState> a2e(new LitState('a', 2));
  edge(2, 6, exp, a2e);
  edge(1, 6, exp, a2e);
  exp[6]->IsMatch = true;
  
  edge(0, 7, exp, new LitState('t'));
  edge(7, 8, exp, new LitState('w'));
  edge(8, 9, exp, new LitState('o', 3));
  exp[9]->IsMatch = true;

  exp[1]->Label = UNALLOCATED;
  exp[2]->Label = UNALLOCATED;
  exp[3]->Label = 0;
  exp[4]->Label = 0;
  exp[5]->Label = 1;
  exp[6]->Label = 2;
  exp[7]->Label = 3;
  exp[8]->Label = UNALLOCATED;
  exp[9]->Label = UNALLOCATED;
  
  ASSERT_EQUAL_GRAPHS(exp, key[0]);
  ASSERT_EQUAL_LABELS(exp, key[0]);
  ASSERT_EQUAL_MATCHES(exp, key[0]);
}

SCOPE_TEST(testPropagateMatchLabels) {
  Compiler comp;
  Graph g;

  edge(0, 1, g, new LitState('x', 0));  
  edge(0, 2, g, new LitState('x', 1));
  edge(0, 3, g, new LitState('y'));
  edge(3, 4, g, new LitState('y'));
  edge(4, 5, g, new LitState('y', 2));

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

  edge(0, 1, g, new LitState('x', 0));  
  edge(0, 2, g, new LitState('x', 1));
  edge(0, 3, g, new LitState('y'));
  edge(3, 4, g, new LitState('y'));
  edge(4, 5, g, new LitState('y', 2));

  g[1]->Label = 0;
  g[2]->Label = 1;
  g[3]->Label = 2;
  g[4]->Label = 2;
  g[5]->Label = 2;

  comp.removeNonMinimalLabels(g);

  SCOPE_ASSERT_EQUAL(0, g[1]->Label);
  SCOPE_ASSERT_EQUAL(1, g[2]->Label);
  SCOPE_ASSERT_EQUAL(2, g[3]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, g[4]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, g[5]->Label);
}

SCOPE_TEST(testLabelGuardStates) {
  Compiler comp;
  Graph g;

  edge(0, 1, g, new LitState('x', 0));  
  edge(0, 2, g, new LitState('x', 1));
  edge(0, 3, g, new LitState('y'));
  edge(3, 4, g, new LitState('y'));
  edge(4, 5, g, new LitState('y', 2));

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
  SCOPE_ASSERT_EQUAL(UNALLOCATED, g[4]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, g[5]->Label); 
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
  exp[2]->Label = UNALLOCATED;
  exp[3]->Label = 1;
 
  exp[2]->IsMatch = true;
  exp[3]->IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, k0);
  ASSERT_EQUAL_LABELS(exp, k0);
  ASSERT_EQUAL_MATCHES(exp, k0);
}
