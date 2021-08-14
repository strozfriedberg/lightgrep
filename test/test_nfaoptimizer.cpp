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

#include "catch.hpp"

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

TEST_CASE("testMerge_aaOrab_toEmpty") {
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

  REQUIRE(4u == dst.verticesSize());

  REQUIRE(0u == dst.inDegree(0));
  REQUIRE(1u == dst.outDegree(0));
  REQUIRE(1u == dst.outVertex(0, 0));

  REQUIRE(1u == dst.inDegree(1));
  REQUIRE(2u == dst.outDegree(1));
  REQUIRE(2u == dst.outVertex(1, 0));
  REQUIRE(3u == dst.outVertex(1, 1));

  REQUIRE(1u == dst.inDegree(2));
  REQUIRE(0u == dst.outDegree(2));

  REQUIRE(1u == dst.inDegree(3));
  REQUIRE(0u == dst.outDegree(3));

  REQUIRE(getBytes(*a) == getBytes(*dst[2].Trans));
  REQUIRE(getBytes(*b) == getBytes(*dst[3].Trans));
}

TEST_CASE("testMerge") {
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

  REQUIRE(8u == fsm.verticesSize());

  REQUIRE(!fsm[0].Trans);
  REQUIRE(0u == fsm.inDegree(0));
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.outVertex(0, 0));

  REQUIRE(NOLABEL == fsm[1].Label);
  REQUIRE(1u == fsm.inDegree(1));
  REQUIRE(0u == fsm.inVertex(1, 0));
  REQUIRE(3u == fsm.outDegree(1));
  REQUIRE(6u == fsm.outVertex(1, 0));
  REQUIRE(2u == fsm.outVertex(1, 1));
  REQUIRE(4u == fsm.outVertex(1, 2));

  REQUIRE(NOLABEL == fsm[2].Label);
  REQUIRE(1u == fsm.inDegree(2));
  REQUIRE(1u == fsm.inVertex(2, 0));
  REQUIRE(2u == fsm.outDegree(2));
  REQUIRE(3u == fsm.outVertex(2, 0));
  REQUIRE(7u == fsm.outVertex(2, 1));

  REQUIRE(0u == fsm[3].Label);
  REQUIRE(1u == fsm.inDegree(3));
  REQUIRE(2u == fsm.inVertex(3, 0));
  REQUIRE(0u == fsm.outDegree(3));

  REQUIRE(NOLABEL == fsm[4].Label);
  REQUIRE(1u == fsm.inDegree(4));
  REQUIRE(1u == fsm.inVertex(4, 0));
  REQUIRE(1u == fsm.outDegree(4));
  REQUIRE(5u == fsm.outVertex(4, 0));

  REQUIRE(1u == fsm[5].Label);
  REQUIRE(1u == fsm.inDegree(5));
  REQUIRE(4u == fsm.inVertex(5, 0));
  REQUIRE(0u == fsm.outDegree(5));

  REQUIRE(NOLABEL == fsm[6].Label);
  REQUIRE(1u == fsm.inDegree(6));
  REQUIRE(1u == fsm.inVertex(6, 0));
  REQUIRE(1u == fsm.outDegree(6));
  REQUIRE(7u == fsm.outVertex(6, 0));

  REQUIRE(2u == fsm[7].Label);
  REQUIRE(3u == fsm.inDegree(7));
  REQUIRE(6u == fsm.inVertex(7, 0));
  REQUIRE(7u == fsm.inVertex(7, 1));
  REQUIRE(2u == fsm.inVertex(7, 2));
  REQUIRE(1u == fsm.outDegree(7));
  REQUIRE(7u == fsm.outVertex(7, 0));
}

