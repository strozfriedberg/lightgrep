#pragma once

#include "graph.h"
#include "transition.h"

#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Transition> TransitionPtr;

struct Empty {};

struct Glushkov {
  Transition* trans;
};

typedef Graph<Empty,Glushkov,Empty> NFA;
typedef boost::shared_ptr<NFA> NFAPtr;

