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

