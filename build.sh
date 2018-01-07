#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh  ||  exit $?
$THISDIR/build-config.sh  ||  exit $?


pushd $THISDIR >/dev/null

make -j 4

popd >/dev/null
