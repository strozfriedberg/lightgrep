#pragma once

#include <iostream>
#include <limits>
#include <set>

#include "basic.h"
#include "transition.h"

class TransitionFactory {
public:
  ~TransitionFactory() {
    std::cerr << Exemplars.size() << std::endl;

    const std::set<Transition*>::iterator end(Exemplars.end());
    for (std::set<Transition*>::iterator i(Exemplars.begin()); i != end; ++i) {
      delete *i;
    }
  }

  Transition* get(Transition* t) {
    const std::set<Transition*>::const_iterator i = Exemplars.find(t);
    if (i == Exemplars.end()) {
      return *Exemplars.insert(t->clone()).first;
    }
    else {
      return *i;
    }
  }

private:
  struct Comp {
    Comp(): mask(std::numeric_limits<uint64>::max()) {}

    bool operator()(const Transition* a, const Transition* b) {
      a_bytes.reset();
      b_bytes.reset();
      a->getBits(a_bytes);
      b->getBits(b_bytes);

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

    ByteSet a_bytes, b_bytes;
    const ByteSet mask;
  };

  std::set<Transition*,Comp> Exemplars;
};
