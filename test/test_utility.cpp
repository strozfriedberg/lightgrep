#include <scope/test.h>

#include "utility.h"
#include "states.h"

SCOPE_TEST(emptyFsm) {
  // what does it mean to have an empty FSM?
  boost::shared_ptr<StaticFSM> tight(convert_to_static(DynamicFSM()));
}

SCOPE_TEST(aFSM) {
  DynamicFSM fsm(2);
  std::pair<EdgeIdx, bool> edge(boost::add_edge(0, 1, fsm));
  SCOPE_ASSERT(edge.second);
  fsm[edge.first].reset(new LitState('a'));

  boost::shared_ptr<StaticFSM> tight(convert_to_static(fsm));
  SCOPE_ASSERT(tight);
  SCOPE_ASSERT_EQUAL(2u, tight->numStates());
  SCOPE_ASSERT_EQUAL(1u, tight->numEdges());
  StaticFSM::StateT s0 = tight->getFirstState();
  StaticFSM::EdgeRange edges = tight->getEdges(s0);
  uint32 numEdges = 0;
  SCOPE_ASSERT_EQUAL((uint64)(tight->getRawBuffer() + 4), (uint64)edges.first);
  SCOPE_ASSERT_EQUAL((uint64)(tight->getRawBuffer() + 12), (uint64)edges.second);
  for (StaticFSM::EdgeIt cur = edges.first; cur != edges.second; ++cur) {
    ++numEdges;
  }
  SCOPE_ASSERT_EQUAL(1u, numEdges);

  byte text = 'a';
  SCOPE_ASSERT(tight->allowed(&text, &text+1, *edges.first));
  text = 'b';
  SCOPE_ASSERT(!tight->allowed(&text, &text+1, *edges.first));

  edges = tight->getEdges(edges.first->StateOffset);
  SCOPE_ASSERT(edges.first == edges.second);
  SCOPE_ASSERT_EQUAL(0, (uint64)edges.first);
}
