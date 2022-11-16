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

#include <catch2/catch_test_macros.hpp>

#include "automata.h"
#include "instructions.h"
#include "nfabuilder.h"
#include "parser.h"
#include "parsetree.h"
#include "states.h"
#include "utility.h"
#include "encoders/concrete_encoders.h"

#include "test_helper.h"

#include <iostream>

void parseOutput(std::string type, ParseNode n) {
  std::cout << type << ": " << n.Val << std::endl;
}

TEST_CASE("parseAorB") {
  NFABuilder nfab;
  NFA& fsm(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"a|b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == fsm.verticesSize());
  REQUIRE(2u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));
  REQUIRE(0u == fsm.outDegree(2));
  REQUIRE(fsm[1].IsMatch);
  REQUIRE(fsm[2].IsMatch);
}

TEST_CASE("parseAorBorC") {
  NFABuilder nfab;
  NFA& fsm(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"a|b|c", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == fsm.verticesSize());
  REQUIRE(3u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));
  REQUIRE(0u == fsm.outDegree(2));
  REQUIRE(0u == fsm.outDegree(3));
  REQUIRE(fsm[1].IsMatch);
  REQUIRE(fsm[2].IsMatch);
  REQUIRE(fsm[3].IsMatch);
}

TEST_CASE("parseAB") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"ab", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(0u == fsm.outDegree(2));
  REQUIRE(!fsm[1].IsMatch);
  REQUIRE(fsm[2].IsMatch);
}

TEST_CASE("parseAlternationAndConcatenation") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"a|bc", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == fsm.verticesSize());
  REQUIRE(2u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));
  REQUIRE(1u == fsm.outDegree(2));
  REQUIRE(0u == fsm.outDegree(3));
  REQUIRE(fsm[1].IsMatch);
  REQUIRE(!fsm[2].IsMatch);
  REQUIRE(fsm[3].IsMatch);
}

TEST_CASE("parseGroup") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"a(b|c)", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(2u == fsm.outDegree(1));
  REQUIRE(0u == fsm.outDegree(2));
  REQUIRE(0u == fsm.outDegree(3));
}

TEST_CASE("parseQuestionMark") {
  NFABuilder nfab;
  ParseTree tree;
  // REQUIRE(bisonParse({"a?", false, false}, tree std::bind(&parseOutput, _1, _2)));
  // tree.Store.clear();
  // REQUIRE(bisonParse({"a?", false, false}, tree std::bind(&Parser::callback, &p, _1, _2)));
  // REQUIRE(!p.good());
  // tree.Store.clear();
  REQUIRE(bisonParse({"ab?", false, false}, tree));
  REQUIRE(nfab.build(tree));

  NFA& fsm(*nfab.getFsm());

  // both s1 and s2 should be match states... it appears that there's an edge duplication???
  // writeGraphviz(std::cerr, fsm);

  REQUIRE(3u == fsm.verticesSize());
  // get really invasive with testing here
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(0u == fsm.outDegree(2));
}

TEST_CASE("parseQuestionMarkFirst") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"a?b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == fsm.verticesSize());
  REQUIRE(2u == fsm.outDegree(0));
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(0u == fsm.outDegree(2));
}

TEST_CASE("parseTwoQuestionMarks") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"ab?c?d", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(5u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(0u == fsm.inDegree(0));
  // a
  REQUIRE(3u == fsm.outDegree(1));
  REQUIRE(1u == fsm.inDegree(1));
  // b?
  REQUIRE(2u == fsm.outDegree(2));
  REQUIRE(1u == fsm.inDegree(2));
  // c?
  REQUIRE(1u == fsm.outDegree(3));
  REQUIRE(2u == fsm.inDegree(3));
  // d
  REQUIRE(0u == fsm.outDegree(4));
  REQUIRE(3u == fsm.inDegree(4));
}

TEST_CASE("parseQuestionWithAlternation") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"(a|b?)c", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == fsm.verticesSize());
  REQUIRE(3u == fsm.outDegree(0));
  REQUIRE(0u == fsm.inDegree(0));
  // a
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(1u == fsm.inDegree(1));
  // b?
  REQUIRE(1u == fsm.outDegree(2));
  REQUIRE(1u == fsm.inDegree(2));
  // c
  REQUIRE(0u == fsm.outDegree(3));
  REQUIRE(3u == fsm.inDegree(3));
}

