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

        apats = ['^(' + p + ')' for p in pats]

        # get matches from shitgrep
        matches = lgtestlib.run_shitgrep(sg, apats, text)

        if len(pats) == 1:
            stest = 'R"({})"'.format(pats[0])
        else:
            stest = '{{ R"({})" }}'.format(')", R"('.join(pats))

        print(f'''TEST_CASE("autoPatternStartsWithTest{setnum}") {{
  STest fixture({stest});''')

        if matches is None:
            # every pattern in this set has zero-length matches
            print('  REQUIRE(fixture.parsesButNotValid());')
        else:
            # this pattern set has no zero-length matches
            print(f'''  const char text[] = "{text}";
  fixture.startsWith(text, text + {len(text)}, 0);
  const std::vector<SearchHit> expected{{''')

            for m in matches:
                print(f'    {{{m[0]}, {m[1]}, {m[2]}}},')

            print('  };')
            print('  REQUIRE(expected == fixture.Hits);')

        print('}\n')

        setnum += 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
