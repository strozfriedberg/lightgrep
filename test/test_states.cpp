/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <catch2/catch_test_macros.hpp>
#include <boost/smart_ptr.hpp>

#include "states.h"
#include "instructions.h"
#include "program.h"

#include <iostream>

template<class TransitionType>
void testClone(const TransitionType& toCopy, byte* text) {
  boost::shared_array<byte> buf(new byte[toCopy.objSize()]);
  TransitionType* dupe(toCopy.clone(buf.get()));
  REQUIRE(buf.get() == (byte*)dupe);
  REQUIRE(text+1 == dupe->allowed(text, text+1));
}

TEST_CASE("byteAccept") {
  const ByteState lit('a');
  byte ch[2] = "a";
  REQUIRE(ch+1 == lit.allowed(ch, ch+1));
  ch[0] = 'b';
  REQUIRE(ch == lit.allowed(ch, ch+1));
  ByteSet bits(0);
  lit.getBytes(bits);
  REQUIRE(1u == bits.count());
  REQUIRE(bits.test('a'));
  REQUIRE(bits.any());
  REQUIRE(!bits.test('c'));

  Instruction instr;
  REQUIRE(1u == lit.numInstructions());
  REQUIRE(lit.toInstruction(&instr));
  REQUIRE(Instruction::makeByte('a') == instr);

  ch[0] = 'a';
  testClone(lit, ch);
  REQUIRE("a" == lit.label());
}

TEST_CASE("eitherAccept") {
  const EitherState e('A', 'a');
  byte ch = 'a';
  REQUIRE(&ch+1 == e.allowed(&ch, &ch+1));
  ch = 'b';
  REQUIRE(&ch == e.allowed(&ch, &ch+1));
  ch = 'A';
  REQUIRE(&ch+1 == e.allowed(&ch, &ch+1));

  ByteSet bits(0);
  e.getBytes(bits);
  REQUIRE(2u == bits.count());
  REQUIRE(bits.test('a'));
  REQUIRE(bits.test('A'));
  REQUIRE(!bits.test('#'));

  Instruction instr;
  REQUIRE(1u == e.numInstructions());
  REQUIRE(e.toInstruction(&instr));
  REQUIRE(Instruction::makeEither('A', 'a') == instr);

  testClone(e, &ch);
  REQUIRE("Aa" == e.label());
}

TEST_CASE("rangeAccept") {
  const RangeState r('0', '9');
  byte ch;
  ByteSet bits(0);
  r.getBytes(bits);
  REQUIRE(10u == bits.count());
  for (unsigned int i = 0; i < 256; ++i) {
    ch = i;
    if ('0' <= ch && ch <= '9') {
      REQUIRE(&ch+1 == r.allowed(&ch, &ch+1));
      REQUIRE(bits.test(ch));
    }
    else {
      REQUIRE(&ch == r.allowed(&ch, &ch+1));
      REQUIRE(!bits.test(ch));
    }
  }
  Instruction instr;
  REQUIRE(1u == r.numInstructions());
  REQUIRE(r.toInstruction(&instr));
  REQUIRE(Instruction::makeRange('0', '9') == instr);

  ch = '1';
  testClone(r, &ch);
  REQUIRE("0-9" == r.label());
}

TEST_CASE("charClassState") {
  ByteSet set;
  set.reset();
  set.set('A');
  set.set('a');
  set.set('B');
  set.set('b');
  const ByteSetState s(set);
  ByteSet bits;
  bits.reset();
  s.getBytes(bits);
  REQUIRE(set == bits);
  REQUIRE(9u == s.numInstructions());
  Program p(9, Instruction::makeHalt());
  REQUIRE(s.toInstruction(&p[0]));
  REQUIRE(Instruction::makeBitVector() == p[0]);
  ByteSet* setPtr = reinterpret_cast<ByteSet*>(&p[1]);
  REQUIRE(set == *setPtr);
  REQUIRE("ABab" == s.label());
}
