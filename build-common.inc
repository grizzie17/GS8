#!/bin/bash

XMACHINE=`uname -m`

case `uname -o` in
[Mm]sys | cygwin* )
	case "$XMACHINE" in
	*64* )
		MINGX="mingw64"
		WXX="w64"
		;;
	* )
		MINGX="mingw32"
		WXX="w32"
		;;
	esac
	export ARCH="${XMACHINE}-${WXX}-mingw32"
	export ARCH_PREFIX="${ARCH}-"
	export CC="${ARCH_PREFIX}gcc"
	export CXX="${ARCH_PREFIX}g++"
	export CXXFLAGS="-g -ggdb -O0"
	export CPPFLAGS="-D_DEBUG"
	#export LDFLAGS="-g -ggdb -Wl,--discard-none -Wl,--gc-keep-exported -L/$MINGX/$ARCH/lib"
	export LDFLAGS="-g -ggdb -L/$MINGX/$ARCH/lib"
	;;
esac
unset MINGX
unset WXX
unset XMACHINE

echo "ARCH=$ARCH"
echo "LDFLAGS=$LDFLAGS"

