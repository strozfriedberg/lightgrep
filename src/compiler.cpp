#include "compiler.h"
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

Compiler::StatePair Compiler::processChild(const Graph& src, Graph& dst, uint32 si, Graph::vertex srcHead, Graph::vertex dstHead) {
  const Graph::vertex srcTail = src.outVertex(srcHead, si);

  Graph::vertex dstTail = Src2Dst[srcTail];
  uint32 di = 0;

  if (dstTail != NONE) {
    for ( ; di < dst.outDegree(dstHead); ++di) {
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

    for (di = DstPos[dstHead]; di < dst.outDegree(dstHead); ++di) {
      dstTail = dst.outVertex(dstHead, di);
      Transition* dstTrans(dst[dstTail]);

      dstBits.reset();
      dstTrans->getBits(dstBits);

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

      if (dstBits == srcBits &&
          dstTrans->Label == srcTrans->Label &&
          (dstTrans->Label == NOLABEL ||
            (0 == src.outDegree(srcTail) && 0 == dst.outDegree(dstTail))) &&
          1 == dst.inDegree(dstTail) &&
          (Dst2Src[dstTail].empty() ||
            1 == src.inDegree(Dst2Src[dstTail].front())) &&
          1 == src.inDegree(srcTail)) {
        found = true;

        #ifdef LBT_TRACE_ENABLED
        std::cerr << "matched " << srcTail << " with " << dstTail << std::endl;
        #endif
        break;
      }
    }

    if (!found) {
      // match not found

      // add a new vertex to the destination if the image of the source
      // tail vertex cannot be matched
      dstTail = dst.addVertex();
      dst.setTran(dstTail, srcTrans->clone());

      #ifdef LBT_TRACE_ENABLED
      std::cerr << "added new vertex " << dstTail << " for "
                                       << srcTail << std::endl;
      #endif

      #ifdef LBT_TRACE_ENABLED
      std::cerr << "added edge " << dstHead << " -> " << dstTail << std::endl;
      #endif
    }
  }

  dst.addEdge(dstHead, dstTail);
  DstPos[dstHead] = di + 1;
  return StatePair(dstTail, srcTail);
}

void Compiler::mergeIntoFSM(Graph& dst, const Graph& src) {
  while (!States.empty()) {
    States.pop();
  }

  const uint32 srcSize = src.numVertices();
  const uint32 dstSize = dst.numVertices();
  Src2Dst.assign(srcSize, NONE);

  for (std::vector< std::vector<Graph::vertex> >::iterator i(Dst2Src.begin()); i != Dst2Src.end(); ++i) {
    i->clear();
  }
  Dst2Src.resize(dstSize + srcSize);

  Visited.clear();
  DstPos.assign(dstSize + srcSize, 0);

  Graph::vertex srcHead, dstHead, srcTail, dstTail;
  ByteSet srcBits, dstBits;

  Src2Dst[0] = 0;

  // push all children of the initial state in the source
  for (int32 i = src.outDegree(0) - 1; i >= 0; --i) {
    States.push(StatePair(0, src.outVertex(0, i)));
  }

  while (!States.empty()) {
    StatePair& p(States.top());
    srcHead = p.first;
    srcTail = p.second;
    States.pop();

    dstHead = Src2Dst[srcHead];

    // skip if we've seen this source vertex already
    if (Visited.find(p) != Visited.end()) {
      continue;
    }

    Visited.insert(p);

    uint32 si = 0;
    for ( ; si < src.outDegree(srcHead); ++si) {
      if (src.outVertex(srcHead, si) == srcTail) {
        break;
      }
    }

    StatePair s(processChild(src, dst, si, srcHead, dstHead));
    srcTail = s.second;
    dstTail = s.first;

    Src2Dst[srcTail] = dstTail;
    Dst2Src[dstTail].push_back(srcTail);

    for (int32 i = src.outDegree(srcTail) - 1; i >= 0; --i) {
      States.push(StatePair(srcTail, src.outVertex(srcTail, i)));
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

  std::stack<Graph::vertex,
             std::vector<Graph::vertex> > next;

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
