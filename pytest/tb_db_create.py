#!/usr/bin/python

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
