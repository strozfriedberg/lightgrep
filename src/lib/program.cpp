/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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
  const size_t icount = (len - (sizeof(Program::MaxLabel) + sizeof(Program::MaxCheck) + sizeof(Program::FilterOff) + 256*256/8)) / sizeof(Instruction);

  ProgramPtr p(new Program(0));

  p->MaxLabel = *reinterpret_cast<const decltype(p->MaxLabel)*>(i);
  i += sizeof(p->MaxLabel);

  p->MaxCheck = *reinterpret_cast<const decltype(p->MaxCheck)*>(i);
  i += sizeof(p->MaxCheck);

  p->FilterOff = *reinterpret_cast<const decltype(p->FilterOff)*>(i);
  i += sizeof(p->FilterOff);

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

  // The caller is responsible for freeing buf. We subvert std::unique_ptr
  // here by giving it an empty deleter.
  p->IBeg = std::unique_ptr<Instruction[], void(*)(Instruction*)>(
    reinterpret_cast<Instruction*>(const_cast<char*>(i)), [](Instruction*){}
  );

  p->IEnd = p->IBeg.get() + icount;

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
