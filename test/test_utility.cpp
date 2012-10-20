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

#include <iostream>
#include <fstream>
#include <functional>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/dynamic_property_map.hpp>

#include "codegen.h"
#include "nfaoptimizer.h"
#include "states.h"
#include "mockcallback.h"

#include "test_helper.h"

/*
std::ostream& operator<<(std::ostream& os, const std::shared_ptr<TransitionPtr>& p) {
  return os;
}
*/

/*
bool buildNFA(NFA& fsm, const std::string& dot) {
  std::istringstream is(dot);

  // Vertex properties
  typedef boost::property<boost::vertex_name_t, std::string> vertex_p;
  // Edge properties
  typedef boost::property<boost::edge_name_t, std::string> edge_p;
  // adjacency_list-based type
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                vertex_p, edge_p> graph_t;

  // Construct an empty graph and prepare the dynamic_property_maps
  graph_t src(0);
  boost::dynamic_properties dp;

  boost::property_map<graph_t, boost::vertex_name_t>::type node_label =
    get(boost::vertex_name, src);
  dp.property("node_id", node_label);

  boost::property_map<graph_t, boost::edge_name_t>::type edge_label =
    get(boost::edge_name, src);
  dp.property("label", edge_label);

  if (!boost::read_graphviz(is, src, dp, "node_id")) return false;

  // Convert this graph to a NFA (annoying!)

  typedef boost::graph_traits<graph_t>::vertex vertex_t;
  typedef boost::graph_traits<graph_t>::edge_iterator edge_iterator;

  edge_iterator e, e_end;
  for (boost::tie(e, e_end) = boost::edges(src); e != e_end; ++e) {
    const unsigned int u = boost::lexical_cast<unsigned int>(
      boost::get(node_label, boost::source(*e, src)));

    const unsigned int v = boost::lexical_cast<unsigned int>(
      boost::get(node_label, boost::target(*e, src)));

    const char lit = boost::lexical_cast<char>(boost::get(edge_label, *e));

    edge(u, v, fsm, fsm.TransFac->getByte(lit));
  }

  return true;
}
*/

std::ostream& operator<<(std::ostream& out, const StateLayoutInfo& state) {
  out << "(" << state.Start << ", " << state.NumEval << ", " << state.NumOther << ", " << state.CheckIndex << ")";
  return out;
}

template<class T>
std::vector<Pattern> makePatterns(const std::initializer_list<T>& list) {
  std::vector<Pattern> ret;
  for (const auto& p : list) {
    ret.emplace_back(p);
  }
  return ret;
}

SCOPE_TEST(twoUnicode) {
  std::vector<Pattern> pats(makePatterns({"aa", "ab"}));
  for (Pattern& p : pats) {
    p.Encoding = LG_CANONICAL_ENCODINGS[LG_ENC_UTF_16LE];
  }

  NFAPtr fsm = createGraph(pats);
  NFA& g = *fsm;

  SCOPE_ASSERT_EQUAL(7u, g.verticesSize());

  SCOPE_ASSERT_EQUAL(0u, g.inDegree(0));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(0));
  SCOPE_ASSERT_EQUAL(1, g.outVertex(0, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(1));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(1));
  SCOPE_ASSERT_EQUAL(2, g.outVertex(1, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(2));
  SCOPE_ASSERT_EQUAL(2u, g.outDegree(2));
  SCOPE_ASSERT_EQUAL(3, g.outVertex(2, 0));
  SCOPE_ASSERT_EQUAL(4, g.outVertex(2, 1));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(3));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(3));
  SCOPE_ASSERT_EQUAL(6, g.outVertex(3, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(4));
  SCOPE_ASSERT_EQUAL(1u, g.outDegree(4));
  SCOPE_ASSERT_EQUAL(5, g.outVertex(4, 0));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(5));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(5));

  SCOPE_ASSERT_EQUAL(1u, g.inDegree(6));
  SCOPE_ASSERT_EQUAL(0u, g.outDegree(6));

  SCOPE_ASSERT(!g[0].Trans);
  SCOPE_ASSERT(!g[1].IsMatch);
  SCOPE_ASSERT(!g[2].IsMatch);
  SCOPE_ASSERT(!g[3].IsMatch);
  SCOPE_ASSERT(!g[4].IsMatch);
  SCOPE_ASSERT(g[5].IsMatch);
  SCOPE_ASSERT(g[6].IsMatch);

  ByteSet abs, ebs;

  const byte exp[] = { 'a', 0, 'a', 'b', 0, 0 };
  for (uint32 i = 1; i < g.verticesSize(); ++i) {
    abs.reset();
    ebs.reset();

    ebs[exp[i-1]] = true;
    g[i].Trans->getBytes(abs);

    SCOPE_ASSERT_EQUAL(ebs, abs);
  }
}

