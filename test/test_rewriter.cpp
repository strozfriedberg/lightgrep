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

#include "parser.h"
#include "parsetree.h"
#include "rewriter.h"
#include "unparser.h"

TEST_CASE("hasZeroLengthMatch_a_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a?", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aS_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aP_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a+", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aQQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a??", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*?", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aPQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a+?", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a0_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{0}", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a1_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1}", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a0_1_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{0,1}", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a0__Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{0,}", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a1__Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1,}", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_ab_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"ab", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSb_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*b", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_abS_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"ab*", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSbS_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*b*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aOrb_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a|b", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSOrb_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*|b", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aOrbS_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a|b*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSOrbS_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*|b*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("spliceOutParentLeftTest") {
  ParseTree tree;
  tree.init(4);

  ParseNode *l = tree.add(ParseNode(ParseNode::LITERAL, 'l'));
  ParseNode *r = tree.add(ParseNode(ParseNode::LITERAL, 'r'));
  ParseNode *con = tree.add(ParseNode(ParseNode::CONCATENATION, l, r));
  tree.Root = tree.add(ParseNode(ParseNode::REGEXP, con));

  spliceOutParent(tree.Root, con, l);

  REQUIRE(l == tree.Root->Child.Left);
  REQUIRE((ParseNode*) nullptr == tree.Root->Child.Right);
}

TEST_CASE("spliceOutParentRightTest") {
  ParseTree tree;
  tree.init(4);

  ParseNode *l = tree.add(ParseNode(ParseNode::LITERAL, 'l'));
  ParseNode *r = tree.add(ParseNode(ParseNode::LITERAL, 'r'));
  ParseNode *con = tree.add(ParseNode(ParseNode::CONCATENATION, l, r));
  tree.Root = tree.add(ParseNode(ParseNode::REGEXP, con));

  spliceOutParent(tree.Root, con, r);

  REQUIRE(r == tree.Root->Child.Left);
  REQUIRE((ParseNode*) nullptr == tree.Root->Child.Right);
}

// FIXME: Split this into multiple tests.
TEST_CASE("reduceTrailingNongreedyThenEmptyTest") {
  ParseTree tree;

  REQUIRE(bisonParse({"a", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a" == unparse(tree));

  REQUIRE(bisonParse({"a?", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a?" == unparse(tree));

  REQUIRE(bisonParse({"a*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*" == unparse(tree));

  REQUIRE(bisonParse({"a+", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a+" == unparse(tree));

  REQUIRE(bisonParse({"a{0}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(bisonParse({"a{1}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"a{0,1}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a?" == unparse(tree));

  REQUIRE(bisonParse({"a{0,}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*" == unparse(tree));

  REQUIRE(bisonParse({"a{1,}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a+" == unparse(tree));

  REQUIRE(bisonParse({"a{1,1}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"a{1,2}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1,2}" == unparse(tree));

  REQUIRE(bisonParse({"a??", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(bisonParse({"a*?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(bisonParse({"a+?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"a{0}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(bisonParse({"a{1}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"a{0,1}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(bisonParse({"a{0,}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(bisonParse({"a{1,}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"a{1,1}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"a{1,2}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(bisonParse({"ab", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("ab" == unparse(tree));

  REQUIRE(bisonParse({"a*b", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*b" == unparse(tree));

  REQUIRE(bisonParse({"ab*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("ab*" == unparse(tree));

  REQUIRE(bisonParse({"a*b*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*b*" == unparse(tree));

  REQUIRE(bisonParse({"a|b", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a|b" == unparse(tree));

  REQUIRE(bisonParse({"a*|b", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*|b" == unparse(tree));

  REQUIRE(bisonParse({"a|b*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a|b*" == unparse(tree));

  REQUIRE(bisonParse({"a*|b*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*|b*" == unparse(tree));

  REQUIRE(bisonParse({"a+?b?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b?" == unparse(tree));

  REQUIRE(bisonParse({"a+?b*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b*" == unparse(tree));

  REQUIRE(bisonParse({"(a|b)+?b*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("(a|b){1}b*" == unparse(tree));

  REQUIRE(bisonParse({"a+?(b|c*)", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}(b|c*)" == unparse(tree));

  REQUIRE(bisonParse({"a+?b{0,5}", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b{0,5}" == unparse(tree));

  REQUIRE(bisonParse({"a{1,5}?b{0,1}", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b?" == unparse(tree));

  REQUIRE(bisonParse({"aa.+?a*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("aa.{1}a*" == unparse(tree));

  REQUIRE(bisonParse({"a.*?a*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a.{0}a*" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenEmpty_aPQdotQQaSQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a+?.??a*?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}.{0}a{0}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenEmpty_PLaPQRPPQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(a+?)+?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("(a{1}){1}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenEmpty_aaaSQOraOraaSQ_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"aaa*?|a|aa*?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("aaa{0}|a|aa{0}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a", false, false}, tree));
  REQUIRE(!reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_1_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1,1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_2_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1,2}", false, false}, tree));
  REQUIRE(!reduceUselessRepetitions(tree.Root));
  REQUIRE("a{1,2}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1Q_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1}?", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a2Q_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{2}?", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a{2}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_2Q_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1,2}?", false, false}, tree));
  REQUIRE(!reduceUselessRepetitions(tree.Root));
  REQUIRE("a{1,2}?" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1Orb1_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{1}|b{1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a|b" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a11_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(a{1}){1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a111_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"((a{1}){1}){1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a12_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(a{1}){2}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a{2}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a121_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"((a{1}){2}){1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a{2}" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a", false, false}, tree));
  REQUIRE(!reduceEmptySubtrees(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a0_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a0b0_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{0}b{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a0b_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a{0}b", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("b" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_ba0_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"ba{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("b" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_aLPa0OraRP_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a(a{0}|a)", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_aLPaOra0RP_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a(a|a{0})", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("aa?" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_aaa0OraOraa0_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"aaa{0}|a|aa{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("aa|a|a" == unparse(tree));
}

TEST_CASE("combineConsecutiveRepetitions_LPabRPPLPabRPP_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(ab)+(ab)+", false, false}, tree));
  REQUIRE(combineConsecutiveRepetitions(tree.Root));
  REQUIRE("(ab){2,}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenGreedy_LPabRPQQab_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(ab)??ab", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE(reduceTrailingNongreedyThenGreedy(tree.Root));
  REQUIRE("(ab){1}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenGreedy_aDotaaaQQaDot_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a.aaa??a.", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE(!reduceTrailingNongreedyThenGreedy(tree.Root));
  REQUIRE("a.aaa??a." == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenGreedy_aSQaOraSQa_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a*?a|a*?a", false, false}, tree));
  REQUIRE(!makeBinopsRightAssociative(tree.Root));
  REQUIRE(reduceTrailingNongreedyThenGreedy(tree.Root));
  REQUIRE("a{1}|a{1}" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_LPabRPc_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(ab)c", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE("abc" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_aLPbcRP_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a(bc)", false, false}, tree));
  REQUIRE(!makeBinopsRightAssociative(tree.Root));
  REQUIRE("abc" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_LPaOrbRPOrc_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"(a|b)|c", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE("a|b|c" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_aOrLPbOrcRP_Test") {
  ParseTree tree;
  REQUIRE(bisonParse({"a|(b|c)", false, false}, tree));
  REQUIRE(!makeBinopsRightAssociative(tree.Root));
  REQUIRE("a|b|c" == unparse(tree));
}
