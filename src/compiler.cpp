#include "compiler.h"
#include "utility.h"

#include <iostream>
#include <set>
#include <stack>
#include <vector>

static const Graph::vertex NONE = 0xFFFFFFFF;
static const Graph::vertex UNLABELABLE = 0xFFFFFFFE;

void Compiler::mergeIntoFSM(Graph& dst, const Graph& src) {
  while (!States.empty()) {
    States.pop();
  }

  const uint32 numVs = src.numVertices();
  StateMap.assign(numVs, NONE);
  Visited.assign(numVs, false);

  Graph::vertex srcHead, dstHead, srcTail, dstTail;
  ByteSet srcBits, dstBits;

  States.push(StatePair(0, 0));
  while (!States.empty()) {
    dstHead = States.top().first;
    srcHead = States.top().second;
    States.pop();

    // skip if we've seen this source vertex already
    if (Visited[srcHead]) continue;


    Visited[srcHead] = true;

    // for each successor of the source vertex
    for (uint32 si = 0, di = 0; si < src.outDegree(srcHead); ++si) {
      srcTail = src.outVertex(srcHead, si);
      TransitionPtr srcTrans(src[srcTail]);

      srcBits.reset();
      srcTrans->getBits(srcBits);

      // try to match it with a successor of the destination vertex,
      // preserving the relative order of the source vertex's successors

      bool found = false;
      for ( ; di < dst.outDegree(dstHead); ++di) {
        dstTail = dst.outVertex(dstHead, di);
        TransitionPtr dstTrans(dst[dstTail]);

        dstBits.reset();
        dstTrans->getBits(dstBits);

        if (dstBits == srcBits &&
            dstTrans->Label == srcTrans->Label &&
            1 == dst.inDegree(dstTail) &&
            1 == src.inDegree(srcTail)) { 
          found = true;
          break;
        }
      }

      if (!found) {
        // match not found
        dstTail = StateMap[srcTail];

        if (dstTail == NONE) {
          // add a new vertex to the destination if the image of the source
          // tail vertex does not exist 
          dstTail = dst.addVertex();
          dst[dstTail] = srcTrans;
        }

        addNewEdge(dstHead, dstTail, dst);
      }
  
      StateMap[srcTail] = dstTail;
      States.push(StatePair(dstTail, srcTail));
    }

/*
    if (!Visited[dstHead]) {
      // std::cerr << "on state pair " << dstHead << ", " << srcHead << std::endl;
      Visited[dstHead] = true;

      for (uint32 i = 0; i < src.outDegree(dstHead); ++i) {
        dstTarget = src.outVertex(dstHead, i);

        if (StateMap[dstTarget] == NONE) {
          TransitionPtr srcTran = src[dstTarget];
          srcBits.reset();
          srcTran->getBits(srcBits);
          // std::cerr << "  dstTarget = " << dstTarget << " with transition " << tran->label() << std::endl;

          bool found = false;

          for (uint32 j = 0; j < dst.outDegree(srcHead); ++j) {
            srcTarget = dst.outVertex(srcHead, j);
            TransitionPtr dstTran = dst[srcTarget];
            dstBits.reset();
            dstTran->getBits(dstBits);
            // std::cerr << "    looking at merge state " << srcTarget << " with transition " << dstTran->label() << std::endl;
            if (dstBits == srcBits &&
                dstTran->Label == srcTran->Label &&
                1 == dst.inDegree(srcTarget) &&
                2 > src.inDegree(dstHead) &&
                2 > src.inDegree(dstTarget)) {
              // std::cerr << "    found equivalent state " << srcTarget << std::endl;
              found = true;
              break;
            }
          }

          if (!found) {
            // The destination NFA and the srcHead NFA have diverged.
            // Copy the tail node from the srcHead to the destination
            srcTarget = dst.addVertex();
            // std::cerr << "  creating new state " << srcTarget << std::endl;
            dst[srcTarget] = srcTran;
          }
          StateMap[dstTarget] = srcTarget;
        }
        else {
          srcTarget = StateMap[dstTarget];
        }
        // std::cerr << "  srcTarget = " << srcTarget << std::endl;

        addNewEdge(srcHead, srcTarget, dst);
        States.push(StatePair(dstTarget, srcTarget));
      }
    }
*/
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
