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

#include "byteset.h"
#include "vm.h"
#include "mockcallback.h"
#include "program.h"

#include <iostream>

SCOPE_TEST(executeByte) {
  byte b = 'a';
  ProgramPtr p(new Program(1, Instruction::makeByte('a')));
  Vm         s(p);
  Thread cur(&(*p)[0]);
  SCOPE_ASSERT(s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);

  s.reset();
  b = 'c';
  SCOPE_ASSERT(!s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front());
}

SCOPE_TEST(executeNotByte) {
  byte b = 'a';
  ProgramPtr p(new Program(1, Instruction::makeByte('a', true)));
  Vm         s(p);
  Thread cur(&(*p)[0]);
  SCOPE_ASSERT(!s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());

  s.reset();
  b = 'c';
  SCOPE_ASSERT(s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);
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
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front().PC);
}

SCOPE_TEST(executeNeither) {
  byte b = 'z';
  ProgramPtr p(new Program(1, Instruction::makeEither('z', '3', true)));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(!s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front().PC);

  s.reset();
  b = '3';
  SCOPE_ASSERT(!s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front().PC);

  s.reset();
  b = '4';
  SCOPE_ASSERT(s.execute(&cur, &b));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);
}

SCOPE_TEST(executeRange) {
  ProgramPtr p(new Program(1, Instruction::makeRange('c', 't')));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  for (uint32_t j = 0; j < 256; ++j) {
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
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front().PC);
    }
  }
}

SCOPE_TEST(executeNotInRange) {
  ProgramPtr p(new Program(1, Instruction::makeRange('c', 't', true)));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  for (uint32_t j = 0; j < 256; ++j) {
    s.reset();
    byte b = j;

    if ('c' <= j && j <= 't') {
      SCOPE_ASSERT(!s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0]), s.active().front().PC);
    }
    else {
      SCOPE_ASSERT(s.execute(&cur, &b));
      SCOPE_ASSERT_EQUAL(1u, s.numActive());
      SCOPE_ASSERT_EQUAL(0u, s.numNext());
      SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);
    }
  }
}

SCOPE_TEST(executeAny) {
  ProgramPtr p(new Program(1, Instruction::makeAny()));
  Vm         s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  for (uint32_t i = 0; i < 256; ++i) {
    s.reset();
    byte b = i;
    SCOPE_ASSERT(s.execute(&cur, &b));
    SCOPE_ASSERT_EQUAL(1u, s.numActive());
    SCOPE_ASSERT_EQUAL(0u, s.numNext());
    SCOPE_ASSERT_EQUAL(&(*p)[1], s.active().front().PC);
  }
}

SCOPE_TEST(executeJump) {
  ProgramPtr p(new Program(10, Instruction()));
  Program& prog(*p);
  prog[0] = Instruction::makeJump(&(*p)[0], 7);
  prog[2] = Instruction::makeHalt();
  prog[3] = Instruction::makeHalt();
  prog[4] = Instruction::makeHalt();
  prog[5] = Instruction::makeHalt();
  prog[5] = Instruction::makeHalt();
  prog[6] = Instruction::makeHalt();
  prog[7] = Instruction::makeHalt();
  prog[8] = Instruction::makeHalt();
  prog[9] = Instruction::makeFinish();

  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 0));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[7], s.active().front().PC);
}

SCOPE_TEST(executeJumpTableRange) {
  byte b;
  std::vector<bool> checkStates;
  ProgramPtr p(new Program(3, Instruction::makeHalt()));
  (*p)[0] = Instruction::makeJumpTableRange('a', 'b');
  *(uint32_t*)&((*p)[1]) = 3;
  *(uint32_t*)&((*p)[2]) = 3;

  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);

  for (uint32_t i = 0; i < 256; ++i) {
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
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0], 0, 0, 0), s.active().front());
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
  for (uint32_t i = 0; i < 256; ++i) {
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
      SCOPE_ASSERT_EQUAL(Thread(&(*p)[0], 0, 0, 0), s.active().front());
    }

    s.reset();
  }
}

