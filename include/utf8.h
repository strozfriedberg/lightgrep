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

class UTF8: public UTFBase {
public:
  virtual uint32 maxByteLength() const { return 4; }

  virtual std::string name() const { return "UTF-8"; }

  virtual uint32 write(int cp, byte buf[]) const;

  using UTFBase::write;

protected:
  virtual void collectRanges(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32& l, uint32 h, uint32 len, uint32 blimit) const;
};

class CachingUTF8: public CachingEncoder<UTF8> {
public:
  CachingUTF8(): CachingEncoder<UTF8>({
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
  }) {}
};
