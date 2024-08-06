/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "nfabuilder.h"
#include "nfaoptimizer.h"
#include "parser.h"
#include "parsetree.h"
#include "encoders/encoderfactory.h"

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
    REQUIRE(av < b.verticesSize());

    for (uint32_t a_ov = 0; a_ov < a.outDegree(av); ++a_ov) {
      REQUIRE(a.outVertex(av, a_ov) < b.verticesSize());
      REQUIRE(edgeExists(b, av, a.outVertex(av, a_ov)));
    }
  }
}

void ASSERT_EQUAL_GRAPHS(const NFA& a, const NFA& b) {
  REQUIRE(a.verticesSize() == b.verticesSize());
  ASSERT_SUPERGRAPH(a, b);
  ASSERT_SUPERGRAPH(b, a);
}

void ASSERT_EQUAL_LABELS(const NFA& a, const NFA& b) {
  REQUIRE(a.verticesSize() == b.verticesSize());
  for (uint32_t v = 0; v < a.verticesSize(); ++v) {
    REQUIRE(((!a[v].Trans && !b[v].Trans) || (a[v].Trans && b[v].Trans)));
    if (a[v].Trans && b[v].Trans) {
      REQUIRE(a[v].Label == b[v].Label);
    }
  }
}

void ASSERT_EQUAL_MATCHES(const NFA& a, const NFA& b) {
  REQUIRE(a.verticesSize() == b.verticesSize());
  for (uint32_t v = 0; v < a.verticesSize(); ++v) {
    REQUIRE(((!a[v].Trans && !b[v].Trans) || (a[v].Trans && b[v].Trans)));
    if (a[v].Trans && b[v].Trans) {
      REQUIRE(a[v].IsMatch == b[v].IsMatch);
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
