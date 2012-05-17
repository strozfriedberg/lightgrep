#include <scope/test.h>

#include <iomanip>
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
  SCOPE_ASSERT(parse(",", false, false, tree));
  SCOPE_ASSERT_EQUAL(",", unparse(tree));
}

SCOPE_TEST(parseUnparse_hyphen_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("-", false, false, tree));
  SCOPE_ASSERT_EQUAL("-", unparse(tree));
}

SCOPE_TEST(parseUnparse_LC_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("{", false, false, tree));
  SCOPE_ASSERT_EQUAL("{", unparse(tree));
}

SCOPE_TEST(parseUnparse_RC_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("}", false, false, tree));
  SCOPE_ASSERT_EQUAL("}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a", false, false, tree));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(parseUnparse_aQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a?", false, false, tree));
  SCOPE_ASSERT_EQUAL("a?", unparse(tree));
}

SCOPE_TEST(parseUnparse_aS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*", false, false, tree));
  SCOPE_ASSERT_EQUAL("a*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a+", false, false, tree));
  SCOPE_ASSERT_EQUAL("a+", unparse(tree));
}

SCOPE_TEST(parseUnparse_aQQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a??", false, false, tree));
  SCOPE_ASSERT_EQUAL("a??", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*?", false, false, tree));
  SCOPE_ASSERT_EQUAL("a*?", unparse(tree));
}

SCOPE_TEST(parseUnparse_aPQ_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a+?", false, false, tree));
  SCOPE_ASSERT_EQUAL("a+?", unparse(tree));
}

SCOPE_TEST(parseUnparse_ab_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("ab", false, false, tree));
  SCOPE_ASSERT_EQUAL("ab", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b", false, false, tree));
  SCOPE_ASSERT_EQUAL("a*b", unparse(tree));
}

SCOPE_TEST(parseUnparse_abS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("ab*", false, false, tree));
  SCOPE_ASSERT_EQUAL("ab*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*b*", false, false, tree));
  SCOPE_ASSERT_EQUAL("a*b*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aOrb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b", false, false, tree));
  SCOPE_ASSERT_EQUAL("a|b", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSOrb_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b", false, false, tree));
  SCOPE_ASSERT_EQUAL("a*|b", unparse(tree));
}

SCOPE_TEST(parseUnparse_aOrbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b*", false, false, tree));
  SCOPE_ASSERT_EQUAL("a|b*", unparse(tree));
}

SCOPE_TEST(parseUnparse_aSOrbS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a*|b*", false, false, tree));
  SCOPE_ASSERT_EQUAL("a*|b*", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPaRP_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(a)", false, false, tree));
  SCOPE_ASSERT_EQUAL("a", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRPS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(ab)*", false, false, tree));
  SCOPE_ASSERT_EQUAL("(ab)*", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPaOrbRPc_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(a|b)c", false, false, tree));
  SCOPE_ASSERT_EQUAL("(a|b)c", unparse(tree));
}

SCOPE_TEST(parseUnparse_aOrbOrc_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a|b|c", false, false, tree));
  SCOPE_ASSERT_EQUAL("a|b|c", unparse(tree));
}

SCOPE_TEST(parseUnparse_abOrcd_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("ab|cd", false, false, tree));
  SCOPE_ASSERT_EQUAL("ab|cd", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBaRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("[a]", false, false, tree));
  SCOPE_ASSERT_EQUAL("[a]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBabcRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("[abc]", false, false, tree));
  SCOPE_ASSERT_EQUAL("[abc]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBabcdRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("[abcd]", false, false, tree));
  SCOPE_ASSERT_EQUAL("[a-d]", unparse(tree));
}

SCOPE_TEST(parseUnparse_LBdcbaRB_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("[dcba]", false, false, tree));
  SCOPE_ASSERT_EQUAL("[a-d]", unparse(tree));
}

SCOPE_TEST(parseUnparse_a3_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{3}", false, false, tree));
  SCOPE_ASSERT_EQUAL("a{3}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a42_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{42}", false, false, tree));
  SCOPE_ASSERT_EQUAL("a{42}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a0_7_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{0,7}", false, false, tree));
  SCOPE_ASSERT_EQUAL("a{0,7}", unparse(tree));
}

SCOPE_TEST(parseUnparse_a4_3_Test) {
  ParseTree tree;
  try {
    parse("a{4,3}", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_a4_3Q_Test) {
  ParseTree tree;
  try {
    parse("a{4,3}?", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_a42__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("a{42,}", false, false, tree));
  SCOPE_ASSERT_EQUAL("a{42,}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRP3_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(ab){3}", false, false, tree));
  SCOPE_ASSERT_EQUAL("(ab){3}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRP5_7_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(ab){5,7}", false, false, tree));
  SCOPE_ASSERT_EQUAL("(ab){5,7}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPabRP42__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(ab){42,}", false, false, tree));
  SCOPE_ASSERT_EQUAL("(ab){42,}", unparse(tree));
}

SCOPE_TEST(parseUnparse_LPa1RP1__Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("(a{1}){1}", false, false, tree));
  SCOPE_ASSERT_EQUAL("(a{1}){1}", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCaCaret_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("[a^]", false, false, tree));
  SCOPE_ASSERT_EQUAL("[a^]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCd_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\d", false, false, tree));
  SCOPE_ASSERT_EQUAL("[0-9]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCD_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\D", false, false, tree));
  SCOPE_ASSERT_EQUAL("[^0-9]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCs_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\s", false, false, tree));
  SCOPE_ASSERT_EQUAL("[\\t\\n\\f\\r ]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCS_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\S", false, false, tree));
  SCOPE_ASSERT_EQUAL("[^\\t\\n\\f\\r ]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCw_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\w", false, false, tree));
  SCOPE_ASSERT_EQUAL("[0-9A-Z_a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_CCW_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\W", false, false, tree));
  SCOPE_ASSERT_EQUAL("[^0-9A-Z_a-z]", unparse(tree));
}

