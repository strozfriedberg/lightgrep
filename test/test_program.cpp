#include <scope/test.h>

#include "program.h"

ProgramPtr makeProgram() {
  ProgramPtr p1(new Program());
  p1->push_back(Instruction::makeLit('a'));
  p1->push_back(Instruction::makeLabel(0));
  p1->push_back(Instruction::makeMatch());
  p1->First.set('a');
  return p1;
}

SCOPE_TEST(testProgramBufSize) {
  ProgramPtr p1(makeProgram());
  SCOPE_ASSERT_EQUAL(48, p1->bufSize());
}

SCOPE_TEST(testProgramSerialization) {
  ProgramPtr  p1(makeProgram());
  std::string buf = p1->marshall();
  ProgramPtr p2 = Program::unmarshall(buf);
  SCOPE_ASSERT(p2);
  SCOPE_ASSERT(*p1 == *p2);
}
