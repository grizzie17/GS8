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


	case `uname -o` in
	Msys )
		echo "...WIN64"
		export CPPFLAGS="\
			-DWIN64 -D_WIN64 \
		"
		;;
	*[Ll]inux )
		echo "...linux"
		export CPPFLAGS="\
			-DLINUX -DLinux -Dlinux \
		"
		;;
	* )
		echo "...undefined"
		;;
	esac
make -j 4 2>&1  |  tee ./build.log  | tweak_paths_for_windows

popd >/dev/null
