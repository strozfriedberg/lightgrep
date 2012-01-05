#!/usr/bin/python

from __future__ import print_function

import os
import re
import sqlite3
import sys

from multiprocessing import Process, Queue
from subprocess import CalledProcessError, PIPE, Popen

git_bin = 'git'
git_pull = [ git_bin, 'pull' ]
git_hash = [ git_bin, 'rev-parse', 'HEAD' ]

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

perf_bin = 'perf'

lg_bin = 'bin/src/cmd/lightgrep'

norvig_test = [ perf_bin, 'stat', '--repeat', '10', '-d', lg_bin, '--no-output', 'pytest/keys/114743.txt', 'pytest/corpora/norvig6mb.txt' ]

twain_test = [ perf_bin, 'stat', '--repeat', '10', '-d', lg_bin, '--no-output', 'pytest/keys/twain.txt', 'pytest/corpora/marktwainworks.txt' ]

dbfile = 'pytest/lg.db'

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

def perfStats(perfspew):
  stats_begin = None;
  for (i, line) in enumerate(perfspew):
    if line.startswith(" Performance counter stats"):
      stats_begin = i + 1
      break;

  stats = dict()
  p = re.compile("\s+((?:\d+|(?:\d{1,3}(?:,\d{3})+))(?:\.\d+)?)\s+([\w-]+)")
  for line in perfspew[stats_begin:]:
    m = p.match(line)
    if m:
      stats[m.group(2).replace('-', '_')] = m.group(1).replace(',', '')

  return stats

def perfTest(name, commit, count, cmd, db):
  stdout = run(cmd)[1].split('\n')

  task_declare("%s test hit count" % (name))
  if '%d hits' % (count) in stdout:
    task_success()
  else:
    task_failure()
    sys.exit()

  stats = perfStats(stdout)
  stats['git'] = commit
  stats['test_name'] = name.lower()

  perf_insert = \
    'INSERT INTO perf ( \
      git, \
      test_name, \
      seconds, \
      task_clock, \
      context_switches, \
      CPU_migrations, \
      page_faults, \
      cycles, \
      stalled_cycles_frontend, \
      stalled_cycles_backend, \
      instructions, \
      branches, \
      branch_misses, \
      L1_dcache_loads, \
      L1_dcache_load_misses, \
      LLC_loads, \
      LLC_load_misses \
    ) VALUES ( \
      :git, \
      :test_name, \
      :seconds, \
      :task_clock, \
      :context_switches, \
      :CPU_migrations, \
      :page_faults, \
      :cycles, \
      :stalled_cycles_frontend, \
      :stalled_cycles_backend, \
      :instructions, \
      :branches, \
      :branch_misses, \
      :L1_dcache_loads, \
      :L1_dcache_load_misses, \
      :LLC_loads, \
      :LLC_load_misses \
    )'

  db.execute(perf_insert, stats)
  db.commit()

def main():
  build_force = False
  commit = None

  # parse our arguments
  if len(sys.argv) > 1:
    for arg in sys.argv[1:]:
      if arg == '-f':
        build_force = True
      else:
        commit = arg

  # put repo into a known state
  run([ git_bin, 'checkout', 'master' ])

  try:
    # check whether the repo is current
    task_declare("Pulling")
    if 'Already up-to-date' in run(git_pull)[0]:
      task_result("up-to-date")
      if not build_force:
        sys.exit()
    else:
      task_success()

    task_declare("Commit")

    # checkout the requested commit, if any
    if commit:
      run([ git_bin, 'checkout', commit])
    else:
      # get hash for HEAD
      commit = run(git_hash)[0].strip()

    task_result(commit)
 
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
      task_failure()
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

    # prepare for tests using the database
    with sqlite3.connect(dbfile) as db:
      if build_force:
        db.execute("DELETE FROM perf WHERE git = ?", (commit,))

      # run Twain test
      perfTest('Twain', commit, 497999, twain_test, db)
      # run fixed-string Norvig corpus test
      perfTest('Norvig', commit, 687628, norvig_test, db)

    # run long tests in parallel
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
