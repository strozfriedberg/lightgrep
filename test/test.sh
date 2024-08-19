#!/bin/bash -ex

if hash parallel ; then
  jobs=$([ $(uname) = 'Darwin' ] && sysctl -n hw.logicalcpu_max || nproc)

  # RANDOM is only 15 bits; this gets us 32
  seed=$(( ($RANDOM << 17) | ($RANDOM << 2) | ($RANDOM & 0x03) ))

  # Catch2 supports test sharding. We run tests as $jobs shards, and
  # randomize test order to catch non-isolation of tests and make it
  # likely that the slowest tests are spread across the shards. So that
  # each shard agrees with the others about how the tetst are divided,
  # each shard needs to know its own index and the RNG seed. Despite the
  # test order being random each time, the test order is fully
  # reproducible in case of a fault because Catch2 prints the seed used.

  parallel -t test/test --shard-count $jobs --shard-index {} --order rand --rng-seed $seed ::: $(seq 0 $(($jobs - 1)))

else
  test/test
fi
