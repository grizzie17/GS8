#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)

echo "cleaning..."

pushd $THISDIR >/dev/null


	for f in `find $THISDIR -name Makefile.am`
	do
		x="${f%.am}"
		[ -e "$x" ]  &&  rm -f $x
		x="$x.in"
		[ -e "$x" ]  &&  rm -f $x
	done

	rm -rf \
		aclocal.m4 ar-lib autom4te.cache \
		build \
		compile configure config.guess config.sub config.log config.status config.h.in \
		depcomp .deps */.deps \
		install-sh install.sh \
		ltmain.sh \
		m4 missing \
		test-driver \
		*/*.o */*/*.o
	sts=$?

popd >/dev/null

exit $sts
