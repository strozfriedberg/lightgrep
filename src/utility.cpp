#include "utility_impl.h"

#include "states.h"

#include "parser.h"
#include "concrete_encodings.h"
#include "compiler.h"

#include <algorithm>
#include <queue>

#include <boost/bind.hpp>
#include <boost/graph/graphviz.hpp>

void addNewEdge(DynamicFSM::vertex_descriptor source, DynamicFSM::vertex_descriptor target, DynamicFSM& fsm) {
  fsm.addEdge(source, target);
}

void addKeys(const std::vector<std::string>& keywords, boost::shared_ptr<Encoding> enc, bool caseSensitive, bool litMode, DynamicFSMPtr& fsm, uint32& keyIdx) {
  SyntaxTree  tree;
  Compiler    comp;
  Parser      p;
  p.setEncoding(enc);
  for (uint32 i = 0; i < keywords.size(); ++i) {
    const std::string& kw(keywords[i]);
    if (!kw.empty()) {
      try {
        p.setCurLabel(keyIdx);
        p.setCaseSensitive(caseSensitive); // do this before each keyword since parsing may change it
        if (parse(kw, litMode, tree, p) && p.good()) {
          if (fsm) {
            comp.mergeIntoFSM(*fsm, *p.getFsm(), keyIdx);
          }
          else {
            fsm = p.getFsm();
            p.resetFsm();
          }
          ++keyIdx;
        }
        else {
          std::cerr << "Could not parse keyword number " << i << ", " << kw << std::endl;
        }
        tree.reset();
        p.reset();
      }
      catch (std::exception& e) {
        std::cerr << "Exception on keyword " << i << ": " << e.what() << std::endl;
        std::cerr << "Currently " << fsm->numVertices() << " vertices" << std::endl;
        throw;
      }
      if (i && i % 10000 == 0) {
        std::cerr << "Parsed " << i << " keywords" << std::endl;
      }
    }
  }
  std::cerr << "Parsed " << keywords.size() << " keywords, beginning labeling" << std::endl;
  comp.labelGuardStates(*fsm);
}

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords, uint32 enc, bool caseSensitive, bool litMode) {
  // std::cerr << "createDynamicFSM" << std::endl;
  DynamicFSMPtr ret;
  uint32 keyIdx = 0;
  if (enc & CP_ASCII) {
    addKeys(keywords, boost::shared_ptr<Encoding>(new Ascii), caseSensitive, litMode, ret, keyIdx);
  }
  if (enc & CP_UCS16) {
    addKeys(keywords, boost::shared_ptr<Encoding>(new UCS16), caseSensitive, litMode, ret, keyIdx);
  }
  return ret;
}

DynamicFSMPtr createDynamicFSM(KwInfo& keyInfo, uint32 enc, bool caseSensitive, bool litMode) {
  DynamicFSMPtr ret;
  uint32 keyIdx = 0;
  if (enc & CP_ASCII) {
    keyInfo.Encodings.push_back("ASCII");
    uint32 encIdx = keyInfo.Encodings.size() - 1;
    addKeys(keyInfo.Keywords, boost::shared_ptr<Encoding>(new Ascii), caseSensitive, litMode, ret, keyIdx);
    for (uint32 i = 0; i < keyInfo.Keywords.size(); ++i) {
      keyInfo.PatternsTable.push_back(std::make_pair<uint32,uint32>(i, encIdx));
    }
  }
  if (enc & CP_UCS16) {
    keyInfo.Encodings.push_back("UCS-16");
    uint32 encIdx = keyInfo.Encodings.size() - 1;
    addKeys(keyInfo.Keywords, boost::shared_ptr<Encoding>(new UCS16), caseSensitive, litMode, ret, keyIdx);
    for (uint32 i = 0; i < keyInfo.Keywords.size(); ++i) {
      keyInfo.PatternsTable.push_back(std::make_pair<uint32,uint32>(i, encIdx));
    }
  }
  return ret;
}

// If the jump is to a state that has only a single out edge, and there's no match on the state, then jump forward directly to the out-edge state
uint32 figureOutLanding(boost::shared_ptr<CodeGenHelper> cg, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
  if (1 == graph.outDegree(v) && UNALLOCATED == graph[v]->Label) {
    return cg->Snippets[*graph.outVerticesBegin(v)].Start;
  }
  else {
    return cg->Snippets[v].Start + cg->Snippets[v].NumEval;
  }
}

