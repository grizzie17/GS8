#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh


pushd $THISDIR >/dev/null

	$THISDIR/autogen.sh

	
	mkdir -p $THISDIR/build  ||  exit $?
	pushd $THISDIR/build >/dev/null
		$THISDIR/configure --prefix=$THISDIR/build  ||  exit $?
		case `uname -o` in
		[Mm]sys | cygwin* )
			sed -e 's/ _spawnv / spawnv /g' -i libtool
			;;
		esac
	popd >/dev/null


popd >/dev/null

echo "Complete..."
exit 0

