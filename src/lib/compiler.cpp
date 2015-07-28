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

#include "compiler.h"

#include "codegen.h"
#include "program.h"
#include "utility.h"

#include <tuple>

uint32_t figureOutLanding(const CodeGenHelper& cg, NFA::VertexDescriptor v, const NFA& graph) {
  // If the jump is to a state that has only a single out edge, and there's
  // no label on the state, then jump forward directly to the out-edge state.
  // i.e., this eliminates an indirect jump... it causes dead code.
  if (1 == graph.outDegree(v) &&
      NOLABEL == graph[v].Label && !graph[v].IsMatch) {
    return cg.Snippets[graph.outVertex(v, 0)].Start;
  }
  else {
    return cg.Snippets[v].Start + cg.Snippets[v].NumEval;
  }
}

std::tuple<uint32_t, uint32_t> minAndMaxValues(const std::vector<std::vector<NFA::VertexDescriptor>>& tbl) {
  uint32_t first = 0,
           last  = 255;

  for (uint32_t i = 0; i < 256; ++i) {
    if (!tbl[i].empty()) {
      first = i;
      break;
    }
  }
  for (uint32_t i = 255; i > first; --i) {
    if (!tbl[i].empty()) {
      last = i;
      break;
    }
  }
  return std::make_tuple(first, last);
}

// JumpTables are either ranged, or full-size, and can have indirect tables at the end when there are multiple transitions out on a single byte value
void createJumpTable(const CodeGenHelper& cg, Instruction const* const base, Instruction* const start, NFA::VertexDescriptor v, const NFA& graph) {
  const uint32_t startIndex = start - base;
  Instruction* cur = start,
             * indirectTbl;

  auto tbl(pivotStates(v, graph));

  uint32_t first, last;
  std::tie(first, last) = minAndMaxValues(tbl);

  *cur++ = Instruction::makeJumpTableRange(first, last);
  indirectTbl = start + 2 + (last - first);

  for (uint32_t i = first; i <= last; ++i) {
    if (tbl[i].empty()) {
      const uint32_t addr = 0xffffffff;
      *cur++ = reinterpret_cast<const Instruction&>(addr);
    }
    else if (1 == tbl[i].size()) {
      const uint32_t addr = figureOutLanding(cg, *tbl[i].begin(), graph);
      *cur++ = reinterpret_cast<const Instruction&>(addr);
    }
    else {
      const uint32_t addr = startIndex + (indirectTbl - start);
      *cur++ = reinterpret_cast<const Instruction&>(addr);

      // write the indirect table in reverse edge order because
      // parent threads have priority over forked children
      for (int32_t j = tbl[i].size() - 1; j >= 0; --j) {
        const uint32_t landing = figureOutLanding(cg, tbl[i][j], graph);

        *indirectTbl = j > 0 ?
          Instruction::makeFork(indirectTbl, landing) :
          Instruction::makeJump(indirectTbl, landing);
        indirectTbl += 2;
      }
    }
  }

  if (indirectTbl - base != cg.Snippets[v].end()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("whoa, big trouble in Little China on " << v << "... Start = "
      << cg.Snippets[v].Start << ", NumEval = " << cg.Snippets[v].NumEval
      << ", NumOther = " << cg.Snippets[v].NumOther << ", but indirectTbl is at " << (indirectTbl - base) << std::endl
    );
  }
}

bool targetCodeFollowsSource(const CodeGenHelper& cg, const NFA::VertexDescriptor source, const NFA::VertexDescriptor target) {
  return cg.DiscoverRanks[source] + 1 == cg.DiscoverRanks[target];
}

void encodeState(const NFA& graph, NFA::VertexDescriptor v, const CodeGenHelper& cg, Instruction const* const base, Instruction* curOp) {
  const NFA::Vertex& state(graph[v]);
  if (state.Trans) {
    state.Trans->toInstruction(curOp);
    curOp += state.Trans->numInstructions();
    // std::cerr << "wrote " << i << std::endl;

    if (state.Label != NOLABEL) {
      *curOp++ = Instruction::makeLabel(state.Label);
    }
    if (cg.Snippets[v].CheckIndex != NONE) {
      *curOp++ = Instruction::makeCheckHalt(cg.Snippets[v].CheckIndex);
    }
    if (state.IsMatch) {
      *curOp++ = Instruction::makeMatch();

      if (graph.outDegree(v)) {
        // nonterminal match, fork to FINISH_OP
        *curOp = Instruction::makeFork(curOp, cg.Guard+1);
        curOp += 2;
      }
      else {
        // terminal match, FINISH_OP is next
        *curOp++ = Instruction::makeFinish();
      }
    }
  }

  if (JUMP_TABLE_RANGE_OP == cg.Snippets[v].Op) {
    createJumpTable(cg, base, curOp, v, graph);
  }
  else {
    const uint32_t v_odeg = graph.outDegree(v);
    if (v_odeg > 0) {
      NFA::VertexDescriptor curTarget;

      // layout non-initial children in reverse order
      for (uint32_t i = v_odeg-1; i > 0; --i) {
        curTarget = graph.outVertex(v, i);
        *curOp = Instruction::makeFork(curOp, cg.Snippets[curTarget].Start);
        curOp += 2;
      }

      // layout first child, falling through if possible
      curTarget = graph.outVertex(v, 0);
      if (!targetCodeFollowsSource(cg, v, curTarget)) { // else: fall through happens
        *curOp = Instruction::makeJump(curOp, cg.Snippets[curTarget].Start);
        curOp += 2;
      }
    }
  }
}

// need a two-pass to get it to work with the bgl visitors
//  discover_vertex: determine slot
//  finish_vertex:
ProgramPtr Compiler::createProgram(const NFA& graph) {
  // std::cerr << "Compiling to byte code" << std::endl;
  const uint32_t numVs = graph.verticesSize();
  CodeGenHelper cg(numVs);
  CodeGenVisitor vis(cg);
  specialVisit(graph, 0ul, vis);
  // std::cerr << "Determined order in first pass" << std::endl;

  ProgramPtr ret(new Program(cg.Guard+2));
  ret->MaxLabel= cg.MaxLabel;
  ret->MaxCheck = cg.MaxCheck;
  std::tie(ret->FilterOff, ret->Filter) = bestPair(graph);

  for (NFA::VertexDescriptor v = 0; v < numVs; ++v) {
    // if (++i % 10000 == 0) {
    //   std::cerr << "have compiled " << i << " states so far" << std::endl;
    // }
    encodeState(graph, v, cg, &(*ret)[0], &(*ret)[cg.Snippets[v].Start]);
  }
  // penultimate instruction will always be Halt, so Vm can jump there
  (*ret)[cg.Guard] = Instruction::makeHalt();
  // last instruction will always be Finish, for handling matches
  (*ret)[cg.Guard+1] = Instruction::makeFinish();

  return ret;
}
