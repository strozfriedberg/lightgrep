#pragma once

#include <iostream>
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
    bool operator()(const Transition* a, const Transition* b);

    ByteSet a_bytes, b_bytes;
  };

  std::set<Transition*,Comp> Exemplars;
};
