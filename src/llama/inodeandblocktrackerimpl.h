#pragma once

#include "inodeandblocktracker.h"

#include <vector>

class InodeAndBlockTrackerImpl: public InodeAndBlockTracker {
public:
  virtual ~InodeAndBlockTrackerImpl() {}

  virtual void setInodeRange(uint64_t begin, uint64_t end);

  virtual bool markInodeSeen(uint64_t inum);

  virtual void setBlockRange(uint64_t begin, uint64_t end);

  virtual void markBlocksAllocated(uint64_t begin, uint64_t end);

  virtual void markBlocksClaimed(uint64_t inum, uint64_t begin, uint64_t end);

//  virtual void handleExtent(const TSK_FS_ATTR_RUN& run);

private:
  std::vector<bool> InodeSeen;

  uint64_t InumBegin,
           InumEnd;

  std::vector<bool> AllocatedBlock;

  uint64_t BlockBegin,
           BlockEnd;
};
