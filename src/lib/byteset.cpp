#include "byteset.h"

#include <iomanip>

std::ostream& operator<<(std::ostream& out, const ByteSet& bs) {
  out << '[' << std::hex;

  int low = -1;
  bool first = true;
  for (unsigned int i = 0; i < 256; ++i) {
    if (bs.test(i)) {
      if (low < 0) {
        if (!first) {
          out << ',';
        }
        out << std::setfill('0') << std::setw(2) << i;
        low = i;
        first = false;
      }
    }
    else if (low >= 0) {
      if ((i-1) > low) {
        out << '-' << std::setfill('0') << std::setw(2) << (i-1);
      }
      low = -1;
    }
  }

  if (0 <= low && low < 255) {
    out << '-' << std::setfill('0') << std::setw(2) << 255;
  }

  out << ']' << std::dec;
  return out;
}
