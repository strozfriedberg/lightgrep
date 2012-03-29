#include <scope/test.h>

#include "test_helper.h"

void edge(NFA::VertexDescriptor source, NFA::VertexDescriptor target, NFA& fsm, Transition* trans) {

  while (source >= fsm.verticesSize()) fsm.addVertex();
  while (target >= fsm.verticesSize()) fsm.addVertex();

  fsm.addEdge(source, target);
  fsm[target].Trans = trans;
}

bool edgeExists(const NFA& g, const NFA::VertexDescriptor source, const NFA::VertexDescriptor target) {
  for (uint32 ov = 0; ov < g.outDegree(source); ++ov) {
    if (g.outVertex(source, ov) == target) {
      return true;
    }
  }
  return false;
}

void ASSERT_SUPERGRAPH(const NFA& a, const NFA& b) {
  for (uint32 av = 0; av < a.verticesSize(); ++av) {
    SCOPE_ASSERT(av < b.verticesSize());

    for (uint32 a_ov = 0; a_ov < a.outDegree(av); ++a_ov) {
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
  for (uint32 v = 0; v < a.verticesSize(); ++v) {
    SCOPE_ASSERT((!a[v].Trans && !b[v].Trans) || (a[v].Trans && b[v].Trans));
    if (a[v].Trans && b[v].Trans) {
      SCOPE_ASSERT_EQUAL(a[v].Label, b[v].Label);
    }
  }
}

void ASSERT_EQUAL_MATCHES(const NFA& a, const NFA& b) {
  SCOPE_ASSERT_EQUAL(a.verticesSize(), b.verticesSize());
  for (uint32 v = 0; v < a.verticesSize(); ++v) {
    SCOPE_ASSERT((!a[v].Trans && !b[v].Trans) || (a[v].Trans && b[v].Trans));
    if (a[v].Trans && b[v].Trans) {
      SCOPE_ASSERT_EQUAL(a[v].IsMatch, b[v].IsMatch);
    }
  }
}
