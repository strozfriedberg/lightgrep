#include <scope/test.h>

#include "vm.h"
#include "MockCallback.h"

#include <iostream>

SCOPE_TEST(executeLit) {
  byte b = 'a';
  ProgramPtr p(new Program(1, Instruction::makeLit('a')));
  Vm         s(p);
  Thread     cur(&(*p)[0]);
  SCOPE_ASSERT(s.execute(cur, &b));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);

  cur.PC = &(*p)[0];
  s.reset();
  b = 'c';
  SCOPE_ASSERT(!s.execute(cur, &b));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(), cur);
}

SCOPE_TEST(executeEither) {
  byte b = 'z';
  ProgramPtr p(new Program(1, Instruction::makeEither('z', '3')));
  Vm         s(p);
  Thread     cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.execute(cur, &b));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);

  s.reset();
  b = '3';
  cur.PC = &(*p)[0];
  SCOPE_ASSERT(s.execute(cur, &b));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);

  s.reset();
  b = '4';
  cur.PC = &(*p)[0];
  SCOPE_ASSERT(!s.execute(cur, &b));
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
    if ('c' <= j && j <= 't') {
      SCOPE_ASSERT(s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(0u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(&(*p)[1], cur.PC);
    }
    else {
      SCOPE_ASSERT(!s.execute(cur, &b));
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

SCOPE_TEST(executeLongJump) {
  ProgramPtr p(new Program(2, Instruction()));
  (*p)[0] = Instruction::makeLongJump(&(*p)[1], 18);
  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 0));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[18], cur.PC);
}

SCOPE_TEST(executeJumpTable) {
  byte b;
  ProgramPtr pp(new Program(257, Instruction::makeHalt()));
  Program& p = *pp;
  p[0]  = Instruction::makeJumpTable();

  for (uint32 i = 1; i < 257; ++i) {
    *(uint32*)&(p[i]) = 0xffffffff;
  }

  *(uint32*)&(p[66]) = 258;

  Vm s(pp);
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    s.reset();
    Thread cur(&p[0], 0, 0, 0);
    if (i == 'A') {
      SCOPE_ASSERT(s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(&p[0] + 258, 0, 0, 0), cur);
    }
    else {
      SCOPE_ASSERT(!s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
    }
    SCOPE_ASSERT_EQUAL(0u, s.numActive());
    SCOPE_ASSERT_EQUAL(0u, s.numNext());
  }
}

SCOPE_TEST(executeJumpTableRange) {
  byte b;
  std::vector<bool> checkStates;
  ProgramPtr p(new Program(3, Instruction::makeHalt()));
  (*p)[0] = Instruction::makeJumpTableRange('a', 'b');
  *(uint32*)&((*p)[1]) = 3;
  *(uint32*)&((*p)[2]) = 3;

  Vm s(p);
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    Thread cur(&(*p)[0], 0, 0, 0);
    if ('a' == i) {
      SCOPE_ASSERT(s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0] + 3, 0, 0, 0), cur);
    }
    else if ('b' == i) {
      SCOPE_ASSERT(s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0] + 3, 0, 0, 0), cur);
    }
    else {
      SCOPE_ASSERT(!s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
    }
    SCOPE_ASSERT_EQUAL(0u, s.numActive());
    SCOPE_ASSERT_EQUAL(0u, s.numNext());
    s.reset();
  }
}

SCOPE_TEST(executeBitVector) {
  SCOPE_ASSERT_EQUAL(32u, sizeof(ByteSet));

  ProgramPtr p(new Program(9, Instruction::makeHalt()));
  (*p)[0] = Instruction::makeBitVector();
  ByteSet *setPtr = reinterpret_cast<ByteSet*>(&(*p)[1]); // so evil, it hurts; the makeHalt() thing is truly heinous
  setPtr->reset();
  setPtr->set('A');
  setPtr->set('a');
  setPtr->set('B');
  setPtr->set('b');

  // std::cout << prog;

  Vm s(p);
  byte b;
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    Thread  cur(&(*p)[0], 0, 0, 0);
    if (i == 'A' || i == 'a' || i == 'B' || i == 'b') {
      SCOPE_ASSERT(s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[9], 0, 0, 0), cur);
    }
    else {
      SCOPE_ASSERT(!s.execute(cur, &b));
      SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
    }
    SCOPE_ASSERT_EQUAL(0u, s.numNext());
    SCOPE_ASSERT_EQUAL(0u, s.numActive());
    s.reset();
  }
}

SCOPE_TEST(executeLabel) {
  ProgramPtr p(new Program(1, Instruction::makeLabel(34)));
  Vm s(p);
  Thread      cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 57));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 34, 0, 0), cur);
}

SCOPE_TEST(executeMatch) {
  ProgramPtr p(new Program(1, Instruction::makeMatch()));
  Vm s(p);
  Thread      cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 57));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 57), cur);
}

SCOPE_TEST(executeFork) {
  ProgramPtr p(new Program(3, Instruction::makeLit('a')));
  (*p)[0] = Instruction::makeFork(2);
  Vm s(p);
  Thread      cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 47));
  SCOPE_ASSERT_EQUAL(0u, s.numActive()); // cha-ching!
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.next()[0].PC);
  SCOPE_ASSERT_EQUAL(&(*p)[2], cur.PC);
}