SCOPE_TEST(executeLabel) {
  ProgramPtr p(new Program(3, Instruction::makeRaw32(0)));
  Program& prog(*p);
  prog[0] = Instruction::makeLabel(34);
  prog[1] = Instruction::makeHalt();
  prog[2] = Instruction::makeFinish();

  prog.MaxLabel = 34;
  prog.MaxCheck = 0;

  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 57));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 34, 0, 0), s.active().front());
}

SCOPE_TEST(executeMatch) {
  ProgramPtr p(new Program(2, Instruction::makeMatch()));
  (*p)[0] = Instruction::makeByte('a'); // just to keep Vm() from executing the match
  p->MaxLabel = 0;
  p->MaxCheck = 0;

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
  (*p)[2] = Instruction::makeByte('a');
  (*p)[3] = Instruction::makeByte('a');

  Vm s(p);
  Thread cur(&(*p)[0], 0, 0, 0);
  SCOPE_ASSERT(s.executeEpsilon(&cur, 47));
  SCOPE_ASSERT_EQUAL(1u, s.numActive()); // cha-ching!
  SCOPE_ASSERT_EQUAL(1u, s.numNext());
  SCOPE_ASSERT_EQUAL(&(*p)[2], s.next()[0].PC);
  SCOPE_ASSERT_EQUAL(&(*p)[3], s.active().front().PC);
}

// re-enable this once check halt is restored to former glory
// SCOPE_TEST(executeCheckHalt) {
//   ProgramPtr p(new Program(2, Instruction::makeCheckHalt(5)));
//   (*p)[1] = Instruction::makeRaw24(3019);
//   Vm         s(p);
//   Thread cur(&(*p)[0], 0, 0, 0);
//   SCOPE_ASSERT(s.executeEpsilon(&cur, 231));
//   SCOPE_ASSERT_EQUAL(1u, s.numActive());
//   SCOPE_ASSERT_EQUAL(0u, s.numNext());
//   SCOPE_ASSERT_EQUAL(Thread(&(*p)[1], 0, 0, 0), s.active()[0]);

// // this code would check the bitvector; not gonna' do this currently, but left as a reminder
// // that doing so again in the future might be okay
// //  SCOPE_ASSERT(checkStates[5]);
// //  SCOPE_ASSERT(checkStates[0]); // this bit is reserved specially to see whether we need to clear the set

//   SCOPE_ASSERT(!s.executeEpsilon(&cur, 231));
//   SCOPE_ASSERT_EQUAL(2, s.numActive());
//   SCOPE_ASSERT_EQUAL(0u, s.numNext());
//   SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, 0), s.active()[1]); // thread died because the state was set
// }

SCOPE_TEST(executeHalt) {
  ProgramPtr p(new Program(1, Instruction::makeHalt()));
  Vm s(p);

  Thread cur(&(*p)[0], 0, 0, Thread::NONE);
  SCOPE_ASSERT(!s.executeEpsilon(&cur, 317));
  SCOPE_ASSERT_EQUAL(1u, s.numActive());
  SCOPE_ASSERT_EQUAL(0u, s.numNext());
  SCOPE_ASSERT_EQUAL(Thread(0, 0, 0, Thread::NONE), s.active().front());
}

SCOPE_TEST(runFrame) {
  ProgramPtr p(new Program(9, Instruction::makeRaw32(0)));
  Program&   prog(*p);
  // not a complete program, but good enough for executing a frame
  prog[0] = Instruction::makeJump(&prog[0], 2);
  prog[2] = Instruction::makeByte('a');
  prog[3] = Instruction::makeFork(&prog[3], 8);
  prog[5] = Instruction::makeLabel(1);
  prog[6] = Instruction::makeMatch();
  prog[7] = Instruction::makeByte('b');
  prog[8] = Instruction::makeByte('c');

  prog.MaxLabel = 1;
  prog.MaxCheck = 0;

  prog.FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    prog.Filter.set((i << 8) | 'a');
  }

  const byte b = 'a';

  Vm s(p);
  s.executeFrame(&b, 0, 0, 0);
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
  prog[6]  = Instruction::makeByte('a');  // 3
  prog[7]  = Instruction::makeFork(&prog[7], 12);   // 4
  prog[9]  = Instruction::makeJump(&prog[9], 13);   // 5
  prog[11] = Instruction::makeByte('b');  // 6
  prog[12] = Instruction::makeByte('c');  // 7
  prog[13] = Instruction::makeByte('d');  // 8

  prog.FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    const uint32_t h = i << 8;
    prog.Filter.set(h | 'a');
    prog.Filter.set(h | 'b');
    prog.Filter.set(h | 'c');
    prog.Filter.set(h | 'd');
  }

  Vm s(p);
  SCOPE_ASSERT_EQUAL(4u, s.first().size());
  SCOPE_ASSERT_EQUAL(&prog[11], s.first()[0].PC);
  SCOPE_ASSERT_EQUAL(&prog[6], s.first()[1].PC);
  SCOPE_ASSERT_EQUAL(&prog[13], s.first()[2].PC);
  SCOPE_ASSERT_EQUAL(&prog[12], s.first()[3].PC);
}

