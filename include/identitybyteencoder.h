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

#include <memory>

#include "byteencoder.h"

class IdentityByteEncoder: public ByteEncoder {
public:
  IdentityByteEncoder(std::unique_ptr<Encoder> enc):
    ByteEncoder("identity", std::move(enc)) {}

  IdentityByteEncoder(const Encoder& enc):
    ByteEncoder("identity", enc) {}

  IdentityByteEncoder(const IdentityByteEncoder&) = default;

  IdentityByteEncoder& operator=(const IdentityByteEncoder&) = default;

  IdentityByteEncoder(IdentityByteEncoder&&) = default;

  IdentityByteEncoder& operator=(IdentityByteEncoder&&) = default;

  virtual IdentityByteEncoder* clone() const {
    return new IdentityByteEncoder(*this);
  }

protected:
  virtual void byteTransform(byte[], uint32_t) const {}
};
