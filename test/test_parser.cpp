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
#include "unicode_sets.h"

TEST_CASE("parseCC_A_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_AtoZ_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_ZtoA_Test") {
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
  REQUIRE(false);
}

TEST_CASE("parseCC_A_CaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_AtoZ_CaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_AtoZ_CaseInsensitiveAsciiTest") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS,
          UnicodeSet{
            {'A', 'Z' + 1},
            {'a', 'z' + 1}
          }
        )
      )
    )
  );

  const std::string p = "[A-Z]";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_Whack_b_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_Whack_b_CaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_FF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_FF_BreakoutCaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_FF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_FF_BreakoutCaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_00toFF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_FFto00_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseCC_A_FF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_A_FF_BreakoutCaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_AtoZ_00toFF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_00toFF_AtoZ_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCC_AtoFF_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseCC_00toA_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseNegCC_A_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_AtoZ_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_ZtoA_Test") {
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
  REQUIRE(false);
}

TEST_CASE("parseNegCC_A_CaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_AtoZ_CaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_AtoZ_CaseInsensitiveAsciiTest") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS,
          ~UnicodeSet{
            {'A', 'Z' + 1},
            {'a', 'z' + 1},
          }
        )
      )
    )
  );

  const std::string p = "[^A-Z]";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_FF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_FF_BreakoutCaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_00toFF_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseNegCC_00to7F_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_FFto00_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseNegCC_A_FF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_A_FF_BreakoutCaseInsensitiveTest") {
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
  REQUIRE(parse({p, false, true}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_AtoZ_00toFF_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_AtoZ_00to7F_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_00toFF_AtoZ_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_00to7F_AtoZ_BreakoutTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegCC_AtoFF_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseNegCC_00toA_BreakoutTest") {
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
  REQUIRE(false);
}

TEST_CASE("parseFailNamedCodePointMissingNameTest") {
  ParseTree tree;
  try {
    parse({"\\N", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\N, at [0,2)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNamedCodePointMissingLeftBraceTest") {
  ParseTree tree;
  try {
    parse({"\\NCYRILLIC SMALL LETTER DOUBLE MONOCULAR O", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\NC, at [0,3)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNamedCodePointMissingRightBraceTest") {
  ParseTree tree;
  try {
    parse({"\\N{CYRILLIC SMALL LETTER DOUBLE MONOCULAR O", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\N{CYRILLIC SMALL LETTER DOUBLE MONOCULAR O, at [0,43)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailHexCodeMissingValueTest") {
  ParseTree tree;
  try {
    parse({"\\x", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\x, at [0,2)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailHexCodeBadValueTest") {
  ParseTree tree;
  try {
    parse({"\\xG", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\xG, at [0,3)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailBadEscapeTest") {
  ParseTree tree;
  try {
    parse({"\\#", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\#, at [0,2)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailPropertyMissingValueTest") {
  ParseTree tree;
  try {
    parse({"\\p", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\p, at [0,2)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegatedPropertyMissingValueTest") {
  ParseTree tree;
  try {
    parse({"\\P", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\P, at [0,2)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailPropertyMissingLeftBrace") {
  ParseTree tree;
  try {
    parse({"\\pLetter", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\p, at [0,2)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailPropertyMissingRightBrace") {
  ParseTree tree;
  try {
    parse({"\\p{Letter", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "invalid escape \\p{Letter, at [0,9)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailReversedBoundedRepetitionTest") {
  ParseTree tree;
  try {
    parse({"a{2,1}", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "2 > 1 in {2,1}, at [1,6)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailReversedNongreedyBoundedRepetitionTest") {
  ParseTree tree;
  try {
    parse({"a{2,1}?", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "2 > 1 in {2,1}?, at [1,7)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseAAmp_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseATilde_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseAHyphen_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseAmpA_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseTildeA_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseHyphenA_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseAAmpB_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseATildeB_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseFailHyphenToA_Test") {
  ParseTree tree;
  try {
    parse({"[--a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for --, at [1,3)" ==
      std::string(e.what())
    );
    return;
  }
}

TEST_CASE("parseFailAToHyphen_Test") {
  ParseTree tree;
  try {
    parse({"[a--]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for --, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegHyphenToA_Test") {
  ParseTree tree;
  try {
    parse({"[^--a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for --, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
}

TEST_CASE("parseFailNegAToHyphen_Test") {
  ParseTree tree;
  try {
    parse({"[^a--]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for --, at [3,5)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailAAmpAmp_Test") {
  ParseTree tree;
  try {
    parse({"[a&&]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for &&, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailAmpAmpA_Test") {
  ParseTree tree;
  try {
    parse({"[&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for &&, at [1,3)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegAAmpAmp_Test") {
  ParseTree tree;
  try {
    parse({"[^a&&]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for &&, at [3,5)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegAmpAmpA_Test") {
  ParseTree tree;
  try {
    parse({"[^&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for &&, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailATildeTilde_Test") {
  ParseTree tree;
  try {
    parse({"[a~~]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for ~~, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailTildeTildeA_Test") {
  ParseTree tree;
  try {
    parse({"[~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for ~~, at [1,3)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegATildeTilde_Test") {
  ParseTree tree;
  try {
    parse({"[^a~~]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for ~~, at [3,5)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegTildeTildeA_Test") {
  ParseTree tree;
  try {
    parse({"[^~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for ~~, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailAHyphenHyphenHyphenHyphenA_Test") {
  ParseTree tree;
  try {
    parse({"[a----a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for --, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailAAmpAmpAmpAmpA_Test") {
  ParseTree tree;
  try {
    parse({"[a&&&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for &&, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailATildeTildeTildeTildeA_Test") {
  ParseTree tree;
  try {
    parse({"[a~~~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for ~~, at [2,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegAHyphenHyphenHyphenHyphenA_Test") {
  ParseTree tree;
  try {
    parse({"[^a----a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for --, at [3,5)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegAAmpAmpAmpAmpA_Test") {
  ParseTree tree;
  try {
    parse({"[^a&&&&a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for &&, at [3,5)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailNegATildeTildeTildeTildeA_Test") {
  ParseTree tree;
  try {
    parse({"[^a~~~~a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "missing operand for ~~, at [3,5)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseAtoCHyphenE_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseAHyphenHyphenHyphen_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseDigitHyphenA_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegDigitHyphenA_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseAHyphenDigit_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegAHyphenDigit_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseDigitHyphenByte_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegDigitHyphenByte_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseByteHyphenDigit_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegByteHyphenDigit_Test") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseHyphenHyphenTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseAmpAmpTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseTildeTildeTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseFailUnmatchedLeftBracketCharacterClassTest") {
  ParseTree tree;
  try {
    parse({"[]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "unmatched left bracket [, at [0,1)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailEmptyCharClassTest") {
  ParseTree tree;
  try {
    parse({"[a&&b]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "empty character class [a&&b], at [0,6)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailEmptyNegCodePointCharClassTest") {
  ParseTree tree;
  try {
    parse({"[^\\x{0}-\\x{10FFFF}]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "empty character class [^\\x{0}-\\x{10FFFF}], at [0,19)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailEmptyNegByteCharClassTest") {
  ParseTree tree;
  try {
    parse({"[^\\z00-\\zFF]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "empty character class [^\\z00-\\zFF], at [0,12)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailBadCharRangeBoundsCharClassTest") {
  ParseTree tree;
  try {
    parse({"[z-a]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "U+7A >= U+61 in z-a, at [1,4)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseFailBadByteRangeBoundsCharClassTest") {
  ParseTree tree;
  try {
    parse({"[\\zFF-\\z00]", false, false}, tree);
  }
  catch (const std::runtime_error& e) {
    REQUIRE(
      "0xFF >= 0x00 in \\zFF-\\z00, at [1,10)" ==
      std::string(e.what())
    );
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseAKillBOrCTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parsePositiveLookbehindATest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegativeLookbehindATest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parsePositiveLookaheadATest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNegativeLookaheadATest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseWhackATest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseWhackZTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseCaretTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseDollarSignTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseWordBoundaryTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parseNonWordBoundaryTest") {
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
  REQUIRE(parse({p, false, false}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_ks_01_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'k', 's'})
      )
    )
  );

  const std::string p = "[ks]";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_ks_02_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'k', 's'})
      )
    )
  );

  const std::string p = "[ks]";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_ks_03_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'K', 'S', 'k', 's', 0x17F, 0x212A})
      )
    )
  );

  const std::string p = "[ks]";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_ks_04_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{'K', 'S', 'k', 's'})
      )
    )
  );

  const std::string p = "[ks]";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_on_digit_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, UnicodeSet{{'0', '9' + 1}})
      )
    )
  );

  const std::string p = "\\d";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_off_digit_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, DIGIT)
      )
    )
  );

  const std::string p = "\\d";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_on_not_digit_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~UnicodeSet{{'0', '9' + 1}})
      )
    )
  );

  const std::string p = "\\D";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_off_not_digit_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~DIGIT)
      )
    )
  );

  const std::string p = "\\D";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_hspace_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, HSPACE)
      )
    )
  );

  const std::string p = "\\h";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_not_hspace_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~HSPACE)
      )
    )
  );

  const std::string p = "\\H";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_vspace_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, VSPACE)
      )
    )
  );

  const std::string p = "\\v";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_not_vspace_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~VSPACE)
      )
    )
  );

  const std::string p = "\\V";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_on_space_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(
          ParseNode::CHAR_CLASS,
          UnicodeSet{{'\t', '\r' + 1}, {' ', ' ' + 1}}
        )
      )
    )
  );

  const std::string p = "\\s";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_off_space_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, HSPACE | VSPACE)
      )
    )
  );

  const std::string p = "\\s";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_on_not_space_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(
          ParseNode::CHAR_CLASS,
          ~UnicodeSet{{'\t', '\r' + 1}, {' ', ' ' + 1}}
        )
      )
    )
  );

  const std::string p = "\\S";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_off_not_space_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~(HSPACE | VSPACE))
      )
    )
  );

  const std::string p = "\\S";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_word_01_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(
          ParseNode::CHAR_CLASS,
          UnicodeSet{
            {'0', '9' + 1},
            {'A', 'Z' + 1},
            {'_', '_' + 1},
            {'a', 'z' + 1}
          }
        )
      )
    )
  );

  const std::string p = "\\w";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_word_02_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(
          ParseNode::CHAR_CLASS,
          UnicodeSet{
            {'0', '9' + 1},
            {'A', 'Z' + 1},
            {'_', '_' + 1},
            {'a', 'z' + 1}
          }
        )
      )
    )
  );

  const std::string p = "\\w";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_word_03_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, WORD)
      )
    )
  );

  const std::string p = "\\w";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_word_04_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, WORD)
      )
    )
  );

  const std::string p = "\\w";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_not_word_01_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(
          ParseNode::CHAR_CLASS,
          ~UnicodeSet{
            {'0', '9' + 1},
            {'A', 'Z' + 1},
            {'_', '_' + 1},
            {'a', 'z' + 1}
          }
        )
      )
    )
  );

  const std::string p = "\\W";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_not_word_02_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(
          ParseNode::CHAR_CLASS,
          ~UnicodeSet{
            {'0', '9' + 1},
            {'A', 'Z' + 1},
            {'_', '_' + 1},
            {'a', 'z' + 1}
          }
        )
      )
    )
  );

  const std::string p = "\\W";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, false, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_not_word_03_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~WORD)
      )
    )
  );

  const std::string p = "\\W";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, false, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}

TEST_CASE("parse_ascii_mode_not_word_04_Test") {
  ParseTree expected;
  expected.init(2);

  expected.Root = expected.add(
    ParseNode(ParseNode::REGEXP,
      expected.add(
        ParseNode(ParseNode::CHAR_CLASS, ~WORD)
      )
    )
  );

  const std::string p = "\\W";
  ParseTree actual;
  actual.init(p.length());
  REQUIRE(parse({p, false, true, true, "UTF-8"}, actual));

  REQUIRE(expected == actual);
}