SCOPE_TEST(parseUnparse_BSx_Test) {
  ParseTree tree;
  try {
    parse("\\x", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_BSx0_Test) {
  ParseTree tree;
  try {
    parse("\\x0", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_BSx00_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\x00", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS0_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\0", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS00_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\00", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS000_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\000", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\x00", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS0000_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\0000", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\x000", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS08_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\08", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\x008", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS377_Test) {
  ParseTree tree;
  SCOPE_ASSERT(parse("\\377", false, false, tree));
  SCOPE_ASSERT_EQUAL("\\xFF", unparse(tree));
}

SCOPE_TEST(parseUnparse_BS400_Test) {
  ParseTree tree;
  try {
    parse("\\400", false, false, tree);
    SCOPE_ASSERT(false);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_BSq_Test) {
  ParseTree tree;
  try {
    parse("\\q", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_xBSq_Test) {
  ParseTree tree;
  try {
    parse("x\\q", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(parseUnparse_invalid_utf8_Test) {
  ParseTree tree;
  try {
    parse("\xFF", false, false, tree);
  }
  catch (const std::runtime_error&) {
    // expected
  }
}

SCOPE_TEST(byteToCharacterString) {
  std::stringstream ss;

  for (uint32 i = 0; i < 256; ++i) {
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

SCOPE_TEST(byteSetToCharacterClassTest) {
  ByteSet bs;

  bs['a'] = true;
  SCOPE_ASSERT_EQUAL("a", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^a", byteSetToCharacterClass(bs));
  bs.reset();

  bs['\a'] = true;
  SCOPE_ASSERT_EQUAL("\\a", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\a", byteSetToCharacterClass(bs));
  bs.reset();

  bs[0] = true;
  SCOPE_ASSERT_EQUAL("\\x00", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\x00", byteSetToCharacterClass(bs));
  bs.reset();

  bs['\t'] = true;
  SCOPE_ASSERT_EQUAL("\\t", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\t", byteSetToCharacterClass(bs));
  bs.reset();

  bs[' '] = true;
  SCOPE_ASSERT_EQUAL(" ", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^ ", byteSetToCharacterClass(bs));
  bs.reset();

  bs['-'] = true;
  SCOPE_ASSERT_EQUAL("-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^-", byteSetToCharacterClass(bs));
  bs.reset();

  bs['^'] = true;
  SCOPE_ASSERT_EQUAL("\\^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^^", byteSetToCharacterClass(bs));
  bs.reset();

  bs['^'] = bs['-'] = true;
  SCOPE_ASSERT_EQUAL("-^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^^-", byteSetToCharacterClass(bs));
  bs.reset();

  bs['\\'] = true;
  SCOPE_ASSERT_EQUAL("\\\\", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\\\", byteSetToCharacterClass(bs));
  bs.reset();

  bs[']'] = true;
  SCOPE_ASSERT_EQUAL("]", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^]", byteSetToCharacterClass(bs));
  bs.reset();

  bs['a'] = bs['d'] = bs['n'] = true;
  SCOPE_ASSERT_EQUAL("adn", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^adn", byteSetToCharacterClass(bs));
  bs.reset();

  bs['a'] = bs['b'] = bs['c'] = true;
  SCOPE_ASSERT_EQUAL("abc", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^abc", byteSetToCharacterClass(bs));
  bs.reset();

  bs['a'] = bs['b'] = bs['c'] = bs['d'] = true;
  SCOPE_ASSERT_EQUAL("a-d", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^a-d", byteSetToCharacterClass(bs));
  bs.reset();

  bs.set();
  SCOPE_ASSERT_EQUAL("\\x00-\\xFF", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^\\x00-\\xFF", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '0'; i < '9' + 1; ++i) bs[i] = true;
  for (uint32 i = 'A'; i < 'Z' + 1; ++i) bs[i] = true;
  for (uint32 i = 'a'; i < 'z' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("0-9A-Za-z", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^0-9A-Za-z", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '-'; i < '0' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("./0-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^./0-", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '-'; i < '1' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL(".-1-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^.-1-", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '*'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("*+,-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^*+,-", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = ')'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL(")-,-", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '+'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("+,-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^+,-", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = ','; i < '.' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL(",-.", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^,-.", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '+'; i < '-' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("+,-", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^+,-", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '^'; i < 'a' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("_`a^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^_`a^", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = '^'; i < 'b' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("_-b^", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^_-b^", byteSetToCharacterClass(bs));
  bs.reset();

  bs['A'] = bs[']'] = true;
  SCOPE_ASSERT_EQUAL("A\\]", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^A\\]", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = 'A'; i < ']' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("A-\\]", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^A-\\]", byteSetToCharacterClass(bs));
  bs.reset();

  for (uint32 i = ']'; i < 'a' + 1; ++i) bs[i] = true;
  SCOPE_ASSERT_EQUAL("]-a", byteSetToCharacterClass(bs));
  bs.flip();
  SCOPE_ASSERT_EQUAL("^]-a", byteSetToCharacterClass(bs));
  bs.reset();
}
