#pragma once

#include "utility.h"
#include "instructions.h"

#include <algorithm>
#include <cstring>
#include <deque>
#include <exception>
#include <iostream>
#include <vector>

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

  void discover(Graph::vertex v, const Graph& graph) {
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

typedef std::vector< std::vector< Graph::vertex > > TransitionTbl;

class CodeGenVisitor {
public:
  CodeGenVisitor(boost::shared_ptr<CodeGenHelper> helper): Helper(helper) {}

  void discover_vertex(Graph::vertex v, const Graph& graph) {
    Helper->discover(v, graph);
  }

  bool shouldBeJumpTable(Graph::vertex v, const Graph& graph, uint32 outDegree, uint32& totalSize) {
    if (outDegree > 3) {
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

  void finish_vertex(Graph::vertex v, const Graph& graph) {
    // std::cerr << "on state " << v << " with discover rank " << Helper->DiscoverRanks[v] << std::endl;

    bool   match = false;
    uint32 labels = 0,
           eval   = (v == 0 ? 0: graph[v]->numInstructions()),
           totalSize;

    const uint32 outDegree = graph.outDegree(v);

    TransitionPtr t = graph[v];
    if (t) {
      if (t->Label != UNALLOCATED) {
        ++labels;
      }
      if (t->IsMatch) {
        match = true;
      }
    }

    uint32 outOps = 0;

    if (outDegree == 0) {
      // std::cerr << "no out edges, so a halt" << std::endl;
      outOps = 1; // HALT instruction
      totalSize = outOps + labels + (match ? 1: 0) +
                  (Helper->Snippets[v].CheckIndex == UNALLOCATED ? 0: 1);
    }
    else if (outDegree < 4) {
      for (uint32 ov = 0; ov < outDegree; ++ov) {
        // if a target state immediately follows the current state,
        // then we don't need an instruction for it
        if (Helper->DiscoverRanks[v] + 1 !=
            Helper->DiscoverRanks[graph.outVertex(v, ov)]) {
          outOps += 2;
        }
      }

      totalSize = outOps + labels + (match ? 1: 0) +
                  (Helper->Snippets[v].CheckIndex == UNALLOCATED ? 0: 1);
    }
    else {
      shouldBeJumpTable(v, graph, outDegree, totalSize);
    }

    Helper->addSnippet(v, eval, totalSize);

    // std::cerr << "outOps = " << outOps << "; labels = " << labels << "; match = " << isMatch << std::endl;
    // std::cerr << "state " << v << " has snippet " << "(" << Helper->Snippets[v].first << ", " << Helper->Snippets[v].second << ")" << std::endl;
  }

private:
  boost::shared_ptr<CodeGenHelper> Helper;
};

template<class VisitorT>
void specialVisit(const Graph& graph, Graph::vertex startVertex, VisitorT& vis) {
  std::deque< Graph::vertex > statesToVisit;
  std::vector< Graph::vertex > inOrder;
  std::vector< bool > discovered(graph.numVertices(), false);

  inOrder.reserve(graph.numVertices());

  discovered[startVertex].flip();
  statesToVisit.push_back(startVertex);

  while (!statesToVisit.empty()) {
    Graph::vertex v = statesToVisit.front();
    statesToVisit.pop_front();

    vis.discover_vertex(v, graph);
    inOrder.push_back(v);

    const uint32 numOut = graph.outDegree(v);
    const bool nobranch = numOut < 2;

    for (uint32 i = 0; i < numOut; ++i) {
      Graph::vertex t = graph.outVertex(v, i);
      if (!discovered[t]) {
        discovered[t].flip();

        if (nobranch) {
          statesToVisit.push_front(t);
        }
        else {
          statesToVisit.push_back(t);
        }
      }
    }
  }

  for (uint32 i = 0; i < inOrder.size(); ++i) {
    vis.finish_vertex(inOrder[i], graph);
  }
}
