#!/usr/bin/env bash -e

for i in $(seq 1 10) ; do
  src/cmd/lightgrep -k pytest/keys/twain.txt --no-output pytest/corpora/marktwainworks.txt 2>&1
done | python3 pytest/lightgrep_stats.py
