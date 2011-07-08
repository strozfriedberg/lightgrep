#pragma once

#include "basic.h"
#include "graph.h"

#include <queue>
#include <stack>

class Compiler {
public:
  typedef std::pair< Graph::vertex, Graph::vertex > StatePair;

  void mergeIntoFSM(Graph& dst, const Graph& src);

  void labelGuardStates(Graph& g);

  void propagateMatchLabels(Graph& g);
  void removeNonMinimalLabels(Graph& g);

private:
  std::vector< std::vector<Graph::vertex> > Dst2Src;
  std::vector<Graph::vertex> Src2Dst;
  std::queue<StatePair> States;
  std::vector<bool> Visited;
};
