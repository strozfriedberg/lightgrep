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
#include <string>

#include "encoders/encoderbase.h"

// FIXME: Inheriting from EncoderBase means we have a Valid member which
// we don't use. We could avoid this by moving the Valid member into a
// subclass of EncoderBase (what to call it?).
class ByteEncoder: public EncoderBase {
public:
  ByteEncoder(std::string&& name, std::unique_ptr<Encoder> enc):
    EncoderBase(),
    Name(std::forward<std::string>(name)),
    BaseEnc(std::move(enc)) {}

  ByteEncoder(std::string&& name, const Encoder& enc):
    EncoderBase(),
    Name(std::forward<std::string>(name)),
    BaseEnc(enc.clone()) {}

  ByteEncoder(const ByteEncoder& other):
    EncoderBase(other),
    Name(other.Name),
    BaseEnc(other.BaseEnc->clone()) {}

  ByteEncoder& operator=(const ByteEncoder& other) {
    EncoderBase::operator=(other);
    Name = other.Name;
    BaseEnc = std::unique_ptr<Encoder>(other.BaseEnc->clone());
    return *this;
  }

  ByteEncoder(ByteEncoder&&) = default;

  ByteEncoder& operator=(ByteEncoder&&) = default;

  virtual uint32_t maxByteLength() const;

  virtual std::string name() const;

  virtual const UnicodeSet& validCodePoints() const;

  virtual uint32_t write(int cp, byte buf[]) const;

  using EncoderBase::write;

protected:
  virtual void byteTransform(byte buf[], uint32_t blen) const = 0;

  std::string Name;
  std::unique_ptr<Encoder> BaseEnc;
};
