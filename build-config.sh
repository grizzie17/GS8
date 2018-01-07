#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh

pushd $THISDIR >/dev/null

mkdir -p m4

echo "aclocal..."
aclocal -I m4 --install  ||  exit 1

echo "autoconf..."
autoconf -f  ||  exit 1

echo "automake..."
automake --add-missing  ||  exit 2

echo "configure..."
#export CPPFLAGS="-DWIN64 -D_WIN64"
./configure  ||  exit 3


popd >/dev/null

