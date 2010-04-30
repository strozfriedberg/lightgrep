#pragma once

#include "StaticFSM.h"

#include "SearchHit.h"

class DFASearch {
public:
  bool init(boost::shared_ptr<StaticFSM> fsm);

  void search(const byte* beg, const byte* end, uint64 logicalOffset, HitCallback& collector);

private:
  boost::shared_ptr<StaticFSM> Fsm;
};
