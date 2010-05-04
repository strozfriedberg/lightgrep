#include "utility_impl.h"

#include "states.h"

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords) {
  DynamicFSMPtr g(new DynamicFSM(1));
  uint32 keyIdx = 0;
  for (std::vector<std::string>::const_iterator kw(keywords.begin()); kw != keywords.end(); ++kw) {
    if (!kw->empty()) {
      DynamicFSM::vertex_descriptor source = 0;
      for (uint32 i = 0; i < kw->size(); ++i) {
        DynamicFSM::vertex_descriptor target = boost::add_vertex(*g);
        if (i == kw->size() - 1) {
          (*g)[boost::add_edge(source, target, *g).first].reset(new LitState((*kw)[i], keyIdx));
        }
        else {
          (*g)[boost::add_edge(source, target, *g).first].reset(new LitState((*kw)[i]));
        }
        source = target;
      }
      ++keyIdx;
    }
  }
  return g;
}

boost::shared_ptr<StaticFSM> convert_to_static(const DynamicFSM& graph) {
  boost::shared_ptr<StaticFSM> ret(new StaticFSM());
  std::pair<EdgeIt, EdgeIt> edges = boost::edges(graph);
  uint32 tSize = 0;
  for (EdgeIt cur = edges.first; cur != edges.second; ++cur) {
    tSize += graph[*cur]->objSize();
  }
  uint32 bufSize = ret->allocate(tSize, num_vertices(graph), num_edges(graph));
  if (bufSize > 0) {
    boost::shared_ptr<LayoutHelper> helper(new LayoutHelper(num_vertices(graph), ret->getRawBuffer()));
    LayoutVisitor vis(helper);
    // std::cout << " *** starting ***" << std::endl;
    boost::breadth_first_search(graph, 0, visitor(vis));
    // std::cout << " *** finishing ***" << std::endl;
    ret->setLastState(helper->LastState);
  }
  return ret;
}

uint32 staticStateSize(DynamicFSM::vertex_descriptor state, const DynamicFSM& graph) {
  uint32 numEdges = 0,
         tSize = 0;
  std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> adj(boost::out_edges(state, graph));
  for (DynamicFSM::out_edge_iterator cur = adj.first; cur != adj.second; ++cur) {
    ++numEdges;
    tSize += graph[*cur]->objSize();
  }
  return sizeof(uint32) + (boost::out_degree(state, graph) * sizeof(StaticEdge)) + tSize;
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
