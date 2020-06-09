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

#include "nfaoptimizer.h"
#include "sequences.h"
#include "states.h"
#include "utility.h"

#include <iostream>
#include <iterator>

static const NFA::VertexDescriptor NONE = 0xFFFFFFFF;
static const NFA::VertexDescriptor UNLABELABLE = 0xFFFFFFFE;

const uint32_t NOLABEL = std::numeric_limits<uint32_t>::max();

bool NFAOptimizer::canMerge(
  const NFA& dst,
  NFA::VertexDescriptor dstTail,
  const Transition* dstTrans,
  ByteSet& dstBits,
  const NFA& src,
  NFA::VertexDescriptor srcTail,
  const ByteSet& srcBits) const
{
  // Explanation of the condition:
  //
  // Vertices match if:
  //
  // 1) they have the same incoming edge
  // 2) they have the same label (i.e., they are match states for
  //    the same pattern, or are not match states)
  // 3) if they are match states, then they have no successors
  // 4) the destination has only one incoming edge
  // 5) the source has only one incoming edge
  // 6) if the destination has been matched with a source, then that
  //    source has only one incoming edge
  // 7) the source has only one incoming edge

  if (
    dst[dstTail].Label == src[srcTail].Label &&
    (
      dst[dstTail].Label == NOLABEL ||
      (0 == src.outDegree(srcTail) && 0 == dst.outDegree(dstTail))
    )
    && 1 == dst.inDegree(dstTail) && 1 == src.inDegree(srcTail)
  )
  {
    const std::map<NFA::VertexDescriptor, std::vector<NFA::VertexDescriptor>>::const_iterator i(Dst2Src.find(dstTail));
    if (i == Dst2Src.end() || 1 == src.inDegree(i->second.front())) {
      dstTrans->getBytes(dstBits);
      return dstBits == srcBits;
    }
  }

  return false;
}

NFAOptimizer::StatePair NFAOptimizer::processChild(
  const NFA& src,
  NFA& dst,
  uint32_t si,
  NFA::VertexDescriptor srcHead,
  NFA::VertexDescriptor dstHead)
{
  const NFA::VertexDescriptor srcTail = src.outVertex(srcHead, si);

  NFA::VertexDescriptor dstTail = Src2Dst[srcTail];
  uint32_t di = 0;

  const uint32_t dstHeadOutDegree = dst.outDegree(dstHead);

  if (dstTail != NONE) {
    for ( ; di < dstHeadOutDegree; ++di) {
      if (dst.outVertex(dstHead, di) == dstTail) {
        break;
      }
    }
  }
  else {
    const Transition* srcTrans(src[srcTail].Trans);

    ByteSet srcBits;
    srcTrans->getBytes(srcBits);

    // try to match it with a successor of the destination vertex,
    // preserving the relative order of the source vertex's successors

    // find dstTail range to which we could map srcTail, by branch order

    bool found = false;
    ByteSet dstBits;

    std::map<NFA::VertexDescriptor, uint32_t>::const_iterator i(DstPos.find(dstHead));
    di = i == DstPos.end() ? 0 : i->second;

    for ( ; di < dstHeadOutDegree; ++di) {
      dstTail = dst.outVertex(dstHead, di);
      const Transition* dstTrans(dst[dstTail].Trans);

//      std::cerr << "match src " << srcTail << " with dst " << dstTail << "? ";

      if (canMerge(dst, dstTail, dstTrans, dstBits,
                   src, srcTail,           srcBits)) {
        found = true;
        break;
      }
    }

    if (!found) {
      // match not found

      // add a new vertex to the destination if the image of the source
      // tail vertex cannot be matched
      dstTail = dst.addVertex();
      dst[dstTail] = src[srcTail];

      if (i == DstPos.end()) {
        di = 0;
      }

      // std::cerr << "added new vertex " << dstTail << " for "
      //                                  << srcTail << std::endl;
      // std::cerr << "added edge " << dstHead << " -> " << dstTail << std::endl;
    }
  }

  // don't insert duplicate edges
  bool found = false;
  for (NFA::VertexSizeType i = 0; i < dstHeadOutDegree; ++i) {
    if (dst.outVertex(dstHead, i) == dstTail) {
      found = true;
      break;
    }
  }

  if (!found) {
    dst.insertEdge(dstHead, dstTail, di);
  }

/*
  const auto dstHeadOut(dst.outVertices(dstHead));
  const auto dstHeadOutEnd(dstHeadOut.end());
  if (std::find(dstHeadOut.begin(), dstHeadOutEnd, dstTail) != dstHeadOutEnd) {
    dst.insertEdge(dstHead, dstTail, di);
  }
*/

  DstPos[dstHead] = di;
  return StatePair(dstTail, srcTail);
}

