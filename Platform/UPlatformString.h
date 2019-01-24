//=======================================================================
//
//!	@file	UPlatformString.h
//!	@brief	Issolate platform specific string library strangeness
//
//=======================================================================
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	28-Nov-2015			J.Griswold		(Reviewed by: xxxx)
		Move from UPlatform.h
|
\+---------------------------------------------------------------------*/
#ifndef _H_UPlatformString
#define _H_UPlatformString
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"
#include "string_sx.h"
#include "UDeclPlatform.h"
//#include "UMath.h"

/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
#if ! defined( __STDC_SECURE_LIB__ )  ||  (__STDC_SECURE_LIB__ < 200410L )
#	define NEED_FUNC_S		1
#	define NEED_SPRINTF_S	1
#endif


#if defined( NEED_FUNC_S )  &&  defined( HAS_STRING_SX )

#	undef	memcpy_s
#	define	memcpy_s( t, tc, s, sc )	memcpy_sx( t, tc, s, sc )

#	undef	strcpy_s
#	define	strcpy_s( t, tc, s )		strcpy_sx( t, tc, s )

#	undef	strncpy_s
#	define	strncpy_s( t, tc, s, sc )	strncpy_sx( t, tc, s, sc )

#	undef	strcat_s
#	define	strcat_s( t, tc, s )		strcat_sx( t, tc, s )

#	undef	strncat_s
#	define	strncat_s( t, tc, s, sc )	strncat_sx( t, tc, s, sc )

#endif

/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/

/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/

#if defined( _MSC_VER )
#elif defined( __GNUC__ )
#	ifndef _stricmp
#		define _stricmp( t, s )			strcasecmp( t, s )
#	endif

#	ifndef stricmp
#		define stricmp( t, s )			_stricmp( t, s )
#	endif

#	ifndef _strnicmp
#		define _strnicmp( t, s, sc )	strncasecmp( t, s, sc )
#	endif

#	ifndef strnicmp
#		define	strnicmp( t, s, sc )	_strnicmp( t, s, sc )
#	endif

#	ifndef sscanf_s
#		define	sscanf_s	sscanf
#	endif

#	ifndef strerror_s
#		define strerror_s(t, tc, en )	strerror(en)
#	endif
#endif

#if defined( NEED_FUNC_S )

#	if defined(OS_WIN32_WCE)
#		define vsnprintf_s	_vsnprintf_s
#		define vsnprintf	_vsnprintf
//#		define getenv_s		_getenv_s_helper
#	endif

#endif	// NEED_FUNC_S

#ifdef NEED_FUNC_S

#	ifndef HAS_STRING_SX

errno_t
		memcpy_s
		(
		void*		t,
		size_t		tc,
		const void*	s,
		size_t		sc
		);

errno_t
		strcpy_s
		(
		char*		t,
		size_t		tc,
		const char*	s
		);

errno_t
		strncpy_s
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		);

errno_t
		strcat_s
		(
		char*		t,
		size_t		tc,
		const char*	s
		);

errno_t
		strncat_s
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		);

#	endif	// HAS_STRING_SX



#endif


#if defined( OS_MSWIN )

WCHAR*
		WideStringFromString
		(
		const char*	sString
		);

#	if defined OS_MSWIN_WCE

const char*
		strerror
		(
		errno_t errnum
		);

const char*
		getenv
		(
		const char* name
		);

#	endif

#endif
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/




#endif /* _H_UPlatformString */
