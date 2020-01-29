#!/bin/bash
# See `config/jenkins/template/README.txt` for more information

DIR=`dirname \`readlink -f $BASH_SOURCE\``
source "$DIR/../helpers.bash"

checkEnvVarDefinition REPO_DIR
checkEnvVarDefinition BUILD_DIR
checkEnvVarDefinition BUILD_TYPE

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DUNIT_TESTS=OFF -DCOVERAGE=ON -DHMI_PROJECT_PATH=$REPO_DIR/test/database/Telltales $REPO_DIR
