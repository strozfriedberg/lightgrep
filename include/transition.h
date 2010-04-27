#pragma once

#include "basic.h"

class Instruction;

class Transition {
public:
  virtual ~Transition() {}

  virtual const byte* allowed(const byte* beg, const byte* end) const = 0;
  virtual void getBits(ByteSet& bitvec) const = 0;
  virtual size_t objSize() const = 0;
  virtual Transition* clone(void* buffer) const = 0;
  virtual size_t numInstructions() const = 0;
  virtual bool   toInstruction(Instruction* addr) const = 0;
};
