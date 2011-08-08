#!/usr/bin/python

#
# Expects patterns on stdin, one per line, and sample count n and size k as
# arguments. Prints n lines of k tab-separated patterns, chosen uniformly
# without replacement within each line from the patterns given on stdin.
#

import random
import sys

def main():
  pats = map(lambda s: s.rstrip('\n'), sys.stdin.readlines()) 
  scount = int(sys.argv[1])
  ssize = int(sys.argv[2])

  for x in range(0, scount):
    print '\t'.join(random.sample(pats, ssize))

  return 0


if __name__ == "__main__":
  sys.exit(main())

