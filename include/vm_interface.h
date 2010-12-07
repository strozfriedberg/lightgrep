#pragma once

#include "basic.h"
#include "program.h"
#include "thread.h"
#include "SearchHit.h"

class VmInterface {
public:
  virtual ~VmInterface() {}

  // In prog, numCheckedStates should be equal to the number + 1 for the reserved bit
  virtual void init(ProgramPtr prog) = 0;

  virtual bool search(const byte* beg, const byte* end, uint64 startOffset, HitCallback& hitFn) = 0;
  virtual void reset() = 0;

  virtual void setDebugRange(uint64 beg, uint64 end) = 0;

  static boost::shared_ptr<VmInterface> create();
};
