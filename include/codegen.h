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

#pragma once

#include "basic.h"

#include "automata.h"
#include "instructions.h"
#include "utility.h"

#include <vector>

static const uint32 NONE = std::numeric_limits<uint32>::max();
static const uint32 NOLABEL = std::numeric_limits<uint32>::max();

struct StateLayoutInfo {
  uint32 Start,
         NumEval,
         NumOther,
         CheckIndex;
  OpCodes Op;

  StateLayoutInfo(): Start(NONE), NumEval(NONE), NumOther(NONE), CheckIndex(NONE), Op(UNINITIALIZED) {}

  StateLayoutInfo(uint32 s, uint32 e, uint32 o, uint32 chk = NONE): Start(s), NumEval(e), NumOther(o), CheckIndex(chk), Op(UNINITIALIZED) {}

  uint32 numTotal() const { return NumEval + NumOther; }

  uint32 end() const { return Start + numTotal(); }

  bool operator==(const StateLayoutInfo& x) const {
    return Start == x.Start &&
           NumEval == x.NumEval &&
           NumOther == x.NumOther &&
           CheckIndex == x.CheckIndex;
  }
};

struct CodeGenHelper {
  CodeGenHelper(uint32 numStates): DiscoverRanks(numStates, NONE),
    Snippets(numStates), Guard(0), NumDiscovered(0), NumChecked(0) {}

  void discover(NFA::VertexDescriptor v, const NFA& graph) {
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

  std::vector<uint32> DiscoverRanks;
  std::vector<StateLayoutInfo> Snippets;
  uint32 Guard,
         NumDiscovered,
         NumChecked;
};

typedef std::vector<std::vector<NFA::VertexDescriptor>> TransitionTbl;

class CodeGenVisitor {
public:
  CodeGenVisitor(std::shared_ptr<CodeGenHelper> helper): Helper(helper) {}

  void discover_vertex(NFA::VertexDescriptor v, const NFA& graph);

  uint32 calcJumpTableSize(NFA::VertexDescriptor v, const NFA& graph, uint32 outDegree);

  void finish_vertex(NFA::VertexDescriptor v, const NFA& graph);

private:
  std::shared_ptr<CodeGenHelper> Helper;
};

void specialVisit(const NFA& graph, NFA::VertexDescriptor startVertex, CodeGenVisitor& vis);

