#!/bin/bash
#
#	Generation of the autotools configure file
#
THISFILE="${BASH_SOURCE[0]}"
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)
THISSCRIPT=`basename $THISFILE`

CONFIGURE_D=$THISDIR


# tell about a problem and then exit
function fatal()
{
	local sts=1

	echo "$1" | grep '^[0-9][0-9]*$' &>/dev/null
	if [ 0 -eq $? ]; then
		sts=$1
		shift
	fi
	echo "$THISSCRIPT - FATAL($sts): $*" >&2
	exit $sts
}

# make sure that the command exists and that it knows about its own version number
function assertCmd()
{
	local cmd="$1"
	local sts=0

	which "$cmd" &>/dev/null
	sts=$?
	if [ 0 -eq $sts ]; then
		$cmd --version | head -1 | sed -r -e 's/^.*[^0-9.]([0-9][0-9.]*)/\1/'
		sts=$?
		if [ 0 -ne $sts ]; then
			fatal $sts "command does not about version option: $cmd"
		fi
	else
		fatal $sts "unable to locate command: $cmd"
	fi
	return $sts
}


# find the current configure script
if [ -r $PWD/configure.ac ]; then
	CONFIGURE_D=$PWD
	CONFIGURE_F=$PWD/configure.ac
elif [ -r $THISDIR/configure.ac ]; then
	CONFIGURE_F=$THISDIR/configure.ac
elif [ -r $THISDIR/configure.in ]; then
	CONFIGURE_F=$THISDIR/configure.in
else
	fatal 1 "unable to locate configure.ac or configure.in"
fi

# assure the needed commands exist
LIBTOOLIZE_V=`assertCmd libtoolize`
ACLOCAL_V=`assertCmd aclocal`
AUTOCONF_V=`assertCmd autoconf`
AUTOHEADER_V=`assertCmd autoheader`
AUTOPOINT_V=`assertCmd autopoint`
AUTOMAKE_V=`assertCmd automake`
MKDIR_V=`assertCmd mkdir`

## autoheader ##
need_autoheader=no
grep '^[ \t]*A[CM]_CONFIG_HEADER' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_autoheader=yes

## automake ##
need_automake=no
grep '^[ \t]*AM_INIT_AUTOMAKE' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_automake=yes

## libtoolize ##
need_libtoolize=no
grep '^[ \t]*LT_INIT' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_libtoolize=yes

## autopoint ##
need_autopoint=no
grep '^[ \t]*AM_GNU_GETTEXT' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_autopoint=yes


pushd $CONFIGURE_D >/dev/null

	if [ "Xyes" = "X$need_libtoolize" ]; then
		echo "...libtoolize... $LIBTOOLIZE_V"
		libtoolize --automake -c --force  ||  fatal $? "libtoolize exited with an error"
	fi

	if [ "Xyes" = "X$need_autopoint" ]; then
		echo "...autopoint... $AUTOPOINT_V"
		autopoint --force  ||  fatal $? "autopoint exited with an error"
	fi

	mkdir -p $CONFIGURE_D/m4  ||  fatal $? "unable to make $CONFIGURE_D/m4"

	#second aclocal to get around problem with aclocal 1.15
	echo "...aclocal... $ACLOCAL_V"
	aclocal -I m4 --install 2>/dev/null  ||  echo "...:::aclocal rerun..."  &&  aclocal -I m4  ||  fatal $? "aclocal exited with an error"

	if [ "Xyes" = "X$need_autoheader" ]; then
		echo "...autoheader... $AUTOHEADER_V"
		autoheader  ||  fatal $? "autoheader exited with an error"
	fi

	echo "...autoconf... $AUTOCONF_V"
	autoconf -f  ||  fatal $? "autoconf exited with an error"

	if [ "Xyes" = "X$need_automake" ]; then
		echo "...automake... $AUTOMAKE_V"
		export AUTOMAKE_JOBS=4
		automake --add-missing --copy --force-missing  ||  fatal $? "automake exited with an error"
	fi

	[ -e configure ]  ||  fatal $? "failed to create required file: configure"

popd >/dev/null

exit 0
