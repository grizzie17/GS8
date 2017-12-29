/*=====================================================================*/
//
//!	@file	stdio_sx.cpp
//!	@see	stdio_sx.h
//
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
#include <stdarg.h>
#include <stdexcept>
#include "stdio_sx.h"
#include "UPlatformString.h"
#include "UWarnings.h"
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
/*=====================================================================+\
||	 class lifecycle functions
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * fopen_s

\+---------------------------------------------------------------------*/
int		fopen_sx
		(
		FILE**		hFile,
		const char*	sName,
		const char* sMode
		)
{
	BEGIN_IGNORE_WARNING(4996)	// using insecure function
	FILE*	pF = fopen( sName, sMode );
	END_IGNORE_WARNING
	if ( pF )
	{
		*hFile = pF;
		return 0;
	}
	else
	{
		return -1;
	}
}

/*---------------------------------------------------------------------+\

 * sprintf_s

\+---------------------------------------------------------------------*/
int		sprintf_sx
		(
		char*		sBuffer,
		size_t		nSizeBuffer,
		const char*	sFormat,
		...
		)
{
	int		nResult = -1;
	if ( !sBuffer  ||  !sFormat)
	{
		nResult = -1;
		errno = EINVAL;
	}
	else
	{
		va_list	vargs;
		va_start( vargs, sFormat );
		nResult = vsnprintf( sBuffer, nSizeBuffer, sFormat, vargs );
		va_end( vargs );
		if ( nResult < 0 )
		{
			errno = -1;
			throw std::runtime_error( std::string("Buffer too small") );
		}
		else if ( (size_t)nResult < nSizeBuffer )
		{
			errno = 0;
		}
		else if ( -1 < errno )
		{
			errno = -1;
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * getenv_s

\+---------------------------------------------------------------------*/
errno_t	getenv_sx
		(
		size_t*		pReturnValue,
		char*		pTarget,
		size_t		nTargetSize,
		const char*	sName
		)
{
	errno_t	eResult = 0;

	char*	sValue;
	BEGIN_IGNORE_WARNING( 4996 )
	sValue = getenv( sName );
	END_IGNORE_WARNING
	if ( sValue )
	{
		eResult = strcpy_s( pTarget, nTargetSize, sValue );
		if (pReturnValue)
			*pReturnValue = strlen(sValue);
	}
	else
	{
		eResult = -1;
	}
	return eResult;
}



/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/

