/*---------------------------------------------------------------------+\
|
|	string_sx.cpp  --
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	26-Apr-2013			J.Griswold
		unwind loop in memcpy_s
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		change count values to size_t so it matches spec.
	03-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#ifndef __STDC_WANT_SECURE_LIB__
#define __STDC_WANT_SECURE_LIB__ 1
#endif
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "string_sx.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * memcpy_sx -

\+---------------------------------------------------------------------*/
errno_t	memcpy_sx
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
		eResult = -1;
		sc = tc;
	}
	char*		tx = (char*)t;
	const char*	sx = (const char*)s;
//	const char*	sEnd = sx + sc;
//	while ( sx < sEnd )
//		*tx++ = *sx++;

	// unroll eight times
	for ( ; 7 < sc; sc -= 8 )
	{
		*tx++ = *sx++;	// 1
		*tx++ = *sx++;	// 2
		*tx++ = *sx++;	// 3
		*tx++ = *sx++;	// 4
		*tx++ = *sx++;	// 5
		*tx++ = *sx++;	// 6
		*tx++ = *sx++;	// 7
		*tx++ = *sx++;	// 8
	}

	switch ( sc )
	{
	case 8:	*tx++ = *sx++;	// fall through
	case 7:	*tx++ = *sx++;	// fall through
	case 6:	*tx++ = *sx++;	// fall through
	case 5:	*tx++ = *sx++;	// fall through
	case 4:	*tx++ = *sx++;	// fall through
	case 3:	*tx++ = *sx++;	// fall through
	case 2:	*tx++ = *sx++;	// fall through
	case 1:	*tx++ = *sx++;	// fall through
		break;
	default:
		break;
	}

	//assert( 0 == eResult );

	return eResult;
}


/*---------------------------------------------------------------------+\

 * strcpy_sx -

\+---------------------------------------------------------------------*/
errno_t	strcpy_sx
		(
		char*		t,
		size_t		tc,
		const char*	s
		)
{
	errno_t	eResult = 0;
	char*	tEnd = t + tc;

	while ( t < tEnd )
	{
		if ( *s )
		{
			*t++ = *s++;
		}
		else
		{
			*t = *s;
			break;
		}
	}

	if ( t == tEnd  &&  0 != *(t-1) )
		eResult = -1;

	//assert( 0 == eResult );

	return eResult;
}

/*---------------------------------------------------------------------+\

 * strncpy_sx -

\+---------------------------------------------------------------------*/
errno_t	strncpy_sx
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
		eResult = -1;
		sc = tc;
	}

	const char*	sEnd = s + sc;
	char*		tEnd = t + tc;

	while ( t < tEnd )
	{
		if ( s < sEnd )
		{
			if ( *s )
			{
				*t++ = *s++;
			}
			else
			{
				*t = *s;
				break;
			}
		}
		else
		{
			// we null terminate if there is room
			*t = 0;
			break;
		}
	}

	//assert( 0 == eResult );

	return eResult;
}


/*---------------------------------------------------------------------+\

 * strcat_sx -

\+---------------------------------------------------------------------*/
errno_t	strcat_sx
		(
		char*		t,
		size_t		tc,
		const char*	s
		)
{
	errno_t	eResult = 0;
	size_t	tn = strlen( t );

	if ( tc <= tn )
	{
		eResult = -1;
	}
	else
	{
		t += tn;
		eResult = strcpy_sx( t, tc - tn, s );
	}
	//assert( 0 == eResult );

	return eResult;
}


/*---------------------------------------------------------------------+\

 * strncat_sx -

\+---------------------------------------------------------------------*/
errno_t	strncat_sx
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		)
{
	errno_t	eResult = 0;
	size_t	tn = strlen( t );
	if ( tc <= tn )
	{
		eResult = -1;
	}
	else
	{
		t += tn;
		eResult = strncpy_sx( t, tc - tn, s, sc );
	}
	//assert( 0 == eResult );

	return eResult;
}




/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

