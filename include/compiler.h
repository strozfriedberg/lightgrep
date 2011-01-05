#pragma once

#include "basic.h"
#include "graph.h"

#include <stack>

class Compiler {
public:
  typedef std::pair< Graph::vertex_descriptor, Graph::vertex_descriptor > StatePair;

  void mergeIntoFSM(Graph& fsm, const Graph& addend, uint32 keyIdx);
  
  void labelGuardStates(Graph& fsm); 
 
private:
  std::vector< Graph::vertex_descriptor > StateMap;
  std::stack< StatePair, std::vector<StatePair> > States;
  std::vector< bool > Visited;

  void propagateMatchLabels(Graph& fsm);
  void removeNonMinimalLabels(Graph& fsm);
};
