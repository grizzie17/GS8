/*=====================================================================*/
/**
*	@file	UPlatformString.cpp
* 	@see	UPlatformString.h
*/
/*=====================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	28-Nov-2015			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "UPlatformString.h"
#include "UNResult.h"
/*---------------------------------------------------------------------+\
|								
|	Local defines / constants	
|								
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Local Type Definitions	
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Private Global Variables
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Public Global Variables	
|							
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|						
|	External Variables	
|						
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||			
||	 Code	
||			
\+=====================================================================*/



#if defined( NEED_FUNC_S )




/*---------------------------------------------------------------------+\

 * getenv_s

\+---------------------------------------------------------------------*/
#if ! defined(OS_WIN32_WCE)
errno_t	getenv_s
		(
		size_t*		pReturnValue,
		char*		pTarget,
		size_t		nTargetSize,
		const char*	sName
		)
{
	errno_t	eResult = 0;

	char*	sValue;
	sValue = getenv( sName );
	if ( sValue )
	{
		eResult = 0;
		strcpy_s( pTarget, nTargetSize, sValue );
	}
	else
	{
		eResult = -1;
	}
	return eResult;
}
#endif


#endif	// NEED_FUNC_S


#if NEED_FUNC_S

#	ifndef HAS_STRING_SX

errno_t	memcpy_s
		(
		void*		t,
		size_t		tc,
		const void*	s,
		size_t		sc
		)
{
	errno_t	eResult = 0;

	if ( tc < sc )
	{
		eResult = WRONG;
		sc = tc;
	}

	::memcpy( t, s, sc );

	return eResult;
}


errno_t	strcpy_s
		(
		char*		t,
		size_t		tc,
		const char*	s
		)
{
	errno_t	eResult = 0;
	size_t	sc = ::strlen(s) + 1;
	if ( tc < sc )
	{
		eResult = WRONG;
		sc = tc;
	}
	::memcpy( t, s, sc );
	return eResult;
}


errno_t	strncpy_s
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		)
{
	errno_t	eResult = 0;
	if ( tc < sc )
	{
		eResult = WRONG;
		sc = tc;
	}
	::strncpy( t, s, sc );
	if ( sc < tc )
		*(t+sc) = 0;	// null terminate
	return eResult;
}


errno_t	strcat_s
		(
		char*		t,
		size_t		tc,
		const char*	s
		)
{
	errno_t	eResult = 0;
	size_t	tn = ::strlen( t );

	if ( tc <= tn )
	{
		eResult = WRONG;
	}
	else
	{
		t += tn;
		eResult = strcpy_s( t, tc - tn, s );
	}

	return eResult;
}


errno_t	strncat_s
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		)
{
	errno_t	eResult = 0;
	size_t	tn = ::strlen( t );
	if ( tc <= tn )
	{
		eResult = -1;
	}
	else
	{
		t += tn;
		eResult = strncpy_s( t, tc - tn, s, sc );
	}

	return eResult;
}

#	endif	// HAS_STRING_SX
#endif


/*---------------------------------------------------------------------+\

 * WideStringFromString

\+---------------------------------------------------------------------*/
#if defined( OS_MSWIN )
WCHAR*	WideStringFromString
		(
		const char*	sString
		)
{
	WCHAR*	ws = 0;
	size_t	nLen = strlen(sString);

	if ( 0 < nLen )
	{
		ws = new WCHAR[nLen+10];
		if ( ws )
		{
			size_t	n = (size_t)::MultiByteToWideChar( CP_ACP, 0, sString, int(nLen), ws, int(nLen+10) );
			if ( 0 < n )
			{
				ws[n] = 0;
			}
			else
			{
				delete [] ws;
				ws = 0;
			}
		}
	}

	return ws;
}
#endif




#if defined( OS_MSWIN_WCE )
/*---------------------------------------------------------------------+\

 * strerror

\+---------------------------------------------------------------------*/
char* strerror(errno_t errnum)
{
	static char	g_sError[128];

	if ( -1 < errnum  &&  errnum < NUM_MESSAGES )
	{
		return messages[errnum];
	}
	else
	{
		sprintf_s( g_sError, sizeof(g_sError), "Unknown Error: %0lx \n", errnum );

		return g_sError;
	}
}





/*---------------------------------------------------------------------+\

 * getenv

\+---------------------------------------------------------------------*/
char*	getenv
		(
		const char* //name
		)
{
	return NULL;
}



#endif	// OS_MSWIN_WCE





/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/

