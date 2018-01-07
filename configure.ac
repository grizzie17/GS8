#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GS8], [8.0.0], [john@grizzlyweb.com])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])



# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_RANLIB
AM_PROG_AR

# Checks for libraries.

# Checks for header files.
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
AC_CHECK_FUNCS([clock_gettime floor ftime getcwd gethostbyname gethostname gettimeofday inet_ntoa memset pow select socket sqrt strchr strerror strpbrk strrchr strspn strstr strtol tzset])

#AC_CONFIG_LIBOBJ_DIR([build/lib])

#AC_CONFIG_SUBDIRS([Common])

#AC_CONFIG_SRCDIR([config.h.in])
#AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
	Common/Common_specs/Makefile
	Common/Makefile
	Platform/Makefile
	Platform/Platform_specs/Makefile
	Makefile
])
AC_OUTPUT




#AC_CONFIG_FILES([Common/Makefile
#                 Config/Makefile
#                 Makefile])
#AC_OUTPUT



