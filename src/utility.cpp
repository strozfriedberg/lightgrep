#include "utility.h"

#include <vector>
#include <iostream>

static const uint32 UNALLOCATED = 0xffffffff;

boost::shared_ptr<StaticFSM> convert_to_static(const DynamicFSM& graph) {
  boost::shared_ptr<StaticFSM> ret(new StaticFSM());
  std::pair<EdgeIt, EdgeIt> edges = boost::edges(graph);
  uint32 tSize = 0;
  for (EdgeIt cur = edges.first; cur != edges.second; ++cur) {
    tSize += graph[*cur]->objSize();
  }
  uint32 bufSize = ret->allocate(tSize, num_vertices(graph), num_edges(graph));
  if (bufSize > 0) {
    std::vector<uint32> stateOffsets(num_vertices(graph), UNALLOCATED);

    stateOffsets[0] = 0;
    uint32 numEdges = out_degree(0, graph);
    
    byte* buffer = ret->getRawBuffer();
    *((uint32*)buffer) = numEdges;
    // std::cout << "numEdges = " << numEdges << std::endl;

    StaticEdge* curEdge = reinterpret_cast<StaticEdge*>(buffer + sizeof(uint32));
    std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> adj(boost::out_edges(0u, graph));
    byte* tranGuard = buffer + sizeof(uint32) + (sizeof(StaticEdge) * numEdges);
    
    // std::cout << "buffer = " << (uint64)buffer << "; bufSize = " << bufSize << "; tranGuard = " << (uint64)tranGuard << std::endl;

    uint32 i = 0;
    for (DynamicFSM::out_edge_iterator cur = adj.first; cur != adj.second; ++cur) {
      curEdge->TransitionOffset = tranGuard - buffer;
      // std::cout << i++ << ": TransitionOffset = " << curEdge->TransitionOffset << std::endl;
      tranGuard += graph[*cur]->clone(tranGuard)->objSize();
    }
    i = 0;
    for (DynamicFSM::out_edge_iterator cur = adj.first; cur != adj.second; ++cur) {
      DynamicFSM::vertex_descriptor nextState = boost::target(*cur, graph);
      if (stateOffsets[nextState] == UNALLOCATED) {
        stateOffsets[nextState] = tranGuard - buffer;
      }
      curEdge->StateOffset = stateOffsets[nextState];
      // std::cout << i++ << ": StateOffset = " << curEdge->StateOffset << std::endl;
    }
    // std::cout << "buffer = " << (uint64)buffer << "; bufSize = " << bufSize << "; tranGuard = " << (uint64)tranGuard << std::endl;
  }
  return ret;
}
