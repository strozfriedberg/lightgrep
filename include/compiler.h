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
  
  StatePair processChild(const Graph& src, Graph& dst, uint32 si, Graph::vertex srcHead, Graph::vertex dstHead);

private:
  std::vector< Branch > Dst2Src;
  std::vector<Graph::vertex> Src2Dst;
  std::stack<StatePair> States;
  std::set<StatePair> Visited;
  std::vector<uint32> DstPos;
};
