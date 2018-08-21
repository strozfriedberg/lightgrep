#!/bin/bash -ex

. $HOME/vendors/build_config.sh

clean_it

./bootstrap.sh

build_it
install_it

if [ $Target = 'linux' -a $Linkage = 'shared' ]; then
  ln -fsr $INST/lib/liblightgrep.so.0.0.0 $INST/lib/liblightgrep.so.0
  ln -fsr $INST/lib/liblightgrep.so.0.0.0 $INST/lib/liblightgrep.so.0.0
fi

case "$Target" in
linux)
  STAGE='src/lib/.libs/liblightgrep.so*'
  ;;

windows)
  case "$Linkage" in
  shared*)
    DLL='src/lib/.libs/liblightgrep.dll'
    STAGE="$DLL $($VENDORS/gather.sh $DLL $MINGW_ROOT/bin $DEPS/bin)"
    ;;
  static)
    STAGE='src/lib/.libs/liblightgrep.a'
    ;;
  esac
  ;;
esac

STAGE+=' pylightgrep/lightgrep.py'

archive_it
