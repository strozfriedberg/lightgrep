#include <scope/test.h>

#include "vm.h"

SCOPE_TEST(executeLit) {
  byte b = 'a';
  Instruction i = Instruction::makeLit('a');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);
  
  next.clear();
  b = 'c';
  SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, next.size());
}

SCOPE_TEST(executeEither) {
  byte b = 'z';
  Instruction i = Instruction::makeEither('z', '3');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);

  next.clear();
  b = '3';
  SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(1u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);

  next.clear();
  b = '4';
  SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, next.size());
}

SCOPE_TEST(executeRange) {
  Instruction i = Instruction::makeRange('c', 't');
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  for (uint32 j = 0; j < 256; ++j) {
    next.clear();
    byte b = j;
    SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 0));
    if ('c' <= j && j <= 't') {
      SCOPE_ASSERT_EQUAL(1u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(&i+1, 0, 0, 0), next[0]);      
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, next.size());
    }
  }
}

SCOPE_TEST(executeJump) {
  byte b;
  Instruction i = Instruction::makeJump(18);
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(Vm::execute(&i, cur, next, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(&i+18, cur.PC);
}

SCOPE_TEST(executeMatch) {
  byte b;
  Instruction i = Instruction::makeMatch();
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(!Vm::execute(&i, cur, next, &b, 57));
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i, 0, 0, 57), cur);
}

SCOPE_TEST(executeSaveLabel) {
  byte b;
  Instruction i = Instruction::makeSaveLabel(31);
  Thread      cur(&i, 0, 0, 0);
  ThreadList  next;
  SCOPE_ASSERT(Vm::execute(&i, cur, next, &b, 47));
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 31, 47, 0), cur);
}

SCOPE_TEST(simpleLitMatch) {
  Instruction prog[4] = { Instruction::makeSaveLabel(3),
                          Instruction::makeLit('a'),
                          Instruction::makeLit('b'),
                          Instruction::makeMatch()      };
  byte text[] = {'a', 'b', 'c'};
  SCOPE_ASSERT(Vm::run(prog, 4, text, &text[3], 35));
  text[1] = 'c';
  SCOPE_ASSERT(!Vm::run(prog, 4, text, &text[3], 35));
}
