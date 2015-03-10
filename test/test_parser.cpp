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

SCOPE_TEST(parseCC_Whack_b_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{0x08})
      )
    )
  );

  const std::string p = "[\\b]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCC_Whack_b_CaseInsensitiveTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{0x08})
      )
    )
  );

  const std::string p = "[\\b]";
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

SCOPE_TEST(parseFailNamedCodePointMissingNameTest) {
  ParseTree tree;
  try {
    parse({"\\N", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\N, at [0,2)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNamedCodePointMissingLeftBraceTest) {
  ParseTree tree;
  try {
    parse({"\\NCYRILLIC SMALL LETTER DOUBLE MONOCULAR O", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\NC, at [0,3)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNamedCodePointMissingRightBraceTest) {
  ParseTree tree;
  try {
    parse({"\\N{CYRILLIC SMALL LETTER DOUBLE MONOCULAR O", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\N{CYRILLIC SMALL LETTER DOUBLE MONOCULAR O, at [0,43)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailHexCodeMissingValueTest) {
  ParseTree tree;
  try {
    parse({"\\x", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\x, at [0,2)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailHexCodeBadValueTest) {
  ParseTree tree;
  try {
    parse({"\\xG", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\xG, at [0,3)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailBadEscapeTest) {
  ParseTree tree;
  try {
    parse({"\\#", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\#, at [0,2)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailPropertyMissingValueTest) {
  ParseTree tree;
  try {
    parse({"\\p", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\p, at [0,2)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegatedPropertyMissingValueTest) {
  ParseTree tree;
  try {
    parse({"\\P", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\P, at [0,2)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailPropertyMissingLeftBrace) {
  ParseTree tree;
  try {
    parse({"\\pLetter", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\p, at [0,2)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailPropertyMissingRightBrace) {
  ParseTree tree;
  try {
    parse({"\\p{Letter", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "invalid escape \\p{Letter, at [0,9)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailReversedBoundedRepetitionTest) {
  ParseTree tree;
  try {
    parse({"a{2,1}", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "2 > 1 in {2,1}, at [1,6)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailReversedNongreedyBoundedRepetitionTest) {
  ParseTree tree;
  try {
    parse({"a{2,1}?", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "2 > 1 in {2,1}?, at [1,7)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseAAmp_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', '&'})
      )
    )
  );

  const std::string p = "[a&]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseATilde_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', '~'})
      )
    )
  );

  const std::string p = "[a~]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseAHyphen_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', '-'})
      )
    )
  );

  const std::string p = "[a-]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseAmpA_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', '&'})
      )
    )
  );

  const std::string p = "[&a]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseTildeA_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', '~'})
      )
    )
  );

  const std::string p = "[~a]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseHyphenA_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', '-'})
      )
    )
  );

  const std::string p = "[-a]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseAAmpB_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', 'b', '&'})
      )
    )
  );

  const std::string p = "[a&b]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseATildeB_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', 'b', '~'})
      )
    )
  );

  const std::string p = "[a~b]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseFailHyphenToA_Test) {
  ParseTree tree;
  try {
    parse({"[--a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for --, at [1,3)",
      std::string(e.what())
    );
    return;
  }
}

SCOPE_TEST(parseFailAToHyphen_Test) {
  ParseTree tree;
  try {
    parse({"[a--]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for --, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegHyphenToA_Test) {
  ParseTree tree;
  try {
    parse({"[^--a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for --, at [2,4)",
      std::string(e.what())
    );
    return;
  }
}

SCOPE_TEST(parseFailNegAToHyphen_Test) {
  ParseTree tree;
  try {
    parse({"[^a--]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for --, at [3,5)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailAAmpAmp_Test) {
  ParseTree tree;
  try {
    parse({"[a&&]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for &&, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailAmpAmpA_Test) {
  ParseTree tree;
  try {
    parse({"[&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for &&, at [1,3)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegAAmpAmp_Test) {
  ParseTree tree;
  try {
    parse({"[^a&&]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for &&, at [3,5)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegAmpAmpA_Test) {
  ParseTree tree;
  try {
    parse({"[^&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for &&, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailATildeTilde_Test) {
  ParseTree tree;
  try {
    parse({"[a~~]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for ~~, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailTildeTildeA_Test) {
  ParseTree tree;
  try {
    parse({"[~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for ~~, at [1,3)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegATildeTilde_Test) {
  ParseTree tree;
  try {
    parse({"[^a~~]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for ~~, at [3,5)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegTildeTildeA_Test) {
  ParseTree tree;
  try {
    parse({"[^~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for ~~, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailAHyphenHyphenHyphenHyphenA_Test) {
  ParseTree tree;
  try {
    parse({"[a----a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for --, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailAAmpAmpAmpAmpA_Test) {
  ParseTree tree;
  try {
    parse({"[a&&&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for &&, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailATildeTildeTildeTildeA_Test) {
  ParseTree tree;
  try {
    parse({"[a~~~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for ~~, at [2,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegAHyphenHyphenHyphenHyphenA_Test) {
  ParseTree tree;
  try {
    parse({"[^a----a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for --, at [3,5)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegAAmpAmpAmpAmpA_Test) {
  ParseTree tree;
  try {
    parse({"[^a&&&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for &&, at [3,5)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailNegATildeTildeTildeTildeA_Test) {
  ParseTree tree;
  try {
    parse({"[^a~~~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "missing operand for ~~, at [3,5)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseAtoCHyphenE_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a', 'b', 'c', 'e', '-'})
      )
    )
  );

  const std::string p = "[a-c-e]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseAHyphenHyphenHyphen_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'a'})
      )
    )
  );

  const std::string p = "[a---]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseDigitHyphenA_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', 'A'})
      )
    )
  );

  const std::string p = "[\\d-A]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegDigitHyphenA_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', 'A'})
      )
    )
  );

  const std::string p = "[^\\d-A]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseAHyphenDigit_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', 'A'})
      )
    )
  );

  const std::string p = "[A-\\d]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegAHyphenDigit_Test) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', 'A'})
      )
    )
  );

  const std::string p = "[^A-\\d]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseDigitHyphenByte_Test) {
  ParseTree expected;
  expected.init(2);

  ParseNode* cc = expected.add(
    ParseNode::CHAR_CLASS,
    UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'}
  );
  cc->Set.Breakout.Bytes.set(0);
  cc->Set.Breakout.Additive = true;

  expected.Root = expected.add(ParseNode(ParseNode::REGEXP, cc));

  const std::string p = "[\\d-\\z00]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegDigitHyphenByte_Test) {
  ParseTree expected;
  expected.init(2);

  ParseNode* cc = expected.add(
    ParseNode::CHAR_CLASS,
    ~UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'}
  );
  cc->Set.Breakout.Bytes.set(0);
  cc->Set.Breakout.Additive = false;

  expected.Root = expected.add(ParseNode(ParseNode::REGEXP, cc));

  const std::string p = "[^\\d-\\z00]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseByteHyphenDigit_Test) {
  ParseTree expected;
  expected.init(2);

  ParseNode* cc = expected.add(
    ParseNode::CHAR_CLASS,
    UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'}
  );
  cc->Set.Breakout.Bytes.set(0);

  expected.Root = expected.add(ParseNode(ParseNode::REGEXP, cc));

  const std::string p = "[\\z00-\\d]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegByteHyphenDigit_Test) {
  ParseTree expected;
  expected.init(2);

  ParseNode* cc = expected.add(
    ParseNode::CHAR_CLASS,
    ~UnicodeSet{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'}
  );
  cc->Set.Breakout.Bytes.set(0);
  cc->Set.Breakout.Additive = false;

  expected.Root = expected.add(ParseNode(ParseNode::REGEXP, cc));

  const std::string p = "[^\\z00-\\d]";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseHyphenHyphenTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CONCATENATION,
          expected.add(
            ParseNode(ParseNode::LITERAL, '-')
          ),
          expected.add(
            ParseNode(ParseNode::LITERAL, '-')
          )
        )
      )
    )
  );

  const std::string p = "--";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseAmpAmpTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CONCATENATION,
          expected.add(
            ParseNode(ParseNode::LITERAL, '&')
          ),
          expected.add(
            ParseNode(ParseNode::LITERAL, '&')
          )
        )
      )
    )
  );

  const std::string p = "&&";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseTildeTildeTest) {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CONCATENATION,
          expected.add(
            ParseNode(ParseNode::LITERAL, '~')
          ),
          expected.add(
            ParseNode(ParseNode::LITERAL, '~')
          )
        )
      )
    )
  );

  const std::string p = "~~";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseFailUnmatchedLeftBracketCharacterClassTest) {
  ParseTree tree;
  try {
    parse({"[]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "unmatched left bracket [, at [0,1)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailEmptyCharClassTest) {
  ParseTree tree;
  try {
    parse({"[a&&b]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "empty character class [a&&b], at [0,6)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailEmptyNegCodePointCharClassTest) {
  ParseTree tree;
  try {
    parse({"[^\\x{0}-\\x{10FFFF}]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "empty character class [^\\x{0}-\\x{10FFFF}], at [0,19)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailEmptyNegByteCharClassTest) {
  ParseTree tree;
  try {
    parse({"[^\\z00-\\zFF]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "empty character class [^\\z00-\\zFF], at [0,12)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailBadCharRangeBoundsCharClassTest) {
  ParseTree tree;
  try {
    parse({"[z-a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "U+7A >= U+61 in z-a, at [1,4)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseFailBadByteRangeBoundsCharClassTest) {
  ParseTree tree;
  try {
    parse({"[\\zFF-\\z00]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    SCOPE_ASSERT_EQUAL(
      "0xFF >= 0x00 in \\zFF-\\z00, at [1,10)",
      std::string(e.what())
    );
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseAKillBOrCTest) {
  ParseTree expected;
  expected.init(7);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::ALTERNATION,
          expected.add(
            ParseNode(ParseNode::CONCATENATION,
              expected.add(
                ParseNode(ParseNode::LOOKBEHIND_POS,
                  expected.add(ParseNode::LITERAL, 'A')
                )
              ),
              expected.add(ParseNode::LITERAL, 'B')
            )
          ),
          expected.add(ParseNode::LITERAL, 'C')
        )
      )
    )
  );

  const std::string p = "A\\KB|C";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parsePositiveLookbehindATest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKBEHIND_POS,
          expected.add(
            ParseNode(ParseNode::LITERAL, 'A')
          )
        )
      )
    )
  );

  const std::string p = "(?<=A)";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegativeLookbehindATest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKBEHIND_NEG,
          expected.add(
            ParseNode(ParseNode::LITERAL, 'A')
          )
        )
      )
    )
  );

  const std::string p = "(?<!A)";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parsePositiveLookaheadATest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKAHEAD_POS,
          expected.add(
            ParseNode(ParseNode::LITERAL, 'A')
          )
        )
      )
    )
  );

  const std::string p = "(?=A)";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNegativeLookaheadATest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKAHEAD_NEG,
          expected.add(
            ParseNode(ParseNode::LITERAL, 'A')
          )
        )
      )
    )
  );

  const std::string p = "(?!A)";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseWhackATest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKBEHIND_NEG,
          expected.add(
            ParseNode(ParseNode::DOT, '.')
          )
        )
      )
    )
  );

  const std::string p = "\\A";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseWhackZTest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKAHEAD_NEG,
          expected.add(
            ParseNode(ParseNode::DOT, '.')
          )
        )
      )
    )
  );

  const std::string p = "\\Z";
  ParseTree actual;
  actual.init(p.length());
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseCaretTest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKBEHIND_NEG,
          expected.add(
            ParseNode::CHAR_CLASS,
            UnicodeSet{'\n', '\v', '\f', '\r', 0x85, 0x2028, 0x2029}
          )
        )
      )
    )
  );

  const std::string p = "^";
  ParseTree actual;
  actual.init(3);
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseDollarSignTest) {
  ParseTree expected;
  expected.init(3);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::LOOKAHEAD_NEG,
          expected.add(
            ParseNode::CHAR_CLASS,
            UnicodeSet{'\n', '\v', '\f', '\r', 0x85, 0x2028, 0x2029}
          )
        )
      )
    )
  );

  const std::string p = "$";
  ParseTree actual;
  actual.init(3);
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseWordBoundaryTest) {
  // \b  = ((?<!\w)(?!\W)|(?<!\W)(?!\w))

  ParseTree expected;
  expected.init(10);

  UnicodeSet wset;
  wset.insert('0', '9' + 1);
  wset.insert('A', 'Z' + 1);
  wset.set('_');
  wset.insert('a', 'z' + 1);

  ParseNode* w = expected.add(ParseNode(ParseNode::CHAR_CLASS, wset));
  ParseNode* W = expected.add(ParseNode(ParseNode::CHAR_CLASS, ~wset));

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::ALTERNATION,
          expected.add(
            ParseNode(ParseNode::CONCATENATION,
              expected.add(
                ParseNode(ParseNode::LOOKBEHIND_NEG, w)
              ),
              expected.add(
                ParseNode(ParseNode::LOOKAHEAD_NEG, W)
              )
            )
          ),
          expected.add(
            ParseNode(ParseNode::CONCATENATION,
              expected.add(
                ParseNode(ParseNode::LOOKBEHIND_NEG, W)
              ),
              expected.add(
                ParseNode(ParseNode::LOOKAHEAD_NEG, w)
              )
            )
          )
        )
      )
    )
  );

  const std::string p = "\\b";
  ParseTree actual;
  actual.init(10);
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}

SCOPE_TEST(parseNonWordBoundaryTest) {
  // \B  = ((?<!\w)(?!\w)|(?<!\W)(?!\W))

  ParseTree expected;
  expected.init(10);

  UnicodeSet wset;
  wset.insert('0', '9' + 1);
  wset.insert('A', 'Z' + 1);
  wset.set('_');
  wset.insert('a', 'z' + 1);

  ParseNode* w = expected.add(ParseNode(ParseNode::CHAR_CLASS, wset));
  ParseNode* W = expected.add(ParseNode(ParseNode::CHAR_CLASS, ~wset));

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::ALTERNATION,
          expected.add(
            ParseNode(ParseNode::CONCATENATION,
              expected.add(
                ParseNode(ParseNode::LOOKBEHIND_NEG, w)
              ),
              expected.add(
                ParseNode(ParseNode::LOOKAHEAD_NEG, w)
              )
            )
          ),
          expected.add(
            ParseNode(ParseNode::CONCATENATION,
              expected.add(
                ParseNode(ParseNode::LOOKBEHIND_NEG, W)
              ),
              expected.add(
                ParseNode(ParseNode::LOOKAHEAD_NEG, W)
              )
            )
          )
        )
      )
    )
  );

  const std::string p = "\\B";
  ParseTree actual;
  actual.init(10);
  SCOPE_ASSERT(parse({p, false, false}, actual));

  SCOPE_ASSERT_EQUAL(expected, actual);
}
