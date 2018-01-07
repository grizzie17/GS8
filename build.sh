#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)

rm -rf aclocal.m4 ar-lib autom4te.cache compile configure config.log config.status depcomp */.deps install-sh install.sh m4 Makefile Makefile.in */Makefile */Makefile.in missing

mkdir -p m4

echo "aclocal..."
aclocal -I m4 --install  ||  exit 1

echo "autoconf..."
autoconf -f  ||  exit 1

echo "automake..."
automake --add-missing  ||  exit 2

echo "configure..."
export CPPFLAGS="-DWIN64 -D_WIN64"
./configure




