#pragma once

#include "inodeandblocktracker.h"

#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_set.hpp>

//#include <vector>
#include <set>

class InodeAndBlockTrackerImpl: public InodeAndBlockTracker {
public:
  virtual ~InodeAndBlockTrackerImpl();

  virtual void setInodeRange(uint64_t begin, uint64_t end);

  virtual bool markInodeSeen(uint64_t inum);

  virtual void setBlockRange(uint64_t begin, uint64_t end);

  virtual void markBlocksAllocated(uint64_t inum, uint64_t begin, uint64_t end);

  virtual void markBlocksClaimed(uint64_t inum, uint64_t begin, uint64_t end);

//  virtual void handleExtent(const TSK_FS_ATTR_RUN& run);

private:
  void dump() const;

//  std::vector<bool> InodeSeen;
  boost::icl::interval_set<uint64_t> InodeSeen;

  uint64_t InumBegin,
           InumEnd;

  uint64_t BlockBegin,
           BlockEnd;

  boost::icl::interval_set<uint64_t> AllocatedBlock;
  boost::icl::interval_map<uint64_t, std::set<uint64_t>> ClaimedBlock;
};
