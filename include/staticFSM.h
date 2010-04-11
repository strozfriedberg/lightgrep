#pragma once

#include "basic.h"

struct StaticEdge {
  StaticEdge(): StateOffset(0), TransitionOffset(0) {}
  StaticEdge(uint32 state, uint32 transition): StateOffset(state), TransitionOffset(transition) {}

  uint32 StateOffset,
         TransitionOffset;
};

class StaticFSM {
public:
  typedef ptrdiff_t StateT;
  typedef StaticEdge* EdgeIt;
  typedef std::pair< EdgeIt, EdgeIt > EdgeRange;

  StaticFSM();

  uint32 numStates() const;
  uint32 numEdges() const;

  StateT getFirstState() const;
  EdgeRange getEdges(StateT curState) const;

  bool allowed(const byte* cur, const byte* end, const StaticEdge& edge) const;

  uint32 allocate(uint32 transitionSize, uint32 numStates, uint32 numEdges);
  byte*  getRawBuffer() const { return Buffer.get(); }

  static EdgeRange getEdges(const byte* buffer);

private:
  uint32 NumStates,
         NumEdges;
  
  boost::shared_array<byte> Buffer;
};
