/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <scope/test.h>

#include "codegen.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"
#include "parser.h"
#include "parsetree.h"
#include "states.h"

#include "test_helper.h"

ByteSet getBytes(Transition& t) {
  ByteSet b;
  t.getBytes(b);
  return b;
}

SCOPE_TEST(testMerge_aaOrab_toEmpty) {
  NFAOptimizer comp;
  NFA dst(1), src(5);

  Transition* a = src.TransFac->getByte('a');
  Transition* b = src.TransFac->getByte('b');

  // aa|ab
  edge(0, 1, src, a);
  edge(1, 2, src, a);
  edge(0, 3, src, a);
  edge(3, 4, src, b);

  comp.mergeIntoFSM(dst, src);

  SCOPE_ASSERT_EQUAL(4u, dst.verticesSize());

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

  SCOPE_ASSERT_EQUAL(getBytes(*a), getBytes(*dst[2].Trans));
  SCOPE_ASSERT_EQUAL(getBytes(*b), getBytes(*dst[3].Trans));
}

SCOPE_TEST(testMerge) {
  NFAOptimizer comp;
  NFA fsm, key(5);

  // a(b|c)d+
  edge(0, 1, key, key.TransFac->getByte('a'));
  edge(1, 2, key, key.TransFac->getByte('b'));
  edge(1, 3, key, key.TransFac->getByte('c'));
  edge(2, 4, key, key.TransFac->getByte('d'));
  edge(3, 4, key, key.TransFac->getByte('d'));
  edge(4, 4, key, key.TransFac->getByte('d'));

  key[4].IsMatch = true;
  key[4].Label = 2;

  // ace
  // azy
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 2, fsm, fsm.TransFac->getByte('c'));
  edge(2, 3, fsm, fsm.TransFac->getByte('e'));
  edge(1, 4, fsm, fsm.TransFac->getByte('z'));
  edge(4, 5, fsm, fsm.TransFac->getByte('y'));

  fsm[3].IsMatch = true;
  fsm[3].Label = 0;

  fsm[5].IsMatch = true;
  fsm[5].Label = 1;

  comp.mergeIntoFSM(fsm, key);

  const uint32_t NOLABEL = std::numeric_limits<uint32_t>::max();

  SCOPE_ASSERT_EQUAL(8u, fsm.verticesSize());

  SCOPE_ASSERT(!fsm[0].Trans);
  SCOPE_ASSERT_EQUAL(0u, fsm.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[1].Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(3u, fsm.outDegree(1));
  SCOPE_ASSERT_EQUAL(6u, fsm.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outVertex(1, 1));
  SCOPE_ASSERT_EQUAL(4u, fsm.outVertex(1, 2));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[2].Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(2));
  SCOPE_ASSERT_EQUAL(1u, fsm.inVertex(2, 0));
  SCOPE_ASSERT_EQUAL(2u, fsm.outDegree(2));
  SCOPE_ASSERT_EQUAL(3u, fsm.outVertex(2, 0));
  SCOPE_ASSERT_EQUAL(7u, fsm.outVertex(2, 1));

  SCOPE_ASSERT_EQUAL(0u, fsm[3].Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(3));
  SCOPE_ASSERT_EQUAL(2u, fsm.inVertex(3, 0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(3));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[4].Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(4));
  SCOPE_ASSERT_EQUAL(1u, fsm.inVertex(4, 0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(4));
  SCOPE_ASSERT_EQUAL(5u, fsm.outVertex(4, 0));

  SCOPE_ASSERT_EQUAL(1u, fsm[5].Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(5));
  SCOPE_ASSERT_EQUAL(4u, fsm.inVertex(5, 0));
  SCOPE_ASSERT_EQUAL(0u, fsm.outDegree(5));

  SCOPE_ASSERT_EQUAL(NOLABEL, fsm[6].Label);
  SCOPE_ASSERT_EQUAL(1u, fsm.inDegree(6));
  SCOPE_ASSERT_EQUAL(1u, fsm.inVertex(6, 0));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(6));
  SCOPE_ASSERT_EQUAL(7u, fsm.outVertex(6, 0));

  SCOPE_ASSERT_EQUAL(2u, fsm[7].Label);
  SCOPE_ASSERT_EQUAL(3u, fsm.inDegree(7));
  SCOPE_ASSERT_EQUAL(6u, fsm.inVertex(7, 0));
  SCOPE_ASSERT_EQUAL(7u, fsm.inVertex(7, 1));
  SCOPE_ASSERT_EQUAL(2u, fsm.inVertex(7, 2));
  SCOPE_ASSERT_EQUAL(1u, fsm.outDegree(7));
  SCOPE_ASSERT_EQUAL(7u, fsm.outVertex(7, 0));
}

