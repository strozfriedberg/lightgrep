# Copyright 2024 Aon Cyber Solutions
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import subprocess
from multiprocessing import Process
from analyze_trace import TraceStats

def runProc(id, name, keys, corpus):
  print("%s %s %s" % (name, keys, corpus))
  args = ['./lightgrep.exe', '--no-output', '--begin-debug=0', keys, corpus]
  lg = subprocess.Popen(args=args, bufsize=-1, stderr=subprocess.PIPE)
  stats = TraceStats()
  stats.RecordSegments = False
  stats.read(lg.stderr)
  lg.wait()
  print('%s\t%s\t%s\t%s' % (id, name, 'TotalThreads', stats.totalThreads()))
  print('%s\t%s\t%s\t%s' % (id, name, 'MaxThreadsOnAFrame', stats.MaxThreadsOnFrame))
  print('%s\t%s\t%s\t%s' % (id, name, 'AvgThreadsPerFrame', stats.avgThreadsPerFrame()))
  print('%s\t%s\t%s\t%s' % (id, name, 'TotalInstructions', stats.totalInstructions()))
  print('%s\t%s\t%s\t%s' % (id, name, 'MaxInstructionsOnAFrame', stats.maxInstructionsOnAFrame()))
  print('%s\t%s\t%s\t%s' % (id, name, 'AvgInstructionsPerFrame', stats.avgInstructionsPerFrame()))
  print('%s\t%s\t%s\t%s' % (id, name, 'MaxThreadLifetime', stats.maxThreadLifetime()))
  print('%s\t%s\t%s\t%s' % (id, name, 'AvgThreadLifetime', stats.avgThreadLifetime()))
  print('%s\t%s\t%s\t%s' % (id, name, 'MaxFinishOpsOnAFrame', stats.maxFinishOpsOnAFrame()))
  print('%s\t%s\t%s\t%s' % (id, name, 'AvgFinishOpsPerFrame', stats.avgFinishOpsPerFrame()))

if __name__ == '__main__':
  id = '12345' # we'll put git commit sha1 here
#  tests = [(id, 'norvig', 'pytest/keys/114743.txt', 'pytest/corpora/norvig6mb.txt'),
#            (id, 'twain', 'pytest/keys/twain.txt', 'pytest/corpora/marktwainworks.txt')]
  tests = [(id, 'norvig', 'pytest/keys/shuf55.txt', 'stupid.txt')]
  procs = [Process(target=runProc, args=t) for t in tests]
  for p in procs:
    p.start()
  for p in procs:
    p.join()
