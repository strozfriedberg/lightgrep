#include "automata.h"

#include <limits>

const uint32 Glushkov::NOLABEL = std::numeric_limits<uint32>::max();

std::string Glushkov::label() const {
  std::stringstream buf;
  if (Trans) {
    buf << Trans->label();
    if (Label != NOLABEL) {
      buf << "/" << Label;
    }
  }
  return buf.str();
}
