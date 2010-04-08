#include "staticFSM.h"

#include <iostream>

static const uint32 STATE_SIZE = 4;

StaticFSM::StaticFSM():
  NumStates(0), NumEdges(0) {}

uint32 StaticFSM::numStates() const {
  return NumStates;
}

uint32 StaticFSM::numEdges() const {
  return NumEdges;
}

StaticFSM::StateT StaticFSM::getFirstState() const {
  return 0;
}

StaticFSM::EdgeRange StaticFSM::getEdges(StaticFSM::StateT curState) const {
  std::pair<EdgeIt, EdgeIt> ret;
  uint32 numEdges = *((uint32*)(getRawBuffer() + curState));
  ret.first = (EdgeIt)(getRawBuffer() + curState + sizeof(uint32));
  ret.second = ret.first + numEdges;
  return ret;
}

uint32 StaticFSM::allocate(uint32 transitionSize, uint32 numStates, uint32 numEdges) {
  // std::cout << "allocate) transitionSize = " << transitionSize << "; numStates = " << numStates << "; numEdges = " << numEdges << std::endl;

  uint32 size = transitionSize + (numStates * STATE_SIZE) + (numEdges * sizeof(StaticEdge));
  Buffer.reset(new byte[size]);
  NumStates = numStates;
  NumEdges = numEdges;
  return size;
}
