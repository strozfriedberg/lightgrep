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

#include <iomanip>
#include <memory>
#include <sstream>

#include "basic.h"
#include "decoders/decoder.h"

class XORDecoder: public Decoder {
public:
  XORDecoder(byte key, const Decoder& trans):
    Key(key),
    Trans(trans.clone())
  {}

  XORDecoder(byte key, std::unique_ptr<Decoder> trans):
    Key(key),
    Trans(std::move(trans))
  {}

  XORDecoder(const XORDecoder& other):
    Key(other.Key),
    Trans(other.Trans->clone())
  {}

  XORDecoder(XORDecoder&&) = default;

  XORDecoder& operator=(const XORDecoder& other) {
    Key = other.Key;
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    return *this;
  }

  XORDecoder& operator=(XORDecoder&&) = default;

  virtual XORDecoder* clone() const {
    return new XORDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "XOR("
       << std::hex << std::setw(2) << std::setfill('0') << std::uppercase
       << ((uint32_t) Key) << ")|" << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    std::pair<int32_t,const byte*> n = Trans->next();
    if (n.first < 0) {
      // do nothing
    }
    else if (n.first < 0x100) {
      n.first ^= Key;
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
    // XOR is 1:1
    return Trans->maxByteLength();
  }

private:
  byte Key;
  std::unique_ptr<Decoder> Trans;
};
