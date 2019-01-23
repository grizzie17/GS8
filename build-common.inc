#!/bin/bash

case `uname -o` in
[Mm]sys | cygwin* )
	export ARCH="x86_64-w64-mingw32"
	export ARCH_PREFIX="${ARCH}-"
	export CC="${ARCH_PREFIX}gcc"
	export CXX="${ARCH_PREFIX}g++"
	export CXXFLAGS="-g -ggdb -O0"
	export CPPFLAGS="-D_DEBUG"
	export LDFLAGS="-g -ggdb -Wl,--discard-none -Wl,--gc-keep-exported -L/mingw64/$ARCH/lib"
	;;
esac
