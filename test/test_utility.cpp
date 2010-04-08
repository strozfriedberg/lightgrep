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
}
