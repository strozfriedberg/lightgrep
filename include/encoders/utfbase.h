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

#include "encoders/encoderbase.h"

class UTFBase: public EncoderBase {
public:
  using EncoderBase::write;

protected:
  UTFBase(): EncoderBase(UnicodeSet{{0, 0xD800}, {0xE000, 0x110000}}) {}

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32_t& l, uint32_t h, uint32_t len, uint32_t blimit) const = 0;

  virtual void writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32_t& l, uint32_t& h, byte* cur, uint32_t len, uint32_t blimit) const;

  virtual void skipRange(UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32_t& l, uint32_t& h, uint32_t ubound) const;
};
