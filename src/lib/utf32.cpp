#include "utf32.h"

void UTF32LE::collectEncodings(std::vector<std::vector<ByteSet>>& va, const UnicodeSet& uset) const {
  byte cur[4];
  byte prev[4];
  bool hasprev = false;

  for (const UnicodeSet::range& r : uset) {
    const uint32 l = r.first, h = r.second;
    for (uint32 cp = l; cp < h; ++cp) {
      if (write(cp, cur) == 0) {
        // cp is invalid, skip it
        continue;
      }

      if (hasprev && std::equal(cur+1, cur+4, prev+1)) {
        // join the previous cp if we are the same up to the last byte
        va.back()[0].set(cur[0]);
      }
      else {
        // otherwise add a new encoding to the list
        va.emplace_back(4);
        for (uint32 i = 0; i < 4; ++i) {
          va.back()[i].set(cur[i]);
        }

        std::swap(prev, cur);
        hasprev = true;
      }
    }
  }
}
