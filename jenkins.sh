#!/bin/bash -ex

. $HOME/vendors/build_config.sh

clean_it

./bootstrap.sh

DEPS_FLAGS="--with-liblightgrep-headers=$HOME/jobs/liblightgrep/workspace/include"

build_it

case "$Target" in
linux)
  STAGE='src/cmd/lightgrep'
  ;;

windows)
  case "$Linkage" in
  shared)
    EXES='src/cmd/.libs/lightgrep.exe'
    STAGE="$EXES $($VENDORS/gather.sh $EXES $MINGW_ROOT/bin $DEPS/bin)"
    ;;
  static)
    EXES='src/cmd/lightgrep.exe'
    check_static $EXES
    STAGE="$EXES"
    ;;
  esac
  ;;
esac

archive_it
