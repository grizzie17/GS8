#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


#$THISDIR/build-clean.sh  ||  exit $?
#$THISDIR/build-config.sh  ||  exit $?


function tweak_paths_for_windows() {
	cat -  | \
		sed \
			-e ':x; s@[^/][^/]*/\.\./@@;t x' \
			-e ':y; s@^\.\./@@g; t y' \
			-e "s@$THISDIR/@@g"
}


pushd $THISDIR/build >/dev/null

mkdir -p bin
mkdir -p lib

make -j 4 2>&1  |  tee ./build.log  | tweak_paths_for_windows

popd >/dev/null
