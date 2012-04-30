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

  template <class SetType>
  Transition* getSmallest(const SetType& bytes) {
    enum {
      NONE,
      ONE,
      RANGE,
      TWO
    } type = NONE;

    byte low, high;

    // This is a little state machine for classifying our byte set.
    for (size_t i = 0; i < 256; ++i) {
      if (bytes.test(i)) {
        switch (type) {
        case NONE:
          low = high = i;
          type = ONE;
          break;
        case ONE:
          if (++high != i) {
            high = i;
            type = TWO;
          }
          else {
            type = RANGE;
          }
          break;
        case RANGE:
          if (++high == i) {
            break;
          }
        case TWO:
          // cc is a union of disjoint ranges
          return getCharClass(bytes);
        }
      }
    }

    switch (type) {
    case NONE:
      return getCharClass(bytes);
    case ONE:
      return getLit(low);
    case RANGE:
// TODO: Check whether there is any performance difference between EITHER
// and RANGE for two-element ranges.
      return getRange(low, high);
    case TWO:
      return getEither(low, high);
    }

    // This is impossible, it's here just to shut the compiler up.
    return getCharClass(bytes);
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
