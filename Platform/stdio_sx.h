//=====================================================================//
//
//!	@file	stdio_sx.h
//!	@brief	Portable equivalent to secure stdio routines
//
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	28-Nov-2015			J.Griswold		(Reviewed by: xxxx)
		Refactor Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_stdio_sx
#define _H_stdio_sx
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include <stdio.h>
#include "UTypes.h"
#include "UDeclPlatform.h"
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
#define	HAS_STDIO_SX
/*---------------------------------------------------------------------+\
|
|	Type Definitions
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

int
		fopen_sx
		(
		FILE**		hFile,
		const char*	sName,
		const char* sMode
		);

errno_t
		getenv_sx
		(
		size_t*		pReturnValue,
		char*		pTarget,
		size_t		nTargetSize,
		const char*	sName
		);

errno_t
		sprintf_sx
		(
		char*		sBuffer,
		size_t		nSizeBuffer,
		const char*	sFormat,
		...
		);

/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/




#endif /* _H_stdio_sx */
