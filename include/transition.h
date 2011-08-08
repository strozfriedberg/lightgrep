#pragma once

#include "basic.h"

class Instruction;

class Transition {
public:
  virtual ~Transition() {}

  virtual const byte* allowed(const byte* beg, const byte* end) const = 0;
  virtual void getBits(ByteSet& bitvec) const = 0;
  virtual size_t objSize() const = 0;
  virtual Transition* clone(void* buffer = 0) const = 0;
  virtual size_t numInstructions() const = 0;
  virtual bool   toInstruction(Instruction* addr) const = 0;
  virtual std::string label() const = 0;

  bool   IsMatch;
  uint32 Label;

protected:
  Transition(): IsMatch(false), Label(0xffffffff) {}
  Transition(uint32 lbl): IsMatch(false), Label(lbl) {}
  Transition(uint32 lbl, bool isMatch): IsMatch(isMatch), Label(lbl) {}

private:
  Transition(const Transition&) {}
  Transition& operator=(const Transition&) {return *this;}
};