TEST_CASE("parseQuestionWithGrouping") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"a(bc)?d", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(5u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  // a
  REQUIRE(1u == fsm.inDegree(1));
  REQUIRE(2u == fsm.outDegree(1));
  // b
  REQUIRE(1u == fsm.inDegree(2));
  REQUIRE(1u == fsm.outDegree(2));
  // c
  REQUIRE(1u == fsm.inDegree(3));
  REQUIRE(1u == fsm.outDegree(3));
  // d
  REQUIRE(2u == fsm.inDegree(4));
  REQUIRE(0u == fsm.outDegree(4));
}

TEST_CASE("parsePlus") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"a+", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(0u == fsm.inDegree(0));
  // a+
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(2u == fsm.inDegree(1));
}

TEST_CASE("parseaPQb") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({"a+?b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == g.verticesSize());

  REQUIRE(1u == g.outDegree(0));
  REQUIRE(0u == g.inDegree(0));

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(2u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));
  REQUIRE(1u == g.outVertex(1, 1));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(0u == g.outDegree(2));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(g[2].IsMatch);
}

TEST_CASE("parseStar") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"ab*c", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(2u == fsm.outDegree(1));
  REQUIRE(2u == fsm.outDegree(2));
  REQUIRE(2u == fsm.inDegree(2));
  REQUIRE(0u == fsm.outDegree(3));
  REQUIRE(2u == fsm.inDegree(3));
}

TEST_CASE("parseStarWithGrouping") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"a(bc)*d", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(5u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  // a
  REQUIRE(2u == fsm.outDegree(1));
  // b
  REQUIRE(2u == fsm.inDegree(2));
  REQUIRE(1u == fsm.outDegree(2));
  // c
  REQUIRE(1u == fsm.inDegree(3));
  REQUIRE(2u == fsm.outDegree(3));
  // d
  REQUIRE(2u == fsm.inDegree(4));
  REQUIRE(0u == fsm.outDegree(4));
}

TEST_CASE("parseaQQb") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({"a??b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(2u == g.outDegree(0));
  REQUIRE(2u == g.outVertex(0, 0));
  REQUIRE(1u == g.outVertex(0, 1));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(edgeExists(g, 1, 2));

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(0u == g.outDegree(2));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(g[2].IsMatch);
}

TEST_CASE("parseaQQbQQc") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({"a??b??c", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(3u == g.outDegree(0));
  REQUIRE(3u == g.outVertex(0, 0));
  REQUIRE(2u == g.outVertex(0, 1));
  REQUIRE(1u == g.outVertex(0, 2));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(3u == g.outVertex(1, 0));
  REQUIRE(2u == g.outVertex(1, 1));

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(edgeExists(g, 2, 3));

  REQUIRE(3u == g.inDegree(3));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);
}

TEST_CASE("parseaQQbQc") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({"a??b?c", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(3u == g.outDegree(0));
  REQUIRE(2u == g.outVertex(0, 0));
  REQUIRE(3u == g.outVertex(0, 1));
  REQUIRE(1u == g.outVertex(0, 2));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));
  REQUIRE(3u == g.outVertex(1, 1));

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(edgeExists(g, 2, 3));

  REQUIRE(3u == g.inDegree(3));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);
}

TEST_CASE("parseaQQOrbQQc") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({R"((a??|b??)c)", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(3u == g.outDegree(0));
  REQUIRE(3u == g.outVertex(0, 0));
  REQUIRE(1u == g.outVertex(0, 1));
  REQUIRE(2u == g.outVertex(0, 2));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(edgeExists(g, 1, 3));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(edgeExists(g, 2, 3));

  REQUIRE(3u == g.inDegree(3));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);
}

TEST_CASE("parseaOrbQa") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({"(a|b?)a", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(3u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));
  REQUIRE(2u == g.outVertex(0, 1));
  REQUIRE(3u == g.outVertex(0, 2));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(edgeExists(g, 1, 3));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(edgeExists(g, 2, 3));

  REQUIRE(3u == g.inDegree(3));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);
}

TEST_CASE("parseaOrbQQa") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({R"((a|b??)a)", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(3u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));
  REQUIRE(3u == g.outVertex(0, 1));
  REQUIRE(2u == g.outVertex(0, 2));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(edgeExists(g, 1, 3));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(edgeExists(g, 2, 3));

  REQUIRE(3u == g.inDegree(3));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);
}

