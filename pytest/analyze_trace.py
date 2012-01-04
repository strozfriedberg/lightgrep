#!/usr/bin/env python
# encoding: utf-8

import sys
import json
import collections

class TraceStats:
  def __init__(self):
    self.MaxThreadsOnFrame = 0
    self.ThreadsPerFrameHist = collections.Counter()
    self.InstructionHist = collections.Counter()
    self.InstructionsPerFrameHist = collections.Counter()
    self.NumThreadsSegments = []

  def read(self, lines):
    curSeg = (-1,0,0)
    for line in lines:
      try:
        rec = json.loads(line)
        if ("offset" not in rec):
          pass
        offset = rec["offset"]
        if (offset > -1):
          n = rec["num"]
          self.MaxThreadsOnFrame = max(self.MaxThreadsOnFrame, n)
          self.ThreadsPerFrameHist[n] += 1
          if (curSeg[2] != n):
            curSeg[1] = offset
            self.NumThreadsSegments.append(curSeg)
            curSeg = (offset, -1, n)
      except:
        pass
  
  def output(self):
    print("Max threads on a frame: " + str(self.MaxThreadsOnFrame))
    print("Threads on a frame histogram:")
    for el in self.ThreadsPerFrameHist.most_common():
      print("  %s" % str(el))

if __name__ == '__main__':
  t = TraceStats()
  t.read(sys.stdin)
  t.output()
