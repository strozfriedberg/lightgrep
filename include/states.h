#pragma once

#include "transition.h"

#include <limits>

struct TransitionComparator;

class LitState: public Transition {
public:
  LitState(byte lit): Lit(lit) {}
  virtual ~LitState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit ? beg+1: beg; }

  virtual void getBits(ByteSet& bits) const { bits.set(Lit); }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual LitState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  LitState(const LitState& x): Transition(), Lit(x.Lit) {}

  byte Lit;

  friend struct TransitionComparator;
};

class EitherState: public Transition {
public:
  EitherState(byte one, byte two): Lit1(one), Lit2(two) {}
  virtual ~EitherState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return *beg == Lit1 || *beg == Lit2 ? beg+1: beg; }

  virtual void getBits(ByteSet& bits) const { bits.set(Lit1); bits.set(Lit2); }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual EitherState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  EitherState(const EitherState& x): Transition(), Lit1(x.Lit1), Lit2(x.Lit2) {}

  byte Lit1, Lit2;

  friend struct TransitionComparator;
};

class RangeState: public Transition {
public:
  RangeState(byte first, byte last): First(first), Last(last) {}
  virtual ~RangeState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return First <= *beg && *beg <= Last ? beg+1: beg; }

  virtual void getBits(ByteSet& bits) const { for (uint32 i = First; i <= Last; ++i) { bits.set(i); }; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual RangeState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 1; };
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  RangeState(const RangeState& x): Transition(), First(x.First), Last(x.Last) {}

  byte First, Last;

  friend struct TransitionComparator;
};

class CharClassState: public Transition {
public:
  CharClassState(ByteSet allowed): Allowed(allowed) {}
  virtual ~CharClassState() {}

  virtual const byte* allowed(const byte* beg, const byte*) const { return Allowed[*beg] ? beg+1: beg; }

  virtual void getBits(ByteSet& bits) const { bits = Allowed; }

  virtual size_t objSize() const { return sizeof(*this); }

  virtual CharClassState* clone(void* buffer) const;

  virtual size_t numInstructions() const { return 9; }
  virtual bool toInstruction(Instruction* addr) const;
  virtual std::string label() const;

private:
  CharClassState(const CharClassState& x): Transition(), Allowed(x.Allowed) {}

  ByteSet Allowed;

  friend struct TransitionComparator;
};

class TransitionComparator {
public:
  TransitionComparator(): mask(std::numeric_limits<uint64>::max()) {}

  bool operator()(const Transition* a, const Transition* b) const {
    if (const LitState* alit = dynamic_cast<const LitState*>(a)) {
      if (const LitState* blit = dynamic_cast<const LitState*>(b)) {
        return alit->Lit < blit->Lit;
      }
      else {
        return true;
      }
    }
    else if (const EitherState* ae = dynamic_cast<const EitherState*>(a)) {
      if (dynamic_cast<const LitState*>(b)) {
        return false;
      }
      else if (const EitherState* be = dynamic_cast<const EitherState*>(b)) {
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
      else {
        return true;
      }
    }
    else if (const RangeState* ar = dynamic_cast<const RangeState*>(a)) {
      if (dynamic_cast<const LitState*>(b) ||
          dynamic_cast<const EitherState*>(b)) {
        return false;
      }
      else if (const RangeState* br = dynamic_cast<const RangeState*>(b)) {
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
      else {
        return true;
      }
    }
    else {
      const CharClassState* acc = dynamic_cast<const CharClassState*>(a);

      const CharClassState* bcc = dynamic_cast<const CharClassState*>(b);
      if (!bcc) {
        return false;
      }

      const ByteSet& a_bytes(acc->Allowed);
      const ByteSet& b_bytes(bcc->Allowed);

      uint64 al, bl;

      al = (a_bytes & mask).to_ulong();
      bl = (b_bytes & mask).to_ulong();

      if (al < bl) {
        return true;
      }
      else if (bl > al) {
        return false;
      }
      else {
        al = ((a_bytes >> 64) & mask).to_ulong();
        bl = ((b_bytes >> 64) & mask).to_ulong();

        if (al < bl) {
          return true;
        }
        else if (bl > al) {
          return false;
        }
        else {
          al = ((a_bytes >> 128) & mask).to_ulong();
          bl = ((b_bytes >> 128) & mask).to_ulong();

          if (al < bl) {
            return true;
          }
          else if (bl > al) {
            return false;
          }
          else {
            return (a_bytes >> 192).to_ulong() < (b_bytes >> 192).to_ulong();
          }
        }
      }
    }
  }

private:
  const ByteSet mask;
};
