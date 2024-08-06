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

#
# Expects patterns on stdin, one per line, and sample count n and size k as
# arguments. Prints n lines of k tab-separated patterns, chosen uniformly
# without replacement within each line from the patterns given on stdin.
#

import random
import sys


def main():
    pats = map(lambda s: s.rstrip('\n'), sys.stdin.readlines())
    scount = int(sys.argv[1])
    ssize = int(sys.argv[2])

    for x in range(0, scount):
        print('\t'.join(random.sample(pats, ssize)))

    return 0


if __name__ == "__main__":
    sys.exit(main())

