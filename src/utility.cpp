#include "utility_impl.h"

#include "states.h"

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
