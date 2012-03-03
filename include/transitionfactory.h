#pragma once

#include <algorithm>
#include <memory>
#include <set>

#include "byteset.h"
#include "transition.h"
#include "states.h"

class TransitionFactory {
public:
  TransitionFactory():
    Lit(0), Either(0, 0), Range(0, 0), CharClass(ByteSet()) {}

  ~TransitionFactory() {
    std::for_each(Exemplars.begin(), Exemplars.end(),
                  std::default_delete<Transition>());
  }

  Transition* getLit(byte lit) {
    Lit.Lit = lit;
    return get(&Lit);
  }

  Transition* getEither(byte lit1, byte lit2) {
    Either.Lit1 = lit1;
    Either.Lit2 = lit2;
    return get(&Either);
  }

  Transition* getRange(byte first, byte last) {
    Range.First = first;
    Range.Last = last;
    return get(&Range);
  }

  Transition* getCharClass(const ByteSet& bytes) {
    CharClass.Allowed = bytes;
    return get(&CharClass);
  }

  Transition* getCharClass(const UnicodeSet& bytes) {
    for (uint32 i = 0; i < 256; ++i) {
      CharClass.Allowed[i] = bytes[i];
    }
    return get(&CharClass);
  }

private:
  Transition* get(Transition* t) {
    auto i = Exemplars.find(t);
    return i == Exemplars.end() ? *Exemplars.insert(t->clone()).first : *i;
  }

  std::set<Transition*,TransitionComparator> Exemplars;

  // Local states so we don't have to create one on each lookup
  LitState Lit;
  EitherState Either;
  RangeState Range;
  CharClassState CharClass;
};
