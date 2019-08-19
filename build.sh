#!/bin/bash -ex

. jenkins-setup/build_config.sh

./bootstrap.sh

LLG_SUBMODULE=vendors/liblightgrep

if [ ! -d "$LLG_SUBMODULE" ]; then
  git clone ssh://git@stash.strozfriedberg.com/asdf/liblightgrep.git $LLG_SUBMODULE
fi

pushd vendors/liblightgrep
git checkout $BRANCH_NAME || git checkout master
popd

DEPS_FLAGS="--with-liblightgrep-headers=vendors/liblightgrep/include"

build_it
install_it