SCOPE_TEST(testMergeLabelsSimple) {
  NFAOptimizer c;
  NFA src(3), dst(3), exp(4);

  // ab
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('b'));

  src[2].Label = 1;
  src[2].IsMatch = true;

  // ac
  edge(0, 1, dst, dst.TransFac->getByte('a'));
  edge(1, 2, dst, dst.TransFac->getByte('c'));

  dst[2].Label = 0;
  dst[2].IsMatch = true;

  c.mergeIntoFSM(dst, src);

  // ab + ac
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('c'));
  edge(1, 3, exp, exp.TransFac->getByte('b'));

  exp[1].Label = NONE;
  exp[2].Label = 0;
  exp[3].Label = 1;

  exp[2].IsMatch = true;
  exp[3].IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

SCOPE_TEST(testMergeLabelsComplex) {
  NFAOptimizer c;
  NFA src(4), dst(4), exp(6);

  // abd
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('b'));
  edge(2, 3, src, src.TransFac->getByte('d'));

  src[3].Label = 0;
  src[3].IsMatch = true;

  // acd
  edge(0, 1, dst, dst.TransFac->getByte('a'));
  edge(1, 2, dst, dst.TransFac->getByte('c'));
  edge(2, 3, dst, dst.TransFac->getByte('d'));

  dst[3].Label = 1;
  dst[3].IsMatch = true;

  c.mergeIntoFSM(dst, src);
  c.labelGuardStates(dst);

  // abd + acd
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('c'));
  edge(2, 3, exp, exp.TransFac->getByte('d'));
  edge(1, 4, exp, exp.TransFac->getByte('b'));
  edge(4, 5, exp, exp.TransFac->getByte('d'));

  exp[1].Label = NONE;
  exp[2].Label = 1;
  exp[3].Label = NONE;
  exp[4].Label = 0;
  exp[5].Label = NONE;

  exp[3].IsMatch = true;
  exp[5].IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

