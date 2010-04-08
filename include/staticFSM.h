#pragma once

#include "basic.h"

class StaticFSM {
public:
  StaticFSM();

  uint32 numStates() const;
  uint32 numEdges() const;

  void allocate(uint32 transitionSize, uint32 numStates, uint32 numEdges);

private:
  uint32 NumStates,
         NumEdges;
  
  boost::shared_array<byte> Buffer;
};