TEST_CASE("parseaSQb") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& g(*nfab.getFsm());

  REQUIRE(bisonParse({"a*?b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(2u == g.outDegree(0));
  REQUIRE(2u == g.outVertex(0, 0));
  REQUIRE(1u == g.outVertex(0, 1));

  REQUIRE(2u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));
  REQUIRE(1u == g.outVertex(1, 1));

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(0u == g.outDegree(2));

  REQUIRE(!g[0].Trans);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(g[2].IsMatch);
}

TEST_CASE("parseDot") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({".+", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(2u == fsm.inDegree(1));

  ByteSet expected{{0x00,0x80}}, actual;
  fsm[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseHexCode") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"\\x20", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));

  ByteSet set;
  fsm[1].Trans->getBytes(set);
  REQUIRE(1u == set.count());
  REQUIRE(set[' ']);
}

TEST_CASE("parseHexDotPlus") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"\\x20\\zFF.+\\x20", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(5u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(1u == fsm.outDegree(2));
  REQUIRE(2u == fsm.outDegree(3));
  REQUIRE(2u == fsm.inDegree(3));
  REQUIRE(0u == fsm.outDegree(4));
  REQUIRE(1u == fsm.inDegree(4));
}

TEST_CASE("parse2ByteUnicode") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF16LE));
  REQUIRE(bisonParse({"ab", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(5u == fsm.verticesSize());
}

TEST_CASE("parseHighHex") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"\\zE5", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());

  ByteSet expected, actual;
  expected.set(0xE5);
  fsm[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseSimpleCharClass") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"[AaBb]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));

  ByteSet expected, actual;
  expected.set('A');
  expected.set('a');
  expected.set('B');
  expected.set('b');
  fsm[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
  REQUIRE("ABab/0" == fsm[1].label());
}

TEST_CASE("parseUnprintableCharClass") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"[A\\zFF\\z00]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));

  ByteSet expected, actual;
  expected.set('A');
  expected.set(0x00);
  expected.set(0xFF);
  fsm[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
  REQUIRE("\\x00A\\xFF/0" == fsm[1].label());
}

TEST_CASE("parseNegatedRanges") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"[^a-zA-Z0-9]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(0u == fsm.outDegree(1));

  ByteSet expected, actual;

  expected.set();
  expected.set('0', '9' + 1, false);
  expected.set('A', 'Z' + 1, false);
  expected.set('a', 'z' + 1, false);
  expected.set(0x80, 0x100, false); // out-of-range

  fsm[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseCaseInsensitive") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"ab", false, true}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == fsm.verticesSize());
  REQUIRE(0u == fsm.inDegree(0));
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.inDegree(1));
  REQUIRE(1u == fsm.outDegree(1));
  REQUIRE(1u == fsm.inDegree(2));
  REQUIRE(0u == fsm.outDegree(2));
  Instruction i;
  REQUIRE(fsm[1].Trans->toInstruction(&i));
  REQUIRE(Instruction::makeEither('A', 'a') == i);
  REQUIRE(fsm[2].Trans->toInstruction(&i));
  REQUIRE(Instruction::makeEither('B', 'b') == i);
}

TEST_CASE("parseCaseInsensitiveCC") {
  NFABuilder nfab;
  ParseTree tree;
  NFA& fsm(*nfab.getFsm());
  REQUIRE(bisonParse({"[a-z]", false, true}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == fsm.verticesSize());
  REQUIRE(0u == fsm.inDegree(0));
  REQUIRE(1u == fsm.outDegree(0));
  REQUIRE(1u == fsm.inDegree(1));
  REQUIRE(0u == fsm.outDegree(1));

  REQUIRE(!fsm[0].IsMatch);
  REQUIRE(fsm[1].IsMatch);

  REQUIRE(!fsm[0].Trans);

  ByteSet ebs, abs;

  ebs.set('A', 'Z' + 1, true);
  ebs.set('a', 'z' + 1, true);

  fsm[1].Trans->getBytes(abs);
  REQUIRE(ebs == abs);
}

TEST_CASE("parseSZeroMatchState") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"a?", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("parseRepeatedSkippables") {
  // we'll simulate a?b*
  NFABuilder nfab;
  REQUIRE(1u == nfab.stack().size());
  nfab.callback(ParseNode(ParseNode::LITERAL, 'a'));
  REQUIRE(2u == nfab.stack().size());
  REQUIRE(NOSKIP == nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::REPETITION, nullptr, 0, 1));
  REQUIRE(2u == nfab.stack().size());
  REQUIRE(1u == nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::LITERAL, 'b'));
  REQUIRE(3u == nfab.stack().size());
  REQUIRE(NOSKIP == nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::REPETITION, nullptr, 0, UNBOUNDED));
  REQUIRE(3u == nfab.stack().size());
  REQUIRE(1u == nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::CONCATENATION, nullptr, nullptr));
  REQUIRE(2u == nfab.stack().size());
  REQUIRE(2u == nfab.stack().top().Skippable);
  nfab.callback(ParseNode(ParseNode::CONCATENATION, nullptr, nullptr));
  REQUIRE(1u == nfab.stack().size());
  REQUIRE(NOSKIP == nfab.stack().top().Skippable);
}

