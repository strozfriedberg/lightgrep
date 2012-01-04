import subprocess
from multiprocessing import Process
from analyze_trace import TraceStats

def runProc(name, keys, corpus):
  print("%s %s %s" % (name, keys, corpus))
  args = ['./lightgrep.exe', '--no-output', '--begin-debug=0', keys, corpus]
  lg = subprocess.Popen(args=args, bufsize=-1, stderr=subprocess.PIPE)
  stats = TraceStats()
  stats.RecordSegments = False
  stats.read(lg.stderr)
  lg.wait()
  stats.output()

if __name__ == '__main__':
  tests = [('norvig', 'pytest/keys/114743.txt', 'pytest/corpora/norvig6mb.txt'),
            ('twain', 'pytest/keys/twain.txt', 'pytest/corpora/marktwainworks.txt')]
  procs = [Process(target=runProc, args=t) for t in tests]
  for p in procs:
    p.start()
  for p in procs:
    p.join()
