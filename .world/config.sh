#!/bin/bash -ex

. .world/build_config.sh

if [ "$Target" != 'macos' ]; then
  CHECK_TARGET=check-valgrind
fi

if [ $Target = 'windows' ]; then
  LDFLAGS+=' -fstack-protector'
fi

if [ "$Target" = 'linux' -a "$Linkage" = 'shared' ]; then
  CONF_FLAGS+=' --enable-java'
fi

CONF_FLAGS+=' --enable-python'

configure_it
