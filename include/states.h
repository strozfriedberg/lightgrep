#pragma once

#include "transition.h"

class LitState: public Transition {
public:
  LitState(byte lit): Transition(), Lit(lit) {}
  LitState(byte lit, uint32 label): Transition(label), Lit(lit) {}
  
  const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { bits.set(Lit); }

  size_t objSize() const { return sizeof(*this); }
  
  LitState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool   toInstruction(Instruction* addr) const;
  virtual std::string label() const;

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

  EitherState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool   toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  byte Lit1, Lit2;
};

class RangeState: public Transition {
public:
  RangeState(byte first, byte last): Transition(), First(first), Last(last) {}
  RangeState(byte first, byte last, uint32 label): Transition(label), First(first), Last(last) {}

  const byte* allowed(const byte* beg, const byte*) const { return First <= *beg && *beg <= Last ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { for (uint32 i = First; i <= Last; ++i) { bits.set(i); }; }

  size_t objSize() const { return sizeof(*this); }

  RangeState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool   toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  byte First, Last;
};

class CharClassState: public Transition {
public:
  CharClassState(ByteSet allowed, const std::string& text): Label(text), Allowed(allowed)  {}

  const byte* allowed(const byte* beg, const byte*) const { return Allowed[*beg] ? beg+1: beg; }

  void getBits(ByteSet& bits) const { bits = Allowed; }

  size_t objSize() const { return sizeof(*this); }

  CharClassState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 9; }
  virtual bool   toInstruction(Instruction* addr) const;
  virtual std::string label() const;

  std::string Label;
  ByteSet     Allowed;
};
