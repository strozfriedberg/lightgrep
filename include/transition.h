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

struct Instruction;

class Transition {
public:
  Transition() {}
  virtual ~Transition() {}

  virtual const byte* allowed(const byte* beg, const byte* end) const = 0;

  virtual ByteSet& getBytes(ByteSet& bs) const {
    bs.reset();
    return orBytes(bs);
  }

  virtual ByteSet& orBytes(ByteSet& bs) const = 0;
  virtual byte type() const = 0;
  virtual size_t objSize() const = 0;
  virtual Transition* clone(void* buffer = 0) const = 0;
  virtual size_t numInstructions() const = 0;
  virtual bool toInstruction(Instruction* addr) const = 0;
  virtual std::string label() const = 0;

private:
  Transition(const Transition&) {}
  Transition& operator=(const Transition&) {return *this;}
};
