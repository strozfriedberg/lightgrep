#pragma once

#include "graph.h"
#include "transition.h"

#include <boost/shared_ptr.hpp>

struct Empty {};

struct Glushkov {
  Transition* Trans;
};

struct Properties {
  bool Deterministic;

  Properties(): Deterministic(true) {}
};

template <class T, size_t N> class SmallVectorFactory {
public:
  typedef SmallVector<T,N> ListType;

  ListType create() {
    return ListType(Store);
  }

private:
  std::vector< std::vector<T> > Store;
};

// FIXME: would like to replace uint32 by Graph::EdgeDescriptor, but how?
typedef Graph< Properties,Glushkov,Empty,SmallVectorFactory<uint32,1> > NFA;
typedef boost::shared_ptr<NFA> NFAPtr;

