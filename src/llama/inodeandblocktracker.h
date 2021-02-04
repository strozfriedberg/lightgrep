#pragma once

#include <cstdint>

class InodeAndBlockTracker {
public: 
  virtual ~InodeAndBlockTracker() {}

  virtual void setInodeRange(uint64_t begin, uint64_t end) = 0;

  virtual bool markInodeSeen(uint64_t inum) = 0;

  virtual void setBlockRange(uint64_t begin, uint64_t end) = 0;

  virtual void markBlocksAllocated(uint64_t begin, uint64_t end) = 0;

  virtual void markBlocksClaimed(uint64_t inum, uint64_t begin, uint64_t end) = 0;
};
