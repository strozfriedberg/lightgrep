#!/usr/bin/env python
# encoding: utf-8

import sys
import json
import collections
import math

class TraceStats:
  def __init__(self):
    self.MaxThreadsOnFrame = 0
    self.ThreadsPerFrameHist = collections.Counter()
    self.InstructionHist = collections.Counter()
    self.InstructionsPerFrameHist = collections.Counter()
    self.ThreadLifetimes = collections.Counter()
    self.NumThreadsSegments = []
    self.NumBytes = 0

  def read(self, lines):
    lastNumThreads = 0
    lastStart = -1
    bytes = 0
    for line in lines:
      try:
        rec = json.loads(line)
        if ("offset" not in rec):
          pass
        offset = rec["offset"]
        if (offset > -1):
          bytes += 1
          n = rec["num"]
          self.MaxThreadsOnFrame = max(self.MaxThreadsOnFrame, n)
          self.ThreadsPerFrameHist[n] += 1
          threadLevel = math.trunc(n / 3)
          if (lastNumThreads != threadLevel):
            self.NumThreadsSegments.append((lastNumThreads, lastStart, offset))
            lastStart = offset
            lastNumThreads = threadLevel
          numInstrs = 0
          for t in rec["list"]:
            state = t["state"]
            if state & 2:
              self.InstructionHist[t["PC"]] += 1
              numInstrs += 1
            elif state & 8 > 0:
              self.ThreadLifetimes[offset - t["Start"]] += 1
          self.InstructionsPerFrameHist[numInstrs] += 1
      except:
        pass
    self.NumThreadsSegments.append((lastNumThreads, lastStart, bytes))
    self.NumBytes = bytes
  
  def output(self):
    print("Num bytes: " + str(self.NumBytes))

    print("Max threads on a frame: " + str(self.MaxThreadsOnFrame))
    print("Threads on a frame histogram:")
    for el in self.ThreadsPerFrameHist.most_common():
      print("  %s, %s, %s" % (el[0], el[1], float(el[1] * 100) / self.NumBytes))

    print("Instructions on a frame histogram:")
    for el in self.InstructionsPerFrameHist.most_common():
      print("  %s, %s, %s" % (el[0], el[1], float(el[1] * 100) / self.NumBytes))

    print("Thread lifetimes:")
    numThreads = sum(self.ThreadLifetimes.values())
    for el in self.ThreadLifetimes.most_common():
      print("  %s, %s, %s" % (el[0], el[1], float(el[1] * 100) / numThreads))

    totalInstrs = sum(self.InstructionHist.values())
    print("Instructions executed histogram:")
    for el in self.InstructionHist.most_common():
      print("  %s, %s, %s" % (el[0], el[1], float(el[1] * 100) / totalInstrs))
    
    print("File segments (%s)" % (str(len(self.NumThreadsSegments))))
    for seg in self.NumThreadsSegments:
      print("  %s, %s, %s, %s" % (seg[0], seg[2] - seg[1], seg[1], seg[2]))

if __name__ == '__main__':
  t = TraceStats()
  t.read(sys.stdin)
  t.output()
