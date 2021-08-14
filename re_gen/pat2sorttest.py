#!/usr/bin/python

#
# Expects either:
#
#   * a tab-separated pattern set followed by a text on each stdin line, or
#   * a tab-separated pattern set on each stdin line, and a text as argv[1].
#
# Writes unit tests to stdout.
#

import os.path
import sys

import lgtestlib

def main():
    sg = os.path.dirname(__file__) + '/shitgrep'

    # get text from command line?
    if len(sys.argv) < 2:
        cl_text = False
    elif len(sys.argv) == 2:
        text = sys.argv[1]
        cl_text = True
    else:
        raise Exception('too many arguments')

    # print head stuff
    print('''#include "catch.hpp"

#include <algorithm>

#include "stest.h"
''')

    setnum = 0

    for line in sys.stdin:
        # read the test set
        parts = line.rstrip('\n').split('\t')

        if cl_text:
            pats = parts
        else:
            pats = parts[0:-1]
            text = parts[-1]

        # get matches from shitgrep
        matches = lgtestlib.run_shitgrep(sg, pats, text)

        if matches is None:
            # every pattern in this set has zero-length matches
            if len(pats) == 1:
                # test single patterns for zero-length matches
                print('''TEST_CASE("autoPatternTest{setnum}") {{
  NFABuilder nfab;
  ParseTree tree;
  REQUIRE(parse({R"({pat})", false, false}, tree));
  REQUIRE(!nfab.build(tree));
}}
'''.format(setnum=setnum, pat=pats[0]))

        else:
            # this pattern set has no zero-length matches
            if len(pats) == 1:
                stest = 'R"({})"'.format(pats[0])
            else:
                stest = '{{ R"({})" }}'.format(')", R"('.join(pats))

            print('''TEST_CASE("autoPatternTest{setnum}") {{
  STest fixture({stest});
  const byte* text = (const byte*) R"({text})";
  fixture.search(text, text + {textlen}, 0);
  std::vector<SearchHit>& actual(fixture.Hits);

  std::vector<SearchHit> expected{''')

            for m in matches:
                print(f'    {{{m[0]}, {m[1]}, {m[2]}}},')

            print('''  };

  std::sort(actual.begin(), actual.end());
  std::sort(expected.begin(), expected.begin());

  std::pair<std::vector<SearchHit>::iterator,
            std::vector<SearchHit>::iterator> mis(
    std::mismatch(expected.begin(), expected.end(), actual.begin())
  );

  if (mis.first != expected.end()) {
    REQUIRE(*mis.first == *mis.second);
  }
}''')

        setnum += 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
