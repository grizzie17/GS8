/*---------------------------------------------------------------------+\
|
|	UOSIncludes.h  --  A standard set of system includes
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	21-Dec-2011			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UOSIncludes
#define _H_UOSIncludes
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
//#if defined(MINGW_HAS_SECURE_API)
//#	if ! defined(__STDC_SECURE_LIB__)
//#		define __STDC_SECURE_LIB__	201100L
//#	endif
//#endif

#include "UMachine.h"
#include "UWarnings.h"
#if defined( OS_MSWIN )
#	if defined( OS_WIN32 )
#		if ! defined( WIN32_LEAN_AND_MEAN )
#			define WIN32_LEAN_AND_MEAN 1
#		endif
#	endif
//#	define INCL_WINSOCK_API_TYPEDEFS	1
//#	define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#	if defined( __MINGW__ )
#		include <_mingw.h>
#	endif
#	include <winsock2.h>
#	include <windows.h>
	BEGIN_IGNORE_WARNING(4820)
#	include <wtypes.h>
// #	include <ws2def.h>
	END_IGNORE_WARNING
//#	include <crtdefs.h>
#	include <winerror.h>
#elif defined( OS_LINUX )  ||  defined( OS_MACINTOSH )  ||  defined( OS_UNIX )
#	include <unistd.h>
#	include <dlfcn.h>
#endif

#if defined( THREADS_POSIX )
#	include <pthread.h>
//#elif defined( THREADS_WINDOWS )
#endif


#if ! defined(__STDC_WANT_SECURE_LIB__)
#	define __STDC_WANT_SECURE_LIB__	1
#endif
#if ! defined(__STDC_WANT_LIB_EXT1__)
#	define __STDC_WANT_LIB_EXT1__	1
#endif
//#define MINGW_HAS_SECURE_API		1
#include <stddef.h>
#include <string.h>
BEGIN_IGNORE_WARNING(4820)	// empty space in packed struct
#include <stdio.h>
END_IGNORE_WARNING	// empty space in packed struct
#include <stdlib.h>
#include <limits.h>
#include <errno.h>



/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Function Macros														|
||																		|
\+=====================================================================*/


#endif /* _H_UOSIncludes */
