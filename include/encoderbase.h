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

#include "encoder.h"

class EncoderBase: public Encoder {
public:
  virtual const UnicodeSet& validCodePoints() const { return Valid; };

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const;

  using Encoder::write;

protected:
  EncoderBase(): EncoderBase(UnicodeSet()) {}

  EncoderBase(UnicodeSet&& valid): Valid(std::forward<UnicodeSet>(valid)) {}

  EncoderBase(const EncoderBase& other): Valid(other.Valid) {}

  EncoderBase(EncoderBase&& other): Valid(std::move(other.Valid)) {}

  EncoderBase& operator=(const EncoderBase& other) {
    Valid = other.Valid;
    return *this;
  }

  EncoderBase& operator=(EncoderBase&& other) {
    Valid = std::move(other.Valid);
    return *this;
  }

  virtual void collectRanges(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

  UnicodeSet Valid;
};
