#include "compiler.h"

#include "utility.h"
#include <stack>
#include <iostream>

#include <boost/bind.hpp>

static const DynamicFSM::vertex_descriptor UNALLOCATED = 0xffffffff;

void Compiler::mergeIntoFSM(DynamicFSM& fsm, const DynamicFSM& addend, uint32 keyIdx) {
  ByteSet tranBits,
          edgeBits;

  while (!States.empty()) {
    States.pop();
  }
  StateMap.assign(boost::num_vertices(addend), UNALLOCATED);
  Visited.assign(boost::num_vertices(addend), false);

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

      OutEdgeRange oldOutRange(boost::out_edges(oldSource, addend));
      for (OutEdgeIt e(oldOutRange.first); e != oldOutRange.second; ++e) {
        oldTarget = boost::target(*e, addend);
        if (StateMap[oldTarget] == UNALLOCATED) {
          TransitionPtr tran = addend[oldTarget];
          tranBits.reset();
          tran->getBits(tranBits);
          // std::cerr << "  oldTarget = " << oldTarget << " with transition " << tran->label() << std::endl;

          bool found = false;

          OutEdgeRange outRange(boost::out_edges(source, fsm)); // done every time to avoid iterator invalidation
          for (OutEdgeIt curEdge(outRange.first); curEdge != outRange.second; ++curEdge) {
            target = boost::target(*curEdge, fsm);
            TransitionPtr edgeTran = fsm[target];
            edgeBits.reset();
            edgeTran->getBits(edgeBits);
            // std::cerr << "    looking at merge state " << target << " with transition " << edgeTran->label() << std::endl;
            if (edgeBits == tranBits &&
                (edgeTran->Label == UNALLOCATED || edgeTran->Label == keyIdx) &&
                1 == boost::in_degree(target, fsm) &&
                2 > boost::in_degree(oldSource, addend) &&
                2 > boost::in_degree(oldTarget, addend)) {
              // std::cerr << "    found equivalent state " << target << std::endl;
              found = true;
              break;
            }
          }

          if (!found) {
            // The destination NFA and the source NFA have diverged.
/*          
            // If the head node in the target NFA had a guard label,
            // advance it to that node's children.
            if (fsm[source] && !fsm[source]->IsMatch && 
                fsm[source]->Label != UNALLOCATED) {
              OutEdgeRange oer(boost::out_edges(source, fsm));
              for (OutEdgeIt oe(oer.first); oe != oer.second; ++oe) {
                fsm[boost::target(*oe, fsm)]->Label = fsm[source]->Label;
              }
              fsm[source]->Label = UNALLOCATED;
            }
*/

            // Copy the tail node from the source to the destination
            target = boost::add_vertex(fsm);
            // std::cerr << "  creating new state " << target << std::endl;
            fsm[target] = tran;

/*
            // If the head node in the addend NFA had a guard label,
            // advance it to the new node in the target NFA.
            if (addend[oldSource] && !addend[oldSource]->IsMatch &&
                addend[oldSource]->Label != UNALLOCATED) {
              fsm[target]->Label = keyIdx; 
            }
*/
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

  std::vector<bool> visited(num_vertices(fsm));

  DynamicFSM::vertex_iterator mi, mi_end;
  for (tie(mi, mi_end) = vertices(fsm); mi != mi_end; ++mi) {
    DynamicFSM::vertex_descriptor m = *mi;

    // skip non-match vertices
    if (!fsm[m] || !fsm[m]->IsMatch) continue;

    const unsigned int label = fsm[m]->Label;
    
    // walk guard label(s) back from this match state
    std::stack<DynamicFSM::vertex_descriptor,
               std::vector<DynamicFSM::vertex_descriptor> > next;
    
    visited.assign(num_vertices(fsm), false);

    next.push(m);
    while (!next.empty()) {
      DynamicFSM::vertex_descriptor t = next.top();
      next.pop();
      visited[t] = true;

      bool unmark = true;
      DynamicFSM::in_edge_iterator ie, ie_end;
      for (tie(ie, ie_end) = in_edges(t, fsm); ie != ie_end; ++ie) {
        DynamicFSM::vertex_descriptor h = source(*ie, fsm);

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
        else {
          // head has a different label

          // unlabel head
          const unsigned int hlabel = fsm[h]->Label;
          fsm[h]->Label = UNALLOCATED;

          // advance head's label to all of its children except tail
          DynamicFSM::out_edge_iterator oe, oe_end;
          for (tie(oe, oe_end) = out_edges(h, fsm); oe != oe_end; ++oe) {
            DynamicFSM::vertex_descriptor c = target(*oe, fsm);
            if (c == t) continue;
            fsm[c]->Label = hlabel; 
          }

          unmark = false;
        }
      }

      if (unmark) {
        // Every head is now marked with the label, so we may safely
        // unmark tail.
        fsm[t]->Label = UNALLOCATED;
      }
    }

    // Relabel match state in case the search unlabeled it
    fsm[m]->Label = label; 
  }
}