void NFAOptimizer::mergeIntoFSM(NFA& dst, const NFA& src) {
  Src2Dst.assign(src.verticesSize(), NONE);
  Dst2Src.clear();
  DstPos.clear();
  Visited.clear();

  Src2Dst[0] = 0;

  // push all outedges of the initial state in the source
  for (int32_t i = src.outDegree(0) - 1; i >= 0; --i) {
    Edges.push(StatePair(0, i));
  }

  while (!Edges.empty()) {
    const StatePair& p(Edges.top());
    Edges.pop();

    const uint32_t si = p.second;
    const NFA::VertexDescriptor srcHead = p.first;
    const NFA::VertexDescriptor dstHead = Src2Dst[srcHead];

    // skip if we've seen this edge already
    if (Visited.find(p) != Visited.end()) {
      continue;
    }

    Visited.insert(p);

    const StatePair s(processChild(src, dst, si, srcHead, dstHead));
    const NFA::VertexDescriptor srcTail = s.second;
    const NFA::VertexDescriptor dstTail = s.first;

    Src2Dst[srcTail] = dstTail;
    Dst2Src[dstTail].push_back(srcTail);

    for (int32_t i = src.outDegree(srcTail) - 1; i >= 0; --i) {
      Edges.push(StatePair(srcTail, i));
    }
  }

  dst.Deterministic &= src.Deterministic;
}

void NFAOptimizer::pruneBranches(NFA& g) {
  std::stack<NFA::VertexDescriptor> next;
  std::set<NFA::VertexDescriptor> seen;

  next.push(0);
  seen.insert(0);

//  ByteSet mbs, obs, nbs;
  ByteSet mbs, obs;

  // walk the graph
  while (!next.empty()) {
    const NFA::VertexDescriptor head = next.top();
    next.pop();

    mbs.reset();

    // remove same-transition edges following a match vertex,
    // accumulating transition bytes for match edges as we go
    for (uint32_t i = 0; i < g.outDegree(head); ++i) {
      const NFA::VertexDescriptor tail = g.outVertex(head, i);

      if (seen.insert(tail).second) {
        next.push(tail);
      }

      g[tail].Trans->getBytes(obs);

//      nbs = obs & ~mbs;
      obs &= ~mbs;

//      if (nbs.none()) {
      if (obs.none()) {
        g.removeEdge(g.outEdge(head, i--));
      }
/*
      else if (nbs != obs) {
        Transition* ot = g[tail];
        Transition* nt = new ByteSetState(nbs);
        nt->IsMatch = ot->IsMatch;
        nt->Label = ot->Label;
        g.setTran(tail, nt);
        delete ot;
      }
*/

      if (g[tail].IsMatch) {
        mbs |= obs;
      }
    }
  }
}

void NFAOptimizer::labelGuardStates(NFA& g) {
  propagateMatchLabels(g);
  removeNonMinimalLabels(g);
}

