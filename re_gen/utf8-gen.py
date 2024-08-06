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

import re
import sys


def main():
    for cp in xrange(0x01, 0x09):
        print_test(cp)

    # skip \t, we use it as a separator between patterns
    # and the text so it can't appear in the text

    for cp in xrange(0x10,0x110000):
        print_test(cp)


def print_test(cp):
    bytes = unichr(cp).encode('UTF-8')
#  pat = re.escape(bytes)
    pat = escape(bytes)
    text = '%s%s' % ((bytes, 'x') if cp % 2 else ('x', bytes))
    print('%s\t0\t0\tUTF-8\t%s' % (pat, text))

def escape(pat):
    return re.sub('([.*+?[\\\\|()])', '\\\\\g<1>', pat)

if __name__ == "__main__":
    sys.exit(main())
