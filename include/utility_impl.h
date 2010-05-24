#pragma once

#include "utility.h"
#include "instructions.h"

#include <vector>
#include <iostream>
#include <cstring>
#include <exception>
#include <algorithm>

#include <boost/graph/breadth_first_search.hpp>

static const uint32 UNALLOCATED = 0xffffffff;

struct CodeGenHelper {
  CodeGenHelper(uint32 numStates): DiscoverRanks(numStates, UNALLOCATED), Snippets(numStates), Guard(0), NumDiscovered(0) {}

  void discover(DynamicFSM::vertex_descriptor v) {
    DiscoverRanks[v] = NumDiscovered++;
  }

  void addSnippet(uint32 state, uint32 num) {
    Snippets[state] = std::make_pair(Guard, num);
    Guard += num;
  }

  std::vector< Instruction > Program;
  std::vector< uint32 > DiscoverRanks;
  std::vector< std::pair< uint32, uint32 > > Snippets;
  uint32 Guard,
         NumDiscovered;
};

typedef DynamicFSM::in_edge_iterator InEdgeIt;
typedef std::pair<InEdgeIt, InEdgeIt> InEdgeRange;
typedef DynamicFSM::out_edge_iterator OutEdgeIt;
typedef std::pair< OutEdgeIt, OutEdgeIt > OutEdgeRange;

class CodeGenVisitor: public boost::default_bfs_visitor {
public:
  CodeGenVisitor(boost::shared_ptr<CodeGenHelper> helper): Helper(helper) {}

  void discover_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    InEdgeRange inRange(in_edges(v, graph));
    uint32 labels = 0;
    for (InEdgeIt in(inRange.first); in != inRange.second; ++in) {
      if (graph[*in]->Label < 0xffffffff) {
        ++labels;
        break;  // only counts first label
      }
    }
    Helper->addSnippet(v, std::max(out_degree(v, graph), 1ul) + (v == 0 ? 0: 1) + labels);
  }

  void finish_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    InEdgeRange inRange(in_edges(v, graph));
    if (inRange.first != inRange.second) {
      TransitionPtr t(graph[*inRange.first]); // this assumes that all states have the same incoming transitions
      Instruction i;
      t->toInstruction(&i);
      Helper->Program.push_back(i);
      if (t->Label < 0xffffffff) {
        Helper->Program.push_back(Instruction::makeSaveLabel(t->Label)); // also problematic
      }
    }
    std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> outRange(out_edges(v, graph));
    if (outRange.first != outRange.second) {
      for (DynamicFSM::out_edge_iterator cur(outRange.first); cur != outRange.second; ++cur) {
        DynamicFSM::out_edge_iterator next(cur);
        ++next;
        if (next == outRange.second) {
          Helper->Program.push_back(Instruction::makeJump(Helper->Snippets[target(*cur, graph)].first));
        }
        else {
          Helper->Program.push_back(Instruction::makeFork(Helper->Snippets[target(*cur, graph)].first));
        }
      }
    }
    else {
      Helper->Program.push_back(Instruction::makeMatch());
    }
  }

private:
  boost::shared_ptr<CodeGenHelper> Helper;
};

class CodeGenVisitor2: public boost::default_bfs_visitor {
public:
  CodeGenVisitor2(boost::shared_ptr<CodeGenHelper> helper): Helper(helper) {}

  void discover_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM&) {
    Helper->discover(v);
  }

  void finish_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    // std::cerr << "on state " << v << " with discover rank " << Helper->DiscoverRanks[v] << std::endl;
    InEdgeRange inRange(in_edges(v, graph));
    uint32 labels = 0;
    bool   isMatch = false;
    for (InEdgeIt in(inRange.first); in != inRange.second; ++in) {
      if (graph[*in]->IsMatch) {
        isMatch = true;
      }
      if (graph[*in]->Label < 0xffffffff) {
        ++labels;
        break;  // only counts first label
      }
    }
    uint32 outOps = 0;
    OutEdgeRange outRange(out_edges(v, graph));
    if (outRange.first == outRange.second) {
      // std::cerr << "no out edges, so a halt" << std::endl;
      outOps = 1; // HALT instruction
    }
    else {
      for (OutEdgeIt curOut(outRange.first); curOut != outRange.second; ++curOut) {
        // if a target state immediately follows the current state, then we don't need an instruction for it
        if (Helper->DiscoverRanks[v] + 1 != Helper->DiscoverRanks[target(*curOut, graph)]) {
          ++outOps;
        }
      }
    }
    // std::cerr << "outOps = " << outOps << "; labels = " << labels << "; match = " << isMatch << std::endl;
    Helper->addSnippet(v, outOps + (v == 0 ? 0: 1) + labels + (isMatch ? 1: 0));
    // std::cerr << "state " << v << " has snippet " << "(" << Helper->Snippets[v].first << ", " << Helper->Snippets[v].second << ")" << std::endl;
  }

private:
  boost::shared_ptr<CodeGenHelper> Helper;
};

template<class VisitorT>
void specialVisit(const DynamicFSM& graph, DynamicFSM::vertex_descriptor startVertex, VisitorT& vis) {
  std::deque< DynamicFSM::vertex_descriptor > statesToVisit;
  std::vector< DynamicFSM::vertex_descriptor > inOrder;
  std::vector< bool > discovered(boost::num_vertices(graph), false);

  discovered[startVertex].flip();
  // vis.discover_vertex(startVertex, graph);
  statesToVisit.push_back(startVertex);
  while (!statesToVisit.empty()) {
    DynamicFSM::vertex_descriptor v = statesToVisit.front();
    statesToVisit.pop_front();

    vis.discover_vertex(v, graph);
    inOrder.push_back(v);

    uint32 numOut = boost::out_degree(v, graph);
    OutEdgeRange outRange = boost::out_edges(v, graph);
    // InEdgeRange  inRange  = boost::in_edges(v, graph);
    bool front = numOut < 2;// && boost::in_degree(v, graph) == 1 && boost::out_degree(boost::source(*inRange.first, graph), graph) == 1;
    for (OutEdgeIt curOut(outRange.first); curOut != outRange.second; ++curOut) {
      DynamicFSM::vertex_descriptor t = boost::target(*curOut, graph);
      if (!discovered[t]) {
        discovered[t].flip();
        // vis.discover_vertex(t, graph);
        if (front) {
          statesToVisit.push_front(t);
        }
        else {
          statesToVisit.push_back(t);
        }
      }
    }
    // vis.finish_vertex(v, graph);
  }
  for (uint32 i = 0; i < inOrder.size(); ++i) {
    vis.finish_vertex(inOrder[i], graph);
  }
}
