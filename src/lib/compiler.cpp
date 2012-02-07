#include "compiler.h"
#include "sequences.h"
#include "states.h"
#include "utility.h"

#include <algorithm>
#include <array>
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
  }

  dst.Deterministic &= src.Deterministic;
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
    const NFA::VertexDescriptor h = next.top();
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
typedef std::array<VDList,256> ByteToVertices;

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

void makePerByteOutNeighborhoods(const NFA& src, const NFA::VertexDescriptor srcHead, ByteToVertices& srcTailLists, ByteSet& outBytes) {
  // for each srcTail, add it to srcHead's per-byte outneighborhood
  const uint32 odeg = src.outDegree(srcHead);
  for (uint32 j = 0; j < odeg; ++j) {
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

typedef std::map<ByteSet, VDList> BytesToVertices;

void makeByteSetsWithDistinctOutNeighborhoods(const ByteToVertices& srcTailLists, BytesToVertices& bytes2SrcList) {
  typedef std::map<VDList, ByteSet> VerticesToBytes;

  VerticesToBytes srcList2Bytes;

  // mark the outgoing byte for each out neighborhood
  const ByteToVertices::const_iterator beg(srcTailLists.begin());
  const ByteToVertices::const_iterator end(srcTailLists.end());
  for (ByteToVertices::const_iterator i(beg); i != end; ++i) {
    srcList2Bytes[*i][i - beg] = true;
  }

  // invert the map
  for (const VerticesToBytes::value_type& v : srcList2Bytes) {
    bytes2SrcList[v.second] = v.first;
  }
}

void addToDeterminizationGroup(const NFA& src, const NFA::VertexDescriptor srcTail, const ByteSet& bs, std::map<ByteSet, std::vector<VDList>>& dstListGroups, bool& startGroup) {
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

typedef std::map<SubsetState, NFA::VertexDescriptor, SubsetStateComp> SubsetStateToState;

void makeDestinationState(const NFA& src, NFA& dst, const NFA::VertexDescriptor dstHead, const ByteSet& bs, const VDList& dstList, SubsetStateToState& dstList2Dst, std::stack<SubsetState>& dstStack) {
  const SubsetState ss(bs, dstList);
  const SubsetStateToState::const_iterator l(dstList2Dst.find(ss));

  NFA::VertexDescriptor dstTail;
  if (l == dstList2Dst.end()) {
    // new sublist dst vertex
    dstList2Dst[ss] = dstTail = dst.addVertex();
    dstStack.push(ss);
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

void collapseCharacterClass(NFA& g, NFA::VertexDescriptor v, ByteSet& outBytes) {
  int32 first = -1;
  int32 last = -1;

  outBytes.reset();
  g[v].Trans->getBits(outBytes);

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
      g[v].Trans = g.TransFac->getLit(first);
    }
    else {
      g[v].Trans = g.TransFac->getRange(first, last);
    }
  }
}

void handleSubsetState(const NFA& src, NFA& dst, const VDList& srcHeadList, const NFA::VertexDescriptor dstHead, std::stack<SubsetState>& dstStack, ByteSet& outBytes, SubsetStateToState& dstList2Dst) {
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
  std::map<ByteSet, std::vector<VDList>> dstListGroups;

  for (const BytesToVertices::value_type& v : bytes2SrcList) {
    const ByteSet& bs(v.first);
    const VDList& srcTailList(v.second);

    bool startGroup = true;

    for (const NFA::VertexDescriptor srcTail : srcTailList) {
      addToDeterminizationGroup(src, srcTail, bs, dstListGroups, startGroup);
    }
  }

  // determinize for each outgoing byte
  for (const std::map<ByteSet, std::vector<VDList>>::value_type& v : dstListGroups) {
    const ByteSet& bs(v.first);
    const std::vector<VDList>& dstLists(v.second);
    for (const VDList& dstList : dstLists) {
      makeDestinationState(src, dst, dstHead, bs, dstList, dstList2Dst, dstStack);
    }
  }
}

void Compiler::subsetDFA(NFA& dst, const NFA& src) {
  std::stack<SubsetState> dstStack;
  SubsetStateToState dstList2Dst;

  // set up initial dst state
  const SubsetState d0(ByteSet(), VDList(1, 0));
  dstList2Dst[d0] = 0;
  dstStack.push(d0);

  ByteSet outBytes;

  // process each subset state
  while (!dstStack.empty()) {
    const SubsetState ss(dstStack.top());
    dstStack.pop();

    const VDList& srcHeadList(ss.second);
    const NFA::VertexDescriptor dstHead = dstList2Dst[ss];

    handleSubsetState(src, dst, srcHeadList, dstHead, dstStack, outBytes, dstList2Dst);
  }

  // collapse CharClassStates where possible
  // isn't necessary, but improves the GraphViz output
  const uint32 dstSize = dst.verticesSize();
  for (uint32 i = 1; i < dstSize; ++i) {
    collapseCharacterClass(dst, i, outBytes);
  }
}
