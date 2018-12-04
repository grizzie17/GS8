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


pushd $THISDIR/build/Gadget >/dev/null

mkdir -p bin
mkdir -p lib


case `uname -s` in
Msys | MSYS | msys | CYGWIN* )
	echo "...WIN64"
	export CPPFLAGS="-DWIN64"
	function tweak_paths() {
		cat -  | \
			sed \
				-e ':x; s@[^/][^/]*/\.\./@@;t x' \
				-e ':y; s@^\.\./@@g; t y' \
				-e "s@$THISDIR/@@g"
	}
	;;
[Ll]inux )
	echo "...linux"
	#export CPPFLAGS="-DLINUX -DLinux -Dlinux"
	function tweak_paths() {
		cat -
	}
	;;
* )
	echo "...undefined"
	;;
esac
make -j 4 2>&1  |  tee ./build.log  | tweak_paths

popd >/dev/null
