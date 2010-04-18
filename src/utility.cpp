#include "utility.h"

#include <vector>
#include <iostream>
#include <cstring>

#include <boost/graph/breadth_first_search.hpp>

static const uint32 UNALLOCATED = 0xffffffff;

struct LayoutHelper {
  LayoutHelper(uint32 numStates, byte* buf): SizeVec(numStates), Offsets(numStates), Buffer(buf), Guard(buf) {}
  
  std::vector< uint32 > SizeVec,
                        Offsets;
  byte* Buffer,
      * Guard;
};

class LayoutVisitor: public boost::default_bfs_visitor {
public:
  LayoutVisitor(boost::shared_ptr<LayoutHelper> helper): Helper(helper) {}

  void initialize_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    // std::cout << "initialize_vertex: " << v << std::endl;
    Helper->SizeVec[v] = staticStateSize(v, graph);
    // std::cout << "size is " << Helper->SizeVec[v] << std::endl;
  }
  void discover_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    // std::cout << "discover_vertex: " << v << std::endl;
    *((uint32*)Helper->Guard) = out_degree(v, graph);
    size_t offset = Helper->Guard - Helper->Buffer;
    Helper->Offsets[v] = offset;
    // std::cout << "offset is " << offset << std::endl;
    std::memset(Helper->Guard + sizeof(uint32), UNALLOCATED, Helper->SizeVec[v] - sizeof(uint32));
    Helper->Guard += Helper->SizeVec[v];
  }

  void finish_vertex(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph) {
    // std::cout << "finish_vertex: " << v << std::endl;
    byte* statePtr = Helper->Buffer + Helper->Offsets[v];
    
    // uint32 numEdges = *((uint32*)statePtr);
    // std::cout << "numEdges = " << numEdges << std::endl;
    StaticEdge* curEdge = reinterpret_cast<StaticEdge*>(statePtr + sizeof(uint32));
    
    std::pair<DynamicFSM::out_edge_iterator, DynamicFSM::out_edge_iterator> adj(boost::out_edges(v, graph));
    byte* tranGuard = statePtr + sizeof(uint32) + (sizeof(StaticEdge) * (*((uint32*)statePtr)));
    
    for (DynamicFSM::out_edge_iterator cur = adj.first; cur != adj.second; ++cur) {
      // std::cout << "adding edge (" << boost::source(*cur, graph) << ", " << boost::target(*cur, graph) << ") at " << (uint64)curEdge << std::endl;
      if (curEdge->StateOffset != UNALLOCATED || curEdge->TransitionOffset != UNALLOCATED) {
        std::cerr << "uh oh..." << std::endl;
      }
      curEdge->StateOffset = Helper->Offsets[boost::target(*cur, graph)];
      curEdge->TransitionOffset = tranGuard - Helper->Buffer;
      // std::cout << "StateOffset = " << curEdge->StateOffset << "; TransitionOffset = " << curEdge->TransitionOffset << "; tranGuard = " << (uint64)tranGuard << std::endl;
      tranGuard += graph[*cur]->clone(tranGuard)->objSize();
    }
  }

private:
  boost::shared_ptr<LayoutHelper> Helper;
};

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

    LayoutVisitor vis(boost::shared_ptr<LayoutHelper>(new LayoutHelper(num_vertices(graph), ret->getRawBuffer())));
    // std::cout << " *** starting ***" << std::endl;
    boost::breadth_first_search(graph, 0, visitor(vis));
    // std::cout << " *** finishing ***" << std::endl;
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
