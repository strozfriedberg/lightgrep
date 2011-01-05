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

  {
    Graph::const_iterator b0(g.inVerticesBegin(0));
    Graph::const_iterator e0(g.inVerticesEnd(0));
    SCOPE_ASSERT(e0 == b0);
  
    Graph::const_iterator b1(g.inVerticesBegin(1));
    Graph::const_iterator e1(g.inVerticesEnd(1));
    SCOPE_ASSERT(e1 == b1);
  }

  // add 0 -> 1
  SCOPE_ASSERT(!g.edgeExists(0, 1));
  g.addEdge(0, 1);
  SCOPE_ASSERT(g.edgeExists(0, 1));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(1));

  {
    Graph::const_iterator b0(g.inVerticesBegin(0));
    Graph::const_iterator e0(g.inVerticesEnd(0));
    SCOPE_ASSERT(e0 == b0);
  
    Graph::const_iterator b1(g.inVerticesBegin(1));
    Graph::const_iterator e1(g.inVerticesEnd(1));
    SCOPE_ASSERT_EQUAL(0, *b1++);
    SCOPE_ASSERT(e1 == b1);
  }

  // add 0 -> 0
  SCOPE_ASSERT(!g.edgeExists(0, 0));
  g.addEdge(0, 0);
  SCOPE_ASSERT(g.edgeExists(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(1));

  {
    Graph::const_iterator b0(g.inVerticesBegin(0));
    Graph::const_iterator e0(g.inVerticesEnd(0));
    SCOPE_ASSERT_EQUAL(0, *b0++);
    SCOPE_ASSERT(e0 == b0);

    Graph::const_iterator b1(g.inVerticesBegin(1));
    Graph::const_iterator e1(g.inVerticesEnd(1));
    SCOPE_ASSERT_EQUAL(0, *b1++);
    SCOPE_ASSERT(e1 == b1);
  }
}

SCOPE_TEST(fsmOutEdges) {
  // two disconnected nodes
  Graph g(2);
  SCOPE_ASSERT_EQUAL(2, g.numVertices());
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));

  {
    Graph::const_iterator b0(g.outVerticesBegin(0));
    Graph::const_iterator e0(g.outVerticesEnd(0));
    SCOPE_ASSERT(e0 == b0);
  
    Graph::const_iterator b1(g.outVerticesBegin(1));
    Graph::const_iterator e1(g.outVerticesEnd(1));
    SCOPE_ASSERT(e1 == b1);
  }

  // add 0 -> 1
  SCOPE_ASSERT(!g.edgeExists(0, 1));
  g.addEdge(0, 1);
  SCOPE_ASSERT(g.edgeExists(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(1));

  {
    Graph::const_iterator b0(g.outVerticesBegin(0));
    Graph::const_iterator e0(g.outVerticesEnd(0));
    SCOPE_ASSERT_EQUAL(1, *b0++);
    SCOPE_ASSERT(e0 == b0);
  
    Graph::const_iterator b1(g.outVerticesBegin(1));
    Graph::const_iterator e1(g.outVerticesEnd(1));
    SCOPE_ASSERT(e1 == b1);
  }

  // add 0 -> 0
  SCOPE_ASSERT(!g.edgeExists(0, 0));
  g.addEdge(0, 0);
  SCOPE_ASSERT(g.edgeExists(0, 0));
  SCOPE_ASSERT_EQUAL(2, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(1));
  
  {
    Graph::const_iterator b0(g.outVerticesBegin(0));
    Graph::const_iterator e0(g.outVerticesEnd(0));
    SCOPE_ASSERT_EQUAL(1, *b0++);
    SCOPE_ASSERT_EQUAL(0, *b0++);
    SCOPE_ASSERT(e0 == b0);
  
    Graph::const_iterator b1(g.outVerticesBegin(1));
    Graph::const_iterator e1(g.outVerticesEnd(1));
    SCOPE_ASSERT(e1 == b1);
  }
}

SCOPE_TEST(fsmManyInZeroOutItr) {
  // This tests the situation where a node has ZERO out-, but MANY indegree.
  Graph g(3);
  g.addEdge(0, 2);
  g.addEdge(1, 2);

  Graph::const_iterator bo2(g.outVerticesBegin(2));
  Graph::const_iterator eo2(g.outVerticesEnd(2));
  SCOPE_ASSERT(eo2 == bo2);

  Graph::const_iterator bi2(g.inVerticesBegin(2));
  Graph::const_iterator ei2(g.inVerticesEnd(2));
  SCOPE_ASSERT_EQUAL(0, *bi2++);
  SCOPE_ASSERT_EQUAL(1, *bi2++);
  SCOPE_ASSERT(ei2 == bi2);
}

