#include "utf16.h"

void UTF16LE::collectEncodings(std::vector<std::vector<ByteSet>>& va, const UnicodeSet& uset) const {
  byte cur[4];
  byte prev[4];

  uint32 clen, plen = 0;

  for (const UnicodeSet::range& r : uset) {
    const uint32 l = r.first, h = r.second;
    for (uint32 cp = l; cp < h; ++cp) {
      clen = write(cp, cur);
      if (clen == 0) {
        // cp is invalid, skip it
        continue;
      }

/*
      if (cur[0] == 0 && cp + 255 < h) {
        // write the whole block in one go
        va.emplace_back(clen);
        for (uint32 i = 0; i < clen; ++i) {
          va.back()[i].set(cur[i]);
        }

        va.back()[clen == 2 ? 0 : 2].reset().flip();
        cp += 255;
        std::swap(prev, cur);
        plen = clen;
        continue;
      }
*/

      if (clen == 2) {
        if (plen == 2 && cur[1] == prev[1]) {
          // join the previous cp if we are the same on the first byte
          va.back()[0].set(cur[0]);
        }
        else {
          // otherwise add a new encoding to the list
          va.emplace_back(clen);
          for (uint32 i = 0; i < clen; ++i) {
            va.back()[i].set(cur[i]);
          }

          std::swap(prev, cur);
          plen = clen;
        }
      }
      else { // clen == 4
        if (plen == 4 && cur[0] == prev[0] && cur[1] == prev[1] && cur[3] == prev[3]) {
          // join the previous cp if we are the same except on byte 2
          va.back()[2].set(cur[2]);
        }
        else {
          // otherwise add a new encoding to the list
          va.emplace_back(clen);
          for (uint32 i = 0; i < clen; ++i) {
            va.back()[i].set(cur[i]);
          }

          std::swap(prev, cur);
          plen = clen;
        }
      }
    }
  }
}
