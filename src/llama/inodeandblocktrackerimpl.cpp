#include "inodeandblocktrackerimpl.h"

void InodeAndBlockTrackerImpl::setInodeRange(uint64_t begin, uint64_t end) {
  InumBegin = begin;
  InumEnd = end;
  // FIXME: Apparently "first_inum" is first in some way other than the usual
  // meaning of first, because it's 2 on DadeMurphy but we still see inode 0
  // there. WTF? For the time being, just waste a few bits at the start of the
  // encountered vector.
  //  InodeEncountered.resize(end - begin);
  InodeSeen.clear();
  InodeSeen.resize(end+1);
}

bool InodeAndBlockTrackerImpl::markInodeSeen(uint64_t inum) {
  // TODO: bounds checking? inum could be bogus
  if (InodeSeen[inum]) {
    return true;
  }
  else {
    InodeSeen[inum] = true;
    return false;
  }
}

void InodeAndBlockTrackerImpl::setBlockRange(uint64_t begin, uint64_t end) {
  // FIXME: unclear if we can rely on end - begin + 1 to be the actual count
  BlockBegin = begin;
  BlockEnd = end;
  AllocatedBlock.clear();
  AllocatedBlock.resize(end+1);
}

void InodeAndBlockTrackerImpl::markBlocksAllocated(uint64_t begin, uint64_t end) {
}

void InodeAndBlockTrackerImpl::markBlocksClaimed(uint64_t inum, uint64_t begin, uint64_t end) {
}
