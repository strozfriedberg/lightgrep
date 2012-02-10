#!/usr/bin/python

import os.path
import sys

import lgtestlib

def main():
  sg = os.path.dirname(__file__) + '/shitgrep'
  lg = os.path.dirname(__file__) + '/../bin/src/cmd/lightgrep'

  if len(sys.argv) != 2:
    raise Exception('wrong number of arguments') 

  text = sys.argv[1]
  pats = [ p.rstrip('\n') for p in sys.stdin.readlines() ]

  # binary search to weed out good patterns quickly
  pats = partition_failure(sg, lg, pats, text)
 
  # now remove patterns one at at time
  for p in reversed(pats):
    if mismatch(sg, lg, [ x for x in pats if x != p ], text):
      pats.remove(p)
    
  print pats


def partition_failure(sg, lg, pats, text):
  if mismatch(sg, lg, pats, text):
    # this pattern list fails
    if (len(pats) == 1):
      # the pattern list is a singleton
      return pats
    else:
      ret = partition_failure(sg, lg, pats[0:len(pats)/2], text)
      if len(ret) > 0:
        # the first half of the pattern list fails
        return ret
      ret = partition_failure(sg, lg, pats[len(pats)/2:], text)
      if len(ret) > 0:
        # the second half of the pattern list fails
        return ret
      return pats
  else:
    # this pattern list is ok
    return list()


def mismatch(sg, lg, pats, text):
  # get matches from shitgrep
  sgmatches = lgtestlib.run_shitgrep(sg, pats, text)

  # get matches from lightgrep
  lgmatches = lgtestlib.run_lightgrep(lg, pats, text)
 
  return lgmatches != sgmatches


if __name__ == "__main__":
  sys.exit(main())
