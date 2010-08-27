#include <scope/test.h>
#include <boost/smart_ptr.hpp>

#include "states.h"
#include "instructions.h"
#include "program.h"

#include <iostream>

template<class TransitionType>
void testClone(const TransitionType& toCopy, byte* text) {
  boost::shared_array<byte> buf(new byte[toCopy.objSize()]);
  TransitionType* dupe(toCopy.clone(buf.get()));
  SCOPE_ASSERT_EQUAL(buf.get(), (byte*)dupe);
  SCOPE_ASSERT_EQUAL(text+1, dupe->allowed(text, text+1));
}

SCOPE_TEST(litAccept) {
  const LitState lit('a');
  byte ch[2] = "a";
  SCOPE_ASSERT_EQUAL(ch+1, lit.allowed(ch, ch+1));
  ch[0] = 'b';
  SCOPE_ASSERT_EQUAL(ch, lit.allowed(ch, ch+1));
  std::bitset<256> bits(0);
  lit.getBits(bits);
  SCOPE_ASSERT_EQUAL(1u, bits.count());
  SCOPE_ASSERT(bits.test('a'));
  SCOPE_ASSERT(bits.any());
  SCOPE_ASSERT(!bits.test('c'));

  Instruction instr;
  SCOPE_ASSERT_EQUAL(1u, lit.numInstructions());
  SCOPE_ASSERT(lit.toInstruction(&instr));
  SCOPE_ASSERT_EQUAL(Instruction::makeLit('a'), instr);

  SCOPE_ASSERT_EQUAL(sizeof(Transition) + 1, lit.objSize());
  ch[0] = 'a';
  testClone(lit, ch);
  SCOPE_ASSERT_EQUAL("a", lit.label());
}

SCOPE_TEST(eitherAccept) {
  const EitherState e('A', 'a');
  byte ch = 'a';
  SCOPE_ASSERT_EQUAL(&ch+1, e.allowed(&ch, &ch+1));
  ch = 'b';
  SCOPE_ASSERT_EQUAL(&ch, e.allowed(&ch, &ch+1));
  ch = 'A';
  SCOPE_ASSERT_EQUAL(&ch+1, e.allowed(&ch, &ch+1));
  
  std::bitset<256> bits(0);
  e.getBits(bits);
  SCOPE_ASSERT_EQUAL(2u, bits.count());
  SCOPE_ASSERT(bits.test('a'));
  SCOPE_ASSERT(bits.test('A'));
  SCOPE_ASSERT(!bits.test('#'));

  Instruction instr;
  SCOPE_ASSERT_EQUAL(1u, e.numInstructions());
  SCOPE_ASSERT(e.toInstruction(&instr));
  SCOPE_ASSERT_EQUAL(Instruction::makeEither('A', 'a'), instr);

  SCOPE_ASSERT_EQUAL(sizeof(Transition) + 2, e.objSize());
  testClone(e, &ch);
  SCOPE_ASSERT_EQUAL("Aa", e.label());
}

SCOPE_TEST(rangeAccept) {
  const RangeState r('0', '9');
  byte ch;
  std::bitset<256> bits(0);
  r.getBits(bits);
  SCOPE_ASSERT_EQUAL(10u, bits.count());
  for (unsigned int i = 0; i < 256; ++i) {
    ch = i;
    if ('0' <= ch && ch <= '9') {
      SCOPE_ASSERT_EQUAL(&ch+1, r.allowed(&ch, &ch+1));
      SCOPE_ASSERT(bits.test(ch));
    }
    else {
      SCOPE_ASSERT_EQUAL(&ch, r.allowed(&ch, &ch+1));
      SCOPE_ASSERT(!bits.test(ch));
    }
  }
  Instruction instr;
  SCOPE_ASSERT_EQUAL(1u, r.numInstructions());
  SCOPE_ASSERT(r.toInstruction(&instr));
  SCOPE_ASSERT_EQUAL(Instruction::makeRange('0', '9'), instr);

  SCOPE_ASSERT_EQUAL(sizeof(Transition) + 2, r.objSize());
  ch = '1';
  testClone(r, &ch);
  SCOPE_ASSERT_EQUAL("0-9", r.label());
}

SCOPE_TEST(charClassState) {
  ByteSet set;
  set.reset();
  set.set('A');
  set.set('a');
  set.set('B');
  set.set('b');
  const CharClassState s(set, "AaBb");
  ByteSet bits;
  bits.reset();
  s.getBits(bits);
  SCOPE_ASSERT_EQUAL(set, bits);
  SCOPE_ASSERT_EQUAL(9u, s.numInstructions());
  Program p(9, Instruction::makeHalt());
  SCOPE_ASSERT(s.toInstruction(&p[0]));
  SCOPE_ASSERT_EQUAL(Instruction::makeBitVector(), p[0]);
  ByteSet* setPtr = reinterpret_cast<ByteSet*>(&p[1]);
  SCOPE_ASSERT_EQUAL(set, *setPtr);
  SCOPE_ASSERT_EQUAL("AaBb", s.label());
}
