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

#include "basic.h"
#include "byteset.h"
#include "rangeset.h"

#include <vector>

class Encoder {
public:
  virtual ~Encoder() {}

  virtual Encoder* clone() const = 0;

  virtual uint32_t maxByteLength() const = 0;

  virtual std::string name() const = 0;

  virtual const UnicodeSet& validCodePoints() const = 0;

  virtual uint32_t write(int32_t cp, byte buf[]) const = 0;

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const = 0;

  virtual uint32_t write(const byte buf[], int32_t& cp) const = 0;
};
