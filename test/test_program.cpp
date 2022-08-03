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

#include <catch2/catch_test_macros.hpp>

#include "program.h"

ProgramPtr makeProgram() {
  ProgramPtr p1(new Program(3));
  (*p1)[0] = Instruction::makeByte('a');
  (*p1)[1] = Instruction::makeLabel(0);
  (*p1)[2] = Instruction::makeMatch();

  p1->FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    p1->Filter.set((i << 8) | 'a');
  }

  return p1;
}

TEST_CASE("testProgramSize") {
  ProgramPtr p1(makeProgram());
  REQUIRE(3u == p1->size());
}

TEST_CASE("testProgramSerialization") {
  ProgramPtr p1(makeProgram());

  const std::vector<char> buf = p1->marshall();
  REQUIRE(p1->bufSize() == buf.size());

  // first copy
  ProgramPtr p2 = Program::unmarshall(buf.data(), buf.size());
  REQUIRE(p2);
  REQUIRE(*p1 == *p2);

  // second copy, shares buffer with first copy
  ProgramPtr p3 = Program::unmarshall(buf.data(), buf.size());
  REQUIRE(p3);
  REQUIRE(*p1 == *p3);

  // p2 and p3 have the same buffer
  REQUIRE(&p2->front() == &p3->front());
  // p1 and p2 have different buffers
  REQUIRE(&p1->front() != &p2->front());
}
