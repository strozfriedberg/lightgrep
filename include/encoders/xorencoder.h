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

#include <algorithm>
#include <memory>

#include <boost/lexical_cast.hpp>

#include "encoders/byteencoder.h"

class XOREncoder: public ByteEncoder {
public:
  XOREncoder(byte key, std::unique_ptr<Encoder> enc):
    ByteEncoder("XOR" + boost::lexical_cast<std::string>((uint32_t) key), std::move(enc)),
    Key(key) {}

  XOREncoder(byte key, const Encoder& enc):
    ByteEncoder("XOR" + boost::lexical_cast<std::string>((uint32_t) key), enc),
    Key(key) {}

  XOREncoder(const XOREncoder&) = default;

  XOREncoder& operator=(const XOREncoder&) = default;

  XOREncoder(XOREncoder&&) = default;

  XOREncoder& operator=(XOREncoder&&) = default;

  virtual XOREncoder* clone() const {
    return new XOREncoder(*this);
  }

protected:
  virtual void byteTransform(byte buf[], uint32_t blen) const {
    const byte key = Key;
    std::transform(buf, buf+blen, buf, [key](byte b){ return b ^ key; });
  }

  virtual void byteUntransform(byte buf[], uint32_t blen) const {
    byteTransform(buf, blen);
  }

private:
  byte Key;
};
