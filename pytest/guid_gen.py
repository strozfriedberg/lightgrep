#!/usr/bin/env python

import uuid
import sys

def nGuids(n):
  for i in xrange(n):
    print uuid.uuid4().hex

if __name__ == "__main__":
  nGuids(int(sys.argv[1]))
