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

#include <bitset>
#include <istream>
#include <ostream>
#include <vector>

#include "basic.h"
#include "instructions.h"
#include "fwd_pointers.h"

class Program: public std::vector<Instruction> {
public:
  Program(size_t num, const Instruction& val):
    std::vector<Instruction>(num, val),
    MaxLabel(0), MaxCheck(0), FilterOff(0), Filter() {}

  Program():
    std::vector<Instruction>(),
    MaxLabel(0), MaxCheck(0), FilterOff(0), Filter() {}

  uint32_t MaxLabel, MaxCheck;

  uint32_t FilterOff;
  std::bitset<256*256> Filter;

  int bufSize() const;

  bool operator==(const Program& rhs) const;

  std::string marshall() const;
  static ProgramPtr unmarshall(const std::string& s);
};

std::ostream& operator<<(std::ostream& out, const Program& prog);

std::istream& operator>>(std::istream& in, Program& prog);
