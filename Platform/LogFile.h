//=====================================================================//
//
//!	@file	LogFile.h
//!	@brief	Provide a central location to log information from
//!
//!	@note	The LogFile functions are in the global namespace
//
//=====================================================================//
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_LogFile
#define _H_LogFile
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/


#include "UMachine.h"
#include "UDeclSpec.h"

namespace Yogi { namespace Core {

/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
// the following controls whether or not DbgPrint actually prints.
#if defined( _DEBUG )
	// comment out following line to hide DbgPrint
#	define DBG_PRINT	1
#else
#	if defined( DBG_PRINT )
#		undef DBG_PRINT
#	endif
#endif

//comment out the following line to hide LogPrint
//#define	LOG_PRINT		1





// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LOGFILE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LOGFILE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#define LOGFILE_API(t)		DEF_API(t)
// #if defined( MSC_VER )
// #	define DCL	__cdecl
// #	if defined( LOGFILE_EXPORTS )
// #		define LOGFILE_API(t)   __declspec(dllexport) t __stdcall
// //#		define LOGFILE_API extern "C" __declspec(dllexport)
// #	else
// //#		define LOGFILE_API __declspec(dllimport)
// #		define LOGFILE_API(t)   __declspec(dllimport) t __stdcall
// #	endif
// #else
// #	define DCL
// #	define LOGFILE_API(t) t
// #endif


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





//!	DbgPrint - print string to console
//!
//!	string will also be logged if logging is enabled
//!
#ifdef  DBG_PRINT
LOGFILE_API(void)
		DbgPrint
		(
		char const*	sFormat,	//!< [in] printf compatible format string
		...						//!< [in] arguments to format string
		);

#else
inline
void	DbgPrint
		(
		char const*,//sFormat,
		...
		)
{
	;//	do nothing
}
#endif



//!	DbgAssert
//!
//!	optionally raise assert and print to console
//!
#if defined(_DEBUG)
LOGFILE_API(void)
		DbgAssert
		(
		bool		bAssertion,	//!< [in] if false then print
		char const*	sFormat,	//!< [in] printf compatible format string
		...						//!< [in] arguments to format string
		);
#else
inline
void	DbgAssert
		(
		bool,//bAssertion,
		char const*,//sFormat,
		...
		)
{
	;// do nothing
}
#endif




//!	LogPrint - print to the logfile
//!
//!	Print to the logfile
//!
#if defined(LOG_PRINT)
LOGFILE_API(void)
		LogPrint
		(
		char const*	sFormat,	//!< [in] printf compatible format string
		...						//!< [in] arguments to format string
		);
#else
inline
void	LogPrint
		(
		char const*,//sFormat,
		...
		)
{
	;//	do nothing
}
#endif

/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/



}}

#endif // _H_LogFile