SCOPE_TEST(testGuardLabelsFourKeys) {
  NFAOptimizer comp;
  NFA key[4], exp;

  // a(b|c)a
  edge(0, 1, key[0], key[0].TransFac->getByte('a'));
  edge(1, 2, key[0], key[0].TransFac->getByte('b'));
  edge(1, 3, key[0], key[0].TransFac->getByte('c'));
  edge(2, 4, key[0], key[0].TransFac->getByte('a'));
  edge(3, 4, key[0], key[0].TransFac->getByte('a'));

  key[0][4].Label = 0;
  key[0][4].IsMatch = true;

  // ac+
  edge(0, 1, key[1], key[1].TransFac->getByte('a'));
  edge(1, 2, key[1], key[1].TransFac->getByte('c'));
  edge(2, 2, key[1], key[1].TransFac->getByte('c'));

  key[1][2].Label = 1;
  key[1][2].IsMatch = true;

  // ab?a
  edge(0, 1, key[2], key[1].TransFac->getByte('a'));
  edge(1, 2, key[2], key[1].TransFac->getByte('b'));
  edge(1, 3, key[2], key[1].TransFac->getByte('a'));
  edge(2, 3, key[2], key[1].TransFac->getByte('a'));

  key[2][3].Label = 2;
  key[2][3].IsMatch = true;

  // two
  edge(0, 1, key[3], key[3].TransFac->getByte('t'));
  edge(1, 2, key[3], key[3].TransFac->getByte('w'));
  edge(2, 3, key[3], key[3].TransFac->getByte('o'));

  key[3][3].Label = 3;
  key[3][3].IsMatch = true;

  // merge
  for (uint32_t i = 1; i < 4; ++i) {
    comp.mergeIntoFSM(key[0], key[i]);
  }

  comp.labelGuardStates(key[0]);

  // expected merged NFA
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('b'));
  edge(1, 3, exp, exp.TransFac->getByte('c'));
  edge(2, 4, exp, exp.TransFac->getByte('a'));
  edge(3, 4, exp, exp.TransFac->getByte('a'));

  exp[4].Label = 0;
  exp[4].IsMatch = true;

  edge(1, 5, exp, exp.TransFac->getByte('c'));
  edge(5, 5, exp, exp.TransFac->getByte('c'));

  exp[5].Label = 1;
  exp[5].IsMatch = true;

  edge(2, 6, exp, exp.TransFac->getByte('a'));
  edge(1, 6, exp, exp.TransFac->getByte('a'));

  exp[6].Label = 2;
  exp[6].IsMatch = true;

  edge(0, 7, exp, exp.TransFac->getByte('t'));
  edge(7, 8, exp, exp.TransFac->getByte('w'));
  edge(8, 9, exp, exp.TransFac->getByte('o'));

  exp[9].Label = 3;
  exp[9].IsMatch = true;

  exp[1].Label = NONE;
  exp[2].Label = NONE;
  exp[3].Label = 0;
  exp[4].Label = 0;
  exp[5].Label = 1;
  exp[6].Label = 2;
  exp[7].Label = 3;
  exp[8].Label = NONE;
  exp[9].Label = NONE;

  ASSERT_EQUAL_GRAPHS(exp, key[0]);
  ASSERT_EQUAL_LABELS(exp, key[0]);
  ASSERT_EQUAL_MATCHES(exp, key[0]);
}

SCOPE_TEST(testPropagateMatchLabels) {
  NFAOptimizer comp;
  NFA g;

  edge(0, 1, g, g.TransFac->getByte('x'));
  edge(0, 2, g, g.TransFac->getByte('x'));
  edge(0, 3, g, g.TransFac->getByte('y'));
  edge(3, 4, g, g.TransFac->getByte('y'));
  edge(4, 5, g, g.TransFac->getByte('y'));

  g[1].Label = 0;
  g[2].Label = 1;
  g[5].Label = 2;

  g[1].IsMatch = true;
  g[2].IsMatch = true;
  g[5].IsMatch = true;

  comp.propagateMatchLabels(g);

  SCOPE_ASSERT_EQUAL(0u, g[1].Label);
  SCOPE_ASSERT_EQUAL(1u, g[2].Label);
  SCOPE_ASSERT_EQUAL(2u, g[3].Label);
  SCOPE_ASSERT_EQUAL(2u, g[4].Label);
  SCOPE_ASSERT_EQUAL(2u, g[5].Label);
}

SCOPE_TEST(testRemoveNonMinimalLabels) {
  NFAOptimizer comp;
  NFA g;

  edge(0, 1, g, g.TransFac->getByte('x'));
  edge(0, 2, g, g.TransFac->getByte('x'));
  edge(0, 3, g, g.TransFac->getByte('y'));
  edge(3, 4, g, g.TransFac->getByte('y'));
  edge(4, 5, g, g.TransFac->getByte('y'));

  g[1].Label = 0;
  g[2].Label = 1;
  g[3].Label = 2;
  g[4].Label = 2;
  g[5].Label = 2;

  g[1].IsMatch = true;
  g[2].IsMatch = true;
  g[5].IsMatch = true;

  comp.removeNonMinimalLabels(g);

  SCOPE_ASSERT_EQUAL(0u, g[1].Label);
  SCOPE_ASSERT_EQUAL(1u, g[2].Label);
  SCOPE_ASSERT_EQUAL(2u, g[3].Label);
  SCOPE_ASSERT_EQUAL(NONE, g[4].Label);
  SCOPE_ASSERT_EQUAL(NONE, g[5].Label);
}

