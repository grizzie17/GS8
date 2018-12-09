#!/bin/bash
THISFILE=${BASH_COMMAND[0]}
THISDIR=$(cd -P `dirname $THISFILE` && pwd -P)


#$THISDIR/build-clean.sh  ||  exit $?
#$THISDIR/build-config.sh  ||  exit $?


ARG="$1"
ARGDIR=""
ARGFILE=""

if [ -n "$ARG" ]; then
	ARGDIR=`dirname $ARG`
	ARGFILE=`basename $ARG | sed -e 's/\.[^.]*$/.o/'`

	case "$ARGDIR" in
	/* )
		# do nothing
		;;
	* )
		ARGDIR="/$ARGDIR"
		;;
	esac
fi
if [ -n "$2" ]; then
	if [ "X-check" = "X$2" ]; then
		ARGFILE="check"
		ARGDIR="${ARGDIR%/test}"
	fi
fi

export CXXFLAGS="-g -ggdb -O0"
export LDFLAGS="-g -ggdb"


echo "THISDIR=$THISDIR"
echo "ARG=$ARG"
echo "ARGDIR=$ARGDIR"
echo "ARGFILE=$ARGFILE"


case `uname -s` in
Msys | MSYS | msys | MINGW* )
	echo "...WIN64"
	#export CPPFLAGS="-DWIN64"
	function tweak_paths() {
		cat -  | \
			sed \
				-e ':x; s@[^/][^/]*/\.\./@@;t x' \
				-e ':y; s@^\.\./@@g; t y' \
				-e "s@$THISDIR/@@g"
	}
	;;
[Ll]inux )
	echo "...linux"
	#export CPPFLAGS="-DLINUX -DLinux -Dlinux"
	function tweak_paths() {
		cat -
	}
	;;
* )
	echo "...undefined"
	;;
esac

pushd $THISDIR/build$ARGDIR >/dev/null

	make -j4 $ARGFILE 2>&1  |  tee $THISDIR/build/build.log  | tweak_paths

popd >/dev/null
