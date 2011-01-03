#include "compiler.h"

#include "utility.h"
#include <stack>
#include <iostream>

#include <boost/bind.hpp>

static const DynamicFSM::vertex_descriptor UNALLOCATED = 0xffffffff;
static const DynamicFSM::vertex_descriptor UNLABELABLE = 0xfffffffe;

void Compiler::mergeIntoFSM(DynamicFSM& fsm, const DynamicFSM& addend, uint32 keyIdx) {
  ByteSet tranBits,
          edgeBits;

  while (!States.empty()) {
    States.pop();
  }
  uint32 numVs = addend.numVertices();
  StateMap.assign(numVs, UNALLOCATED);
  Visited.assign(numVs, false);

  DynamicFSM::vertex_descriptor oldSource,
                                source,
                                oldTarget,
                                target;

  States.push(StatePair(0, 0));
  while (!States.empty()) {
    oldSource = States.top().first;
    source    = States.top().second;
    States.pop();
    if (!Visited[oldSource]) {
      // std::cerr << "on state pair " << oldSource << ", " << source << std::endl;
      Visited[oldSource] = true;

      const DynamicFSM::AdjacentList& oldOutVs(addend.outVertices(oldSource));
      for (DynamicFSM::const_iterator it(oldOutVs.begin()); it != oldOutVs.end(); ++it) {
        oldTarget = *it;
        if (StateMap[oldTarget] == UNALLOCATED) {
          TransitionPtr tran = addend[oldTarget];
          tranBits.reset();
          tran->getBits(tranBits);
          // std::cerr << "  oldTarget = " << oldTarget << " with transition " << tran->label() << std::endl;

          bool found = false;

          const DynamicFSM::AdjacentList& outVs(fsm.outVertices(source));
          for (DynamicFSM::const_iterator curEdge(outVs.begin()); curEdge != outVs.end(); ++curEdge) {
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

void Compiler::labelGuardStates(DynamicFSM& fsm) {
  using namespace boost;

  std::vector<bool> visited(fsm.numVertices());

  
  DynamicFSM::const_iterator mi_end = fsm.end();
  for (DynamicFSM::const_iterator mi = fsm.begin(); mi != mi_end; ++mi) {
    DynamicFSM::vertex_descriptor m = *mi;

    // skip non-match vertices
    if (!fsm[m] || !fsm[m]->IsMatch) continue;

    const unsigned int label = fsm[m]->Label;
    
    // walk guard label(s) back from this match state
    std::stack<DynamicFSM::vertex_descriptor,
               std::vector<DynamicFSM::vertex_descriptor> > next;
    
    visited.assign(fsm.numVertices(), false);

    next.push(m);
    while (!next.empty()) {
      DynamicFSM::vertex_descriptor t = next.top();
      next.pop();
      visited[t] = true;

      bool unmark = true;
      DynamicFSM::const_iterator ie_end(fsm.inVertices(t).end());
      for (DynamicFSM::const_iterator ie = fsm.inVertices(t).begin(); ie != ie_end; ++ie) {
        DynamicFSM::vertex_descriptor h = *ie;

        // skip head if we've already seen it
        if (visited[h]) continue;
          
        if (!fsm[h]) {
          // head is the initial state
          unmark = false;
        }
        else if (fsm[h]->Label == UNALLOCATED) {
          // mark head with our label 
          fsm[h]->Label = label;

          // visit head next
          next.push(h);
        }
        else if (fsm[h]->Label == label) {
          // head has our own label, do nothing
        }
        else if (fsm[h]->Label == UNLABELABLE) {
          // head has already been backtracked from
          unmark = false;
        }
        else {
          // head has a different label

          // unlabel head
          const unsigned int hlabel = fsm[h]->Label;
          fsm[h]->Label = UNALLOCATED;

          // advance head's label to all of its unlabeled children except tail
          DynamicFSM::const_iterator oe_end(fsm.outVertices(h).end());
          for (DynamicFSM::const_iterator oe = fsm.outVertices(h).begin(); oe != oe_end; ++oe) {
            DynamicFSM::vertex_descriptor c = *oe;
            if (c != t && fsm[c]->Label == UNALLOCATED) {
              fsm[c]->Label = hlabel;
            }
          }

          unmark = false;

          // mark head as unlabelable
          fsm[h]->Label = UNLABELABLE;
        }
      }

      if (unmark) {
        // Every head is now marked with the label, so we may safely
        // unmark tail.
        fsm[t]->Label = UNALLOCATED;
      }
    }
  }

  // mark every UNLABELABLE vertex as UNALLOCATED
  for (DynamicFSM::const_iterator mi = fsm.begin(); mi != mi_end; ++mi) {
    DynamicFSM::vertex_descriptor m = *mi;
    if (fsm[m] && fsm[m]->Label == UNLABELABLE) {
      fsm[m]->Label = UNALLOCATED;
    }
  }
}