void NFAOptimizer::propagateMatchLabels(NFA& g) {
  // uint32_t count = 0;

  std::stack<NFA::VertexDescriptor, std::vector<NFA::VertexDescriptor>> next, unext;

  for (NFA::VertexDescriptor m = 0; m < g.verticesSize(); ++m) {
    // skip non-match vertices
    if (!g[m].IsMatch) continue;

    // if (++count % 10000 == 0) {
    //   std::cerr << "handled " << i << " labeled vertices" << std::endl;
    // }

    const uint32_t label = g[m].Label;

    // walk label back from this match state to all of its ancestors
    // which have no other match-state descendants

    next.push(m);

    while (!next.empty()) {
      const NFA::VertexDescriptor t = next.top();
      next.pop();

      // check each parent of the current state
      for (const NFA::VertexDescriptor h : g.inVertices(t)) {
        if (!g[h].Trans) {
          // Skip the initial state.
          continue;
        }
        else if (g[h].Label == NONE) {
          // Mark unmarked parents with our label and walk back to them.
          g[h].Label = label;
          next.push(h);
        }
        else if (g[h].Label == UNLABELABLE) {
          // This parent is already marked as an ancestor of multiple match
          // states; all paths from it back to the root are already marked
          // as unlabelable, so we don't need to walk back from it.
        }
        else if (g[h].Label == label) {
          // This parent has our label, which means we've already walked
          // back through it.
        }
        else {
          // This parent has the label of some other match state. Mark it
          // and all of its ancestors unlabelable.

          unext.push(h);

          while (!unext.empty()) {
            const NFA::VertexDescriptor u = unext.top();
            unext.pop();

            g[u].Label = UNLABELABLE;

            for (const NFA::VertexDescriptor uh : g.inVertices(u)) {
              if (g[uh].Trans && g[uh].Label != UNLABELABLE) {
                // Walking on all nodes not already marked unlabelable
                unext.push(uh);
              }
            }
          }
        }
      }
    }
  }
}

void NFAOptimizer::removeNonMinimalLabels(NFA& g) {
  // Make a list of all tails of edges where the head is an ancestor of
  // multiple match states, but the tail is an ancestor of only one.
  std::vector<bool> visited(g.verticesSize());

  std::set<NFA::VertexDescriptor> heads;
  std::stack<NFA::VertexDescriptor, std::vector<NFA::VertexDescriptor>> next;

  next.push(0);
  visited[0] = true;

  while (!next.empty()) {
    NFA::VertexDescriptor h = next.top();
    next.pop();

    for (const NFA::VertexDescriptor t : g.outVertices(h)) {
      if (!visited[t]) {
        if (g[t].Label == UNLABELABLE) {
          g[t].Label = NONE;
          next.push(t);
        }
        else {
          heads.insert(t);
        }

        visited[t] = true;
      }
    }
  }

  // Push all of the minimal guard states we found back onto the stack.
  for (const NFA::VertexDescriptor v : heads) {
    next.push(v);
  }

  // Unlabel every remaining node not in heads.
  while (!next.empty()) {
    const NFA::VertexDescriptor h = next.top();
    next.pop();

    for (const NFA::VertexDescriptor t : g.outVertices(h)) {
      if (!visited[t]) {
        // NB: Any node which should be labeled, we've already visited,
        // so we can unlabel everything we reach this way.
        g[t].Label = NONE;
        next.push(t);
        visited[t] = true;
      }
    }
  }
}

void makePerByteOutNeighborhoods(
  const NFA& src,
  const NFA::VertexDescriptor srcHead,
  ByteToVertices& srcTailLists,
  ByteSet& outBytes)
{
  // for each srcTail, add it to srcHead's per-byte outneighborhood
  for (const NFA::VertexDescriptor srcTail : src.outVertices(srcHead)) {
    src[srcTail].Trans->getBytes(outBytes);

    for (uint32_t b = 0; b < 256; ++b) {
      if (outBytes[b]) {
        srcTailLists[b].push_back(srcTail);
      }
    }
  }
}

using BytesToVertices = std::map<ByteSet, VList>;

void makeByteSetsWithDistinctOutNeighborhoods(
  const ByteToVertices& srcTailLists,
  BytesToVertices& bytes2SrcList)
{
  using VerticesToBytes = std::map<VList, ByteSet>;

  VerticesToBytes srcList2Bytes;

  // mark the outgoing byte for each out neighborhood
  const auto beg(srcTailLists.cbegin());
  const auto end(srcTailLists.cend());
  for (auto i(beg); i != end; ++i) {
    srcList2Bytes[*i][i - beg] = true;
  }

  // invert the map
  for (const VerticesToBytes::value_type& v : srcList2Bytes) {
    bytes2SrcList[v.second] = v.first;
  }
}

