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

#include "program.h"

#include <cstring>
#include <iomanip>

bool Program::operator==(const Program& rhs) const {
  return MaxLabel == rhs.MaxLabel &&
         MaxCheck == rhs.MaxCheck &&
         FilterOff == rhs.FilterOff &&
         Filter == rhs.Filter &&
         std::equal(begin(), end(), rhs.begin());
}

std::vector<char> Program::marshall() const {
  const size_t plen = size()*sizeof(Instruction);
  std::vector<char> buf(sizeof(*this) + plen);
  // write everything except IBeg, IEnd; leave those as nulls
  std::memcpy(buf.data(), this, sizeof(*this)-sizeof(IBeg)-sizeof(IEnd));
  // write the Instructions
  std::memcpy(buf.data()+sizeof(*this), IBeg.get(), plen);
  return buf;
}

ProgramPtr Program::unmarshall(void* buf, size_t len) {
  // The caller is responsible for freeing buf. We subvert std::unique_ptr
  // and std::shared_ptr here by giving them empty deleters.

  Program* p = static_cast<Program*>(buf);

  // IBeg may contain garbage; prevent operator= from calling the deleter.
  p->IBeg.release();
  // Set IBeg to the start of the instructions; set an empty deleter since
  // the caller is responsible for freeing buf.
  p->IBeg = std::unique_ptr<Instruction[], void(*)(Instruction*)>(
    reinterpret_cast<Instruction*>(p + 1), [](Instruction*){}
  );

  p->IEnd = reinterpret_cast<Instruction*>(static_cast<char*>(buf) + len);

  return ProgramPtr(p, [](Program*){});
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
      const uint32_t start = prog[i].Op.T2.First, end = prog[i].Op.T2.Last;
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
