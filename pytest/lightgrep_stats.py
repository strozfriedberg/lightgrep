#!/usr/bin/env python3
# encoding: utf-8

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