SCOPE_TEST(firstBitset) {
  NFA fsm(3);
  edge(0, 1, fsm, fsm.TransFac->getByte('A'));
  edge(0, 2, fsm, fsm.TransFac->getByte('B'));

  const ByteSet accepted = firstBytes(fsm);
  for (unsigned int i = 0; i < 256; ++i) {
    if (i == 'A' || i == 'B') {
      SCOPE_ASSERT(accepted[i]);
    }
    else {
      SCOPE_ASSERT(!accepted[i]);
    }
  }
}

SCOPE_TEST(simpleCollapse) {
  NFAPtr fsm = createGraph(makePatterns({"ab", "ac"}));
  SCOPE_ASSERT_EQUAL(4u, fsm->verticesSize());
  SCOPE_ASSERT_EQUAL(1u, fsm->outDegree(0));
  SCOPE_ASSERT_EQUAL(2u, fsm->outDegree(1));
  SCOPE_ASSERT_EQUAL(0u, fsm->outDegree(2));
  SCOPE_ASSERT_EQUAL(0u, fsm->outDegree(3));
}

SCOPE_TEST(codeGen2DiscoverVertex) {
  NFA fsm(2);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  std::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);

  vis.discover_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->NumDiscovered);
  SCOPE_ASSERT_EQUAL(0u, cg->DiscoverRanks[1]);

  vis.discover_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(2u, cg->NumDiscovered);
  SCOPE_ASSERT_EQUAL(1u, cg->DiscoverRanks[0]);
}

SCOPE_TEST(codeGen2FinishVertex) {
  NFA fsm(5);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 2, fsm, fsm.TransFac->getByte('b'));
  edge(2, 3, fsm, fsm.TransFac->getByte('c'));
  edge(2, 4, fsm, fsm.TransFac->getByte('d'));
  std::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);

  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;
  cg->DiscoverRanks[3] = 3;
  cg->DiscoverRanks[4] = 4;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].Start);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].numTotal());

  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[1].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].numTotal());

  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[2].Start);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[2].numTotal());

  vis.finish_vertex(3, fsm);
  SCOPE_ASSERT_EQUAL(4u, cg->Snippets[3].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[3].numTotal());

  vis.finish_vertex(4, fsm);
  SCOPE_ASSERT_EQUAL(5u, cg->Snippets[4].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[4].numTotal());
}

SCOPE_TEST(alternationCodeGen2FinishVertex) {
  NFA fsm(3);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(0, 2, fsm, fsm.TransFac->getByte('b'));
  std::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);

  cg->NumDiscovered = 3;
  cg->DiscoverRanks[0] = 0;
  cg->DiscoverRanks[1] = 1;
  cg->DiscoverRanks[2] = 2;

  vis.finish_vertex(0, fsm);
  SCOPE_ASSERT_EQUAL(0u, cg->Snippets[0].Start);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[0].numTotal());

  vis.finish_vertex(1, fsm);
  SCOPE_ASSERT_EQUAL(2u, cg->Snippets[1].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[1].numTotal());

  vis.finish_vertex(2, fsm);
  SCOPE_ASSERT_EQUAL(3u, cg->Snippets[2].Start);
  SCOPE_ASSERT_EQUAL(1u, cg->Snippets[2].numTotal());
}

