#include "compiler.h"
#include "states.h"
#include "utility.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <vector>

static const Graph::vertex NONE = 0xFFFFFFFF;
static const Graph::vertex UNLABELABLE = 0xFFFFFFFE;

const uint32 NOLABEL = std::numeric_limits<uint32>::max();

bool Compiler::canMerge(const Graph& dst, Graph::vertex dstTail, const Transition* dstTrans, ByteSet& dstBits, const Graph& src, Graph::vertex srcTail, const Transition* srcTrans, const ByteSet& srcBits) const {
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
    dstTrans->Label == srcTrans->Label &&
    (
      dstTrans->Label == NOLABEL ||
      (0 == src.outDegree(srcTail) && 0 == dst.outDegree(dstTail))
    )
    && 1 == dst.inDegree(dstTail) && 1 == src.inDegree(srcTail)
  )
  {
    const std::map< Graph::vertex, std::vector<Graph::vertex> >::const_iterator i(Dst2Src.find(dstTail));
    if (i == Dst2Src.end() || 1 == src.inDegree(i->second.front())) {
      dstBits.reset();
      dstTrans->getBits(dstBits);
      return dstBits == srcBits;
    }
  }

  return false;
}

Compiler::StatePair Compiler::processChild(const Graph& src, Graph& dst, uint32 si, Graph::vertex srcHead, Graph::vertex dstHead) {
  const Graph::vertex srcTail = src.outVertex(srcHead, si);

  Graph::vertex dstTail = Src2Dst[srcTail];
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
    const Transition* srcTrans(src[srcTail]);

    ByteSet srcBits;
    srcTrans->getBits(srcBits);

    // try to match it with a successor of the destination vertex,
    // preserving the relative order of the source vertex's successors

    // find dstTail range to which we could map srcTail, by branch order

    bool found = false;
    ByteSet dstBits;

    std::map<Graph::vertex, uint32>::const_iterator i(DstPos.find(dstHead));
    di = i == DstPos.end() ? 0 : i->second;

    for ( ; di < dstHeadOutDegree; ++di) {
      dstTail = dst.outVertex(dstHead, di);
      const Transition* dstTrans(dst[dstTail]);

//      std::cerr << "match src " << srcTail << " with dst " << dstTail << "? ";

      if (canMerge(dst, dstTail, dstTrans, dstBits,
                   src, srcTail, srcTrans, srcBits)) {
        found = true;
        break;
      }
    }

    if (!found) {
      // match not found

      // add a new vertex to the destination if the image of the source
      // tail vertex cannot be matched
      dstTail = dst.addVertex();
      dst.setTran(dstTail, srcTrans->clone());

      if (i == DstPos.end()) {
        di = 0;
      }

      #ifdef LBT_TRACE_ENABLED
      std::cerr << "added new vertex " << dstTail << " for "
                                       << srcTail << std::endl;
      #endif

      #ifdef LBT_TRACE_ENABLED
      std::cerr << "added edge " << dstHead << " -> " << dstTail << std::endl;
      #endif
    }
  }

  dst.addEdgeAt(dstHead, dstTail, di);
  DstPos[dstHead] = di;
  return StatePair(dstTail, srcTail);
}

void Compiler::mergeIntoFSM(Graph& dst, const Graph& src) {
  Src2Dst.assign(src.numVertices(), NONE);
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
    const Graph::vertex srcHead = p.first;
    const Graph::vertex dstHead = Src2Dst[srcHead];

    // skip if we've seen this edge already
    if (Visited.find(p) != Visited.end()) {
      continue;
    }

    Visited.insert(p);

    const StatePair s(processChild(src, dst, si, srcHead, dstHead));
    const Graph::vertex srcTail = s.second;
    const Graph::vertex dstTail = s.first;

    Src2Dst[srcTail] = dstTail;
    Dst2Src[dstTail].push_back(srcTail);

    for (int32 i = src.outDegree(srcTail) - 1; i >= 0; --i) {
      Edges.push(StatePair(srcTail, i));
    }
  }
}

