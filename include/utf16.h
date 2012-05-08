#pragma once

#include "encoder.h"

template <bool LE>
class UTF16Base: public Encoder {
public:
  virtual uint32 maxByteLength() const { return 4; }

  virtual uint32 write(int cp, byte buf[]) const {
    if (cp < 0) {
      // too small
      return 0;
    }
    else if (cp < 0xD800) {
      // direct representation
      buf[LE ? 0 : 1] = cp & 0xFF;
      buf[LE ? 1 : 0] = cp >> 8;
      return 2;
    }
    else if (cp < 0xE000) {
      // UTF-16 surrogates, invalid
      return 0;
    }
    else if (cp < 0x10000) {
      // direct representation
      buf[LE ? 0 : 1] = cp & 0xFF;
      buf[LE ? 1 : 0] = cp >> 8;
      return 2;
    }
    else if (cp < 0x110000) {
      // surrogate pair representation
      const uint16 lead = 0xD800 - (0x10000 >> 10) + (cp >> 10);
      const uint16 trail = 0xDC00 + (cp & 0x3FF);

      buf[LE ? 0 : 1] = lead & 0xFF;
      buf[LE ? 1 : 0] = lead >> 8;
      buf[LE ? 2 : 3] = trail & 0xFF;
      buf[LE ? 3 : 2] = trail >> 8;
      return 4;
    }
    else {
      // too large
      return 0;
    }
  }

  virtual void write(std::vector<std::vector<ByteSet>>& v,
                     const UnicodeSet& uset) const
  {
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
        if (cur[LE ? 0 : 3] == 0 && cp + 255 < h) {
          // write the whole block in one go
          v.emplace_back(clen);
          for (uint32 i = 0; i < clen; ++i) {
            v.back()[i].set(cur[i]);
          }

          v.back()[(clen == 2 ? 0 : 2) + !LE].reset().flip();
          cp += 255;
          std::swap(prev, cur);
          plen = clen;
          continue;
        }
*/

        if (clen == 2) {
          if (plen == 2 && cur[LE ? 1 : 0] == prev[LE ? 1 : 0]) {
            // join the previous cp if we agree on the relevant byte
            v.back()[LE ? 0 : 1].set(cur[LE ? 0 : 1]);
          }
          else {
            // otherwise add a new encoding to the list
            v.emplace_back(clen);
            for (uint32 i = 0; i < clen; ++i) {
              v.back()[i].set(cur[i]);
            }

            std::swap(prev, cur);
            plen = clen;
          }
        }
        else { // clen == 4
          if (plen == 4 &&
              cur[0] == prev[0] &&
              cur[1] == prev[1] &&
              cur[LE ? 3 : 2] == prev[LE ? 3 : 2])
          {
            // join the previous cp if we are the same except on byte 2
            v.back()[LE ? 2 : 3].set(cur[LE ? 2 : 3]);
          }
          else {
            // otherwise add a new encoding to the list
            v.emplace_back(clen);
            for (uint32 i = 0; i < clen; ++i) {
              v.back()[i].set(cur[i]);
            }

            std::swap(prev, cur);
            plen = clen;
          }
        }
      }
    }
  }

  using Encoder::write;
};

typedef UTF16Base<true>  UTF16LE;
typedef UTF16Base<false> UTF16BE;
