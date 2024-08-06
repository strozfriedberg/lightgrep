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
class UTF32Base: public UTFBase {
public:
  virtual UTF32Base<LE>* clone() const { return new UTF32Base<LE>(); }

  virtual uint32_t maxByteLength() const { return 4; }

  virtual std::string name() const { return LE ? "UTF-32LE" : "UTF-32BE"; }

  virtual uint32_t write(int32_t cp, byte buf[]) const {
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

  virtual uint32_t write(const byte buf[], int32_t& cp) const {
    cp = (buf[LE ? 0 : 3]      ) |
         (buf[LE ? 1 : 2] <<  8) |
         (buf[LE ? 2 : 1] << 16) |
         (buf[LE ? 3 : 0] << 24);

    if (cp < 0 || (0xD800 <= cp && cp < 0xE000) || 0x110000 <= cp) {
      // out of range
      cp = -1;
      return 0;
    }
    else {
      return 4;
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
