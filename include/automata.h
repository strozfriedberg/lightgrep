#pragma once

#include "graph.h"
#include "transition.h"
#include "vectorfamily.h"

#include <boost/shared_ptr.hpp>

struct Empty {};

struct Glushkov {
  Transition* Trans;
};

struct Properties {
  bool Deterministic;

  Properties(): Deterministic(true) {}
};

typedef Graph<Properties,Glushkov,Empty,VectorFamily> NFA;
typedef boost::shared_ptr<NFA> NFAPtr;

