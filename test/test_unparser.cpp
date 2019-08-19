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

#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "parser.h"
#include "parsetree.h"
#include "unparser.h"

SCOPE_TEST(unparseEmptyTest) {
  ParseTree tree;
  ParseNode root(ParseNode::REGEXP, 0, 0, 0);
  tree.Root = &root;

  SCOPE_ASSERT_EQUAL("", unparse(tree));
}

SCOPE_TEST(parseUnparse_comma_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({",", false, false}, tree));
  SCOPE_ASSERT_EQUAL(",", unparse(tree));
}

SCOPE_TEST(parseUnparse_hyphen_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"-", false, false}, tree));
  SCOPE_ASSERT_EQUAL("-", unparse(tree));
}

SCOPE_TEST(parseUnparse_LC_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"{", false, false}, tree));
  SCOPE_ASSERT_EQUAL("{", unparse(tree));
}

SCOPE_TEST(parseUnparse_RC_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(parseUnparse_aQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a?", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a?", unparse(tree));
}

SCOPE_TEST(parseUnparse_aS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a*", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a+", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a+", unparse(tree));
}

SCOPE_TEST(parseUnparse_aQQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a??", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a??", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a*?", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a*?", unparse(tree));
}

SCOPE_TEST(parseUnparse_aPQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a+?", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a+?", unparse(tree));
}

SCOPE_TEST(parseUnparse_ab_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"ab", false, false}, tree));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a*b", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a*b", unparse(tree));
}

SCOPE_TEST(parseUnparse_abS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"ab*", false, false}, tree));
  SCOPE_ASSERT_EQUAL("ab*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a*b*", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a*b*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aOrb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a|b", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSOrb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a*|b", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a*|b", unparse(tree));
}

SCOPE_TEST(parseUnparse_aOrbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a|b*", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a|b*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSOrbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a*|b*", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a*|b*", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPaRP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(a)", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRPS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(ab)*", false, false}, tree));
  SCOPE_ASSERT_EQUAL("(ab)*", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPaOrbRPc_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(a|b)c", false, false}, tree));
  SCOPE_ASSERT_EQUAL("(a|b)c", unparse(tree));
}

SCOPE_TEST(parseUnparse_aOrbOrc_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a|b|c", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a|b|c", unparse(tree));
}

