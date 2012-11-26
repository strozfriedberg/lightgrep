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

class OCEEncoder: public ByteEncoder {
public:
  OCEEncoder(std::unique_ptr<Encoder> enc):
    ByteEncoder("OCE", std::move(enc)) {}

  OCEEncoder(const Encoder& enc):
    ByteEncoder("OCE", enc) {}

  OCEEncoder(const OCEEncoder&) = default;

  OCEEncoder& operator=(const OCEEncoder&) = default;

  OCEEncoder(OCEEncoder&&) = default;

  OCEEncoder& operator=(OCEEncoder&&) = default;

  virtual OCEEncoder* clone() const {
    return new OCEEncoder(*this);
  }

  // OCE: bytes -> bytes
  static const byte OCE[];

protected:
  virtual void byteTransform(byte buf[], uint32_t blen) const;
};