TEST_CASE("parseZeroDotStarZero") {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"0.*0", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));
  REQUIRE(3u == g.outVertex(1, 1));

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(2u == g.inVertex(2, 0));
  REQUIRE(1u == g.inVertex(2, 1));
  REQUIRE(2u == g.outDegree(2));
  REQUIRE(2u == g.outVertex(2, 0));
  REQUIRE(3u == g.outVertex(2, 1));

  REQUIRE(2u == g.inDegree(3));
  REQUIRE(1u == g.inVertex(3, 0));
  REQUIRE(2u == g.inVertex(3, 1));
  REQUIRE(0u == g.outDegree(3));
}

#define TEST_REPETITION_N(pattern, n) \
  std::ostringstream ss; \
  ss << pattern << '{' << n << '}'; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  REQUIRE(bisonParse({ss.str(), false, false}, tree)); \
  REQUIRE(nfab.build(tree)); \
\
  REQUIRE(n + 1 == g.verticesSize()); \
\
  REQUIRE(0u == g.inDegree(0)); \
  REQUIRE(1u == g.outDegree(0)); \
  REQUIRE(1u == g.outVertex(0, 0)); \
\
  for (uint32_t i = 1; i < n; ++i) { \
    REQUIRE(1u == g.inDegree(i)); \
    REQUIRE(1u == g.outDegree(i)); \
    REQUIRE(i+1 == g.outVertex(i, 0)); \
    REQUIRE(!g[i].IsMatch); \
  } \
\
  REQUIRE(1u == g.inDegree(n)); \
  REQUIRE(0u == g.outDegree(n)); \
  REQUIRE(g[n].IsMatch);

TEST_CASE("parse_aLCnRC") {
  for (uint32_t c = 1; c < 100; ++c) {
    TEST_REPETITION_N("a", c);
  }
}

#define TEST_REPETITION_N_U(pattern, n) \
  std::ostringstream ss; \
  ss << pattern << '{' << n << ",}"; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  REQUIRE(bisonParse({ss.str(), false, false}, tree)); \
  REQUIRE(nfab.build(tree)); \
\
  REQUIRE(n + 1 == g.verticesSize()); \
\
  REQUIRE(0u == g.inDegree(0)); \
  REQUIRE(1u == g.outDegree(0)); \
  REQUIRE(1u == g.outVertex(0, 0)); \
\
  for (uint32_t i = 1; i < n; ++i) { \
    REQUIRE(1u == g.inDegree(i)); \
    REQUIRE(1u == g.outDegree(i)); \
    REQUIRE(i+1 == g.outVertex(i, 0)); \
    REQUIRE(!g[i].IsMatch); \
  } \
\
  REQUIRE(2u == g.inDegree(n)); \
  REQUIRE(1u == g.outDegree(n)); \
  REQUIRE(n == g.outVertex(n, 0)); \
  REQUIRE(g[n].IsMatch);

TEST_CASE("parse_aLCn_RC") {
  for (uint32_t n = 1; n < 100; ++n) {
    TEST_REPETITION_N_U("a", n);
  }
}

TEST_CASE("parse_aLC0_RCQb") {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"a{0,}?b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(2u == g.outDegree(0));
  REQUIRE(2u == g.outVertex(0, 0));
  REQUIRE(1u == g.outVertex(0, 1));

  REQUIRE(2u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(0));
  REQUIRE(2u == g.outVertex(1, 0));
  REQUIRE(1u == g.outVertex(1, 1));
  REQUIRE(!g[1].IsMatch);

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(0u == g.outDegree(2));
  REQUIRE(g[2].IsMatch);
}

