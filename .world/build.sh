#!/bin/bash -ex

. .world/build_config.sh

if [ "$Target" = 'windows' ]; then
  MAKE_FLAGS+=' LOG_COMPILER=.world/wine_wrapper.sh'
fi

make_it

if [[ "$Target" == 'windows' && "$Linkage" == 'static' ]]; then
  # Installed wine cannot run the test executable; skip it for now
  # See https://bugzilla.redhat.com/show_bug.cgi?id=2108032
  exit 0
fi

make_check_it

if [[ "$Target" == 'linux' && "$Linkage" == 'shared' ]]; then
  # Build a Python wheel
  VENV=.venv
  if [[ "$Target" == 'windows' ]]; then
    PYTHON=python
    VENVBIN=Scripts
  else
    PYTHON=python3
    VENVBIN=bin
  fi

  pushd pylightgrep
  $PYTHON -m venv $VENV
  . "$VENV/$VENVBIN/activate"
  pip install build
  $PYTHON -m build -w
  deactivate
  popd
fi
