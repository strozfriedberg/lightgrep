#include <scope/test.h>

#include "parser.h"
#include "parsetree.h"

SCOPE_TEST(parseCC_A_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP, 
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet('A'))
      )
    )
  );

  const std::string p = "[A]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, false, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parse_CC_AtoZ_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP, 
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet('A', 'Z' + 1))
      )
    )
  );

  const std::string p = "[A-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, false, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}
