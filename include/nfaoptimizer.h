/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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
