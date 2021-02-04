#include "inodeandblocktrackerimpl.h"
#include "throw.h"

void InodeAndBlockTrackerImpl::setInodeRange(uint64_t begin, uint64_t end) {
  THROW_IF(begin > end, "bad range [" << begin << ',' << end << ')');
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
  THROW_IF(inum < InumBegin, "inum " << inum << " < " << InumBegin << " InumBegin");
  THROW_IF(inum >= InumEnd, "inum " << inum << " >= " << InumEnd << " InumEnd");
  const bool ret = InodeSeen[inum];
  InodeSeen[inum] = true;
  return ret;
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
