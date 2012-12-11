/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_AtoZ_Test) {
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
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_ZtoA_Test) {
  const std::string p = "[Z-A]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
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
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_AtoZ_CaseInsensitiveTest) {
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
  SCOPE_ASSERT(parse({p, false, true}, actual));

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

  const std::string p = "\\zFF";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

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

  const std::string p = "\\zFF";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

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

  const std::string p = "[\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

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

  const std::string p = "[\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_00toFF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ByteSet{{0x00, 0x100}})
      )
    )
  );

  const std::string p = "[\\z00-\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_FFto00_BreakoutTest) {
  const std::string p = "[\\zFF-\\z00]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
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

  const std::string p = "[A\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

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

  const std::string p = "[A\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_AtoZ_00toFF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{{'A', 'Z' + 1}}, ByteSet{{0x00, 0x100}})
      )
    )
  );

  const std::string p = "[A-Z\\z00-\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_00toFF_AtoZ_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{{'A', 'Z' + 1}}, ByteSet{{0x00, 0x100}})
      )
    )
  );

  const std::string p = "[\\z00-\\zFFA-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_AtoFF_BreakoutTest) {
  const std::string p = "[A-\\zFF]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseCC_00toA_BreakoutTest) {
  const std::string p = "[\\z00-A]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseNegCC_A_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{'A'})
      )
    )
  );

  const std::string p = "[^A]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_AtoZ_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{{'A', 'Z' + 1}})
      )
    )
  );

  const std::string p = "[^A-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_ZtoA_Test) {
  const std::string p = "[^Z-A]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseNegCC_A_CaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{'A', 'a'})
      )
    )
  );

  const std::string p = "[^A]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_AtoZ_CaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS,
          ~UnicodeSet{
            {'A', 'Z' + 1},
            {'a', 'z' + 1},
            { 0x212A, 0x212B },
            { 0x17F, 0x180 }
          }
        )
      )
    )
  );

  const std::string p = "[^A-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_FF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~ByteSet(0xFF))
      )
    )
  );

  const std::string p = "[^\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_FF_BreakoutCaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~ByteSet(0xFF))
      )
    )
  );

  const std::string p = "[^\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_00toFF_BreakoutTest) {
  const std::string p = "[^\\z00-\\zFF]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseNegCC_00to7F_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~ByteSet{{0x00, 0x80}})
      )
    )
  );

  const std::string p = "[^\\z00-\\z7F]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_FFto00_BreakoutTest) {
  const std::string p = "[^\\zFF-\\z00]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseNegCC_A_FF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{'A'}, ByteSet(0xFF), false)
      )
    )
  );

  const std::string p = "[^A\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_A_FF_BreakoutCaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{'A', 'a'}, ByteSet(0xFF), false)
      )
    )
  );

  const std::string p = "[^A\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, true}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_AtoZ_00toFF_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{{'A', 'Z' + 1}}, ByteSet{{0x00, 0x100}}, false)
      )
    )
  );

  const std::string p = "[^A-Z\\z00-\\zFF]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_AtoZ_00to7F_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{{'A', 'Z' + 1}}, ByteSet{{0x00, 0x80}}, false)
      )
    )
  );

  const std::string p = "[^A-Z\\z00-\\z7F]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_00toFF_AtoZ_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{{'A', 'Z' + 1}}, ByteSet{{0x00, 0x100}}, false)
      )
    )
  );

  const std::string p = "[^\\z00-\\zFFA-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_00to7F_AtoZ_BreakoutTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{{'A', 'Z' + 1}}, ByteSet{{0x00, 0x80}}, false)
      )
    )
  );

  const std::string p = "[^\\z00-\\z7FA-Z]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegCC_AtoFF_BreakoutTest) {
  const std::string p = "[^A-\\zFF]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseNegCC_00toA_BreakoutTest) {
  const std::string p = "[^\\z00-A]";
  ParseTree actual;
  actual.init(p.length());

  try {
    parse({p, false, false}, actual);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}
