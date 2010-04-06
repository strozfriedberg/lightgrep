#pragma once

class LitState {
public:
  LitState(char lit): Lit(lit) {}
  
  const char* allowed(const char* beg, const char*) const { return *beg == Lit ? beg+1: beg; }

private:
  char Lit;
};
