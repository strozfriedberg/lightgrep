#include "utility_impl.h"

#include "states.h"

#include <deque>

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords) {
  DynamicFSMPtr g(new DynamicFSM(1));
  uint32 keyIdx = 0;
  ByteSet charBits,
          edgeBits;
  for (std::vector<std::string>::const_iterator kw(keywords.begin()); kw != keywords.end(); ++kw) {
    if (!kw->empty()) {
      DynamicFSM::vertex_descriptor source = 0;
      for (uint32 i = 0; i < kw->size(); ++i) {
        byte b = (*kw)[i];
        charBits.reset();
        charBits.set(b);
        std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> edgeRange(boost::out_edges(source, *g));
        DynamicFSM::vertex_descriptor target;
        bool found = false;
        for (DynamicFSM::out_edge_iterator edgeIt(edgeRange.first); edgeIt != edgeRange.second; ++edgeIt) {
          edgeBits.reset();
          Transition& trans(*(*g)[*edgeIt]);
          trans.getBits(edgeBits);
          if (charBits == edgeBits && (trans.Label == 0xffffffff || trans.Label == keyIdx)) {
            target = boost::target(*edgeIt, *g);
            found = true;
            break;
          }
        }
        if (!found) {
          target = boost::add_vertex(*g);
          if (i == kw->size() - 1) {
            (*g)[boost::add_edge(source, target, *g).first].reset(new LitState(b, keyIdx));
          }
          else {
            (*g)[boost::add_edge(source, target, *g).first].reset(new LitState(b));
          }
        }
        source = target;
      }
      ++keyIdx;
    }
  }
  return g;
}

boost::shared_ptr< std::vector<Instruction> > createProgram(const DynamicFSM& graph) {
  boost::shared_ptr< std::vector<Instruction> > ret(new std::vector<Instruction>());
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(graph)));
  CodeGenVisitor vis(cg);
  boost::breadth_first_search(graph, 0, visitor(vis));
  ret->swap(cg->Program);
  return ret;
}

// need a two-pass to get it to work with the bgl visitors
//  discover_vertex: determine slot
//  finish_vertex:   

ProgramPtr createProgram2(const DynamicFSM& graph) {
  // std::cerr << "createProgram2" << std::endl;
  ProgramPtr ret(new std::vector<Instruction>());
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(graph)));
  CodeGenVisitor2 vis(cg);
  specialVisit(graph, 0ul, vis);
  
  ret->resize(cg->Guard);
  for (DynamicFSM::vertex_descriptor v = 0; v < boost::num_vertices(graph); ++v) {
    // std::cerr << "on vertex " << v << " at " << cg->Snippets[v].first << std::endl;
    Instruction* curOp = &(*ret)[cg->Snippets[v].first];
    InEdgeRange inRange(in_edges(v, graph));
    if (inRange.first != inRange.second) {
      TransitionPtr t(graph[*inRange.first]); // this assumes that all states have the same incoming transitions
      Instruction i;
      t->toInstruction(&i);
      *curOp++ = i;
      // std::cerr << "wrote " << i << std::endl;
      if (t->Label < 0xffffffff) {
        *curOp++ = Instruction::makeSaveLabel(t->Label); // also problematic
        // std::cerr << "wrote " << Instruction::makeSaveLabel(t->Label) << std::endl;
      }
    }
    OutEdgeRange outRange(out_edges(v, graph));
    if (outRange.first != outRange.second) {
      bool hasTargetAtNext = false;
      for (DynamicFSM::out_edge_iterator cur(outRange.first); cur != outRange.second; ++cur) {
        DynamicFSM::vertex_descriptor curTarget = boost::target(*cur, graph);
        // std::cerr << "targeting " << curTarget << " at " << cg->Snippets[curTarget].first << std::endl;
        if (cg->DiscoverRanks[v] + 1 != cg->DiscoverRanks[curTarget]) {
          DynamicFSM::out_edge_iterator next(cur);
          ++next;
          if (next == outRange.second && !hasTargetAtNext) {
            *curOp++ = Instruction::makeJump(cg->Snippets[curTarget].first);
            // std::cerr << "wrote " << Instruction::makeJump(cg->Snippets[curTarget].first) << std::endl;
          }
          else {
            *curOp++ = Instruction::makeFork(cg->Snippets[curTarget].first);
            // std::cerr << "wrote " << Instruction::makeFork(cg->Snippets[curTarget].first) << std::endl;
          }
        }
        else {
          hasTargetAtNext = true;
          // std::cerr << "skipping because it's next" << std::endl;
        }
      }
    }
    else {
      *curOp++ = Instruction::makeMatch();
      // std::cerr << "wrote " << Instruction::makeMatch() << std::endl;
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
    graph[*curEdge]->getBits(tBits);
    ret |= tBits;
  }
  return ret;
}