SCOPE_TEST(parseUnparse_abOrcd_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"ab|cd", false, false}, tree));
  SCOPE_ASSERT_EQUAL("ab|cd", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBaRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBabcRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[abc]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[abc]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBabcdRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[abcd]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a-d]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBdcbaRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[dcba]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a-d]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a3_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a{3}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a{3}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a42_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a{42}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a{42}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a0_7_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a{0,7}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a{0,7}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a4_3_Test) {
  ParseTree tree;
  try {
    parse({"a{4,3}", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a4_3Q_Test) {
  ParseTree tree;
  try {
    parse({"a{4,3}?", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a42__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"a{42,}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("a{42,}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRP3_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(ab){3}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("(ab){3}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRP5_7_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(ab){5,7}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("(ab){5,7}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRP42__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(ab){42,}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("(ab){42,}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPa1RP1__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"(a{1}){1}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("(a{1}){1}", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCaCaret_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a^]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a^]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCd_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\d", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[0-9]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCD_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\D", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^0-9]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCs_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\s", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[\\t\\n\\f\\r ]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\S", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^\\t\\n\\f\\r ]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCw_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\w", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[0-9A-Z_a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCW_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\W", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^0-9A-Z_a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBaTozAToZCCdDot_PctBSHyphenPlusRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a-zA-Z\\d._%\\-+]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[%+.0-9A-Z_a-z-]", unparse(tree));
}

SCOPE_TEST(parseUnparse_BSx_Test) {
  ParseTree tree;
  try {
    parse({"\\x", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_BSx0_Test) {
  ParseTree tree;
  try {
    parse({"\\x0", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_BSx00_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\x00", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\0", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS00_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\00", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS000_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\000", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS0000_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\0000", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\x000", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS08_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\08", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\x008", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS377_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"\\377", false, false}, tree));
  SCOPE_ASSERT_EQUAL("\\xFF", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS400_Test) {
  ParseTree tree;
  try {
    parse({"\\400", false, false}, tree);
    SCOPE_ASSERT(false);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_BSq_Test) {
  ParseTree tree;
  try {
    parse({"\\q", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_xBSq_Test) {
  ParseTree tree;
  try {
    parse({"x\\q", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_invalid_utf8_Test) {
  ParseTree tree;
  try {
    parse({"\xFF", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_CCempty_Test) {
  ParseTree tree;
  try {
    parse({"[]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_CC_left_bracket_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[\\[]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[[]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CC_right_bracket_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[]]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CC_right_bracket_left_bracket_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[]\\[]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[[\\]]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_nested_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_many_levels_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a]b[[c]d][[[e]]]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a-e]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_not_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^[^a]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_and_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a&&a]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_and_b_Test) {
  ParseTree tree;
  try {
    parse({"[a&&b]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a_and_a_and_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a&&a&&a]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_nested_a_and_nested_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a]&&[a]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_word_and_digit_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[\\w&&\\d]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[0-9]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_and_a_to_z_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]&&[a-z]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_and_b_to_y_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]&&[b-y]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[b-y]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_and_not_y_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]&&[^y]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a-xz]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_less_a_Test) {
  ParseTree tree;
  try {
    parse({"[a--a]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a_less_b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a--b]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_less_a_less_a_Test) {
  ParseTree tree;
  try {
    parse({"[a--a--a]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_nested_a_less_nested_a_Test) {
  ParseTree tree;
  try {
    parse({"[[a]--[a]]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_word_less_digit_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[\\w--\\d]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[A-Z_a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_less_a_to_z_Test) {
  ParseTree tree;
  try {
    parse({"[[a-z]--[a-z]]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a_to_z_less_b_to_y_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]--[b-y]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[az]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_less_not_y_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]--[^y]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[y]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_xor_a_Test) {
  ParseTree tree;
  try {
    parse({"[a~~a]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a_xor_b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a~~b]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[ab]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_xor_a_xor_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a~~a~~a]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_word_xor_digit_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[\\w~~\\d]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[A-Z_a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_xor_a_to_z_Test) {
  ParseTree tree;
  try {
    parse({"[[a-z]~~[a-z]]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  SCOPE_ASSERT(false);
}

SCOPE_TEST(parseUnparse_a_to_z_xor_b_to_y_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]~~[b-y]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[az]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_to_z_xor_not_y_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a-z]~~[^y]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^a-xz]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_not_not_not_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^[^[^[^a]]]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_not_caret_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^[^^]]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[\\^]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_hyphen_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^\\-a]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^a-]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_a_and_b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^a&&b]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[\\x00-\\xFF]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_a_less_b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^a--b]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_a_xor_b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^a~~b]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^ab]", unparse(tree));
}

SCOPE_TEST(parseUnparse_nested_a_less_b_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[[a]--b]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_not_nested_a_to_b_less_hyphen_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[^[a-b]--\\-]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[^ab]", unparse(tree));
}

SCOPE_TEST(parseUnparse_minus_hyphen_precedence_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"[a-z--b-y]", false, false}, tree));
  SCOPE_ASSERT_EQUAL("[az]", unparse(tree));
}

SCOPE_TEST(parseUnparse_hyphen_hyphen_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"--", false, false}, tree));
  SCOPE_ASSERT_EQUAL("--", unparse(tree));
}

SCOPE_TEST(parseUnparse_american_express_cc_number_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse({"3[47]\\d{2}[ \\-]?\\d{6}[ \\-]?\\d{5}", false, false}, tree));
  SCOPE_ASSERT_EQUAL("3[47][0-9]{2}[ -]?[0-9]{6}[ -]?[0-9]{5}", unparse(tree));
}

SCOPE_TEST(byteToCharacterStringTest) {
  std::ostringstream ss;

  for (uint32_t i = 0; i < 256; ++i) {
    std::string actual = byteToCharacterString(i);

    switch (i) {
    case '\a': SCOPE_ASSERT_EQUAL("\\a", actual); break;
    case '\b': SCOPE_ASSERT_EQUAL("\\b", actual); break;
    case 0x1B: SCOPE_ASSERT_EQUAL("\\e", actual); break;
    case '\f': SCOPE_ASSERT_EQUAL("\\f", actual); break;
    case '\n': SCOPE_ASSERT_EQUAL("\\n", actual); break;
    case '\r': SCOPE_ASSERT_EQUAL("\\r", actual); break;
    case '\t': SCOPE_ASSERT_EQUAL("\\t", actual); break;
    case '\\': SCOPE_ASSERT_EQUAL("\\\\", actual); break;
    default:
      if (0x20 <= i && i <= 0x7E) {
        SCOPE_ASSERT_EQUAL(std::string(1, (char) i), actual);
      }
      else {
        ss << "\\x" << std::hex << std::uppercase
                    << std::setfill('0') << std::setw(2) << i;
        SCOPE_ASSERT_EQUAL(ss.str(), actual);
        ss.str("");
      }
    }
  }
}

SCOPE_TEST(byteSet_a_ToCharacterClassTest) {
  ByteSet bs;
  bs['a'] = true;
  SCOPE_ASSERT_EQUAL("a", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^a", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_whack_a_ToCharacterClassTest) {
  ByteSet bs;
  bs['\a'] = true;
  SCOPE_ASSERT_EQUAL("\\a", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\a", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_null_ToCharacterClassTest) {
  ByteSet bs;
  bs[0] = true;
  SCOPE_ASSERT_EQUAL("\\x00", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\x00", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_tab_ToCharacterClassTest) {
  ByteSet bs;
  bs['\t'] = true;
  SCOPE_ASSERT_EQUAL("\\t", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\t", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_space_ToCharacterClassTest) {
  ByteSet bs;
  bs[' '] = true;
  SCOPE_ASSERT_EQUAL(" ", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^ ", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_hyphen_ToCharacterClassTest) {
  ByteSet bs;
  bs['-'] = true;
  SCOPE_ASSERT_EQUAL("-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_caret_ToCharacterClassTest) {
  ByteSet bs;
  bs['^'] = true;
  SCOPE_ASSERT_EQUAL("\\^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^^", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_caret_hyphen_ToCharacterClassTest) {
  ByteSet bs;
  bs['^'] = bs['-'] = true;
  SCOPE_ASSERT_EQUAL("-^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^^-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_whack_whack_ToCharacterClassTest) {
  ByteSet bs;
  bs['\\'] = true;
  SCOPE_ASSERT_EQUAL("\\\\", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\\\", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_right_bracketcaret_ToCharacterClassTest) {
  ByteSet bs;
  bs[']'] = true;
  SCOPE_ASSERT_EQUAL("]", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^]", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_adn_ToCharacterClassTest) {
  ByteSet bs;
  bs['a'] = bs['d'] = bs['n'] = true;
  SCOPE_ASSERT_EQUAL("adn", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^adn", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_abc_ToCharacterClassTest) {
  ByteSet bs;
  bs['a'] = bs['b'] = bs['c'] = true;
  SCOPE_ASSERT_EQUAL("abc", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^abc", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_abcd_ToCharacterClassTest) {
  ByteSet bs;
  bs['a'] = bs['b'] = bs['c'] = bs['d'] = true;
  SCOPE_ASSERT_EQUAL("a-d", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^a-d", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_all_ToCharacterClassTest) {
  ByteSet bs;
  bs.set();
  SCOPE_ASSERT_EQUAL("\\x00-\\xFF", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\x00-\\xFF", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_digits_letters_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '0'; i < '9' + 1; ++i) bs[i] = true;
  for (uint32_t i = 'A'; i < 'Z' + 1; ++i) bs[i] = true;
  for (uint32_t i = 'a'; i < 'z' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("0-9A-Za-z", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^0-9A-Za-z", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_hyphen_to_zero_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '-'; i < '0' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("./0-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^./0-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_hyphen_to_one_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '-'; i < '1' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL(".-1-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^.-1-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_asterisk_to_hyphen_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '*'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("*+,-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^*+,-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_right_parenthesis_to_hyphen_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = ')'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL(")-,-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^)-,-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_comma_to_period_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = ','; i < '.' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL(",-.", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^,-.", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_plus_to_hyphen_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '+'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("+,-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^+,-", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_caret_to_a_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '^'; i < 'a' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("_`a^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^_`a^", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_caret_to_b_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = '^'; i < 'b' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("_-b^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^_-b^", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_A_right_bracket_ToCharacterClassTest) {
  ByteSet bs;
  bs['A'] = bs[']'] = true;
  SCOPE_ASSERT_EQUAL("A\\]", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^A\\]", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_A_to_right_bracket_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = 'A'; i < ']' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("A-\\]", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^A-\\]", byteSetToCharacterClass(bs));
}

SCOPE_TEST(byteSet_right_bracket_to_a_ToCharacterClassTest) {
  ByteSet bs;
  for (uint32_t i = ']'; i < 'a' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("]-a", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^]-a", byteSetToCharacterClass(bs));
}
