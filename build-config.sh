#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh

pushd $THISDIR >/dev/null

	mkdir -p $THISDIR/m4  ||  exit 1

	echo "aclocal..."
	aclocal -I m4 --install  ||  exit 1

	echo "autoconf..."
	autoconf -f  ||  exit 1

	echo "automake..."
	automake --add-missing  ||  exit 2

	echo "configure..."
	export WIN64=1
	export _WIN64=1
	export CPPFLAGS="-DWIN64 -D_WIN64"
	mkdir -p $THISDIR/build  ||  exit 3
	pushd $THISDIR/build >/dev/null
		$THISDIR/configure  ||  exit 3
	popd >/dev/null


popd >/dev/null

