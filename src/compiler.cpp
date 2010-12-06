#include "compiler.h"

#include "utility.h"
#include <stack>
#include <iostream>

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

      OutEdgeRange  oldOutRange(boost::out_edges(oldSource, addend));
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
            // the target NFA and the source NFA have diverged; copy
            // add this vertex from the source to the target

            target = boost::add_vertex(fsm);
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
