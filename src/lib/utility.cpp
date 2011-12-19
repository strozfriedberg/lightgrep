
#include "codegen.h"
#include "concrete_encodings.h"
#include "compiler.h"
#include "encodings.h"
#include "nfabuilder.h"
#include "parser.h"
#include "rewriter.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <queue>

#include <boost/bind.hpp>
#include <boost/graph/graphviz.hpp>

void addPattern(
  NFABuilder& nfab,
  ParseTree& tree,
  Compiler& comp,
  Graph& g,
  const std::string& pattern,
  uint32 patIndex,
  bool caseSensitive,
  bool fixedString,
  const std::string& encoding)
{
  // prepare the NFA builder
  nfab.reset();
  nfab.setCurLabel(patIndex);
  nfab.setCaseSensitive(caseSensitive);

  if (encoding == LG_SUPPORTED_ENCODINGS[LG_ENC_ASCII]) {
    nfab.setEncoding(boost::shared_ptr<Encoding>(new Ascii));
  }
  else if (encoding == LG_SUPPORTED_ENCODINGS[LG_ENC_UTF_16]) {
    nfab.setEncoding(boost::shared_ptr<Encoding>(new UCS16));
  }
  else {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Unrecognized encoding '" << encoding << "'");
  }

  // parse the pattern
  if (parse(pattern, fixedString, tree)) {
    // rewrite the parse tree, if necessary
    bool rewritten = false;
    if (pattern.find('?',1) != std::string::npos) {
      rewritten |= reduce_trailing_nongreedy_then_empty(tree.Root);
    }

    if (rewritten || pattern.find('{',1) != std::string::npos) {
      reduce_empty_subtrees(tree.Root);
      reduce_useless_repetitions(tree.Root);
    }

    // build the NFA for this pattern
    if (nfab.build(tree)) {
      // and merge it into the greater NFA
      comp.pruneBranches(*nfab.getFsm());
      comp.mergeIntoFSM(g, *nfab.getFsm());
      return;
    }
  }

  throw std::runtime_error("Could not parse");
}

void addKeys(const std::vector<std::string>& keywords, const std::string& encoding, bool caseSensitive, bool litMode, GraphPtr& fsm, uint32& keyIdx, Compiler& comp) {
  ParseTree   tree;
  NFABuilder  nfab;

  for (uint32 i = 0; i < keywords.size(); ++i, ++keyIdx) {
    const std::string& kw(keywords[i]);

    try {
      addPattern(nfab, tree, comp, *fsm, kw, keyIdx,
                 caseSensitive, litMode, encoding);
    }
    catch (const std::runtime_error& e) {
      std::cerr << e.what() << " keyword number " << i
                << ", " << kw << std::endl;
    }
  }
}

uint32 totalCharacters(const std::vector<std::string>& keywords) {
  uint32 ret = 0;
  for (std::vector<std::string>::const_iterator it(keywords.begin()); it != keywords.end(); ++it) {
    ret += it->size();
  }
  return ret;
}

void addKeys(KwInfo& keyInfo, GraphPtr g, Compiler& comp, const std::string encName, bool caseSensitive, bool litMode, uint32& keyIdx) {
  keyInfo.Encodings.push_back(encName);
  const uint32 encIdx = keyInfo.Encodings.size() - 1;

  addKeys(keyInfo.Keywords, encName, caseSensitive, litMode, g, keyIdx, comp);

  for (uint32 i = 0; i < keyInfo.Keywords.size(); ++i) {
    keyInfo.PatternsTable.push_back(std::make_pair<uint32,uint32>(i, encIdx));
  }
}

GraphPtr createGraph(const std::vector<std::string>& keywords, uint32 enc, bool caseSensitive, bool litMode, bool determinize) {
  KwInfo keyInfo;
  keyInfo.Keywords = keywords;
  return createGraph(keyInfo, enc, caseSensitive, litMode, determinize);
}

