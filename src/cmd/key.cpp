#include "key.h"

std::ostream& operator<<(std::ostream& out, const Key& k) {
  out << static_cast<Pattern>(k) << ", " << k.UserIndex;
  return out;
}
