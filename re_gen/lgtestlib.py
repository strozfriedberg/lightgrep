
import os
import subprocess
import tempfile

def run_shitgrep(sg, pats, text):
  pf = None

  try:
    if len(pats) == 1:
      # specify single patterns on command line
      cmd = (sg, '-p', pats[0])
    else:
      # write multiple patterns to temporary pattern file
      pf, pfname = tempfile.mkstemp()
      for p in pats:
        print >>pf, p

      cmd = (sg, pfname)

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
    # every pattern in this pattern set has zero-length matches
    return None

  matches = []
  for m in sgout.splitlines():
    matches.append(map(int, m.split('\t', 3)[0:3]))

  return matches

