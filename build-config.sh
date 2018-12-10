#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh


pushd $THISDIR >/dev/null

	$THISDIR/autogen.sh  ||  exit $?


	mkdir -p $THISDIR/build  ||  exit $?
	mkdir -p $THISDIR/build/lib  ||  exit $?
	pushd $THISDIR/build >/dev/null
		#export CXXFLAGS="-g -ggdb -O0"
		#export LDFLAGS="-g -ggdb -Wl,--discard-none -Wl,--gc-keep-exported"
		$THISDIR/configure --enable-debug  --prefix=$THISDIR/build  ||  exit $?
		case `uname -o` in
		[Mm]sys | cygwin* )
			echo "patching libtool"
			sed -e 's/ _spawnv / spawnv /g' -i libtool  ||  exit $?
			patch $THISDIR/test-driver < $THISDIR/build-patches/test-driver.patch  ||  exit $?
			;;
		esac
	popd >/dev/null


popd >/dev/null

echo "Complete..."
exit 0
