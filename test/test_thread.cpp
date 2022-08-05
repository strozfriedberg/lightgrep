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

#include "thread.h"

TEST_CASE("defaultThreadConstructor") {
  Thread t;
  Instruction *nullPtr = 0;
  REQUIRE(nullPtr == t.PC);
  REQUIRE(Thread::NOLABEL == t.Label);
  REQUIRE(0u == t.Start);
  REQUIRE(Thread::NONE == t.End);
}

TEST_CASE("threadSize") {
  REQUIRE(sizeof(Thread) <= 32);
}

/*
TEST_CASE("threadInit") {
  Thread t;
  Instruction* basePtr = reinterpret_cast<Instruction*>(17);
  uint64_t startOffset = 0xfffffffffffffffd;
  t.init(basePtr, startOffset);
  REQUIRE(basePtr == t.PC);
  REQUIRE(std::numeric_limits<uint32_t>::max() == t.Label);
  REQUIRE(startOffset == t.Start);
  REQUIRE(std::numeric_limits<uint64_t>::max() == t.End);
}
*/

TEST_CASE("threadJump") {
  Thread t;
  Instruction* basePtr = reinterpret_cast<Instruction*>(8);
  t.jump(basePtr, 5);
  REQUIRE(reinterpret_cast<Instruction*>(28) == t.PC);
  REQUIRE(Thread::NOLABEL == t.Label);
  REQUIRE(0u == t.Start);
  REQUIRE(Thread::NONE == t.End);
}

TEST_CASE("threadFork") {
  Thread parent(0, 5, 123, std::numeric_limits<uint64_t>::max()),
         child;
  child.fork(parent, 0, 4);
  REQUIRE(reinterpret_cast<Instruction*>(16) == child.PC);
  REQUIRE(5u == child.Label);
  REQUIRE(123u == child.Start);
  REQUIRE(Thread::NONE == child.End);
}
