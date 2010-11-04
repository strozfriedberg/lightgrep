#include <scope/test.h>

#include "vm.h"
#include "MockCallback.h"

#include <iostream>

SCOPE_TEST(executeLit) {
  byte b = 'a';
  ProgramPtr p(new Program(1, Instruction::makeLit('a')));
  Vm         s(p);
  Thread     cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(!s.execute(cur, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), s.next()[0]);

  cur.PC = &(*p)[0];
  s.reset();
  b = 'c';
  SCOPE_ASSERT(!s.execute(cur, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
}

SCOPE_TEST(executeEither) {
  byte b = 'z';
  ProgramPtr p(new Program(1, Instruction::makeEither('z', '3')));
  Vm         s(p);
  Thread     cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(!s.execute(cur, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), s.next()[0]);
  SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);

  s.reset();
  b = '3';
  cur.PC = &(*p)[0];
  SCOPE_ASSERT(!s.execute(cur, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), s.next()[0]);
  SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);

  s.reset();
  b = '4';
  cur.PC = &(*p)[0];
  SCOPE_ASSERT(!s.execute(cur, &b, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
}

SCOPE_TEST(executeRange) {
  ProgramPtr p(new Program(1, Instruction::makeRange('c', 't')));
  Vm         s(p);
  Thread     cur(&(*p)[0], 0, 0, 0);
  for (uint32 j = 0; j < 256; ++j) {
    s.reset();
    byte b = j;
    cur.PC = &(*p)[0];
    SCOPE_ASSERT(!s.execute(cur, &b, 0));
    if ('c' <= j && j <= 't') {
      SCOPE_ASSERT_EQUAL(0u, s.numActive());
      SCOPE_ASSERT_EQUAL(1u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), s.next()[0]);      
      SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
    }
  }
}

SCOPE_TEST(executeJump) {
  ProgramPtr p(new Program(1, Instruction::makeJump(18)));
  Vm         s(p);
  Thread     cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[18], cur.PC);
}

SCOPE_TEST(executeJumpTable) {
  byte b;
  ProgramPtr  prog(new Program(257, Instruction::makeHalt());
  *prog[0]  = Instruction::makeJumpTable();
  *prog[66] = Instruction::makeJump(258);
  Vm  s(p);
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    s.reset();
    Thread cur(prog.get(), 0, 0, 0);
    SCOPE_ASSERT(!s.execute(cur, &b, 0));
    SCOPE_ASSERT_EQUAL(0u, s.numActive());
    if (i == 'A') {
      SCOPE_ASSERT_EQUAL(1u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&(*prog)[0] + 1 + b, 0, 0, 0), s.next()[0]);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
    }
  }
}

SCOPE_TEST(executeJumpTableRange) {
  byte b;
  std::vector<bool> checkStates;
  Program prog(3, Instruction::makeHalt());
  Instruction instr = Instruction::makeJumpTableRange('a', 'b');
  Vm::ThreadList next, active;
  
  prog[0] = instr;
  prog[1] = Instruction::makeJump(3);
  prog[2] = Instruction::makeJump(3);
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    next.clear();
    active.clear();
    Thread cur(&prog[0], 0, 0, 0);
    SCOPE_ASSERT(!Vm::execute(&prog[0], cur, checkStates, active, next, &b, 0));
    SCOPE_ASSERT_EQUAL(0u, active.size());
    if ('a' == i) {
      SCOPE_ASSERT_EQUAL(1u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(&prog[0] + 1, 0, 0, 0), next[0]);
    }
    else if ('b' == i) {
      SCOPE_ASSERT_EQUAL(1u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(&prog[0] + 2, 0, 0, 0), next[0]);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
    }
  }
}

SCOPE_TEST(executeBitVector) {
  SCOPE_ASSERT_EQUAL(32u, sizeof(ByteSet));

  Program prog(9, Instruction::makeHalt());
  prog[0] = Instruction::makeBitVector();
  ByteSet *setPtr = reinterpret_cast<ByteSet*>(&prog[1]); // so evil, it hurts
  setPtr->reset();
  setPtr->set('A');
  setPtr->set('a');
  setPtr->set('B');
  setPtr->set('b');

  // std::cout << prog;

  std::vector<bool> checkStates;
  Vm::ThreadList  next,
                  active;
  byte b;
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    next.clear();
    active.clear();
    Thread  cur(&prog[0], 0, 0, 0);
    SCOPE_ASSERT(!Vm::execute(&prog[0], cur, checkStates, active, next, &b, 0));
    SCOPE_ASSERT_EQUAL(0u, active.size());
    if (i == 'A' || i == 'a' || i == 'B' || i == 'b') {
      SCOPE_ASSERT_EQUAL(1u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(&prog[9], 0, 0, 0), next[0]);
    }
    else {
      SCOPE_ASSERT_EQUAL(0u, next.size());
      SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
    }
  }
}

