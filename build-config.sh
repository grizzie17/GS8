#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


$THISDIR/build-clean.sh


pushd $THISDIR >/dev/null

	echo "libtoolize..."
	libtoolize  ||  exit $?

	mkdir -p $THISDIR/m4  ||  exit $?

	echo "aclocal..."
	aclocal -I m4 --install  ||  exit 1

	echo "autoconf..."
	autoconf -f  ||  exit 1

	echo "automake..."
	automake --add-missing  ||  exit 2

	echo "configure..."

	case `uname -o` in
	Msys )
		echo "...WIN64"
		export CPPFLAGS="\
			-DWIN64 -D_WIN64 \
			-D__STDC_WANT_SECURE_LIB__=1 \
			-I/C/msys64/usr/include \
			-I/C/msys64/usr/include/w32api \
			-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include \
			-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include/c++ \
			-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include/c++/x86_64-pc-msys \
			-I/C/msys64/usr/lib/gcc/x86_64-pc-msys/6.4.0/include/c++/backward \
		"
		;;
	*[Ll]inux )
		echo "...linux"
		export CPPFLAGS="\
			-DLINUX -DLinux -Dlinux \
			-I/usr/include \
			-I/usr/include/c++/5.4.0 \
		"
		;;
	* )
		echo "...undefined"
		;;
	esac
	mkdir -p $THISDIR/build  ||  exit 3
	pushd $THISDIR/build >/dev/null
		$THISDIR/configure --prefix=$THISDIR/build  ||  exit 3
	popd >/dev/null


popd >/dev/null

