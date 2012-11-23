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

#include "byteset.h"
#include "transition.h"
#include "rangeset.h"

struct TransitionComparator;
class TransitionFactory;

enum TransitionType {
  ByteStateType,
  EitherStateType,
  RangeStateType,
  ByteSetStateType
};

class ByteState: public Transition {
public:
  ByteState(byte b): Byte(b) {}
  virtual ~ByteState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return *beg == Byte ? beg + 1 : beg;
  }

  virtual ByteSet& orBytes(ByteSet& bs) const {
    bs.set(Byte);
    return bs;
  }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual byte type() const { return ByteStateType; }

  virtual ByteState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  ByteState(const ByteState& x): Transition(), Byte(x.Byte) {}

  byte Byte;

  friend struct TransitionComparator;
  friend class TransitionFactory;
};

class EitherState: public Transition {
public:
  EitherState(byte one, byte two): Byte1(one), Byte2(two) {}
  virtual ~EitherState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return *beg == Byte1 || *beg == Byte2 ? beg + 1 : beg;
  }

  virtual ByteSet& orBytes(ByteSet& bs) const {
    bs.set(Byte1);
    bs.set(Byte2);
    return bs;
  }

  virtual byte type() const { return EitherStateType; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual EitherState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  EitherState(const EitherState& x):
    Transition(), Byte1(x.Byte1), Byte2(x.Byte2) {}

  byte Byte1, Byte2;

  friend struct TransitionComparator;
  friend class TransitionFactory;
};

class RangeState: public Transition {
public:
  RangeState(byte first, byte last): First(first), Last(last) {}
  virtual ~RangeState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return First <= *beg && *beg <= Last ? beg+1: beg;
  }

  virtual ByteSet& orBytes(ByteSet& bs) const {
    return bs.set(First, Last+1, true);
  }

  virtual byte type() const { return RangeStateType; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual RangeState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  RangeState(const RangeState& x): Transition(), First(x.First), Last(x.Last) {}

  byte First, Last;

  friend struct TransitionComparator;
  friend class TransitionFactory;
};

class ByteSetState: public Transition {
public:
  ByteSetState(const ByteSet& allowed): Allowed(allowed) {}

  ByteSetState(const UnicodeSet& allowed) {
    for (uint32_t i = 0; i < 256; ++i) {
      Allowed[i] = allowed[i];
    }
  }

  virtual ~ByteSetState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return Allowed[*beg] ? beg+1 : beg;
  }

  virtual ByteSet& orBytes(ByteSet& bs) const {
    bs |= Allowed;
    return bs;
  }

  virtual byte type() const { return ByteSetStateType; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual ByteSetState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 9; }
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  ByteSetState(const ByteSetState& x): Transition(), Allowed(x.Allowed) {}

  ByteSet Allowed;

  friend struct TransitionComparator;
  friend class TransitionFactory;
};

struct TransitionComparator {
  //
  // This defines a total ordering over Transitions, such that
  //
  //   ByteState < EitherState < RangeState < ByteSetState
  //
  // and for two Transitions of the same type, the one with the
  // lexicographically least data is the lesser.
  //
  bool operator()(const Transition* a, const Transition* b) const {
    switch (a->type()) {
    case ByteStateType:
      switch (b->type()) {
      case ByteStateType:
        return static_cast<const ByteState*>(a)->Byte <
               static_cast<const ByteState*>(b)->Byte;
      case EitherStateType:
      case RangeStateType:
      case ByteSetStateType:
        return true;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    case EitherStateType:
      switch (b->type()) {
      case ByteStateType:
        return false;
      case EitherStateType:
        {
          const EitherState* ae = static_cast<const EitherState*>(a);
          const EitherState* be = static_cast<const EitherState*>(b);

          if (ae->Byte1 < be->Byte1) {
            return true;
          }
          else if (ae->Byte1 > be->Byte1) {
            return false;
          }
          else {
            return ae->Byte2 < be->Byte2;
          }
        }
      case RangeStateType:
      case ByteSetStateType:
        return true;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    case RangeStateType:
      switch (b->type()) {
      case ByteStateType:
      case EitherStateType:
        return false;
      case RangeStateType:
        {
          const RangeState* ar = static_cast<const RangeState*>(a);
          const RangeState* br = static_cast<const RangeState*>(b);

          if (ar->First < br->First) {
            return true;
          }
          else if (ar->First > br->First) {
            return false;
          }
          else {
            return ar->Last < br->Last;
          }
        }
      case ByteSetStateType:
        return true;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    case ByteSetStateType:
      switch (b->type()) {
      case ByteStateType:
      case EitherStateType:
      case RangeStateType:
        return false;
      case ByteSetStateType:
        return static_cast<const ByteSetState*>(a)->Allowed <
               static_cast<const ByteSetState*>(b)->Allowed;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    default:
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << a->type());
    }
  }
};
