#!/usr/bin/env python3
# encoding: utf-8

import sys
import statistics

from collections import defaultdict

def do_it():
    cols = defaultdict(list)
    for line in sys.stdin:
        fields = line.split(maxsplit=1)
        cols[fields[1].strip()].append(float(fields[0]))

    print('col\tmin\tmax\tavg\tharm\tmed\tvar')
    for col, vals in cols.items():
        if statistics.pvariance(vals) == 0.0:
            continue
        print('{}\t{:.6f}\t{:.6f}\t{:.6f}\t{:.6f}\t{:.6f}\t{:.6f}'.format(col,
                                                                            min(vals),
                                                                            max(vals),
                                                                            statistics.mean(vals),
                                                                            statistics.harmonic_mean(vals),
                                                                            statistics.median_low(vals),
                                                                            statistics.pvariance(vals)))

if __name__ == "__main__":
    do_it()
