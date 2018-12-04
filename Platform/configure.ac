
AC_PREREQ([2.69])
AC_INIT([GS8], [8.0.0], [john@grizzlyweb.com])

AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

#AC_PROG_RANLIB
#AC_PROG_LIBTOOL
LT_INIT


AC_LANG([C++])

case `uname -o` in
[Mm]sys )
	CPPFLAGS = "-DMSYS"
	;;
[Ll]inux* )
	;;
esac

#AX_CXX_COMPILE_STDCXX_11([noext],[manditory])

AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h memory.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h strings.h sys/ioctl.h sys/socket.h sys/time.h sys/timeb.h termios.h unistd.h])

AC_CONFIG_FILES([
	Makefile
	Platform_specs/Makefile
])
AC_OUTPUT