SCOPE_TEST(fsmInItrPreIncrement) {
  Graph g(3);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);

  Graph::const_iterator bi0(g.inVerticesBegin(0));
  Graph::const_iterator ei0(g.inVerticesEnd(0));
  SCOPE_ASSERT(ei0 == bi0);

  Graph::const_iterator bi1(g.inVerticesBegin(1));
  Graph::const_iterator ei1(g.inVerticesEnd(1));
  SCOPE_ASSERT_EQUAL(0, *bi1);
  SCOPE_ASSERT(ei1 == ++bi1);

  Graph::const_iterator bi2(g.inVerticesBegin(2));
  Graph::const_iterator ei2(g.inVerticesEnd(2));
  SCOPE_ASSERT_EQUAL(0, *bi2);
  SCOPE_ASSERT_EQUAL(1, *(++bi2));
  SCOPE_ASSERT(ei2 == ++bi2);
}

SCOPE_TEST(fsmInItrPostIncrement) {
  Graph g(3);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);

  Graph::const_iterator bi0(g.inVerticesBegin(0));
  Graph::const_iterator ei0(g.inVerticesEnd(0));
  SCOPE_ASSERT(ei0 == bi0);

  Graph::const_iterator bi1(g.inVerticesBegin(1));
  Graph::const_iterator ei1(g.inVerticesEnd(1));
  SCOPE_ASSERT_EQUAL(0, *bi1++);
  SCOPE_ASSERT(ei1 == bi1);

  Graph::const_iterator bi2(g.inVerticesBegin(2));
  Graph::const_iterator ei2(g.inVerticesEnd(2));
  SCOPE_ASSERT_EQUAL(0, *bi2++);
  SCOPE_ASSERT_EQUAL(1, *bi2++);
  SCOPE_ASSERT(ei2 == bi2);
}

SCOPE_TEST(fsmOutItrPreOutcrement) {
  Graph g(3);
  g.addEdge(1, 0);
  g.addEdge(2, 0);
  g.addEdge(2, 1);

  Graph::const_iterator bo0(g.outVerticesBegin(0));
  Graph::const_iterator eo0(g.outVerticesEnd(0));
  SCOPE_ASSERT(eo0 == bo0);

  Graph::const_iterator bo1(g.outVerticesBegin(1));
  Graph::const_iterator eo1(g.outVerticesEnd(1));
  SCOPE_ASSERT_EQUAL(0, *bo1);
  SCOPE_ASSERT(eo1 == ++bo1);

  Graph::const_iterator bo2(g.outVerticesBegin(2));
  Graph::const_iterator eo2(g.outVerticesEnd(2));
  SCOPE_ASSERT_EQUAL(0, *bo2);
  SCOPE_ASSERT_EQUAL(1, *(++bo2));
  SCOPE_ASSERT(eo2 == ++bo2);
}

SCOPE_TEST(fsmOutItrPostOutcrement) {
  Graph g(3);
  g.addEdge(1, 0);
  g.addEdge(2, 0);
  g.addEdge(2, 1);

  Graph::const_iterator bo0(g.outVerticesBegin(0));
  Graph::const_iterator eo0(g.outVerticesEnd(0));
  SCOPE_ASSERT(eo0 == bo0);

  Graph::const_iterator bo1(g.outVerticesBegin(1));
  Graph::const_iterator eo1(g.outVerticesEnd(1));
  SCOPE_ASSERT_EQUAL(0, *bo1++);
  SCOPE_ASSERT(eo1 == bo1);

  Graph::const_iterator bo2(g.outVerticesBegin(2));
  Graph::const_iterator eo2(g.outVerticesEnd(2));
  SCOPE_ASSERT_EQUAL(0, *bo2++);
  SCOPE_ASSERT_EQUAL(1, *bo2++);
  SCOPE_ASSERT(eo2 == bo2);
}

SCOPE_TEST(fsmClear) {
  Graph g(1);
  g.addEdge(0, 0);
 
  SCOPE_ASSERT_EQUAL(1, g.numVertices());
  g.clear();
  SCOPE_ASSERT_EQUAL(0, g.numVertices());
}

SCOPE_TEST(fsmVertexSize) {
  SCOPE_ASSERT_EQUAL(26, sizeof(Graph::Vertex));
}
