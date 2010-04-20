#include "staticFSM.h"

#include "transition.h"
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

StaticFSM::StateT StaticFSM::getLastState() const {
  return LastState;
}

StaticFSM::EdgeRange StaticFSM::getEdges(StaticFSM::StateT curState) const {
  return getEdges(getRawBuffer() + curState);
}

void StaticFSM::setLastState(StateT last) {
  LastState = last;
}

bool StaticFSM::allowed(const byte *cur, const byte* end, const StaticEdge& edge) const {
  Transition *t = reinterpret_cast<Transition*>(getRawBuffer() + edge.TransitionOffset);
  return cur != t->allowed(cur, end);
}

uint32 StaticFSM::allocate(uint32 transitionSize, uint32 numStates, uint32 numEdges) {
  // std::cout << "allocate) transitionSize = " << transitionSize << "; numStates = " << numStates << "; numEdges = " << numEdges << std::endl;
  if (!(numEdges > 0 && numStates < 2)) {
    uint32 size = transitionSize + (numStates * STATE_SIZE) + (numEdges * sizeof(StaticEdge));
    Buffer.reset(new byte[size]);
    NumStates = numStates;
    NumEdges = numEdges;
    return size;
  }
  else {
    Buffer.reset(0);
    NumStates = 0;
    NumEdges = 0;
    return 0;
  }
}

StaticFSM::EdgeRange StaticFSM::getEdges(const byte* buffer) {
  EdgeRange ret;
  uint32 numEdges = *((uint32*)buffer);
  if (numEdges) {
    ret.first = (EdgeIt)(buffer + sizeof(uint32));
    ret.second = ret.first + numEdges;
  }
  else {
    ret.first = ret.second = 0;
  }
  return ret;
}
