#!/bin/bash
function checkEnvVarDefinition() {
    if [ -z "$1" ] ; then
        echo "No name of env. variable is given" 1>&2
        exit 2
    fi

    if [ -z "${!1}" ]; then
        echo "Env. variable ${1} isn't defined" 1>&2
        exit 1
    fi
}
