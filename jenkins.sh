#!/bin/bash -ex

git clone ssh://git@stash.strozfriedberg.com/asdf/jenkins-setup.git
pushd jenkins-setup
git checkout ASDF-2013
popd
. jenkins-setup/build_config.sh

unpack_deps

./bootstrap.sh

git clone ssh://git@stash.strozfriedberg.com/asdf/liblightgrep.git vendors/liblightgrep
pushd vendors/liblightgrep
git checkout $BRANCH_NAME || git checkout master
popd

DEPS_FLAGS="--with-liblightgrep-headers=vendors/liblightgrep/include"

build_it
install_it
gather_deps
archive_it_ex
