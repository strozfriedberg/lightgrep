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

struct StateLayoutInfo {
  uint32 Start,
         NumEval,
         NumOther,
         CheckIndex;
  OpCodes Op;

  StateLayoutInfo(): Start(UNALLOCATED), NumEval(UNALLOCATED), NumOther(UNALLOCATED), CheckIndex(UNALLOCATED), Op(UNINITIALIZED) {}
  StateLayoutInfo(uint32 s, uint32 e, uint32 o, uint32 chk = UNALLOCATED): Start(s), NumEval(e), NumOther(o), CheckIndex(chk), Op(UNINITIALIZED) {}

  uint32 numTotal() const { return NumEval + NumOther; }

  bool operator==(const StateLayoutInfo& x) const {
    return Start == x.Start && NumEval == x.NumEval && NumOther == x.NumOther && CheckIndex == x.CheckIndex;
  }
};

struct CodeGenHelper {
  CodeGenHelper(uint32 numStates): DiscoverRanks(numStates, UNALLOCATED), Snippets(numStates), Guard(0), NumDiscovered(0), NumChecked(0) {}

  void discover(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    DiscoverRanks[v] = NumDiscovered++;
    if (graph.inDegree(v) > 1) {
      Snippets[v].CheckIndex = ++NumChecked;
    }
  }

  void addSnippet(uint32 state, uint32 numEval, uint32 numOther) {
    StateLayoutInfo& info(Snippets[state]);
    info.Start = Guard;
    info.NumEval = numEval;
    info.NumOther = numOther;
    Guard += info.numTotal();
  }

  std::vector< uint32 > DiscoverRanks;
  std::vector< StateLayoutInfo > Snippets;
  uint32 Guard,
         NumDiscovered,
         NumChecked;
};

typedef std::vector< std::vector< DynamicFSM::vertex_descriptor > > TransitionTbl;

class CodeGenVisitor: public boost::default_bfs_visitor {
public:
  CodeGenVisitor(boost::shared_ptr<CodeGenHelper> helper): Helper(helper) {}

  void discover_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    Helper->discover(v, graph);
  }

  bool shouldBeJumpTable(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph, uint32 outDegree, uint32& totalSize) {
    if (outDegree > 3 && (v == 0 || graph[v]->Label == UNALLOCATED)) {
      TransitionTbl tbl(pivotStates(v, graph));
      if (maxOutbound(tbl) < outDegree) {
        uint32 sizeIndirectTables = 0,
                num,
                first = 256,
                last  = 0;
        for (uint32 i = 0; i < 256; ++i) {
          num = tbl[i].size();
          if (num > 1) {
            sizeIndirectTables += num;
          }
          if (num) {
            first = std::min(first, i);
            last  = i;
          }
        }
        sizeIndirectTables *= 2;

        if (last - first < 128) {
          totalSize = 2 + (last - first) + sizeIndirectTables; // JumpTableRange instr + inclusive number
          Helper->Snippets[v].Op = JUMP_TABLE_RANGE_OP;
        }
        else {
          Helper->Snippets[v].Op = JUMP_TABLE_OP;
          totalSize = 257 + sizeIndirectTables;
        }
        return true;
      }
    }
    totalSize = 0;
    return false;
  }

  void finish_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    // std::cerr << "on state " << v << " with discover rank " << Helper->DiscoverRanks[v] << std::endl;
    bool   match = false;
    uint32 labels = 0,
           eval   = (v == 0 ? 0: graph[v]->numInstructions()) + (Helper->Snippets[v].CheckIndex == UNALLOCATED ? 0: 1),
           outDegree = graph.outDegree(v),
           totalSize;
    if (shouldBeJumpTable(v, graph, outDegree, totalSize)) {
      Helper->addSnippet(v, eval, totalSize);
      return;
    }
    TransitionPtr t = graph[v];
    if (t) {
      if (t->Label < 0xffffffff) {
        ++labels;
      }
      if (t->IsMatch) {
        match = true;
      }
    }
    uint32 outOps = 0;
    DynamicFSM::const_iterator  ov(graph.outVertices(v).begin()),
                                ov_end(graph.outVertices(v).end());
    if (ov == ov_end) {
      // std::cerr << "no out edges, so a halt" << std::endl;
      outOps = 1; // HALT instruction
    }
    else {
      for (; ov != ov_end; ++ov) {
        // if a target state immediately follows the current state, then we don't need an instruction for it
        if (Helper->DiscoverRanks[v] + 1 != Helper->DiscoverRanks[*ov]) {
          outOps += 2;
        }
      }
    }
    // std::cerr << "outOps = " << outOps << "; labels = " << labels << "; match = " << isMatch << std::endl;
    Helper->addSnippet(v, eval, outOps + labels + (match ? 1: 0));
    // std::cerr << "state " << v << " has snippet " << "(" << Helper->Snippets[v].first << ", " << Helper->Snippets[v].second << ")" << std::endl;
  }

private:
  boost::shared_ptr<CodeGenHelper> Helper;
};

template<class VisitorT>
void specialVisit(const DynamicFSM& graph, DynamicFSM::vertex_descriptor startVertex, VisitorT& vis) {
  std::deque< DynamicFSM::vertex_descriptor > statesToVisit;
  std::vector< DynamicFSM::vertex_descriptor > inOrder;
  std::vector< bool > discovered(graph.numVertices(), false);

  discovered[startVertex].flip();
  // vis.discover_vertex(startVertex, graph);
  statesToVisit.push_back(startVertex);
  while (!statesToVisit.empty()) {
    DynamicFSM::vertex_descriptor v = statesToVisit.front();
    statesToVisit.pop_front();

    vis.discover_vertex(v, graph);
    inOrder.push_back(v);

    const uint32 numOut = graph.outDegree(v);

    DynamicFSM::const_iterator  ov(graph.outVertices(v).begin()),
                                ov_end(graph.outVertices(v).end());
    const bool nobranch = numOut < 2;
    for (; ov != ov_end; ++ov) {
      DynamicFSM::vertex_descriptor t = *ov;
      if (!discovered[t]) {
        discovered[t].flip();
        // vis.discover_vertex(t, graph);
        if (nobranch) {
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