void Compiler::pruneBranches(Graph& g) {
  std::stack<Graph::vertex> next;
  std::set<Graph::vertex> seen;

  next.push(0);
  seen.insert(0);

  ByteSet mbs, obs;

  // walk the graph
  while (!next.empty()) {
    const Graph::vertex head = next.top();
    next.pop();

    // remove same-transition edges following a match vertex
    for (uint32 i = 0; i < g.outDegree(head); ++i) {
      const Graph::vertex tail = g.outVertex(head, i);

      if (seen.insert(tail).second) {
        next.push(tail);
      }

      if (g[tail]->IsMatch) {
        mbs.reset();
        g[tail]->getBits(mbs);
        mbs.flip();

        for (uint32 j = g.outDegree(head) - 1; j > i; --j) {
          const Graph::vertex t2 = g.outVertex(head, j);

          obs.reset();
          g[t2]->getBits(obs);

          obs &= mbs;

          if (obs.none()) {
            g.removeEdge(head, j);
          }
/*
          else {
            Transition* ot = g[t2];
            Transition* nt = new CharClassState(obs);
            nt->IsMatch = ot->IsMatch;
            nt->Label = ot->Label;
            g.setTran(t2, nt);
            delete ot;
          }
*/
        }
      }
    }
  }
}

void Compiler::labelGuardStates(Graph& g) {
  propagateMatchLabels(g);
  removeNonMinimalLabels(g);
}

