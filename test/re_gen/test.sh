#!/bin/bash

export LD_LIBRARY_PATH=/home/uckelman/projects/lightbox/lightgrep/lib

SORT='-k 1n,2 -k 2n,3 -k 3n,4'

../../bin/test/test -c search $1 $2 2>/dev/null | sort $SORT >lg_results
./shitgrep $1 $2 2>/dev/null | sort $SORT >sg_results

diff sg_results lg_results
