/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <deque>
#include <vector>

#include "codegen.h"

void CodeGenVisitor::discover_vertex(NFA::VertexDescriptor v, const NFA& graph) {
  Helper.discover(v, graph);
}

uint32_t CodeGenVisitor::calcJumpTableSize(NFA::VertexDescriptor v, const NFA& graph, uint32_t outDegree) {
  if (outDegree > 3) {
    TransitionTbl tbl(pivotStates(v, graph));
    if (maxOutbound(tbl) < outDegree) {
      uint32_t sizeIndirectTables = 0,
             num,
             first = 256,
             last  = 0;

      for (uint32_t i = 0; i < 256; ++i) {
        num = tbl[i].size();
        if (num > 1) {
          sizeIndirectTables += num;
        }
        if (num) {
          first = std::min(first, i);
          last  = i;
        }
      }

      Helper.Snippets[v].Op = JUMP_TABLE_RANGE_OP;
      // JumpTableRange instr + inclusive number
      return 2 + (last - first) + 2*sizeIndirectTables;
    }
  }
  return 0;
}

void CodeGenVisitor::finish_vertex(NFA::VertexDescriptor v, const NFA& graph) {
  // std::cerr << "on state " << v << " with discover rank " << Helper.DiscoverRanks[v] << std::endl;

  uint32_t label = 0,
         match = 0,
         eval  = (v == 0 ? 0 : graph[v].Trans->numInstructions());

  const uint32_t outDegree = graph.outDegree(v);

  if (graph[v].Label != NONE) {
    label = 1;
  }

  if (graph[v].IsMatch) {
    // 1 for match, 1 for finish; or 1 for match, 2 for jump if
    // match is nonterminal
    match = 2 + (outDegree > 0);
  }

  uint32_t outOps = 0;

  if (outDegree) {
    outOps = calcJumpTableSize(v, graph, outDegree);

    if (outDegree < 4 || outOps == 0) {
      // count each of the non-initial children
      outOps += 2*(outDegree-1);

      // count the first child only if it needs a jump
      if (Helper.DiscoverRanks[v] + 1 !=
          Helper.DiscoverRanks[graph.outVertex(v, 0)]) {
        outOps += 2;
      }
    }
  }

  const uint32_t totalSize = outOps + label + match +
                           (Helper.Snippets[v].CheckIndex == NONE ? 0: 1);

  Helper.addSnippet(v, eval, totalSize);

  // std::cerr << "outOps = " << outOps << "; labels = " << labels << "; match = " << isMatch << std::endl;
  // std::cerr << "state " << v << " has snippet " << "(" << Helper.Snippets[v].first << ", " << Helper.Snippets[v].second << ")" << std::endl;
}

void specialVisit(const NFA& graph, NFA::VertexDescriptor startVertex, CodeGenVisitor& vis) {
  std::deque<NFA::VertexDescriptor> statesToVisit;
  std::vector<NFA::VertexDescriptor> inOrder;
  std::vector<bool> discovered(graph.verticesSize(), false);

  inOrder.reserve(graph.verticesSize());

  discovered[startVertex].flip();
  statesToVisit.push_back(startVertex);

  while (!statesToVisit.empty()) {
    const NFA::VertexDescriptor v = statesToVisit.front();
    statesToVisit.pop_front();

    vis.discover_vertex(v, graph);
    inOrder.push_back(v);

    const bool nobranch = graph.outDegree(v) < 2;

    for (const NFA::VertexDescriptor t : graph.outVertices(v)) {
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

  for (const NFA::VertexDescriptor v : inOrder) {
    vis.finish_vertex(v, graph);
  }
}
