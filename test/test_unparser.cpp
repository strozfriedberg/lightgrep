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

#include "catch.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "parser.h"
#include "parsetree.h"
#include "unparser.h"

TEST_CASE("unparseEmptyTest") {
  ParseTree tree;
  ParseNode root(ParseNode::REGEXP, 0, 0, 0);
  tree.Root = &root;

  REQUIRE("" == unparse(tree));
}

TEST_CASE("parseUnparse_comma_Test") {
  ParseTree tree;
  REQUIRE(parse({",", false, false}, tree));
  REQUIRE("," == unparse(tree));
}

TEST_CASE("parseUnparse_hyphen_Test") {
  ParseTree tree;
  REQUIRE(parse({"-", false, false}, tree));
  REQUIRE("-" == unparse(tree));
}

TEST_CASE("parseUnparse_LC_Test") {
  ParseTree tree;
  REQUIRE(parse({"{", false, false}, tree));
  REQUIRE("{" == unparse(tree));
}

TEST_CASE("parseUnparse_RC_Test") {
  ParseTree tree;
  REQUIRE(parse({"}", false, false}, tree));
  REQUIRE("}" == unparse(tree));
}

TEST_CASE("parseUnparse_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"a", false, false}, tree));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("parseUnparse_aQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a?", false, false}, tree));
  REQUIRE("a?" == unparse(tree));
}

TEST_CASE("parseUnparse_aS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*", false, false}, tree));
  REQUIRE("a*" == unparse(tree));
}

TEST_CASE("parseUnparse_aP_Test") {
  ParseTree tree;
  REQUIRE(parse({"a+", false, false}, tree));
  REQUIRE("a+" == unparse(tree));
}

TEST_CASE("parseUnparse_aQQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a??", false, false}, tree));
  REQUIRE("a??" == unparse(tree));
}

TEST_CASE("parseUnparse_aSQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*?", false, false}, tree));
  REQUIRE("a*?" == unparse(tree));
}

TEST_CASE("parseUnparse_aPQ_Test") {
  ParseTree tree;
  REQUIRE(parse({"a+?", false, false}, tree));
  REQUIRE("a+?" == unparse(tree));
}

TEST_CASE("parseUnparse_ab_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab", false, false}, tree));
  REQUIRE("ab" == unparse(tree));
}

TEST_CASE("parseUnparse_aSb_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*b", false, false}, tree));
  REQUIRE("a*b" == unparse(tree));
}

TEST_CASE("parseUnparse_abS_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab*", false, false}, tree));
  REQUIRE("ab*" == unparse(tree));
}

TEST_CASE("parseUnparse_aSbS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*b*", false, false}, tree));
  REQUIRE("a*b*" == unparse(tree));
}

TEST_CASE("parseUnparse_aOrb_Test") {
  ParseTree tree;
  REQUIRE(parse({"a|b", false, false}, tree));
  REQUIRE("a|b" == unparse(tree));
}

TEST_CASE("parseUnparse_aSOrb_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*|b", false, false}, tree));
  REQUIRE("a*|b" == unparse(tree));
}

TEST_CASE("parseUnparse_aOrbS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a|b*", false, false}, tree));
  REQUIRE("a|b*" == unparse(tree));
}

TEST_CASE("parseUnparse_aSOrbS_Test") {
  ParseTree tree;
  REQUIRE(parse({"a*|b*", false, false}, tree));
  REQUIRE("a*|b*" == unparse(tree));
}

TEST_CASE("parseUnparse_LPaRP_Test") {
  ParseTree tree;
  REQUIRE(parse({"(a)", false, false}, tree));
  REQUIRE("a" == unparse(tree));
}

TEST_CASE("parseUnparse_LPabRPS_Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab)*", false, false}, tree));
  REQUIRE("(ab)*" == unparse(tree));
}

TEST_CASE("parseUnparse_LPaOrbRPc_Test") {
  ParseTree tree;
  REQUIRE(parse({"(a|b)c", false, false}, tree));
  REQUIRE("(a|b)c" == unparse(tree));
}

TEST_CASE("parseUnparse_aOrbOrc_Test") {
  ParseTree tree;
  REQUIRE(parse({"a|b|c", false, false}, tree));
  REQUIRE("a|b|c" == unparse(tree));
}

TEST_CASE("parseUnparse_abOrcd_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab|cd", false, false}, tree));
  REQUIRE("ab|cd" == unparse(tree));
}

TEST_CASE("parseUnparse_LBaRB_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_LBabcRB_Test") {
  ParseTree tree;
  REQUIRE(parse({"[abc]", false, false}, tree));
  REQUIRE("[abc]" == unparse(tree));
}

