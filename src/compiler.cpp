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

void resizeBranchVec(std::vector< Compiler::Branch >& vec, uint32 size) {
  for (std::vector< Compiler::Branch >::iterator it(vec.begin()); it != vec.end(); ++it) {
    it->clear();
  }
  vec.resize(size);
}

void Compiler::reduceRange(const Graph& dst, Graph::vertex dstHead, const Branch& sbranch, uint32& lb, uint32& ub) {
  for (uint32 di = lb; di < ub; ++di) {
    // get dstTail vertex and its preimages
    Graph::vertex dstTail = dst.outVertex(dstHead, di);
    const std::vector<Graph::vertex>& preimages(Dst2Src[dstTail]);

    // compare src branch to the branch of each preimage
    std::vector<Graph::vertex>::const_iterator i(preimages.begin());
    for ( ; i != preimages.end(); ++i) {
      const Branch& dbranch = BranchMap[*i];
      if (std::lexicographical_compare(dbranch.begin(), dbranch.end(),
                                       sbranch.begin(), sbranch.end())) {
        // dst branch < src branch, advance the lower bound
        lb = di;
      }
      else {
        // src branch >= dst branch, set upper bound and stop
        ub = di;
        break;
      }
    }
  }
}

const uint32 NOLABEL = std::numeric_limits<uint32>::max();

Compiler::StatePair Compiler::processChild(const Graph& src, Graph& dst, uint32 si, Graph::vertex srcHead, Graph::vertex dstHead, uint32& lb) {
  const Graph::vertex srcTail = src.outVertex(srcHead, si);
  Graph::vertex dstTail = Src2Dst[srcTail];
  if (dstTail != NONE) {
    dst.addEdge(dstHead, dstTail);
  }
  else {
    const Transition* srcTrans(src[srcTail]);

    ByteSet srcBits;
    srcTrans->getBits(srcBits);

    BranchMap[srcTail] = BranchMap[srcHead];
    BranchMap[srcTail].push_back(si);
    const Branch& sbranch(BranchMap[srcTail]);

    #ifdef LBT_TRACE_ENABLED
    std::cerr << "trying to match " << srcTail << " on branch ";
    std::copy(sbranch.begin(), sbranch.end(),
              std::ostream_iterator<Graph::vertex>(std::cerr, "."));
    std::cerr << std::endl;
    #endif

    // try to match it with a successor of the destination vertex,
    // preserving the relative order of the source vertex's successors

    // find dstTail range to which we could map srcTail, by branch order
    uint32 ub = dst.outDegree(dstHead);

    reduceRange(dst, dstHead, sbranch, lb, ub);

    bool found = false;

    ByteSet dstBits;

    for (uint32 di = lb; di < ub; ++di) {
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

      dst.addEdge(dstHead, dstTail);

      #ifdef LBT_TRACE_ENABLED
      std::cerr << "added edge " << dstHead << " -> " << dstTail << std::endl;
      #endif
    }
  }

  return StatePair(dstTail, srcTail);
}

void Compiler::mergeIntoFSM(Graph& dst, const Graph& src) {
  while (!States.empty()) {
    States.pop();
  }

  const uint32 srcSize = src.numVertices();
  const uint32 dstSize = dst.numVertices();
  Src2Dst.assign(srcSize, NONE);
  resizeBranchVec(Dst2Src, srcSize + dstSize);
  resizeBranchVec(BranchMap, srcSize);
//  Dst2Src.assign(srcSize + dstSize, std::vector<Graph::vertex>());
//  BranchMap.assign(srcSize, Branch());
  Visited.assign(srcSize, false);

  Graph::vertex srcHead, dstHead, srcTail, dstTail;
  ByteSet srcBits, dstBits;

  States.push(StatePair(0, 0));
  while (!States.empty()) {
    dstHead = States.front().first;
    srcHead = States.front().second;
    States.pop();

    #ifdef LBT_TRACE_ENABLED
    std::cerr << "popped (" << dstHead << ',' << srcHead << ')' << std::endl;
    #endif

    // skip if we've seen this source vertex already
    if (Visited[srcHead]) {
      #ifdef LBT_TRACE_ENABLED
      std::cerr << "already seen " << srcHead << ", skipping" << std::endl;
      #endif
      continue;
    }

    Visited[srcHead] = true;

    // for each successor of the source vertex
    for (uint32 si = 0, lb = 0; si < src.outDegree(srcHead); ++si) {
      StatePair s(processChild(src, dst, si, srcHead, dstHead, lb));
      srcTail = s.second;
      dstTail = s.first;

      Src2Dst[srcTail] = dstTail;
      Dst2Src[dstTail].push_back(srcTail);
      States.push(s);

      #ifdef LBT_TRACE_ENABLED
      std::cerr << "pushed (" << dstTail << ',' << srcTail << ')' << std::endl;
      #endif
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
