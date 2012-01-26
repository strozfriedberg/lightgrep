#pragma once

#include "graph.h"
#include "transition.h"
#include "vectorfamily.h"

#include <limits>
#include <string>

#include <boost/shared_ptr.hpp>

struct Empty {};

struct Glushkov {
  static const uint32 NOLABEL;

  Glushkov(): Trans(0), IsMatch(false), Label(NOLABEL) {}

  Glushkov(const Glushkov& g): Trans(g.Trans ? g.Trans->clone() : 0), IsMatch(g.IsMatch), Label(g.Label) {}

  virtual ~Glushkov() {
    delete Trans;
  }

  Glushkov& operator=(const Glushkov& other) {
    if (this != &other) {
      delete Trans;
      Trans = other.Trans ? other.Trans->clone() : 0;
      IsMatch = other.IsMatch;
      Label = other.Label;
    }
    return *this;
  }

  std::string label() const {
    std::stringstream buf;
    if (Trans) {
      buf << Trans->label();
      if (Label != NOLABEL) {
        buf << "/" << Label;
      }
    }
    return buf.str();
  }

  Transition* Trans;
  bool IsMatch;
  uint32 Label;
};

struct Properties {
  bool Deterministic;

  Properties(): Deterministic(true) {}
};

typedef Graph<Properties,Glushkov,Empty,VectorFamily> NFA;
typedef boost::shared_ptr<NFA> NFAPtr;

