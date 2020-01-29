#!/bin/bash
# See `config/jenkins/template/README.txt` for more information

DIR=`dirname \`readlink -f $BASH_SOURCE\``
source "$DIR/../helpers.bash"

make package
