/************************************************************************
*
*	@file string_sx.h
*
*	@brief compatibility with std "safe" string routines
*
		The naming conventions for the arguments are as follows:

			t	= target
			tc	= target count (sizeof)
			s	= source
			sc	= source count

*
\***********************************************************************/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		change count values to size_t so it matches spec.
	03-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_string_sx
#define _H_string_sx
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include <stdio.h>
#include <errno.h>
#include "UTypes.h"
#include "UDeclPlatform.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
#define HAS_STRING_SX
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
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

DECL_API(errno_t)
		memcpy_sx
		(
		void*		t,
		size_t		tc,
		const void*	s,
		size_t		sc
		);

DECL_API(errno_t)
		strcpy_sx
		(
		char*		t,
		size_t		tc,
		const char*	s
		);

DECL_API(errno_t)
		strncpy_sx
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		);

DECL_API(errno_t)
		strcat_sx
		(
		char*		t,
		size_t		tc,
		const char*	s
		);

DECL_API(errno_t)
		strncat_sx
		(
		char*		t,
		size_t		tc,
		const char*	s,
		size_t		sc
		);

/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/




#endif /* _H_string_sx */
