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
  CodeGenHelper(uint32 numStates): Snippets(numStates), Guard(0) {}

  void addSnippet(uint32 state, uint32 num) {
    Snippets[state] = std::make_pair(Guard, num);
    Guard += num;
  }

  std::vector< Instruction > Program;
  std::vector< std::pair< uint32, uint32 > > Snippets;
  uint32 Guard;
};

class CodeGenVisitor: public boost::default_bfs_visitor {
public:
  typedef DynamicFSM::in_edge_iterator InEdgeIt;
  typedef std::pair<InEdgeIt, InEdgeIt> InEdgeRange;

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
