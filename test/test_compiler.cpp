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

#include "catch.hpp"

#include "test_helper.h"
#include "compiler.h"
#include "program.h"

TEST_CASE("acOrbcProgram") {
  NFA fsm(4);

  edge(0, 1, fsm, fsm.TransFac->getByte('a')); // ac|bc
  edge(0, 2, fsm, fsm.TransFac->getByte('b'));
  edge(1, 3, fsm, fsm.TransFac->getByte('c'));
  edge(2, 3, fsm, fsm.TransFac->getByte('c'));
  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);

  REQUIRE(10u == prog.size());
  REQUIRE(Instruction::makeFork(&prog[0], 5) == prog[0]);
  REQUIRE(Instruction::makeByte('a') == prog[2]);
  REQUIRE(Instruction::makeByte('c') == prog[3]);
  REQUIRE(Instruction::makeCheckHalt(1) == prog[4]);
  REQUIRE(Instruction::makeByte('b') == prog[5]);
  REQUIRE(Instruction::makeJump(&prog[6],2) == prog[6]);
  REQUIRE(Instruction::makeHalt() == prog[8]);
  REQUIRE(Instruction::makeFinish() == prog[9]);
}

TEST_CASE("keywordLabelsProgram") {
  NFA fsm(4);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(0, 2, fsm, fsm.TransFac->getByte('b'));
  edge(2, 3, fsm, fsm.TransFac->getByte('c'));

  fsm[1].Label = 0;
  fsm[3].Label = 1;

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);

  REQUIRE(9u == prog.size());
  REQUIRE(Instruction::makeFork(&prog[0], 5) == prog[0]);
  REQUIRE(Instruction::makeByte('a') == prog[2]);
  REQUIRE(Instruction::makeLabel(0) == prog[3]);
  REQUIRE(Instruction::makeByte('b') == prog[4]);
  REQUIRE(Instruction::makeByte('c') == prog[5]);
  REQUIRE(Instruction::makeLabel(1) == prog[6]);
  REQUIRE(Instruction::makeHalt() == prog[7]);
  REQUIRE(Instruction::makeFinish() == prog[8]);
}

TEST_CASE("twoStateBetterLayout") {
  NFA fsm(2);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);
  REQUIRE(3u == prog.size());
  REQUIRE(Instruction::makeByte('a') == prog[0]);
  REQUIRE(Instruction::makeHalt() == prog[1]);
  REQUIRE(Instruction::makeFinish() == prog[2]);
}


TEST_CASE("alternationBetterLayout") {
  NFA fsm(3);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(0, 2, fsm, fsm.TransFac->getByte('b'));

  fsm[1].Label = 0;
  fsm[2].Label = 0;

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);

  REQUIRE(8u == prog.size());
  REQUIRE(Instruction::makeFork(&prog[0], 4) == prog[0]);
  REQUIRE(Instruction::makeByte('a') == prog[2]);
  REQUIRE(Instruction::makeLabel(0) == prog[3]);
  REQUIRE(Instruction::makeByte('b') == prog[4]);
  REQUIRE(Instruction::makeLabel(0) == prog[5]);
  REQUIRE(Instruction::makeHalt() == prog[6]);
  REQUIRE(Instruction::makeFinish() == prog[7]);
}

void createTrie(NFA& fsm) {
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 2, fsm, fsm.TransFac->getByte('b'));
  edge(2, 3, fsm, fsm.TransFac->getByte('l'));
  edge(3, 4, fsm, fsm.TransFac->getByte('e'));
  edge(2, 5, fsm, fsm.TransFac->getByte('e'));
  edge(5, 6, fsm, fsm.TransFac->getByte('t'));
  edge(0, 7, fsm, fsm.TransFac->getByte('b'));
  edge(7, 8, fsm, fsm.TransFac->getByte('i'));
  edge(8, 9, fsm, fsm.TransFac->getByte('t'));
  edge(9, 10, fsm, fsm.TransFac->getByte('e'));
}

