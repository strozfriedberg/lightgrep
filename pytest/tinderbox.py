#!/usr/bin/python

import os
import subprocess
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
long_test_single = [ test_bin, '--long-test' ]

bzcat_bin = 'bzcat'
long_test_single_bzcat = [ bzcat_bin, 're_gen/aQ-3.bz2' ]
long_test_triple_bzcat = [ bzcat_bin, 're_gen/aQ-3-3.bz2' ]

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
      
    # run single-pattern long test
    p1 = subprocess.Popen(long_test_single_bzcat, bufsize=-1, stdout=subprocess.PIPE)
    p2 = subprocess.Popen(long_test_single, bufsize=-1, stdin=p1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    
    single_pattern_tests = [] 
#    for line in p2.communicate()[0].split('\n'):
#      if line.endswith('falied!'):
#        single_pattern_tests.append(line)
#        single_pattern_tests.append(next(line))
#        single_pattern_tests.append(next(line))

    print gcc_warnings
    print unit_tests
    print single_pattern_tests

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
