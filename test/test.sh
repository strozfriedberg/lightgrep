#!/bin/bash -ex

if hash parallel ; then
  jobs=$(nproc)

  # RANDOM is only 15 bits; this gets us 32
  seed=$(( ($RANDOM << 17) | ($RANDOM << 2) | ($RANDOM & 0x03) ))

  parallel -t test/test --shard-count $jobs --shard-index {} --order rand --rng-seed $seed ::: $(seq 0 $(($jobs - 1)))

else
  test/test
fi
