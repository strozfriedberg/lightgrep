#!/usr/bin/python

#
# Expects one pattern per line on stdin, text as only command-line argument.
# Writes tests to stdout in multipattern "long" test format.
#

import os.path
import struct
import subprocess
import sys

def main():
  path = os.path.dirname(__file__)

  # compile the output structs
  lstruct = struct.Struct('=L')
  mstruct = struct.Struct('=QQQ')
 
  # get the text
  text = sys.argv[1]

  patnum = 0

  # read the patterns 
  for pat in sys.stdin:
    pat = pat.rstrip('\n')
    
    # get matches from shitgrep
    proc = subprocess.Popen(
      (path + '/shitgrep', '-p', pat),
      stdin=subprocess.PIPE,
      stdout=subprocess.PIPE,
      stderr=subprocess.PIPE
    )

    sgout, sgerr = proc.communicate(text)

    retval = proc.wait()
    if retval:
      raise Exception('shitgrep returned {}, {}'.format(retval, sgerr))

    if 'is not allowed as a final state of the NFA' in sgerr:
      # skip patterns with zero-length matches
      continue

    matches = []
    for m in sgout.splitlines():
      matches.append(map(int, m.split('\t', 3)[0:3]))

    # write out this pattern and its matches
    sys.stdout.write(lstruct.pack(1))
    sys.stdout.write(lstruct.pack(len(pat)))
    sys.stdout.write(pat)
    sys.stdout.write(lstruct.pack(len(text)))
    sys.stdout.write(text)
    sys.stdout.write(lstruct.pack(len(matches)))

    for m in matches:
      sys.stdout.write(mstruct.pack(m[0], m[1], m[2]))

    # show progress
    patnum += 1
    if not patnum % 100:
      print >> sys.stderr, patnum

if __name__ == "__main__":
  sys.exit(main())