void addToDeterminizationGroup(
  const NFA& src,
  const NFA::VertexDescriptor srcTail,
  const ByteSet& bs,
  std::map<ByteSet, std::vector<VList>>& dstListGroups,
  bool& startGroup)
{
  if (src[srcTail].IsMatch) {
    // match states are always singleton groups
    dstListGroups[bs].emplace_back();
    startGroup = true;
  }
  else if (startGroup) {
    dstListGroups[bs].emplace_back();
    startGroup = false;
  }

  dstListGroups[bs].back().push_back(srcTail);
}

void makeDestinationState(
  const NFA& src,
  const NFA::VertexDescriptor dstHead,
  const ByteSet& bs,
  const VList& dstList,
  uint32_t depth,
  NFA& dst,
  SubsetStateToState& dstList2Dst,
  std::stack<std::pair<SubsetState, int>>& dstStack)
{
  // create or retrieve the state reached from dstHead over the transition
  // on byte set bs, and add an edge from dstHead to that state

  const SubsetState ss(bs, dstList);
  const SubsetStateToState::const_iterator l(dstList2Dst.find(ss));

  NFA::VertexDescriptor dstTail;
  if (l == dstList2Dst.end()) {
    // new sublist dst vertex
    dstList2Dst[ss] = dstTail = dst.addVertex();
    dstStack.push({ss, depth});
    dst[dstTail].Trans = dst.TransFac->getSmallest(bs);

    if (src[dstList.front()].IsMatch) {
      dst[dstTail].IsMatch = true;
      dst[dstTail].Label = src[dstList.front()].Label;
    }
  }
  else {
    // old sublist vertex
    dstTail = l->second;
  }

  dst.addEdge(dstHead, dstTail);
}

void handleSubsetStateSuccessors(
  const NFA& src,
  const VList& srcHeadList,
  const NFA::VertexDescriptor dstHead,
  uint32_t depth,
  NFA& dst,
  std::stack<std::pair<SubsetState,int>>& dstStack,
  ByteSet& outBytes,
  SubsetStateToState& dstList2Dst)
{
  ByteToVertices srcTailLists;

  // for each byte, collect all srcTails leaving srcHeads
  for (const NFA::VertexDescriptor srcHead : srcHeadList) {
    makePerByteOutNeighborhoods(src, srcHead, srcTailLists, outBytes);
  }

  // remove right duplicates from each srcTailsList
  for (ByteToVertices::value_type& p : srcTailLists) {
    removeRightDuplicates(p);
  }

  // collapse outgoing bytes with the same srcTails
  BytesToVertices bytes2SrcList;
  makeByteSetsWithDistinctOutNeighborhoods(srcTailLists, bytes2SrcList);

  // form each srcTailList into determinizable groups
  std::map<ByteSet, std::vector<VList>> dstListGroups;

  for (const auto& v : bytes2SrcList) {
    const ByteSet& bs(v.first);
    const VList& srcTailList(v.second);

    bool startGroup = true;

    for (const NFA::VertexDescriptor srcTail : srcTailList) {
      addToDeterminizationGroup(src, srcTail, bs, dstListGroups, startGroup);
    }
  }

  // determinize for each outgoing byte set
  for (const auto& v : dstListGroups) {
    const ByteSet& bs(v.first);
    const std::vector<VList>& dstLists(v.second);
    for (const VList& dstList : dstLists) {
      makeDestinationState(src, dstHead, bs, dstList, depth, dst, dstList2Dst, dstStack);
    }
  }
}

