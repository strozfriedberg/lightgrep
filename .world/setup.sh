#!/bin/bash -ex

. .world/build_config.sh

./bootstrap.sh

mvn wrapper:wrapper