SCOPE_TEST(layoutWithCheckHalt) {
  NFA fsm(3);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 2, fsm, fsm.TransFac->getByte('b'));
  edge(2, 2, fsm, fsm.TransFac->getByte('b'));

  fsm[2].Label = 0;
  fsm[2].IsMatch = true;

  std::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(fsm.verticesSize()));
  CodeGenVisitor vis(cg);
  specialVisit(fsm, 0, vis);

  SCOPE_ASSERT_EQUAL(0u, cg->DiscoverRanks[0]);
  SCOPE_ASSERT_EQUAL(1u, cg->DiscoverRanks[1]);
  SCOPE_ASSERT_EQUAL(2u, cg->DiscoverRanks[2]);
  SCOPE_ASSERT_EQUAL(StateLayoutInfo(0u, 0u, 0u, NONE), cg->Snippets[0]);
  SCOPE_ASSERT_EQUAL(StateLayoutInfo(0u, 1u, 0u, NONE), cg->Snippets[1]);
  SCOPE_ASSERT_EQUAL(StateLayoutInfo(1u, 1u, 7u, 1u), cg->Snippets[2]);
}

SCOPE_TEST(testCodeGenVisitorShouldBeJumpTableRange) {
  NFA g(4);
  edge(0, 1, g, g.TransFac->getByte('a'));
  edge(0, 2, g, g.TransFac->getByte('b'));
  edge(0, 3, g, g.TransFac->getByte('c'));
  edge(0, 4, g, g.TransFac->getByte('e'));

  std::shared_ptr<CodeGenHelper> cgh(new CodeGenHelper(g.verticesSize()));
  CodeGenVisitor vis(cgh);

  SCOPE_ASSERT_EQUAL(6, vis.calcJumpTableSize(0, g, g.outDegree(0)));
  SCOPE_ASSERT_EQUAL(JUMP_TABLE_RANGE_OP, cgh->Snippets[0].Op);
  SCOPE_ASSERT_EQUAL(0, vis.calcJumpTableSize(1, g, g.outDegree(1)));
  SCOPE_ASSERT_EQUAL(0, vis.calcJumpTableSize(2, g, g.outDegree(2)));
  SCOPE_ASSERT_EQUAL(0, vis.calcJumpTableSize(3, g, g.outDegree(3)));
}

SCOPE_TEST(testInitVM) {
  SearchInfo info;
  std::shared_ptr<VmInterface> search = initVM(makePatterns({"one", "two"}), info);
               //012345678901234
  byte text[] = "a onetwothree";

  std::vector<SearchHit> hits;
  SCOPE_ASSERT(!search->search(&text[0], &text[13], 0, &mockCallback, &hits));
  search->closeOut(&mockCallback, &hits);
  SCOPE_ASSERT_EQUAL(2u, hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 5, 0), hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(5, 8, 1), hits[1]);
}

SCOPE_TEST(testPivotTransitions) {
  NFA fsm(5);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(0, 2, fsm, fsm.TransFac->getByte('a'));
  edge(0, 3, fsm, fsm.TransFac->getByte('z'));
  edge(0, 4, fsm, fsm.TransFac->getByte('z'));

  fsm[1].IsMatch = true;
  fsm[1].Label = 0;

  fsm[2].IsMatch = true;
  fsm[2].Label = 1;

  std::vector<std::vector<NFA::VertexDescriptor>> tbl = pivotStates(0, fsm);
  SCOPE_ASSERT_EQUAL(256u, tbl.size());
  for (uint32 i = 0; i < 256; ++i) {
    if (i == 'a') {
      SCOPE_ASSERT_EQUAL(2u, tbl[i].size());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 1) != tbl[i].end());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 2) != tbl[i].end());
    }
    else if (i == 'z') {
      SCOPE_ASSERT_EQUAL(2u, tbl[i].size());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 3) != tbl[i].end());
      SCOPE_ASSERT(std::find(tbl[i].begin(), tbl[i].end(), 4) != tbl[i].end());
    }
    else {
      SCOPE_ASSERT(tbl[i].empty());
    }
  }
}

SCOPE_TEST(testMaxOutbound) {
  NFA fsm(5);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(0, 2, fsm, fsm.TransFac->getByte('a'));
  edge(0, 3, fsm, fsm.TransFac->getByte('b'));
  edge(0, 4, fsm, fsm.TransFac->getByte('c'));
  std::vector<std::vector<NFA::VertexDescriptor>> tbl = pivotStates(0, fsm);
  SCOPE_ASSERT_EQUAL(2u, maxOutbound(tbl));
}
