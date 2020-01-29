#!/bin/bash
# See `config/jenkins/template/README.txt` for more information

DIR=`dirname \`readlink -f $BASH_SOURCE\``
source "$DIR/../helpers.bash"

checkEnvVarDefinition BUILD_THREADS

make -j $BUILD_THREADS
