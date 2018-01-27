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

export CPPFLAGS="\
	-DWIN64 -D_WIN64 \
	-I/C/msys64/usr/include \
	-I/C/msys64/usr/include/w32api \
	-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include \
	-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include/c++ \
	-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include/c++/x86_64-pc-msys \
	-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include/c++/backward \
"
make -j 4 2>&1  |  tee ./build.log  | tweak_paths_for_windows

popd >/dev/null
