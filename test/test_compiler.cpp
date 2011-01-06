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
  comp.mergeIntoFSM(fsm, key, 2);

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

  // ac
  edge(0, 1, dst, new LitState('a'));
  edge(1, 2, dst, new LitState('c', 1));

  c.mergeIntoFSM(dst, src, 1);  // XXX: wtf does '1' do?
  
  // ab + ac
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('c', 1));
  edge(1, 3, exp, new LitState('b', 2));

  ASSERT_EQUAL_GRAPHS(exp, dst);

  SCOPE_ASSERT(!dst[0]);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, dst[1]->Label);
  SCOPE_ASSERT_EQUAL(1,           dst[2]->Label);
  SCOPE_ASSERT_EQUAL(0,           dst[3]->Label);

  SCOPE_ASSERT(!dst[1]->IsMatch);
  SCOPE_ASSERT(dst[2]->IsMatch);
  SCOPE_ASSERT(dst[3]->IsMatch);
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

  c.mergeIntoFSM(dst, src, 1);
  c.labelGuardStates(dst); 
 
  // abd + acd
  edge(0, 1, exp, new LitState('a'));
  edge(1, 2, exp, new LitState('c'));
  edge(2, 3, exp, new LitState('d', 1));
  edge(1, 4, exp, new LitState('b'));
  edge(4, 5, exp, new LitState('d', 0));

  ASSERT_EQUAL_GRAPHS(exp, dst);

  SCOPE_ASSERT(!dst[0]);

  SCOPE_ASSERT_EQUAL(UNALLOCATED, dst[1]->Label);
  SCOPE_ASSERT_EQUAL(1,           dst[2]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, dst[3]->Label);
  SCOPE_ASSERT_EQUAL(0,           dst[4]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, dst[5]->Label);

  SCOPE_ASSERT(!dst[1]->IsMatch);
  SCOPE_ASSERT(!dst[2]->IsMatch);
  SCOPE_ASSERT(dst[3]->IsMatch);
  SCOPE_ASSERT(!dst[4]->IsMatch);
  SCOPE_ASSERT(dst[5]->IsMatch);
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
    comp.mergeIntoFSM(key[0], key[i], i);
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

  ASSERT_EQUAL_GRAPHS(exp, key[0]);

  SCOPE_ASSERT(!key[0][0]);

  SCOPE_ASSERT_EQUAL(UNALLOCATED, key[0][1]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, key[0][2]->Label);
  SCOPE_ASSERT_EQUAL(0,           key[0][3]->Label);
  SCOPE_ASSERT_EQUAL(0,           key[0][4]->Label);
  SCOPE_ASSERT_EQUAL(1,           key[0][5]->Label);
  SCOPE_ASSERT_EQUAL(2,           key[0][6]->Label);
  SCOPE_ASSERT_EQUAL(3,           key[0][7]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, key[0][8]->Label);
  SCOPE_ASSERT_EQUAL(UNALLOCATED, key[0][9]->Label);

  SCOPE_ASSERT(!key[0][1]->IsMatch);
  SCOPE_ASSERT(!key[0][2]->IsMatch);
  SCOPE_ASSERT(!key[0][3]->IsMatch);
  SCOPE_ASSERT(key[0][4]->IsMatch);
  SCOPE_ASSERT(key[0][5]->IsMatch);
  SCOPE_ASSERT(key[0][6]->IsMatch);
  SCOPE_ASSERT(!key[0][7]->IsMatch);
  SCOPE_ASSERT(!key[0][8]->IsMatch);
  SCOPE_ASSERT(key[0][9]->IsMatch);
}
