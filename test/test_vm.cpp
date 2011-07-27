#include <scope/test.h>

#include "vm.h"
#include "mockcallback.h"

#include <iostream>

SCOPE_TEST(executeLit) {
  byte b = 'a';
  ProgramPtr p(new Program(1, Instruction::makeLit('a')));
  Vm         s(p);
  Thread cur(&(*p)[0]);
  SCOPE_ASSERT(s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);

  s.reset();
  b = 'c';
  SCOPE_ASSERT(!s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(Thread(&p->back() - 1), s.active().front());
}

SCOPE_TEST(executeEither) {
  byte b = 'z';
  ProgramPtr p(new Program(1, Instruction::makeEither('z', '3')));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);

  s.reset();
  b = '3';
  SCOPE_ASSERT(s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);

  s.reset();
  b = '4';
  SCOPE_ASSERT(!s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&p->back()-1), s.active().front().PC);
}

SCOPE_TEST(executeRange) {
  ProgramPtr p(new Program(1, Instruction::makeRange('c', 't')));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  for (uint32 j = 0; j < 256; ++j) {
    s.reset();
    byte b = j;

    if ('c' <= j && j <= 't') {
      SCOPE_ASSERT(s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);
    }
    else {
      SCOPE_ASSERT(!s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&p->back()-1), s.active().front().PC);
    }
  }
}

SCOPE_TEST(executeAny) {
  ProgramPtr p(new Program(1, Instruction::makeAny()));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  for (uint32 i = 0; i < 256; ++i) {
    s.reset();
    byte b = i;
    SCOPE_ASSERT(s.execute(&cur, &b));
    SCOPE_ASSERT_EQUAL(1u, s.numActive());
    SCOPE_ASSERT_EQUAL(0u, s.numNext());
    SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);
  }
}

SCOPE_TEST(executeJump) {
  ProgramPtr p(new Program(2, Instruction()));
  (*p)[0] = Instruction::makeJump(&(*p)[0], 18);
  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 0));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[18], s.active().front().PC);
}

SCOPE_TEST(executeJumpTable) {
  byte b;
  ProgramPtr pp(new Program(257, Instruction::makeHalt()));
  Program& p = *pp;
  p[0] = Instruction::makeJumpTable();

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
      SCOPE_ASSERT(s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&p[0] + 258, 0, 0, 0), s.active().front());
    }
    else {
      SCOPE_ASSERT(!s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&p.back()-1, 0, 0, 0), s.active().front());
    }
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
  Thread cur(&(*p)[0], 0, 0, 0);

  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    if ('a' == i) {
      SCOPE_ASSERT(s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0] + 3, 0, 0, 0), s.active().front());
    }
    else if ('b' == i) {
      SCOPE_ASSERT(s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0] + 3, 0, 0, 0), s.active().front());
    }
    else {
      SCOPE_ASSERT(!s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&p->back()-1, 0, 0, 0), s.active().front());
    }

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

  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  byte b;
  for (uint32 i = 0; i < 256; ++i) {
    b = i;
    if (i == 'A' || i == 'a' || i == 'B' || i == 'b') {
      SCOPE_ASSERT(s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[9], 0, 0, 0), s.active().front());
    }
    else {
      SCOPE_ASSERT(!s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&p->back()-1, 0, 0, 0), s.active().front());
    }

    s.reset();
  }
}

SCOPE_TEST(executeLabel) {
  ProgramPtr p(new Program(1, Instruction::makeLabel(34)));
  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 57));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 34, 0, 0), s.active().front());
}

SCOPE_TEST(executeMatch) {
  ProgramPtr p(new Program(2, Instruction::makeMatch()));
  (*p)[0] = Instruction::makeLit('a'); // just to keep Vm::init() from executing the match
  Vm s(p);

  Thread cur(&(*p)[1], 0, 0, Thread::NONE);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 57));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[2], 0, 0, 57), s.active().front());
}

SCOPE_TEST(executeFork) {
  ProgramPtr p(new Program(4, Instruction()));
  (*p)[0] = Instruction::makeFork(&(*p)[0], 3);
  (*p)[2] = Instruction::makeLit('a');
  (*p)[3] = Instruction::makeLit('a');
  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 47));
  SCOPE_ASSERT_EQUAL(1u, s.numActive()); // cha-ching!
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[2], s.next()[0].PC);
  SCOPE_ASSERT_EQUAL(&(*p)[3], s.active().front().PC);
}

