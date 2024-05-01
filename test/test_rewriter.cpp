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

#include "parser.h"
#include "parsetree.h"
#include "rewriter.h"
#include "unparser.h"

TEST_CASE("hasZeroLengthMatch_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"a", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a?", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aP_Test") {
  ParseTree tree;
  REQUIRE(parse({"a+", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aQQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a??", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*?", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aPQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a+?", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a0_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0}", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a1_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1}", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a0_1_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0,1}", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a0__Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0,}", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_a1__Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1,}", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_ab_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSb_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*b", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_abS_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab*", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSbS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*b*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aOrb_Test") {
  ParseTree tree;
  REQUIRE(parse({"a|b", false, false}, tree));
  REQUIRE(!hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSOrb_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*|b", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aOrbS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a|b*", false, false}, tree));
  REQUIRE(hasZeroLengthMatch(tree.Root));
}

TEST_CASE("hasZeroLengthMatch_aSOrbS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*|b*", false, false}, tree));
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

  REQUIRE(parse({"a", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a" == unparse(tree));

  REQUIRE(parse({"a?", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a?" == unparse(tree));

  REQUIRE(parse({"a*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*" == unparse(tree));

  REQUIRE(parse({"a+", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a+" == unparse(tree));

  REQUIRE(parse({"a{0}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(parse({"a{1}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"a{0,1}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a?" == unparse(tree));

  REQUIRE(parse({"a{0,}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*" == unparse(tree));

  REQUIRE(parse({"a{1,}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a+" == unparse(tree));

  REQUIRE(parse({"a{1,1}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"a{1,2}", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1,2}" == unparse(tree));

  REQUIRE(parse({"a??", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(parse({"a*?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(parse({"a+?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"a{0}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(parse({"a{1}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"a{0,1}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(parse({"a{0,}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{0}" == unparse(tree));

  REQUIRE(parse({"a{1,}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"a{1,1}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"a{1,2}?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}" == unparse(tree));

  REQUIRE(parse({"ab", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("ab" == unparse(tree));

  REQUIRE(parse({"a*b", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*b" == unparse(tree));

  REQUIRE(parse({"ab*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("ab*" == unparse(tree));

  REQUIRE(parse({"a*b*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*b*" == unparse(tree));

  REQUIRE(parse({"a|b", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a|b" == unparse(tree));

  REQUIRE(parse({"a*|b", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*|b" == unparse(tree));

  REQUIRE(parse({"a|b*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a|b*" == unparse(tree));

  REQUIRE(parse({"a*|b*", false, false}, tree));
  REQUIRE(!reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a*|b*" == unparse(tree));

  REQUIRE(parse({"a+?b?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b?" == unparse(tree));

  REQUIRE(parse({"a+?b*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b*" == unparse(tree));

  REQUIRE(parse({"(a|b)+?b*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("(a|b){1}b*" == unparse(tree));

  REQUIRE(parse({"a+?(b|c*)", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}(b|c*)" == unparse(tree));

  REQUIRE(parse({"a+?b{0,5}", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b{0,5}" == unparse(tree));

  REQUIRE(parse({"a{1,5}?b{0,1}", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}b?" == unparse(tree));

  REQUIRE(parse({"aa.+?a*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("aa.{1}a*" == unparse(tree));

  REQUIRE(parse({"a.*?a*", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a.{0}a*" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenEmpty_aPQdotQQaSQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a+?.??a*?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("a{1}.{0}a{0}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenEmpty_PLaPQRPPQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"(a+?)+?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("(a{1}){1}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenEmpty_aaaSQOraOraaSQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"aaa*?|a|aa*?", false, false}, tree));
  REQUIRE(reduceTrailingNongreedyThenEmpty(tree.Root));
  REQUIRE("aaa{0}|a|aa{0}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"a", false, false}, tree));
  REQUIRE(!reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_1_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1,1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_2_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1,2}", false, false}, tree));
  REQUIRE(!reduceUselessRepetitions(tree.Root));
  REQUIRE("a{1,2}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1Q_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1}?", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a2Q_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{2}?", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a{2}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1_2Q_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1,2}?", false, false}, tree));
  REQUIRE(!reduceUselessRepetitions(tree.Root));
  REQUIRE("a{1,2}?" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a1Orb1_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{1}|b{1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a|b" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a11_Test") {
  ParseTree tree;
  REQUIRE(parse({"(a{1}){1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a111_Test") {
  ParseTree tree;
  REQUIRE(parse({"((a{1}){1}){1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a12_Test") {
  ParseTree tree;
  REQUIRE(parse({"(a{1}){2}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a{2}" == unparse(tree));
}

TEST_CASE("reduceUselessRepetitions_a121_Test") {
  ParseTree tree;
  REQUIRE(parse({"((a{1}){2}){1}", false, false}, tree));
  REQUIRE(reduceUselessRepetitions(tree.Root));
  REQUIRE("a{2}" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"a", false, false}, tree));
  REQUIRE(!reduceEmptySubtrees(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a0_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a0b0_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0}b{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_a0b_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0}b", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("b" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_ba0_Test") {
  ParseTree tree;
  REQUIRE(parse({"ba{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("b" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_aLPa0OraRP_Test") {
  ParseTree tree;
  REQUIRE(parse({"a(a{0}|a)", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_aLPaOra0RP_Test") {
  ParseTree tree;
  REQUIRE(parse({"a(a|a{0})", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("aa?" == unparse(tree));
}

TEST_CASE("reduceEmptySubtrees_aaa0OraOraa0_Test") {
  ParseTree tree;
  REQUIRE(parse({"aaa{0}|a|aa{0}", false, false}, tree));
  REQUIRE(reduceEmptySubtrees(tree.Root));
  REQUIRE("aa|a|a" == unparse(tree));
}

TEST_CASE("combineConsecutiveRepetitions_LPabRPPLPabRPP_Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab)+(ab)+", false, false}, tree));
  REQUIRE(combineConsecutiveRepetitions(tree.Root));
  REQUIRE("(ab){2,}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenGreedy_LPabRPQQab_Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab)??ab", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE(reduceTrailingNongreedyThenGreedy(tree.Root));
  REQUIRE("(ab){1}" == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenGreedy_aDotaaaQQaDot_Test") {
  ParseTree tree;
  REQUIRE(parse({"a.aaa??a.", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE(!reduceTrailingNongreedyThenGreedy(tree.Root));
  REQUIRE("a.aaa??a." == unparse(tree));
}

TEST_CASE("reduceTrailingNongreedyThenGreedy_aSQaOraSQa_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*?a|a*?a", false, false}, tree));
  REQUIRE(!makeBinopsRightAssociative(tree.Root));
  REQUIRE(reduceTrailingNongreedyThenGreedy(tree.Root));
  REQUIRE("a{1}|a{1}" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_LPabRPc_Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab)c", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE("abc" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_aLPbcRP_Test") {
  ParseTree tree;
  REQUIRE(parse({"a(bc)", false, false}, tree));
  REQUIRE(!makeBinopsRightAssociative(tree.Root));
  REQUIRE("abc" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_LPaOrbRPOrc_Test") {
  ParseTree tree;
  REQUIRE(parse({"(a|b)|c", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
  REQUIRE("a|b|c" == unparse(tree));
}

TEST_CASE("makeBinopsRightAssociative_aOrLPbOrcRP_Test") {
  ParseTree tree;
  REQUIRE(parse({"a|(b|c)", false, false}, tree));
  REQUIRE(!makeBinopsRightAssociative(tree.Root));
  REQUIRE("a|b|c" == unparse(tree));
}

/*
TEST_CASE("makeBinopsRightAssociative_use_after_free") {
  ParseTree tree;
  REQUIRE(parse({"\\W^^^^^\\W", false, false}, tree));
  REQUIRE(makeBinopsRightAssociative(tree.Root));
}
*/
