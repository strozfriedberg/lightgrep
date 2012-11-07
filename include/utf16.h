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
class UTF16Base: public UTFBase {
public:
  virtual UTF16Base<LE>* clone() const { return new UTF16Base<LE>(); }

  virtual uint32 maxByteLength() const { return 4; }

  virtual std::string name() const { return LE ? "UTF-16LE" : "UTF-16BE"; }

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

  using UTFBase::write;

protected:
  virtual void collectRanges(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& va) const {
    auto i = uset.begin();
    const auto iend = uset.end();
    if (i == iend) {
      return;
    }

    uint32 l = i->first, h = i->second;
    byte cur[4];

    // handle low two-byte encodings
    writeRange(va, i, iend, l, h, cur, 2, 0xD800);

    // skip the UTF-16 surrogates
    skipRange(i, iend, l, h, 0xE000);

    // handle high two-byte encodings
    writeRange(va, i, iend, l, h, cur, 2, 0x10000);

    // handle four-byte encodings
    writeRange(va, i, iend, l, h, cur, 4, 0x110000);
  }

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32& l, uint32 h, uint32 len, uint32 blimit) const {
    if (l < std::min(h, blimit) && l % 256 > 0) {
      const uint32 m = std::min({ h, blimit, (l/256+1)*256 });
      v[len-(LE ? 2 : 1)].set(l & 0xFF, ((m-1) & 0xFF)+1, true);
      l = m;
    }
  }
};

typedef UTF16Base<true>  UTF16LE;
typedef UTF16Base<false> UTF16BE;

class CachingUTF16LE: public CachingEncoder<UTF16LE> {
public:
  CachingUTF16LE(): CachingEncoder<UTF16LE>({
    // \p{Any}, .
    {
      {{0, 0xD800}, {0xE000, 0x110000}},
      {
        { {{0x00,0x100}}, {{0x00,0xD8}, {0xE0,0x100}} },
        { {{0x00,0x100}}, {{0xD8,0xDC}}, {{0x00,0x100}}, {{0xDC,0xE0}} }
      }
    }
  }) {}
};

class CachingUTF16BE: public CachingEncoder<UTF16BE> {
public:
  CachingUTF16BE(): CachingEncoder<UTF16BE>({
    // \p{Any}, .
    {
      {{0, 0xD800}, {0xE000, 0x110000}},
      {
        { {{0x00,0xD8}, {0xE0,0x100}}, {{0x00,0x100}} },
        { {{0xD8,0xDC}}, {{0x00,0x100}}, {{0xDC,0xE0}}, {{0x00,0x100}} }
      }
    }
  }) {}
};