SCOPE_TEST(executeCheckHalt) {
  ProgramPtr p(new Program(2, Instruction::makeCheckHalt(5)));
  (*p)[1] = Instruction::makeRaw24(3019);
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 231));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), s.active()[0]);

// this code would check the bitvector; not gonna' do this currently, but left as a reminder
// that doing so again in the future might be okay
//  SCOPE_ASSERT(checkStates[5]);
//  SCOPE_ASSERT(checkStates[0]); // this bit is reserved specially to see whether we need to clear the set

  SCOPE_ASSERT(!s.executeEpsilon(&cur, 231));
  SCOPE_ASSERT_EQUAL(2, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), s.active()[1]); // thread died because the state was set
}

SCOPE_TEST(executeHaltNoMatch) {
  ProgramPtr p(new Program(1, Instruction::makeHalt()));
  Vm         s(p);

  Thread cur(&(*p)[0], 0, 0, Thread::NONE);
  SCOPE_ASSERT(!s.executeEpsilon(&cur, 317));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, Thread::NONE), s.active().front());
}

SCOPE_TEST(executeHaltMatch) {
  ProgramPtr p(new Program(1, Instruction::makeHalt()));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(!s.executeEpsilon(&cur, 317));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(cur, s.active().front());
}

SCOPE_TEST(runFrame) {
  MockCallback cb;
  ProgramPtr p(new Program(9, Instruction::makeRaw32(0)));
  Program&   prog(*p);
  // not a complete program, but good enough for executing a frame
  prog[0] = Instruction::makeJump(&prog[0], 2);
  prog[2] = Instruction::makeLit('a');
  prog[3] = Instruction::makeFork(&prog[3], 8);
  prog[5] = Instruction::makeLabel(1);
  prog[6] = Instruction::makeMatch();
  prog[7] = Instruction::makeLit('b');
  prog[8] = Instruction::makeLit('c');
  prog.First.set('a');

  byte b = 'a';
  Vm s(p);
  s.executeFrame(&b, 0, cb);
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(2u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&prog[7], 1, 0, 0), s.next()[0]);
  SCOPE_ASSERT_EQUAL(Thread(&prog[8], Thread::NOLABEL, 0, Thread::NONE), s.next()[1]);
}

SCOPE_TEST(testInit) {
  ProgramPtr p(new Program(14, Instruction::makeRaw32(0)));
  Program& prog(*p);
  prog[0]  = Instruction::makeFork(&prog[0], 7);   // 0
  prog[2]  = Instruction::makeFork(&prog[2], 6);   // 1
  prog[4]  = Instruction::makeJump(&prog[4], 11);   // 2
  prog[6]  = Instruction::makeLit('a');  // 3
  prog[7]  = Instruction::makeFork(&prog[7], 12);   // 4
  prog[9]  = Instruction::makeJump(&prog[9], 13);   // 5
  prog[11] = Instruction::makeLit('b');  // 6
  prog[12] = Instruction::makeLit('c');  // 7
  prog[13] = Instruction::makeLit('d');  // 8
  prog.First.set('a');
  prog.First.set('b');
  prog.First.set('c');
  prog.First.set('d');

  Vm s;
  s.init(p);
  SCOPE_ASSERT_EQUAL(4u, s.first().size());
  SCOPE_ASSERT_EQUAL(&prog[11], s.first()[0].PC);
  SCOPE_ASSERT_EQUAL(&prog[6], s.first()[1].PC);
  SCOPE_ASSERT_EQUAL(&prog[13], s.first()[2].PC);
  SCOPE_ASSERT_EQUAL(&prog[12], s.first()[3].PC);
}

SCOPE_TEST(simpleLitMatch) {
  ProgramPtr p(new Program());
  Program& prog(*p);
  prog.push_back(Instruction::makeLit('a'));
  prog.push_back(Instruction::makeLit('b'));
  prog.push_back(Instruction::makeLabel(3));
  prog.push_back(Instruction::makeMatch());
  prog.push_back(Instruction::makeHalt());
  prog.push_back(Instruction::makeFinish());

  byte text[] = {'a', 'b', 'c'};
  MockCallback cb;
  Vm v;
  prog.First.set('a');
  v.init(p);
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
  v.closeOut(cb);
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(35, 2, 3), cb.Hits[0]);
  text[1] = 'c';
  SCOPE_ASSERT(!v.search(text, &text[3], 35, cb));
}

