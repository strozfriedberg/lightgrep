#!/bin/bash -e

if [ -e src/lib/.libs/liblightgrep.so ]; then
  LIBS=$(realpath src/lib/.libs)
  pushd pylightgrep
  LD_LIBRARY_PATH=$LIBS:$LD_LIBRARY_PATH python3 -m unittest -v
  popd
fi
