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
  const size_t plen = bufSize();
  std::vector<char> buf(plen);
  char* i = buf.data();

  // MaxLabel
  std::memcpy(i, &MaxLabel, sizeof(MaxLabel));
  i += sizeof(MaxLabel);

  // MaxCheck
  std::memcpy(i, &MaxCheck, sizeof(MaxCheck));
  i += sizeof(MaxCheck);

  // FilterOff
  std::memcpy(i, &FilterOff, sizeof(FilterOff));
  i += sizeof(FilterOff);

  // Filter
  for (size_t b = 0; b < Filter.size(); b += 8) {
    *i = Filter[b] |
         (Filter[b+1] << 1) |
         (Filter[b+2] << 2) |
         (Filter[b+3] << 3) |
         (Filter[b+4] << 4) |
         (Filter[b+5] << 5) |
         (Filter[b+6] << 6) |
         (Filter[b+7] << 7);
    ++i;
  }

  // Instructions
  std::memcpy(i, IBeg.get(), size()*sizeof(Instruction));

  // XXX: i should be at the end now

  return buf;
}

ProgramPtr Program::unmarshall(const void* buf, size_t len) {
  const char* i = static_cast<const char*>(buf);
  const size_t icount = (len - (sizeof(MaxLabel) + sizeof(MaxCheck) + sizeof(FilterOff) + 256*256/8)) / sizeof(Instruction);

  ProgramPtr p(new Program(icount));

  p->MaxLabel = *reinterpret_cast<const decltype(MaxLabel)*>(i);
  i += sizeof(MaxLabel);

  p->MaxCheck = *reinterpret_cast<const decltype(MaxCheck)*>(i);
  i += sizeof(MaxCheck);

  p->FilterOff = *reinterpret_cast<const decltype(FilterOff)*>(i);
  i += sizeof(FilterOff);

  for (size_t b = 0; b < p->Filter.size() / 8; ++b, ++i) {
    p->Filter[8*b]   = *i & 0x01;
    p->Filter[8*b+1] = *i & 0x02;
    p->Filter[8*b+2] = *i & 0x04;
    p->Filter[8*b+3] = *i & 0x08;
    p->Filter[8*b+4] = *i & 0x10;
    p->Filter[8*b+5] = *i & 0x20;
    p->Filter[8*b+6] = *i & 0x40;
    p->Filter[8*b+7] = *i & 0x80;
  }

  std::memcpy(p->IBeg.get(), i, icount*sizeof(Instruction));

  return p;

/*
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
*/

/*
  std::unique_ptr<char[]> x(new char[len]);
  std::memcpy(x.get(), buf, len);

  ProgramPtr p(reinterpret_cast<Program*>(x.release()), [](Program* p){ delete[] reinterpret_cast<char*>(p); });
  p->IBeg.release();
  p->IBeg = std::unique_ptr<Instruction[], void(*)(Instruction*)>(
    reinterpret_cast<Instruction*>(p.get() + 1), [](Instruction*){}
  );
  p->IEnd = reinterpret_cast<Instruction*>(x.get() + len);

  return p;
*/




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
