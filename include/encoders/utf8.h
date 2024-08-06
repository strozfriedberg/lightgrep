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

class UTF8: public UTFBase {
public:
  virtual UTF8* clone() const { return new UTF8(); }

  virtual uint32_t maxByteLength() const { return 4; }

  virtual std::string name() const { return "UTF-8"; }

  virtual uint32_t write(int32_t cp, byte buf[]) const;

  using UTFBase::write;

  virtual uint32_t write(const byte buf[], int32_t& cp) const;

protected:
  virtual void collectRanges(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32_t& l, uint32_t h, uint32_t len, uint32_t blimit) const;
};

class CachingUTF8: public CachingEncoder {
public:
  CachingUTF8(): CachingEncoder(
    UTF8(),
    {
      // \p{Any}, .
      {
        {{0, 0xD800}, {0xE000, 0x110000}},
        {
          { {{0x00, 0x80}} },
          { {{0xC2, 0xE0}}, {{0x80, 0xC0}} },
          {   0xE0,         {{0xA0, 0xC0}}, {{0x80, 0xC0}} },
          {   0xED,         {{0x80, 0xA0}}, {{0x80, 0xC0}} },
          { {{0xE1,0xED}, {0xEE,0xF0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
          {   0xF0,         {{0x90, 0xC0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
          {   0xF4,         {{0x80, 0x90}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
          { {{0xF1, 0xF4}}, {{0x80, 0xC0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} }
        }
      }
    }
  ) {}
};