SCOPE_TEST(newThreadInit) {
  ProgramPtr p(new Program);
  p->push_back(Instruction::makeJumpTableRange('a', 'b')); //  0
  p->push_back(Instruction::makeRaw32(4));                 //  1
  p->push_back(Instruction::makeRaw32(8));                 //  2
  p->push_back(Instruction::makeLit('a'));                 //  3
  p->push_back(Instruction::makeLabel(1));                 //  4
  p->push_back(Instruction::makeMatch());                  //  5
  p->push_back(Instruction::makeHalt());                   //  6
  p->push_back(Instruction::makeLit('b'));                 //  7
  p->push_back(Instruction::makeLit('c'));                 //  8
  p->push_back(Instruction::makeLabel(0));                 //  9
  p->push_back(Instruction::makeMatch());                  // 10
  p->push_back(Instruction::makeHalt());                   // 11
  p->push_back(Instruction::makeFinish());                 // 12
  byte text[] = {'a', 'a', 'b', 'c'};
  MockCallback cb;
  Vm v;
  p->First.set('a');
  p->First.set('b');
  v.init(p);

  v.executeFrame(&text[0], 13, cb);
  SCOPE_ASSERT_EQUAL(1, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 13, 13), v.active()[0]);
  SCOPE_ASSERT_EQUAL(1, v.next().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 13, 13), v.next()[0]);

  v.cleanup();
  SCOPE_ASSERT_EQUAL(1, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 13, 13), v.active()[0]);
  SCOPE_ASSERT_EQUAL(0, v.next().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 13, 13), v.active()[0]);

  v.executeFrame(&text[1], 14, cb);
  SCOPE_ASSERT_EQUAL(2, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(0, 1, 13, 13), v.active()[0]);
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 14, 14), v.active()[1]);
  SCOPE_ASSERT_EQUAL(1, v.next().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 14, 14), v.next()[0]);

  v.cleanup();
  SCOPE_ASSERT_EQUAL(1, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[12], 1, 14, 14), v.active()[0]);
  SCOPE_ASSERT_EQUAL(0, v.next().size());

  v.executeFrame(&text[2], 15, cb);
  SCOPE_ASSERT_EQUAL(2, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(0, 1, 14, 14), v.active()[0]);
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[8], Thread::NOLABEL, 15, Thread::NONE), v.active()[1]);
  SCOPE_ASSERT_EQUAL(1, v.next().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[8], Thread::NOLABEL, 15, Thread::NONE), v.next()[0]);

  v.cleanup();
  SCOPE_ASSERT_EQUAL(1, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[8], Thread::NOLABEL, 15, Thread::NONE), v.active()[0]);
  SCOPE_ASSERT_EQUAL(0, v.next().size());
}

SCOPE_TEST(threeKeywords) {
  ProgramPtr p(new Program(19, Instruction::makeRaw32(0))); // (a)|(b)|(bc)
  Program& prog(*p);

  prog[0]  = Instruction::makeFork(&prog[0], 4);
  prog[2]  = Instruction::makeJump(&prog[2], 8);
  prog[4]  = Instruction::makeLit('a');
  prog[5]  = Instruction::makeLabel(0);
  prog[6]  = Instruction::makeMatch();
  prog[7]  = Instruction::makeHalt();
  prog[8]  = Instruction::makeLit('b');
  prog[9]  = Instruction::makeFork(&prog[9], 14);
  prog[11] = Instruction::makeLabel(1);
  prog[12] = Instruction::makeMatch();
  prog[13] = Instruction::makeHalt();
  prog[14] = Instruction::makeLit('c');
  prog[15] = Instruction::makeLabel(2);
  prog[16] = Instruction::makeMatch();
  prog[17] = Instruction::makeHalt();
  prog[18] = Instruction::makeFinish();

  byte text[] = {'c', 'a', 'b', 'c'};
  MockCallback cb;
  Vm v;
  p->First.set('a');
  p->First.set('b');
  v.init(p);
  SCOPE_ASSERT(!v.search(text, &text[4], 10, cb));
  v.closeOut(cb);
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
  p->push_back(Instruction::makeFinish());
  byte text1[] = {'a', 'c', 'a'},
       text2[] = {'b', 'b'};
  MockCallback cb;
  Vm v;
  p->First.set('a');
  v.init(p);
  SCOPE_ASSERT(v.search(text1, &text1[3], 0, cb));
  SCOPE_ASSERT_EQUAL(0u, cb.Hits.size());
  SCOPE_ASSERT(!v.search(text2, &text2[2], 3, cb));
  v.closeOut(cb);
  SCOPE_ASSERT_EQUAL(1u, cb.Hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 2, 0), cb.Hits[0]);
}
