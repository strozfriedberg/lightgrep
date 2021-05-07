#include "inodeandblocktrackerimpl.h"
#include "throw.h"

#include <iostream>

void InodeAndBlockTrackerImpl::dump() const {
  std::cerr << "a {\n";
  for (const auto& i : AllocatedBlock) {
    std::cerr << " [" << i.lower() << ',' << i.upper() << "),\n";
  }
  std::cerr << "}\n";

  std::cerr << "c {\n";
  for (const auto& p : ClaimedBlock) {
    std::cerr << " [" << p.first.lower() << ',' << p.first.upper() << "): {";
    for (const auto& claimant : p.second) {
      std::cerr << claimant << ',';
    }
    std::cerr << "},\n";
  }
  std::cerr << '}' << std::endl;
}

InodeAndBlockTrackerImpl::~InodeAndBlockTrackerImpl() {
  dump();
}

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
//  InodeSeen.resize(end);
  std::cerr << "InodeSeen.size() == " << end << std::endl;
}

bool InodeAndBlockTrackerImpl::markInodeSeen(uint64_t inum) {
  THROW_IF(inum < InumBegin, "inum " << inum << " < " << InumBegin << " InumBegin");
  THROW_IF(inum >= InumEnd, "inum " << inum << " >= " << InumEnd << " InumEnd");
//  const bool ret = InodeSeen[inum];
//  InodeSeen[inum] = true;
  const bool ret = InodeSeen.find(inum) != InodeSeen.end();
  InodeSeen.insert({inum, inum + 1});
  return ret;
}

void InodeAndBlockTrackerImpl::setBlockRange(uint64_t begin, uint64_t end) {
  THROW_IF(begin > end, "bad range [" << begin << ',' << end << ')');

  dump();
  BlockBegin = begin;
  BlockEnd = end;
  // FIXME: unclear if we can rely on end - begin + 1 to be the actual count
  AllocatedBlock.clear();
  ClaimedBlock.clear();
//  AllocatedBlock.resize(end+1);
}

void InodeAndBlockTrackerImpl::markBlocksAllocated(uint64_t inum, uint64_t begin, uint64_t end) {
  const boost::icl::interval<uint64_t>::type i(begin, end);
  AllocatedBlock.insert(i);
  ClaimedBlock.erase(i);
}

void InodeAndBlockTrackerImpl::markBlocksClaimed(uint64_t inum, uint64_t begin, uint64_t end) {
  boost::icl::interval_set<uint64_t> not_alloc(
    boost::icl::interval<uint64_t>::type(begin, end)
  );
  not_alloc -= AllocatedBlock;

  for (const auto& seg : not_alloc) {
    ClaimedBlock.insert({seg, std::set<uint64_t>{inum}});
  }
}
