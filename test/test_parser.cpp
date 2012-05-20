#include <scope/test.h>

#include "parser.h"
#include "parsetree.h"

SCOPE_TEST(parseCC_A_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'A'})
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
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{{'A', 'Z' + 1}})
      )
    )
  );

  const std::string p = "[A-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, false, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_A_CaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'A', 'a'})
      )
    )
  );

  const std::string p = "[A]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, true, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parse_CC_AtoZ_CaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS,
          UnicodeSet{
            {'A', 'Z' + 1},
            {'a', 'z' + 1},
            { 0x212A, 0x212B },
            { 0x17F, 0x180 }
          }
        )
      )
    )
  );

  const std::string p = "[A-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, true, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parse_FF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::BYTE, 0xFF)
      )
    )
  );

  const std::string p = "\\xFF";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, false, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parse_FF_BreakoutCaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::BYTE, 0xFF)
      )
    )
  );

  const std::string p = "\\xFF";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, true, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_FF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ByteSet(0xFF))
      )
    )
  );

  const std::string p = "[\\xFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, false, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_FF_BreakoutCaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ByteSet(0xFF))
      )
    )
  );

  const std::string p = "[\\xFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, true, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_A_FF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'A'}, ByteSet(0xFF))
      )
    )
  );

  const std::string p = "[A\\xFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, false, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_A_FF_BreakoutCaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'A', 'a'}, ByteSet(0xFF))
      )
    )
  );

  const std::string p = "[A\\xFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse(p, false, true, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}
