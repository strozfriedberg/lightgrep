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


#pragma once

#include "basic.h"

#include "automata.h"
#include "instructions.h"
#include "utility.h"

#include <vector>

static const uint32_t NONE = std::numeric_limits<uint32_t>::max();
static const uint32_t NOLABEL = std::numeric_limits<uint32_t>::max();

struct StateLayoutInfo {
  uint32_t Start,
           NumEval,
           NumOther,
           CheckIndex;
  OpCodes Op;

  StateLayoutInfo(): Start(NONE), NumEval(NONE), NumOther(NONE), CheckIndex(NONE), Op(HALT_OP) {}

  StateLayoutInfo(uint32_t s, uint32_t e, uint32_t o, uint32_t chk = NONE): Start(s), NumEval(e), NumOther(o), CheckIndex(chk), Op(HALT_OP) {}

  uint32_t numTotal() const { return NumEval + NumOther; }

  uint32_t end() const { return Start + numTotal(); }

  bool operator==(const StateLayoutInfo& x) const {
    return Start == x.Start &&
           NumEval == x.NumEval &&
           NumOther == x.NumOther &&
           CheckIndex == x.CheckIndex;
  }
};

struct CodeGenHelper {
  CodeGenHelper(uint32_t numStates): DiscoverRanks(numStates, NONE),
    Snippets(numStates), Guard(0),
    NumDiscovered(0), MaxLabel(0), MaxCheck(0) {}

  void discover(NFA::VertexDescriptor v, const NFA& graph) {
    DiscoverRanks[v] = NumDiscovered++;

    if (graph.inDegree(v) > 1) {
      Snippets[v].CheckIndex = ++MaxCheck;
    }

    const uint32_t label = graph[v].Label;
    if (label != NOLABEL && label > MaxLabel) {
      MaxLabel = label;
    }
  }

  void addSnippet(uint32_t state, uint32_t numEval, uint32_t numOther) {
    StateLayoutInfo& info(Snippets[state]);
    info.Start = Guard;
    info.NumEval = numEval;
    info.NumOther = numOther;
    Guard += info.numTotal();
  }

  std::vector<uint32_t> DiscoverRanks;
  std::vector<StateLayoutInfo> Snippets;
  uint32_t Guard,
           NumDiscovered,
           MaxLabel,
           MaxCheck;
};

typedef std::vector<std::vector<NFA::VertexDescriptor>> TransitionTbl;

class CodeGenVisitor {
public:
  CodeGenVisitor(CodeGenHelper& helper): Helper(helper) {}

  void discover_vertex(NFA::VertexDescriptor v, const NFA& graph);

  uint32_t calcJumpTableSize(NFA::VertexDescriptor v, const NFA& graph, uint32_t outDegree);

  void finish_vertex(NFA::VertexDescriptor v, const NFA& graph);

private:
  CodeGenHelper& Helper;
};

void specialVisit(const NFA& graph, NFA::VertexDescriptor startVertex, CodeGenVisitor& vis);

