#include "staticFSM.h"

static const uint32 STATE_SIZE = 4;
static const uint32 EDGE_SIZE = 4;

StaticFSM::StaticFSM():
  NumStates(0) {}

uint32 StaticFSM::numStates() const {
  return NumStates;
}

void StaticFSM::allocate(uint32 transitionSize, uint32 numStates, uint32 numEdges) {
  Buffer.reset(new byte[transitionSize + (numStates * STATE_SIZE) + (numEdges * EDGE_SIZE)]);
  NumStates = numStates;
}
