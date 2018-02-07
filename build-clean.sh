#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)

echo "cleaning..."

pushd $THISDIR >/dev/null

rm -rf \
	aclocal.m4 ar-lib autom4te.cache \
	build build.log \
	compile configure config.guess config.sub config.h.in config.log config.status \
	depcomp .deps */.deps \
	install-sh install.sh \
	ltmain.sh \
	m4 Makefile Makefile.in */Makefile */Makefile.in */*/Makefile.in missing \
	test-driver \
	*/*.o */*/*.o
sts=$?

popd >/dev/null

exit $sts
