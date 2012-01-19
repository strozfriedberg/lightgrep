#!/usr/bin/python

import os
import sqlite3
import sys

def main():
  dbfile = sys.argv[1]

  perf_schema = \
    'CREATE TABLE perf ( \
      git TEXT, \
      test_name TEXT, \
      seconds REAL, \
      task_clock REAL, \
      context_switches INTEGER, \
      CPU_migrations INTEGER, \
      page_faults INTEGER, \
      cycles INTEGER, \
      stalled_cycles_frontend INTEGER, \
      stalled_cycles_backend INTEGER, \
      instructions INTEGER, \
      branches INTEGER, \
      branch_misses INTEGER, \
      L1_dcache_loads INTEGER, \
      L1_dcache_load_misses INTEGER, \
      LLC_loads INTEGER, \
      LLC_load_misses INTEGER, \
      PRIMARY KEY (git, test_name) \
    )'

  commit_schema = \
    'CREATE TABLE commits ( \
      git TEXT PRIMARY KEY, \
      timestamp INTEGER \
    )'

  try:
    with sqlite3.connect(dbfile) as db:
      db.execute(commit_schema)
      db.execute(perf_schema)
  except:
    os.unlink(dbfile)
    raise

if __name__ == "__main__":
  main()
