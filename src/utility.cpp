#include "utility_impl.h"

#include "states.h"

#include "parser.h"

#include <deque>
#include <stack>
#include <algorithm>

#include <boost/bind.hpp>
#include <boost/graph/graphviz.hpp>

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords) {
  // std::cerr << "createDynamicFSM" << std::endl;
  DynamicFSMPtr ret;
  uint32 keyIdx = 0;
  for (uint32 i = 0; i < keywords.size(); ++i) {
    std::string kw = keywords[i];
    if (!kw.empty()) {
      Parser      p;
      SyntaxTree  tree;
      p.setCurLabel(keyIdx);
      if (parse(kw, tree, boost::bind(&Parser::callback, &p, _1, _2))) {
        if (ret) {
          mergeIntoFSM(*ret, *p.getFsm(), keyIdx);
        }
        else {
          ret = p.getFsm();
        }
        ++keyIdx;
      }
      else {
        std::cerr << "Could not parse " << kw << std::endl;
      }
    }
  }
  return ret;
}

  // DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords) {
  // DynamicFSMPtr g(new DynamicFSM(1));
  // uint32 keyIdx = 0;
  // ByteSet charBits,
  //         edgeBits;
  // for (std::vector<std::string>::const_iterator kw(keywords.begin()); kw != keywords.end(); ++kw) {
  //   if (!kw->empty()) {
  //     DynamicFSM::vertex_descriptor source = 0;
  //     for (uint32 i = 0; i < kw->size(); ++i) {
  //       byte b = (*kw)[i];
  //       charBits.reset();
  //       charBits.set(b);
  //       std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> edgeRange(boost::out_edges(source, *g));
  //       DynamicFSM::vertex_descriptor target;
  //       bool found = false;
  //       for (DynamicFSM::out_edge_iterator edgeIt(edgeRange.first); edgeIt != edgeRange.second; ++edgeIt) {
  //         edgeBits.reset();
  //         Transition& trans(*(*g)[boost::target(*edgeIt, *g)]);
  //         trans.getBits(edgeBits);
  //         if (charBits == edgeBits && (trans.Label == 0xffffffff || trans.Label == keyIdx)) {
  //           target = boost::target(*edgeIt, *g);
  //           found = true;
  //           break;
  //         }
  //       }
  //       if (!found) {
  //         target = boost::add_vertex(*g);
  //         if (i == kw->size() - 1) {
  //           TransitionPtr t(new LitState(b, keyIdx));
  //           t->IsMatch = true;
  //           boost::add_edge(source, target, *g);
  //           (*g)[target] = t;
  //         }
  //         else {
  //           boost::add_edge(source, target, *g);
  //           (*g)[target].reset(new LitState(b));
  //         }
  //       }
  //       source = target;
  //     }
  //     ++keyIdx;
  //   }
  // }
  // return g;
  // }

// need a two-pass to get it to work with the bgl visitors
//  discover_vertex: determine slot
//  finish_vertex:   

void createJumpTable(boost::shared_ptr<CodeGenHelper> cg, Instruction* base, uint32 baseIndex, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
  Instruction* cur = base,
             * indirectTbl = base + 257;
  *cur++ = Instruction::makeJumpTable();
  std::vector< std::vector< DynamicFSM::vertex_descriptor > > tbl(pivotStates(v, graph));
  for (uint32 i = 0; i < 256; ++i) {
    if (tbl[i].empty()) {
      *cur++ = Instruction::makeHalt();
    }
    else if (1 == tbl[i].size()) {
      StateLayoutInfo info = cg->Snippets[*tbl[i].begin()];
      *cur++ = Instruction::makeJump(info.Start + info.NumEval);
    }
    else {
      *cur++ = Instruction::makeJump(baseIndex + (indirectTbl - base));
      for (uint32 j = 0; j < tbl[i].size(); ++j) {
        StateLayoutInfo info = cg->Snippets[tbl[i][j]];
        *indirectTbl++ = (j + 1 == tbl[i].size() ? Instruction::makeJump(info.Start + info.NumEval): Instruction::makeFork(info.Start + info.NumEval));
      }
    }
  }
  if (indirectTbl - base != cg->Snippets[v].NumOther) {
    std::cerr << "whoa, big trouble in Little China on " << v << "... NumOther == " << cg->Snippets[v].NumOther << ", but diff is " << (indirectTbl - base) << std::endl;
  }
}

