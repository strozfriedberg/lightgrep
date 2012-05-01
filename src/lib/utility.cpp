#include "codegen.h"
#include "concrete_encoders.h"
#include "compiler.h"
#include "encodings.h"
#include "nfabuilder.h"
#include "parser.h"
#include "rewriter.h"

#include <algorithm>
#include <functional>
#include <queue>
#include <sstream>
#include <stdexcept>

#include <boost/graph/graphviz.hpp>

void addKeys(const std::vector<Pattern>& keywords, bool ignoreBad, Parser& p, uint32& keyIdx) {
  for (uint32 i = 0; i < keywords.size(); ++i, ++keyIdx) {
    try {
      p.addPattern(keywords[i], keyIdx);
    }
    catch (std::runtime_error&) {
      if (!ignoreBad) {
        throw;
      }
    }
  }
}

uint32 totalCharacters(const std::vector<Pattern>& keywords) {
  uint32 ret = 0;
  for (auto& p : keywords) {
    ret += p.Expression.size();
  }
  return ret;
}

// FIXME: this duplicates a lot of parsePatterns() in main.cpp
void addKeys(PatternInfo& keyInfo, bool ignoreBad, Parser& p, uint32& keyIdx) {
  addKeys(keyInfo.Patterns, ignoreBad, p, keyIdx);

  for (uint32 i = 0; i < keyInfo.Patterns.size(); ++i) {
    uint32 encIdx = 0;
    const char** end = LG_SUPPORTED_ENCODINGS + sizeof(LG_SUPPORTED_ENCODINGS);
    const char** ptr = std::find(LG_SUPPORTED_ENCODINGS, end,
                                 keyInfo.Patterns[i].Encoding);
    if (ptr != end) {
      encIdx = ptr - LG_SUPPORTED_ENCODINGS;
    }

    keyInfo.Table.emplace_back(i, encIdx);
  }
}

NFAPtr createGraph(PatternInfo& keyInfo, bool determinize, bool ignoreBadParse) {
  Parser p(totalCharacters(keyInfo.Patterns));
  uint32 keyIdx = 0;

  addKeys(keyInfo, ignoreBadParse, p, keyIdx);
  if (p.Fsm) {

    if (determinize) {
      NFAPtr dfa(new NFA(1));
      dfa->TransFac = p.Fsm->TransFac;
      p.Comp.subsetDFA(*dfa, *p.Fsm);
      p.Fsm = dfa;
    }
    p.Comp.labelGuardStates(*p.Fsm);
  }
  return p.Fsm;
}

NFAPtr createGraph(const std::vector<Pattern>& keywords, bool determinize, bool ignoreBadParse) {
  PatternInfo keyInfo;
  keyInfo.Patterns = keywords;
  return createGraph(keyInfo, determinize, ignoreBadParse);
}

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
      *cur++ = *reinterpret_cast<const Instruction*>(&addr);
    }
    else if (1 == tbl[i].size()) {
      const uint32 addr = figureOutLanding(cg, *tbl[i].begin(), graph);
      *cur++ = *reinterpret_cast<const Instruction*>(&addr);
    }
    else {
      const uint32 addr = startIndex + (indirectTbl - start);
      *cur++ = *reinterpret_cast<const Instruction*>(&addr);

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
ProgramPtr createProgram(const NFA& graph) {
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

void bfs(const NFA& graph, NFA::VertexDescriptor start, Visitor& visitor) {
  std::vector<bool> seen(graph.verticesSize());
  std::queue<NFA::VertexDescriptor> next;

  visitor.discoverVertex(start, graph);
  next.push(start);
  seen[start] = true;

  while (!next.empty()) {
    NFA::VertexDescriptor h = next.front();
    next.pop();

    for (uint32 ov = 0; ov < graph.outDegree(h); ++ov) {
      NFA::VertexDescriptor t = graph.outVertex(h, ov);
      if (!seen[t]) {
        // One might think that we discover a vertex at the tail of an
        // edge first, but one would be wrong...
        visitor.treeEdge(h, t, graph);
        visitor.discoverVertex(t, graph);
        next.push(t);
        seen[t] = true;
      }
    }
  }
}

void nextBytes(ByteSet& set, NFA::VertexDescriptor v, const NFA& graph) {
  ByteSet tBits;
  for (uint32 ov = 0; ov < graph.outDegree(v); ++ov) {
    tBits.reset();
    graph[graph.outVertex(v, ov)].Trans->getBits(tBits);
    set |= tBits;
  }
}

ByteSet firstBytes(const NFA& graph) {
  ByteSet ret;
  ret.reset();
  nextBytes(ret, 0, graph);
  return ret;
}

std::shared_ptr<VmInterface> initVM(const std::vector<Pattern>& keywords, SearchInfo&) {
  std::shared_ptr<VmInterface> vm = VmInterface::create();
  NFAPtr fsm = createGraph(keywords);
  ProgramPtr prog = createProgram(*fsm);
  prog->First = firstBytes(*fsm);
  vm->init(prog);
  return vm;
}

std::vector<std::vector<NFA::VertexDescriptor>> pivotStates(NFA::VertexDescriptor source, const NFA& graph) {
  std::vector<std::vector<NFA::VertexDescriptor>> ret(256);
  ByteSet permitted;

  for (uint32 i = 0; i < graph.outDegree(source); ++i) {
    NFA::VertexDescriptor ov = graph.outVertex(source, i);

    permitted.reset();
    graph[ov].Trans->getBits(permitted);
    for (uint32 i = 0; i < 256; ++i) {
      if (permitted[i] && std::find(ret[i].begin(), ret[i].end(), ov) == ret[i].end()) {
        ret[i].push_back(ov);
      }
    }
  }
  return ret;
}

uint32 maxOutbound(const std::vector<std::vector<NFA::VertexDescriptor>>& tranTable) {
  uint32 ret = 0;
  for (const std::vector<NFA::VertexDescriptor>& v : tranTable) {
    ret = v.size() > ret ? v.size() : ret;
  }
  return ret;
}

void writeVertex(std::ostream& out, NFA::VertexDescriptor v, const NFA& graph) {
  out << "  " << v << " [label=\"" << v << "\"";

  if (graph[v].IsMatch) {
    // double ring for match states
    out << ", peripheries=2";
  }

  out << "];\n";
}

std::string escape(char c, const std::string& text) {
  // escape a character in the given string
  std::string repl(text);
  for (std::string::size_type next = repl.find(c);
       next != std::string::npos; next = repl.find(c, next)) {
    repl.insert(next, 1, '\\');
    next += 2;
  }
  return repl;
}

void writeEdge(std::ostream& out, NFA::VertexDescriptor v, NFA::VertexDescriptor u, uint32 priority, const NFA& graph) {
  const std::string esclabel = escape('"', escape('\\', graph[u].label()));

  out << "  " << v << " -> " << u << " ["
      << "label=\"" << esclabel << "\", "
      << "taillabel=\"" << priority << "\"];\n";
}

void writeGraphviz(std::ostream& out, const NFA& graph) {
  out << "digraph G {\n  rankdir=LR;\n  ranksep=equally;\n  node [shape=\"circle\"];" << std::endl;

  for (uint32 i = 0; i < graph.verticesSize(); ++i) {
    writeVertex(out, i, graph);
  }

  for (uint32 i = 0; i < graph.verticesSize(); ++i) {
    for (uint32 j = 0; j < graph.outDegree(i); ++j) {
      writeEdge(out, i, graph.outVertex(i, j), j, graph);
    }
  }

  out << "}" << std::endl;
}
