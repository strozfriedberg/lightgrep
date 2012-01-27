#pragma once

#include <limits>
#include <set>

#include "basic.h"
#include "transition.h"
#include "states.h"

class TransitionFactory {
public:
  ~TransitionFactory() {
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
  std::set<Transition*,TransitionComparator> Exemplars;
};
