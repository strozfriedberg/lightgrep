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

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

#include "graph.h"
#include "simplevectorfamily.h"

struct X {};

template <typename T>
struct S: public SimpleVectorFamily<T> {};

TEST_CASE("graphNullaryCtor") {
  Graph<X,X,X,S> g;
  REQUIRE(0u == g.verticesSize());
  REQUIRE(0u == g.edgesSize());
}

TEST_CASE("graphFiveCtor") {
  Graph<X,X,X,S> g(5);
  REQUIRE(5u == g.verticesSize());
  REQUIRE(0u == g.edgesSize());
}

TEST_CASE("graphTenTwentyCtor") {
  Graph<X,X,X,S> g(10, 20);
  REQUIRE(10u == g.verticesSize());
  REQUIRE(20u == g.verticesCapacity());
  REQUIRE(0u == g.edgesSize());
}

TEST_CASE("graphSixSevenEightCtor") {
  Graph<X,X,X,S> g(6, 7, 8);
  REQUIRE(6u == g.verticesSize());
  REQUIRE(7u == g.verticesCapacity());
  REQUIRE(0u == g.edgesSize());
  REQUIRE(8u == g.edgesCapacity());
}

TEST_CASE("graphAddVertex") {
  Graph<X,X,X,S> g(0);
  REQUIRE(0u == g.addVertex());
  REQUIRE(1u == g.verticesSize());
  REQUIRE(1u == g.addVertex());
  REQUIRE(2u == g.verticesSize());
  REQUIRE(2u == g.addVertex());
  REQUIRE(3u == g.verticesSize());
}

TEST_CASE("graphAddLoop") {
  Graph<X,X,X,S> g(1);
  REQUIRE(0u == g.addEdge(0, 0));
  REQUIRE(1u == g.edgesSize());
  REQUIRE(1u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(0u == g.inVertex(0, 0));
  REQUIRE(0u == g.outVertex(0, 0));
  REQUIRE(0u == g.inEdge(0, 0));
  REQUIRE(0u == g.outEdge(0, 0));
}

TEST_CASE("graphAddEdge") {
  Graph<X,X,X,S> g(2);

  // two disconnected vertices
  REQUIRE(2u == g.verticesSize());
  REQUIRE(0u == g.edgesSize());
  REQUIRE(0u == g.inDegree(0));
  REQUIRE(0u == g.outDegree(0));
  REQUIRE(0u == g.inDegree(1));
  REQUIRE(0u == g.outDegree(1));

  // 0 -> 1
  REQUIRE(0u == g.addEdge(0, 1));
  REQUIRE(1u == g.edgesSize());
  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));
  REQUIRE(0u == g.outEdge(0, 0));
  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.outDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(0u == g.inEdge(1, 0));

  // 1 -> 0
  REQUIRE(1u == g.addEdge(1, 0));
  REQUIRE(2u == g.edgesSize());
  REQUIRE(1u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.inVertex(0, 0));
  REQUIRE(1u == g.outVertex(0, 0));
  REQUIRE(1u == g.inEdge(0, 0));
  REQUIRE(0u == g.outEdge(0, 0));
  REQUIRE(1u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(0u == g.outVertex(1, 0));
  REQUIRE(0u == g.inEdge(1, 0));
  REQUIRE(1u == g.outEdge(1, 0));
}

TEST_CASE("graphRemoveEdge") {
  Graph<X,X,X,S> g(2);

  REQUIRE(0u == g.addEdge(0, 1));
  REQUIRE(1u == g.addEdge(1, 0));
  REQUIRE(2u == g.edgesSize());
  g.removeEdge(0);
  REQUIRE(1u == g.edgesSize());
  REQUIRE(1u == g.inDegree(0));
  REQUIRE(0u == g.outDegree(0));
  REQUIRE(0u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(1u == g.inVertex(0, 0));
  REQUIRE(0u == g.outVertex(1, 0));
  REQUIRE(0u == g.inEdge(0, 0));
  REQUIRE(0u == g.outEdge(1, 0));
}

TEST_CASE("graphRemoveVertex") {
  Graph<X,X,X,S> g(3);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 0);

  g.removeVertex(1);
  REQUIRE(2u == g.verticesSize());
  REQUIRE(1u == g.edgesSize());
  REQUIRE(1u == g.inDegree(0));
  REQUIRE(0u == g.outDegree(0));
  REQUIRE(0u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(1u == g.inVertex(0, 0));
  REQUIRE(0u == g.outVertex(1, 0));
  REQUIRE(0u == g.inEdge(0, 0));
  REQUIRE(0u == g.outEdge(1, 0));
}

TEST_CASE("graphClearVertices") {
  Graph<X,X,X,S> g(1);
  g.addEdge(0, 0);
  REQUIRE(1u == g.verticesSize());
  REQUIRE(1u == g.edgesSize());
  g.clearVertices();
  REQUIRE(0u == g.verticesSize());
  REQUIRE(0u == g.edgesSize());
}

TEST_CASE("graphClearEdges") {
  Graph<X,X,X,S> g(1);
  g.addEdge(0, 0);
  REQUIRE(1u == g.verticesSize());
  REQUIRE(1u == g.edgesSize());
  g.clearEdges();
  REQUIRE(1u == g.verticesSize());
  REQUIRE(0u == g.edgesSize());
}

TEST_CASE("graphInVertices") {
  typedef Graph<X,X,X,S> G;

  G g(5);
  g.addEdge(0, 1);
  g.addEdge(2, 1);
  g.addEdge(3, 1);
  g.addEdge(4, 1);

  const G::NeighborList nl(g.inVertices(1));
  const std::vector<G::VertexDescriptor> act(nl.begin(), nl.end());
  const std::vector<G::VertexDescriptor> exp{0,2,3,4};
  REQUIRE(exp == act);
}

TEST_CASE("graphOutVertices") {
  typedef Graph<X,X,X,S> G;

  G g(5);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);

  const G::NeighborList nl(g.outVertices(1));
  const std::vector<G::VertexDescriptor> act(nl.begin(), nl.end());
  const std::vector<G::VertexDescriptor> exp{2,3,4};
  REQUIRE(exp == act);
}
