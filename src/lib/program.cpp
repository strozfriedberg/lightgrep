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

#include "program.h"

#include <iomanip>
#include <iostream>
#include <sstream>

int Program::bufSize() const {
  return sizeof(ByteSet) + sizeof(uint32_t) + (size() * sizeof(value_type));
}

bool Program::operator==(const Program& rhs) const {
  return NumChecked == rhs.NumChecked &&
         First == rhs.First &&
         std::equal(begin(), end(), rhs.begin());
}

std::string Program::marshall() const {
  std::stringstream buf;
  buf.write((char*)&NumChecked, sizeof(NumChecked));
  buf.write((char*)&First, sizeof(First));
  for (auto instruction: *this) {
    buf.write((char*)&instruction, sizeof(instruction));
  }
  return buf.str();
}

ProgramPtr Program::unmarshall(const std::string& s) {
  ProgramPtr p(new Program);
  std::stringstream buf(s);
  buf.read((char*)&p->NumChecked, sizeof(uint32_t));
  buf.read((char*)&p->First, sizeof(ByteSet));
  Instruction i;
  while (buf.read((char*)&i, sizeof(Instruction))) {
    p->push_back(i);
  }
  return p;
}

std::ostream& printIndex(std::ostream& out, uint32_t i) {
  out << std::setfill('0') << std::hex << std::setw(8) << i << ' ';
  return out;
}

std::ostream& operator<<(std::ostream& out, const Program& prog) {
  for (uint32_t i = 0; i < prog.size(); ++i) {
    printIndex(out, i) << prog[i] << '\n';

    if (prog[i].OpCode == BIT_VECTOR_OP) {
      for (uint32_t j = 1; j < 9; ++j) {
        out << std::hex << std::setfill('0') << std::setw(8)
            << i + j << '\t' << *(uint32_t*)(&prog[i]+j) << '\n';
      }

      out << std::dec;
      i += 8;
    }
    else if (prog[i].OpCode == JUMP_TABLE_RANGE_OP) {
      uint32_t start = 0,
             end = 255;

      if (prog[i].OpCode == JUMP_TABLE_RANGE_OP) {
        start = prog[i].Op.Range.First;
        end = prog[i].Op.Range.Last;
      }

      for (uint32_t j = start; j <= end; ++j) {
        ++i;
        printIndex(out, i) << std::setfill(' ') << std::setw(3) << j << ": " << reinterpret_cast<const uint32_t&>(prog[i]) << '\n';
      }
    }
    else if (prog[i].OpCode == JUMP_OP || prog[i].OpCode == FORK_OP) {
      ++i;
      printIndex(out, i) << reinterpret_cast<const uint32_t&>(prog[i]) << '\n';
    }
  }

  return out;
}
