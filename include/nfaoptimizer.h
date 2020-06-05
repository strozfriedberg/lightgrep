/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "basic.h"
#include "automata.h"

#include <algorithm>
#include <array>
#include <limits>
#include <map>
#include <set>
#include <stack>
#include <vector>

using VDList = std::vector<NFA::VertexDescriptor>;
using SubsetState = std::pair<ByteSet, VDList>;
using ByteToVertices = std::array<VDList,256>;

class NFAOptimizer {
public:
  typedef std::pair<NFA::VertexDescriptor, NFA::VertexDescriptor> StatePair;
  typedef std::pair<NFA::VertexDescriptor, uint32_t> EdgePair;

  void mergeIntoFSM(NFA& dst, const NFA& src);

  void labelGuardStates(NFA& g);

  void propagateMatchLabels(NFA& g);
  void removeNonMinimalLabels(NFA& g);

  void subsetDFA(NFA& dst, const NFA& src, uint32_t determinizeDepth = std::numeric_limits<uint32_t>::max());

  void pruneBranches(NFA& g);

  StatePair processChild(const NFA& src, NFA& dst, uint32_t si, NFA::VertexDescriptor srcHead, NFA::VertexDescriptor dstHead);

  bool canMerge(const NFA& dst, NFA::VertexDescriptor dstTail, const Transition* dstTrans, ByteSet& dstBits, const NFA& src, NFA::VertexDescriptor srcTail, const ByteSet& srcBits) const;

private:
  std::map<NFA::VertexDescriptor, std::vector<NFA::VertexDescriptor>> Dst2Src;
  std::vector<NFA::VertexDescriptor> Src2Dst;
  std::stack<EdgePair> Edges;
  std::set<EdgePair> Visited;
  std::map<NFA::VertexDescriptor, uint32_t> DstPos;
};

void connectSubsetStateToOriginal(
  NFA& dst,
  const NFA& src,
  const std::vector<NFA::VertexDescriptor>& srcHeadList,
  const NFA::VertexDescriptor dstHead,
  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor>& src2Dst
);

void completeOriginal(
  NFA& dst,
  const NFA& src,
  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor>& src2Dst
);

struct SubsetStateComp {
  bool operator()(const SubsetState& a, const SubsetState& b) const {
    const int c = a.first.compare(b.first);
    if (c < 0) {
      return true;
    }
    else if (c > 0) {
      return false;
    }
    else {
      return std::lexicographical_compare(a.second.begin(), a.second.end(),
                                          b.second.begin(), b.second.end());
    }
  }
};

using SubsetStateToState = std::map<SubsetState, NFA::VertexDescriptor, SubsetStateComp>;

void makeDestinationState(
  const NFA& src,
  const NFA::VertexDescriptor dstHead,
  const ByteSet& bs,
  const VDList& dstList,
  uint32_t depth,
  NFA& dst,
  SubsetStateToState& dstList2Dst,
  std::stack<std::pair<SubsetState, int>>& dstStack
);

void handleSubsetStateSuccessors(
  const NFA& src,
  const VDList& srcHeadList,
  const NFA::VertexDescriptor dstHead,
  uint32_t depth,
  NFA& dst,
  std::stack<std::pair<SubsetState,int>>& dstStack,
  ByteSet& outBytes,
  SubsetStateToState& dstList2Dst,
  std::map<ByteSet, std::vector<std::vector<NFA::VertexDescriptor>>>& dstListGroups
);
