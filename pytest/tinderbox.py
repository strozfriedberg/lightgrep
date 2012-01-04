#!/usr/bin/python

from __future__ import print_function

import os
import sys

from multiprocessing import Process, Queue
from subprocess import CalledProcessError, PIPE, Popen

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

def task_declare(name):
  print(name, end=": ")

def task_result(result):
  print(result)

def task_success():
  task_result("ok")

def task_failure():
  task_result("failed!")

def runLongTest(knownGoodData, errQueue):
  bzcat = [bzcat_bin, knownGoodData]
  p1 = Popen(bzcat, bufsize=-1, stdout=PIPE)
  p2 = Popen(long_test, bufsize=-1, stdin=p1.stdout, stdout=PIPE, stderr=open(os.devnull, 'w'))

  for line in p2.stdout:
    if line.endswith('failed!'):
      errQueue.put((line, p2.stdout.readline(), p2.stdout.readline()))
  errQueue.put(None)
  p2.wait()

def main():
  try:
    # check whether the repo is current
    task_declare("Pulling")
    if 'Already up-to-date' in run(git_pull)[0]:
      task_result("up-to-date")
#      sys.exit()
    else:
      task_success()
 
    # clean and build
    task_declare("Cleaning")
    run(scons_clean, scons_env)
    task_success()

    task_declare("Building")
    result = run(scons_build, scons_env)
    stdout = result[0].split('\n')
    stderr = result[1].split('\n')

    gcc_warnings = [ line for line in stderr if 'warning' in line ]
    gcc_errors = [ line for line in stderr if 'error' in line ]
   
    if gcc_warnings:
      task_result("warnings")
      task_result(gcc_warnings)
    
    if gcc_errors:
      task_failed()
      task_result(gcc_errors)
      sys.exit()
  
    if not gcc_warnings:
      task_success()

    # check unit test failures
    task_declare("Unit tests")
    try:
      fail_end = stdout.index('Failures!')
      unit_failures = stdout[stdout.index('bin/test/test --test')+1:fail_end]
      task_failure()
      task_result(unit_failures)
      sys.exit()
    except ValueError:
      task_success() 
 
    # from here onward, run tests in parallel
 
    # run long tests
    task_declare("Long tests")
    longErrs = Queue()
    oneProc = Process(target=runLongTest, args=('re_gen/aQ-3.bz2', longErrs))
    threeProc = Process(target=runLongTest, args=('re_gen/aQ-3-3.bz2', longErrs))
    oneProc.start()
    threeProc.start()

    long_failures = []
    err = ('', '', '')
    while err is not None:
      err = longErrs.get()
      if (err is not None):
        long_failures.append(err)

    oneProc.join()
    threeProc.join()

    if long_failures:
      task_failure()
      task_result(long_failures)
    else:
      task_success()

  except (CalledProcessError, OSError) as e:
    print(e)


def run(cmd, environ=None):
  proc = Popen(args=cmd, env=environ, bufsize=-1, stdout=PIPE, stderr=PIPE)
  return proc.communicate()


if __name__ == "__main__":
  main()
