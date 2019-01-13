#!/bin/bash

case `uname -o` in
[Mm]sys | cygwin* )
	export CC="x86_64-w64-mingw32-gcc"
	export CXX="x86_64-w64-mingw32-g++"
	export CXXFLAGS="-g -ggdb -O0"
	export CPPFLAGS="-D_DEBUG"
	export LDFLAGS="-g -ggdb -Wl,--discard-none -Wl,--gc-keep-exported"
	;;
esac
