#pragma once

#include "basic.h"
#include "byteset.h"

struct Instruction;

class Transition {
public:
  Transition() {}
  virtual ~Transition() {}

  virtual const byte* allowed(const byte* beg, const byte* end) const = 0;

  virtual ByteSet& getBytes(ByteSet& bs) const {
    bs.reset();
    return orBytes(bs);
  }

  virtual ByteSet& orBytes(ByteSet& bs) const = 0;
  virtual byte type() const = 0;
  virtual size_t objSize() const = 0;
  virtual Transition* clone(void* buffer = 0) const = 0;
  virtual size_t numInstructions() const = 0;
  virtual bool toInstruction(Instruction* addr) const = 0;
  virtual std::string label() const = 0;

private:
  Transition(const Transition&) {}
  Transition& operator=(const Transition&) {return *this;}
};
