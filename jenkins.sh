#!/bin/bash -ex

. jenkins-setup/build_config.sh

unpack_deps

./bootstrap.sh

build_it
install_it

mkdir -p $INST/lib/python
cp pylightgrep/lightgrep.py $INST/lib/python

if [ $Target = 'linux' -a $Linkage = 'shared' ]; then
  ln -fsr $INST/lib/liblightgrep.so.0.0.0 $INST/lib/liblightgrep.so.0
  ln -fsr $INST/lib/liblightgrep.so.0.0.0 $INST/lib/liblightgrep.so.0.0
fi

gather_deps
archive_it_ex
