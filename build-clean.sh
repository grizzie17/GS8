#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)

pushd $THISDIR >/dev/null

rm -rf \
	aclocal.m4 ar-lib autom4te.cache \
	compile configure config.log config.status \
	depcomp .deps */.deps \
	install-sh install.sh \
	m4 Makefile Makefile.in */Makefile */Makefile.in missing \
	*/*.o */*/*.o
sts=$?

popd >/dev/null

exit $sts