GraphPtr createGraph(KwInfo& keyInfo, uint32 enc, bool caseSensitive, bool litMode, bool determinize) {
  GraphPtr g(new Graph(1, totalCharacters(keyInfo.Keywords)));
  uint32 keyIdx = 0;

  Compiler comp;

  if (enc & CP_ASCII) {
    addKeys(keyInfo, g, comp, LG_SUPPORTED_ENCODINGS[LG_ENC_ASCII], caseSensitive, litMode, keyIdx);
  }

  if (enc & CP_UCS16) {
    addKeys(keyInfo, g, comp, LG_SUPPORTED_ENCODINGS[LG_ENC_UTF_16], caseSensitive, litMode, keyIdx);
  }

  if (g) {
    if (determinize) {
      GraphPtr dfa(new Graph(1));
      comp.subsetDFA(*dfa, *g);
      g = dfa;
    }

    comp.labelGuardStates(*g);
  }

  return g;
}

uint32 figureOutLanding(boost::shared_ptr<CodeGenHelper> cg, Graph::vertex v, const Graph& graph) {
  // If the jump is to a state that has only a single out edge, and there's
  // no label on the state, then jump forward directly to the out-edge state.
  if (1 == graph.outDegree(v) &&
      NOLABEL == graph[v]->Label && !graph[v]->IsMatch) {
    return cg->Snippets[graph.outVertex(v, 0)].Start;
  }
  else {
    return cg->Snippets[v].Start + cg->Snippets[v].NumEval;
  }
}

