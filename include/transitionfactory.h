/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    Byte(0), Either(0, 0), Range(0, 0), BSet(ByteSet()) {}

  ~TransitionFactory() {
    std::for_each(Exemplars.begin(), Exemplars.end(),
                  std::default_delete<Transition>());
  }

  Transition* getByte(byte b) {
    Byte.Byte = b;
    return get(&Byte);
  }

  Transition* getEither(byte b1, byte b2) {
    Either.Byte1 = b1;
    Either.Byte2 = b2;
    return get(&Either);
  }

  Transition* getRange(byte first, byte last) {
    Range.First = first;
    Range.Last = last;
    return get(&Range);
  }

  Transition* getByteSet(const ByteSet& bset) {
    BSet.Allowed = bset;
    return get(&BSet);
  }

  Transition* getByteSet(const UnicodeSet& bset) {
    // NB: This should be used *only* when we intend to intersect
    // the input set with [0x00,0xFF].
    for (uint32_t i = 0; i < 256; ++i) {
      BSet.Allowed.set(i, bset.test(i));
    }
    return get(&BSet);
  }

  template <class SetType>
  Transition* getSmallest(const SetType& bset) {
    enum {
      NONE,
      ONE,
      RANGE,
      TWO
    } type = NONE;

    byte low = 0, high = 0;

    // This is a little state machine for classifying our byte set.
    for (size_t i = 0; i < 256; ++i) {
      if (bset.test(i)) {
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
          return getByteSet(bset);
        }
      }
    }

    switch (type) {
    case NONE:
      return getByteSet(bset);
    case ONE:
      return getByte(low);
    case RANGE:
// TODO: Check whether there is any performance difference between EITHER
// and RANGE for two-element ranges.
      return getRange(low, high);
    case TWO:
      return getEither(low, high);
    }

    // This is impossible, it's here just to shut the compiler up.
    return getByteSet(bset);
  }

private:
  Transition* get(Transition* t) {
    auto i = Exemplars.find(t);
    return i == Exemplars.end() ? *Exemplars.insert(t->clone()).first : *i;
  }

  std::set<Transition*,TransitionComparator> Exemplars;

  // Local states so we don't have to create one on each lookup
  ByteState Byte;
  EitherState Either;
  RangeState Range;
  ByteSetState BSet;
};
