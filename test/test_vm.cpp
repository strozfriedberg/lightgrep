#include <scope/test.h>

#include "vm.h"

SCOPE_TEST(executeLit) {
  byte b = 'a';
  Instruction i = Instruction::makeLit('a');
  ThreadList  next;
  SCOPE_ASSERT(Vm::execute(&i, next, &b));
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  
  next.clear();
  b = 'c';
  SCOPE_ASSERT(!Vm::execute(&i, next, &b));
  SCOPE_ASSERT_EQUAL(0u, next.size());
}
