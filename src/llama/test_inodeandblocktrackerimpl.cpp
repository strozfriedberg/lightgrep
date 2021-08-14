#include <scope/test.h>

#include "inodeandblocktrackerimpl.h"

#include <stdexcept>

SCOPE_TEST(testInodeVisit) {
  InodeAndBlockTrackerImpl t;
  t.setInodeRange(0, 256);

  // none are seen yet
  for (int i = 0; i < 256; ++i) {
    SCOPE_ASSERT(!t.markInodeSeen(i));
  }

  // all are seen now
  for (int i = 0; i < 256; ++i) {
    SCOPE_ASSERT(t.markInodeSeen(i));
  }

  // reset (doesn't matter if its the same size)
  t.setInodeRange(0, 256);
  
  // none are seen once again
  for (int i = 0; i < 256; ++i) {
    SCOPE_ASSERT(!t.markInodeSeen(i));
  }
}

SCOPE_TEST(testInodeBadRange) {
  InodeAndBlockTrackerImpl t;
  SCOPE_EXPECT(t.setInodeRange(3, 1), std::runtime_error);
}

SCOPE_TEST(testInodeTooSmall) {
  InodeAndBlockTrackerImpl t;
  t.setInodeRange(1, 3);
  SCOPE_EXPECT(t.markInodeSeen(0), std::runtime_error);
}

SCOPE_TEST(testInodeTooLarge) {
  InodeAndBlockTrackerImpl t;
  t.setInodeRange(1, 3);
  SCOPE_EXPECT(t.markInodeSeen(3), std::runtime_error);
}

SCOPE_TEST(testBlocksAllocated) {
  InodeAndBlockTrackerImpl t;
  t.setBlockRange(0, 256);
}
