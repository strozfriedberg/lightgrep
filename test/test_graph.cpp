#include <scope/test.h>

#include "graph.h"

SCOPE_TEST(numVerticesWithReserve) {
  Graph g(0, 1);
  SCOPE_ASSERT_EQUAL(1, g.capacity());
  SCOPE_ASSERT_EQUAL(0, g.addVertex());
  SCOPE_ASSERT_EQUAL(1, g.capacity());
  SCOPE_ASSERT_EQUAL(1, g.addVertex());
  SCOPE_ASSERT(2 <= g.capacity());
  SCOPE_ASSERT_EQUAL(2, g.addVertex());
  SCOPE_ASSERT(3 <= g.capacity());
}

SCOPE_TEST(fsmAddVertex) {
  Graph g(0);
  SCOPE_ASSERT_EQUAL(0, g.addVertex());
  SCOPE_ASSERT_EQUAL(1, g.addVertex());
  SCOPE_ASSERT_EQUAL(2, g.addVertex());
}

SCOPE_TEST(fsmInEdges) {
  // two disconnected nodes
  Graph g(2);
  SCOPE_ASSERT_EQUAL(2, g.numVertices());
  SCOPE_ASSERT_EQUAL(0, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(1));

  // add 0 -> 1
  SCOPE_ASSERT(!g.edgeExists(0, 1));
  g.addEdge(0, 1);
  SCOPE_ASSERT(g.edgeExists(0, 1));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(1, 0));

  // add 0 -> 0
  SCOPE_ASSERT(!g.edgeExists(0, 0));
  g.addEdge(0, 0);
  SCOPE_ASSERT(g.edgeExists(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(1, 0));
}

SCOPE_TEST(fsmOutEdges) {
  // two disconnected nodes
  Graph g(2);
  SCOPE_ASSERT_EQUAL(2, g.numVertices());
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));

  // add 0 -> 1
  SCOPE_ASSERT(!g.edgeExists(0, 1));
  g.addEdge(0, 1);
  SCOPE_ASSERT(g.edgeExists(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(1));

  // add 0 -> 0
  SCOPE_ASSERT(!g.edgeExists(0, 0));
  g.addEdge(0, 0);
  SCOPE_ASSERT(g.edgeExists(0, 0));
  SCOPE_ASSERT_EQUAL(2, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outVertex(0, 1));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(1));
}

SCOPE_TEST(fsmManyInZeroOutItr) {
  // This tests the situation where a node has ZERO out-, but MANY indegree.
  Graph g(3);
  g.addEdge(0, 2);
  g.addEdge(1, 2);

  SCOPE_ASSERT_EQUAL(0, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(2, 0));
  SCOPE_ASSERT_EQUAL(1, g.inVertex(2, 1));

  SCOPE_ASSERT_EQUAL(1, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(2));
}

SCOPE_TEST(fsmClear) {
  Graph g(1);
  g.addEdge(0, 0);

  SCOPE_ASSERT_EQUAL(1, g.numVertices());
  g.clear();
  SCOPE_ASSERT_EQUAL(0, g.numVertices());
}

SCOPE_TEST(fsmVertexSize) {
  SCOPE_ASSERT(sizeof(Graph::Vertex) <= 32);
}