SCOPE_TEST(executeLongFork) {
  ProgramPtr p(new Program(4, Instruction()));
  (*p)[0] = Instruction::makeLongFork(&(*p)[1], 3);
  (*p)[2] = Instruction::makeLit('a');
  (*p)[3] = Instruction::makeLit('a');
  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 47));
  SCOPE_ASSERT_EQUAL(0u, s.numActive()); // cha-ching!
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[2], s.next()[0].PC);
  SCOPE_ASSERT_EQUAL(&(*p)[3], cur.PC);
}

SCOPE_TEST(executeCheckHalt) {
  ProgramPtr p(new Program(2, Instruction::makeCheckHalt(5)));
  (*p)[1] = Instruction::makeJump(3019);
  Vm         s(p);
  Thread     cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(cur, 231));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), cur);

// this code would check the bitvector; not gonna' do this currently, but left as a reminder
// that doing so again in the future might be okay
//  SCOPE_ASSERT(checkStates[5]);
//  SCOPE_ASSERT(checkStates[0]); // this bit is reserved specially to see whether we need to clear the set

  cur.PC = &(*p)[0];
  SCOPE_ASSERT(!s.executeEpsilon(cur, 231));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur); // thread died because the state was set
}

SCOPE_TEST(executeHalt) {
  ProgramPtr p(new Program(1, Instruction::makeHalt()));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(!s.executeEpsilon(cur, 317));
  SCOPE_ASSERT_EQUAL(0u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), cur);
}

SCOPE_TEST(runFrame) {
  MockCallback cb;
  ProgramPtr p(new Program());
  Program&   prog(*p);
  // not a complete program, but good enough for executing a frame
  prog.push_back(Instruction::makeJump(1));  // 0
  prog.push_back(Instruction::makeLit('a')); // 1
  prog.push_back(Instruction::makeFork(6));  // 2
  prog.push_back(Instruction::makeLabel(1)); // 3
  prog.push_back(Instruction::makeMatch());  // 4 
  prog.push_back(Instruction::makeLit('b')); // 5
  prog.push_back(Instruction::makeLit('c')); // 6
  prog.First.set('a');

  const uint64 unalloc = std::numeric_limits<uint64>::max();
  Vm s(p);
  byte b = 'a';
  s.executeFrame(&b, 0, cb);
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(2u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&prog[5], 1, 0, 0), s.next()[0]);
  SCOPE_ASSERT_EQUAL(Thread(&prog[6], std::numeric_limits<uint32>::max(), 0, unalloc), s.next()[1]);
}

SCOPE_TEST(testInit) {
  ProgramPtr p(new Program);
  Program& prog(*p);
  prog.push_back(Instruction::makeFork(4));   // 0
  prog.push_back(Instruction::makeFork(3));   // 1
  prog.push_back(Instruction::makeJump(6));   // 2
  prog.push_back(Instruction::makeLit('a'));  // 3
  prog.push_back(Instruction::makeFork(7));   // 4
  prog.push_back(Instruction::makeJump(8));   // 5
  prog.push_back(Instruction::makeLit('b'));  // 6
  prog.push_back(Instruction::makeLit('c'));  // 7
  prog.push_back(Instruction::makeLit('d'));  // 8
  prog.First.set('a');
  prog.First.set('b');
  prog.First.set('c');
  prog.First.set('d');

  Vm s;
  s.init(p);
  SCOPE_ASSERT_EQUAL(4u, s.first().size());
  SCOPE_ASSERT_EQUAL(&prog[6], s.first()[0].PC);
  SCOPE_ASSERT_EQUAL(&prog[3], s.first()[1].PC);
  SCOPE_ASSERT_EQUAL(&prog[8], s.first()[2].PC);
  SCOPE_ASSERT_EQUAL(&prog[7], s.first()[3].PC);
}

SCOPE_TEST(simpleLitMatch) {
  ProgramPtr p(new Program());
  Program& prog(*p);
  prog.push_back(Instruction::makeLit('a'));
  prog.push_back(Instruction::makeLit('b'));
  prog.push_back(Instruction::makeLabel(3));
  prog.push_back(Instruction::makeMatch());
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
  p->push_back(Instruction::makeJump(6));       // 1
  p->push_back(Instruction::makeLit('a'));      // 2
  p->push_back(Instruction::makeLabel(0));      // 3
  p->push_back(Instruction::makeMatch());       // 4
  p->push_back(Instruction::makeHalt());        // 5
  p->push_back(Instruction::makeLit('b'));      // 6
  p->push_back(Instruction::makeFork(11));      // 7
  p->push_back(Instruction::makeLabel(1));      // 8
  p->push_back(Instruction::makeMatch());       // 9
  p->push_back(Instruction::makeHalt());        // 10
  p->push_back(Instruction::makeLit('c'));      // 11
  p->push_back(Instruction::makeLabel(2));      // 12
  p->push_back(Instruction::makeMatch());       // 13
  p->push_back(Instruction::makeHalt());        // 14

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
  p->push_back(Instruction::makeLabel(0));
  p->push_back(Instruction::makeMatch());
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
