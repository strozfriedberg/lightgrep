#include <scope/test.h>

#include "parser.h"
#include "parsetree.h"
#include "unparser.h"

SCOPE_TEST(parseUnparseTest) {
  ParseTree tree;

  SCOPE_ASSERT(parse("a", false, tree));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("a?", false, tree));
  SCOPE_ASSERT_EQUAL("a?", unparse(tree));

  SCOPE_ASSERT(parse("a*", false, tree));
  SCOPE_ASSERT_EQUAL("a*", unparse(tree));

  SCOPE_ASSERT(parse("a+", false, tree));
  SCOPE_ASSERT_EQUAL("a+", unparse(tree));

  SCOPE_ASSERT(parse("a??", false, tree));
  SCOPE_ASSERT_EQUAL("a??", unparse(tree));

  SCOPE_ASSERT(parse("a*?", false, tree));
  SCOPE_ASSERT_EQUAL("a*?", unparse(tree));

  SCOPE_ASSERT(parse("a+?", false, tree));
  SCOPE_ASSERT_EQUAL("a+?", unparse(tree));

  SCOPE_ASSERT(parse("ab", false, tree));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));

  SCOPE_ASSERT(parse("a*b", false, tree));
  SCOPE_ASSERT_EQUAL("a*b", unparse(tree));

  SCOPE_ASSERT(parse("ab*", false, tree));
  SCOPE_ASSERT_EQUAL("ab*", unparse(tree));

  SCOPE_ASSERT(parse("a*b*", false, tree));
  SCOPE_ASSERT_EQUAL("a*b*", unparse(tree));

  SCOPE_ASSERT(parse("a|b", false, tree));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));

  SCOPE_ASSERT(parse("a*|b", false, tree));
  SCOPE_ASSERT_EQUAL("a*|b", unparse(tree));

  SCOPE_ASSERT(parse("a|b*", false, tree));
  SCOPE_ASSERT_EQUAL("a|b*", unparse(tree));
  
  SCOPE_ASSERT(parse("a*|b*", false, tree));
  SCOPE_ASSERT_EQUAL("a*|b*", unparse(tree));

  SCOPE_ASSERT(parse("(a)", false, tree));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));

  SCOPE_ASSERT(parse("(ab)*", false, tree));
  SCOPE_ASSERT_EQUAL("(ab)*", unparse(tree));

  SCOPE_ASSERT(parse("(a|b)c", false, tree));
  SCOPE_ASSERT_EQUAL("(a|b)c", unparse(tree));

  SCOPE_ASSERT(parse("a|b|c", false, tree));
  SCOPE_ASSERT_EQUAL("a|b|c", unparse(tree));
}
