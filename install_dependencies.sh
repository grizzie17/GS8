#!/bin/bash

	if [ -n "$(command -v apt-get)" ]; then
		PACKAGES="libfreetype6 libfreetype6-dev libftgl2 libftgl-dev freeglut3 freeglut3-dev valgrind libgtk-3-dev"
		dpkg -s $PACKAGES &> /dev/null
		if [ 0 -ne $? ]; then
			apt-get install $PACKAGES
		fi
	elif [ -n "$(command -v yum)" ]; then
		sudo yum install gtk2-devel wxGTK-devel gtk+ glib2-devel cmake clang
	fi

