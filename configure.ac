#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GS8], [8.0.0], [john@grizzlyweb.com])

AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])


EXTERNAL_CFLAGS="$CFLAGS"
EXTERNAL_CXXFLAGS="$CXXFLAGS"
EXTERNAL_CPPFLAGS="$CPPFLAGS"

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_RANLIB

CFLAGS="$EXTERNAL_CFLAGS"
CXXFLAGS="$EXTERNAL_CXXFLAGS"
CPPFLAGS="$EXTERNAL_CPPFLAGS"

LT_INIT
AC_SUBST([LIBTOOL_DEPS])

#PKG_CHECK_MODULES([CHECK],[platform_specs])

AC_LANG([C++])

AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])




#AC_DEFINE([__STDC_WANT_SECURE_LIB__],[1])
#AC_DEFINE([__STDC_WANT_LIB_EXT1__],[1])
#AC_SUBST([__STDC_WANT_SECURE_LIB__])
#AC_SUBST([__STDC_WANT_LIB_EXT1__])

AC_DEFINE([_POSIX_REALTIME_SIGNALS],[1])

# GCC is a bit picky about redefinitions of built-in macros. Alas, "built-in"
# simply means "starts with double underscore", so we have to hack around that
# below. Note that clang is happy, even without the guard.
AH_VERBATIM([__STDC_WANT_LIB_EXT1__], [/* we want C11 library extensions  */
#ifndef __STDC_WANT_LIB_EXT1__
# define __STDC_WANT_LIB_EXT1__ 1
#endif])
AH_VERBATIM([__STDC_WANT_SECURE_LIB__], [/* we want C11 secure library  */
#ifndef __STDC_WANT_SECURE_LIB__
# define __STDC_WANT_SECURE_LIB__ 1
#endif])



# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h float.h limits.h memory.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h strings.h sys/ioctl.h sys/socket.h sys/time.h sys/timeb.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime floor ftime getcwd gethostbyname gethostname gettimeofday inet_ntoa memset pow select socket sqrt strchr strerror strpbrk strrchr strspn strstr strtol tzset fopen_s vsnprintf_s snprintf_s strcat_s strcpy_s strncpy_s])

#AC_CONFIG_LIBOBJ_DIR([build/lib])

#AC_CONFIG_SUBDIRS([Common])

#AC_CONFIG_SRCDIR([config.h.in])
#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Platform/Makefile
	Platform/Platform_specs/Makefile
	Common/Makefile
	Common/Common_specs/Makefile
	Gadget/Makefile
	Gadget/Gadget_specs/Makefile
	Draw/VDraw/Makefile
	Draw/VDrawOpenGL/Makefile
	Draw/CDrawOpenGL/Makefile
	VSAShared/Makefile
	WorkbenchShared/Makefile
	Makefile
])
AC_OUTPUT





