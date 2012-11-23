/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "caching_encoder.h"
#include "utfbase.h"

template <bool LE>
class UTF32Base: public UTFBase {
public:
  virtual UTF32Base<LE>* clone() const { return new UTF32Base<LE>(); }

  virtual uint32_t maxByteLength() const { return 4; }

  virtual std::string name() const { return LE ? "UTF-32LE" : "UTF-32BE"; }

  virtual uint32_t write(int cp, byte buf[]) const {
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

  using UTFBase::write;

protected:
  virtual void collectRanges(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& va) const {
    auto i = uset.begin();
    const auto iend = uset.end();
    if (i == iend) {
      return;
    }

    uint32_t l = i->first, h = i->second;
    byte cur[4];

    // handle low four-byte encodings
    writeRange(va, i, iend, l, h, cur, 4, 0xD800);

    // skip the UTF-16 surrogates
    skipRange(i, iend, l, h, 0xE000);

    // handle hight four-byte encodings
    writeRange(va, i, iend, l, h, cur, 4, 0x110000);
  }

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32_t& l, uint32_t h, uint32_t, uint32_t blimit) const {
    if (l < std::min(h, blimit) && l % 256 > 0) {
      const uint32_t m = std::min({ h, blimit, (l/256+1)*256 });
      v[LE ? 0 : 3].set(l & 0xFF, ((m-1) & 0xFF)+1, true);
      l = m;
    }
  }
};

typedef UTF32Base<true>  UTF32LE;
typedef UTF32Base<false> UTF32BE;

class CachingUTF32LE: public CachingEncoder {
public:
  CachingUTF32LE(): CachingEncoder(
    UTF32LE(),
    {
      // \p{Any}, .
      {
        {{0, 0xD800}, {0xE000, 0x110000}},
        {
          { {{0x00,0x100}}, {{0xD8,0xE0}}, {{0x01,0x11}}, 0x00 },
          { {{0x00,0x100}}, {{0x00,0xD8},{0xE0,0x100}}, {{0x00,0x11}}, 0x00 }
        }
      }
    }
  ) {}
};

class CachingUTF32BE: public CachingEncoder {
public:
  CachingUTF32BE(): CachingEncoder(
    UTF32BE(),
    {
      // \p{Any}, .
      {
        {{0, 0xD800}, {0xE000, 0x110000}},
        {
          { 0x00, 0x00, {{0x00,0xD8},{0xE0,0x100}}, {{0x00,0x100}} },
          { 0x00, {{0x01,0x11}}, {{0x00,0x100}}, {{0x00,0x100}} }
        }
      }
    }
  ) {}
};
