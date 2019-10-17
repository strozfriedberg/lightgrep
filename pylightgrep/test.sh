#!/bin/bash -e

if [ -e src/lib/.libs/liblightgrep.so ]; then
  LD_LIBRARY_PATH=src/lib/.libs:$LD_LIBRARY_PATH pylightgrep/test.py -v
fi