// JumpTables are either ranged, or full-size, and can have indirect tables at the end when there are multiple transitions out on a single byte value
void createJumpTable(boost::shared_ptr<CodeGenHelper> cg, Instruction* base, uint32 baseIndex, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
  Instruction* cur = base,
             * indirectTbl;

  std::vector< std::vector< DynamicFSM::vertex_descriptor > > tbl(pivotStates(v, graph));
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
    indirectTbl = base + 2 + (last - first);
  }
  else {
    *cur++ = Instruction::makeJumpTable();
    indirectTbl = base + 257;
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
      const uint32 addr = baseIndex + (indirectTbl - base);
      *cur++ = *reinterpret_cast<const Instruction*>(&addr);
      for (uint32 j = 0; j < tbl[i].size(); ++j) {
        uint32 landing = figureOutLanding(cg, tbl[i][j], graph);

        *indirectTbl = (j + 1 == tbl[i].size() ?
          Instruction::makeLongJump(indirectTbl+1, landing) :
          Instruction::makeLongFork(indirectTbl+1, landing));
        indirectTbl += 2;
/*
        *indirectTbl++ = (j + 1 == tbl[i].size() ?
          Instruction::makeJump(landing) : Instruction::makeFork(landing));
*/
      }
    }
  }
  if (indirectTbl - base != cg->Snippets[v].NumOther) {
    std::cerr << "whoa, big trouble in Little China on " << v << "... NumOther == " << cg->Snippets[v].NumOther << ", but diff is " << (indirectTbl - base) << std::endl;
  }
}

// need a two-pass to get it to work with the bgl visitors
//  discover_vertex: determine slot
//  finish_vertex:   
ProgramPtr createProgram(const DynamicFSM& graph) {
  std::cerr << "Compiling to byte code" << std::endl;
  ProgramPtr ret(new Program);
  uint32 numVs = graph.numVertices();
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(numVs));
  CodeGenVisitor vis(cg);
  specialVisit(graph, 0ul, vis);
  std:: cerr << "Determined order in first pass" << std::endl;
  ret->NumChecked = cg->NumChecked;
  ret->resize(cg->Guard);
  uint32 i = 0;
  for (DynamicFSM::vertex_descriptor v = 0; v < numVs; ++v) {
    if (++i % 10000 == 0) {
      std::cerr << "have compiled " << i << " states so far" << std::endl;
    }
    Instruction* curOp = &(*ret)[cg->Snippets[v].Start];
    if (cg->Snippets[v].CheckIndex != UNALLOCATED) {
      *curOp++ = Instruction::makeCheckHalt(cg->Snippets[v].CheckIndex);
    }
    TransitionPtr t(graph[v]);
    if (t) {
      t->toInstruction(curOp);
      curOp += t->numInstructions();
      // std::cerr << "wrote " << i << std::endl;
      if (t->Label < 0xffffffff) {
        *curOp++ = Instruction::makeLabel(t->Label); // also problematic
        // std::cerr << "wrote " << Instruction::makeSaveLabel(t->Label) << std::endl;
      }
      if (t->IsMatch) {
        *curOp++ = Instruction::makeMatch();
      }
    }
    if (JUMP_TABLE_RANGE_OP == cg->Snippets[v].Op || JUMP_TABLE_OP == cg->Snippets[v].Op) {
      createJumpTable(cg, curOp, curOp - &(*ret)[0], v, graph);
      continue;
    }
    DynamicFSM::const_iterator ov(graph.outVerticesBegin(v)),
                               ov_end(graph.outVerticesEnd(v));
    if (ov != ov_end) {
      bool hasTargetAtNext = false;
      DynamicFSM::vertex_descriptor nextTarget = 0;
      for (; ov != ov_end; ++ov) {
        DynamicFSM::vertex_descriptor curTarget = *ov;
        // std::cerr << "targeting " << curTarget << " at " << cg->Snippets[curTarget].first << std::endl;
        if (cg->DiscoverRanks[v] + 1 != cg->DiscoverRanks[curTarget]) {




          DynamicFSM::const_iterator nextov(ov);
          nextov.Base.reset(ov.Base->clone());
          ++nextov;




          if (nextov == ov_end && !hasTargetAtNext) {
            *curOp = Instruction::makeLongJump(curOp+1, cg->Snippets[curTarget].Start);
            // std::cerr << "wrote " << Instruction::makeJump(cg->Snippets[curTarget].first) << std::endl;
          }
          else {
            *curOp = Instruction::makeLongFork(curOp+1, cg->Snippets[curTarget].Start);
            // std::cerr << "wrote " << Instruction::makeFork(cg->Snippets[curTarget].first) << std::endl;
          }
          curOp += 2;
        }
        else {
          hasTargetAtNext = true;
          nextTarget = curTarget;
          // std::cerr << "skipping because it's next" << std::endl;
        }
      }
    }
    else {
      *curOp++ = Instruction::makeHalt();
      // std::cerr << "wrote " << Instruction::makeHalt() << std::endl;
    }
  }
  return ret;
}

class SkipTblVisitor: public Visitor {
public:
  SkipTblVisitor(boost::shared_ptr<SkipTable> skip): Skipper(skip) {}
  
  void discoverVertex(DynamicFSM::vertex_descriptor v,
                      const DynamicFSM& graph) const {
    Skipper->calculateTransitions(v, graph);
  }
 
