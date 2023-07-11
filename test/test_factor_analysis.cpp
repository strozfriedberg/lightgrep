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

#include "automata.h"
#include "factor_analysis.h"
#include "graph.h"
#include "simplevectorfamily.h"

TEST_CASE("testEdgeCount") {
  NFA g(5);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);

  const NFA::NeighborList nl(g.outVertices(1));

  REQUIRE(3u == edgeCount(nl));
}

TEST_CASE("testAddEdges") {
  NFA g(3);

  add_edges(g, {
    {0, 1},
    {1, 0},
    {1, 2},
    {2, 0}
  });

  const NFA::NeighborList nl0(g.outVertices(0));
  const NFA::NeighborList nl1(g.outVertices(1));
  const NFA::NeighborList nl2(g.outVertices(2));

  REQUIRE(1u == edgeCount(nl0));
  REQUIRE(2u == edgeCount(nl1));
  REQUIRE(1u == edgeCount(nl2));

  REQUIRE(4u == g.edgesSize());

  // 0
  REQUIRE(2u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  // 1
  REQUIRE(1u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(0u == g.outVertex(1, 0));
  REQUIRE(2u == g.outVertex(1, 1));

  // 2
  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(0u == g.outVertex(2, 0));
}

TEST_CASE("testListsConcatenator") {
  const Lists act = listsConcatenator({{{0, 1, 2, 3, 4}, {5, 6, 7}}, {{8, 9}}, {{10, 11}, {12, 13, 14, 15}}});
  const Lists exp{{0, 1, 2, 3, 4}, {5, 6, 7}, {8, 9}, {10, 11}, {12, 13, 14, 15}};

  REQUIRE(exp == act);
}

TEST_CASE("testListContains") {
  const bool act = listContains({1, 2, 3, 4, 5, 6, 7}, 6);

  REQUIRE(true == act);
}

TEST_CASE("testDFS") {
  NFA g(8);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(4, 5);
  g.addEdge(5, 6);
  g.addEdge(5, 7);
  g.addEdge(2, 7);

  const Lists act = depthFirstSearch(0, 7, g);
  const Lists exp{{0, 1, 4, 5, 7}, {0, 2, 7}};

  REQUIRE(exp == act);
}

TEST_CASE("testDFSLoop") {
  NFA g(5);
  g.addEdge(0, 1);
  g.addEdge(1, 0);
  g.addEdge(0, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 0);
  g.addEdge(3, 4);
  g.addEdge(1, 2);

  const Lists act = depthFirstSearch(1, 4, g);
  const Lists exp{{1, 0, 2, 3, 4}, {1, 2, 3, 4}};

  REQUIRE(exp == act);
}

TEST_CASE("testDFSMultipath") {
  NFA g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(0, 4);
  g.addEdge(4, 5);
  g.addEdge(5, 3);

  const Lists act = depthFirstSearch(0, 3, g);
  const Lists exp{{0, 1, 2, 3}, {0, 4, 5, 3}};

  REQUIRE(exp == act);
}

TEST_CASE("testContainsSubset") {
  bool act1 = containsSubset<int>({0,1,2,3,4,5,6,7,8}, {4, 5, 6});
  bool act2 = containsSubset<int>({0,1,2,3,4,5,6,7,8}, {4, 6});
  bool act3 = containsSubset<int>({0,1,2,3,4,5,6,7,8}, {9, 10});
  bool act4 = containsSubset<int>({0,1,2,3,4,5}, {0,1,2,3,4,5});
  bool act5 = containsSubset<int>({0,1,2,3,4,5}, {1,1,1,1,1,1});
  bool act6 = containsSubset<int>({0,1,2,3,4,5}, {3,4,5});
  bool act7 = containsSubset<int>({0,1,2,3,4,5}, {3,4,5,6});

  REQUIRE(true == act1);
  REQUIRE(false == act2);
  REQUIRE(false == act3);
  REQUIRE(true == act4);
  REQUIRE(false == act5);
  REQUIRE(true == act6);
  REQUIRE(false == act7);
}

TEST_CASE("testDFSDominator") {
  NFA g(14);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {1, 11},
    {2, 3},
    {3, 4},
    {4, 5},
    {5, 6},
    {6, 7},
    {6, 10},
    {7, 8},
    {8, 9},
    {10, 9},
    {11, 12},
    {11, 13},
    {12, 4},
    {13, 4},
  });

  const List act = dominantPath(0, 9, g);
  const List exp {4, 5, 6};

  REQUIRE(exp == act);
}

TEST_CASE("testDFSDominator2") {
  NFA g(12);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {2, 3},
    {2, 11},
    {3, 4},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 8},
    {7, 10},
    {8, 9},
    {10, 9},
    {11, 5}
  });

  const List act = dominantPath(0, 9, g);
  const List exp {0, 1, 2};

  REQUIRE(exp == act);
}

TEST_CASE("testDFSDominator3") {
  NFA g(7);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {1, 5},
    {2, 3},
    {3, 4},
    {5, 6},
    {6, 2}
  });

  const List act = dominantPath(0, 4, g);
  const List exp {2, 3, 4};

  REQUIRE(exp == act);
}

TEST_CASE("testDFSDominator4") {
  NFA g(7);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {1, 5},
    {2, 3},
    {2, 6},
    {3, 4},
    {5, 6},
    {6, 2}
  });

  const List act = dominantPath(0, 4, g);
  const List exp {2, 3, 4};

  REQUIRE(exp == act);
}

List extendDominantPath(
  NFA::VertexDescriptor startingNode,
  std::list<NFA::VertexDescriptor> endingNodes,
  const NFA& graph) {

  std::vector<Lists> all_paths;

  for (NFA::VertexDescriptor endingNode : endingNodes) {
    Lists paths(depthFirstSearch(startingNode, endingNode, graph));

    all_paths.push_back(paths);
  }

  Lists pos = listsConcatenator(all_paths);

  int n = pos.size();

  List s = pos[0];
  int len = s.size();

  List res = {};

  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j <= len; j++) {
      List stem(s.begin() + i, s.begin() + j);
      int k = 1;

      for (k = 1; k < n; k++) {
        if (!containsSubset<NFA::VertexDescriptor>(pos[k], stem)) {
          break;
        }
      }

      if (k == n && res.size() < stem.size()) {
        res = stem;
      }
    }
  }

  return res;
}

TEST_CASE("testDFSExtendDominator") {
  NFA g(15);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {1, 11},
    {2, 3},
    {3, 4},
    {4, 5},
    {5, 6},
    {6, 7},
    {6, 10},
    {7, 8},
    {8, 9},
    {10, 14},
    {11, 12},
    {11, 13},
    {12, 4},
    {13, 4},
  });

  const List act = extendDominantPath(0, {9, 14}, g);
  const List exp {4, 5, 6};

  REQUIRE(exp == act);
}

TEST_CASE("testDFSExtendDominator2") {
  NFA g(6);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {2, 2},
    {2, 3},
    {1, 4},
    {4, 5},
  });

  const List act = extendDominantPath(0, {3, 5}, g);
  const List exp {0, 1};

  REQUIRE(exp == act);
}

