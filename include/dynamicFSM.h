#pragma once

#include <boost/graph/adjacency_list.hpp>
#include "transition.h"

typedef boost::shared_ptr<Transition> TransitionPtr;

typedef boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS, TransitionPtr, boost::no_property, boost::no_property, boost::setS> DynamicFSM;
typedef boost::shared_ptr<DynamicFSM> DynamicFSMPtr;

typedef DynamicFSM::edge_descriptor EdgeIdx;
typedef DynamicFSM::edge_iterator EdgeIt;
