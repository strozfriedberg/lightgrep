#!/bin/bash -ex

. $HOME/vendors/build_config.sh

clean_it

./bootstrap.sh

# FIXME: match branch
git clone -b master ssh://git@stash.strozfriedberg.com/asdf/liblightgrep.git vendors/liblightgrep

DEPS_FLAGS="--with-liblightgrep-headers=vendors/liblightgrep/include"

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
