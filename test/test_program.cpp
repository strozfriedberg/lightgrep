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

#include <scope/test.h>

#include "program.h"

ProgramPtr makeProgram() {
  ProgramPtr p1(new Program());
  p1->push_back(Instruction::makeByte('a'));
  p1->push_back(Instruction::makeLabel(0));
  p1->push_back(Instruction::makeMatch());

  p1->FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    p1->Filter.set((i << 8) | 'a');
  }

  return p1;
}

SCOPE_TEST(testProgramBufSize) {
  ProgramPtr p1(makeProgram());
  SCOPE_ASSERT_EQUAL(8216, p1->bufSize());
}

SCOPE_TEST(testProgramSerialization) {
  ProgramPtr p1(makeProgram());
  std::string buf = p1->marshall();
  ProgramPtr p2 = Program::unmarshall(buf);
  SCOPE_ASSERT(p2);
  SCOPE_ASSERT(*p1 == *p2);
}
