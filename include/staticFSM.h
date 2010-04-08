#pragma once

#include "basic.h"

class StaticFSM {
public:
  StaticFSM();

  uint32 numStates() const;

  void allocate(uint32 transitionSize, uint32 numStates, uint32 numEdges);

private:
  uint32 NumStates;
  
  boost::shared_array<byte> Buffer;
};