TEST_CASE("parseUnparse_LBabcdRB_Test") {
  ParseTree tree;
  REQUIRE(parse({"[abcd]", false, false}, tree));
  REQUIRE("[a-d]" == unparse(tree));
}

TEST_CASE("parseUnparse_LBdcbaRB_Test") {
  ParseTree tree;
  REQUIRE(parse({"[dcba]", false, false}, tree));
  REQUIRE("[a-d]" == unparse(tree));
}

TEST_CASE("parseUnparse_a3_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{3}", false, false}, tree));
  REQUIRE("a{3}" == unparse(tree));
}

TEST_CASE("parseUnparse_a42_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{42}", false, false}, tree));
  REQUIRE("a{42}" == unparse(tree));
}

TEST_CASE("parseUnparse_a0_7_Test") {
  ParseTree tree;
  REQUIRE(parse({"a{0,7}", false, false}, tree));
  REQUIRE("a{0,7}" == unparse(tree));
}

TEST_CASE("parseUnparse_a4_3_Test") {
  ParseTree tree;
  try {
    parse({"a{4,3}", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a4_3Q_Test") {
  ParseTree tree;
  try {
    parse({"a{4,3}?", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a42__Test") {
  ParseTree tree;
  REQUIRE(parse({"a{42,}", false, false}, tree));
  REQUIRE("a{42,}" == unparse(tree));
}

TEST_CASE("parseUnparse_LPabRP3_Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab){3}", false, false}, tree));
  REQUIRE("(ab){3}" == unparse(tree));
}

TEST_CASE("parseUnparse_LPabRP5_7_Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab){5,7}", false, false}, tree));
  REQUIRE("(ab){5,7}" == unparse(tree));
}

TEST_CASE("parseUnparse_LPabRP42__Test") {
  ParseTree tree;
  REQUIRE(parse({"(ab){42,}", false, false}, tree));
  REQUIRE("(ab){42,}" == unparse(tree));
}

TEST_CASE("parseUnparse_LPa1RP1__Test") {
  ParseTree tree;
  REQUIRE(parse({"(a{1}){1}", false, false}, tree));
  REQUIRE("(a{1}){1}" == unparse(tree));
}

TEST_CASE("parseUnparse_CCaCaret_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a^]", false, false}, tree));
  REQUIRE("[a^]" == unparse(tree));
}

TEST_CASE("parseUnparse_CCd_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\d", false, false}, tree));
  REQUIRE("[0-9]" == unparse(tree));
}

TEST_CASE("parseUnparse_CCD_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\D", false, false}, tree));
  REQUIRE("[^0-9]" == unparse(tree));
}

TEST_CASE("parseUnparse_CCs_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\s", false, false}, tree));
  REQUIRE("[\\t-\\r ]" == unparse(tree));
}

TEST_CASE("parseUnparse_CCS_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\S", false, false}, tree));
  REQUIRE("[^\\t-\\r ]" == unparse(tree));
}

TEST_CASE("parseUnparse_CCw_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\w", false, false}, tree));
  REQUIRE("[0-9A-Z_a-z]" == unparse(tree));
}

TEST_CASE("parseUnparse_CCW_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\W", false, false}, tree));
  REQUIRE("[^0-9A-Z_a-z]" == unparse(tree));
}

TEST_CASE("parseUnparse_LBaTozAToZCCdDot_PctBSHyphenPlusRB_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a-zA-Z\\d._%\\-+]", false, false}, tree));
  REQUIRE("[%+.0-9A-Z_a-z-]" == unparse(tree));
}

TEST_CASE("parseUnparse_BSx_Test") {
  ParseTree tree;
  try {
    parse({"\\x", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_BSx0_Test") {
  ParseTree tree;
  try {
    parse({"\\x0", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_BSx00_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\x00", false, false}, tree));
  REQUIRE("\\x00" == unparse(tree));
}

TEST_CASE("parseUnparse_BS0_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\0", false, false}, tree));
  REQUIRE("\\x00" == unparse(tree));
}

TEST_CASE("parseUnparse_BS00_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\00", false, false}, tree));
  REQUIRE("\\x00" == unparse(tree));
}

TEST_CASE("parseUnparse_BS000_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\000", false, false}, tree));
  REQUIRE("\\x00" == unparse(tree));
}

TEST_CASE("parseUnparse_BS0000_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\0000", false, false}, tree));
  REQUIRE("\\x000" == unparse(tree));
}

TEST_CASE("parseUnparse_BS08_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\08", false, false}, tree));
  REQUIRE("\\x008" == unparse(tree));
}

