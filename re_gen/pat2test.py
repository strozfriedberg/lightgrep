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
  print '''#include <scope/test.h>

#include "stest.h"
'''

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

    if len(pats) == 1:
      stest = 'R"({})"'.format(pats[0])
    else:
      stest = '{{ R"({})" }}'.format(')", R"('.join(pats))

    print '''SCOPE_FIXTURE_CTOR(autoPatternTest{setnum}, STest, STest({stest})) {{'''.format(setnum=setnum, stest=stest)

    if matches is None:
      # every pattern in this set has zero-length matches
      print '  SCOPE_ASSERT(fixture.parsesButNotValid());'
    else:
      # this pattern set has no zero-length matches
      print '''  const char text[] = R"({text})";
  fixture.search(text, text + {textlen}, 0);
  SCOPE_ASSERT_EQUAL({matchcount}u, fixture.Hits.size());'''.format(text=text, textlen=len(text), matchcount=len(matches))

      for i, m in enumerate(matches):
        print '  SCOPE_ASSERT_EQUAL(SearchHit({}, {}, {}), fixture.Hits[{}]);'.format(m[0], m[1], m[2], i)

    print '}\n'

    setnum += 1

  return 0


if __name__ == "__main__":
  sys.exit(main())

