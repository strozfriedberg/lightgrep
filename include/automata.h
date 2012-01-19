#pragma once

#include "graph.h"
#include "transition.h"

#include <boost/shared_ptr.hpp>

struct Empty {};

struct Glushkov {
  Transition* Trans;
};

typedef Graph<Empty,Glushkov,Empty> NFA;
typedef boost::shared_ptr<NFA> NFAPtr;