TEST_CASE("parseUnparse_BS377_Test") {
  ParseTree tree;
  REQUIRE(parse({"\\377", false, false}, tree));
  REQUIRE("\\xFF" == unparse(tree));
}

TEST_CASE("parseUnparse_BS400_Test") {
  ParseTree tree;
  try {
    parse({"\\400", false, false}, tree);
    REQUIRE(false);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_BSq_Test") {
  ParseTree tree;
  try {
    parse({"\\q", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_xBSq_Test") {
  ParseTree tree;
  try {
    parse({"x\\q", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_invalid_utf8_Test") {
  ParseTree tree;
  try {
    parse({"\xFF", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_CCempty_Test") {
  ParseTree tree;
  try {
    parse({"[]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_CC_left_bracket_Test") {
  ParseTree tree;
  REQUIRE(parse({"[\\[]", false, false}, tree));
  REQUIRE("[[]" == unparse(tree));
}

TEST_CASE("parseUnparse_CC_right_bracket_Test") {
  ParseTree tree;
  REQUIRE(parse({"[]]", false, false}, tree));
  REQUIRE("[]]" == unparse(tree));
}

TEST_CASE("parseUnparse_CC_right_bracket_left_bracket_Test") {
  ParseTree tree;
  REQUIRE(parse({"[]\\[]", false, false}, tree));
  REQUIRE("[[\\]]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_nested_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a]]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_many_levels_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a]b[[c]d][[[e]]]]", false, false}, tree));
  REQUIRE("[a-e]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_not_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^[^a]]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_and_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a&&a]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_and_b_Test") {
  ParseTree tree;
  try {
    parse({"[a&&b]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a_and_a_and_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a&&a&&a]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_nested_a_and_nested_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a]&&[a]]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_word_and_digit_Test") {
  ParseTree tree;
  REQUIRE(parse({"[\\w&&\\d]", false, false}, tree));
  REQUIRE("[0-9]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_and_a_to_z_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]&&[a-z]]", false, false}, tree));
  REQUIRE("[a-z]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_and_b_to_y_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]&&[b-y]]", false, false}, tree));
  REQUIRE("[b-y]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_and_not_y_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]&&[^y]]", false, false}, tree));
  REQUIRE("[a-xz]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_less_a_Test") {
  ParseTree tree;
  try {
    parse({"[a--a]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a_less_b_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a--b]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_less_a_less_a_Test") {
  ParseTree tree;
  try {
    parse({"[a--a--a]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_nested_a_less_nested_a_Test") {
  ParseTree tree;
  try {
    parse({"[[a]--[a]]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_word_less_digit_Test") {
  ParseTree tree;
  REQUIRE(parse({"[\\w--\\d]", false, false}, tree));
  REQUIRE("[A-Z_a-z]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_less_a_to_z_Test") {
  ParseTree tree;
  try {
    parse({"[[a-z]--[a-z]]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a_to_z_less_b_to_y_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]--[b-y]]", false, false}, tree));
  REQUIRE("[az]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_less_not_y_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]--[^y]]", false, false}, tree));
  REQUIRE("[y]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_xor_a_Test") {
  ParseTree tree;
  try {
    parse({"[a~~a]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a_xor_b_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a~~b]", false, false}, tree));
  REQUIRE("[ab]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_xor_a_xor_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a~~a~~a]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_word_xor_digit_Test") {
  ParseTree tree;
  REQUIRE(parse({"[\\w~~\\d]", false, false}, tree));
  REQUIRE("[A-Z_a-z]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_xor_a_to_z_Test") {
  ParseTree tree;
  try {
    parse({"[[a-z]~~[a-z]]", false, false}, tree);
  }
  catch (const std::runtime_error&) {
    // expected
    return;
  }
  REQUIRE(false);
}

TEST_CASE("parseUnparse_a_to_z_xor_b_to_y_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]~~[b-y]]", false, false}, tree));
  REQUIRE("[az]" == unparse(tree));
}

TEST_CASE("parseUnparse_a_to_z_xor_not_y_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a-z]~~[^y]]", false, false}, tree));
  REQUIRE("[^a-xz]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_not_not_not_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^[^[^[^a]]]]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_not_caret_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^[^^]]", false, false}, tree));
  REQUIRE("[\\^]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_hyphen_a_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^\\-a]", false, false}, tree));
  REQUIRE("[^a-]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_a_and_b_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^a&&b]", false, false}, tree));
  REQUIRE("[\\x00-\\xFF]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_a_less_b_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^a--b]", false, false}, tree));
  REQUIRE("[^a]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_a_xor_b_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^a~~b]", false, false}, tree));
  REQUIRE("[^ab]" == unparse(tree));
}

TEST_CASE("parseUnparse_nested_a_less_b_Test") {
  ParseTree tree;
  REQUIRE(parse({"[[a]--b]", false, false}, tree));
  REQUIRE("[a]" == unparse(tree));
}

TEST_CASE("parseUnparse_not_nested_a_to_b_less_hyphen_Test") {
  ParseTree tree;
  REQUIRE(parse({"[^[a-b]--\\-]", false, false}, tree));
  REQUIRE("[^ab]" == unparse(tree));
}

TEST_CASE("parseUnparse_minus_hyphen_precedence_Test") {
  ParseTree tree;
  REQUIRE(parse({"[a-z--b-y]", false, false}, tree));
  REQUIRE("[az]" == unparse(tree));
}

TEST_CASE("parseUnparse_hyphen_hyphen_Test") {
  ParseTree tree;
  REQUIRE(parse({"--", false, false}, tree));
  REQUIRE("--" == unparse(tree));
}

TEST_CASE("parseUnparse_american_express_cc_number_Test") {
  ParseTree tree;
  REQUIRE(parse({"3[47]\\d{2}[ \\-]?\\d{6}[ \\-]?\\d{5}", false, false}, tree));
  REQUIRE("3[47][0-9]{2}[ -]?[0-9]{6}[ -]?[0-9]{5}" == unparse(tree));
}

TEST_CASE("byteToCharacterStringTest") {
  std::ostringstream ss;

  for (uint32_t i = 0; i < 256; ++i) {
    std::string actual = byteToCharacterString(i);

    switch (i) {
    case '\a': REQUIRE("\\a" == actual); break;
    case '\b': REQUIRE("\\b" == actual); break;
    case 0x1B: REQUIRE("\\e" == actual); break;
    case '\f': REQUIRE("\\f" == actual); break;
    case '\n': REQUIRE("\\n" == actual); break;
    case '\r': REQUIRE("\\r" == actual); break;
    case '\t': REQUIRE("\\t" == actual); break;
    case '\\': REQUIRE("\\\\" == actual); break;
    default:
      if (0x20 <= i && i <= 0x7E) {
        REQUIRE(std::string(1, (char) i) == actual);
      }
      else {
        ss << "\\x" << std::hex << std::uppercase
                    << std::setfill('0') << std::setw(2) << i;
        REQUIRE(ss.str() == actual);
        ss.str("");
      }
    }
  }
}

TEST_CASE("byteSet_a_ToCharacterClassTest") {
  ByteSet bs;
  bs['a'] = true;
  REQUIRE("a" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^a" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_whack_a_ToCharacterClassTest") {
  ByteSet bs;
  bs['\a'] = true;
  REQUIRE("\\a" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^\\a" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_null_ToCharacterClassTest") {
  ByteSet bs;
  bs[0] = true;
  REQUIRE("\\x00" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^\\x00" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_tab_ToCharacterClassTest") {
  ByteSet bs;
  bs['\t'] = true;
  REQUIRE("\\t" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^\\t" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_space_ToCharacterClassTest") {
  ByteSet bs;
  bs[' '] = true;
  REQUIRE(" " == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^ " == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_hyphen_ToCharacterClassTest") {
  ByteSet bs;
  bs['-'] = true;
  REQUIRE("-" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_caret_ToCharacterClassTest") {
  ByteSet bs;
  bs['^'] = true;
  REQUIRE("\\^" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^^" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_caret_hyphen_ToCharacterClassTest") {
  ByteSet bs;
  bs['^'] = bs['-'] = true;
  REQUIRE("-^" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^^-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_whack_whack_ToCharacterClassTest") {
  ByteSet bs;
  bs['\\'] = true;
  REQUIRE("\\\\" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^\\\\" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_right_bracketcaret_ToCharacterClassTest") {
  ByteSet bs;
  bs[']'] = true;
  REQUIRE("]" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^]" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_adn_ToCharacterClassTest") {
  ByteSet bs;
  bs['a'] = bs['d'] = bs['n'] = true;
  REQUIRE("adn" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^adn" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_abc_ToCharacterClassTest") {
  ByteSet bs;
  bs['a'] = bs['b'] = bs['c'] = true;
  REQUIRE("abc" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^abc" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_abcd_ToCharacterClassTest") {
  ByteSet bs;
  bs['a'] = bs['b'] = bs['c'] = bs['d'] = true;
  REQUIRE("a-d" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^a-d" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_all_ToCharacterClassTest") {
  ByteSet bs;
  bs.set();
  REQUIRE("\\x00-\\xFF" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^\\x00-\\xFF" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_digits_letters_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '0'; i < '9' + 1; ++i) bs[i] = true;
  for (uint32_t i = 'A'; i < 'Z' + 1; ++i) bs[i] = true;
  for (uint32_t i = 'a'; i < 'z' + 1; ++i) bs[i] = true;
  REQUIRE("0-9A-Za-z" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^0-9A-Za-z" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_hyphen_to_zero_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '-'; i < '0' + 1; ++i) bs[i] = true;
  REQUIRE("./0-" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^./0-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_hyphen_to_one_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '-'; i < '1' + 1; ++i) bs[i] = true;
  REQUIRE(".-1-" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^.-1-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_asterisk_to_hyphen_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '*'; i < '-' + 1; ++i) bs[i] = true;
  REQUIRE("*+,-" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^*+,-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_right_parenthesis_to_hyphen_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = ')'; i < '-' + 1; ++i) bs[i] = true;
  REQUIRE(")-,-" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^)-,-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_comma_to_period_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = ','; i < '.' + 1; ++i) bs[i] = true;
  REQUIRE(",-." == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^,-." == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_plus_to_hyphen_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '+'; i < '-' + 1; ++i) bs[i] = true;
  REQUIRE("+,-" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^+,-" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_caret_to_a_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '^'; i < 'a' + 1; ++i) bs[i] = true;
  REQUIRE("_`a^" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^_`a^" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_caret_to_b_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = '^'; i < 'b' + 1; ++i) bs[i] = true;
  REQUIRE("_-b^" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^_-b^" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_A_right_bracket_ToCharacterClassTest") {
  ByteSet bs;
  bs['A'] = bs[']'] = true;
  REQUIRE("A\\]" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^A\\]" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_A_to_right_bracket_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = 'A'; i < ']' + 1; ++i) bs[i] = true;
  REQUIRE("A-\\]" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^A-\\]" == byteSetToCharacterClass(bs));
}

TEST_CASE("byteSet_right_bracket_to_a_ToCharacterClassTest") {
  ByteSet bs;
  for (uint32_t i = ']'; i < 'a' + 1; ++i) bs[i] = true;
  REQUIRE("]-a" == byteSetToCharacterClass(bs));
  bs.flip();
  REQUIRE("^]-a" == byteSetToCharacterClass(bs));
}

TEST_CASE("parseUnparse_i_switch_01_Test") {
  ParseTree tree;
  REQUIRE(parse({"(?i)abcd", false, false}, tree));
  REQUIRE("[Aa][Bb][Cc][Dd]" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_02_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab(?i)cd", false, false}, tree));
  REQUIRE("ab[Cc][Dd]" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_03_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab((?i)c)d", false, false}, tree));
  REQUIRE("ab[Cc]d" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_04_Test") {
  ParseTree tree;
  REQUIRE(parse({"a(?i)b(?-i)cd", false, false}, tree));
  REQUIRE("a[Bb]cd" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_05_Test") {
  ParseTree tree;
  REQUIRE(parse({"(?i)((?-i)abcd)", false, false}, tree));
  REQUIRE("abcd" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_06_Test") {
  ParseTree tree;
  REQUIRE(parse({"abcd(?i)", false, false}, tree));
  REQUIRE("abcd" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_07_Test") {
  ParseTree tree;
  REQUIRE(parse({"a(?i)b|cd", false, false}, tree));
  REQUIRE("a[Bb]|[Cc][Dd]" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_08_Test") {
  ParseTree tree;
  REQUIRE(parse({"(?i)(?-i)abcd", false, false}, tree));
  REQUIRE("abcd" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_09_Test") {
  ParseTree tree;
  REQUIRE(parse({"(?i)((?-i)ab)cd", false, false}, tree));
  REQUIRE("ab[Cc][Dd]" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_10_Test") {
  ParseTree tree;
  REQUIRE(parse({"(?i)(?i)abcd", false, false}, tree));
  REQUIRE("[Aa][Bb][Cc][Dd]" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_11_Test") {
  ParseTree tree;
  REQUIRE(parse({"ab(?i)|cd", false, false}, tree));
  REQUIRE("ab|[Cc][Dd]" == unparse(tree));
}

TEST_CASE("parseUnparse_i_switch_12_Test") {
  // (?i) is not a switch when inside a character class
  ParseTree tree;
  REQUIRE(parse({"ab[(?i)]cd", false, false}, tree));
  REQUIRE("ab[()?i]cd" == unparse(tree));
}
