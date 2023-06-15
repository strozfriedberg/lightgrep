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

typedef Graph<X,X,X,S> G;

int edgeCount(G::NeighborList nl) {
  return nl.end() - nl.begin();
}

TEST_CASE("testEdgeCount") {
  G g(5);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);

  const G::NeighborList nl(g.outVertices(1));

  REQUIRE(3u == edgeCount(nl));
}

typedef std::vector<G::VertexDescriptor> List;
typedef std::vector<List> Lists;

Lists listsConcatenator(std::vector<Lists> l) {
  Lists ret;

  for (unsigned int i = 0; i < l.size(); i++) {
    Lists currLists = l[i];
    for (unsigned int j = 0; j < currLists.size(); j++) {
      List currList = currLists[j];
      if (currList.size() > 0) {
        ret.push_back(currList);
      }
    }
  }

  return ret;
}

TEST_CASE("testListsConcatenator") {
  const Lists act = listsConcatenator({{{0, 1, 2, 3, 4}, {5, 6, 7}}, {{8, 9}}, {{10, 11}, {12, 13, 14, 15}}});
  const Lists exp{{0, 1, 2, 3, 4}, {5, 6, 7}, {8, 9}, {10, 11}, {12, 13, 14, 15}};

  REQUIRE(exp == act);
}

bool listContains(List l, G::VertexDescriptor node) {
  return false;
}

TEST_CASE("testListContains") {
  const bool act = listContains({1, 2, 3, 4, 5, 6, 7}, 6);

  REQUIRE(true == act);
}


Lists depthFirstSearch(
  G::VertexDescriptor startingNode, 
  G::VertexDescriptor endingNode, 
  G graph, 
  Lists lists = Lists{}) {

  return Lists {};
}


TEST_CASE("testDFS") {
  G g(8);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(4, 5);
  g.addEdge(5, 6);
  g.addEdge(5, 7);
  g.addEdge(2, 7);

  //Just to confirm all tests pass for List and Lists refactor
  //const Lists act = depthFirstSearch(0, 7, g);
  const Lists act{{0, 1, 4, 5, 7}, {0, 2, 7}};
  const Lists exp{{0, 1, 4, 5, 7}, {0, 2, 7}};

  REQUIRE(exp == act);
}