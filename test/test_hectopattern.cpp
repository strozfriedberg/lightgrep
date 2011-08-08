#include <scope/test.h>

#include <algorithm>

#include "stest.h"

SCOPE_FIXTURE_CTOR(hundredPatternSearch, STest, STest(100, (const char *[]){
  "a|a??.|.|a?",
  "a?|aa|a??a+?",
  "a*(a)|a*?|.+",
  "a??a+.+?(a)",
  "a+(.).*?a.",
  "a??|.|.|aa|aa",
  "a+?|.?aa|a*",
  "a|a|.|.|.+.+",
  "a?|.?|.??.|a",
  "a+a+?|.+|.*?",
  "a+?|.+..|.a",
  "a?a+|a?|.|.",
  "a|a|aa.*|a+?",
  "a*a?a??|.+",
  "a+|a|.|.|(a)",
  "aa|.?.+?|.+?",
  "aa+?a*(a)",
  "a?|a|.a|a.",
  "(a)|(.)a|.a*?",
  "a*?|a*?|a*?|.|a",
  "a|.+?|a|a.+",
  "a*.aa*?|.+",
  "a??|(.).*.+?",
  "a+?|.?|.?a*",
  "a?.*..|a?",
  "a*?|.+(.)",
  "a*|aa|aa|.a",
  "a+?...a|.+",
  "a|.(.)aa|.+?",
  "a+?|a|.|a|.a.",
  "a?.?|.|.|a*",
  "a|a.??(a.)",
  "a.|(a)|(.*?)",
  "a.aaa??a.",
  "a??.*.??a+?",
  "a.(.)(a|.)",
  "a+.?|.|.(.)",
  "a*?a??a*?|a?",
  "a*?a.|.?a?",
  "a+aa..|a+",
  "a?|a+?|a|.(.)",
  "a|a.+|a*?a|a",
  "a+?|a|aa??|(.)",
  "a|.??a*|.a",
  "a??|.??..|.*",
  "a+?|a?.?a.",
  "aa(a).|a|.",
  "a|.|.+a|.",
  "aa.*.a.+",
  "a*.+?|.*|.*",
  "a+?a?|a|a|.*?",
  "aaaa|a|.|a|.",
  "aaaa*.a",
  "a?|a+?|a|a|aa",
  "aa*|.*|.+?",
  "a*.+?(a)*",
  "a+?(a)|a.a?",
  "a.a?a+(a)",
  "a+|(a)..|.",
  "a+?|a*?a|.|a",
  "a+?|a|.|a|(a)",
  "(a)|(a)|.a*?",
  "a|aa?a|.|.*?",
  "a|a|(a).*a+?",
  "a?|..|a.*?",
  "a+a+?|.|.|a*?",
  "a?|.+|(.)+",
  "a+..|.*|a*?",
  "a*?|.|a|a+?|.|.",
  "a*?a*?..|.",
  "a??|a*|a.+?",
  "a?a+.|.(a)",
  "a+.+?|a*?aa",
  "a?.*aa(.)",
  "a*?|a*|a.|a|a",
  "a?|(.).?|a+?",
  "a|.|.*|.aa*?",
  "a|a|.*|.?a??",
  "a*?.*|aa|a",
  "a+a|a.|.|a|.",
  "a.a|..|(.)",
  "a|.aaa|.a+",
  "a*?|a?..|(a)",
  "a*a|.|a*?|.*?",
  "a*?.+?.?(a)",
  "a|.(.)..",
  "a|..+|.*.a",
  "a+|.|a*?|.|a",
  "a|a(a).a|.*?",
  "a*?|a*.|.|.+",
  "a?|.?.*?.",
  "a??a.|a?aa",
  "a|..|..|a|(a)",
  "a*?.|.|.?.|.",
  "a??a*|a+|a+",
  "a..a|..|a??",
  "a??|a.|.??|.|a",
  "a??a?a*.?",
  "a.|.*a*?|.|a",
  "a*|..|.|..*?"
})) {
  const byte* text = (const byte*) "aaabaacabbabcacbaccbbbcbccca";
  fixture.search(text, text + 28, 0, fixture);
  std::vector<SearchHit>& actual = fixture.Hits;
  SCOPE_ASSERT_EQUAL(661, actual.size());

  std::vector<SearchHit> expected;
  expected.reserve(661);
  expected.push_back(SearchHit(0, 1, 7));
  expected.push_back(SearchHit(0, 1, 10));
  expected.push_back(SearchHit(0, 1, 12));
  expected.push_back(SearchHit(0, 1, 18));
  expected.push_back(SearchHit(0, 1, 20));
  expected.push_back(SearchHit(0, 1, 28));
  expected.push_back(SearchHit(0, 1, 29));
  expected.push_back(SearchHit(0, 1, 31));
  expected.push_back(SearchHit(0, 1, 41));
  expected.push_back(SearchHit(0, 1, 42));
  expected.push_back(SearchHit(0, 1, 45));
  expected.push_back(SearchHit(0, 1, 47));
  expected.push_back(SearchHit(0, 1, 51));
  expected.push_back(SearchHit(0, 1, 59));
  expected.push_back(SearchHit(0, 1, 60));
  expected.push_back(SearchHit(0, 1, 61));
  expected.push_back(SearchHit(0, 1, 63));
  expected.push_back(SearchHit(0, 1, 81));
  expected.push_back(SearchHit(0, 1, 85));
  expected.push_back(SearchHit(0, 1, 86));
  expected.push_back(SearchHit(0, 1, 92));
  expected.push_back(SearchHit(0, 1, 93));
  expected.push_back(SearchHit(0, 2, 15));
  expected.push_back(SearchHit(0, 2, 56));
  expected.push_back(SearchHit(0, 2, 69));
  expected.push_back(SearchHit(0, 2, 91));
  expected.push_back(SearchHit(0, 3, 14));
  expected.push_back(SearchHit(0, 3, 16));
  expected.push_back(SearchHit(0, 3, 58));
  expected.push_back(SearchHit(0, 3, 79));
  expected.push_back(SearchHit(0, 3, 80));
  expected.push_back(SearchHit(0, 3, 84));
  expected.push_back(SearchHit(0, 4, 35));
  expected.push_back(SearchHit(0, 4, 36));
  expected.push_back(SearchHit(0, 4, 46));
  expected.push_back(SearchHit(0, 4, 71));
  expected.push_back(SearchHit(0, 4, 72));
  expected.push_back(SearchHit(0, 5, 3));
  expected.push_back(SearchHit(0, 5, 21));
  expected.push_back(SearchHit(0, 5, 27));
  expected.push_back(SearchHit(0, 5, 39));
  expected.push_back(SearchHit(0, 5, 52));
  expected.push_back(SearchHit(0, 6, 4));
  expected.push_back(SearchHit(0, 6, 55));
  expected.push_back(SearchHit(0, 7, 73));
  expected.push_back(SearchHit(0, 28, 34));
  expected.push_back(SearchHit(0, 28, 48));
  expected.push_back(SearchHit(1, 1, 7));
  expected.push_back(SearchHit(1, 1, 10));
  expected.push_back(SearchHit(1, 1, 12));
  expected.push_back(SearchHit(1, 1, 18));
  expected.push_back(SearchHit(1, 1, 20));
  expected.push_back(SearchHit(1, 1, 28));
  expected.push_back(SearchHit(1, 1, 29));
  expected.push_back(SearchHit(1, 1, 31));
  expected.push_back(SearchHit(1, 1, 41));
  expected.push_back(SearchHit(1, 1, 42));
  expected.push_back(SearchHit(1, 1, 45));
  expected.push_back(SearchHit(1, 1, 47));
  expected.push_back(SearchHit(1, 1, 51));
  expected.push_back(SearchHit(1, 1, 59));
  expected.push_back(SearchHit(1, 1, 60));
  expected.push_back(SearchHit(1, 1, 61));
  expected.push_back(SearchHit(1, 1, 63));
  expected.push_back(SearchHit(1, 1, 81));
  expected.push_back(SearchHit(1, 1, 85));
  expected.push_back(SearchHit(1, 1, 86));
  expected.push_back(SearchHit(1, 1, 92));
  expected.push_back(SearchHit(1, 1, 93));
  expected.push_back(SearchHit(2, 1, 7));
  expected.push_back(SearchHit(2, 1, 10));
  expected.push_back(SearchHit(2, 1, 12));
  expected.push_back(SearchHit(2, 1, 18));
  expected.push_back(SearchHit(2, 1, 20));
  expected.push_back(SearchHit(2, 1, 28));
  expected.push_back(SearchHit(2, 1, 29));
  expected.push_back(SearchHit(2, 1, 31));
  expected.push_back(SearchHit(2, 1, 41));
  expected.push_back(SearchHit(2, 1, 42));
  expected.push_back(SearchHit(2, 1, 45));
  expected.push_back(SearchHit(2, 1, 47));
  expected.push_back(SearchHit(2, 1, 51));
  expected.push_back(SearchHit(2, 1, 59));
  expected.push_back(SearchHit(2, 1, 60));
  expected.push_back(SearchHit(2, 1, 61));
  expected.push_back(SearchHit(2, 1, 63));
  expected.push_back(SearchHit(2, 1, 81));
  expected.push_back(SearchHit(2, 1, 85));
  expected.push_back(SearchHit(2, 1, 86));
  expected.push_back(SearchHit(2, 1, 92));
  expected.push_back(SearchHit(2, 1, 93));
  expected.push_back(SearchHit(2, 2, 15));
  expected.push_back(SearchHit(2, 2, 69));
  expected.push_back(SearchHit(2, 2, 91));
  expected.push_back(SearchHit(2, 3, 56));
  expected.push_back(SearchHit(2, 4, 57));
  expected.push_back(SearchHit(3, 1, 7));
  expected.push_back(SearchHit(3, 1, 14));
  expected.push_back(SearchHit(3, 1, 20));
  expected.push_back(SearchHit(3, 1, 28));
  expected.push_back(SearchHit(3, 1, 29));
  expected.push_back(SearchHit(3, 1, 42));
  expected.push_back(SearchHit(3, 1, 47));
  expected.push_back(SearchHit(3, 1, 51));
  expected.push_back(SearchHit(3, 1, 58));
  expected.push_back(SearchHit(3, 1, 59));
  expected.push_back(SearchHit(3, 1, 60));
  expected.push_back(SearchHit(3, 1, 61));
  expected.push_back(SearchHit(3, 1, 79));
  expected.push_back(SearchHit(3, 1, 93));
  expected.push_back(SearchHit(3, 2, 18));
  expected.push_back(SearchHit(3, 2, 80));
  expected.push_back(SearchHit(3, 2, 92));
  expected.push_back(SearchHit(3, 3, 45));
  expected.push_back(SearchHit(3, 3, 81));
  expected.push_back(SearchHit(3, 3, 84));
  expected.push_back(SearchHit(3, 4, 85));
  expected.push_back(SearchHit(3, 25, 10));
  expected.push_back(SearchHit(3, 25, 86));
  expected.push_back(SearchHit(4, 1, 7));
  expected.push_back(SearchHit(4, 1, 12));
  expected.push_back(SearchHit(4, 1, 20));
  expected.push_back(SearchHit(4, 1, 28));
  expected.push_back(SearchHit(4, 1, 29));
  expected.push_back(SearchHit(4, 1, 31));
  expected.push_back(SearchHit(4, 1, 41));
  expected.push_back(SearchHit(4, 1, 42));
  expected.push_back(SearchHit(4, 1, 46));
  expected.push_back(SearchHit(4, 1, 47));
  expected.push_back(SearchHit(4, 1, 51));
  expected.push_back(SearchHit(4, 1, 59));
  expected.push_back(SearchHit(4, 1, 60));
  expected.push_back(SearchHit(4, 1, 61));
  expected.push_back(SearchHit(4, 1, 63));
  expected.push_back(SearchHit(4, 1, 93));
  expected.push_back(SearchHit(4, 2, 14));
  expected.push_back(SearchHit(4, 2, 15));
  expected.push_back(SearchHit(4, 2, 58));
  expected.push_back(SearchHit(4, 2, 69));
  expected.push_back(SearchHit(4, 2, 79));
  expected.push_back(SearchHit(4, 2, 91));
  expected.push_back(SearchHit(4, 3, 36));
  expected.push_back(SearchHit(4, 3, 71));
  expected.push_back(SearchHit(4, 3, 72));
  expected.push_back(SearchHit(4, 4, 35));
  expected.push_back(SearchHit(5, 1, 7));
  expected.push_back(SearchHit(5, 1, 12));
  expected.push_back(SearchHit(5, 1, 18));
  expected.push_back(SearchHit(5, 1, 20));
  expected.push_back(SearchHit(5, 1, 28));
  expected.push_back(SearchHit(5, 1, 29));
  expected.push_back(SearchHit(5, 1, 31));
  expected.push_back(SearchHit(5, 1, 39));
  expected.push_back(SearchHit(5, 1, 41));
  expected.push_back(SearchHit(5, 1, 42));
  expected.push_back(SearchHit(5, 1, 46));
  expected.push_back(SearchHit(5, 1, 47));
  expected.push_back(SearchHit(5, 1, 51));
  expected.push_back(SearchHit(5, 1, 59));
  expected.push_back(SearchHit(5, 1, 60));
  expected.push_back(SearchHit(5, 1, 61));
  expected.push_back(SearchHit(5, 1, 63));
  expected.push_back(SearchHit(5, 1, 92));
  expected.push_back(SearchHit(5, 1, 93));
  expected.push_back(SearchHit(5, 3, 3));
  expected.push_back(SearchHit(5, 3, 21));
  expected.push_back(SearchHit(5, 3, 56));
  expected.push_back(SearchHit(5, 3, 80));
  expected.push_back(SearchHit(5, 23, 27));
  expected.push_back(SearchHit(6, 1, 7));
  expected.push_back(SearchHit(6, 1, 14));
  expected.push_back(SearchHit(6, 1, 20));
  expected.push_back(SearchHit(6, 1, 28));
  expected.push_back(SearchHit(6, 1, 29));
  expected.push_back(SearchHit(6, 1, 42));
  expected.push_back(SearchHit(6, 1, 46));
  expected.push_back(SearchHit(6, 1, 47));
  expected.push_back(SearchHit(6, 1, 51));
  expected.push_back(SearchHit(6, 1, 58));
  expected.push_back(SearchHit(6, 1, 59));
  expected.push_back(SearchHit(6, 1, 60));
  expected.push_back(SearchHit(6, 1, 61));
  expected.push_back(SearchHit(6, 1, 79));
  expected.push_back(SearchHit(6, 1, 93));
  expected.push_back(SearchHit(6, 2, 15));
  expected.push_back(SearchHit(6, 2, 18));
  expected.push_back(SearchHit(6, 2, 55));
  expected.push_back(SearchHit(6, 2, 69));
  expected.push_back(SearchHit(6, 2, 81));
  expected.push_back(SearchHit(6, 2, 84));
  expected.push_back(SearchHit(6, 2, 92));
  expected.push_back(SearchHit(6, 3, 45));
  expected.push_back(SearchHit(7, 1, 7));
  expected.push_back(SearchHit(7, 1, 12));
  expected.push_back(SearchHit(7, 1, 14));
  expected.push_back(SearchHit(7, 1, 20));
  expected.push_back(SearchHit(7, 1, 28));
  expected.push_back(SearchHit(7, 1, 29));
  expected.push_back(SearchHit(7, 1, 31));
  expected.push_back(SearchHit(7, 1, 39));
  expected.push_back(SearchHit(7, 1, 41));
  expected.push_back(SearchHit(7, 1, 42));
  expected.push_back(SearchHit(7, 1, 46));
  expected.push_back(SearchHit(7, 1, 47));
  expected.push_back(SearchHit(7, 1, 51));
  expected.push_back(SearchHit(7, 1, 58));
  expected.push_back(SearchHit(7, 1, 59));
  expected.push_back(SearchHit(7, 1, 60));
  expected.push_back(SearchHit(7, 1, 61));
  expected.push_back(SearchHit(7, 1, 63));
  expected.push_back(SearchHit(7, 1, 85));
  expected.push_back(SearchHit(7, 1, 93));
  expected.push_back(SearchHit(7, 2, 36));
  expected.push_back(SearchHit(7, 2, 71));
  expected.push_back(SearchHit(7, 2, 72));
  expected.push_back(SearchHit(7, 2, 79));
  expected.push_back(SearchHit(7, 2, 91));
  expected.push_back(SearchHit(7, 5, 4));
  expected.push_back(SearchHit(8, 1, 7));
  expected.push_back(SearchHit(8, 1, 14));
  expected.push_back(SearchHit(8, 1, 18));
  expected.push_back(SearchHit(8, 1, 20));
  expected.push_back(SearchHit(8, 1, 28));
  expected.push_back(SearchHit(8, 1, 29));
  expected.push_back(SearchHit(8, 1, 42));
  expected.push_back(SearchHit(8, 1, 46));
  expected.push_back(SearchHit(8, 1, 47));
  expected.push_back(SearchHit(8, 1, 51));
  expected.push_back(SearchHit(8, 1, 55));
  expected.push_back(SearchHit(8, 1, 58));
  expected.push_back(SearchHit(8, 1, 59));
  expected.push_back(SearchHit(8, 1, 60));
  expected.push_back(SearchHit(8, 1, 61));
  expected.push_back(SearchHit(8, 1, 93));
  expected.push_back(SearchHit(8, 2, 15));
  expected.push_back(SearchHit(8, 2, 69));
  expected.push_back(SearchHit(8, 2, 80));
  expected.push_back(SearchHit(8, 2, 92));
  expected.push_back(SearchHit(8, 3, 84));
  expected.push_back(SearchHit(8, 4, 85));
  expected.push_back(SearchHit(8, 20, 21));
  expected.push_back(SearchHit(9, 1, 7));
  expected.push_back(SearchHit(9, 1, 14));
  expected.push_back(SearchHit(9, 1, 20));
  expected.push_back(SearchHit(9, 1, 28));
  expected.push_back(SearchHit(9, 1, 29));
  expected.push_back(SearchHit(9, 1, 36));
  expected.push_back(SearchHit(9, 1, 42));
  expected.push_back(SearchHit(9, 1, 46));
  expected.push_back(SearchHit(9, 1, 47));
  expected.push_back(SearchHit(9, 1, 51));
  expected.push_back(SearchHit(9, 1, 58));
  expected.push_back(SearchHit(9, 1, 59));
  expected.push_back(SearchHit(9, 1, 60));
  expected.push_back(SearchHit(9, 1, 61));
  expected.push_back(SearchHit(9, 1, 79));
  expected.push_back(SearchHit(9, 1, 93));
  expected.push_back(SearchHit(9, 2, 18));
  expected.push_back(SearchHit(9, 2, 55));
  expected.push_back(SearchHit(9, 2, 71));
  expected.push_back(SearchHit(9, 2, 81));
  expected.push_back(SearchHit(9, 3, 45));
  expected.push_back(SearchHit(10, 1, 7));
  expected.push_back(SearchHit(10, 1, 12));
  expected.push_back(SearchHit(10, 1, 14));
  expected.push_back(SearchHit(10, 1, 20));
  expected.push_back(SearchHit(10, 1, 28));
  expected.push_back(SearchHit(10, 1, 29));
  expected.push_back(SearchHit(10, 1, 31));
  expected.push_back(SearchHit(10, 1, 39));
  expected.push_back(SearchHit(10, 1, 41));
  expected.push_back(SearchHit(10, 1, 42));
  expected.push_back(SearchHit(10, 1, 46));
  expected.push_back(SearchHit(10, 1, 47));
  expected.push_back(SearchHit(10, 1, 51));
  expected.push_back(SearchHit(10, 1, 58));
  expected.push_back(SearchHit(10, 1, 59));
  expected.push_back(SearchHit(10, 1, 60));
  expected.push_back(SearchHit(10, 1, 61));
  expected.push_back(SearchHit(10, 1, 63));
  expected.push_back(SearchHit(10, 1, 92));
  expected.push_back(SearchHit(10, 1, 93));
  expected.push_back(SearchHit(10, 2, 15));
  expected.push_back(SearchHit(10, 2, 36));
  expected.push_back(SearchHit(10, 2, 56));
  expected.push_back(SearchHit(10, 2, 69));
  expected.push_back(SearchHit(10, 2, 72));
  expected.push_back(SearchHit(10, 2, 79));
  expected.push_back(SearchHit(10, 2, 80));
  expected.push_back(SearchHit(10, 2, 91));
  expected.push_back(SearchHit(10, 4, 3));
  expected.push_back(SearchHit(10, 4, 35));
  expected.push_back(SearchHit(11, 1, 7));
  expected.push_back(SearchHit(11, 1, 14));
  expected.push_back(SearchHit(11, 1, 18));
  expected.push_back(SearchHit(11, 1, 20));
  expected.push_back(SearchHit(11, 1, 28));
  expected.push_back(SearchHit(11, 1, 29));
  expected.push_back(SearchHit(11, 1, 42));
  expected.push_back(SearchHit(11, 1, 46));
  expected.push_back(SearchHit(11, 1, 47));
  expected.push_back(SearchHit(11, 1, 51));
  expected.push_back(SearchHit(11, 1, 55));
  expected.push_back(SearchHit(11, 1, 58));
  expected.push_back(SearchHit(11, 1, 59));
  expected.push_back(SearchHit(11, 1, 60));
  expected.push_back(SearchHit(11, 1, 61));
  expected.push_back(SearchHit(11, 1, 93));
  expected.push_back(SearchHit(11, 2, 92));
  expected.push_back(SearchHit(11, 3, 84));
  expected.push_back(SearchHit(12, 1, 7));
  expected.push_back(SearchHit(12, 1, 14));
  expected.push_back(SearchHit(12, 1, 20));
  expected.push_back(SearchHit(12, 1, 28));
  expected.push_back(SearchHit(12, 1, 29));
  expected.push_back(SearchHit(12, 1, 36));
  expected.push_back(SearchHit(12, 1, 42));
  expected.push_back(SearchHit(12, 1, 46));
  expected.push_back(SearchHit(12, 1, 47));
  expected.push_back(SearchHit(12, 1, 51));
  expected.push_back(SearchHit(12, 1, 58));
  expected.push_back(SearchHit(12, 1, 59));
  expected.push_back(SearchHit(12, 1, 60));
  expected.push_back(SearchHit(12, 1, 61));
  expected.push_back(SearchHit(12, 1, 79));
  expected.push_back(SearchHit(12, 1, 93));
  expected.push_back(SearchHit(12, 2, 15));
  expected.push_back(SearchHit(12, 2, 18));
  expected.push_back(SearchHit(12, 2, 55));
  expected.push_back(SearchHit(12, 2, 69));
  expected.push_back(SearchHit(12, 2, 71));
  expected.push_back(SearchHit(12, 2, 80));
  expected.push_back(SearchHit(12, 2, 81));
  expected.push_back(SearchHit(12, 3, 45));
  expected.push_back(SearchHit(12, 4, 85));
  expected.push_back(SearchHit(13, 1, 7));
  expected.push_back(SearchHit(13, 1, 12));
  expected.push_back(SearchHit(13, 1, 14));
  expected.push_back(SearchHit(13, 1, 20));
  expected.push_back(SearchHit(13, 1, 28));
  expected.push_back(SearchHit(13, 1, 29));
  expected.push_back(SearchHit(13, 1, 31));
  expected.push_back(SearchHit(13, 1, 39));
  expected.push_back(SearchHit(13, 1, 41));
  expected.push_back(SearchHit(13, 1, 42));
  expected.push_back(SearchHit(13, 1, 46));
  expected.push_back(SearchHit(13, 1, 47));
  expected.push_back(SearchHit(13, 1, 51));
  expected.push_back(SearchHit(13, 1, 58));
  expected.push_back(SearchHit(13, 1, 59));
  expected.push_back(SearchHit(13, 1, 60));
  expected.push_back(SearchHit(13, 1, 61));
  expected.push_back(SearchHit(13, 1, 63));
  expected.push_back(SearchHit(13, 1, 92));
  expected.push_back(SearchHit(13, 1, 93));
  expected.push_back(SearchHit(13, 2, 36));
  expected.push_back(SearchHit(13, 2, 56));
  expected.push_back(SearchHit(13, 2, 72));
  expected.push_back(SearchHit(13, 2, 79));
  expected.push_back(SearchHit(13, 2, 91));
  expected.push_back(SearchHit(13, 5, 4));
  expected.push_back(SearchHit(14, 1, 7));
  expected.push_back(SearchHit(14, 1, 14));
  expected.push_back(SearchHit(14, 1, 18));
  expected.push_back(SearchHit(14, 1, 20));
  expected.push_back(SearchHit(14, 1, 28));
  expected.push_back(SearchHit(14, 1, 29));
  expected.push_back(SearchHit(14, 1, 42));
  expected.push_back(SearchHit(14, 1, 46));
  expected.push_back(SearchHit(14, 1, 47));
  expected.push_back(SearchHit(14, 1, 51));
  expected.push_back(SearchHit(14, 1, 55));
  expected.push_back(SearchHit(14, 1, 58));
  expected.push_back(SearchHit(14, 1, 59));
  expected.push_back(SearchHit(14, 1, 60));
  expected.push_back(SearchHit(14, 1, 61));
  expected.push_back(SearchHit(14, 1, 93));
  expected.push_back(SearchHit(14, 2, 15));
  expected.push_back(SearchHit(14, 2, 69));
  expected.push_back(SearchHit(14, 2, 80));
  expected.push_back(SearchHit(14, 2, 92));
  expected.push_back(SearchHit(14, 3, 84));
  expected.push_back(SearchHit(15, 1, 7));
  expected.push_back(SearchHit(15, 1, 14));
  expected.push_back(SearchHit(15, 1, 20));
  expected.push_back(SearchHit(15, 1, 28));
  expected.push_back(SearchHit(15, 1, 29));
  expected.push_back(SearchHit(15, 1, 36));
  expected.push_back(SearchHit(15, 1, 42));
  expected.push_back(SearchHit(15, 1, 46));
  expected.push_back(SearchHit(15, 1, 47));
  expected.push_back(SearchHit(15, 1, 51));
  expected.push_back(SearchHit(15, 1, 58));
  expected.push_back(SearchHit(15, 1, 59));
  expected.push_back(SearchHit(15, 1, 60));
  expected.push_back(SearchHit(15, 1, 61));
  expected.push_back(SearchHit(15, 1, 79));
  expected.push_back(SearchHit(15, 1, 93));
  expected.push_back(SearchHit(15, 2, 18));
  expected.push_back(SearchHit(15, 2, 55));
  expected.push_back(SearchHit(15, 2, 71));
  expected.push_back(SearchHit(15, 2, 81));
  expected.push_back(SearchHit(15, 3, 45));
  expected.push_back(SearchHit(16, 1, 7));
  expected.push_back(SearchHit(16, 1, 12));
  expected.push_back(SearchHit(16, 1, 14));
  expected.push_back(SearchHit(16, 1, 20));
  expected.push_back(SearchHit(16, 1, 28));
  expected.push_back(SearchHit(16, 1, 29));
  expected.push_back(SearchHit(16, 1, 31));
  expected.push_back(SearchHit(16, 1, 39));
  expected.push_back(SearchHit(16, 1, 41));
  expected.push_back(SearchHit(16, 1, 42));
  expected.push_back(SearchHit(16, 1, 46));
  expected.push_back(SearchHit(16, 1, 47));
  expected.push_back(SearchHit(16, 1, 51));
  expected.push_back(SearchHit(16, 1, 58));
  expected.push_back(SearchHit(16, 1, 59));
  expected.push_back(SearchHit(16, 1, 60));
  expected.push_back(SearchHit(16, 1, 61));
  expected.push_back(SearchHit(16, 1, 63));
  expected.push_back(SearchHit(16, 1, 85));
  expected.push_back(SearchHit(16, 1, 92));
  expected.push_back(SearchHit(16, 1, 93));
  expected.push_back(SearchHit(16, 2, 15));
  expected.push_back(SearchHit(16, 2, 36));
  expected.push_back(SearchHit(16, 2, 56));
  expected.push_back(SearchHit(16, 2, 69));
  expected.push_back(SearchHit(16, 2, 72));
  expected.push_back(SearchHit(16, 2, 79));
  expected.push_back(SearchHit(16, 2, 80));
  expected.push_back(SearchHit(16, 2, 91));
  expected.push_back(SearchHit(16, 4, 35));
  expected.push_back(SearchHit(16, 12, 3));
  expected.push_back(SearchHit(17, 1, 7));
  expected.push_back(SearchHit(17, 1, 14));
  expected.push_back(SearchHit(17, 1, 18));
  expected.push_back(SearchHit(17, 1, 20));
  expected.push_back(SearchHit(17, 1, 28));
  expected.push_back(SearchHit(17, 1, 29));
  expected.push_back(SearchHit(17, 1, 42));
  expected.push_back(SearchHit(17, 1, 46));
  expected.push_back(SearchHit(17, 1, 47));
  expected.push_back(SearchHit(17, 1, 51));
  expected.push_back(SearchHit(17, 1, 55));
  expected.push_back(SearchHit(17, 1, 58));
  expected.push_back(SearchHit(17, 1, 59));
  expected.push_back(SearchHit(17, 1, 60));
  expected.push_back(SearchHit(17, 1, 61));
  expected.push_back(SearchHit(17, 1, 93));
  expected.push_back(SearchHit(17, 2, 92));
  expected.push_back(SearchHit(17, 4, 85));
  expected.push_back(SearchHit(17, 11, 84));
  expected.push_back(SearchHit(18, 1, 7));
  expected.push_back(SearchHit(18, 1, 14));
  expected.push_back(SearchHit(18, 1, 18));
  expected.push_back(SearchHit(18, 1, 20));
  expected.push_back(SearchHit(18, 1, 28));
  expected.push_back(SearchHit(18, 1, 29));
  expected.push_back(SearchHit(18, 1, 36));
  expected.push_back(SearchHit(18, 1, 42));
  expected.push_back(SearchHit(18, 1, 46));
  expected.push_back(SearchHit(18, 1, 47));
  expected.push_back(SearchHit(18, 1, 51));
  expected.push_back(SearchHit(18, 1, 55));
  expected.push_back(SearchHit(18, 1, 58));
  expected.push_back(SearchHit(18, 1, 59));
  expected.push_back(SearchHit(18, 1, 60));
  expected.push_back(SearchHit(18, 1, 61));
  expected.push_back(SearchHit(18, 1, 79));
  expected.push_back(SearchHit(18, 1, 93));
  expected.push_back(SearchHit(18, 2, 15));
  expected.push_back(SearchHit(18, 2, 69));
  expected.push_back(SearchHit(18, 2, 80));
  expected.push_back(SearchHit(19, 1, 7));
  expected.push_back(SearchHit(19, 1, 14));
  expected.push_back(SearchHit(19, 1, 18));
  expected.push_back(SearchHit(19, 1, 20));
  expected.push_back(SearchHit(19, 1, 28));
  expected.push_back(SearchHit(19, 1, 29));
  expected.push_back(SearchHit(19, 1, 36));
  expected.push_back(SearchHit(19, 1, 42));
  expected.push_back(SearchHit(19, 1, 46));
  expected.push_back(SearchHit(19, 1, 47));
  expected.push_back(SearchHit(19, 1, 51));
  expected.push_back(SearchHit(19, 1, 55));
  expected.push_back(SearchHit(19, 1, 58));
  expected.push_back(SearchHit(19, 1, 59));
  expected.push_back(SearchHit(19, 1, 60));
  expected.push_back(SearchHit(19, 1, 61));
  expected.push_back(SearchHit(19, 1, 79));
  expected.push_back(SearchHit(19, 1, 93));
  expected.push_back(SearchHit(19, 2, 92));
  expected.push_back(SearchHit(20, 1, 7));
  expected.push_back(SearchHit(20, 1, 14));
  expected.push_back(SearchHit(20, 1, 18));
  expected.push_back(SearchHit(20, 1, 20));
  expected.push_back(SearchHit(20, 1, 28));
  expected.push_back(SearchHit(20, 1, 29));
  expected.push_back(SearchHit(20, 1, 36));
  expected.push_back(SearchHit(20, 1, 42));
  expected.push_back(SearchHit(20, 1, 46));
  expected.push_back(SearchHit(20, 1, 47));
  expected.push_back(SearchHit(20, 1, 51));
  expected.push_back(SearchHit(20, 1, 55));
  expected.push_back(SearchHit(20, 1, 58));
  expected.push_back(SearchHit(20, 1, 59));
  expected.push_back(SearchHit(20, 1, 60));
  expected.push_back(SearchHit(20, 1, 61));
  expected.push_back(SearchHit(20, 1, 79));
  expected.push_back(SearchHit(20, 1, 93));
  expected.push_back(SearchHit(20, 2, 15));
  expected.push_back(SearchHit(20, 2, 69));
  expected.push_back(SearchHit(20, 2, 80));
  expected.push_back(SearchHit(21, 1, 7));
  expected.push_back(SearchHit(21, 1, 14));
  expected.push_back(SearchHit(21, 1, 18));
  expected.push_back(SearchHit(21, 1, 20));
  expected.push_back(SearchHit(21, 1, 28));
  expected.push_back(SearchHit(21, 1, 29));
  expected.push_back(SearchHit(21, 1, 36));
  expected.push_back(SearchHit(21, 1, 42));
  expected.push_back(SearchHit(21, 1, 46));
  expected.push_back(SearchHit(21, 1, 47));
  expected.push_back(SearchHit(21, 1, 51));
  expected.push_back(SearchHit(21, 1, 55));
  expected.push_back(SearchHit(21, 1, 58));
  expected.push_back(SearchHit(21, 1, 59));
  expected.push_back(SearchHit(21, 1, 60));
  expected.push_back(SearchHit(21, 1, 61));
  expected.push_back(SearchHit(21, 1, 79));
  expected.push_back(SearchHit(21, 1, 93));
  expected.push_back(SearchHit(21, 2, 92));
  expected.push_back(SearchHit(21, 4, 85));
  expected.push_back(SearchHit(22, 1, 7));
  expected.push_back(SearchHit(22, 1, 14));
  expected.push_back(SearchHit(22, 1, 18));
  expected.push_back(SearchHit(22, 1, 20));
  expected.push_back(SearchHit(22, 1, 28));
  expected.push_back(SearchHit(22, 1, 29));
  expected.push_back(SearchHit(22, 1, 36));
  expected.push_back(SearchHit(22, 1, 42));
  expected.push_back(SearchHit(22, 1, 46));
  expected.push_back(SearchHit(22, 1, 47));
  expected.push_back(SearchHit(22, 1, 51));
  expected.push_back(SearchHit(22, 1, 55));
  expected.push_back(SearchHit(22, 1, 58));
  expected.push_back(SearchHit(22, 1, 59));
  expected.push_back(SearchHit(22, 1, 60));
  expected.push_back(SearchHit(22, 1, 61));
  expected.push_back(SearchHit(22, 1, 79));
  expected.push_back(SearchHit(22, 1, 93));
  expected.push_back(SearchHit(22, 2, 15));
  expected.push_back(SearchHit(22, 2, 69));
  expected.push_back(SearchHit(22, 2, 80));
  expected.push_back(SearchHit(23, 1, 7));
  expected.push_back(SearchHit(23, 1, 14));
  expected.push_back(SearchHit(23, 1, 18));
  expected.push_back(SearchHit(23, 1, 20));
  expected.push_back(SearchHit(23, 1, 28));
  expected.push_back(SearchHit(23, 1, 29));
  expected.push_back(SearchHit(23, 1, 36));
  expected.push_back(SearchHit(23, 1, 42));
  expected.push_back(SearchHit(23, 1, 46));
  expected.push_back(SearchHit(23, 1, 47));
  expected.push_back(SearchHit(23, 1, 51));
  expected.push_back(SearchHit(23, 1, 55));
  expected.push_back(SearchHit(23, 1, 58));
  expected.push_back(SearchHit(23, 1, 59));
  expected.push_back(SearchHit(23, 1, 60));
  expected.push_back(SearchHit(23, 1, 61));
  expected.push_back(SearchHit(23, 1, 79));
  expected.push_back(SearchHit(23, 1, 93));
  expected.push_back(SearchHit(23, 2, 92));
  expected.push_back(SearchHit(24, 1, 7));
  expected.push_back(SearchHit(24, 1, 14));
  expected.push_back(SearchHit(24, 1, 18));
  expected.push_back(SearchHit(24, 1, 20));
  expected.push_back(SearchHit(24, 1, 28));
  expected.push_back(SearchHit(24, 1, 29));
  expected.push_back(SearchHit(24, 1, 36));
  expected.push_back(SearchHit(24, 1, 42));
  expected.push_back(SearchHit(24, 1, 46));
  expected.push_back(SearchHit(24, 1, 47));
  expected.push_back(SearchHit(24, 1, 51));
  expected.push_back(SearchHit(24, 1, 55));
  expected.push_back(SearchHit(24, 1, 58));
  expected.push_back(SearchHit(24, 1, 59));
  expected.push_back(SearchHit(24, 1, 60));
  expected.push_back(SearchHit(24, 1, 61));
  expected.push_back(SearchHit(24, 1, 79));
  expected.push_back(SearchHit(24, 1, 93));
  expected.push_back(SearchHit(24, 2, 15));
  expected.push_back(SearchHit(24, 2, 69));
  expected.push_back(SearchHit(24, 2, 80));
  expected.push_back(SearchHit(25, 1, 7));
  expected.push_back(SearchHit(25, 1, 14));
  expected.push_back(SearchHit(25, 1, 18));
  expected.push_back(SearchHit(25, 1, 20));
  expected.push_back(SearchHit(25, 1, 28));
  expected.push_back(SearchHit(25, 1, 29));
  expected.push_back(SearchHit(25, 1, 36));
  expected.push_back(SearchHit(25, 1, 42));
  expected.push_back(SearchHit(25, 1, 46));
  expected.push_back(SearchHit(25, 1, 47));
  expected.push_back(SearchHit(25, 1, 51));
  expected.push_back(SearchHit(25, 1, 55));
  expected.push_back(SearchHit(25, 1, 58));
  expected.push_back(SearchHit(25, 1, 59));
  expected.push_back(SearchHit(25, 1, 60));
  expected.push_back(SearchHit(25, 1, 61));
  expected.push_back(SearchHit(25, 1, 79));
  expected.push_back(SearchHit(25, 1, 93));
  expected.push_back(SearchHit(25, 2, 92));
  expected.push_back(SearchHit(26, 1, 7));
  expected.push_back(SearchHit(26, 1, 14));
  expected.push_back(SearchHit(26, 1, 20));
  expected.push_back(SearchHit(26, 1, 28));
  expected.push_back(SearchHit(26, 1, 29));
  expected.push_back(SearchHit(26, 1, 36));
  expected.push_back(SearchHit(26, 1, 42));
  expected.push_back(SearchHit(26, 1, 46));
  expected.push_back(SearchHit(26, 1, 47));
  expected.push_back(SearchHit(26, 1, 51));
  expected.push_back(SearchHit(26, 1, 58));
  expected.push_back(SearchHit(26, 1, 59));
  expected.push_back(SearchHit(26, 1, 60));
  expected.push_back(SearchHit(26, 1, 61));
  expected.push_back(SearchHit(26, 1, 79));
  expected.push_back(SearchHit(26, 1, 93));
  expected.push_back(SearchHit(26, 2, 15));
  expected.push_back(SearchHit(26, 2, 18));
  expected.push_back(SearchHit(26, 2, 55));
  expected.push_back(SearchHit(26, 2, 69));
  expected.push_back(SearchHit(26, 2, 71));
  expected.push_back(SearchHit(26, 2, 80));
  expected.push_back(SearchHit(26, 2, 81));
  expected.push_back(SearchHit(27, 1, 7));
  expected.push_back(SearchHit(27, 1, 12));
  expected.push_back(SearchHit(27, 1, 14));
  expected.push_back(SearchHit(27, 1, 20));
  expected.push_back(SearchHit(27, 1, 28));
  expected.push_back(SearchHit(27, 1, 29));
  expected.push_back(SearchHit(27, 1, 31));
  expected.push_back(SearchHit(27, 1, 36));
  expected.push_back(SearchHit(27, 1, 39));
  expected.push_back(SearchHit(27, 1, 41));
  expected.push_back(SearchHit(27, 1, 42));
  expected.push_back(SearchHit(27, 1, 45));
  expected.push_back(SearchHit(27, 1, 46));
  expected.push_back(SearchHit(27, 1, 47));
  expected.push_back(SearchHit(27, 1, 51));
  expected.push_back(SearchHit(27, 1, 58));
  expected.push_back(SearchHit(27, 1, 59));
  expected.push_back(SearchHit(27, 1, 60));
  expected.push_back(SearchHit(27, 1, 61));
  expected.push_back(SearchHit(27, 1, 63));
  expected.push_back(SearchHit(27, 1, 79));
  expected.push_back(SearchHit(27, 1, 85));
  expected.push_back(SearchHit(27, 1, 92));
  expected.push_back(SearchHit(27, 1, 93));

  std::sort(actual.begin(), actual.end());
  std::sort(expected.begin(), expected.begin());

  std::pair<std::vector<SearchHit>::iterator,
            std::vector<SearchHit>::iterator> mis(
    std::mismatch(expected.begin(), expected.end(), actual.begin())
  );

  if (mis.first != expected.end()) {
    SCOPE_ASSERT_EQUAL(*mis.first, *mis.second);
  }
}
