#!/bin/bash -ex

. .world/build_config.sh

if [ "$Target" = 'windows' ]; then
  MAKE_FLAGS+=' LOG_COMPILER=wine'
fi

make_it
make_check_it
