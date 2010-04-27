#include <scope/test.h>

#include "vm.h"

SCOPE_TEST(executeLit) {
  byte b = 'a';
  Instruction i = Instruction::makeLit('a');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(Vm::execute(&i, &i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  
  next.clear();
  b = 'c';
  SCOPE_ASSERT(!Vm::execute(&i, &i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, next.size());
}

SCOPE_TEST(executeJump) {
  byte b;
  Instruction i = Instruction::makeJump(18);
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(Vm::execute(&i, &i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(&i+18, cur.PC);
}

SCOPE_TEST(executeMatch) {
  byte b;
  Instruction i = Instruction::makeMatch();
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(!Vm::execute(&i, &i, cur, next, &b, 57));
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i, 0, 0, 57), cur);
}
