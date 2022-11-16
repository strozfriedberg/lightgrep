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

#include <catch2/catch_test_macros.hpp>

#include "parser.h"
#include "nfabuilder.h"
#include "parsetree.h"

#include "stest.h"

TEST_CASE("testregexBasicModifiedSearch0") {
  STest fixture("a...b");
  fixture.search("abababbb", 0);
  const std::vector<SearchHit> expected {
    {2, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch1") {
  STest fixture("XXXXXX");
  fixture.search("..XXXXXX", 0);
  const std::vector<SearchHit> expected {
    {2, 8, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch2") {
  STest fixture("\\)");
  fixture.search("()", 0);
  const std::vector<SearchHit> expected {
    {1, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch3") {
  STest fixture("a]");
  fixture.search("a]a", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch4") {
  STest fixture("}");
  fixture.search("}", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch5") {
  STest fixture("\\}");
  fixture.search("}", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch6") {
  STest fixture("\\]");
  fixture.search("]", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch7") {
  STest fixture("]");
  fixture.search("]", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch8") {
  STest fixture("{");
  fixture.search("{", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch9") {
  STest fixture("}");
  fixture.search("}", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch10") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(..)*(...)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch11") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(..)*(...)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch12") {
  STest fixture("(ab|a)(bc|c)");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch13") {
  STest fixture("(ab)c|abc");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch14") {
  STest fixture("a{0}b");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    {1, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch15") {
  STest fixture("(a*)(b?)(b+)b{3}");
  fixture.search("aaabbbbbbb", 0);
  const std::vector<SearchHit> expected {
    {0, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch16") {
  STest fixture("(a*)(b{0,1})(b{1,})b{3}");
  fixture.search("aaabbbbbbb", 0);
  const std::vector<SearchHit> expected {
    {0, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

/*
TEST_CASE("testregexBasicModifiedSearch17") {
  STest fixture("a{9876543210}");
  fixture.search("NULL", 0);
  REQUIRE(0u == fixture.Hits.size());
}
*/

TEST_CASE("testregexBasicModifiedSearch18") {
  STest fixture("((a|a)|a)");
  fixture.search("a", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch19") {
  STest fixture("(a*)(a|aa)");
  fixture.search("aaaa", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch20") {
  STest fixture("a*(a.|aa)");
  fixture.search("aaaa", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch21") {
  STest fixture("a(b)|c(d)|a(e)f");
  fixture.search("aef", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch22") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a|b)?.*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch23") {
  STest fixture("(a|b)c|a(b|c)");
  fixture.search("ac", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch24") {
  STest fixture("(a|b)c|a(b|c)");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch25") {
  STest fixture("(a|b)*c|(a|ab)*c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch26") {
  STest fixture("(a|b)*c|(a|ab)*c");
  fixture.search("xc", 0);
  const std::vector<SearchHit> expected {
    {1, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch27") {
  STest fixture("(.a|.b).*|.*(.a|.b)");
  fixture.search("xa", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch28") {
  STest fixture("a?(ab|ba)ab");
  fixture.search("abab", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch29") {
  STest fixture("a?(ac{0}b|ba)ab");
  fixture.search("abab", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch30") {
  STest fixture("ab|abab");
  fixture.search("abbabab", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
    {3, 5, 0},
    {5, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch31") {
  STest fixture("aba|bab|bba");
  fixture.search("baaabbbaba", 0);
  const std::vector<SearchHit> expected {
    {5, 8, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch32") {
  STest fixture("aba|bab");
  fixture.search("baaabbbaba", 0);
  const std::vector<SearchHit> expected {
    {6, 9, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch33") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(aa|aaa)*|(a|aaaaa)", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch34") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a.|.a.)*|(a|.a...)", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch35") {
  STest fixture("ab|a");
  fixture.search("xabc", 0);
  const std::vector<SearchHit> expected {
    {1, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch36") {
  STest fixture("ab|a");
  fixture.search("xxabc", 0);
  const std::vector<SearchHit> expected {
    {2, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch37") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(Ab|cD)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch38") {
  STest fixture("[^\\-]");
  fixture.search("--a", 0);
  const std::vector<SearchHit> expected {
    {2, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch39") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"[a\\-]*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch40") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"[a-m\\-]*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch41") {
  STest fixture(":::1:::0:|:::1:1:0:");
  fixture.search(":::0:::1:::1:::0:", 0);
  const std::vector<SearchHit> expected {
    {8, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch42") {
  STest fixture(":::1:::0:|:::1:1:1:");
  fixture.search(":::0:::1:::1:::0:", 0);
  const std::vector<SearchHit> expected {
    {8, 17, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

/*
TEST_CASE("testregexBasicModifiedSearch43") {
  STest fixture("[[:upper:]]");
  fixture.search("A", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch44") {
  STest fixture("[[:lower:]]+");
  fixture.search("`az{", 0);
  const std::vector<SearchHit> expected {
    {1, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch45") {
  STest fixture("[[:upper:]]+");
  fixture.search("@AZ[", 0);
  const std::vector<SearchHit> expected {
    {1, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
*/

/*
TEST_CASE("testregexBasicModifiedSearch46") {
  STest fixture("[[-]]");
  fixture.search("[[-]]", 0);
  const std::vector<SearchHit> expected {
    {2, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
*/

/*
TEST_CASE("testregexBasicModifiedSearch47") {
  STest fixture("[[.NIL.]]");
  fixture.search("NULL", 0);
  REQUIRE(0u == fixture.Hits.size());
}

TEST_CASE("testregexBasicModifiedSearch48") {
  STest fixture("[[=aleph=]]");
  fixture.search("NULL", 0);
  REQUIRE(0u == fixture.Hits.size());
}
*/

TEST_CASE("testregexBasicModifiedSearch49") {
  STest fixture("\\n");
  fixture.search("\\n", 0);
  REQUIRE(0u == fixture.Hits.size());
}

TEST_CASE("testregexBasicModifiedSearch50") {
  STest fixture("\\n");
  fixture.search("\\n", 0);
  REQUIRE(0u == fixture.Hits.size());
}

TEST_CASE("testregexBasicModifiedSearch51") {
  STest fixture("[^a]");
  fixture.search("\\n", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
    {1, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch52") {
  STest fixture("\\na");
  fixture.search("\\na", 0);
  REQUIRE(0u == fixture.Hits.size());
}

TEST_CASE("testregexBasicModifiedSearch53") {
  STest fixture("(a)(b)(c)");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch54") {
  STest fixture("xxx");
  fixture.search("xxx", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch55") {
  STest fixture("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?");
  fixture.search("feb 6,", 0);
  const std::vector<SearchHit> expected {
    {0, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch56") {
  STest fixture("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?");
  fixture.search("2/7", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch57") {
  STest fixture("((([Ff]eb[^ ]* *|0*2/|\\* */?)0*[6-7]))([^0-9])?");
  fixture.search("feb 1,Feb 6", 0);
  const std::vector<SearchHit> expected {
    {6, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch58") {
  STest fixture("((((((((((((((((((((((((((((((x))))))))))))))))))))))))))))))");
  fixture.search("x", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch59") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"((((((((((((((((((((((((((((((x))))))))))))))))))))))))))))))*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch60") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"a?(ab|ba)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch61") {
  STest fixture("abaa|abbaa|abbbaa|abbbbaa");
  fixture.search("ababbabbbabbbabbbbabbbbaa", 0);
  const std::vector<SearchHit> expected {
    {18, 25, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch62") {
  STest fixture("abaa|abbaa|abbbaa|abbbbaa");
  fixture.search("ababbabbbabbbabbbbabaa", 0);
  const std::vector<SearchHit> expected {
    {18, 22, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch63") {
  STest fixture("aaac|aabc|abac|abbc|baac|babc|bbac|bbbc");
  fixture.search("baaabbbabac", 0);
  const std::vector<SearchHit> expected {
    {7, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch64") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({".*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch65") {
  STest fixture("aaaa|bbbb|cccc|ddddd|eeeeee|fffffff|gggg|hhhh|iiiii|jjjjj|kkkkk|llll");
  fixture.search("XaaaXbbbXcccXdddXeeeXfffXgggXhhhXiiiXjjjXkkkXlllXcbaXaaaa", 0);
  const std::vector<SearchHit> expected {
    {53, 57, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch66") {
  STest fixture("aaaa\\nbbbb\\ncccc\\nddddd\\neeeeee\\nfffffff\\ngggg\\nhhhh\\niiiii\\njjjjj\\nkkkkk\\nllll");
  fixture.search("XaaaXbbbXcccXdddXeeeXfffXgggXhhhXiiiXjjjXkkkXlllXcbaXaaaa", 0);
  REQUIRE(0u == fixture.Hits.size());
}

TEST_CASE("testregexBasicModifiedSearch67") {
  STest fixture("a*a*a*a*a*b");
  fixture.search("aaaaaaaaab", 0);
  const std::vector<SearchHit> expected {
    {0, 10, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch68") {
  STest fixture("abc");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch69") {
  STest fixture("abc");
  fixture.search("xabcy", 0);
  const std::vector<SearchHit> expected {
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch70") {
  STest fixture("abc");
  fixture.search("ababc", 0);
  const std::vector<SearchHit> expected {
    {2, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch71") {
  STest fixture("ab*c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch72") {
  STest fixture("ab*bc");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch73") {
  STest fixture("ab*bc");
  fixture.search("abbc", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch74") {
  STest fixture("ab*bc");
  fixture.search("abbbbc", 0);
  const std::vector<SearchHit> expected {
    {0, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch75") {
  STest fixture("ab+bc");
  fixture.search("abbc", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch76") {
  STest fixture("ab+bc");
  fixture.search("abbbbc", 0);
  const std::vector<SearchHit> expected {
    {0, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch77") {
  STest fixture("ab?bc");
  fixture.search("abbc", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch78") {
  STest fixture("ab?bc");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch79") {
  STest fixture("ab?c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch80") {
  STest fixture("a.c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch81") {
  STest fixture("a.c");
  fixture.search("axc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch82") {
  STest fixture("a.*c");
  fixture.search("axyzc", 0);
  const std::vector<SearchHit> expected {
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch83") {
  STest fixture("a[bc]d");
  fixture.search("abd", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch84") {
  STest fixture("a[b-d]e");
  fixture.search("ace", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch85") {
  STest fixture("a[b-d]");
  fixture.search("aac", 0);
  const std::vector<SearchHit> expected {
    {1, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch86") {
  STest fixture("a[\\-b]");
  fixture.search("a-", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch87") {
  STest fixture("a[b\\-]");
  fixture.search("a-", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch88") {
  STest fixture("a]");
  fixture.search("a]", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch89") {
  STest fixture("a[\\]]b");
  fixture.search("a]b", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch90") {
  STest fixture("a[^bc]d");
  fixture.search("aed", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch91") {
  STest fixture("a[^\\-b]c");
  fixture.search("adc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch92") {
  STest fixture("a[^\\]b]c");
  fixture.search("adc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch93") {
  STest fixture("ab|cd");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch94") {
  STest fixture("ab|cd");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
    {2, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch95") {
  STest fixture("a\\(b");
  fixture.search("a(b", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch96") {
  STest fixture("a\\(*b");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch97") {
  STest fixture("a\\(*b");
  fixture.search("a((b", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch98") {
  STest fixture("((a))");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch99") {
  STest fixture("(a)b(c)");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch100") {
  STest fixture("a+b+c");
  fixture.search("aabbabc", 0);
  const std::vector<SearchHit> expected {
    {4, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch101") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"a*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch102") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a*)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch103") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a*)+", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch104") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a*|b)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch105") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a+|b)*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch106") {
  STest fixture("(a+|b)+");
  fixture.search("ab", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch107") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"(a+|b)?", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch108") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"[^ab]*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch109") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"a*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch110") {
  STest fixture("([abc])*d");
  fixture.search("abbbcd", 0);
  const std::vector<SearchHit> expected {
    {0, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch111") {
  STest fixture("([abc])*bcd");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch112") {
  STest fixture("a|b|c|d|e");
  fixture.search("e", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch113") {
  STest fixture("(a|b|c|d|e)f");
  fixture.search("ef", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch114") {
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(bisonParse({"((a*|b))*", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}

TEST_CASE("testregexBasicModifiedSearch115") {
  STest fixture("abcd*efg");
  fixture.search("abcdefg", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch116") {
  STest fixture("ab*");
  fixture.search("xabyabbbz", 0);
  const std::vector<SearchHit> expected {
    {1, 3, 0},
    {4, 8, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch117") {
  STest fixture("ab*");
  fixture.search("xayabbbz", 0);
  const std::vector<SearchHit> expected {
    {1, 2, 0},
    {3, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch118") {
  STest fixture("(ab|cd)e");
  fixture.search("abcde", 0);
  const std::vector<SearchHit> expected {
    {2, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch119") {
  STest fixture("[abhgefdc]ij");
  fixture.search("hij", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch120") {
  STest fixture("(a|b)c*d");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {1, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch121") {
  STest fixture("(ab|ab*)bc");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch122") {
  STest fixture("a([bc]*)c*");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch123") {
  STest fixture("a([bc]*)(c*d)");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch124") {
  STest fixture("a([bc]+)(c*d)");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch125") {
  STest fixture("a([bc]*)(c+d)");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch126") {
  STest fixture("a[bcd]*dcdcde");
  fixture.search("adcdcde", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch127") {
  STest fixture("(ab|a)b*c");
  fixture.search("abc", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch128") {
  STest fixture("((a)(b)c)(d)");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch129") {
  STest fixture("[A-Za-z_][A-Za-z0-9_]*");
  fixture.search("alpha", 0);
  const std::vector<SearchHit> expected {
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch130") {
  STest fixture("a(bc+|b[eh])g|.h");
  fixture.search("abh", 0);
  const std::vector<SearchHit> expected {
    {1, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch131") {
  STest fixture("(bc+d|ef*g.|h?i(j|k))");
  fixture.search("effgz", 0);
  const std::vector<SearchHit> expected {
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch132") {
  STest fixture("(bc+d|ef*g.|h?i(j|k))");
  fixture.search("ij", 0);
  const std::vector<SearchHit> expected {
    {0, 2, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch133") {
  STest fixture("(bc+d|ef*g.|h?i(j|k))");
  fixture.search("reffgz", 0);
  const std::vector<SearchHit> expected {
    {1, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch134") {
  STest fixture("(((((((((a)))))))))");
  fixture.search("a", 0);
  const std::vector<SearchHit> expected {
    {0, 1, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch135") {
  STest fixture("multiple words");
  fixture.search("multiple words yeah", 0);
  const std::vector<SearchHit> expected {
    {0, 14, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch136") {
  STest fixture("(.*)c(.*)");
  fixture.search("abcde", 0);
  const std::vector<SearchHit> expected {
    {0, 5, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch137") {
  STest fixture("abcd");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch138") {
  STest fixture("a(bc)d");
  fixture.search("abcd", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch139") {
  STest fixture("a[-]?c");
  fixture.search("ac", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch140") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Qaddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch141") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Mo'ammar Gadhafi", 0);
  const std::vector<SearchHit> expected {
    {0, 16, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch142") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Kaddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch143") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Qadhafi", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch144") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Gadafi", 0);
  const std::vector<SearchHit> expected {
    {0, 14, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch145") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Mu'ammar Qadafi", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch146") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Moamar Gaddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 14, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch147") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Mu'ammar Qadhdhafi", 0);
  const std::vector<SearchHit> expected {
    {0, 18, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch148") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Khaddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 16, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch149") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Ghaddafy", 0);
  const std::vector<SearchHit> expected {
    {0, 16, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch150") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Ghadafi", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch151") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Ghaddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 16, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch152") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muamar Kaddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 14, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch153") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Quathafi", 0);
  const std::vector<SearchHit> expected {
    {0, 16, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch154") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Muammar Gheddafi", 0);
  const std::vector<SearchHit> expected {
    {0, 16, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch155") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Moammar Khadafy", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch156") {
  STest fixture("M[ou]'?am+[ae]r .*([AEae]l[\\- ])?[GKQ]h?[aeu]+([dtz][dhz]?)+af[iy]");
  fixture.search("Moammar Qudhafi", 0);
  const std::vector<SearchHit> expected {
    {0, 15, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch157") {
  STest fixture("a+(b|c)*d+");
  fixture.search("aabcdd", 0);
  const std::vector<SearchHit> expected {
    {0, 6, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch158") {
  STest fixture(".+");
  fixture.search("vivi", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch159") {
  STest fixture("(.+)");
  fixture.search("vivi", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch160") {
  STest fixture("([^!.]+).att.com!(.+)");
  fixture.search("gryphon.att.com!eby", 0);
  const std::vector<SearchHit> expected {
    {0, 19, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch161") {
  STest fixture("([^!]+!)?([^!]+)");
  fixture.search("bas", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch162") {
  STest fixture("([^!]+!)?([^!]+)");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch163") {
  STest fixture("([^!]+!)?([^!]+)");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch164") {
  STest fixture(".+!([^!]+!)([^!]+)");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch165") {
  STest fixture("((foo)|(bar))!bas");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch166") {
  STest fixture("((foo)|(bar))!bas");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {4, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch167") {
  STest fixture("((foo)|(bar))!bas");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch168") {
  STest fixture("((foo)|bar)!bas");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch169") {
  STest fixture("((foo)|bar)!bas");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {4, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch170") {
  STest fixture("((foo)|bar)!bas");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch171") {
  STest fixture("(foo|(bar))!bas");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch172") {
  STest fixture("(foo|(bar))!bas");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {4, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch173") {
  STest fixture("(foo|(bar))!bas");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch174") {
  STest fixture("(foo|bar)!bas");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch175") {
  STest fixture("(foo|bar)!bas");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {4, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch176") {
  STest fixture("(foo|bar)!bas");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch177") {
  STest fixture("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
    {8, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch178") {
  STest fixture("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)");
  fixture.search("bas", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch179") {
  STest fixture("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch180") {
  STest fixture("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
    {8, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch181") {
  STest fixture("([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+)");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch182") {
  STest fixture("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))");
  fixture.search("bas", 0);
  const std::vector<SearchHit> expected {
    {0, 3, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch183") {
  STest fixture("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))");
  fixture.search("bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch184") {
  STest fixture("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))");
  fixture.search("foo!bar!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
    {8, 11, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch185") {
  STest fixture("(([^!]+!)?([^!]+)|.+!([^!]+!)([^!]+))");
  fixture.search("foo!bas", 0);
  const std::vector<SearchHit> expected {
    {0, 7, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch186") {
  STest fixture(".*(/XXX).*");
  fixture.search("/XXX", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch187") {
  STest fixture(".*(\\\\XXX).*");
  fixture.search("\\XXX", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch188") {
  STest fixture("\\\\XXX");
  fixture.search("\\XXX", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch189") {
  STest fixture(".*(/000).*");
  fixture.search("/000", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch190") {
  STest fixture(".*(\\\\000).*");
  fixture.search("\\000", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}

TEST_CASE("testregexBasicModifiedSearch191") {
  STest fixture("\\\\000");
  fixture.search("\\000", 0);
  const std::vector<SearchHit> expected {
    {0, 4, 0},
  };
  REQUIRE(expected == fixture.Hits);
}
