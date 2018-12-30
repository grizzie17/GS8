#!/bin/bash
#
#	Generation of the autotools configure file
#
THISFILE="${BASH_SOURCE[0]}"
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)
THISSCRIPT=`basename $THISFILE`

CONFIGURE_D=$THISDIR


ARCH_PREFIX=""
case `uname -o` in
[Mm]sys )
	ARCH_PREFIX="x86_64-w64-mingw32-"
	;;
esac

export ACLOCAL=aclocal
export AUTOCONF=autoconf
export AUTOHEADER=autoheader
export AUTOMAKE=automake
export AUTOPOINT=autopoint
export AUTORECONF=autoreconf
export INTLTOOLIZE=intltoolize
export LIBTOOLIZE=libtoolize
export PKGCONFIG=pkg-config
export MKDIR=mkdir



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
	local fullcmd
	local var
	local ver

	fullcmd=`which $ARCH_PREFIX$cmd 2>/dev/null`
	sts=$?
	if [ 0 -ne $sts ]; then
		fullcmd=`which $cmd`
		sts=$?
	fi

	#echo "fullcmd=$fullcmd" >&2

	if [ 0 -eq $sts ]; then
		ver=`$fullcmd --version | head -1 | sed -r -e 's/^.*[^0-9.]([0-9][0-9.]*)/\1/'`
		sts=$?
		if [ 0 -eq $sts ]; then
			var=`echo "$cmd" | tr '[a-z]' '[A-Z]' | sed -e 's/-//g'`
			eval export $var=$fullcmd
			eval export ${var}_V=$ver
			#echo "$var=${!var}" >&2
		else
			fatal $sts "command does not know about version option: $cmd"
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
assertCmd $ACLOCAL
assertCmd $AUTOCONF
assertCmd $AUTOHEADER
assertCmd $AUTOMAKE
assertCmd $AUTOPOINT
assertCmd $AUTORECONF
assertCmd $LIBTOOLIZE
assertCmd $INTLTOOLIZE
assertCmd $PKGCONFIG
assertCmd $MKDIR

# echo "ACLOCAL=$ACLOCAL"
# echo "AUTOCONF=$AUTOCONF"
# echo "AUTOHEADER=$AUTOHEADER"
# echo "AUTOMAKE=$AUTOMAKE"
# echo "AUTOPOINT=$AUTOPOINT"
# echo "AUTORECONF=$AUTORECONF"
# echo "LIBTOOLIZE=$LIBTOOLIZE"
# echo "INTLTOOLIZE=$INTLTOOLIZE"
# echo "PKGCONFIG=$PKGCONFIG"
# echo "MKDIR=$MKDIR"

## autoheader ##
need_autoheader=no
grep '^[ \t]*A[CM]_CONFIG_HEADER' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_autoheader=yes

## automake ##
need_automake=no
grep '^[ \t]*AM_INIT_AUTOMAKE' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_automake=yes

## autopoint ##
need_autopoint=no
grep '^[ \t]*AM_GNU_GETTEXT_VERSION' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_autopoint=yes

## intltoolize ##
need_intltoolize=no
grep '^[ \t]*AC_PROG_INTLTOOL' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_intltoolize=yes

## libtoolize ##
need_libtoolize=no
grep '^[ \t]*LT_INIT' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_libtoolize=yes
grep '^[ \t]*AC_PROG_LIBTOOL' $CONFIGURE_F  &>/dev/null
[ 0 -eq $? ]  &&  need_libtoolize=yes


pushd $CONFIGURE_D >/dev/null

	if [ "Xyes" = "X$need_autopoint" ]; then
		echo "...autopoint... $AUTOPOINT_V"
		$AUTOPOINT --force  ||  fatal $? "autopoint exited with an error"
	fi

	#second aclocal to get around problem with aclocal 1.15
	echo "...aclocal... $ACLOCAL_V"
	mkdir -p $CONFIGURE_D/m4  ||  fatal $? "unable to make $CONFIGURE_D/m4"
	$ACLOCAL -I m4 --install 2>/dev/null  ||  echo "...:::aclocal rerun..."  &&  $ACLOCAL -I m4  ||  fatal $? "aclocal exited with an error"

	if [ "Xyes" = "X$need_libtoolize" ]; then
		echo "...libtoolize... $LIBTOOLIZE_V"
		$LIBTOOLIZE --automake -c --force  ||  fatal $? "libtoolize exited with an error"
	fi

	if [ "Xyes" = "X$need_autoheader" ]; then
		echo "...autoheader... $AUTOHEADER_V"
		$AUTOHEADER --force  ||  fatal $? "autoheader exited with an error"
	fi

	if [ "Xyes" = "X$need_automake" ]; then
		echo "...automake... $AUTOMAKE_V"
		export AUTOMAKE_JOBS=4
		$AUTOMAKE --add-missing --copy --force-missing  ||  fatal $? "automake exited with an error"
	fi

	echo "...autoconf... $AUTOCONF_V"
	$AUTOCONF --force  ||  fatal $? "autoconf exited with an error"

	if [ "Xyes" = "X$need_intltoolize" ]; then
		echo "...intltoolize... $INTLTOOLIZE_V"
		$INTLTOOLIZE --automake  ||  fatal $? "intltoolize exited with an error"
	fi

	[ -e configure ]  ||  fatal $? "failed to create required file: configure"

popd >/dev/null

exit 0
