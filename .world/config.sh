#!/bin/bash -ex

. .world/build_config.sh

if [ "$Target" != 'macos']; then
  CHECK_TARGET=check-valgrind
fi

configure_it