// JumpTables are either ranged, or full-size, and can have indirect tables at the end when there are multiple transitions out on a single byte value
void createJumpTable(boost::shared_ptr<CodeGenHelper> cg, Instruction const* const base, Instruction* const start, Graph::vertex v, const Graph& graph) {
  const uint32 startIndex = start - base;
  Instruction* cur = start,
             * indirectTbl;

  std::vector< std::vector< Graph::vertex > > tbl(pivotStates(v, graph));
  uint32 first = 0,
         last  = 255;

  if (JUMP_TABLE_RANGE_OP == cg->Snippets[v].Op) {
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
  }
  else {
    *cur++ = Instruction::makeJumpTable();
    indirectTbl = start + 257;
  }

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
ProgramPtr createProgram(const Graph& graph) {
  // std::cerr << "Compiling to byte code" << std::endl;
  ProgramPtr ret(new Program);
  const uint32 numVs = graph.numVertices();
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(numVs));
  CodeGenVisitor vis(cg);
  specialVisit(graph, 0ul, vis);
  // std::cerr << "Determined order in first pass" << std::endl;
  ret->NumChecked = cg->NumChecked;
  ret->resize(cg->Guard);

  for (Graph::vertex v = 0; v < numVs; ++v) {
    // if (++i % 10000 == 0) {
    //   std::cerr << "have compiled " << i << " states so far" << std::endl;
    // }
    Instruction* curOp = &(*ret)[cg->Snippets[v].Start];
    Transition* t(graph[v]);
    if (t) {
      t->toInstruction(curOp);
      curOp += t->numInstructions();
      // std::cerr << "wrote " << i << std::endl;

      if (t->Label != NOLABEL) {
        *curOp++ = Instruction::makeLabel(t->Label);
      }

      if (cg->Snippets[v].CheckIndex != NONE) {
        *curOp++ = Instruction::makeCheckHalt(cg->Snippets[v].CheckIndex);
      }

      if (t->IsMatch) {
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

    if (JUMP_TABLE_RANGE_OP == cg->Snippets[v].Op ||
        JUMP_TABLE_OP == cg->Snippets[v].Op) {
      createJumpTable(cg, &(*ret)[0], curOp, v, graph);
      continue;
    }

    const uint32 v_odeg = graph.outDegree(v);
    if (v_odeg > 0) {
      Graph::vertex curTarget;

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

class SkipTblVisitor: public Visitor {
public:
  SkipTblVisitor(boost::shared_ptr<SkipTable> skip): Skipper(skip) {}

  void discoverVertex(Graph::vertex v, const Graph& graph) const {
    Skipper->calculateTransitions(v, graph);
  }

  void treeEdge(Graph::vertex h, Graph::vertex t, const Graph& graph) const {
    Skipper->setDistance(h, t, graph);
  }

private:
  boost::shared_ptr<SkipTable> Skipper;
};

uint32 calculateLMin(const Graph& graph) {
  return calculateSkipTable(graph)->l_min();
}

boost::shared_ptr<SkipTable> calculateSkipTable(const Graph& graph) {
  // std::cerr << "calculating skiptable and l-min" << std::endl;
  boost::shared_ptr<SkipTable> skip(new SkipTable(graph.numVertices()));
  SkipTblVisitor vis(skip);
  bfs(graph, 0, vis);
  skip->finishSkipVec();
  return skip;
}

void bfs(const Graph& graph, Graph::vertex start, Visitor& visitor) {
  std::vector<bool> seen(graph.numVertices());
  std::queue<Graph::vertex> next;

  visitor.discoverVertex(start, graph);
  next.push(start);
  seen[start] = true;

  while (!next.empty()) {
    Graph::vertex h = next.front();
    next.pop();

    for (uint32 ov = 0; ov < graph.outDegree(h); ++ov) {
      Graph::vertex t = graph.outVertex(h, ov);
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

void nextBytes(ByteSet& set, Graph::vertex v, const Graph& graph) {
  ByteSet tBits;
  for (uint32 ov = 0; ov < graph.outDegree(v); ++ov) {
    tBits.reset();
    graph[graph.outVertex(v, ov)]->getBits(tBits);
    set |= tBits;
  }
}

ByteSet firstBytes(const Graph& graph) {
  ByteSet ret;
  ret.reset();
  nextBytes(ret, 0, graph);
  return ret;
}

boost::shared_ptr<VmInterface> initVM(const std::vector<std::string>& keywords, SearchInfo&) {
  boost::shared_ptr<VmInterface> vm = VmInterface::create();
  GraphPtr fsm = createGraph(keywords);
  ProgramPtr prog = createProgram(*fsm);
  prog->Skip = calculateSkipTable(*fsm);
  prog->First = firstBytes(*fsm);
  vm->init(prog);
  return vm;
}

std::vector< std::vector< Graph::vertex > > pivotStates(Graph::vertex source, const Graph& graph) {
  std::vector< std::vector< Graph::vertex > > ret(256);
  ByteSet permitted;

  for (uint32 i = 0; i < graph.outDegree(source); ++i) {
    Graph::vertex ov = graph.outVertex(source, i);

    permitted.reset();
    graph[ov]->getBits(permitted);
    for (uint32 i = 0; i < 256; ++i) {
      if (permitted[i] && std::find(ret[i].begin(), ret[i].end(), ov) == ret[i].end()) {
        ret[i].push_back(ov);
      }
    }
  }
  return ret;
}

uint32 maxOutbound(const std::vector< std::vector< Graph::vertex > >& tranTable) {
  uint32 ret = 0;
  for (std::vector< std::vector< Graph::vertex > >::const_iterator it(tranTable.begin()); it != tranTable.end(); ++it) {
    ret = it->size() > ret ? it->size() : ret;
  }
  return ret;
}

void writeVertex(std::ostream& out, Graph::vertex v, const Graph& graph) {
  out << "  " << v << " [label=\"" << v << "\"";

  if (graph[v] && graph[v]->IsMatch) {
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

void writeEdge(std::ostream& out, Graph::vertex v, Graph::vertex u,
               uint32 priority, const Graph& graph) {
  const std::string esclabel = escape('"', escape('\\', graph[u]->label()));

  out << "  " << v << " -> " << u << " ["
      << "label=\"" << esclabel << "\", "
      << "taillabel=\"" << priority << "\"];\n";
}

void writeGraphviz(std::ostream& out, const Graph& graph) {
  out << "digraph G {\n  rankdir=LR;\n  ranksep=equally;\n  node [shape=\"circle\"];" << std::endl;

  for (uint32 i = 0; i < graph.numVertices(); ++i) {
    writeVertex(out, i, graph);
  }

  for (uint32 i = 0; i < graph.numVertices(); ++i) {
    for (uint32 j = 0; j < graph.outDegree(i); ++j) {
      writeEdge(out, i, graph.outVertex(i, j), j, graph);
    }
  }

  out << "}" << std::endl;
}
