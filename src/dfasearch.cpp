#include "dfasearch.h"

#include <iostream>

bool DFASearch::init(boost::shared_ptr<StaticFSM> fsm) {
  Fsm = fsm;
  return Fsm;
}

void match(const byte* beg, const byte* end, StaticFSM& fsm, StaticFSM::StateT curState, uint64 start, HitCallback& collector) {
  StaticFSM::EdgeRange edges = fsm.getEdges(curState);
  StaticFSM::EdgeIt curEdge;
  // if (edges.first == edges.second) {
  //   collect.collect() // for one-byte search hits
  // }
  bool good;
  for (const byte* cur = beg + 1; cur != end; ++cur) {
    good = false;
    // std::cout << "at " << (cur - beg) << ", byte is " << *cur << "; curState = " << curState << "; numEdges = " << edges.second - edges.first << std::endl;
    for (curEdge = edges.first; curEdge != edges.second; ++curEdge) {
      if (fsm.allowed(cur, end, *curEdge)) {
        curState = curEdge->StateOffset;
        edges = fsm.getEdges(curState);
        if (edges.first == edges.second) {
          collector.collect(SearchHit(start, cur - beg + 1, 0));
          return;
        }
        good = true;
        break;
      }
    }
    if (!good) {
      // std::cout << "exiting dfa at " << start + (cur - beg + 1) << std::endl;
      break;
    }
  }
}

void DFASearch::search(const byte* beg, const byte* end, uint64 logicalOffset, HitCallback& collector) {
  StaticFSM::StateT s0 = Fsm->getFirstState();
  StaticFSM::EdgeRange edges = Fsm->getEdges(s0);
  StaticFSM::EdgeIt curEdge;
  for (const byte* cur = beg; cur != end; ++cur) {
    for (curEdge = edges.first; curEdge != edges.second; ++curEdge) {
      if (Fsm->allowed(cur, end, *curEdge)) {
        // std::cout << "first state match on " << *cur << " at " << logicalOffset << std::endl;
        match(cur, end, *Fsm, curEdge->StateOffset, logicalOffset, collector);
      }
    }
    ++logicalOffset;
  }
}
