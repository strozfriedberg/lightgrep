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

#include <istream>
#include <ostream>
#include <vector>

#include "basic.h"
#include "instructions.h"
#include "fwd_pointers.h"
#include "byteset.h"

class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val):
    std::vector<Instruction>(num, val), NumChecked(0), First() {}

  Program(): std::vector<Instruction>(), NumChecked(0), First() {}

  uint32  NumChecked;

  ByteSet First;

  int bufSize() const;

  bool operator==(const Program& rhs) const;

  std::string marshall() const;
  static ProgramPtr unmarshall(const std::string& s);
};

std::ostream& operator<<(std::ostream& out, const Program& prog);

std::istream& operator>>(std::istream& in, Program& prog);
