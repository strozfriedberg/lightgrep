#!/bin/bash -ex

. .world/build_config.sh

install_it

mkdir -p $INSTALL/lib/python
cp pylightgrep/lightgrep.py $INSTALL/lib/python

if [ $Target = 'linux' -a $Linkage = 'shared' ]; then
  ln -fsr $INSTALL/lib/liblightgrep.so.0.0.0 $INSTALL/lib/liblightgrep.so.0
  ln -fsr $INSTALL/lib/liblightgrep.so.0.0.0 $INSTALL/lib/liblightgrep.so.0.0
  cp -av src/java/target/jlightgrep-0.0.1.jar $INSTALL
fi
