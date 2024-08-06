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
