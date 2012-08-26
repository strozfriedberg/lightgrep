#include "compiler.h"

#include "codegen.h"

uint32 figureOutLanding(std::shared_ptr<CodeGenHelper> cg, NFA::VertexDescriptor v, const NFA& graph) {
  // If the jump is to a state that has only a single out edge, and there's
  // no label on the state, then jump forward directly to the out-edge state.
  if (1 == graph.outDegree(v) &&
      NOLABEL == graph[v].Label && !graph[v].IsMatch) {
    return cg->Snippets[graph.outVertex(v, 0)].Start;
  }
  else {
    return cg->Snippets[v].Start + cg->Snippets[v].NumEval;
  }
}

// JumpTables are either ranged, or full-size, and can have indirect tables at the end when there are multiple transitions out on a single byte value
void createJumpTable(std::shared_ptr<CodeGenHelper> cg, Instruction const* const base, Instruction* const start, NFA::VertexDescriptor v, const NFA& graph) {
  const uint32 startIndex = start - base;
  Instruction* cur = start,
             * indirectTbl;

  std::vector<std::vector<NFA::VertexDescriptor>> tbl(pivotStates(v, graph));
  uint32 first = 0,
         last  = 255;

  for (uint32 i = 0; i < 256; ++i) {
    if (!tbl[i].empty()) {
      first = i;
      break;
    }
  }

  for (uint32 i = 255; i > first; --i) {
    if (!tbl[i].empty()) {
      last = i;
      break;
    }
  }

  *cur++ = Instruction::makeJumpTableRange(first, last);
  indirectTbl = start + 2 + (last - first);

  for (uint32 i = first; i <= last; ++i) {
    if (tbl[i].empty()) {
      const uint32 addr = 0xffffffff;
      *cur++ = reinterpret_cast<const Instruction&>(addr);
    }
    else if (1 == tbl[i].size()) {
      const uint32 addr = figureOutLanding(cg, *tbl[i].begin(), graph);
      *cur++ = reinterpret_cast<const Instruction&>(addr);
    }
    else {
      const uint32 addr = startIndex + (indirectTbl - start);
      *cur++ = reinterpret_cast<const Instruction&>(addr);

      // write the indirect table in reverse edge order because
      // parent threads have priority over forked children
      for (int32 j = tbl[i].size() - 1; j >= 0; --j) {
        const uint32 landing = figureOutLanding(cg, tbl[i][j], graph);

        *indirectTbl = j > 0 ?
          Instruction::makeFork(indirectTbl, landing) :
          Instruction::makeJump(indirectTbl, landing);
        indirectTbl += 2;
      }
    }
  }

  if (indirectTbl - base != cg->Snippets[v].end()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("whoa, big trouble in Little China on " << v << "... Start = "
      << cg->Snippets[v].Start << ", NumEval = " << cg->Snippets[v].NumEval
      << ", NumOther = " << cg->Snippets[v].NumOther << ", but indirectTbl is at " << (indirectTbl - base) << std::endl
    );
  }
}

// need a two-pass to get it to work with the bgl visitors
//  discover_vertex: determine slot
//  finish_vertex:
ProgramPtr Compiler::createProgram(const NFA& graph) {
  // std::cerr << "Compiling to byte code" << std::endl;
  ProgramPtr ret(new Program);
  const uint32 numVs = graph.verticesSize();
  std::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(numVs));
  CodeGenVisitor vis(cg);
  specialVisit(graph, 0ul, vis);
  // std::cerr << "Determined order in first pass" << std::endl;
  ret->NumChecked = cg->NumChecked;
  ret->resize(cg->Guard);

  for (NFA::VertexDescriptor v = 0; v < numVs; ++v) {
    // if (++i % 10000 == 0) {
    //   std::cerr << "have compiled " << i << " states so far" << std::endl;
    // }
    Instruction* curOp = &(*ret)[cg->Snippets[v].Start];
    Transition* t(graph[v].Trans);
    if (t) {
      t->toInstruction(curOp);
      curOp += t->numInstructions();
      // std::cerr << "wrote " << i << std::endl;

      if (graph[v].Label != NOLABEL) {
        *curOp++ = Instruction::makeLabel(graph[v].Label);
      }

      if (cg->Snippets[v].CheckIndex != NONE) {
        *curOp++ = Instruction::makeCheckHalt(cg->Snippets[v].CheckIndex);
      }

      if (graph[v].IsMatch) {
        *curOp++ = Instruction::makeMatch();

        if (graph.outDegree(v)) {
          // nonterminal match, fork to FINISH_OP
          *curOp = Instruction::makeFork(curOp, cg->Guard+1);
          curOp += 2;
        }
        else {
          // terminal match, FINISH_OP is next
          *curOp++ = Instruction::makeFinish();
        }
      }
    }

    if (JUMP_TABLE_RANGE_OP == cg->Snippets[v].Op) {
      createJumpTable(cg, &(*ret)[0], curOp, v, graph);
      continue;
    }

    const uint32 v_odeg = graph.outDegree(v);
    if (v_odeg > 0) {
      NFA::VertexDescriptor curTarget;

      // layout non-initial children in reverse order
      for (uint32 i = v_odeg-1; i > 0; --i) {
        curTarget = graph.outVertex(v, i);
        *curOp = Instruction::makeFork(curOp, cg->Snippets[curTarget].Start);
        curOp += 2;
      }

      // layout first child, falling through if possible
      curTarget = graph.outVertex(v, 0);
      if (cg->DiscoverRanks[v] + 1 != cg->DiscoverRanks[curTarget] ) {
        *curOp = Instruction::makeJump(curOp, cg->Snippets[curTarget].Start);
        curOp += 2;
      }
    }
  }

//  if (!(Instruction::makeHalt() == ret->back())) {
  // penultimate instruction will always be Halt, so Vm can jump there
  ret->push_back(Instruction::makeHalt());
//  }

  // last instruction will always be Finish, for handling matches
  ret->push_back(Instruction::makeFinish());

  return ret;
}