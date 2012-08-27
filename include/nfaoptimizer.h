#pragma once

#include "basic.h"
#include "automata.h"

#include <map>
#include <set>
#include <stack>

class NFAOptimizer {
public:
  typedef std::pair<NFA::VertexDescriptor, NFA::VertexDescriptor> StatePair;
  typedef std::pair<NFA::VertexDescriptor, uint32> EdgePair;

  void mergeIntoFSM(NFA& dst, const NFA& src);

  void labelGuardStates(NFA& g);

  void propagateMatchLabels(NFA& g);
  void removeNonMinimalLabels(NFA& g);

  void subsetDFA(NFA& dst, const NFA& src);

  void pruneBranches(NFA& g);

  StatePair processChild(const NFA& src, NFA& dst, uint32 si, NFA::VertexDescriptor srcHead, NFA::VertexDescriptor dstHead);

  bool canMerge(const NFA& dst, NFA::VertexDescriptor dstTail, const Transition* dstTrans, ByteSet& dstBits, const NFA& src, NFA::VertexDescriptor srcTail, const ByteSet& srcBits) const;

private:
  std::map<NFA::VertexDescriptor, std::vector<NFA::VertexDescriptor>> Dst2Src;
  std::vector<NFA::VertexDescriptor> Src2Dst;
  std::stack<EdgePair> Edges;
  std::set<EdgePair> Visited;
  std::map<NFA::VertexDescriptor, uint32> DstPos;
};
