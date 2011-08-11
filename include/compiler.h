#pragma once

#include "basic.h"
#include "graph.h"

#include <set>
#include <stack>

class Compiler {
public:
  typedef std::vector<Graph::vertex> Branch;
  typedef std::pair< Graph::vertex, Graph::vertex > StatePair;

  void mergeIntoFSM(Graph& dst, const Graph& src);

  void labelGuardStates(Graph& g);

  void propagateMatchLabels(Graph& g);
  void removeNonMinimalLabels(Graph& g);
  
  void reduceRange(const Graph& dst, Graph::vertex dstHead, const Branch& sbranch, uint32& lb, uint32& ub);

  StatePair processChild(const Graph& src, Graph& dst, uint32 si, Graph::vertex srcHead, Graph::vertex dstHead, uint32& lb);

private:
  std::vector< Branch > Dst2Src,
                        BranchMap;
  std::vector<Graph::vertex> Src2Dst;
  std::stack<StatePair> States;
//  std::vector<bool> Visited;
  std::set<StatePair> Visited;
};
