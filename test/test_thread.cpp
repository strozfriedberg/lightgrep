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

#include "thread.h"

SCOPE_TEST(defaultThreadConstructor) {
  Thread t;
  Instruction *nullPtr = 0;
  SCOPE_ASSERT_EQUAL(nullPtr, t.PC);
  SCOPE_ASSERT_EQUAL(Thread::NOLABEL, t.Label);
  SCOPE_ASSERT_EQUAL(0u, t.Start);
  SCOPE_ASSERT_EQUAL(Thread::NONE, t.End);
}

SCOPE_TEST(threadSize) {
  SCOPE_ASSERT(sizeof(Thread) <= 32);
}

/*
SCOPE_TEST(threadInit) {
  Thread t;
  Instruction* basePtr = reinterpret_cast<Instruction*>(17);
  uint64_t startOffset = 0xfffffffffffffffd;
  t.init(basePtr, startOffset);
  SCOPE_ASSERT_EQUAL(basePtr, t.PC);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint32_t>::max(), t.Label);
  SCOPE_ASSERT_EQUAL(startOffset, t.Start);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint64_t>::max(), t.End);
}
*/

SCOPE_TEST(threadJump) {
  Thread t;
  Instruction* basePtr = reinterpret_cast<Instruction*>(8);
  t.jump(basePtr, 5);
  SCOPE_ASSERT_EQUAL(reinterpret_cast<Instruction*>(28), t.PC);
  SCOPE_ASSERT_EQUAL(Thread::NOLABEL, t.Label);
  SCOPE_ASSERT_EQUAL(0u, t.Start);
  SCOPE_ASSERT_EQUAL(Thread::NONE, t.End);
}

SCOPE_TEST(threadFork) {
  Thread parent(0, 5, 123, std::numeric_limits<uint64_t>::max()),
         child;
  child.fork(parent, 0, 4);
  SCOPE_ASSERT_EQUAL(reinterpret_cast<Instruction*>(16), child.PC);
  SCOPE_ASSERT_EQUAL(5u, child.Label);
  SCOPE_ASSERT_EQUAL(123u, child.Start);
  SCOPE_ASSERT_EQUAL(Thread::NONE, child.End);
}
