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

// FIXME: Inheriting from EncoderBase means we have a Valid member which
// we don't use. We could avoid this by moving the Valid member into a
// subclass of EncoderBase (what to call it?).
class OCEEncoder: public EncoderBase {
public:
  template <class BaseEncoder>
  OCEEncoder(BaseEncoder&& enc):
    BaseEnc(new BaseEncoder(std::forward<BaseEncoder>(enc))) {}

  virtual uint32 maxByteLength() const;

  virtual std::string name() const;

  virtual const UnicodeSet& validCodePoints() const;

  virtual uint32 write(int cp, byte buf[]) const;

  using EncoderBase::write;

  // OCE: bytes -> bytes
  static const byte OCE[];

private:
  std::unique_ptr<Encoder> BaseEnc;
};
