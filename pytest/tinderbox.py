#!/usr/bin/python

import os
import subprocess
from multiprocessing import Process, Queue
import sys

git_bin = 'git'
git_pull = [ git_bin, 'pull' ]

scons_bin = 'scons'
scons_threads = 8
scons_boost_type = '-mt'

scons_boost_type_arg = 'boostType="%s"' % (scons_boost_type)
scons_threads_arg = '-j%d' % (scons_threads)

scons_clean = [ scons_bin, '-c', scons_boost_type_arg ]
scons_build = [ scons_bin, scons_threads_arg, scons_boost_type_arg ]

scons_env = os.environ
scons_env['LD_LIBRARY_PATH'] = '/home/uckelman/projects/lightbox/lightgrep/lib'

test_bin = 'bin/test/test'
long_test = [ test_bin, '--long-test' ]

bzcat_bin = 'bzcat'
long_test_single_bzcat = [ bzcat_bin, 're_gen/aQ-3.bz2' ]
long_test_triple_bzcat = [ bzcat_bin, 're_gen/aQ-3-3.bz2' ]

def runLongTest(knownGoodData, errQueue):
  bzcat = [bzcat_bin, knownGoodData]
  p1 = subprocess.Popen(bzcat, bufsize=-1, stdout=subprocess.PIPE)
  p2 = subprocess.Popen(long_test, bufsize=-1, stdin=p1.stdout, stdout=subprocess.PIPE, stderr=open('/dev/null', 'w'))

  for line in p2.stdout:
    if line.endswith('failed!'):
      errQueue.put((line, p2.stdout.readline(), p2.stdout.readline()))
  errQueue.put(None)
  p2.wait()

def main():
  try:
    # check whether the repo is current
#    if 'Already up-to-date' in run(git_pull)[0]:
#      sys.exit()
    
    # clean and bulid
    run(scons_clean, scons_env)

    result = run(scons_build, scons_env)
    stdout = result[0].split('\n')
    stderr = result[1].split('\n')

    gcc_warnings = [ line for line in stderr if 'warning' in line ]
    
    try:
      fail_end = stdout.index('Failures!')
      unit_tests = stdout[stdout.index('bin/test/test --test')+1:fail_end]
    except ValueError:
      unit_tests = []
      
    print(gcc_warnings)
    print(unit_tests)

    # run single-pattern long test
    longErrs = Queue()
    oneProc = Process(target=runLongTest, args=('re_gen/aQ-3.bz2', longErrs))
    threeProc = Process(target=runLongTest, args=('re_gen/aQ-3-3.bz2', longErrs))
    oneProc.start()
    threeProc.start()
    err = ('', '', '')
    while err is not None:
      err = longErrs.get()
      if (err is not None):
        print(err)
    
    oneProc.join()
    threeProc.join()

  except (subprocess.CalledProcessError, OSError) as e:
    print e


def run(cmd, environ=None):
  proc = subprocess.Popen(args=cmd,
                          env=environ,
                          bufsize=-1,
                          stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE)
  return proc.communicate()


if __name__ == "__main__":
  main()