TEST_CASE("testMergeLabelsSimple") {
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

TEST_CASE("testMergeLabelsComplex") {
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

TEST_CASE("testGuardLabelsFourKeys") {
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

TEST_CASE("testPropagateMatchLabels") {
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

  REQUIRE(0u == g[1].Label);
  REQUIRE(1u == g[2].Label);
  REQUIRE(2u == g[3].Label);
  REQUIRE(2u == g[4].Label);
  REQUIRE(2u == g[5].Label);
}

TEST_CASE("testRemoveNonMinimalLabels") {
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

  REQUIRE(0u == g[1].Label);
  REQUIRE(1u == g[2].Label);
  REQUIRE(2u == g[3].Label);
  REQUIRE(NONE == g[4].Label);
  REQUIRE(NONE == g[5].Label);
}

TEST_CASE("testLabelGuardStates") {
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

  REQUIRE(0u == g[1].Label);
  REQUIRE(1u == g[2].Label);
  REQUIRE(2u == g[3].Label);
  REQUIRE(NONE == g[4].Label);
  REQUIRE(NONE == g[5].Label);
}

TEST_CASE("testSubstringKey") {
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

TEST_CASE("testCreateXXYYY") {
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

TEST_CASE("testDeterminize0") {
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

TEST_CASE("testDeterminize1") {
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

TEST_CASE("testDeterminize2") {
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

TEST_CASE("testDeterminize3") {
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

TEST_CASE("testDeterminize4") {
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

TEST_CASE("testDeterminize5") {
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

TEST_CASE("testDeterminizePartial0") {
  const ByteSet az{{'a', 'z' + 1}};

  NFA g(5);
  edge(0, 1, g, g.TransFac->getByteSet(az));
  edge(1, 1, g, g.TransFac->getByteSet(az));
  edge(1, 2, g, g.TransFac->getByte('i'));
  edge(0, 3, g, g.TransFac->getByteSet(az));
  edge(3, 3, g, g.TransFac->getByteSet(az));
  edge(3, 4, g, g.TransFac->getByte('m'));

  g[1].Label = 0;
  g[3].Label = 1;
  g[2].IsMatch = true;
  g[4].IsMatch = true;

  NFA exp(5);
  edge(0, 1, exp, exp.TransFac->getByteSet(az));
  edge(1, 1, exp, exp.TransFac->getByteSet(az));
  edge(1, 4, exp, exp.TransFac->getByte('i'));
  edge(0, 2, exp, exp.TransFac->getByteSet(az));
  edge(2, 2, exp, exp.TransFac->getByteSet(az));
  edge(2, 3, exp, exp.TransFac->getByte('m'));

  exp[1].Label = 0;
  exp[2].Label = 1;
  exp[3].IsMatch = true;
  exp[4].IsMatch = true;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g, 0);

  // 0-depth partial determinization = no determinization at all
  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

TEST_CASE("testDeterminizePartial1") {
  const ByteSet az{{'a', 'z' + 1}};

  NFA g(5);
  edge(0, 1, g, g.TransFac->getByteSet(az));
  edge(1, 1, g, g.TransFac->getByteSet(az));
  edge(1, 2, g, g.TransFac->getByte('i'));
  edge(0, 3, g, g.TransFac->getByteSet(az));
  edge(3, 3, g, g.TransFac->getByteSet(az));
  edge(3, 4, g, g.TransFac->getByte('m'));

  g[1].Label = 0;
  g[3].Label = 1;
  g[2].IsMatch = true;
  g[4].IsMatch = true;

  NFA exp(6);
  edge(0, 1, exp, exp.TransFac->getByteSet(az));
  edge(1, 2, exp, exp.TransFac->getByteSet(az));
  edge(1, 3, exp, exp.TransFac->getByte('i'));
  edge(1, 4, exp, exp.TransFac->getByteSet(az));
  edge(1, 5, exp, exp.TransFac->getByte('i'));
  edge(2, 2, exp, exp.TransFac->getByteSet(az));
  edge(2, 3, exp, exp.TransFac->getByte('i'));
  edge(4, 4, exp, exp.TransFac->getByteSet(az));
  edge(4, 5, exp, exp.TransFac->getByte('m'));

  exp[2].Label = 0;
  exp[4].Label = 1;
  exp[3].IsMatch = true;
  exp[5].IsMatch = true;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g, 1);

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

TEST_CASE("testDeterminizePartial2") {
  const ByteSet az{{'a', 'z' + 1}};
  const ByteSet ahjlnz{{'a', 'h' + 1}, {'j', 'l' + 1}, {'n', 'z' + 1}};

  NFA g(5);
  edge(0, 1, g, g.TransFac->getByteSet(az));
  edge(1, 1, g, g.TransFac->getByteSet(az));
  edge(1, 2, g, g.TransFac->getByte('i'));
  edge(0, 3, g, g.TransFac->getByteSet(az));
  edge(3, 3, g, g.TransFac->getByteSet(az));
  edge(3, 4, g, g.TransFac->getByte('m'));

  g[1].Label = 0;
  g[3].Label = 1;
  g[2].IsMatch = true;
  g[4].IsMatch = true;

  NFA exp(12);
  edge(0, 1, exp, exp.TransFac->getByteSet(az));

  edge(1, 2, exp, exp.TransFac->getByte('i'));
  edge(1, 3, exp, exp.TransFac->getByte('i'));
  edge(1, 4, exp, exp.TransFac->getByte('i'));
  edge(1, 5, exp, exp.TransFac->getByte('m'));
  edge(1, 6, exp, exp.TransFac->getByte('m'));
  edge(1, 7, exp, exp.TransFac->getByteSet(ahjlnz));

  edge(2, 8, exp, exp.TransFac->getByteSet(az));
  edge(2, 9, exp, exp.TransFac->getByte('i'));

  edge(4, 10, exp, exp.TransFac->getByteSet(az));
  edge(4, 11, exp, exp.TransFac->getByte('m'));

  edge(5, 8, exp, exp.TransFac->getByteSet(az));
  edge(5, 9, exp, exp.TransFac->getByte('i'));
  edge(5, 10, exp, exp.TransFac->getByteSet(az));
  edge(5, 11, exp, exp.TransFac->getByte('m'));

  edge(7, 8, exp, exp.TransFac->getByteSet(az));
  edge(7, 9, exp, exp.TransFac->getByte('i'));
  edge(7, 10, exp, exp.TransFac->getByteSet(az));
  edge(7, 11, exp, exp.TransFac->getByte('m'));

  edge(8, 8, exp, exp.TransFac->getByteSet(az));
  edge(8, 9, exp, exp.TransFac->getByte('i'));

  edge(10, 10, exp, exp.TransFac->getByteSet(az));
  edge(10, 11, exp, exp.TransFac->getByte('m'));

  // NB: This is an odd looking set of labels becuase we're not calling
  // comp.labelGuardStates() to walk back the labels
  exp[8].Label = 0;
  exp[10].Label = 1;
  exp[3].IsMatch = true;
  exp[6].IsMatch = true;
  exp[9].IsMatch = true;
  exp[11].IsMatch = true;

  NFA h(1);
  NFAOptimizer comp;
  comp.subsetDFA(h, g, 2);

  ASSERT_EQUAL_GRAPHS(exp, h);
  ASSERT_EQUAL_LABELS(exp, h);
  ASSERT_EQUAL_MATCHES(exp, h);
}

TEST_CASE("testPruneBranches") {
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

TEST_CASE("testConnectSubsetStateToOriginal0") {
  NFA src(6);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('b'));
  edge(1, 4, src, src.TransFac->getByte('c'));
  edge(2, 3, src, src.TransFac->getByte('d'));
  edge(3, 5, src, src.TransFac->getByte('e'));

  NFA dst(1);

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{
    {1,0}, {3,0}
  };

  NFA exp(3);
  exp.addEdge(0, 1);
  exp.addEdge(0, 2);

  connectSubsetStateToOriginal(dst, src, {1,3}, 0, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
}

TEST_CASE("testConnectSubsetStateToOriginal1") {
  NFA src(6);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('b'));
  edge(1, 4, src, src.TransFac->getByte('c'));
  edge(2, 3, src, src.TransFac->getByte('d'));
  edge(3, 5, src, src.TransFac->getByte('e'));

  NFA dst(2);
  edge(0, 1, dst, dst.TransFac->getByte('a'));

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{
    {1,0}, {3,0}, {4,1}
  };

  NFA exp(2);
  exp.addEdge(0, 1);

  connectSubsetStateToOriginal(dst, src, {4}, 1, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
}

TEST_CASE("testConnectSubsetStateToOriginal2") {
  NFA src(6);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('b'));
  edge(1, 4, src, src.TransFac->getByte('c'));
  edge(2, 3, src, src.TransFac->getByte('d'));
  edge(3, 5, src, src.TransFac->getByte('e'));

  NFA dst(2);
  edge(0, 1, dst, dst.TransFac->getByte('a'));

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{
    {1,0}, {3,0}, {4,1}
  };

  NFA exp(3);
  exp.addEdge(0, 1);
  exp.addEdge(0, 2);

  connectSubsetStateToOriginal(dst, src, {1, 3}, 0, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
}

TEST_CASE("testCompleteOriginal0") {
  // When src and dst are the same and src2Dst is an identity map,
  // completeOriginal() should be a no-op.
  NFA src(3);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('a'));

  src[2].IsMatch = true;
  src[2].Label = 1;

  NFA dst(src);

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{
    {1, 1}, {2, 2}
  };

  NFA exp(src);

  completeOriginal(dst, src, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

TEST_CASE("testCompleteOriginal1") {
  NFA src(3);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('a'));

  src[2].IsMatch = true;
  src[2].Label = 1;

  NFA dst(2);
  edge(0, 1, dst, dst.TransFac->getByte('a'));

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{ {1, 1} };

  NFA exp(src);

  completeOriginal(dst, src, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

TEST_CASE("testCompleteOriginal2") {
  NFA src(4);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('b'));
  edge(1, 3, src, src.TransFac->getByte('c'));

  src[2].IsMatch = true;
  src[2].Label = 1;

  src[3].IsMatch = true;
  src[3].Label = 2;

  NFA dst(2);
  edge(0, 1, dst, dst.TransFac->getByte('a'));

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{ {1, 1} };

  NFA exp(src);

  completeOriginal(dst, src, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

TEST_CASE("testCompleteOriginal3") {
  /*
            2
           /
      0 - 1
           \
            3

    applied to

      0 - 1
       \
        2

    with 1 mapping to 1 should yield

            3
           /
      0 - 1
      |    \
      2     4

    with 2 mapping to 3, 3 mapping to 4.

  */
  NFA src(4);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('b'));
  edge(1, 3, src, src.TransFac->getByte('c'));

  src[2].IsMatch = true;
  src[2].Label = 1;

  src[3].IsMatch = true;
  src[3].Label = 2;

  NFA dst(3);
  edge(0, 1, dst, dst.TransFac->getByte('a'));
  edge(0, 2, dst, dst.TransFac->getByte('d'));

  dst[2].IsMatch = true;
  dst[2].Label = 3;

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{ {1, 1} };

  NFA exp(5);
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(0, 2, exp, exp.TransFac->getByte('d'));
  edge(1, 3, exp, exp.TransFac->getByte('b'));
  edge(1, 4, exp, exp.TransFac->getByte('c'));

  exp[2].IsMatch = true;
  exp[2].Label = 3;

  exp[3].IsMatch = true;
  exp[3].Label = 1;

  exp[4].IsMatch = true;
  exp[4].Label = 2;

  completeOriginal(dst, src, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

TEST_CASE("testCompleteOriginal4") {
  /*
             o
         1 - 2 - 3
        /
       0
        \
         4 - 5

    applied to

                3
          o    /
      0 - 1 - 2
               \
                4

    with 1 mapping to 3 and 4 mapping to 4 should yield

                    o
                3 - 6 - 7
          o    /
      0 - 1 - 2
               \
                4 - 5

    with 2 mapping to 6, 3 mapping to 7, 5 mapping to 5.

  */
  NFA src(6);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 2, src, src.TransFac->getByte('b'));
  edge(2, 2, src, src.TransFac->getByte('b'));
  edge(2, 3, src, src.TransFac->getByte('c'));
  edge(0, 4, src, src.TransFac->getByte('d'));
  edge(4, 5, src, src.TransFac->getByte('e'));

  src[3].IsMatch = true;
  src[3].Label = 1;

  src[5].IsMatch = true;
  src[5].Label = 2;

  NFA dst(5);
  edge(0, 1, dst, dst.TransFac->getByte('w'));
  edge(1, 1, dst, dst.TransFac->getByte('w'));
  edge(1, 2, dst, dst.TransFac->getByte('x'));
  edge(2, 3, dst, dst.TransFac->getByte('y'));
  edge(2, 4, dst, dst.TransFac->getByte('z'));

  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst{
    {1, 3}, { 4, 4 }
  };

  NFA exp(8);
  edge(0, 1, exp, exp.TransFac->getByte('w'));
  edge(1, 1, exp, exp.TransFac->getByte('w'));
  edge(1, 2, exp, exp.TransFac->getByte('x'));
  edge(2, 3, exp, exp.TransFac->getByte('y'));
  edge(2, 4, exp, exp.TransFac->getByte('z'));
  edge(3, 6, exp, exp.TransFac->getByte('b'));
  edge(6, 6, exp, exp.TransFac->getByte('b'));
  edge(6, 7, exp, exp.TransFac->getByte('c'));
  edge(4, 5, exp, exp.TransFac->getByte('e'));

  exp[7].IsMatch = true;
  exp[7].Label = 1;

  exp[5].IsMatch = true;
  exp[5].Label = 2;

  completeOriginal(dst, src, src2Dst);
  ASSERT_EQUAL_GRAPHS(exp, dst);
  ASSERT_EQUAL_LABELS(exp, dst);
  ASSERT_EQUAL_MATCHES(exp, dst);
}

TEST_CASE("testMakeDestinationState0") {
  NFA src(4);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 1, src, src.TransFac->getByte('a'));
  edge(1, 3, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('a'));
  edge(2, 1, src, src.TransFac->getByte('a'));
  edge(2, 3, src, src.TransFac->getByte('a'));
  edge(3, 2, src, src.TransFac->getByte('a'));

  src[3].IsMatch = true;
  src[3].Label = 1;

  const ByteSet bs('a');

  NFA dst(1);
  SubsetStateToState dstList2Dst;
  std::stack<std::pair<SubsetState, int>> dstStack;

  makeDestinationState(src, 0, bs, {1,2}, 1, dst, dstList2Dst, dstStack);

  NFA exp(2);
  edge(0, 1, exp, exp.TransFac->getByte('a'));

  const decltype(dstList2Dst) exp_dstList2Dst{{SubsetState{bs, {1,2}}, 1}};

  const std::vector<std::pair<SubsetState, int>> dstUnstack = unstack(dstStack);
  const decltype(dstUnstack) exp_dstUnstack{{SubsetState{bs, {1,2}}, 1}};

  ASSERT_EQUAL_GRAPHS(exp, dst);
  REQUIRE(exp_dstList2Dst == dstList2Dst);
  REQUIRE(exp_dstUnstack == dstUnstack);
}

TEST_CASE("testMakeDestinationState1") {
  NFA src(4);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 1, src, src.TransFac->getByte('a'));
  edge(1, 3, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('a'));
  edge(2, 1, src, src.TransFac->getByte('a'));
  edge(2, 3, src, src.TransFac->getByte('a'));
  edge(3, 2, src, src.TransFac->getByte('a'));

  src[3].IsMatch = true;
  src[3].Label = 1;

  const ByteSet bs('a');

  NFA dst(2);
  edge(0, 1, dst, dst.TransFac->getByte('a'));

  SubsetStateToState dstList2Dst{{SubsetState{bs, {1,2}}, 1}};
  std::stack<std::pair<SubsetState, int>> dstStack;

  makeDestinationState(src, 0, bs, {1,2}, 1, dst, dstList2Dst, dstStack);

  NFA exp(2);
  edge(0, 1, exp, exp.TransFac->getByte('a'));

  const decltype(dstList2Dst) exp_dstList2Dst{{SubsetState{bs, {1,2}}, 1}};

  const std::vector<std::pair<SubsetState, int>> dstUnstack = unstack(dstStack);
  const decltype(dstUnstack) exp_dstUnstack;

  ASSERT_EQUAL_GRAPHS(exp, dst);
  REQUIRE(exp_dstList2Dst == dstList2Dst);
  REQUIRE(exp_dstUnstack == dstUnstack);
}

TEST_CASE("testHandleSubstateStateSuccessors0") {
  NFA src(4);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 1, src, src.TransFac->getByte('a'));
  edge(1, 3, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('a'));
  edge(2, 1, src, src.TransFac->getByte('a'));
  edge(2, 3, src, src.TransFac->getByte('a'));
  edge(3, 2, src, src.TransFac->getByte('a'));

  src[3].IsMatch = true;
  src[3].Label = 1;

  const ByteSet bs('a');

  NFA dst(1);
  std::stack<std::pair<SubsetState, int>> dstStack;
  ByteSet outBytes; // not an output param, supplied for reuse
  SubsetStateToState dstList2Dst;

  handleSubsetStateSuccessors(
    src, {0}, 0, 1, dst, dstStack, outBytes, dstList2Dst
  );

  NFA exp(2);
  edge(0, 1, exp, exp.TransFac->getByte('a'));

  const decltype(dstList2Dst) exp_dstList2Dst{{SubsetState{bs, {1,2}}, 1}};

  const std::vector<std::pair<SubsetState, int>> dstUnstack = unstack(dstStack);
  const decltype(dstUnstack) exp_dstUnstack{{SubsetState{bs, {1,2}}, 1}};

  ASSERT_EQUAL_GRAPHS(exp, dst);
  REQUIRE(exp_dstList2Dst == dstList2Dst);
  REQUIRE(exp_dstUnstack == dstUnstack);
}

TEST_CASE("testHandleSubstateStateSuccessors1") {
  NFA src(4);
  edge(0, 1, src, src.TransFac->getByte('a'));
  edge(1, 1, src, src.TransFac->getByte('a'));
  edge(1, 3, src, src.TransFac->getByte('a'));
  edge(0, 2, src, src.TransFac->getByte('a'));
  edge(2, 1, src, src.TransFac->getByte('a'));
  edge(2, 3, src, src.TransFac->getByte('a'));
  edge(3, 2, src, src.TransFac->getByte('a'));

  src[3].IsMatch = true;
  src[3].Label = 1;

  const ByteSet bs('a');

  NFA dst(1);
  edge(0, 1, dst, dst.TransFac->getByte('a'));

  std::stack<std::pair<SubsetState, int>> dstStack;
  ByteSet outBytes; // not an output param, supplied for reuse
  SubsetStateToState dstList2Dst{{SubsetState{bs, {1,2}}, 1}};

  handleSubsetStateSuccessors(
    src, {1,2}, 1, 2, dst, dstStack, outBytes, dstList2Dst
  );

  NFA exp(4);
  edge(0, 1, exp, exp.TransFac->getByte('a'));
  edge(1, 2, exp, exp.TransFac->getByte('a'));
  edge(1, 3, exp, exp.TransFac->getByte('a'));

  dst[2].IsMatch = true;
  dst[2].Label = 1;

  const decltype(dstList2Dst) exp_dstList2Dst{
    {SubsetState{bs, {1,2}}, 1},
    {SubsetState{bs, {1}},   2},
    {SubsetState{bs, {3}},   3}
  };

  const std::vector<std::pair<SubsetState, int>> dstUnstack = unstack(dstStack);
  const decltype(dstUnstack) exp_dstUnstack{
    {SubsetState{bs, {3}}, 2},
    {SubsetState{bs, {1}}, 2}
  };

  ASSERT_EQUAL_GRAPHS(exp, dst);
  REQUIRE(exp_dstList2Dst == dstList2Dst);
  REQUIRE(exp_dstUnstack == dstUnstack);
}
