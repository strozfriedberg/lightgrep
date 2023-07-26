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

#include "factor_analysis.h"
#include "fwd_pointers.h"
#include "nfabuilder.h"
#include "parser.h"

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

TEST_CASE("testBFS") {
  NFA g(8);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(4, 5);
  g.addEdge(5, 6);
  g.addEdge(5, 7);
  g.addEdge(2, 7);

  g[3].IsMatch = true;
  g[6].IsMatch = true;
  g[7].IsMatch = true;

  const Lists act = breadthFirstSearch(0, g);
  const Lists exp{{ 0, 1, 3 }, { 0, 2, 7 }, { 0, 1, 4, 5, 6 }, { 0, 1, 4, 5, 7 }};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSLoop") {
  NFA g(5);
  g.addEdge(0, 1);
  g.addEdge(1, 0);
  g.addEdge(0, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 0);
  g.addEdge(3, 4);
  g.addEdge(1, 2);

  g[4].IsMatch = true;

  const Lists act = breadthFirstSearch(1, g);
  const Lists exp{{1, 2, 3, 4}, {1, 0, 2, 3, 4}};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSMultipath") {
  NFA g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(0, 4);
  g.addEdge(4, 5);
  g.addEdge(5, 3);

  g[3].IsMatch = true;

  const Lists act = breadthFirstSearch(0, g);
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

TEST_CASE("testBFSDominator") {
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


  g[9].IsMatch = true;

  const List act = dominantPath(0, g);
  const List exp {4, 5, 6};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSDominator2") {
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

  g[9].IsMatch = true;

  const List act = dominantPath(0, g);
  const List exp {5, 6, 7};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSDominator3") {
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

  g[4].IsMatch = true;

  const List act = dominantPath(0, g);
  const List exp {2, 3, 4};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSDominator4") {
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

  g[4].IsMatch = true;

  const List act = dominantPath(0, g);
  const List exp {2, 3, 4};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSExtendDominator") {
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

  g[9].IsMatch = true;
  g[14].IsMatch = true;

  const List act = dominantPath(0, g);
  const List exp {4, 5, 6};

  REQUIRE(exp == act);
}

TEST_CASE("testBFSExtendDominator2") {
  NFA g(6);

  add_edges(g, {
    {0, 1},
    {1, 2},
    {2, 2},
    {2, 3},
    {1, 4},
    {4, 5},
  });

  g[3].IsMatch = true;
  g[5].IsMatch = true;

  const List act = dominantPath(0, g);
  const List exp {0, 1};

  REQUIRE(exp == act);
}

NFAPtr construct(const std::string& pattern) {
  Pattern pat(pattern);
  ParseTree tree;
  parse(pat, tree);
  NFABuilder builder;
  builder.build(tree);
  return builder.getFsm();
}

TEST_CASE("test_simple_factor") /*"[!shouldfail]")*/ {
  NFAPtr nfa = construct("glushkov");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 9u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "glushkov");
}

TEST_CASE("test_nondominant_factor") {
  NFAPtr nfa = construct("(abc|def).*ghi");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 11u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "ghi");
}

TEST_CASE("test_one_more") {
  NFAPtr nfa = construct("a+b+c+foo");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 7u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "foo");
}

TEST_CASE("test_zero_more") {
  NFAPtr nfa = construct("a*foob*c*");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 7u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "foo");
}

TEST_CASE("test_zero_or_one") {
  NFAPtr nfa = construct("a?fooc?");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 6u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "foo");
}

TEST_CASE("test_case_insensitive_factor") {
  NFAPtr nfa = construct("foo(h|H)(t|T)(t|T)(p|P)");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 12u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "foo");
}

TEST_CASE("test_too_short") {
  NFAPtr nfa = construct("fox*bar");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 7u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "bar");
}

TEST_CASE("test_min_length") {
  NFAPtr nfa = construct("fox*");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 4u);
  std::string longest_factor = analyze(*nfa, 2);
  REQUIRE(longest_factor == "fo");
}

TEST_CASE("test_same_length") {
  NFAPtr nfa = construct("aaac*bbb");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 8u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "aaa");
}

TEST_CASE("test_same_length_multi_accept") {
  NFAPtr nfa = construct("a(aa|bb)");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 6u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "");
}

TEST_CASE("test_longer_factor") {
  NFAPtr nfa = construct("aaac*bbbb");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 9u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "bbbb");
}

TEST_CASE("test_longer_factor_multi_accept") {
  NFAPtr nfa = construct("a(aa|bbb)");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 7u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "");
}

TEST_CASE("test_dominant_too_short") {
  NFAPtr nfa = construct("aa*bb");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 5u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "");
}

TEST_CASE("test_no_dominant") {
  NFAPtr nfa = construct("aa(abc|def)g");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 10u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "");
}

TEST_CASE("test_back_edges",) {
  NFAPtr nfa = construct("((abc)+d)+");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 5u);
  std::string longest_factor = analyze(*nfa, 3);
  REQUIRE(longest_factor == "abcd");
}