TEST_CASE("betterLayout") {
  // a
  //  b
  //   le
  //   et
  // b
  //  ite

  NFA fsm(11);
  createTrie(fsm);

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);

  REQUIRE(18u == prog.size());
  REQUIRE(Instruction::makeFork(&prog[0], 8) == prog[0]);
  REQUIRE(Instruction::makeByte('a') == prog[2]);
  REQUIRE(Instruction::makeByte('b') == prog[3]);
  REQUIRE(Instruction::makeFork(&prog[4], 12) == prog[4]);
  REQUIRE(Instruction::makeJump(&prog[6], 14) == prog[6]);
  REQUIRE(Instruction::makeByte('b') == prog[8]);
  REQUIRE(Instruction::makeByte('i') == prog[9]);
  REQUIRE(Instruction::makeByte('t') == prog[10]);
  REQUIRE(Instruction::makeByte('e') == prog[11]);
  REQUIRE(Instruction::makeByte('l') == prog[12]);
  REQUIRE(Instruction::makeByte('e') == prog[13]);
  REQUIRE(Instruction::makeByte('e') == prog[14]);
  REQUIRE(Instruction::makeByte('t') == prog[15]);
  REQUIRE(Instruction::makeHalt() == prog[16]);
  REQUIRE(Instruction::makeFinish() == prog[17]);
}

TEST_CASE("generateCheckHalt") {
  NFA fsm(2);
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 1, fsm, fsm.TransFac->getByte('a'));

  fsm[1].Label = 0;
  fsm[1].IsMatch = true;

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);
  REQUIRE(1u == prog.MaxCheck);

  // std::cout << prog;
  REQUIRE(10u == prog.size());
  REQUIRE(Instruction::makeByte('a') == prog[0]);
  REQUIRE(Instruction::makeLabel(0) == prog[1]);
  REQUIRE(Instruction::makeCheckHalt(1) == prog[2]);
  REQUIRE(Instruction::makeMatch() == prog[3]);
  REQUIRE(Instruction::makeFork(&prog[4], 9) == prog[4]);
  REQUIRE(Instruction::makeJump(&prog[6], 0) == prog[6]);
  REQUIRE(Instruction::makeHalt() == prog[8]);
  REQUIRE(Instruction::makeFinish() == prog[9]);
}

TEST_CASE("testBitVectorGeneration") {
  ByteSet bits;
  bits.reset();
  bits.set('0');
  bits.set('2');
  bits.set('4');
  bits.set('8');
  NFA fsm(2);
  edge(0, 1, fsm, fsm.TransFac->getByteSet(bits));
  fsm[1].Label = 0;
  fsm[1].IsMatch = true;

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);
  REQUIRE(14u == prog.size());
  REQUIRE(Instruction::makeBitVector() == prog[0]);
  REQUIRE(bits == reinterpret_cast<ByteSet&>(prog[1]));
  REQUIRE(Instruction::makeLabel(0) == prog[9]);
  REQUIRE(Instruction::makeMatch() == prog[10]);
  REQUIRE(Instruction::makeFinish() == prog[11]);
  REQUIRE(Instruction::makeHalt() == prog[12]);
  REQUIRE(Instruction::makeFinish() == prog[13]);
}

