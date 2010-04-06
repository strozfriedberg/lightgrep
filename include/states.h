#pragma once

class LitState {
public:
  LitState(char lit): Lit(lit) {}
  
  const char* allowed(const char* beg, const char*) const { return *beg == Lit ? beg+1: beg; }

private:
  char Lit;
};

class EitherState {
public:
  EitherState(char one, char two): Lit1(one), Lit2(two) {}

  const char* allowed(const char* beg, const char*) const { return *beg == Lit1 || *beg == Lit2 ? beg+1: beg; }

private:
  char Lit1, Lit2;
};

class RangeState {
public:
  RangeState(char first, char last): First(first), Last(last) {}

  const char* allowed(const char* beg, const char*) const { return First <= *beg && *beg <= Last ? beg+1: beg; }

private:
  char First, Last;
};
