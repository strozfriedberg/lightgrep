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

class DecoratingEncoder: public Encoder {
public:
  DecoratingEncoder(std::unique_ptr<Encoder> enc):
    Encoder(),
    BaseEnc(std::move(enc))
  {}

  DecoratingEncoder(const Encoder& enc):
    Encoder(),
    BaseEnc(enc.clone())
  {}

  DecoratingEncoder(const DecoratingEncoder& other):
    Encoder(other),
    BaseEnc(other.BaseEnc->clone())
  {}

  DecoratingEncoder& operator=(const DecoratingEncoder& other) {
    Encoder::operator=(other);
    BaseEnc = std::unique_ptr<Encoder>(other.BaseEnc->clone());
    return *this;
  }

  DecoratingEncoder(DecoratingEncoder&&) = default;

  DecoratingEncoder& operator=(DecoratingEncoder&&) = default;

  virtual DecoratingEncoder* clone() const {
    return new DecoratingEncoder(*this);
  }

  virtual uint32_t maxByteLength() const {
    return BaseEnc->maxByteLength();
  }

  virtual std::string name() const {
    return BaseEnc->name();
  }

  virtual const UnicodeSet& validCodePoints() const {
    return BaseEnc->validCodePoints();
  }

  virtual uint32_t write(int cp, byte buf[]) const {
    return BaseEnc->write(cp, buf); 
  }

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& vo) const {
    BaseEnc->write(uset, vo);
  }

protected:
  std::unique_ptr<Encoder> BaseEnc;
};
