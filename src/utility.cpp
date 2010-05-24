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
            TransitionPtr t(new LitState(b, keyIdx));
            t->IsMatch = true;
            (*g)[boost::add_edge(source, target, *g).first] = t;
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

// need a two-pass to get it to work with the bgl visitors
//  discover_vertex: determine slot
//  finish_vertex:   

ProgramPtr createProgram(const DynamicFSM& graph) {
  // std::cerr << "createProgram2" << std::endl;
  ProgramPtr ret(new std::vector<Instruction>());
  boost::shared_ptr<CodeGenHelper> cg(new CodeGenHelper(boost::num_vertices(graph)));
  CodeGenVisitor vis(cg);
  specialVisit(graph, 0ul, vis);
  
  ret->resize(cg->Guard);
  for (DynamicFSM::vertex_descriptor v = 0; v < boost::num_vertices(graph); ++v) {
    // std::cerr << "on vertex " << v << " at " << cg->Snippets[v].first << std::endl;
    Instruction* curOp = &(*ret)[cg->Snippets[v].Start];
    InEdgeRange inRange(in_edges(v, graph));
    if (inRange.first != inRange.second) {
      TransitionPtr t(graph[*inRange.first]); // this assumes that all states have the same incoming transitions
      Instruction i;
      t->toInstruction(&i);
      *curOp++ = i;
      // std::cerr << "wrote " << i << std::endl;
      if (t->Label < 0xffffffff) {
        *curOp++ = Instruction::makeMatch(t->Label); // also problematic
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

boost::shared_ptr<Vm> initVM(const std::vector<std::string>& keywords, SearchInfo&) {
  boost::shared_ptr<Vm> vm(new Vm);
  DynamicFSMPtr fsm = createDynamicFSM(keywords);
  ProgramPtr prog = createProgram(*fsm);
  vm->init(prog, firstBytes(*fsm), 1);
  return vm;
}

std::vector< std::set< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph) {
  std::vector< std::set< DynamicFSM::vertex_descriptor > > ret(256);
  OutEdgeRange outRange(boost::out_edges(source, graph));
  ByteSet permitted;
  for (OutEdgeIt outIt(outRange.first); outIt != outRange.second; ++outIt) {
    permitted.reset();
    graph[*outIt]->getBits(permitted);
    DynamicFSM::vertex_descriptor t = boost::target(*outIt, graph);
    for (uint32 i = 0; i < 256; ++i) {
      if (permitted[i]) {
        ret[i].insert(t);
      }
    }
  }
  return ret;
}
