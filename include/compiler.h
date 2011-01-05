#pragma once

#include "basic.h"
#include "dynamicFSM.h"

#include <stack>

class Compiler {
public:
  typedef std::pair< DynamicFSM::vertex_descriptor, DynamicFSM::vertex_descriptor > StatePair;

  void mergeIntoFSM(DynamicFSM& fsm, const DynamicFSM& addend, uint32 keyIdx);
  
  void labelGuardStates(DynamicFSM& fsm); 
 
private:
  std::vector< DynamicFSM::vertex_descriptor > StateMap;
  std::stack< StatePair, std::vector<StatePair> > States;
  std::vector< bool > Visited;

  void propagateMatchLabels(DynamicFSM& fsm);
  void removeNonMinimalLabels(DynamicFSM& fsm);
};
