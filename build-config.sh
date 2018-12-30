#!/bin/bash
THISFILE=${BASH_SOURCE[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh


pushd $THISDIR >/dev/null

	case `uname -o` in
	[Mm]sys | cygwin* )
		export CC="x86_64-w64-mingw32-gcc"
		export CXX="x86_64-w64-mingw32-g++"
		export CXXFLAGS="-g -ggdb -O0"
		export LDFLAGS="-g -ggdb -Wl,--discard-none -Wl,--gc-keep-exported"
		;;
	esac
	$THISDIR/autogen.sh  ||  exit $?


	mkdir -p $THISDIR/build  ||  exit $?
	mkdir -p $THISDIR/build/lib  ||  exit $?
	pushd $THISDIR/build >/dev/null
		echo ":::configure:::"
		$THISDIR/configure  --prefix=$THISDIR/build  ||  exit $?
		case `uname -o` in
		[Mm]sys | cygwin* )
			echo "patching libtool for Msys"
			sed -e 's/ _spawnv / spawnv /g' -i libtool  ||  exit $?
			echo "patching test-driver"
			patch $THISDIR/test-driver < $THISDIR/build-patches/test-driver.patch  ||  exit $?
			;;
		esac
	popd >/dev/null


popd >/dev/null

echo "Complete..."
exit 0