SCOPE_TEST(testLabelGuardStates) {
  NFAOptimizer comp;
  NFA g;

  edge(0, 1, g, g.TransFac->getByte('x'));
  edge(0, 2, g, g.TransFac->getByte('x'));
  edge(0, 3, g, g.TransFac->getByte('y'));
  edge(3, 4, g, g.TransFac->getByte('y'));
  edge(4, 5, g, g.TransFac->getByte('y'));

  g[1].Label = 0;
  g[1].IsMatch = true;

  g[2].Label = 1;
  g[2].IsMatch = true;

  g[5].Label = 2;
  g[5].IsMatch = true;

  comp.propagateMatchLabels(g);
  comp.removeNonMinimalLabels(g);

  SCOPE_ASSERT_EQUAL(0u, g[1].Label);
  SCOPE_ASSERT_EQUAL(1u, g[2].Label);
  SCOPE_ASSERT_EQUAL(2u, g[3].Label);
  SCOPE_ASSERT_EQUAL(NONE, g[4].Label);
  SCOPE_ASSERT_EQUAL(NONE, g[5].Label);
}

SCOPE_TEST(testSubstringKey) {
  NFAOptimizer comp;
  NFA k0, k1, exp;

  // an
  edge(0, 1, k0, k0.TransFac->getByte('a'));
  edge(1, 2, k0, k0.TransFac->getByte('n'));
  k0[2].IsMatch = true;
  k0[2].Label = 0;

  // a
  edge(0, 1, k1, k1.TransFac->getByte('a'));
  k1[1].IsMatch = true;
  k1[1].Label = 1;

  // merge
  comp.mergeIntoFSM(k0, k1);
  comp.labelGuardStates(k0);

  // expected merged NFA
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('n'));
  edge(0, 3, exp, exp.TransFac->getByte('a'));

  exp[1].Label = 0;
  exp[2].Label = NONE;
  exp[3].Label = 1;

  exp[2].IsMatch = true;
  exp[3].IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, k0);
  ASSERT_EQUAL_LABELS(exp, k0);
  ASSERT_EQUAL_MATCHES(exp, k0);
}

SCOPE_TEST(testCreateXXYYY) {
  NFAPtr gptr(createGraph({"x", "x", "yyy"}, true));
  NFA& g = *gptr;

  NFA exp;
  edge(0, 1, exp, exp.TransFac->getByte('x'));
  edge(0, 2, exp, exp.TransFac->getByte('x'));
  edge(0, 3, exp, exp.TransFac->getByte('y'));
  edge(3, 4, exp, exp.TransFac->getByte('y'));
  edge(4, 5, exp, exp.TransFac->getByte('y'));

  exp[1].Label = 1;
  exp[2].Label = 0;
  exp[3].Label = 2;
  exp[4].Label = NONE;
  exp[5].Label = NONE;

  exp[1].IsMatch = true;
  exp[2].IsMatch = true;
  exp[5].IsMatch = true;

  ASSERT_EQUAL_GRAPHS(exp, g);
  ASSERT_EQUAL_LABELS(exp, g);
  ASSERT_EQUAL_MATCHES(exp, g);
}