SCOPE_TEST(simpleLitMatch) {
  // "ab"
  ProgramPtr p(new Program(8, Instruction::makeRaw32(0)));
  Program& prog(*p);
  prog[0] = Instruction::makeByte('a');
  prog[1] = Instruction::makeByte('b');
  prog[2] = Instruction::makeLabel(3);
  prog[3] = Instruction::makeMatch();
  prog[4] = Instruction::makeFork(&prog[4], 7);
  prog[6] = Instruction::makeHalt();
  prog[7] = Instruction::makeFinish();

  prog.MaxLabel = 3;
  prog.MaxCheck = 0;

  prog.FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    prog.Filter.set((i << 8) | 'a');
  }

  byte text[] = {'a', 'b', 'c'};

  Vm v(p);
  std::vector<SearchHit> hits;
  SCOPE_ASSERT_EQUAL(38u, v.search(text, text + 3, 35, &mockCallback, &hits));
  v.closeOut(&mockCallback, &hits);
  SCOPE_ASSERT_EQUAL(1u, hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(35, 37, 3), hits[0]);
  text[1] = 'c';
  hits.clear();
  SCOPE_ASSERT_EQUAL(38u, v.search(text, text + 3 , 35, &mockCallback, &hits));
  SCOPE_ASSERT_EQUAL(0u, hits.size());
}

SCOPE_TEST(newThreadInit) {
  ProgramPtr p(new Program(17, Instruction::makeRaw32(0)));
  Program& prog(*p);
  prog[0]  = Instruction::makeJumpTableRange('a', 'b');
  prog[1]  = Instruction::makeRaw32(4);
  prog[2]  = Instruction::makeRaw32(9);
  prog[3]  = Instruction::makeByte('a');
  prog[4]  = Instruction::makeLabel(1);
  prog[5]  = Instruction::makeMatch();
  prog[6]  = Instruction::makeFork(&prog[6], 16);
  prog[8]  = Instruction::makeHalt();
  prog[9]  = Instruction::makeByte('b');
  prog[10]  = Instruction::makeByte('c');
  prog[11] = Instruction::makeLabel(0);
  prog[12] = Instruction::makeMatch();
  prog[13] = Instruction::makeFork(&prog[13], 16);
  prog[15] = Instruction::makeHalt();
  prog[16] = Instruction::makeFinish();

  prog.MaxLabel = 1;
  prog.MaxCheck = 0;

  const byte text[] = {'a', 'a', 'b', 'c'};

  p->FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    const uint32_t h = i << 8;
    p->Filter.set(h | 'a');
    p->Filter.set(h | 'b');
  }

  Vm v(p);

  v.executeFrame(&text[0], 13, 0, 0);
  SCOPE_ASSERT_EQUAL(1u, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(0, 1, 13, 13), v.active()[0]);
  SCOPE_ASSERT_EQUAL(0u, v.next().size());

  v.cleanup();
  SCOPE_ASSERT_EQUAL(0u, v.active().size());
  SCOPE_ASSERT_EQUAL(0u, v.next().size());

  v.executeFrame(&text[1], 14, 0, 0);
  SCOPE_ASSERT_EQUAL(1u, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(0, 1, 14, 14), v.active()[0]);
  SCOPE_ASSERT_EQUAL(0u, v.next().size());

  v.cleanup();
  SCOPE_ASSERT_EQUAL(0u, v.active().size());
  SCOPE_ASSERT_EQUAL(0u, v.next().size());

  v.executeFrame(&text[2], 15, 0, 0);
  SCOPE_ASSERT_EQUAL(1u, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[9], Thread::NOLABEL, 15, Thread::NONE), v.active()[0]);
  SCOPE_ASSERT_EQUAL(1u, v.next().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[9], Thread::NOLABEL, 15, Thread::NONE), v.next()[0]);

  v.cleanup();
  SCOPE_ASSERT_EQUAL(1u, v.active().size());
  SCOPE_ASSERT_EQUAL(Thread(&(*p)[9], Thread::NOLABEL, 15, Thread::NONE), v.active()[0]);
  SCOPE_ASSERT_EQUAL(0u, v.next().size());
}

