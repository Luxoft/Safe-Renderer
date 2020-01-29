#!/bin/bash
# See `config/jenkins/template/README.txt` for more information

DIR=`dirname \`readlink -f $BASH_SOURCE\``
source "$DIR/../helpers.bash"

checkEnvVarDefinition COV_ARGS
checkEnvVarDefinition BUILD_THREADS

$COV_ARGS make -j $BUILD_THREADS
