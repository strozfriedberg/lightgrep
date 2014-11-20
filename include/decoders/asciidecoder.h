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

#include "decoders/decoder.h"

class ASCIIDecoder: public Decoder {
public:
  ASCIIDecoder(const Decoder& trans):
    Trans(trans.clone())
  {}

  ASCIIDecoder(std::unique_ptr<Decoder> trans):
    Trans(std::move(trans))
  {}

  ASCIIDecoder(const ASCIIDecoder& other):
    Trans(other.Trans->clone())
  {}

  ASCIIDecoder(ASCIIDecoder&&) = default;

  ASCIIDecoder& operator=(const ASCIIDecoder& other) {
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    return *this;
  }

  ASCIIDecoder& operator=(ASCIIDecoder&&) = default;

  virtual ASCIIDecoder* clone() const {
    return new ASCIIDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "ASCII" << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    std::pair<int32_t,const byte*> n = Trans->next();
    if (n.first >= 0x80) {
      n.first = -n.first-1;
    }
    return n;
  }

  virtual void reset(const byte* beg, const byte* end) {
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // ASCII is 1:1
    return Trans->maxByteLength();
  }

private:
  std::unique_ptr<Decoder> Trans;
};
