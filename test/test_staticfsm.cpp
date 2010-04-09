#include <scope/test.h>

#include "StaticFSM.h"

SCOPE_TEST(testGetEdges) {
  uint32 num = 5;
  StaticFSM::EdgeRange edges = StaticFSM::getEdges((byte*)&num);
  SCOPE_ASSERT_EQUAL(((uint64)&num)+4, (uint64)edges.first);
  SCOPE_ASSERT_EQUAL(((uint64)&num) + 4 + (5 * sizeof(StaticEdge)), (uint64)edges.second);
}
