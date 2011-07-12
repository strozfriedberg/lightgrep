#!/usr/bin/python

#
# Expects one tab-separated pattern set per line on stdin, text as only
# command-line argument. Writes tests to stdout in multipattern "long"
# test format.
#

import os.path
import struct
import subprocess
import sys
import tempfile

def main():
  path = os.path.dirname(__file__)

  # compile the output structs
  lstruct = struct.Struct('=L')
  mstruct = struct.Struct('=QQQ')

  # get the text
  text = sys.argv[1]

  setnum = 0

  for line in sys.stdin:
    # read the patterns
    pats = line.rstrip('\n').split('\t')

    pf = None

    try:
      if len(pats) == 1:
        # specify single patterns on command line
        cmd = (path + '/shitgrep', '-p', pats[0])
      else:
        # write multiple patterns to temporary pattern file
        pf, pfname = tempfile.mkstemp()
        for p in pats:
          print >>pf, p

        cmd = (path + '/shitgrep', pfname)

      # get matches from shitgrep
      proc = subprocess.Popen(cmd,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
      )

      sgout, sgerr = proc.communicate(text)

      retval = proc.wait()
      if retval:
        raise Exception('shitgrep returned {}, {}'.format(retval, sgerr))

    finally:
      if pf:
        # clean up pattern file, if we used one
        pf.close()
        os.unlink(pfname)

    if len(pats) == sgerr.count('is not allowed as a final state of the NFA'):
      # skip pattern sets which have only zero-length matches
      continue

    matches = []
    for m in sgout.splitlines():
      matches.append(map(int, m.split('\t', 3)[0:3]))

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

if __name__ == "__main__":
  sys.exit(main())

