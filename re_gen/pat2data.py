#!/usr/bin/python

#
# Expects one tab-separated pattern set per line on stdin, text as only
# command-line argument. Writes tests to stdout in multipattern "long"
# test format.
#

import os.path
import struct
import sys

import lgtestlib

def main():
  sg = os.path.dirname(__file__) + '/shitgrep'

  # compile the output structs
  lstruct = struct.Struct('=L')
  mstruct = struct.Struct('=QQQ')

  # get the text
  text = sys.argv[1]

  setnum = 0

  for line in sys.stdin:
    # read the patterns
    pats = line.rstrip('\n').split('\t')

    # get matches from shitgrep
    matches = lgtestlib.run_shitgrep(sg, pats, text)

    if matches is None:
      # skip pattern sets where every pattern has zero-length matches
      continue

    # write out patterns and their matches
    sys.stdout.write(lstruct.pack(len(pats)))
    for pat in pats:
      sys.stdout.write(lstruct.pack(len(pat)))
      sys.stdout.write(pat)
    sys.stdout.write(lstruct.pack(len(text)))
    sys.stdout.write(text)
    sys.stdout.write(lstruct.pack(len(matches)))

    for m in matches:
      sys.stdout.write(mstruct.pack(m[0], m[1], m[2]))

    # show progress
    setnum += 1
    if not setnum % 100:
      print >>sys.stderr, setnum

  print >>sys.stderr, setnum
  return 0


if __name__ == "__main__":
  sys.exit(main())

