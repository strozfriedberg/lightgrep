#pragma once

#include "inodeandblocktracker.h"

class DummyTracker: public InodeAndBlockTracker {
public:
  virtual ~DummyTracker() {}

  virtual void setInodeRange(uint64_t begin, uint64_t end) {}

  virtual bool markInodeSeen(uint64_t inum) {}

  virtual void setBlockRange(uint64_t begin, uint64_t end) {}

  virtual void markBlocksAllocated(uint64_t inum, uint64_t begin, uint64_t end) {}

  virtual void markBlocksClaimed(uint64_t inum, uint64_t begin, uint64_t end) {}
};
