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

#include <memory>
#include <sstream>

#include "decoders/decoder.h"

class OCEDecoder: public Decoder {
public:
  OCEDecoder(const Decoder& trans):
    Trans(trans.clone())
  {}

  OCEDecoder(std::unique_ptr<Decoder> trans):
    Trans(std::move(trans))
  {}

  OCEDecoder(const OCEDecoder& other):
    Trans(other.Trans->clone())
  {}

  OCEDecoder(OCEDecoder&&) = default;

  OCEDecoder& operator=(const OCEDecoder& other) {
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    return *this;
  }

  OCEDecoder& operator=(OCEDecoder&&) = default;

  virtual OCEDecoder* clone() const {
    return new OCEDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "|OCE" << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    std::pair<int32_t,const byte*> n = Trans->next();
    if (n.first < 0) {
      // do nothing
    }
    else if (n.first < 0x100) {
      n.first = unOCE[n.first];
    }
    else {
      n.first = -n.first-1;
    }

    return n;
  }

  virtual void reset(const byte* beg, const byte* end) {
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // OCE is 1:1
    return Trans->maxByteLength();
  }

  static const byte unOCE[];

private:
  std::unique_ptr<Decoder> Trans;
};
