#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GS8], [8.0.0], [john@grizzlyweb.com])
AC_CONFIG_SRCDIR([GS8.md])
AC_CONFIG_HEADERS([config.h])


AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AM_CONDITIONAL([OS_MSYS], [test "xMsys" = x$(uname -o)])
AM_CONDITIONAL([OS_LINUX], [test "xLinux" = x$(uname -s)])
AC_SUBST([OS_MSYS])
AC_SUBST([OS_LINUX])



EXTERNAL_CFLAGS="$CFLAGS"
EXTERNAL_CXXFLAGS="$CXXFLAGS"
EXTERNAL_CPPFLAGS="$CPPFLAGS"
EXTERNAL_LDFLAGS="$LDFLAGS"

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
#AC_PROG_AWK
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_SED



# AM_COND_IF([OS_MSYS], [
# LT_INIT([shared,pic-only,win32-dll])
# ])

#AM_COND_IF([OS_LINUX], [
LT_INIT([shared,pic-only])
#])

# CFLAGS="$EXTERNAL_CFLAGS"
# CXXFLAGS="$EXTERNAL_CXXFLAGS"
# CPPFLAGS="$EXTERNAL_CPPFLAGS"


AC_LANG([C++])

AX_CXX_COMPILE_STDCXX_17([noext],[mandatory])
# AX_BOOST_UNIT_TEST_FRAMEWORK



#AC_DEFINE([_POSIX_REALTIME_SIGNALS],[])

# GCC is a bit picky about redefinitions of built-in macros. Alas, "built-in"
# simply means "starts with double underscore", so we have to hack around that
# below. Note that clang is happy, even without the guard.
AH_VERBATIM([__STDC_WANT_LIB_EXT1__],
[
/* we want C11 library extensions  */
#ifndef __STDC_WANT_LIB_EXT1__
# define __STDC_WANT_LIB_EXT1__ 1
#endif
])
AH_VERBATIM([__STDC_WANT_SECURE_LIB__],
[
/* we want C11 secure library  */
#ifndef __STDC_WANT_SECURE_LIB__
# define __STDC_WANT_SECURE_LIB__ 1
#endif
])
# AH_VERBATIM([_POSIX_REALTIME_SIGNALS], [/* we want posix library  */
# #ifndef _POSIX_REALTIME_SIGNALS
# # define _POSIX_REALTIME_SIGNALS 1
# #endif])





# Checks for libraries.

# Checks for header files.
#AC_HEADER_STDC
AC_LANG_PUSH([C])
AC_CHECK_HEADERS([assert.h ctype.h errno.h fcntl.h float.h limits.h math.h memory.h stdarg.h stddef.h stdint.h stdio.h stdlib.h string.h strings.h sys/time.h sys/timeb.h sys/types.h time.h unistd.h])
AM_COND_IF([OS_MSYS], [
	AC_CHECK_HEADERS([olectl.h process.h tchar.h winerror.h])
])
AM_COND_IF([OS_LINUX], [
	AC_CHECK_HEADERS([arpa/inet.h dirent.h netdb.h net/if.h netinet/in.h pthread.h semaphore.h sys/ioctl.h sys/socket.h  sys/stat.h termios.h ])
])
AC_LANG_POP([C])
# AC_LANG_PUSH([C++])
# AC_CHECK_HEADERS([cstddef stdexcept string])
# AC_LANG_POP([C++])
# AC_CHECK_HEADERS([cstddef ctype.h errno.h fcntl.h float.h limits.h math.h memory.h stdarg.h stddef.h stdexcept stdint.h stdio.h stdlib.h string string.h strings.h sys/time.h sys/timeb.h sys/types.h time.h unistd.h],[],[])



# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL
# AC_C_INLINE
# AC_TYPE_INT16_T
# AC_TYPE_INT32_T
# AC_TYPE_INT64_T
# AC_TYPE_INT8_T
AC_TYPE_SIZE_T
# AC_TYPE_UINT16_T
# AC_TYPE_UINT32_T
# AC_TYPE_UINT64_T
# AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_CHECK_FUNCS([clock_gettime floor fopen_s ftime getcwd gethostbyname gethostname gettimeofday inet_ntoa memcpy_s memset pow select socket sprintf_s sqrt strcat_s strchr strcpy_s strerror strncpy_s strpbrk strrchr strspn strstr strtol tzset vsnprintf_s])