SCOPE_TEST(executeMatch) {
  byte b;
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeMatch(3);
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, checkStates, active, next, &b, 57));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+1, 3, 0, 57), cur);
}

SCOPE_TEST(executeFork) {
  byte b;
  std::vector<bool> checkStates;
  Instruction i = Instruction::makeFork(237);
  Thread      cur(&i, 0, 0, 0);
  Vm::ThreadList  next,
              active;
  SCOPE_ASSERT(Vm::execute(&i, cur, checkStates, active, next, &b, 47));
  SCOPE_ASSERT_EQUAL(1u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(&i+237, 0, 0, 0), active[0]);
  SCOPE_ASSERT_EQUAL(&i+1, cur.PC);
}

SCOPE_TEST(executeCheckBranch) {
  byte b;
  std::vector<bool> checkStates(6, false);
  Instruction i[] = {Instruction::makeCheckBranch(5), Instruction::makeJump(3019)};
  Thread      cur(i, 0, 0, 0);
  Vm::ThreadList next,
                 active;
  SCOPE_ASSERT(Vm::execute(i, cur, checkStates, active, next, &b, 231));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(i+1, 0, 0, 0), cur);
  SCOPE_ASSERT(checkStates[5]);
  SCOPE_ASSERT(checkStates[0]); // this bit is reserved specially to see whether we need to clear the set

  cur.PC = i;
  SCOPE_ASSERT(Vm::execute(i, cur, checkStates, active, next, &b, 231));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(i+2, 0, 0, 0), cur); // skipped ahead because the state was set
  SCOPE_ASSERT(checkStates[5]);
  SCOPE_ASSERT(checkStates[0]);
}

SCOPE_TEST(executeHalt) {
  byte b;
  std::vector<bool> checkStates(1, false);
  Instruction i = Instruction::makeHalt();
  Thread cur(&i, 0, 0, 0);
  Vm::ThreadList next, active;
  SCOPE_ASSERT(!Vm::execute(&i, cur, checkStates, active, next, &b, 317));
  SCOPE_ASSERT_EQUAL(0u, active.size());
  SCOPE_ASSERT_EQUAL(0u, next.size());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
}

SCOPE_TEST(simpleLitMatch) {
  ProgramPtr p(new Program());
  Program& prog(*p);
  prog.push_back(Instruction::makeLit('a'));
  prog.push_back(Instruction::makeLit('b'));
  prog.push_back(Instruction::makeMatch(3));
  prog.push_back(Instruction::makeHalt());

  byte text[] = {'a', 'b', 'c'};
  MockCallback cb;
  Vm v;
  prog.First.set('a');
  v.init(p);
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(35, 2, 3), cb.Hits[0]);
  text[1] = 'c';
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
}

SCOPE_TEST(threeKeywords) {
  ProgramPtr p(new Program); // (a)|(b)|(bc)
  p->push_back(Instruction::makeFork(2));       // 0
  p->push_back(Instruction::makeJump(5));       // 1
  p->push_back(Instruction::makeLit('a'));      // 2
  p->push_back(Instruction::makeMatch(0));       // 3
  p->push_back(Instruction::makeHalt());        // 4
  p->push_back(Instruction::makeLit('b'));      // 5
  p->push_back(Instruction::makeFork(9));      // 6
  p->push_back(Instruction::makeMatch(1));       // 7
  p->push_back(Instruction::makeHalt());        // 8
  p->push_back(Instruction::makeLit('c'));      // 9
  p->push_back(Instruction::makeMatch(2));       // 10
  p->push_back(Instruction::makeHalt());        // 11

  byte text[] = {'c', 'a', 'b', 'c'};
  MockCallback cb;
  Vm v;
  p->First.set('a');
  p->First.set('b');
  v.init(p);
  SCOPE_ASSERT(!v.search(text, &text[4], 10, cb));
  SCOPE_ASSERT_EQUAL(3u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(11, 1, 0), cb.Hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 1, 1), cb.Hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 2, 2), cb.Hits[2]);
}

SCOPE_TEST(stitchedText) {
  ProgramPtr p(new Program);
  p->push_back(Instruction::makeLit('a'));
  p->push_back(Instruction::makeLit('b'));
  p->push_back(Instruction::makeMatch(0));
  p->push_back(Instruction::makeHalt());
  byte text1[] = {'a', 'c', 'a'},
       text2[] = {'b', 'b'};
  MockCallback cb;
  Vm v;
  p->First.set('a');
  v.init(p);
  SCOPE_ASSERT(v.search(text1, &text1[3], 0, cb));
  SCOPE_ASSERT_EQUAL(0u, cb.Hits.size());
  SCOPE_ASSERT(!v.search(text2, &text2[2], 3, cb));
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), cb.Hits[0]);
}