ProgramPtr createProgram(const DynamicFSM& graph) {
  // std::cerr << "createProgram2" << std::endl;
  ProgramPtr ret(new Program);
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(graph)));
  CodeGenVisitor vis(cg);
  specialVisit(graph, 0ul, vis);
  ret->NumChecked = cg->NumChecked;
  ret->resize(cg->Guard);
  for (DynamicFSM::vertex_descriptor v = 0; v < boost::num_vertices(graph); ++v) {
    // std::cerr << "on vertex " << v << " at " << cg->Snippets[v].first << std::endl;
    Instruction* curOp = &(*ret)[cg->Snippets[v].Start];
    TransitionPtr t(graph[v]);
    if (t) {
      t->toInstruction(curOp);
      curOp += t->numInstructions();
      // std::cerr << "wrote " << i << std::endl;
      if (t->Label < 0xffffffff) {
        *curOp++ = Instruction::makeMatch(t->Label); // also problematic
        // std::cerr << "wrote " << Instruction::makeSaveLabel(t->Label) << std::endl;
      }
    }
    if (cg->Snippets[v].numTotal() > 256) {
      createJumpTable(cg, curOp, curOp - &(*ret)[0], v, graph);
      continue;
    }
    OutEdgeRange outRange(out_edges(v, graph));
    if (outRange.first != outRange.second) {
      bool hasTargetAtNext = false;
      DynamicFSM::vertex_descriptor nextTarget = 0;
      for (DynamicFSM::out_edge_iterator cur(outRange.first); cur != outRange.second; ++cur) {
        DynamicFSM::vertex_descriptor curTarget = boost::target(*cur, graph);
        // std::cerr << "targeting " << curTarget << " at " << cg->Snippets[curTarget].first << std::endl;
        if (cg->DiscoverRanks[v] + 1 != cg->DiscoverRanks[curTarget]) {
          DynamicFSM::out_edge_iterator next(cur);
          ++next;
          if (cg->Snippets[curTarget].CheckIndex != UNALLOCATED) {
            if (next == outRange.second && !hasTargetAtNext) {
              *curOp++ = Instruction::makeCheckHalt(cg->Snippets[curTarget].CheckIndex);
            }
            else {
              *curOp++ = Instruction::makeCheckBranch(cg->Snippets[curTarget].CheckIndex);
            }
          }
          if (next == outRange.second && !hasTargetAtNext) {
            *curOp++ = Instruction::makeJump(cg->Snippets[curTarget].Start);
            // std::cerr << "wrote " << Instruction::makeJump(cg->Snippets[curTarget].first) << std::endl;
          }
          else {
            *curOp++ = Instruction::makeFork(cg->Snippets[curTarget].Start);
            // std::cerr << "wrote " << Instruction::makeFork(cg->Snippets[curTarget].first) << std::endl;
          }
        }
        else {
          hasTargetAtNext = true;
          nextTarget = curTarget;
          // std::cerr << "skipping because it's next" << std::endl;
        }
      }
      if (hasTargetAtNext && cg->Snippets[nextTarget].CheckIndex != UNALLOCATED) {
        *curOp++ = Instruction::makeCheckHalt(cg->Snippets[nextTarget].CheckIndex);
      }
    }
    else {
      *curOp++ = Instruction::makeHalt();
      // std::cerr << "wrote " << Instruction::makeHalt() << std::endl;
    }
  }
  return ret;
}

ByteSet firstBytes(const DynamicFSM& graph) {
  std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> edgeRange(boost::out_edges(0, graph));
  ByteSet ret,
          tBits;
  for (DynamicFSM::out_edge_iterator curEdge(edgeRange.first); curEdge != edgeRange.second; ++curEdge) {
    tBits.reset();
    graph[boost::target(*curEdge, graph)]->getBits(tBits);
    ret |= tBits;
  }
  return ret;
}

boost::shared_ptr<Vm> initVM(const std::vector<std::string>& keywords, SearchInfo&) {
  boost::shared_ptr<Vm> vm(new Vm);
  DynamicFSMPtr fsm = createDynamicFSM(keywords);
  ProgramPtr prog = createProgram(*fsm);
  vm->init(prog, firstBytes(*fsm), 1);
  return vm;
}