TEST_CASE("generateJumpTableRange") {
  NFA fsm(7); // a(b|c|d|g)f
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 2, fsm, fsm.TransFac->getByte('b'));
  edge(1, 3, fsm, fsm.TransFac->getByte('c'));
  edge(1, 4, fsm, fsm.TransFac->getByte('d'));
  edge(1, 5, fsm, fsm.TransFac->getByte('g'));
  edge(2, 6, fsm, fsm.TransFac->getByte('f'));
  edge(3, 6, fsm, fsm.TransFac->getByte('f'));
  edge(4, 6, fsm, fsm.TransFac->getByte('f'));
  edge(5, 6, fsm, fsm.TransFac->getByte('f'));

  fsm[1].Label = 0;
  fsm[6].IsMatch = true;

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);

  REQUIRE(25u == prog.size());
  REQUIRE(Instruction::makeByte('a') == prog[0]);
  REQUIRE(Instruction::makeLabel(0) == prog[1]);
  REQUIRE(Instruction::makeJumpTableRange('b', 'g') == prog[2]);
  REQUIRE(10u == *(uint32_t*) &prog[3]); // b
  REQUIRE(10u == *(uint32_t*) &prog[4]); // c
  REQUIRE(10u == *(uint32_t*) &prog[5]); // d
  REQUIRE(0u == *(uint32_t*) &prog[6]); // e
  REQUIRE(0u == *(uint32_t*) &prog[7]); // f
  REQUIRE(10u == *(uint32_t*) &prog[8]); // g
  REQUIRE(Instruction::makeByte('b') == prog[9]);
  REQUIRE(Instruction::makeByte('f') == prog[10]);
  REQUIRE(Instruction::makeCheckHalt(1) == prog[11]);
  REQUIRE(Instruction::makeMatch() == prog[12]);
  REQUIRE(Instruction::makeFinish() == prog[13]);
// From here on, this is garbage---maybe don't even test this?
/*
  REQUIRE(Instruction::makeByte('c') == prog[13]);
  REQUIRE(Instruction::makeJump(&prog[14], 9) == prog[14]);
  REQUIRE(Instruction::makeByte('d') == prog[14]);
  REQUIRE(Instruction::makeJump(&prog[15], 9) == prog[15]);
  REQUIRE(Instruction::makeByte('g') == prog[17]);
  REQUIRE(Instruction::makeJump(&prog[18], 9) == prog[18]);
*/
  REQUIRE(Instruction::makeHalt() == prog[23]);
  REQUIRE(Instruction::makeFinish() == prog[24]);
}

TEST_CASE("generateJumpTableRangePreLabel") {
  NFA fsm(7); // a(b|c|d|g)fg + a(b|c|d|g)fh
  edge(0, 1, fsm, fsm.TransFac->getByte('a'));
  edge(1, 2, fsm, fsm.TransFac->getByte('b'));
  edge(1, 3, fsm, fsm.TransFac->getByte('c'));
  edge(1, 4, fsm, fsm.TransFac->getByte('d'));
  edge(1, 5, fsm, fsm.TransFac->getByte('g'));
  edge(2, 6, fsm, fsm.TransFac->getByte('f'));
  edge(3, 6, fsm, fsm.TransFac->getByte('f'));
  edge(4, 6, fsm, fsm.TransFac->getByte('f'));
  edge(5, 6, fsm, fsm.TransFac->getByte('f'));
  edge(6, 7, fsm, fsm.TransFac->getByte('g'));
  edge(6, 8, fsm, fsm.TransFac->getByte('h'));

  fsm[7].Label = 0;
  fsm[8].Label = 1;
  fsm[7].IsMatch = true;
  fsm[8].IsMatch = true;

  ProgramPtr p = Compiler::createProgram(fsm);
  Program& prog(*p);

  REQUIRE(34u == prog.size());
  REQUIRE(Instruction::makeByte('a') == prog[0]);
  REQUIRE(Instruction::makeJumpTableRange('b', 'g') == prog[1]);
  REQUIRE(9u == *(uint32_t*) &prog[2]); // b
  REQUIRE(9u == *(uint32_t*) &prog[3]); // c
  REQUIRE(9u == *(uint32_t*) &prog[4]); // d
  REQUIRE(0u == *(uint32_t*) &prog[5]); // e
  REQUIRE(0u == *(uint32_t*) &prog[6]); // f
  REQUIRE(9u == *(uint32_t*) &prog[7]); // g
//  REQUIRE(Instruction::makeByte('b') == prog[8]);
  REQUIRE(Instruction::makeByte('f') == prog[9]);
  REQUIRE(Instruction::makeCheckHalt(1) == prog[10]);
  REQUIRE(Instruction::makeFork(&prog[11], 28) == prog[11]);
  REQUIRE(Instruction::makeJump(&prog[13], 24) == prog[13]);
// intervening crap
  REQUIRE(Instruction::makeByte('g') == prog[24]);
  REQUIRE(Instruction::makeLabel(0) == prog[25]);
  REQUIRE(Instruction::makeMatch() == prog[26]);
  REQUIRE(Instruction::makeFinish() == prog[27]);
  REQUIRE(Instruction::makeByte('h') == prog[28]);
  REQUIRE(Instruction::makeLabel(1) == prog[29]);
  REQUIRE(Instruction::makeMatch() == prog[30]);
  REQUIRE(Instruction::makeFinish() == prog[31]);
  REQUIRE(Instruction::makeHalt() == prog[32]);
  REQUIRE(Instruction::makeFinish() == prog[33]);
}

