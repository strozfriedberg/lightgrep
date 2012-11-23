/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

#include <memory>

#include "encoderfactory.h"
#include "nfabuilder.h"
#include "nfaoptimizer.h"
#include "parser.h"
#include "parsetree.h"

#include "test_helper.h"

void edge(NFA::VertexDescriptor source, NFA::VertexDescriptor target, NFA& fsm, Transition* trans) {

  while (source >= fsm.verticesSize()) fsm.addVertex();
  while (target >= fsm.verticesSize()) fsm.addVertex();

  fsm.addEdge(source, target);
  fsm[target].Trans = trans;
}

bool edgeExists(const NFA& g, const NFA::VertexDescriptor source, const NFA::VertexDescriptor target) {
  for (uint32_t ov = 0; ov < g.outDegree(source); ++ov) {
    if (g.outVertex(source, ov) == target) {
      return true;
    }
  }
  return false;
}

void ASSERT_SUPERGRAPH(const NFA& a, const NFA& b) {
  for (uint32_t av = 0; av < a.verticesSize(); ++av) {
    SCOPE_ASSERT(av < b.verticesSize());

    for (uint32_t a_ov = 0; a_ov < a.outDegree(av); ++a_ov) {
      SCOPE_ASSERT(a.outVertex(av, a_ov) < b.verticesSize());
      SCOPE_ASSERT(edgeExists(b, av, a.outVertex(av, a_ov)));
    }
  }
}

void ASSERT_EQUAL_GRAPHS(const NFA& a, const NFA& b) {
  SCOPE_ASSERT_EQUAL(a.verticesSize(), b.verticesSize());
  ASSERT_SUPERGRAPH(a, b);
  ASSERT_SUPERGRAPH(b, a);
}

void ASSERT_EQUAL_LABELS(const NFA& a, const NFA& b) {
  SCOPE_ASSERT_EQUAL(a.verticesSize(), b.verticesSize());
  for (uint32_t v = 0; v < a.verticesSize(); ++v) {
    SCOPE_ASSERT((!a[v].Trans && !b[v].Trans) || (a[v].Trans && b[v].Trans));
    if (a[v].Trans && b[v].Trans) {
      SCOPE_ASSERT_EQUAL(a[v].Label, b[v].Label);
    }
  }
}

void ASSERT_EQUAL_MATCHES(const NFA& a, const NFA& b) {
  SCOPE_ASSERT_EQUAL(a.verticesSize(), b.verticesSize());
  for (uint32_t v = 0; v < a.verticesSize(); ++v) {
    SCOPE_ASSERT((!a[v].Trans && !b[v].Trans) || (a[v].Trans && b[v].Trans));
    if (a[v].Trans && b[v].Trans) {
      SCOPE_ASSERT_EQUAL(a[v].IsMatch, b[v].IsMatch);
    }
  }
}

NFAPtr createGraph(const std::vector<Pattern>& pats, bool determinize) {
  EncoderFactory encfac;
  NFABuilder nfab;
  ParseTree tree;
  NFAOptimizer comp;
  NFAPtr g(new NFA(1));

  for (uint32_t i = 0; i < pats.size(); ++i) {
    parse(pats[i], tree);

    nfab.reset();
    nfab.setCurLabel(i);
    nfab.setEncoder(encfac.get(pats[i].Encoding));

    if (nfab.build(tree)) {
      comp.pruneBranches(*nfab.getFsm());
      comp.mergeIntoFSM(*g, *nfab.getFsm());
    }
  }

  if (determinize) {
    NFA dfa(1);
    comp.subsetDFA(dfa, *g);
    comp.labelGuardStates(dfa);
    *g = dfa;
  }

  return g;
}