std::vector< std::vector< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph) {
  std::vector< std::vector< DynamicFSM::vertex_descriptor > > ret(256);
  OutEdgeRange outRange(boost::out_edges(source, graph));
  ByteSet permitted;
  for (OutEdgeIt outIt(outRange.first); outIt != outRange.second; ++outIt) {
    permitted.reset();
    DynamicFSM::vertex_descriptor t = boost::target(*outIt, graph);
    graph[t]->getBits(permitted);
    for (uint32 i = 0; i < 256; ++i) {
      if (permitted[i] && std::find(ret[i].begin(), ret[i].end(), t) == ret[i].end()) {
        ret[i].push_back(t);
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

void mergeIntoFSM(DynamicFSM& fsm, const DynamicFSM& addend, uint32 keyIdx) {
  typedef std::pair< DynamicFSM::vertex_descriptor, DynamicFSM::vertex_descriptor > StatePair;

  ByteSet tranBits,
          edgeBits;

  std::vector< DynamicFSM:: vertex_descriptor > stateMap(boost::num_vertices(addend), UNALLOCATED);

  std::vector< bool >           visited(boost::num_vertices(addend), false);
  DynamicFSM::vertex_descriptor oldSource,
                                source,
                                oldTarget,
                                target;

  std::stack< StatePair > states;
  states.push(StatePair(0, 0));
  while (!states.empty()) {
    oldSource = states.top().first;
    source    = states.top().second;
    states.pop();
    if (!visited[oldSource]) {
      // std::cerr << "on state pair " << oldSource << ", " << source << std::endl;
      visited[oldSource] = true;

      OutEdgeRange  outRange(boost::out_edges(source, fsm)),
                    oldOutRange(boost::out_edges(oldSource, addend));
      for (OutEdgeIt e(oldOutRange.first); e != oldOutRange.second; ++e) {
        oldTarget = boost::target(*e, addend);
        if (stateMap[oldTarget] == UNALLOCATED) {
          TransitionPtr tran = addend[oldTarget];
          tranBits.reset();
          tran->getBits(tranBits);
          // std::cerr << "oldTarget = " << oldTarget << " with transition " << tran->label() << std::endl;

          bool found = false;

          for (OutEdgeIt curEdge(outRange.first); curEdge != outRange.second; ++curEdge) {
            target = boost::target(*curEdge, fsm);
            TransitionPtr edgeTran = fsm[target];
            edgeBits.reset();
            edgeTran->getBits(edgeBits);
            // std::cerr << "looking at merge state " << target << " with transition " << edgeTran->label() << std::endl;
            if (edgeBits == tranBits && (edgeTran->Label == UNALLOCATED || edgeTran->Label == keyIdx) && 1 == boost::in_degree(target, fsm) && 2 > boost::in_degree(oldSource, addend) && 2 > boost::in_degree(oldTarget, addend)) {
              // std::cerr << "found equivalent state " << target << std::endl;
              found = true;
              break;
            }
          }
          if (!found) {
            target = boost::add_vertex(fsm);
            // std::cerr << "creating new state " << target << std::endl;
            fsm[target] = tran;
          }
          stateMap[oldTarget] = target;
        }
        else {
          target = stateMap[oldTarget];
        }
        // std::cerr << "target = " << target << std::endl;
        boost::add_edge(source, target, fsm);
        states.push(StatePair(oldTarget, target));
      }
    }
  }
}

void writeVertex(std::ostream& out, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
  std::string l;
  if (v != 0) {
    l = graph[v]->label();
  }
  if (boost::in_degree(v, graph) == 0) {
    out << "[label=\"" << l << "\", style=\"filled\", fillcolor=\"lightgreen\"]";
  }
  else if (boost::out_degree(v, graph) == 0) {
    out << "[label=\"" << l << "\", style=\"filled\", fillcolor=\"tomato\", shape=\"doublecircle\"]";
  }
  else if (graph[v]->Label < 0xffffffff) {
    out << "[label=\"" << l << "\", shape=\"doublecircle\"]";
  }
  else {
    out << "[label=\"" << l << "\"]";
  }
}

void writeGraphviz(std::ostream& out, const DynamicFSM& graph) {
  out << "digraph G {" << std::endl;
  for (uint32 i = 0; i < boost::num_vertices(graph); ++i) {
    out << i;
    writeVertex(out, i, graph);
    out << ";" << std::endl;
  }
  for (uint32 i = 0; i < boost::num_vertices(graph); ++i) {
    OutEdgeRange outRange(boost::out_edges(i, graph));
    for (OutEdgeIt it(outRange.first); it != outRange.second; ++it) {
      out << i << "->" << boost::target(*it, graph) << " ";
      out << ";" << std::endl;
    }
  }
  out << "}" << std::endl;
}
