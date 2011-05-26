
#include <deque>
#include <vector>

#include "codegen.h"

void CodeGenVisitor::discover_vertex(Graph::vertex v, const Graph& graph) {
  Helper->discover(v, graph);
}

uint32 CodeGenVisitor::calcJumpTableSize(Graph::vertex v, const Graph& graph, uint32 outDegree) {
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

void CodeGenVisitor::finish_vertex(Graph::vertex v, const Graph& graph) {
  // std::cerr << "on state " << v << " with discover rank " << Helper->DiscoverRanks[v] << std::endl;

  uint32 label = 0,
         match = 0,
         eval  = (v == 0 ? 0 : graph[v]->numInstructions());

  const Transition* t = graph[v];
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
  else {
    outOps = calcJumpTableSize(v, graph, outDegree);

    if (outDegree < 4 || outOps == 0) {
      // count each of the non-initial children
      outOps += 2*(outDegree-1);

      // count the first child only if it needs a jump
      if (Helper->DiscoverRanks[v] + 1 !=
          Helper->DiscoverRanks[graph.outVertex(v, 0)]) {
        outOps += 2;
      }
    }
  }

  const uint32 totalSize = outOps + label + match +
                           (Helper->Snippets[v].CheckIndex == NONE ? 0: 1);

  Helper->addSnippet(v, eval, totalSize);

  // std::cerr << "outOps = " << outOps << "; labels = " << labels << "; match = " << isMatch << std::endl;
  // std::cerr << "state " << v << " has snippet " << "(" << Helper->Snippets[v].first << ", " << Helper->Snippets[v].second << ")" << std::endl;
}

void specialVisit(const Graph& graph, Graph::vertex startVertex, CodeGenVisitor& vis) {
  std::deque<Graph::vertex> statesToVisit;
  std::vector<Graph::vertex> inOrder;
  std::vector<bool> discovered(graph.numVertices(), false);

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