TEST_CASE("testFirstChildNext") {
  NFA g;
  edge(0, 1, g, g.TransFac->getByte('0'));
  edge(1, 2, g, g.TransFac->getByte('0'));
  edge(1, 3, g, g.TransFac->getByte('0'));
  edge(2, 3, g, g.TransFac->getByte('0'));

  g[1].Label = 0;
  g[3].IsMatch = true;

  ProgramPtr p = Compiler::createProgram(g);
  Program& prog(*p);

  REQUIRE(11u == prog.size());
  REQUIRE(Instruction::makeByte('0') == prog[0]);
  REQUIRE(Instruction::makeLabel(0) == prog[1]);
  REQUIRE(Instruction::makeFork(&prog[2], 5) == prog[2]);
  REQUIRE(Instruction::makeByte('0') == prog[4]);
  REQUIRE(Instruction::makeByte('0') == prog[5]);
  REQUIRE(Instruction::makeCheckHalt(1) == prog[6]);
  REQUIRE(Instruction::makeMatch() == prog[7]);
  REQUIRE(Instruction::makeFinish() == prog[8]);
  REQUIRE(Instruction::makeHalt() == prog[9]);
  REQUIRE(Instruction::makeFinish() == prog[10]);
}

TEST_CASE("testFirstChildPrev") {
  NFA g;
  edge(0, 1, g, g.TransFac->getByte('0'));
  edge(1, 2, g, g.TransFac->getRange(0, 255));
  edge(2, 2, g, g.TransFac->getRange(0, 255));
  edge(2, 3, g, g.TransFac->getByte('0'));
  edge(1, 3, g, g.TransFac->getByte('0'));

  g[1].Label = 0;
  g[3].IsMatch = true;

  ProgramPtr p = Compiler::createProgram(g);
  Program& prog(*p);

  REQUIRE(16u == prog.size());
  REQUIRE(Instruction::makeByte('0') == prog[0]);
  REQUIRE(Instruction::makeLabel(0) == prog[1]);
  REQUIRE(Instruction::makeFork(&prog[2], 10) == prog[2]);
  REQUIRE(Instruction::makeAny() == prog[4]);
  REQUIRE(Instruction::makeCheckHalt(1) == prog[5]);
  REQUIRE(Instruction::makeFork(&prog[6], 10) == prog[6]);
  REQUIRE(Instruction::makeJump(&prog[8], 4) == prog[8]);
  REQUIRE(Instruction::makeByte('0') == prog[10]);
  REQUIRE(Instruction::makeCheckHalt(2) == prog[11]);
  REQUIRE(Instruction::makeMatch() == prog[12]);
  REQUIRE(Instruction::makeFinish() == prog[13]);
  REQUIRE(Instruction::makeHalt() == prog[14]);
  REQUIRE(Instruction::makeFinish() == prog[15]);
}
