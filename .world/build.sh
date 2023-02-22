#!/bin/bash -ex

. .world/build_config.sh

if [ "$Target" = 'windows' ]; then
  MAKE_FLAGS+=' LOG_COMPILER=wine'
fi

make_it

if [[ "$Target" == 'windows' && "$Linkage" == 'static' ]]; then
  # Installed wine cannot run the test executable; skip it for now
  # See https://bugzilla.redhat.com/show_bug.cgi?id=2108032
  exit 0
fi

make_check_it
