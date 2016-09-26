#!/usr/bin/bash -e

for i in $(seq 1 10) ; do
  src/cmd/lightgrep -k pytest/keys/twain.txt --no-output 10x-twain.txt 2>&1 | grep -Po '.*(?= searchTime)'
done
