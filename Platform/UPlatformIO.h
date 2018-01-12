//=====================================================================//
//
//!	@file	UPlatformIO.h
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
#ifndef _H_UPlatformIO
#define _H_UPlatformIO
#pragma once
/*---------------------------------------------------------------------+\
|						
|	Include Files		
|						
\+---------------------------------------------------------------------*/
//#include "UOSIncludes.h"
#include "UMath.h"
#include "stdio_sx.h"

/*---------------------------------------------------------------------+\
|						
|	Defines				
|						
\+---------------------------------------------------------------------*/





#if ! defined( __STDC_SECURE_LIB__ )  &&  ! defined( __STDC_LIB_EXT1__ )

#	undef	sprintf_s
#	define	sprintf_s( buf, sz, fmt, ... )	sprintf_sx( buf, sz, fmt, ## __VA_ARGS__ )

#	undef	vsnprintf_s
#	define	vsnprintf_s( buf, sz, mx, fmt, varg )	vsnprintf( buf, umin(sz,mx), fmt, varg )


#	undef	fopen_s
#	define	fopen_s( hf, nm, md )			fopen_sx( hf, nm, md )

#	undef	getenv_s
#	define	getenv_s( rtn, tgt, sz, nm )	getenv_sx( rtn, tgt, sz, nm )

#endif
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
/*=====================================================================+\
||						
||	Inline Functions	
||						
\+=====================================================================*/



#endif /* _H_UPlatformIO */

