#include "compiler.h"
#include "states.h"
#include "utility.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <vector>

static const NFA::VertexDescriptor NONE = 0xFFFFFFFF;
static const NFA::VertexDescriptor UNLABELABLE = 0xFFFFFFFE;

const uint32 NOLABEL = std::numeric_limits<uint32>::max();

bool Compiler::canMerge(const NFA& dst, NFA::VertexDescriptor dstTail, const Transition* dstTrans, ByteSet& dstBits, const NFA& src, NFA::VertexDescriptor srcTail, const ByteSet& srcBits) const {
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
      dstBits.reset();
      dstTrans->getBits(dstBits);
      return dstBits == srcBits;
    }
  }

  return false;
}

Compiler::StatePair Compiler::processChild(const NFA& src, NFA& dst, uint32 si, NFA::VertexDescriptor srcHead, NFA::VertexDescriptor dstHead) {
  const NFA::VertexDescriptor srcTail = src.outVertex(srcHead, si);

  NFA::VertexDescriptor dstTail = Src2Dst[srcTail];
  uint32 di = 0;

  const uint32 dstHeadOutDegree = dst.outDegree(dstHead);

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
    srcTrans->getBits(srcBits);

    // try to match it with a successor of the destination vertex,
    // preserving the relative order of the source vertex's successors

    // find dstTail range to which we could map srcTail, by branch order

    bool found = false;
    ByteSet dstBits;

    std::map<NFA::VertexDescriptor, uint32>::const_iterator i(DstPos.find(dstHead));
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

  DstPos[dstHead] = di;
  return StatePair(dstTail, srcTail);
}

void Compiler::mergeIntoFSM(NFA& dst, const NFA& src) {
  Src2Dst.assign(src.verticesSize(), NONE);
  Dst2Src.clear();
  DstPos.clear();
  Visited.clear();

  Src2Dst[0] = 0;

  // push all outedges of the initial state in the source
  for (int32 i = src.outDegree(0) - 1; i >= 0; --i) {
    Edges.push(StatePair(0, i));
  }

  while (!Edges.empty()) {
    const StatePair& p(Edges.top());
    Edges.pop();

    const uint32 si = p.second;
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

    for (int32 i = src.outDegree(srcTail) - 1; i >= 0; --i) {
      Edges.push(StatePair(srcTail, i));
    }

    dst.Deterministic &= src.Deterministic;
  }
}

