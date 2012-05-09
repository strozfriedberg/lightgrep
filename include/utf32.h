#pragma once

#include "encoder.h"

template <bool LE>
class UTF32Base: public Encoder {
public:
  UTF32Base(): valid(0, 0x110000) {}

  virtual uint32 maxByteLength() const { return 4; }

  virtual const UnicodeSet& validCodePoints() const { return valid; };

  virtual uint32 write(int cp, byte buf[]) const {
    if (cp < 0) {
      // too small
      return 0;
    }
    else if (cp < 0xD800) {
      buf[LE ? 0 : 3] =  cp        & 0xFF;
      buf[LE ? 1 : 2] = (cp >>  8) & 0xFF;
      buf[LE ? 2 : 1] = (cp >> 16) & 0xFF;
      buf[LE ? 3 : 0] = (cp >> 24) & 0xFF;
      return 4;
    }
    else if (cp < 0xE000) {
      // UTF-16 surrogates, invalid
      return 0;
    }
    else if (cp < 0x110000) {
      buf[LE ? 0 : 3] =  cp        & 0xFF;
      buf[LE ? 1 : 2] = (cp >>  8) & 0xFF;
      buf[LE ? 2 : 1] = (cp >> 16) & 0xFF;
      buf[LE ? 3 : 0] = (cp >> 24) & 0xFF;
      return 4;
    }
    else {
      // too large
      return 0;
    }
  }

  virtual void write(std::vector<std::vector<ByteSet>>& v, const UnicodeSet& uset) const {
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

        if (hasprev &&
            std::equal(cur+(LE ? 1 : 0), cur+(LE ? 4 : 3), prev+(LE ? 1 : 0))) {
          // join the previous cp if we are the same up to the last byte
          v.back()[LE ? 0 : 3].set(cur[LE ? 0 : 3]);
        }
        else {
          // otherwise add a new encoding to the list
          v.emplace_back(4);
          for (uint32 i = 0; i < 4; ++i) {
            v.back()[i].set(cur[i]);
          }

          std::swap(prev, cur);
          hasprev = true;
        }
      }
    }
  }

  using Encoder::write;

private:
  const UnicodeSet valid;
};

typedef UTF32Base<true>  UTF32LE;
typedef UTF32Base<false> UTF32BE;