SCOPE_TEST(threeKeywords) {
  ProgramPtr p(new Program(25, Instruction::makeRaw32(0))); // (a)|(b)|(bc)
  Program& prog(*p);

  prog[0]  = Instruction::makeFork(&prog[0], 4);
  prog[2]  = Instruction::makeJump(&prog[2], 10);
  prog[4]  = Instruction::makeByte('a');
  prog[5]  = Instruction::makeLabel(0);
  prog[6]  = Instruction::makeMatch();
  prog[7]  = Instruction::makeFork(&prog[7], 24);
  prog[9]  = Instruction::makeHalt();
  prog[10] = Instruction::makeByte('b');
  prog[11] = Instruction::makeFork(&prog[11], 18);
  prog[13] = Instruction::makeLabel(1);
  prog[14] = Instruction::makeMatch();
  prog[15] = Instruction::makeFork(&prog[15], 24);
  prog[17] = Instruction::makeHalt();
  prog[18] = Instruction::makeByte('c');
  prog[19] = Instruction::makeLabel(2);
  prog[20] = Instruction::makeMatch();
  prog[21] = Instruction::makeFork(&prog[21], 24);
  prog[23] = Instruction::makeHalt();
  prog[24] = Instruction::makeFinish();

  prog.MaxLabel = 2;
  prog.MaxCheck = 0;

  const byte text[] = {'c', 'a', 'b', 'c'};

  p->FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    const uint32_t h = i << 8;
    p->Filter.set(h | 'a');
    p->Filter.set(h | 'b');
  }

  Vm v(p);
  std::vector<SearchHit> hits;
  SCOPE_ASSERT_EQUAL(14u, v.search(text, &text[4], 10, &mockCallback, &hits));
  v.closeOut(&mockCallback, &hits);
  SCOPE_ASSERT_EQUAL(3u, hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(11, 12, 0), hits[0]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 13, 1), hits[1]);
  SCOPE_ASSERT_EQUAL(SearchHit(12, 14, 2), hits[2]);
}

SCOPE_TEST(stitchedText) {
  ProgramPtr p(new Program(8, Instruction::makeRaw32(0)));
  Program& prog(*p);
  prog[0] = Instruction::makeByte('a');
  prog[1] = Instruction::makeByte('b');
  prog[2] = Instruction::makeLabel(0);
  prog[3] = Instruction::makeMatch();
  prog[4] = Instruction::makeFork(&prog[4], 7);
  prog[6] = Instruction::makeHalt();
  prog[7] = Instruction::makeFinish();

  prog.MaxLabel = 0;
  prog.MaxCheck = 0;

  const byte text1[] = {'a', 'c', 'a'};
  const byte text2[] = {'b', 'b'};

  p->FilterOff = 0;
  for (uint32_t i = 0; i < 256; ++i) {
    p->Filter.set((i << 8) | 'a');
  }

  Vm v(p);
  std::vector<SearchHit> hits;
  SCOPE_ASSERT_EQUAL(2u, v.search(text1, &text1[3], 0, &mockCallback, &hits));
  SCOPE_ASSERT_EQUAL(0u, hits.size());
  SCOPE_ASSERT_EQUAL(5u, v.search(text2, &text2[2], 3, &mockCallback, &hits));
  v.closeOut(&mockCallback, &hits);
  SCOPE_ASSERT_EQUAL(1u, hits.size());
  SCOPE_ASSERT_EQUAL(SearchHit(2, 4, 0), hits[0]);
}
