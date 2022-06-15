#!/bin/bash -ex

. .world/build_config.sh

if [ "$Target" != 'macos' ]; then
  CHECK_TARGET=check-valgrind
fi

if [ $Target = 'windows' ]; then
  LDFLAGS+=' -fstack-protector'
fi

CONF_FLAGS+=' --enable-python --enable-java'

configure_it