void Compiler::propagateMatchLabels(Graph& g) {
  uint32 i = 0;

  std::stack<Graph::vertex, std::vector<Graph::vertex> > next, unext;

  for (Graph::vertex m = 0; m < g.numVertices(); ++m) {
    // skip non-match vertices
    if (!g[m] || !g[m]->IsMatch) continue;

    if (++i % 10000 == 0) {
      std::cerr << "handled " << i << " labeled vertices" << std::endl;
    }

    const unsigned int label = g[m]->Label;

    // walk label back from this match state to all of its ancestors
    // which have no other match-state descendants

    next.push(m);

    while (!next.empty()) {
      Graph::vertex t = next.top();
      next.pop();

      // check each parent of the current state
      for (uint32 i = 0; i < g.inDegree(t); ++i) {
        Graph::vertex h = g.inVertex(t, i);

        if (!g[h]) {
          // Skip the initial state.
          continue;
        }
        else if (g[h]->Label == NONE) {
          // Mark unmarked parents with our label and walk back to them.
          g[h]->Label = label;
          next.push(h);
        }
        else if (g[h]->Label == UNLABELABLE) {
          // This parent is already marked as an ancestor of multiple match
          // states; all paths from it back to the root are already marked
          // as unlabelable, so we don't need to walk back from it.
        }
        else if (g[h]->Label == label) {
          // This parent has our label, which means we've already walked
          // back through it.
        }
        else {
          // This parent has the label of some other match state. Mark it
          // and all of its ancestors unlabelable.

          unext.push(h);

          while (!unext.empty()) {
            Graph::vertex u = unext.top();
            unext.pop();

            g[u]->Label = UNLABELABLE;

            for (uint32 j = 0; j < g.inDegree(u); ++j) {
              Graph::vertex uh = g.inVertex(u, j);
              if (g[uh] && g[uh]->Label != UNLABELABLE) {
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

void Compiler::removeNonMinimalLabels(Graph& g) {
  // Make a list of all tails of edges where the head is an ancestor of
  // multiple match states, but the tail is an ancestor of only one.
  std::vector<bool> visited(g.numVertices());

  std::set<Graph::vertex> heads;
  std::stack<Graph::vertex, std::vector<Graph::vertex> > next;

  next.push(0);
  visited[0] = true;

  while (!next.empty()) {
    Graph::vertex h = next.top();
    next.pop();

    for (uint32 i = 0; i < g.outDegree(h); ++i) {
      Graph::vertex t = g.outVertex(h, i);

      if (visited[t]) continue;

      if (g[t]->Label == UNLABELABLE) {
        g[t]->Label = NONE;
        next.push(t);
      }
      else {
        heads.insert(t);
      }

      visited[t] = true;
    }
  }

  // Push all of the minimal guard states we found back onto the stack.
  for (std::set<Graph::vertex>::const_iterator vi(heads.begin()); vi != heads.end(); ++vi) {
    next.push(*vi);
  }

  // Unlabel every remaining node not in heads.
  while (!next.empty()) {
    Graph::vertex h = next.top();
    next.pop();

    for (uint32 i = 0; i < g.outDegree(h); ++i) {
      Graph::vertex t = g.outVertex(h, i);

      if (visited[t]) continue;

      // NB: Any node which should be labeled, we've already visited,
      // so we can unlabel everything we reach this way.
      g[t]->Label = NONE;
      next.push(t);
      visited[t] = true;
    }
  }
}

struct ByteSetLess {
  bool operator()(const ByteSet& a, const ByteSet& b) const {
    for (uint32 i = 0; i < 256; ++i) {
      if (a[i] < b[i]) {
        return false;
      }
      else if (a[i] > b[i]) {
        return true;
      }
    }

    return false;
  }
};

struct PairLess {
  bool operator()(
    const std::pair<ByteSet, std::vector<Graph::vertex> >& a,
    const std::pair<ByteSet, std::vector<Graph::vertex> >& b) const
  {
    for (uint32 i = 0; i < 256; ++i) {
      if (a.first[i] < b.first[i]) {
        return false;
      }
      else if (a.first[i] > b.first[i]) {
        return true;
      }
    }

    return std::lexicographical_compare(a.second.begin(), a.second.end(),
                                        b.second.begin(), b.second.end());
  }
};

void Compiler::subsetDFA(Graph& dst, const Graph& src) {

  std::stack< std::pair<ByteSet, std::vector<Graph::vertex> > > dstStack;
  std::map< std::pair<ByteSet, std::vector<Graph::vertex> >, Graph::vertex, PairLess > dstList2Dst;

  // set up initial dst state
  const std::pair<ByteSet, std::vector<Graph::vertex> > d0(ByteSet(), std::vector<Graph::vertex>(1, 0));
  dstList2Dst[d0] = 0;
  dstStack.push(d0);

  ByteSet outBytes;

  while (!dstStack.empty()) {
    const std::pair<ByteSet, std::vector<Graph::vertex> > p(dstStack.top());
    dstStack.pop();

    const std::vector<Graph::vertex>& srcHeadList(p.second);
    const Graph::vertex dstHead = dstList2Dst[p];

    // for each byte, collect all srcTails leaving srcHeads
    std::map< byte, std::vector<Graph::vertex> > srcTailLists;

    for (std::vector<Graph::vertex>::const_iterator i(srcHeadList.begin()); i != srcHeadList.end(); ++i) {
      const Graph::vertex srcHead = *i;

      for (uint32 j = 0; j < src.outDegree(srcHead); ++j) {
        const Graph::vertex srcTail = src.outVertex(srcHead, j);

        outBytes.reset();
        src[srcTail]->getBits(outBytes);

        for (uint32 b = 0; b < 256; ++b) {
          if (outBytes[b]) {
            srcTailLists[b].push_back(srcTail);
          }
        }
      }
    }

    // remove right duplicates from each srcTailsList
    for (std::map< byte, std::vector<Graph::vertex> >::iterator i(srcTailLists.begin()); i != srcTailLists.end(); ++i) {
      std::vector<Graph::vertex>& srcTailList(i->second);
      std::set<Graph::vertex> seen;

      for (std::vector<Graph::vertex>::iterator j(srcTailList.begin()); j != srcTailList.end(); ) {
        const Graph::vertex srcTail = *j;
        if (seen.insert(srcTail).second) {
          ++j;
        }
        else {
          j = srcTailList.erase(j);
        }
      }
    }

    // collapse outgoing bytes with the same srcTails
    std::map<std::vector<Graph::vertex>, ByteSet> srcList2Bytes;

    for (std::map< byte, std::vector<Graph::vertex> >::const_iterator i(srcTailLists.begin()); i != srcTailLists.end(); ++i) {
      const byte b = i->first;
      const std::vector<Graph::vertex>& srcTailList(i->second);

      srcList2Bytes[srcTailList][b] = true;
    }

    std::map<ByteSet, std::vector<Graph::vertex>, ByteSetLess> bytes2SrcList;

    for (std::map<std::vector<Graph::vertex>, ByteSet>::const_iterator i(srcList2Bytes.begin()); i != srcList2Bytes.end(); ++i) {
      const ByteSet bs = i->second;
      const std::vector<Graph::vertex>& srcTailList(i->first);

      bytes2SrcList[bs] = srcTailList;
    }

    // form each srcTailList into determinizable groups
    std::map<ByteSet, std::vector< std::vector<Graph::vertex> >, ByteSetLess> dstListGroups;

    for (std::map<ByteSet, std::vector<Graph::vertex>, ByteSetLess>::const_iterator i(bytes2SrcList.begin()); i != bytes2SrcList.end(); ++i) {
      const ByteSet bs = i->first;
      const std::vector<Graph::vertex>& srcTailList(i->second);

      bool startGroup = true;

      for (std::vector<Graph::vertex>::const_iterator j(srcTailList.begin()); j != srcTailList.end(); ++j) {
        const Graph::vertex srcTail = *j;

        if (src[srcTail]->IsMatch) {
          // match states are always singleton groups
          dstListGroups[bs].push_back(std::vector<Graph::vertex>());
          startGroup = true;
        }
        else if (startGroup) {
          dstListGroups[bs].push_back(std::vector<Graph::vertex>());
          startGroup = false;
        }

        dstListGroups[bs].back().push_back(srcTail);
      }
    }

    // determinize for each outgoing byte
    for (std::map<ByteSet, std::vector< std::vector<Graph::vertex> >, ByteSetLess>::const_iterator i(dstListGroups.begin()); i != dstListGroups.end(); ++i) {
      const ByteSet bs = i->first;
      const std::vector< std::vector<Graph::vertex> >& dstLists(i->second);

      for (std::vector< std::vector<Graph::vertex> >::const_iterator j(dstLists.begin()); j != dstLists.end(); ++j) {

        const std::vector<Graph::vertex>& dstList(*j);
        const std::pair<ByteSet, std::vector<Graph::vertex> > p(bs, dstList);

        std::map< std::pair<ByteSet, std::vector<Graph::vertex> >, Graph::vertex, PairLess>::const_iterator l(dstList2Dst.find(p));

        Graph::vertex dstTail;
        if (l == dstList2Dst.end()) {
          // new sublist dst vertex
          dstList2Dst[p] = dstTail = dst.addVertex();
          dstStack.push(std::make_pair(bs, dstList));
          dst.setTran(dstTail, new CharClassState(bs));
        }
        else {
          // old sublist vertex
          dstTail = l->second;
        }

        if (src[dstList.front()]->IsMatch) {
          dst[dstTail]->IsMatch = true;
          dst[dstTail]->Label = src[dstList.front()]->Label;
        }

        dst.addEdge(dstHead, dstTail);
      }
    }
  }

  // collapse CharClassStates where possible
  // isn't necessary, but improves the GraphViz output
  for (uint32 i = 1; i < dst.numVertices(); ++i) {
    const Transition* t = dst[i]; 
    
    int32 first = -1;
    int32 last = -1;

    outBytes.reset();
    t->getBits(outBytes);

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
      Transition* r;
      if (first == last) {
        r = new LitState(first);
      }
      else {
        r = new RangeState(first, last);
      }

      r->IsMatch = t->IsMatch;
      r->Label = t->Label;
      dst.setTran(i, r);
      delete t;
    }
  }
}
