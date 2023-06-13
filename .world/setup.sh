#!/bin/bash -ex

. .world/build_config.sh

./bootstrap.sh

pushd src/java
mvn wrapper:wrapper
popd