void connectSubsetStateToOriginal(
  NFA& dst,
  const NFA& src,
  const VList& srcHeadList,
  const NFA::VertexDescriptor dstHead,
  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor>& src2Dst
)
{
  /*
    A subset state in the partial DFA dst (by definition) corresponds to a
    set of states in the NFA src. The NFA states in this set have a (possibly
    empty) set of successors in src. This function creates in dst states
    corresponding to those successors, and makes edges to them from the given
    subset state.

    E.g., if {1,3} is a subset state in dst and src is

        1 - 4
       /
      0
       \
        2 - 3 - 5

    then this function will ensure that 4' and 5' exist in dst (creating
    them if necessary) and that {1,3} has edges going to them.

    Note that this doesn't bother with labels or matches; completeOriginal()
    is responsible for setting those.
  */

  for (const auto& v: srcHeadList) {
    for (const auto& n: src.outVertices(v)) {
      // get the image of n in dst, creating it if necessary
      const auto i = src2Dst.find(n);
      const NFA::VertexDescriptor dst_n = i == src2Dst.end() ? src2Dst[n] = dst.addVertex() : i->second;

      dst.addEdge(dstHead, dst_n);
    }
  }
}

void completeOriginal(
  NFA& dst,
  const NFA& src,
  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor>& src2Dst
)
{
  /*
    The purpose of this function is to paste undeterminized tails onto
    a partially-determinized NFA. Splices between the endpoints of the
    partially-determinized NFA dst and source NFA src are stored in
    src2Dst.

    For each x in src2Dst, the subgraph in src rooted at x is copied to
    src2Dst[x]. That's it.

    E.g., with src

                2 - 3
               /
          0 - 1 - 4 - 5

    and dst
               C
              /
         A - B
              \
               D - E

    with 1 mapped to C yields

                 2 - 3
                /
               C - 4 - 5
              /
         A - B
              \
               D - E

  */

  std::stack<NFA::VertexDescriptor> next;

  for (const auto& p: src2Dst) {
    next.push(p.first);
  }

  while (!next.empty()) {
    NFA::VertexDescriptor h = next.top();
    next.pop();

    const NFA::VertexDescriptor hh = src2Dst[h];
    dst[hh].Label = src[h].Label;
    dst[hh].IsMatch = src[h].IsMatch;
    dst[hh].Trans = dst.TransFac->get(src[h].Trans);

    for (const auto& t: src.outVertices(h)) {
      NFA::VertexDescriptor tt;
      const auto i = src2Dst.find(t);
      if (i == src2Dst.end()) {
        // make sure t' exists
        src2Dst[t] = tt = dst.addVertex();

        next.push(t);
      }
      else {
        tt = i->second;
      }

      // connect h' to t'
      dst.addEdge(hh, tt);
    }
  }
}

void NFAOptimizer::subsetDFA(NFA& dst, const NFA& src, uint32_t determinizeLimit) {
  // std::cerr << "starting subsetDFA" << std::endl;
  std::stack<std::pair<SubsetState, int>> dstStack;
  SubsetStateToState dstList2Dst;
  std::map<NFA::VertexDescriptor, NFA::VertexDescriptor> src2Dst;

  // set up initial dst state
  const SubsetState d0(ByteSet(), VList{0});
  dstList2Dst[d0] = 0;
  dstStack.push({d0, 0});

  ByteSet outBytes;

  // process each subset state
  // uint32_t num = 0;
  while (!dstStack.empty()) {
    // if (++num % 10000 == 0) {
    //   std::cerr << "processed " << num << " subset states so far" << std::endl;
    // }
    const SubsetState ss(dstStack.top().first);
    const uint32_t depth = dstStack.top().second;
    dstStack.pop();

    const VList& srcHeadList(ss.second);
    const NFA::VertexDescriptor dstHead = dstList2Dst[ss];

    if (depth < determinizeLimit) {
      // continue processing this subset state's successors
      handleSubsetStateSuccessors(
        src, srcHeadList, dstHead, depth + 1,
        dst, dstStack, outBytes, dstList2Dst
      );
    }
    else {
      // connect this subset state back to the (copy of) the original graph
      connectSubsetStateToOriginal(dst, src, srcHeadList, dstHead, src2Dst);
    }
  }

  if (!src2Dst.empty()) {
    // we did not fully determinize; paste on the rest of the original graph
    dst.Deterministic = false;
    completeOriginal(dst, src, src2Dst);
  }

  // std::cerr << "done with subsetDFA" << std::endl;
}
