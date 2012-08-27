#pragma once

#include "basic.h"
#include "fwd_pointers.h"
#include "searchhit.h"

class VmInterface {
public:
  virtual ~VmInterface() {}

  // In prog, numCheckedStates should be equal to the number + 1 for the reserved bit
  virtual void init(ProgramPtr prog) = 0;

  virtual void startsWith(const byte* const beg, const byte* const end, const uint64 startOffset, HitCallback hitFn, void* userData) = 0;
  virtual bool search(const byte* const beg, const byte* const end, const uint64 startOffset, HitCallback hitFn, void* userData) = 0;
  virtual void closeOut(HitCallback hitFn, void* userData) = 0;
  virtual void reset() = 0;

  #ifdef LBT_TRACE_ENABLED
  virtual void setDebugRange(uint64 beg, uint64 end) = 0;
  #endif

  static std::shared_ptr<VmInterface> create();
};
