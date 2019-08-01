#!/bin/bash -ex

. jenkins-setup/build_config.sh

./bootstrap.sh

CHECK_TARGET=check-valgrind
build_it
install_it

mkdir -p $INSTALL/lib/python
cp pylightgrep/lightgrep.py $INSTALL/lib/python

if [ $Target = 'linux' -a $Linkage = 'shared' ]; then
  ln -fsr $INSTALL/lib/liblightgrep.so.0.0.0 $INSTALL/lib/liblightgrep.so.0
  ln -fsr $INSTALL/lib/liblightgrep.so.0.0.0 $INSTALL/lib/liblightgrep.so.0.0
fi
