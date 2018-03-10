#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh


pushd $THISDIR >/dev/null

	echo "libtoolize..."
	libtoolize  ||  exit $?

	mkdir -p $THISDIR/m4  ||  exit $?

	#second aclocal to get around problem with aclocal 1.15
	echo "aclocal..."
	aclocal -I m4 --install 2>/dev/null  ||  aclocal -I m4  ||  exit $?

	echo "autoconf..."
	autoconf -f  ||  exit $?

	echo "automake..."
	automake --add-missing  ||  exit $?

	echo "configure..."

	case `uname -o` in
	Msys | MSYS | msys )
		echo "...WIN64"
		export CPPFLAGS="-DWIN64"
		;;
	*[Ll]inux )
		echo "...linux"
		#export CPPFLAGS="-DLINUX -DLinux -Dlinux"
		;;
	* )
		echo "...undefined"
		;;
	esac
	mkdir -p $THISDIR/build  ||  exit $?
	pushd $THISDIR/build >/dev/null
		$THISDIR/configure --prefix=$THISDIR/build  ||  exit $?
	popd >/dev/null


popd >/dev/null

echo "Complete..."
exit 0

