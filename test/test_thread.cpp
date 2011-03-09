#include <scope/test.h>

#include "thread.h"

SCOPE_TEST(defaultThreadConstructor) {
  Thread t;
  Instruction *nullPtr = 0;
  SCOPE_ASSERT_EQUAL(nullPtr, t.PC);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint32>::max(), t.Label);
  SCOPE_ASSERT_EQUAL(0, t.Start);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint64>::max(), t.End);
}

SCOPE_TEST(threadInit) {
  Thread t;
  Instruction* basePtr = reinterpret_cast<Instruction*>(17);
  uint64 startOffset = 0xfffffffffffffffd;
  t.init(basePtr, startOffset);
  SCOPE_ASSERT_EQUAL(basePtr, t.PC);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint32>::max(), t.Label);
  SCOPE_ASSERT_EQUAL(startOffset, t.Start);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint64>::max(), t.End);
}

SCOPE_TEST(threadJump) {
  Thread t;
  Instruction* basePtr = reinterpret_cast<Instruction*>(8);
  t.jump(basePtr, 5);
  SCOPE_ASSERT_EQUAL(reinterpret_cast<Instruction*>(28), t.PC);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint32>::max(), t.Label);
  SCOPE_ASSERT_EQUAL(0, t.Start);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint64>::max(), t.End);
}

SCOPE_TEST(threadFork) {
  Thread parent(0, 5, 123, std::numeric_limits<uint64>::max()),
         child;
  child.fork(parent, 0, 4);
  SCOPE_ASSERT_EQUAL(reinterpret_cast<Instruction*>(16), child.PC);
  SCOPE_ASSERT_EQUAL(5, child.Label);
  SCOPE_ASSERT_EQUAL(123, child.Start);
  SCOPE_ASSERT_EQUAL(std::numeric_limits<uint64>::max(), child.End);
}
