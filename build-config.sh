#!/bin/bash
THISFILE=${BASH_SOURCE[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


case "$1" in
-c | --clean )
	$THISDIR/build-clean.sh
	;;
esac



source $THISDIR/build-common.inc


pushd $THISDIR >/dev/null

	$THISDIR/autogen.sh  ||  exit $?


	mkdir -p $THISDIR/build  ||  exit $?
	mkdir -p $THISDIR/build/lib  ||  exit $?
	pushd $THISDIR/build >/dev/null
		echo ":::configure:::"
		$THISDIR/configure  ||  exit $?
		case `uname -o` in
		[Mm]sys | cygwin* )
			#echo "patching libtool for Msys"
			#sed -e 's/ _spawnv / spawnv /g' -i libtool  ||  exit $?
			echo "patching test-driver"
			patch $THISDIR/test-driver < $THISDIR/build-patches/test-driver.patch  ||  exit $?
			;;
		esac
	popd >/dev/null


popd >/dev/null

echo "Complete..."
exit 0