SCOPE_TEST(testDeterminize0) {
  NFA g(7);
  edge(0, 1, g, g.TransFac->getByte('a'));
  edge(1, 2, g, g.TransFac->getByte('1'));
  edge(1, 3, g, g.TransFac->getByte('2'));
  edge(0, 4, g, g.TransFac->getEither('a', 'b'));
  edge(4, 5, g, g.TransFac->getByte('3'));
  edge(4, 6, g, g.TransFac->getByte('4'));

  NFA h(1);

  NFAOptimizer comp;
  comp.subsetDFA(h, g);

  NFA exp;
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(0, 2, exp, exp.TransFac->getByte('b'));
  edge(2, 3, exp, exp.TransFac->getByte('3'));
  edge(2, 4, exp, exp.TransFac->getByte('4'));
  edge(1, 5, exp, exp.TransFac->getByte('1'));
  edge(1, 6, exp, exp.TransFac->getByte('2'));
  edge(1, 3, exp, exp.TransFac->getByte('3'));
  edge(1, 4, exp, exp.TransFac->getByte('4'));

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize1) {
  NFA g(5);
  edge(0, 2, g, g.TransFac->getByte('a'));
  edge(0, 1, g, g.TransFac->getByte('a'));
  edge(1, 2, g, g.TransFac->getByte('a'));
  edge(2, 3, g, g.TransFac->getByte('a'));
  edge(3, 4, g, g.TransFac->getByte('a'));

  g[4].IsMatch = true;
  g[4].Label = 0;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g);

  NFA exp(5);
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('a'));
  edge(2, 3, exp, exp.TransFac->getByte('a'));
  edge(2, 4, exp, exp.TransFac->getByte('a'));
  edge(4, 3, exp, exp.TransFac->getByte('a'));

  exp[3].IsMatch = true;
  exp[3].Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize2) {
  NFA g(3);
  edge(0, 1, g, g.TransFac->getByte('a'));
  edge(0, 2, g, g.TransFac->getByte('a'));
  edge(1, 3, g, g.TransFac->getByte('a'));
  edge(2, 3, g, g.TransFac->getByte('a'));

  g[3].IsMatch = true;
  g[3].Label = 0;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g);

  NFA exp(2);
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('a'));

  exp[2].IsMatch = true;
  exp[2].Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize3) {
  NFA g(2);
  edge(0, 1, g, g.TransFac->getByte('a'));
  edge(1, 1, g, g.TransFac->getByte('a'));

  g[1].IsMatch = true;
  g[1].Label = 0;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g);

  ASSERT_EQUAL_GRAPHS(g, h);
  ASSERT_EQUAL_LABELS(g, h);
  ASSERT_EQUAL_MATCHES(g, h);
}

SCOPE_TEST(testDeterminize4) {
  NFA g(2);
  edge(0, 1, g, g.TransFac->getEither('a', 'b'));

  g[1].IsMatch = true;
  g[1].Label = 0;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g);

  NFA exp(2);
  ByteSet bytes;
  bytes['a'] = bytes['b'] = true;
  edge(0, 1, exp, exp.TransFac->getByteSet(bytes));

  exp[1].IsMatch = true;
  exp[1].Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testDeterminize5) {
  NFA g(4);
  edge(0, 1, g, g.TransFac->getByte('d'));
  edge(1, 2, g, g.TransFac->getByte('d'));
  edge(1, 1, g, g.TransFac->getByte('d'));
  edge(1, 3, g, g.TransFac->getByte('x'));
  edge(2, 1, g, g.TransFac->getByte('d'));
  edge(2, 3, g, g.TransFac->getByte('x'));

  g[3].IsMatch = true;
  g[3].Label = 0;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g);

  NFA exp(5);
  edge(0, 1, exp, exp.TransFac->getByte('d'));
  edge(1, 2, exp, exp.TransFac->getByte('x'));
  edge(1, 3, exp, exp.TransFac->getByte('d'));
  edge(3, 2, exp, exp.TransFac->getByte('x'));
  edge(3, 4, exp, exp.TransFac->getByte('d'));
  edge(4, 2, exp, exp.TransFac->getByte('x'));
  edge(4, 3, exp, exp.TransFac->getByte('d'));

  exp[2].IsMatch = true;
  exp[2].Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

SCOPE_TEST(testPruneBranches) {
  NFA g(3);
  edge(0, 1, g, g.TransFac->getByte('a'));
  edge(0, 2, g, g.TransFac->getByte('a'));

  g[1].IsMatch = true;
  g[1].Label = 0;

  NFAOptimizer comp;
  comp.pruneBranches(g);

  NFA exp(3);
  edge(0, 1, exp, exp.TransFac->getByte('a'));

  exp[2].Trans = exp.TransFac->getByte('a');

  exp[1].IsMatch = true;
  exp[1].Label = 0;

  ASSERT_EQUAL_GRAPHS(exp, g);
  ASSERT_EQUAL_LABELS(exp, g);
  ASSERT_EQUAL_MATCHES(exp, g);
}
