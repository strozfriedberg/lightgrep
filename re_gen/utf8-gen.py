#!/usr/bin/python

import re
import sys

def main():
  for cp in xrange(0x01, 0x09):
    print_test(cp)

  # skip \t, we use it as a separator between patterns
  # and the text so it can't appear in the text

  for cp in xrange(0x10,0x110000):
    print_test(cp)

def print_test(cp):
  bytes = unichr(cp).encode('UTF-8')
#  pat = re.escape(bytes)
  pat = escape(bytes)
  text = '%s%s' % ((bytes, 'x') if cp % 2 else ('x', bytes))
  print('%s\t0\t0\tUTF-8\t%s' % (pat, text))

def escape(pat):
  return re.sub('([.*+?[\\\\|()])', '\\\\\g<1>', pat)

if __name__ == "__main__":
  sys.exit(main())
