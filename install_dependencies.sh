#!/bin/bash

if [ -n "$(command -v apt-get)" ]; then
	PACKAGES="libfreetype6 libfreetype6-dev libftgl2 libftgl-dev freeglut3 freeglut3-dev valgrind libgtk-3-dev"
	dpkg -s $PACKAGES &> /dev/null
	if [ 0 -ne $? ]; then
		apt-get install $PACKAGES
	fi
elif [ -n "$(command -v yum)" ]; then
	sudo yum install gtk2-devel wxGTK-devel gtk+ glib2-devel cmake clang
elif [ -n "$(command -v pacman)" ]; then
	PFX="mingw-w64-x86_64-" 
	pacman -S -yy ${PFX}gtk2 ${PFX}gtk3 cmake ${PFX}clang ${PFX}glib2 ${PFX}freeglut ${PFX}freetype ${PFX}ftgl ${PFX}glib2
else
	echo "no recognized package manager"
fi

