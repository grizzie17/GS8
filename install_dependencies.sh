#!/bin/bash

PFX=""
AUTOTOOLS="autoconf autoconf-archive automake cmake intltool libtool make"

if [ -n "$(command -v apt-get)" ]; then
	PACKAGES="libfreetype6 libfreetype6-dev libftgl2 libftgl-dev freeglut3 freeglut3-dev valgrind libgtk-3-dev"
	dpkg -s $PACKAGES $AUTOTOOLS &> /dev/null
	if [ 0 -ne $? ]; then
		echo "installing packages"
		apt-get install $PACKAGES $AUTOTOOLS
	fi
elif [ -n "$(command -v yum)" ]; then
	sudo yum install gtk2-devel wxGTK-devel gtk+ glib2-devel cmake clang
elif [ -n "$(command -v pacman)" ]; then
	PFX="mingw-w64-x86_64-"
	PFXD="mingw-w64-x86-64-"
	pacman -S -yy \
		base-devel \
		$AUTOTOOLS \
		pkgconfig \
		libutil-linux-devel \
		${PFX}gnutls \
		${PFX}boost \
		${PFX}python2 ${PFX}python3 \
		${PFX}gtk2 ${PFX}gtk3 \
		${PFX}clang ${PFX}glib2 \
		${PFX}dlfcn \
		${PFX}freeglut ${PFX}freetype ${PFX}ftgl
else
	echo "no recognized package manager"
fi
