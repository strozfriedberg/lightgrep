#!/usr/bin/env python
# encoding: utf-8

import sys
import json
import collections
import math

InstructionCodes = {  
  0:'UNINITIALIZED',
  1:'LIT_OP',
  2:'EITHER_OP',
  3:'RANGE_OP',
  4:'ANY_OP',
  5:'BIT_VECTOR_OP',
  6:'JUMP_TABLE_RANGE_OP',
  7:'FINISH_OP',
  8:'FORK_OP',
  9:'JUMP_OP',
  10:'CHECK_HALT_OP',
  11:'LABEL_OP',
  12:'MATCH_OP',
  13:'HALT_OP',
  14:'ILLEGAL'
}

def avg(counter):
  running = 0.0
  total = 0
  for el in counter.most_common():
    running += el[0] * el[1]
    total += el[1]
  return running / total

class TraceStats:
  def __init__(self):
    self.MaxThreadsOnFrame = 0
    self.ThreadsPerFrameHist = collections.Counter()
    self.InstructionHist = collections.Counter()
    self.InstructionsPerFrameHist = collections.Counter()
    self.OpCodes = collections.Counter()
    self.ThreadLifetimes = collections.Counter()
    self.NumThreadsSegments = []
    self.NumBytes = 0
    self.RecordSegments = True
    self.FinishOpsPerFrameHist = collections.Counter()
    self.LabelHist = collections.Counter()
    self.WorstFrame = ''

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
          if (n > self.MaxThreadsOnFrame):
            self.MaxThreadsOnFrame = n
            self.WorstFrame = line
          self.ThreadsPerFrameHist[n] += 1
          threadLevel = math.trunc(n / 3)
          if (lastNumThreads != threadLevel and self.RecordSegments):
            if (lastNumThreads > 0):
              self.NumThreadsSegments.append((lastNumThreads, lastStart, offset))
            lastStart = offset
            lastNumThreads = threadLevel
          numInstrs = 0
          for t in rec["list"]:
            finishOps = 0
            state = t["state"]
            if state & 2: # pre-run
              self.InstructionHist[t["PC"]] += 1
              self.LabelHist[t["Label"]] += 1
              op = t["op"]
              self.OpCodes[op] += 1
              if op == 7:
                finishOps += 1
              numInstrs += 1
#            elif state & 8 > 0: # died
#              self.ThreadLifetimes[offset - t["Start"]] += 1
          self.InstructionsPerFrameHist[numInstrs] += 1
          self.FinishOpsPerFrameHist[finishOps] += 1
      except:
        pass
    self.NumThreadsSegments.append((lastNumThreads, lastStart, bytes))
    self.NumBytes = bytes
  
  def totalThreads(self):
    return sum(self.ThreadLifetimes.values())

  def totalInstructions(self):
    return sum(self.OpCodes.values())

  def maxInstructionsOnAFrame(self):
    return max(self.InstructionsPerFrameHist.keys())

  def maxThreadLifetime(self):
    return max(self.ThreadLifetimes.keys())

  def avgThreadsPerFrame(self):
    return avg(self.ThreadsPerFrameHist)

  def avgInstructionsPerFrame(self):
    return avg(self.InstructionsPerFrameHist)

  def avgThreadLifetime(self):
    return avg(self.ThreadLifetimes)

  def maxFinishOpsOnAFrame(self):
    return max(self.FinishOpsPerFrameHist.keys())

  def avgFinishOpsPerFrame(self):
    return avg(self.FinishOpsPerFrameHist)

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

    print("Instruction Types:")
    totalInstrs = sum(self.OpCodes.values())
    for el in self.OpCodes.most_common():
      print("  %s, %s, %s" % (InstructionCodes[el[0]], el[1], float(el[1] * 100) / totalInstrs))

    print("Label Histogram")
    for el in self.LabelHist.most_common():
      print("  %s, %s, %s" % (el[0], el[1], float(el[1] * 100) / totalInstrs))

#    totalInstrs = sum(self.InstructionHist.values())
    print("Instructions executed histogram:")
    for el in self.InstructionHist.most_common():
      print("  %s, %s, %s" % (el[0], el[1], float(el[1] * 100) / totalInstrs))
    
    print("File segments (%s)" % (str(len(self.NumThreadsSegments))))
    for seg in self.NumThreadsSegments:
      print("  %s, %s, %s, %s" % (seg[0], seg[2] - seg[1], seg[1], seg[2]))

    print("Worst frame:")
    print(self.WorstFrame)

if __name__ == '__main__':
  t = TraceStats()
  t.RecordSegments = False
  try:
    t.read(sys.stdin)
  finally:
    t.output()
