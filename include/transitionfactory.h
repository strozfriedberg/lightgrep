/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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

  Transition* getSmallest(const ByteSet& bset) {
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

  Transition* get(Transition* t) {
    auto i = Exemplars.find(t);
    return i == Exemplars.end() ? *Exemplars.insert(t->clone()).first : *i;
  }

private:
  std::set<Transition*, TransitionComparator> Exemplars;

  // Local states so we don't have to create one on each lookup
  ByteState Byte;
  EitherState Either;
  RangeState Range;
  ByteSetState BSet;
};