void Compiler::pruneBranches(NFA& g) {
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
    for (uint32 i = 0; i < g.outDegree(head); ++i) {
      const NFA::VertexDescriptor tail = g.outVertex(head, i);

      if (seen.insert(tail).second) {
        next.push(tail);
      }

      obs.reset();
      g[tail].Trans->getBits(obs);

//      nbs = obs & ~mbs;
      obs &= ~mbs;

//      if (nbs.none()) {
      if (obs.none()) {
        g.removeEdge(g.outEdge(head, i--));
      }
/*
      else if (nbs != obs) {
        Transition* ot = g[tail];
        Transition* nt = new CharClassState(nbs);
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

void Compiler::labelGuardStates(NFA& g) {
  propagateMatchLabels(g);
  removeNonMinimalLabels(g);
}

void Compiler::propagateMatchLabels(NFA& g) {
  uint32 i = 0;

  std::stack<NFA::VertexDescriptor, std::vector<NFA::VertexDescriptor>> next, unext;

  for (NFA::VertexDescriptor m = 0; m < g.verticesSize(); ++m) {
    // skip non-match vertices
    if (!g[m].IsMatch) continue;

    if (++i % 10000 == 0) {
      std::cerr << "handled " << i << " labeled vertices" << std::endl;
    }

    const uint32 label = g[m].Label;

    // walk label back from this match state to all of its ancestors
    // which have no other match-state descendants

    next.push(m);

    while (!next.empty()) {
      NFA::VertexDescriptor t = next.top();
      next.pop();

      // check each parent of the current state
      for (uint32 i = 0; i < g.inDegree(t); ++i) {
        NFA::VertexDescriptor h = g.inVertex(t, i);

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
            NFA::VertexDescriptor u = unext.top();
            unext.pop();

            g[u].Label = UNLABELABLE;

            for (uint32 j = 0; j < g.inDegree(u); ++j) {
              NFA::VertexDescriptor uh = g.inVertex(u, j);
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

void Compiler::removeNonMinimalLabels(NFA& g) {
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

    for (uint32 i = 0; i < g.outDegree(h); ++i) {
      NFA::VertexDescriptor t = g.outVertex(h, i);

      if (visited[t]) continue;

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

  // Push all of the minimal guard states we found back onto the stack.
  for (std::set<NFA::VertexDescriptor>::const_iterator vi(heads.begin()); vi != heads.end(); ++vi) {
    next.push(*vi);
  }

  // Unlabel every remaining node not in heads.
  while (!next.empty()) {
    NFA::VertexDescriptor h = next.top();
    next.pop();

    for (uint32 i = 0; i < g.outDegree(h); ++i) {
      NFA::VertexDescriptor t = g.outVertex(h, i);

      if (visited[t]) continue;

      // NB: Any node which should be labeled, we've already visited,
      // so we can unlabel everything we reach this way.
      g[t].Label = NONE;
      next.push(t);
      visited[t] = true;
    }
  }
}

typedef std::vector<NFA::VertexDescriptor> VDList;
typedef std::pair<ByteSet, VDList> SubsetState;

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

void Compiler::subsetDFA(NFA& dst, const NFA& src) {
  typedef std::map<SubsetState, NFA::VertexDescriptor, SubsetStateComp> SubsetStateToStateMap;
  typedef std::set<NFA::VertexDescriptor> VDSet;

  std::stack<SubsetState> dstStack;
  SubsetStateToStateMap dstList2Dst;

  // set up initial dst state
  const SubsetState d0(ByteSet(), VDList(1, 0));
  dstList2Dst[d0] = 0;
  dstStack.push(d0);

  ByteSet outBytes;

  while (!dstStack.empty()) {
    const SubsetState p(dstStack.top());
    dstStack.pop();

    const VDList& srcHeadList(p.second);
    const NFA::VertexDescriptor dstHead = dstList2Dst[p];

    // for each byte, collect all srcTails leaving srcHeads
    std::map<byte, VDList> srcTailLists;

    for (const NFA::VertexDescriptor srcHead : srcHeadList) {
      for (uint32 j = 0; j < src.outDegree(srcHead); ++j) {
        const NFA::VertexDescriptor srcTail = src.outVertex(srcHead, j);

        outBytes.reset();
        src[srcTail].Trans->getBits(outBytes);

        for (uint32 b = 0; b < 256; ++b) {
          if (outBytes[b]) {
            srcTailLists[b].push_back(srcTail);
          }
        }
      }
    }

    // remove right duplicates from each srcTailsList
    for (std::map<byte, VDList>::iterator i(srcTailLists.begin()); i != srcTailLists.end(); ++i) {
      VDList& srcTailList(i->second);
      VDSet seen;

      for (VDList::iterator j(srcTailList.begin()); j != srcTailList.end(); ) {
        const NFA::VertexDescriptor srcTail = *j;
        if (seen.insert(srcTail).second) {
          ++j;
        }
        else {
          j = srcTailList.erase(j);
        }
      }
    }

    // collapse outgoing bytes with the same srcTails
    std::map<VDList, ByteSet> srcList2Bytes;

    for (std::map<byte, VDList>::const_iterator i(srcTailLists.begin()); i != srcTailLists.end(); ++i) {
      const byte b = i->first;
      const VDList& srcTailList(i->second);
      srcList2Bytes[srcTailList][b] = true;
    }

    std::map<ByteSet, VDList> bytes2SrcList;

    for (std::map<VDList, ByteSet>::const_iterator i(srcList2Bytes.begin()); i != srcList2Bytes.end(); ++i) {
      const ByteSet bs = i->second;
      const VDList& srcTailList(i->first);

      bytes2SrcList[bs] = srcTailList;
    }

    // form each srcTailList into determinizable groups
    std::map<ByteSet, std::vector<VDList>> dstListGroups;

    for (std::map<ByteSet, VDList>::const_iterator i(bytes2SrcList.begin()); i != bytes2SrcList.end(); ++i) {
      const ByteSet bs = i->first;
      const VDList& srcTailList(i->second);

      bool startGroup = true;

      for (VDList::const_iterator j(srcTailList.begin()); j != srcTailList.end(); ++j) {
        const NFA::VertexDescriptor srcTail = *j;

        if (src[srcTail].IsMatch) {
          // match states are always singleton groups
          dstListGroups[bs].push_back(VDList());
          startGroup = true;
        }
        else if (startGroup) {
          dstListGroups[bs].push_back(VDList());
          startGroup = false;
        }

        dstListGroups[bs].back().push_back(srcTail);
      }
    }

    // determinize for each outgoing byte
    for (std::map<ByteSet, std::vector<VDList>>::const_iterator i(dstListGroups.begin()); i != dstListGroups.end(); ++i) {
      const ByteSet bs = i->first;
      const std::vector<VDList>& dstLists(i->second);

      for (std::vector<VDList>::const_iterator j(dstLists.begin()); j != dstLists.end(); ++j) {

        const VDList& dstList(*j);
        const SubsetState p(bs, dstList);

        const SubsetStateToStateMap::const_iterator l(dstList2Dst.find(p));

        NFA::VertexDescriptor dstTail;
        if (l == dstList2Dst.end()) {
          // new sublist dst vertex
          dstList2Dst[p] = dstTail = dst.addVertex();
          dstStack.push(std::make_pair(bs, dstList));
          dst[dstTail].Trans = dst.TransFac->getCharClass(bs);
        }
        else {
          // old sublist vertex
          dstTail = l->second;
        }

        if (src[dstList.front()].IsMatch) {
          dst[dstTail].IsMatch = true;
          dst[dstTail].Label = src[dstList.front()].Label;
        }

        dst.addEdge(dstHead, dstTail);
      }
    }
  }

  // collapse CharClassStates where possible
  // isn't necessary, but improves the GraphViz output
  const uint32 dstSize = dst.verticesSize();
  for (uint32 i = 1; i < dstSize; ++i) {
    int32 first = -1;
    int32 last = -1;

    outBytes.reset();
    dst[i].Trans->getBits(outBytes);

    for (int32 b = 0; b < 256; ++b) {
      if (outBytes[b]) {
        if (first == -1) {
          // start of a range
          first = last = b;
        }
        else if (last != b - 1) {
          // not a range
          first = -1;
          break;
        }
        else {
          // ongoing range
          last = b;
        }
      }
    }

    if (first != -1) {
      if (first == last) {
        dst[i].Trans = dst.TransFac->getLit(first);
      }
      else {
        dst[i].Trans = dst.TransFac->getRange(first, last);
      }
    }
  }
}
