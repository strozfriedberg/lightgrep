#include "pattern.h"

std::ostream& operator<<(std::ostream& out, const Pattern& p) {
  out << p.Expression << ", " << (p.FixedString ? "fixed": "grep") << ", "
    << (p.CaseInsensitive ? "no case": "case") << ", " << p.Encoding;
  return out;
}