#GLOBAL_CXXFLAGS=" -std=c++17 -Werror -Wall"
GLOBAL_CXXFLAGS=""
# case `uname -s` in
# [Mm]sys* | mingw* | MINGW* )
# # WDEFS="-DMSYS -DWIN64"
# # AM_CPPFLAGS="$WDEFS"
# # AM_CXXFLAGS=" ${GLOBAL_CXXFLAGS} -mwindows"
# # NO_UNDEFINED="-no-undefined"
# # #CC="gcc $WDEFS"
# # #CXX="g++ $WDEFS"
# # #CC="x86_64-pc-msys-gcc $WDEFS"
# # #CXX="x86_64-pc-msys-g++ $WDEFS"
# # CC="x86_64-w64-mingw32-gcc $WDEFS"
# # CXX="x86_64-w64-mingw32-g++ $WDEFS"
# # AC_SUBST([CC])
# # AC_SUBST([CXX])
# ;;

# [Ll]inux* )
# # AM_CPPFLAGS="-DLINUX"
# # AM_CXXFLAGS="${GLOBAL_CXXFLAGS}"
# # NO_UNDEFINED=""
# ;;
# esac
AM_COND_IF([OS_MSYS],
	[
		GLOBAL_CXXFLAGS+=" -mwindows "
		#EXTSUBDIRS="Draw/VGDI WorkbenchWin"
		EXTSUBDIRS="Draw/VGDI Draw/CDrawWin WorkbenchWin"
		NO_UNDEFINED="-no-undefined"
		WS2_32="-lWs2_32"
		DYLIBEXT=".dll"
		MINGWPREFIX="/mingw64/x86_64-w64-mingw32"
	])
AM_COND_IF([OS_LINUX],
	[
		EXTSUBDIRS="Draw/VDrawOpenGL Draw/CDrawOpenGL WorkbenchGLUT"
		NO_UNDEFINED=""
		WS2_32="-ldl"
		ARFLAGS="cr"
		AR_FLAGS="cr"
		DYLIBEXT=".so"
		MINGWPREFIX="/usr"
	])

AC_SUBST([AM_CPPFLAGS])
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])
AC_SUBST([NO_UNDEFINED])
AC_SUBST([WS2_32])
AC_SUBST([MINGWPREFIX])
AC_SUBST([EXTSUBDIRS])
AC_SUBST([DYLIBEXT])
AC_SUBST([GLOBAL_CXXFLAGS])
AC_SUBST([XLIBDIR])
# AC_SUBST([OSCONFFILES])

AM_CONDITIONAL([DEBUG], [test -n $(echo "$CXXFLAGS" | grep '\-g[gdb0-9]*' 2>/dev/null)])


changequote({,})
CXXFLAGS=`echo "$CXXFLAGS"  |  $SED -e 's/-O[0-9s]*//g' -e 's/-g[gdb0-9]*//g'`
CPPFLAGS=`echo "$CPPFLAGS"  |  $SED -e 's/-D_*DEBUG\b//g'`
LDFLAGS=`echo "$LDFLAGS"  |  $SED -e 's/-Wl,-s//g' -e 's/-Wl,--strip-all//g'`
changequote([,])
AM_COND_IF([DEBUG],
	[
	CXXFLAGS="$CXXFLAGS -g -ggdb  -O0 "
	CPPFLAGS="$CPPFLAGS -D_DEBUG "
	LDFLAGS="$LDFLAGS -g -ggdb "
	],
	[
	CXXFLAGS="$CXXFLAGS -O3 "
	CPPFLAGS="$CPPFLAGS -DNDEBUG "
	LDFLAGS="$LDFLAGS -Wl,-S "
	])


AC_CONFIG_FILES(
	[Platform/Makefile
	Common/Makefile
	Draw/VDraw/Makefile
	Draw/CDrawTmxWin/Makefile
	Draw/CDrawWorkbench/Makefile
	Gadget/Makefile
	VSAShared/Makefile
	WorkbenchShared/Makefile
	Config/Makefile]
	)
AM_COND_IF([OS_MSYS],
	AC_CONFIG_FILES(
		[Draw/VGDI/Makefile
		Draw/CDrawWin/Makefile
		WorkbenchWin/Makefile])
)
AM_COND_IF([OS_LINUX],
	AC_CONFIG_FILES(
		[Draw/VDrawOpenGL/Makefile
		Draw/CDrawOpenGL/Makefile
		WorkbenchGLUT/Makefile])
)
AC_CONFIG_FILES(
	[Services/ServiceVehicleDataSample/Makefile
	Services/ServiceVehicleDirectLoad/Makefile
	GenericContainer/Makefile
	CmdPlugins/CmdCameraSelector/Makefile
	CmdPlugins/CmdConstant/Makefile
	CmdPlugins/CmdConstantD/Makefile
	CmdPlugins/CmdCopyToD/Makefile
	CmdPlugins/CmdKeyName/Makefile
	CmdPlugins/CmdReturnTrue/Makefile
	CmdPlugins/CmdTouchCalibrate/Makefile
	CmdPlugins/CmdVehicleDataLoader/Makefile
	CmdPlugins/CmdVehicleDataSample/Makefile
	]
)
AC_CONFIG_FILES(
	[Makefile]
)
AC_OUTPUT
