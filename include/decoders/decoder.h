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

#include "basic.h"

#include <string>
#include <utility>

class Decoder {
public:
  virtual ~Decoder() {}

  virtual Decoder* clone() const = 0;

  virtual std::string name() const = 0;

  virtual std::pair<int32_t,const byte*> next() = 0;

  virtual void reset(const byte* beg, const byte* end) = 0;

  virtual uint32_t maxByteLength() const = 0;

  static const int32_t END;
};
