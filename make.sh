#!/bin/bash

if [ -r /proc/cpuinfo ]; then
	CORES=`grep "^core id" /proc/cpuinfo | wc -l`
	#echo Jobs=$CORES
else
	CORES=2
fi

cd $(dirname "$0")


make -j $CORES -f Makefile.mk $@
echo Jobs=$CORES

