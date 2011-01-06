#pragma once

#include "basic.h"
#include "graph.h"

#include <stack>

class Compiler {
public:
  typedef std::pair< Graph::vertex, Graph::vertex > StatePair;

  void mergeIntoFSM(Graph& dst, const Graph& src);
  
  void labelGuardStates(Graph& fsm); 
 
private:
  std::vector< Graph::vertex > StateMap;
  std::stack< StatePair, std::vector<StatePair> > States;
  std::vector< bool > Visited;

  void propagateMatchLabels(Graph& fsm);
  void removeNonMinimalLabels(Graph& fsm);
};