#define TEST_REPETITION_NG_N_U(pattern, n) \
  std::ostringstream ss; \
  ss << pattern << '{' << n << ",}?b"; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  REQUIRE(bisonParse({ss.str(), false, false}, tree)); \
  REQUIRE(nfab.build(tree)); \
\
  REQUIRE(n + 2 == g.verticesSize()); \
\
  REQUIRE(0u == g.inDegree(0)); \
  REQUIRE(1u == g.outDegree(0)); \
  REQUIRE(1 == g.outVertex(0, 0)); \
\
  for (uint32_t i = 1; i < n-1; ++i) { \
    REQUIRE(1u == g.inDegree(i)); \
    REQUIRE(1u == g.outDegree(i)); \
    REQUIRE(i+1 == g.outVertex(i, 0)); \
    REQUIRE(!g[i].IsMatch); \
  } \
\
  REQUIRE(2u == g.inDegree(n)); \
  REQUIRE(2u == g.outDegree(n)); \
  REQUIRE(n+1 == g.outVertex(n, 0)); \
  REQUIRE(n == g.outVertex(n, 1)); \
  REQUIRE(!g[n].IsMatch); \
\
  REQUIRE(1u == g.inDegree(n+1)); \
  REQUIRE(0u == g.outDegree(n+1)); \
  REQUIRE(g[n].IsMatch);

TEST_CASE("parse_aLCn_RCQb") {
  for (uint32_t n = 1; n < 100; ++n) {
    TEST_REPETITION_N_U("a", n);
  }
}

TEST_CASE("parse_xa0_") {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"xa{0,}", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));

  REQUIRE(2u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(2u == g.outVertex(2, 0));

  REQUIRE(g[1].IsMatch);
  REQUIRE(g[2].IsMatch);
}

#define TEST_REPETITION_N_M(pattern, n, m) \
  std::ostringstream ss; \
  ss << pattern << '{' << n << ',' << m << '}'; \
\
  NFABuilder nfab; \
  NFA& g(*nfab.getFsm()); \
  ParseTree tree; \
  REQUIRE(bisonParse({ss.str(), false, false}, tree)); \
  REQUIRE(nfab.build(tree)); \
\
  REQUIRE(m + 1 == g.verticesSize()); \
\
  REQUIRE(0u == g.inDegree(0)); \
  REQUIRE(1u == g.outDegree(0)); \
  REQUIRE(1u == g.outVertex(0, 0)); \
\
  for (uint32_t i = 1; i < n; ++i) { \
    REQUIRE(1u == g.inDegree(i)); \
    REQUIRE(1u == g.outDegree(i)); \
    REQUIRE(i+1 == g.outVertex(i, 0)); \
    REQUIRE(!g[i].IsMatch); \
  } \
\
  for (uint32_t i = n; i < m; ++i) { \
    REQUIRE(1u == g.inDegree(i)); \
    REQUIRE(1u == g.outDegree(i)); \
    REQUIRE(i+1 == g.outVertex(i, 0)); \
    REQUIRE(g[i].IsMatch); \
  } \
\
  REQUIRE(1u == g.inDegree(m)); \
  REQUIRE(0u == g.outDegree(m)); \
  REQUIRE(g[m].IsMatch);

TEST_CASE("parse_aLCn_mRC") {
  for (uint32_t n = 1; n < 5; ++n) {
    for (uint32_t m = n; m < 5; ++m) {
      TEST_REPETITION_N_M("a", n, m);
    }
  }
}

TEST_CASE("parse_aaQQb") {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"aa??b", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(2u == g.outDegree(1));
  REQUIRE(3u == g.outVertex(1, 0));
  REQUIRE(2u == g.outVertex(1, 1));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(3u == g.outVertex(2, 0));

  REQUIRE(2u == g.inDegree(3));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);
}

