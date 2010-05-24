#pragma once

#include "basic.h"

class Instruction;

#pragma pack(1)
class Transition {
public:
  Transition(): IsMatch(false), Label(0xffffffff) {}
  Transition(uint32 lbl): IsMatch(false), Label(lbl) {}
  virtual ~Transition() {}

  virtual const byte* allowed(const byte* beg, const byte* end) const = 0;
  virtual void getBits(ByteSet& bitvec) const = 0;
  virtual size_t objSize() const = 0;
  virtual Transition* clone(void* buffer) const = 0;
  virtual size_t numInstructions() const = 0;
  virtual bool   toInstruction(Instruction* addr) const = 0;
  virtual std::string label() const = 0;

  bool   IsMatch;
  uint32 Label;
};
#pragma pack(pop)
