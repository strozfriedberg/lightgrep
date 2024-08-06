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
