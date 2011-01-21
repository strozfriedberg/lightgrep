#pragma once

#include "utility.h"
#include "instructions.h"

#include <algorithm>
#include <cstring>
#include <deque>
#include <exception>
#include <iostream>
#include <vector>

static const uint32 NONE = std::numeric_limits<uint32>::max();

struct StateLayoutInfo {
  uint32 Start,
         NumEval,
         NumOther,
         CheckIndex;
  OpCodes Op;

  StateLayoutInfo(): Start(NONE), NumEval(NONE), NumOther(NONE), CheckIndex(NONE), Op(UNINITIALIZED) {}
  StateLayoutInfo(uint32 s, uint32 e, uint32 o, uint32 chk = NONE): Start(s), NumEval(e), NumOther(o), CheckIndex(chk), Op(UNINITIALIZED) {}

  uint32 numTotal() const { return NumEval + NumOther; }

  bool operator==(const StateLayoutInfo& x) const {
    return Start == x.Start && NumEval == x.NumEval && NumOther == x.NumOther && CheckIndex == x.CheckIndex;
  }
};

/*
std::ostream& operator<<(std::ostream& out, const StateLayoutInfo& info) {
  out << "Start == " << info.Start 
      << ", NumEval == " << info.NumEval
      << ", NumOther == " << info.NumOther
      << ", CheckIndex == " << info.CheckIndex
      << ", Op == " << info.Op;
  return out;
}
*/

struct CodeGenHelper {
  CodeGenHelper(uint32 numStates): DiscoverRanks(numStates, NONE), Snippets(numStates), Guard(0), NumDiscovered(0), NumChecked(0) {}

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

  uint32 calcJumpTableSize(Graph::vertex v, const Graph& graph, uint32 outDegree) {
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

        uint32 totalSize;

        if (last - first < 128) {
          // JumpTableRange instr + inclusive number
          totalSize = 2 + (last - first) + sizeIndirectTables;
          Helper->Snippets[v].Op = JUMP_TABLE_RANGE_OP;
        }
        else {
          Helper->Snippets[v].Op = JUMP_TABLE_OP;
          totalSize = 257 + sizeIndirectTables;
        }

        return totalSize;
      }
    }
    return 0;
  }

  void finish_vertex(Graph::vertex v, const Graph& graph) {
    // std::cerr << "on state " << v << " with discover rank " << Helper->DiscoverRanks[v] << std::endl;

    uint32 label = 0,
           match = 0,
           eval  = (v == 0 ? 0 : graph[v]->numInstructions());

    TransitionPtr t = graph[v];
    if (t) {
      if (t->Label != NONE) {
        label = 1;
      }
      if (t->IsMatch) {
        match = 1;
      }
    }

    const uint32 outDegree = graph.outDegree(v);
    uint32 outOps = 0;

    if (outDegree == 0) {
      // std::cerr << "no out edges, so a halt" << std::endl;
      outOps = 1; // HALT instruction
    }
    else if (outDegree < 4) {
      // count each of the non-initial children
      outOps += 2*(outDegree-1);

      // count the first child only if it needs a jump
      if (Helper->DiscoverRanks[v] + 1 != 
          Helper->DiscoverRanks[graph.outVertex(v, 0)]) {
        outOps += 2;
      }
    }
    else {
      outOps = calcJumpTableSize(v, graph, outDegree);
    }

    const uint32 totalSize = outOps + label + match +
                             (Helper->Snippets[v].CheckIndex == NONE ? 0: 1);

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