  void treeEdge(DynamicFSM::vertex_descriptor h,
                DynamicFSM::vertex_descriptor t,
                const DynamicFSM& graph) const {
    Skipper->setDistance(h, t, graph);
  }

private:
  boost::shared_ptr<SkipTable> Skipper;
};

uint32 calculateLMin(const DynamicFSM& graph) {
  return calculateSkipTable(graph)->l_min();
}

boost::shared_ptr<SkipTable> calculateSkipTable(const DynamicFSM& graph) {
  std::cerr << "calculating skiptable and l-min" << std::endl;
  boost::shared_ptr<SkipTable> skip(new SkipTable(graph.numVertices()));
  SkipTblVisitor vis(skip);
  bfs(graph, 0, vis);
  skip->finishSkipVec();
  return skip;
}

void bfs(const DynamicFSM& graph, DynamicFSM::vertex_descriptor start, Visitor& visitor) {
  std::vector<bool> seen(graph.numVertices());
  std::queue<DynamicFSM::vertex_descriptor> next;

  visitor.discoverVertex(start, graph);
  next.push(start);
  seen[start] = true;
  
  while (!next.empty()) {
    DynamicFSM::vertex_descriptor h = next.front();
    next.pop();
  
    DynamicFSM::const_iterator ov(graph.outVerticesBegin(h)),
                               ov_end(graph.outVerticesEnd(h));
    for ( ; ov != ov_end; ++ov) {
      DynamicFSM::vertex_descriptor t = *ov;
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

void nextBytes(ByteSet& set, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
  ByteSet tBits;
  DynamicFSM::const_iterator ov(graph.outVerticesBegin(v)),
                             ov_end(graph.outVerticesEnd(v));
  for ( ; ov != ov_end; ++ov) {
    tBits.reset();
    graph[*ov]->getBits(tBits);
    set |= tBits;
  }
}

ByteSet firstBytes(const DynamicFSM& graph) {
  ByteSet ret;
  ret.reset();
  nextBytes(ret, 0, graph);
  return ret;
}

boost::shared_ptr<VmInterface> initVM(const std::vector<std::string>& keywords, SearchInfo&) {
  boost::shared_ptr<VmInterface> vm = VmInterface::create();
  DynamicFSMPtr fsm = createDynamicFSM(keywords);
  ProgramPtr prog = createProgram(*fsm);
  prog->Skip = calculateSkipTable(*fsm);
  prog->First = firstBytes(*fsm);
  vm->init(prog);
  return vm;
}

std::vector< std::vector< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph) {
  std::vector< std::vector< DynamicFSM::vertex_descriptor > > ret(256);  
  ByteSet permitted;
  DynamicFSM::const_iterator ov(graph.outVerticesBegin(source)),
                             ov_end(graph.outVerticesEnd(source));
  for ( ; ov != ov_end; ++ov) {
    permitted.reset();
    graph[*ov]->getBits(permitted);
    for (uint32 i = 0; i < 256; ++i) {
      if (permitted[i] && std::find(ret[i].begin(), ret[i].end(), *ov) == ret[i].end()) {
        ret[i].push_back(*ov);
      }
    }
  }
  return ret;
}

uint32 maxOutbound(const std::vector< std::vector< DynamicFSM::vertex_descriptor > >& tranTable) {
  uint32 ret = 0;
  for (std::vector< std::vector< DynamicFSM::vertex_descriptor > >::const_iterator it(tranTable.begin()); it != tranTable.end(); ++it) {
    ret = it->size() > ret ? it->size(): ret;
  }
  return ret;
}

void writeVertex(std::ostream& out, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
  std::string l;

  if (v != 0) {
    l = graph[v]->label();
  }

  if (!graph[v]) { // initial state
    out << "[label=\"" << (l.empty() ? "Start": l) << "\", style=\"filled\", fillcolor=\"green1\"]";
  }
  else if (graph[v]->IsMatch) { // match state
    out << "[label=\"" << l << "\", style=\"filled\", fillcolor=\"tomato\", shape=\"doublecircle\"]";
  }
  else if (graph[v]->Label < 0xffffffff) { // guard state
    out << "[label=\"" << l << "\", shape=\"doublecircle\"]";
  }
  else { // all other states
    out << "[label=\"" << l << "\"]";
  }
}

void writeGraphviz(std::ostream& out, const DynamicFSM& graph) {
  out << "digraph G {\nrankdir=LR;\nranksep=equally;" << std::endl;
  for (uint32 i = 0; i < graph.numVertices(); ++i) {
    out << i;
    writeVertex(out, i, graph);
    out << ";" << std::endl;
  }
  for (uint32 i = 0; i < graph.numVertices(); ++i) {
    DynamicFSM::const_iterator ov(graph.outVerticesBegin(i)),
                               ov_end(graph.outVerticesEnd(i));
    for ( ; ov != ov_end; ++ov) {
      out << i << "->" << *ov << " ";
      out << ";" << std::endl;
    }
  }
  out << "}" << std::endl;
}
