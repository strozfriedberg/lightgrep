#include "ascii.h"

uint32 ASCII::write(int cp, byte buf[]) const {
  if (cp < 0) {
    return 0;
  }
  else if (cp < 0x100) {
    buf[0] = cp;
    return 1;
  }
  else {
    return 0;
  }
}

void ASCII::write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const {
  v.emplace_back(1);
  for (const UnicodeSet::range& r : uset) {
    if (r.first > 0xFF) {
      break;
    }
    else if (r.second > 0xFF) {
      v[0][0].set(r.first, 0x100, true);
      break;
    }
    else {
      v[0][0].set(r.first, r.second, true);
    }
  }
}
