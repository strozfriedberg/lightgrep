/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#include "basic.h"
#include "decoders/decoder.h"

class ByteSource: public Decoder {
public:
  ByteSource(const byte* beg, const byte* end):
    Cur(beg), End(end)
  {}

  ByteSource(const ByteSource&) = default;

  ByteSource& operator=(const ByteSource&) = default;

  virtual ByteSource* clone() const {
    return new ByteSource(*this);
  }

  virtual std::string name() const {
    return "";
  }

  virtual std::pair<int32_t,const byte*> next() {
    if (Cur == End) {
      return std::make_pair(END, End);
    }
    else {
      const int32_t n = *Cur;
      return std::make_pair(n, Cur++);
    }
  }

  virtual void reset(const byte* beg, const byte* end) {
    Cur = beg;
    End = end;
  }

  virtual uint32_t maxByteLength() const {
    return 1;
  }

 private:
  const byte* Cur;
  const byte* End;
};
