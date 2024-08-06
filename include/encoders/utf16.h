/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "encoders/caching_encoder.h"
#include "encoders/utfbase.h"

template <bool LE>
class UTF16Base: public UTFBase {
public:
  virtual UTF16Base<LE>* clone() const { return new UTF16Base<LE>(); }

  virtual uint32_t maxByteLength() const { return 4; }

  virtual std::string name() const { return LE ? "UTF-16LE" : "UTF-16BE"; }

  virtual uint32_t write(int32_t cp, byte buf[]) const {
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
      const uint16_t lead = 0xD800 - (0x10000 >> 10) + (cp >> 10);
      const uint16_t trail = 0xDC00 + (cp & 0x3FF);

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

  virtual uint32_t write(const byte buf[], int32_t& cp) const {
    cp = buf[LE ? 0 : 1] | (buf[LE ? 1 : 0] << 8);

    if (cp < 0xD800) {
      // direct representation
      return 2;
    }
    else if (cp < 0xDC00) {
      // found lead of UTF-16 surrogate pair
      const uint16_t lead = cp;

      const uint16_t trail = buf[LE ? 2 : 3] | (buf[LE ? 3 : 2] << 8);
      if (trail < 0xDC00) {
        // invalid
        return 0;
      }
      else if (trail < 0xE000) {
        // found trail of UTF-16 surrogate pair
        cp = ((lead - (0xD800 - (0x10000 >> 10))) << 10) | (trail - 0xDC00);
        return 4;
      }
      else {
        // invalid
        return 0;
      }
    }
    else if (cp < 0xE000) {
      // invalid
      return 0;
    }
    else {
      // direct representation
      return 2;
    }
  }

protected:
  virtual void collectRanges(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& va) const {
    auto i = uset.begin();
    const auto iend = uset.end();
    if (i == iend) {
      return;
    }

    uint32_t l = i->first, h = i->second;
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

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32_t& l, uint32_t h, uint32_t len, uint32_t blimit) const {
    if (l < std::min(h, blimit) && l % 256 > 0) {
      const uint32_t m = std::min({ h, blimit, (l/256+1)*256 });
      v[len-(LE ? 2 : 1)].set(l & 0xFF, ((m-1) & 0xFF)+1, true);
      l = m;
    }
  }
};

typedef UTF16Base<true>  UTF16LE;
typedef UTF16Base<false> UTF16BE;

class CachingUTF16LE: public CachingEncoder {
public:
  CachingUTF16LE(): CachingEncoder(
    UTF16LE(),
    {
      // \p{Any}, .
      {
        {{0, 0xD800}, {0xE000, 0x110000}},
        {
          { {{0x00,0x100}}, {{0x00,0xD8}, {0xE0,0x100}} },
          { {{0x00,0x100}}, {{0xD8,0xDC}}, {{0x00,0x100}}, {{0xDC,0xE0}} }
        }
      }
    }
  ) {}
};

class CachingUTF16BE: public CachingEncoder {
public:
  CachingUTF16BE(): CachingEncoder(
    UTF16BE(),
    {
      // \p{Any}, .
      {
        {{0, 0xD800}, {0xE000, 0x110000}},
        {
          { {{0x00,0xD8}, {0xE0,0x100}}, {{0x00,0x100}} },
          { {{0xD8,0xDC}}, {{0x00,0x100}}, {{0xDC,0xE0}}, {{0x00,0x100}} }
        }
      }
    }
  ) {}
};
