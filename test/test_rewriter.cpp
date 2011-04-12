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

SCOPE_TEST(pruneSubtreeRootTest) {
  ParseTree tree;
  tree.init(1);

  tree.Root = tree.add(Node(Node::REGEXP, 0, 0, 0));

  std::stack<Node*> branch;
  prune_subtree(tree.Root, branch);

  SCOPE_ASSERT_EQUAL(1, branch.size());
  SCOPE_ASSERT_EQUAL(tree.Root, branch.top());
  SCOPE_ASSERT_EQUAL((Node*) 0, tree.Root->Left);
}

SCOPE_TEST(pruneSubtreeRootParentTest) {
  ParseTree tree;
  tree.init(2);

  Node* n = tree.add(Node(Node::LITERAL, 0, 0, 'a'));
  tree.Root = tree.add(Node(Node::REGEXP, n, 0, 0));

  std::stack<Node*> branch;
  branch.push(tree.Root);
  prune_subtree(n, branch);

  SCOPE_ASSERT_EQUAL(1, branch.size());
  SCOPE_ASSERT_EQUAL(tree.Root, branch.top());
  SCOPE_ASSERT_EQUAL((Node*) 0, tree.Root->Left);
}

SCOPE_TEST(pruneSubtreeUnaryParentTest) {
  ParseTree tree;
  tree.init(3);

  Node* na = tree.add(Node(Node::LITERAL, 0, 0, 'a'));
  Node* np = tree.add(Node(Node::PLUS, na, 0, 0));
  tree.Root = tree.add(Node(Node::REGEXP, np, 0, 0));

  std::stack<Node*> branch;
  branch.push(tree.Root);
  branch.push(np);
  prune_subtree(na, branch);

  SCOPE_ASSERT_EQUAL(1, branch.size());
  SCOPE_ASSERT_EQUAL(tree.Root, branch.top());
  SCOPE_ASSERT_EQUAL((Node*) 0, tree.Root->Left);
}

SCOPE_TEST(pruneSubtreeLeftBinaryParentTest) {
  ParseTree tree;
  tree.init(4);

  Node* na = tree.add(Node(Node::LITERAL, 0, 0, 'a'));
  Node* nb = tree.add(Node(Node::LITERAL, 0, 0, 'b'));
  Node* alt = tree.add(Node(Node::ALTERNATION, na, nb, 0));
  tree.Root = tree.add(Node(Node::REGEXP, alt, 0, 0));

  std::stack<Node*> branch;
  branch.push(tree.Root);
  branch.push(alt);
  prune_subtree(na, branch);

  SCOPE_ASSERT_EQUAL(1, branch.size());
  SCOPE_ASSERT_EQUAL(tree.Root, branch.top());
  SCOPE_ASSERT_EQUAL(nb, tree.Root->Left);
}

SCOPE_TEST(pruneSubtreeRightBinaryParentTest) {
  ParseTree tree;
  tree.init(4);

  Node* na = tree.add(Node(Node::LITERAL, 0, 0, 'a'));
  Node* nb = tree.add(Node(Node::LITERAL, 0, 0, 'b'));
  Node* alt = tree.add(Node(Node::ALTERNATION, na, nb, 0));
  tree.Root = tree.add(Node(Node::REGEXP, alt, 0, 0));

  std::stack<Node*> branch;
  branch.push(tree.Root);
  branch.push(alt);
  prune_subtree(nb, branch);

  SCOPE_ASSERT_EQUAL(1, branch.size());
  SCOPE_ASSERT_EQUAL(tree.Root, branch.top());
  SCOPE_ASSERT_EQUAL(na, tree.Root->Left);
}

