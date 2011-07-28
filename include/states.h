#pragma once

#include "transition.h"

class LitState: public Transition {
public:
  LitState(byte lit): Transition(), Lit(lit) {}
  LitState(byte lit, uint32 label): Transition(label), Lit(lit) {}
  virtual ~LitState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit ? beg+1: beg; }

  virtual void getBits(std::bitset<256>& bits) const { bits.set(Lit); }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual LitState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  LitState(const LitState& x): Transition(x.Label, x.IsMatch), Lit(x.Lit) {}
  byte Lit;
};

class EitherState: public Transition {
public:
  EitherState(byte one, byte two): Transition(), Lit1(one), Lit2(two) {}
  EitherState(byte one, byte two, uint32 label): Transition(label), Lit1(one), Lit2(two) {}
  virtual ~EitherState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit1 || *beg == Lit2 ? beg+1: beg; }

  virtual void getBits(std::bitset<256>& bits) const { bits.set(Lit1); bits.set(Lit2); }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual EitherState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  EitherState(const EitherState& x): Transition(x.Label, x.IsMatch), Lit1(x.Lit1), Lit2(x.Lit2) {}

  byte Lit1, Lit2;
};

class RangeState: public Transition {
public:
  RangeState(byte first, byte last): Transition(), First(first), Last(last) {}
  RangeState(byte first, byte last, uint32 label): Transition(label), First(first), Last(last) {}
  virtual ~RangeState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return First <= *beg && *beg <= Last ? beg+1: beg; }

  virtual void getBits(std::bitset<256>& bits) const { for (uint32 i = First; i <= Last; ++i) { bits.set(i); }; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual RangeState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  RangeState(const RangeState& x): Transition(x.Label, x.IsMatch), First(x.First), Last(x.Last) {}

  byte First, Last;
};

class CharClassState: public Transition {
public:
  CharClassState(ByteSet allowed, const std::string& text): LabelStr(text), Allowed(allowed)  {}
  virtual ~CharClassState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return Allowed[*beg] ? beg+1: beg; }

  virtual void getBits(ByteSet& bits) const { bits = Allowed; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual CharClassState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 9; }
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

  std::string LabelStr;

private:
  CharClassState(const CharClassState& x): Transition(x.Label, x.IsMatch), LabelStr(x.LabelStr), Allowed(x.Allowed) {}

  ByteSet     Allowed;
};
