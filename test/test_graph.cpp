#include <scope/test.h>

#include <vector>

#include "graph.h"

struct X {};

struct F {
  typedef std::vector<uint32> ListType;

  ListType create() {
    return std::vector<uint32>();
  }
};

SCOPE_TEST(graphNullaryCtor) {
  Graph<X,X,X,F> g;
  SCOPE_ASSERT_EQUAL(0, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
}

SCOPE_TEST(graphFiveCtor) {
  Graph<X,X,X,F> g(5);
  SCOPE_ASSERT_EQUAL(5, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
}

SCOPE_TEST(graphTenTwentyCtor) {
  Graph<X,X,X,F> g(10, 20);
  SCOPE_ASSERT_EQUAL(10, g.verticesSize());
  SCOPE_ASSERT_EQUAL(20, g.verticesCapacity());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
}

SCOPE_TEST(graphSixSevenEightCtor) {
  Graph<X,X,X,F> g(6, 7, 8);
  SCOPE_ASSERT_EQUAL(6, g.verticesSize());
  SCOPE_ASSERT_EQUAL(7, g.verticesCapacity());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
  SCOPE_ASSERT_EQUAL(8, g.edgesCapacity());
}

SCOPE_TEST(graphAddVertex) {
  Graph<X,X,X,F> g(0);
  SCOPE_ASSERT_EQUAL(0, g.addVertex());
  SCOPE_ASSERT_EQUAL(1, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1, g.addVertex());
  SCOPE_ASSERT_EQUAL(2, g.verticesSize());
  SCOPE_ASSERT_EQUAL(2, g.addVertex());
  SCOPE_ASSERT_EQUAL(3, g.verticesSize());
}

SCOPE_TEST(graphAddLoop) {
  Graph<X,X,X,F> g(1);
  SCOPE_ASSERT_EQUAL(0, g.addEdge(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outEdge(0, 0));
}

SCOPE_TEST(graphAddEdge) {
  Graph<X,X,X,F> g(2);

  // two disconnected vertices
  SCOPE_ASSERT_EQUAL(2, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
  SCOPE_ASSERT_EQUAL(0, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(1));

  // 0 -> 1
  SCOPE_ASSERT_EQUAL(0, g.addEdge(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.edgesSize());
  SCOPE_ASSERT_EQUAL(0, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outEdge(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0, g.inEdge(1, 0));

  // 1 -> 0
  SCOPE_ASSERT_EQUAL(1, g.addEdge(1, 0));
  SCOPE_ASSERT_EQUAL(2, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outEdge(0, 0));
  SCOPE_ASSERT_EQUAL(1, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(0, g.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0, g.inEdge(1, 0));
  SCOPE_ASSERT_EQUAL(1, g.outEdge(1, 0));
}

SCOPE_TEST(graphRemoveEdge) {
  Graph<X,X,X,F> g(2);

  SCOPE_ASSERT_EQUAL(0, g.addEdge(0, 1));
  SCOPE_ASSERT_EQUAL(1, g.addEdge(1, 0));
  SCOPE_ASSERT_EQUAL(2, g.edgesSize());
  g.removeEdge(0);
  SCOPE_ASSERT_EQUAL(1, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(1, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outEdge(1, 0));
}

SCOPE_TEST(graphRemoveVertex) {
  Graph<X,X,X,F> g(3);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 0);

  g.removeVertex(1);
  SCOPE_ASSERT_EQUAL(2, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(1, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0, g.outEdge(1, 0));
}

SCOPE_TEST(graphClearVertices) {
  Graph<X,X,X,F> g(1);
  g.addEdge(0, 0);
  SCOPE_ASSERT_EQUAL(1, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1, g.edgesSize());
  g.clearVertices();
  SCOPE_ASSERT_EQUAL(0, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
}

SCOPE_TEST(graphClearEdges) {
  Graph<X,X,X,F> g(1);
  g.addEdge(0, 0);
  SCOPE_ASSERT_EQUAL(1, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1, g.edgesSize());
  g.clearEdges();
  SCOPE_ASSERT_EQUAL(1, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0, g.edgesSize());
}

