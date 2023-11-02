#!/usr/bin/env bash -e

for i in $(seq 1 10) ; do
  src/cmd/lightgrep -k pytest/keys/twain.txt --verbose pytest/corpora/marktwainworks.txt 2>&1 >/dev/null
done | python3 pytest/lightgrep_stats.py