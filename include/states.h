#pragma once

#include <bitset>
#include "basic.h"

class LitState {
public:
  LitState(byte lit): Lit(lit) {}
  
  const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { bits.set(Lit); }

private:
  byte Lit;
};

class EitherState {
public:
  EitherState(byte one, byte two): Lit1(one), Lit2(two) {}

  const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit1 || *beg == Lit2 ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { bits.set(Lit1); bits.set(Lit2); }

private:
  byte Lit1, Lit2;
};

class RangeState {
public:
  RangeState(byte first, byte last): First(first), Last(last) {}

  const byte* allowed(const byte* beg, const byte*) const { return First <= *beg && *beg <= Last ? beg+1: beg; }

  void getBits(std::bitset<256>& bits) const { for (byte i = First; i <= Last; ++i) { bits.set(i); }; }

private:
  byte First, Last;
};
