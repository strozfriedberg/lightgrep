#include <scope/test.h>

#include "parser.h"
#include "parsetree.h"
#include "rewriter.h"
#include "unparser.h"

SCOPE_TEST(hasZeroLengthMatch_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a?", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a+", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aQQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a??", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aSQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aPQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_a0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0}", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_a1_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1}", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_a0_1_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,1}", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_a0__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,}", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_a1__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,}", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_ab_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aSb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_abS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("ab*", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aSbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b*", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aOrb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b", false, tree));
  SCOPE_ASSERT(!has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aSOrb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aOrbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b*", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(hasZeroLengthMatch_aSOrbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b*", false, tree));
  SCOPE_ASSERT(has_zero_length_match(tree.Root));
}

SCOPE_TEST(spliceOutParentLeftTest) {
  ParseTree tree;
  tree.init(4);

  Node *l = tree.add(Node(Node::LITERAL, 'l'));
  Node *r = tree.add(Node(Node::LITERAL, 'r'));
  Node *con = tree.add(Node(Node::CONCATENATION, l, r));
  tree.Root = tree.add(Node(Node::REGEXP, con));

  splice_out_parent(tree.Root, con, l);

  SCOPE_ASSERT_EQUAL(l, tree.Root->Left);
  SCOPE_ASSERT_EQUAL((Node*) 0, tree.Root->Right);
}

SCOPE_TEST(spliceOutParentRightTest) {
  ParseTree tree;
  tree.init(4);

  Node *l = tree.add(Node(Node::LITERAL, 'l'));
  Node *r = tree.add(Node(Node::LITERAL, 'r'));
  Node *con = tree.add(Node(Node::CONCATENATION, l, r));
  tree.Root = tree.add(Node(Node::REGEXP, con));

  splice_out_parent(tree.Root, con, r);

  SCOPE_ASSERT_EQUAL(r, tree.Root->Left);
  SCOPE_ASSERT_EQUAL((Node*) 0, tree.Root->Right);
}

// FIXME: Split this into multiple tests.
SCOPE_TEST(reduceTrailingNongreedyThenEmptyTest) {
  ParseTree tree;

  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("a?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a?", unparse(tree));

  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*", unparse(tree));

  SCOPE_ASSERT(parse("a+", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a+", unparse(tree));

  SCOPE_ASSERT(parse("a{0}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a{1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a?", unparse(tree));

  SCOPE_ASSERT(parse("a{0,}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*", unparse(tree));

  SCOPE_ASSERT(parse("a{1,}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a+", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}", unparse(tree));

  SCOPE_ASSERT(parse("a??", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a+?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a{1}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,1}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));

  SCOPE_ASSERT(parse("a*b", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*b", unparse(tree));

  SCOPE_ASSERT(parse("ab*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("ab*", unparse(tree));

  SCOPE_ASSERT(parse("a*b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*b*", unparse(tree));

  SCOPE_ASSERT(parse("a|b", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));

  SCOPE_ASSERT(parse("a*|b", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*|b", unparse(tree));

  SCOPE_ASSERT(parse("a|b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a|b*", unparse(tree));

  SCOPE_ASSERT(parse("a*|b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*|b*", unparse(tree));

  SCOPE_ASSERT(parse("a+?b?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}b?", unparse(tree));

  SCOPE_ASSERT(parse("a+?b*", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}b*", unparse(tree));

  SCOPE_ASSERT(parse("(a|b)+?b*", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("(a|b){1}b*", unparse(tree));

  SCOPE_ASSERT(parse("a+?(b|c*)", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}(b|c*)", unparse(tree));

  SCOPE_ASSERT(parse("a+?b{0,5}", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}b{0,5}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,5}?b{0,1}", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}b?", unparse(tree));

  SCOPE_ASSERT(parse("aa.+?a*", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("aa.{1}a*", unparse(tree));

  SCOPE_ASSERT(parse("a.*?a*", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a.{0}a*", unparse(tree));
}

SCOPE_TEST(reduceTrailingNongreedyThenEmpty_aPQdotQQaSQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?.??a*?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}.{0}a{0}", unparse(tree));
}

SCOPE_TEST(reduceTrailingNongreedyThenEmpty_PLaPQRPPQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(a+?)+?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("(a{1}){1}", unparse(tree));
}

SCOPE_TEST(reduceTrailingNongreedyThenEmpty_aaaSQOraOraaSQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("aaa*?|a|aa*?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("aaa{0}|a|aa{0}", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT(!reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a1_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1}", false, tree));
  SCOPE_ASSERT(reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a1_1_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,1}", false, tree));
  SCOPE_ASSERT(reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a1_2_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}", false, tree));
  SCOPE_ASSERT(!reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a1Q_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1}?", false, tree));
  SCOPE_ASSERT(reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a2Q_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{2}?", false, tree));
  SCOPE_ASSERT(reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a{2}", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a1_2Q_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1,2}?", false, tree));
  SCOPE_ASSERT(!reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}?", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_a1Orb1_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{1}|b{1}", false, tree));
  SCOPE_ASSERT(reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));
}

SCOPE_TEST(reduceUselessRepetitions_PLaPQRPPQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(a{1}){1}", false, tree));
  SCOPE_ASSERT(reduce_useless_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT(!reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_a0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0}", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_a0b0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0}b{0}", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_a0b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0}b", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("b", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_ba0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("ba{0}", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("b", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_aLPa0OraRP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a(a{0}|a)", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_aLPaOra0RP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a(a|a{0})", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("aa?", unparse(tree));
}

SCOPE_TEST(reduceEmptySubtrees_aaa0OraOraa0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("aaa{0}|a|aa{0}", false, tree));
  SCOPE_ASSERT(reduce_empty_subtrees(tree.Root));
  SCOPE_ASSERT_EQUAL("aa|a|a", unparse(tree));
}

