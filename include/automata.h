#pragma once

#include "graph.h"
#include "transition.h"
#include "vectorfamily.h"

#include <boost/shared_ptr.hpp>

struct Empty {};

struct Glushkov {
  Glushkov(): Trans(0) {}

  Glushkov(const Glushkov& g): Trans(g.Trans ? g.Trans->clone() : 0) {}

  virtual ~Glushkov() {
    delete Trans;
  }

  Transition* Trans;
};

struct Properties {
  bool Deterministic;

  Properties(): Deterministic(true) {}
};

typedef Graph<Properties,Glushkov,Empty,VectorFamily> NFA;
typedef boost::shared_ptr<NFA> NFAPtr;