TEST_CASE("parse_xLPaORaQQRPy") {
  NFABuilder nfab;
  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({R"(x(a|a??)y)", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(5u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(3u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));
  REQUIRE(4u == g.outVertex(1, 1));
  REQUIRE(3u == g.outVertex(1, 2));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(4u == g.outVertex(2, 0));

  REQUIRE(1u == g.inDegree(3));
  REQUIRE(1u == g.outDegree(3));
  REQUIRE(4u == g.outVertex(3, 0));

  REQUIRE(3u == g.inDegree(4));
  REQUIRE(0u == g.outDegree(4));

  REQUIRE(!g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(!g[3].IsMatch);
  REQUIRE(g[4].IsMatch);
}

TEST_CASE("parseEncodingByteBreakout") {
  // 0x80 is not a valid UTF-8 byte by itself, we use \z to break it out

  NFABuilder nfab;
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF8));

  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"\\z80", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(0u == g.outDegree(1));

  REQUIRE(!g[0].IsMatch);
  REQUIRE(g[1].IsMatch);

  REQUIRE(!g[0].Trans);

  ByteSet expected, actual;
  expected.set(0x80);
  g[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseEncodingNotByteBreakout") {
  // 0x80 is a valid UTF-8 code point, referred to by \x{80}

  NFABuilder nfab;
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF8));

  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"\\x{80}", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(3u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(1u == g.outDegree(1));
  REQUIRE(2u == g.outVertex(1, 0));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(1u == g.inVertex(2, 0));
  REQUIRE(0u == g.outDegree(2));

  REQUIRE(!g[0].IsMatch);
  REQUIRE(!g[1].IsMatch);
  REQUIRE(g[2].IsMatch);

  REQUIRE(!g[0].Trans);

  ByteSet expected, actual;
  expected.set(0xC2);
  g[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);

  expected.reset();
  actual.reset();

  expected.set(0x80);
  g[2].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseEncodingCCCodePointWithBreakout") {
  NFABuilder nfab;
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF8));

  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"[A\\zFF]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 0));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(0u == g.outDegree(1));

  REQUIRE(!g[0].IsMatch);
  REQUIRE(g[1].IsMatch);

  REQUIRE(!g[0].Trans);

  ByteSet expected{'A', 0xFF}, actual;
  g[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseEncodingCCCodePoint2ByteWithBreakout") {
  NFABuilder nfab;
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF8));

  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"[\\x{80}\\zFF]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(4u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(2u == g.outDegree(0));
  REQUIRE(2u == g.outVertex(0, 0));
  REQUIRE(3u == g.outVertex(0, 1));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(2u == g.inVertex(1, 0));
  REQUIRE(0u == g.outDegree(1));

  REQUIRE(1u == g.inDegree(2));
  REQUIRE(0u == g.inVertex(2, 0));
  REQUIRE(1u == g.outDegree(2));
  REQUIRE(1u == g.outVertex(2, 0));

  REQUIRE(1u == g.inDegree(3));
  REQUIRE(0u == g.inVertex(3, 0));
  REQUIRE(0u == g.outDegree(3));

  REQUIRE(!g[0].IsMatch);
  REQUIRE(g[1].IsMatch);
  REQUIRE(!g[2].IsMatch);
  REQUIRE(g[3].IsMatch);

  REQUIRE(!g[0].Trans);

  ByteSet expected{0x80}, actual;
  g[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);

  expected.reset();
  actual.reset();

  expected.set(0xC2);
  g[2].Trans->getBytes(actual);
  REQUIRE(expected == actual);

  expected.reset();
  actual.reset();

  expected.set(0xFF);
  g[3].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseEncodingCCBreakoutOnly") {
  NFABuilder nfab;
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF8));

  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"[\\zFF]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 1));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(0u == g.outDegree(1));

  REQUIRE(!g[0].IsMatch);
  REQUIRE(g[1].IsMatch);

  REQUIRE(!g[0].Trans);

  ByteSet expected{0xFF}, actual;
  g[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}

TEST_CASE("parseEncodingNegCCCodePointWithBreakout") {
  NFABuilder nfab;
  nfab.setEncoder(std::shared_ptr<Encoder>(new UTF8));

  NFA& g(*nfab.getFsm());
  ParseTree tree;
  REQUIRE(bisonParse({"[^\\x{02}-\\x{10FFFF}\\x01]", false, false}, tree));
  REQUIRE(nfab.build(tree));

  REQUIRE(2u == g.verticesSize());

  REQUIRE(0u == g.inDegree(0));
  REQUIRE(1u == g.outDegree(0));
  REQUIRE(1u == g.outVertex(0, 1));

  REQUIRE(1u == g.inDegree(1));
  REQUIRE(0u == g.inVertex(1, 0));
  REQUIRE(0u == g.outDegree(1));

  REQUIRE(!g[0].IsMatch);
  REQUIRE(g[1].IsMatch);

  REQUIRE(!g[0].Trans);

  ByteSet expected{0x00}, actual;
  g[1].Trans->getBytes(actual);
  REQUIRE(expected == actual);
}