SCOPE_TEST(reduceTrailingNongreedyTest) {
  ParseTree tree;

  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("a?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a?", unparse(tree));

  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a*", unparse(tree));

  SCOPE_ASSERT(parse("a+", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a+", unparse(tree));

  SCOPE_ASSERT(parse("a{0}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}", unparse(tree));

  SCOPE_ASSERT(parse("a{1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0,1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0,}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}", unparse(tree));

  SCOPE_ASSERT(parse("a??", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a+?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("a{0}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a{1}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,1}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a{0,}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a{1,}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));

  SCOPE_ASSERT(parse("a*b", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a*b", unparse(tree));

  SCOPE_ASSERT(parse("ab*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("ab*", unparse(tree));

  SCOPE_ASSERT(parse("a*b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a*b*", unparse(tree));

  SCOPE_ASSERT(parse("a|b", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));

  SCOPE_ASSERT(parse("a*|b", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a*|b", unparse(tree));

  SCOPE_ASSERT(parse("a|b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a|b*", unparse(tree));

  SCOPE_ASSERT(parse("a*|b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a*|b*", unparse(tree));

  SCOPE_ASSERT(parse("a+?b?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a+?b?", unparse(tree));

  SCOPE_ASSERT(parse("a+?b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a+?b*", unparse(tree));

  SCOPE_ASSERT(parse("(a|b)+?b*", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("(a|b)+?b*", unparse(tree));

  SCOPE_ASSERT(parse("a+?(b|c*)", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a+?(b|c*)", unparse(tree));

  SCOPE_ASSERT(parse("ab+?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));

  SCOPE_ASSERT(parse("ab*?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("ab??", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("ab??b??", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("ab*?b??", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("ab+?b??", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));

  SCOPE_ASSERT(parse("a(b+?|c)", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a(b|c)", unparse(tree));

  SCOPE_ASSERT(parse("a(b??|c)", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("ac", unparse(tree));

  SCOPE_ASSERT(parse("a(b|c??)", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));

  SCOPE_ASSERT(parse("a(b??|c*?)", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("a+|b+?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a+|b", unparse(tree));

  SCOPE_ASSERT(parse("a+?|b+?", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy(tree.Root));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));
}

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
  SCOPE_ASSERT_EQUAL("a{0,1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0,}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0,}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}", unparse(tree));

  SCOPE_ASSERT(parse("a??", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a??", unparse(tree));

  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a*?", unparse(tree));

  SCOPE_ASSERT(parse("a+?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a+?", unparse(tree));

  SCOPE_ASSERT(parse("a{0}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0}?", unparse(tree));

  SCOPE_ASSERT(parse("a{1}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}?", unparse(tree));

  SCOPE_ASSERT(parse("a{0,1}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0,1}?", unparse(tree));

  SCOPE_ASSERT(parse("a{0,}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{0,}?", unparse(tree));

  SCOPE_ASSERT(parse("a{1,}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,}?", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}?", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}?", false, tree));
  SCOPE_ASSERT(!reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}?", unparse(tree));

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
  SCOPE_ASSERT_EQUAL("ab?", unparse(tree));

  SCOPE_ASSERT(parse("a+?b*", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("ab*", unparse(tree));

  SCOPE_ASSERT(parse("(a|b)+?b*", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("(a|b)b*", unparse(tree));

  SCOPE_ASSERT(parse("a+?(b|c*)", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("a(b|c*)", unparse(tree));

  SCOPE_ASSERT(parse("a+?b{0,5}", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("ab{0,5}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,5}?b{0,1}", false, tree));
  SCOPE_ASSERT(reduce_trailing_nongreedy_then_empty(tree.Root));
  SCOPE_ASSERT_EQUAL("ab{0,1}", unparse(tree));
}

SCOPE_TEST(reduceEmptyRepetitionsTest) {
  ParseTree tree;

  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT(!reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("a{0}", false, tree));
  SCOPE_ASSERT(reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a{1}", false, tree));
  SCOPE_ASSERT(!reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{0}b", false, tree));
  SCOPE_ASSERT(reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("b", unparse(tree));

  SCOPE_ASSERT(parse("a{0,0}", false, tree));
  SCOPE_ASSERT(reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("", unparse(tree));

  SCOPE_ASSERT(parse("a{1,1}", false, tree));
  SCOPE_ASSERT(!reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1}", unparse(tree));

  SCOPE_ASSERT(parse("a{1,2}", false, tree));
  SCOPE_ASSERT(!reduce_empty_repetitions(tree.Root));
  SCOPE_ASSERT_EQUAL("a{1,2}", unparse(tree));
}
