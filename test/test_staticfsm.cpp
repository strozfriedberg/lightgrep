#include <scope/test.h>

#include "StaticFSM.h"

SCOPE_TEST(testGetEdges) {
  uint32 num = 5;
  StaticFSM::EdgeRange edges = StaticFSM::getEdges((byte*)&num);
  SCOPE_ASSERT_EQUAL(((uint64)&num)+4, (uint64)edges.first);
  SCOPE_ASSERT_EQUAL(((uint64)&num) + 4 + (5 * sizeof(StaticEdge)), (uint64)edges.second);
}

SCOPE_TEST(testAllocate) {
  StaticFSM fsm;
  SCOPE_ASSERT_EQUAL(sizeof(uint32), fsm.allocate(0, 1, 0));
  SCOPE_ASSERT_EQUAL(1u, fsm.numStates());
  SCOPE_ASSERT_EQUAL(0u, fsm.numEdges());

  SCOPE_ASSERT_EQUAL(0u, fsm.allocate(0, 0, 1));
  SCOPE_ASSERT_EQUAL(0u, fsm.numStates());
  SCOPE_ASSERT_EQUAL(0u, fsm.numEdges());

  SCOPE_ASSERT_EQUAL(0u, fsm.allocate(0, 1, 1));
  SCOPE_ASSERT_EQUAL(0u, fsm.numStates());
  SCOPE_ASSERT_EQUAL(0u, fsm.numEdges());

  SCOPE_ASSERT_EQUAL((2 * sizeof(uint32)) + sizeof(StaticEdge), fsm.allocate(0, 2, 1));
  SCOPE_ASSERT_EQUAL(2u, fsm.numStates());
  SCOPE_ASSERT_EQUAL(1u, fsm.numEdges());

  SCOPE_ASSERT_EQUAL(57 + (2 * sizeof(uint32)) + sizeof(StaticEdge), fsm.allocate(57, 2, 1));
  SCOPE_ASSERT_EQUAL(2u, fsm.numStates());
  SCOPE_ASSERT_EQUAL(1u, fsm.numEdges());
}
