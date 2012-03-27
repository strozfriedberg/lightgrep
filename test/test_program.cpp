#include <scope/test.h>

#include "program.h"

SCOPE_TEST(testProgramBufSize) {
  ProgramPtr p1(new Program());
  p1->push_back(Instruction::makeLit('a'));
  p1->push_back(Instruction::makeLabel(0));
  p1->push_back(Instruction::makeMatch());
  p1->First.set('a');

  SCOPE_ASSERT_EQUAL(48, p1->bufSize());
}
