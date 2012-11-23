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

#include "encoderbase.h"

class CharEncoder: public EncoderBase {
public:
  CharEncoder(const std::string& name, std::unique_ptr<Encoder> enc):
    EncoderBase(),
    Name(name),
    BaseEnc(std::move(enc)) {}

  CharEncoder(const std::string& name, const Encoder& enc):
    EncoderBase(),
    Name(name),
    BaseEnc(enc.clone()) {}

  CharEncoder(const CharEncoder& other):
    EncoderBase(other),
    Name(other.Name),
    BaseEnc(other.BaseEnc->clone()) {}

  CharEncoder& operator=(const CharEncoder& other) {
    EncoderBase::operator=(other);
    Name = other.Name;
    BaseEnc = std::unique_ptr<Encoder>(other.BaseEnc->clone());
    return *this;
  }

  CharEncoder(CharEncoder&&) = default;

  CharEncoder& operator=(CharEncoder&&) = default;

  virtual std::string name() const;

  virtual uint32 write(int cp, byte buf[]) const;

  using EncoderBase::write;

protected:
  virtual int charTransform(int cp) const = 0;

  std::string Name;
  std::unique_ptr<Encoder> BaseEnc;
};
