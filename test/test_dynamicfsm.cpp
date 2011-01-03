#include <scope/test.h>

#include "newdynamicFSM.h"

SCOPE_TEST(numVerticesWithReserve) {
  DynamicFSM g(0, 1);
  SCOPE_ASSERT_EQUAL(1, g.capacity());
  SCOPE_ASSERT_EQUAL(0, g.addVertex());
  SCOPE_ASSERT_EQUAL(1, g.capacity());
  SCOPE_ASSERT_EQUAL(1, g.addVertex());
  SCOPE_ASSERT(2 <= g.capacity());
  SCOPE_ASSERT_EQUAL(2, g.addVertex());
  SCOPE_ASSERT(3 <= g.capacity());
}

SCOPE_TEST(fsmAddVertex) {
  DynamicFSM g(0);
  SCOPE_ASSERT_EQUAL(0, g.addVertex());
  SCOPE_ASSERT_EQUAL(1, g.addVertex());
  SCOPE_ASSERT_EQUAL(2, g.addVertex());
}

SCOPE_TEST(fsmInEdges) {
  DynamicFSM g(2);
  SCOPE_ASSERT_EQUAL(0, g.inVertices(0).size());
  SCOPE_ASSERT_EQUAL(0, g.inVertices(1).size());
  g.addEdge(0, 1);
  SCOPE_ASSERT(g.edgeExists(0, 1));
  SCOPE_ASSERT_EQUAL(0, g.inVertices(0).size());
  SCOPE_ASSERT_EQUAL(1, g.inVertices(1).size());
  SCOPE_ASSERT_EQUAL(0, g.inVertices(1)[0]);
  g.addEdge(0, 0);
  SCOPE_ASSERT(g.edgeExists(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inVertices(0).size());
  SCOPE_ASSERT_EQUAL(2, g.outVertices(0).size());
  SCOPE_ASSERT_EQUAL(1, g.outVertices(0)[0]);
  SCOPE_ASSERT_EQUAL(0, g.outVertices(0)[1]);
}

SCOPE_TEST(fsmOutEdges) {
  DynamicFSM g(2);
  SCOPE_ASSERT_EQUAL(0, g.outVertices(0).size());
  SCOPE_ASSERT_EQUAL(0, g.outVertices(0).size());
  g.addEdge(0, 1);
  SCOPE_ASSERT(g.edgeExists(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.outVertices(0).size());
  SCOPE_ASSERT_EQUAL(0, g.outVertices(1).size());
  SCOPE_ASSERT_EQUAL(1, g.outVertices(0)[0]);
}

SCOPE_TEST(fsmVertexSize) {
//  SCOPE_ASSERT_EQUAL(12, sizeof(TransitionPtr));
  SCOPE_ASSERT_EQUAL(34, sizeof(DynamicFSM::Vertex));  
}
