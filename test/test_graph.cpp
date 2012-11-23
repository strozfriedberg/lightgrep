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

#include <algorithm>
#include <vector>

#include "graph.h"
#include "simplevectorfamily.h"

struct X {};

template <typename T>
struct S: public SimpleVectorFamily<T> {};

SCOPE_TEST(graphNullaryCtor) {
  Graph<X,X,X,S> g;
  SCOPE_ASSERT_EQUAL(0u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
}

SCOPE_TEST(graphFiveCtor) {
  Graph<X,X,X,S> g(5);
  SCOPE_ASSERT_EQUAL(5u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
}

SCOPE_TEST(graphTenTwentyCtor) {
  Graph<X,X,X,S> g(10, 20);
  SCOPE_ASSERT_EQUAL(10u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(20u, g.verticesCapacity());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
}

SCOPE_TEST(graphSixSevenEightCtor) {
  Graph<X,X,X,S> g(6, 7, 8);
  SCOPE_ASSERT_EQUAL(6u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(7u, g.verticesCapacity());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(8u, g.edgesCapacity());
}

SCOPE_TEST(graphAddVertex) {
  Graph<X,X,X,S> g(0);
  SCOPE_ASSERT_EQUAL(0u, g.addVertex());
  SCOPE_ASSERT_EQUAL(1u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, g.addVertex());
  SCOPE_ASSERT_EQUAL(2u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(2u, g.addVertex());
  SCOPE_ASSERT_EQUAL(3u, g.verticesSize());
}

SCOPE_TEST(graphAddLoop) {
  Graph<X,X,X,S> g(1);
  SCOPE_ASSERT_EQUAL(0u, g.addEdge(0, 0));
  SCOPE_ASSERT_EQUAL(1u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outEdge(0, 0));
}

SCOPE_TEST(graphAddEdge) {
  Graph<X,X,X,S> g(2);

  // two disconnected vertices
  SCOPE_ASSERT_EQUAL(2u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(1));

  // 0 -> 1
  SCOPE_ASSERT_EQUAL(0u, g.addEdge(0, 1));
  SCOPE_ASSERT_EQUAL(1u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outEdge(0, 0));
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, g.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0u, g.inEdge(1, 0));

  // 1 -> 0
  SCOPE_ASSERT_EQUAL(1u, g.addEdge(1, 0));
  SCOPE_ASSERT_EQUAL(2u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1u, g.outVertex(0, 0));
  SCOPE_ASSERT_EQUAL(1u, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outEdge(0, 0));
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, g.inVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0u, g.inEdge(1, 0));
  SCOPE_ASSERT_EQUAL(1u, g.outEdge(1, 0));
}

SCOPE_TEST(graphRemoveEdge) {
  Graph<X,X,X,S> g(2);

  SCOPE_ASSERT_EQUAL(0u, g.addEdge(0, 1));
  SCOPE_ASSERT_EQUAL(1u, g.addEdge(1, 0));
  SCOPE_ASSERT_EQUAL(2u, g.edgesSize());
  g.removeEdge(0);
  SCOPE_ASSERT_EQUAL(1u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0u, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outEdge(1, 0));
}

SCOPE_TEST(graphRemoveVertex) {
  Graph<X,X,X,S> g(3);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 0);

  g.removeVertex(1);
  SCOPE_ASSERT_EQUAL(2u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, g.edgesSize());
  SCOPE_ASSERT_EQUAL(1u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(0u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.inVertex(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outVertex(1, 0));
  SCOPE_ASSERT_EQUAL(0u, g.inEdge(0, 0));
  SCOPE_ASSERT_EQUAL(0u, g.outEdge(1, 0));
}

SCOPE_TEST(graphClearVertices) {
  Graph<X,X,X,S> g(1);
  g.addEdge(0, 0);
  SCOPE_ASSERT_EQUAL(1u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, g.edgesSize());
  g.clearVertices();
  SCOPE_ASSERT_EQUAL(0u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
}

SCOPE_TEST(graphClearEdges) {
  Graph<X,X,X,S> g(1);
  g.addEdge(0, 0);
  SCOPE_ASSERT_EQUAL(1u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(1u, g.edgesSize());
  g.clearEdges();
  SCOPE_ASSERT_EQUAL(1u, g.verticesSize());
  SCOPE_ASSERT_EQUAL(0u, g.edgesSize());
}

SCOPE_TEST(graphInVertices) {
  typedef Graph<X,X,X,S> G;

  G g(5);
  g.addEdge(0, 1);
  g.addEdge(2, 1);
  g.addEdge(3, 1);
  g.addEdge(4, 1);

  const G::NeighborList nl(g.inVertices(1));
  const std::vector<G::VertexDescriptor> act(nl.begin(), nl.end());
  const std::vector<G::VertexDescriptor> exp{0,2,3,4};
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(graphOutVertices) {
  typedef Graph<X,X,X,S> G;

  G g(5);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);

  const G::NeighborList nl(g.outVertices(1));
  const std::vector<G::VertexDescriptor> act(nl.begin(), nl.end());
  const std::vector<G::VertexDescriptor> exp{2,3,4};
  SCOPE_ASSERT_EQUAL(exp, act);
}
