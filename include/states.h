#pragma once

#include "transition.h"

#pragma pack(1)
// This gets the states to take up as little space as possible.
// It is a relatively portable directive to the compiler to layout the class according to the minimum
// byte alignment. A class using inheritance typically has hidden overhead of a single pointer (to its
// virtual function table) in addition to the total size of its members. If packing wasn't turned on,
// then the structure would probably be word-aligned. So, on a 64 bit platform, the size of LitState
// would normally be 16 bytes, 8 bytes for the hidden pointer and 8 bytes as the minimum space for the
// object's members. #pragma pack(1) takes the size down to 9 bytes.
//
// Byte packing like this can often have a negative performance impact. But since we're going to have
// many of these objects in a contiguous buffer, it makes sense to pack them to reap the benefits of
// L1 cache.

class LitState: public Transition {
public:
  LitState(byte lit): Transition(), Lit(lit) {}
  LitState(byte lit, uint32 label): Transition(label), Lit(lit) {}
  
  const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { bits.set(Lit); }

  size_t objSize() const { return sizeof(*this); }
  
  LitState* clone(void* buffer) const {
    return new(buffer) LitState(Lit);
  }

  virtual size_t numInstructions() const { return 1; };
  virtual bool   toInstruction(Instruction* addr) const;

private:
  byte Lit;
};

class EitherState: public Transition {
public:
  EitherState(byte one, byte two): Transition(), Lit1(one), Lit2(two) {}
  EitherState(byte one, byte two, uint32 label): Transition(label), Lit1(one), Lit2(two) {}

  const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit1 || *beg == Lit2 ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { bits.set(Lit1); bits.set(Lit2); }

  size_t objSize() const { return sizeof(*this); }

  EitherState* clone(void* buffer) const {
    return new(buffer) EitherState(Lit1, Lit2);
  }

  virtual size_t numInstructions() const { return 1; };
  virtual bool   toInstruction(Instruction* addr) const;

private:
  byte Lit1, Lit2;
};

class RangeState: public Transition {
public:
  RangeState(byte first, byte last): Transition(), First(first), Last(last) {}
  RangeState(byte first, byte last, uint32 label): Transition(label), First(first), Last(last) {}

  const byte* allowed(const byte* beg, const byte*) const { return First <= *beg && *beg <= Last ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { for (byte i = First; i <= Last; ++i) { bits.set(i); }; }

  size_t objSize() const { return sizeof(*this); }

  RangeState* clone(void* buffer) const {
    return new(buffer) RangeState(First, Last);
  }

  virtual size_t numInstructions() const { return 1; };
  virtual bool   toInstruction(Instruction* addr) const;

private:
  byte First, Last;
};
#pragma pack(pop)
