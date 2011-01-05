#include "compiler.h"
#include "utility.h"

#include <iostream>
#include <set>
#include <stack>
#include <vector>

static const Graph::vertex_descriptor UNALLOCATED = 0xffffffff;
static const Graph::vertex_descriptor UNLABELABLE = 0xfffffffe;

void Compiler::mergeIntoFSM(Graph& fsm, const Graph& addend, uint32 keyIdx) {
  ByteSet tranBits,
          edgeBits;

  while (!States.empty()) {
    States.pop();
  }
  uint32 numVs = addend.numVertices();
  StateMap.assign(numVs, UNALLOCATED);
  Visited.assign(numVs, false);

  Graph::vertex_descriptor oldSource,
                                source,
                                oldTarget,
                                target = Graph::BAD;

  States.push(StatePair(0, 0));
  while (!States.empty()) {
    oldSource = States.top().first;
    source    = States.top().second;
    States.pop();
    if (!Visited[oldSource]) {
      // std::cerr << "on state pair " << oldSource << ", " << source << std::endl;
      Visited[oldSource] = true;

      for (Graph::const_iterator it(addend.outVerticesBegin(oldSource)); it != addend.outVerticesEnd(oldSource); ++it) {
        oldTarget = *it;
        if (StateMap[oldTarget] == UNALLOCATED) {
          TransitionPtr tran = addend[oldTarget];
          tranBits.reset();
          tran->getBits(tranBits);
          // std::cerr << "  oldTarget = " << oldTarget << " with transition " << tran->label() << std::endl;

          bool found = false;

          for (Graph::const_iterator curEdge(fsm.outVerticesBegin(source)); curEdge != fsm.outVerticesEnd(source); ++curEdge) {
            target = *curEdge;
            TransitionPtr edgeTran = fsm[target];
            edgeBits.reset();
            edgeTran->getBits(edgeBits);
            // std::cerr << "    looking at merge state " << target << " with transition " << edgeTran->label() << std::endl;
            if (edgeBits == tranBits &&
                (edgeTran->Label == UNALLOCATED || edgeTran->Label == keyIdx) &&
                1 == fsm.inDegree(target) &&
                2 > addend.inDegree(oldSource) &&
                2 > addend.inDegree(oldTarget)) {
              // std::cerr << "    found equivalent state " << target << std::endl;
              found = true;
              break;
            }
          }

          if (!found) {
            // The destination NFA and the source NFA have diverged.
            // Copy the tail node from the source to the destination
            target = fsm.addVertex();
            // std::cerr << "  creating new state " << target << std::endl;
            fsm[target] = tran;
          }
          StateMap[oldTarget] = target;
        }
        else {
          target = StateMap[oldTarget];
        }
        // std::cerr << "  target = " << target << std::endl;
        
        addNewEdge(source, target, fsm);
        States.push(StatePair(oldTarget, target));
      }
    }
  }
}

void Compiler::labelGuardStates(Graph& fsm) {
  propagateMatchLabels(fsm);
  removeNonMinimalLabels(fsm);
}

void Compiler::propagateMatchLabels(Graph& fsm) {
  uint32 i = 0;

  Graph::const_iterator mi_end(fsm.end());
  for (Graph::const_iterator mi(fsm.begin()); mi != mi_end; ++mi) {
    Graph::vertex_descriptor m = *mi;

    // skip non-match vertices
    if (!fsm[m] || !fsm[m]->IsMatch) continue;

    if (++i % 10000 == 0) {
      std::cerr << "handled " << i << " labeled vertices" << std::endl;
    }

    const unsigned int label = fsm[m]->Label;
    
    // walk label back from this match state to all of its ancestors
    // which have no other match-state descendants

    std::stack<Graph::vertex_descriptor,
               std::vector<Graph::vertex_descriptor> > next;
    
    next.push(m);

    while (!next.empty()) {
      Graph::vertex_descriptor t = next.top();
      next.pop();
      
      // check each parent of the current state
      Graph::const_iterator ie(fsm.inVerticesBegin(t));
      Graph::const_iterator ie_end(fsm.inVerticesEnd(t));
      for ( ; ie != ie_end; ++ie) {
        Graph::vertex_descriptor h = *ie;
        
        if (!fsm[h]) {
          // Skip the initial state.
          continue;
        }
        else if (fsm[h]->Label == UNALLOCATED) {
          // Mark unmarked parents with our label and walk back to them.
          fsm[h]->Label = label;
          next.push(h);
        }
        else if (fsm[h]->Label == UNLABELABLE) {
          // This parent is already marked as an ancestor of multiple match
          // states; all paths from it back to the root are already marked
          // as unlabelable, so we don't need to walk back from it.
        }
        else if (fsm[h]->Label == label) {
          // This parent has our label, which means we've already walked
          // back through it.
        }
        else {
          // This parent has the label of some other match state. Mark it
          // and all of its ancestors unlabelable.
          std::stack<Graph::vertex_descriptor,
               std::vector<Graph::vertex_descriptor> > unext;

          unext.push(h);

          while (!unext.empty()) {
            Graph::vertex_descriptor u = unext.top();
            unext.pop();

            fsm[u]->Label = UNLABELABLE;

            Graph::const_iterator ue(fsm.inVerticesBegin(u));
            Graph::const_iterator ue_end(fsm.inVerticesEnd(u));
            for ( ; ue != ue_end; ++ue) {
              Graph::vertex_descriptor uh = *ue;
              if (fsm[uh] && fsm[uh]->Label != UNLABELABLE) {
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

void Compiler::removeNonMinimalLabels(Graph& fsm) {
  // Make a list of all tails of edges where the head is an ancestor of
  // multiple match states, but the tail is an ancestor of only one.
  std::vector<bool> visited(fsm.numVertices());

  std::set<Graph::vertex_descriptor> heads;

  std::stack<Graph::vertex_descriptor,
             std::vector<Graph::vertex_descriptor> > next;

  next.push(0);
  visited[0] = true;

  while (!next.empty()) {
    Graph::vertex_descriptor h = next.top();
    next.pop();

    Graph::const_iterator vi(fsm.outVerticesBegin(h));
    Graph::const_iterator vi_end(fsm.outVerticesEnd(h));
    for ( ; vi != vi_end; ++vi) {
      Graph::vertex_descriptor t = *vi;

      if (visited[t] || !fsm[t]) continue; 

      if (fsm[t]->Label == UNLABELABLE) {
        fsm[t]->Label = UNALLOCATED;
        next.push(t);
      }
      else {
        heads.insert(t);
      }

      visited[t] = true;
    }
  }

  // Push all of the minimal guard states we found back onto the stack.
  for (std::set<Graph::vertex_descriptor>::const_iterator vi(heads.begin()); vi != heads.end(); ++vi) {
    next.push(*vi);
  }

  // Unlabel every remaining node not in heads.
  while (!next.empty()) {
    Graph::vertex_descriptor h = next.top();
    next.pop();

    Graph::const_iterator vi(fsm.outVerticesBegin(h));
    Graph::const_iterator vi_end(fsm.outVerticesEnd(h));
    for ( ; vi != vi_end; ++vi) {
      Graph::vertex_descriptor t = *vi;

      if (visited[t] || !fsm[t]) continue; 

      // NB: Any node which should be labeled, we've already visited,
      // so we can unlabel everything we reach this way.
      fsm[t]->Label = UNALLOCATED;
      next.push(t);
      visited[t] = true;
    }
  }
}
