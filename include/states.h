#pragma once

#include "transition.h"

#include <limits>

struct TransitionComparator;
class TransitionFactory;

enum TransitionType {
  LitStateType,
  EitherStateType,
  RangeStateType,
  CharClassStateType
};

class LitState: public Transition {
public:
  LitState(byte lit): Lit(lit) {}
  virtual ~LitState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return *beg == Lit ? beg + 1 : beg;
  }

  virtual void getBits(ByteSet& bits) const { bits.set(Lit); }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual byte type() const { return LitStateType; }

  virtual LitState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  LitState(const LitState& x): Transition(), Lit(x.Lit) {}

  byte Lit;

  friend struct TransitionComparator;
  friend class TransitionFactory;
};

class EitherState: public Transition {
public:
  EitherState(byte one, byte two): Lit1(one), Lit2(two) {}
  virtual ~EitherState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return *beg == Lit1 || *beg == Lit2 ? beg + 1 : beg;
  }

  virtual void getBits(ByteSet& bits) const { bits.set(Lit1); bits.set(Lit2); }

  virtual byte type() const { return EitherStateType; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual EitherState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  EitherState(const EitherState& x): Transition(), Lit1(x.Lit1), Lit2(x.Lit2) {}

  byte Lit1, Lit2;

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

  virtual void getBits(ByteSet& bits) const {
    for (uint32 i = First; i <= Last; ++i) { bits.set(i); };
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

class CharClassState: public Transition {
public:
  CharClassState(ByteSet allowed): Allowed(allowed) {}
  virtual ~CharClassState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const {
    return Allowed[*beg] ? beg+1 : beg;
  }

  virtual void getBits(ByteSet& bits) const { bits = Allowed; }

  virtual byte type() const { return CharClassStateType; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual CharClassState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 9; }
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  CharClassState(const CharClassState& x): Transition(), Allowed(x.Allowed) {}

  ByteSet Allowed;

  friend struct TransitionComparator;
  friend class TransitionFactory;
};

bool operator<(const ByteSet& lbs, const ByteSet& rbs);

struct TransitionComparator {
  //
  // This defines a total ordering over Transitions, such that
  //
  //   LitState < EitherState < RangeState < CharClassState
  //
  // and for two Transitions of the same type, the one with the
  // lexicographically least data is the lesser.
  //
  bool operator()(const Transition* a, const Transition* b) const {
    switch (a->type()) {
    case LitStateType:
      switch (b->type()) {
      case LitStateType:
        return static_cast<const LitState*>(a)->Lit <
               static_cast<const LitState*>(b)->Lit;
      case EitherStateType:
      case RangeStateType:
      case CharClassStateType:
        return true;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    case EitherStateType:
      switch (b->type()) {
      case LitStateType:
        return false;
      case EitherStateType:
        {
          const EitherState* ae = static_cast<const EitherState*>(a);
          const EitherState* be = static_cast<const EitherState*>(b);

          if (ae->Lit1 < be->Lit1) {
            return true;
          }
          else if (ae->Lit1 > be->Lit1) {
            return false;
          }
          else {
            return ae->Lit2 < be->Lit2;
          }
        }
      case RangeStateType:
      case CharClassStateType:
        return true;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    case RangeStateType:
      switch (b->type()) {
      case LitStateType:
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
      case CharClassStateType:
        return true;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    case CharClassStateType:
      switch (b->type()) {
      case LitStateType:
      case EitherStateType:
      case RangeStateType:
        return false;
      case CharClassStateType:
        return static_cast<const CharClassState*>(a)->Allowed <
               static_cast<const CharClassState*>(b)->Allowed;
      default:
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << b->type());
      }
    default:
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Impossible! " << a->type());
    }
  }
};

