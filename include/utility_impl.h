#pragma once

#include "utility.h"

#include <vector>
#include <iostream>
#include <cstring>
#include <exception>

#include <boost/graph/breadth_first_search.hpp>

static const uint32 UNALLOCATED = 0xffffffff;

struct LayoutHelper {
  LayoutHelper(uint32 numStates, byte* buf): SizeVec(numStates), Offsets(numStates), LastState(UNALLOCATED), Buffer(buf), Guard(buf) {}
  
  std::vector< uint32 > SizeVec,
                        Offsets;

  uint32 LastState;
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
    uint32 numEdges = out_degree(v, graph);
    *((uint32*)Helper->Guard) = numEdges;
    size_t offset = Helper->Guard - Helper->Buffer;
    Helper->Offsets[v] = offset;
    if (0 == numEdges) {
      if (UNALLOCATED == Helper->LastState) {
        // std::cout << "last state is " << v << " at offset " << offset << std::endl;
        Helper->LastState = offset;
      }
      else {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Helper->LastState = " << Helper->LastState << ", offset = " << offset << ", v = " << v);
      }
    }
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
        // std::stringstream buf;
        // buf << __FILE__ << ":" << __LINE__ << ": "<< "(" << boost::source(*cur, graph) << ", " << boost::target(*cur, graph) << "), stateOffset = " << curEdge->StateOffset
        //   << ", transitionOffset = " << curEdge->TransitionOffset;
        // throw std::runtime_error(buf.str());
        THROW_RUNTIME_ERROR_WITH_OUTPUT("(" << boost::source(*cur, graph) << ", " << boost::target(*cur, graph) << "), stateOffset = " << curEdge->StateOffset
          << ", transitionOffset = " << curEdge->TransitionOffset);
      }
      curEdge->StateOffset = Helper->Offsets[boost::target(*cur, graph)];
      curEdge->TransitionOffset = tranGuard - Helper->Buffer;
      // std::cout << "StateOffset = " << curEdge->StateOffset << "; TransitionOffset = " << curEdge->TransitionOffset << "; tranGuard = " << (uint64)tranGuard << std::endl;
      tranGuard += graph[*cur]->clone(tranGuard)->objSize();
      ++curEdge;
    }
  }

private:
  boost::shared_ptr<LayoutHelper> Helper;
};
