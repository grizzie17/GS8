/*------------------------------------------------------------------*//**
*
*	@file UPlatform.h
*
*	@brief isolate some funny platform specific stuff
*
*//*-------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Notes:	Following characters used to identify good programming fonts
|			O0Q@ 1lI|! qpg .,:; {([<>])}
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	01-May-2013			J.Griswold
		Add macros for enable/disable specific warnings for GCC compilers.
		Still need to figure out if we can unify to a single portable
		mechanism.
	26-Apr-2013			J.Griswold
		Add function inlines for the _s functions when string_sx
		is not available
	17-Jan-2013			J.Griswold
		Change conditionals away from OS to feature defined in UMachine.h
	02-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Add #define that controls whether DbgPrint will output
		to the console or be suppressed.  DbgPrint will never
		display when we are building for release.
	27-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add GetUserConfigFolder function
	02-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Change 'forever_loop' and 'sequence' macros to be switched
		based on compiler definition.
		Add BEGIN_OVERRUN_WARNING macros
	28-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Add FileExists and FolderExists functions
	21-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		add 'sscanf_s' macro to the linux side.
	17-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add new GetApplicationFolder that will return the folder
		from which the application is running
	14-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Move 'min' & 'max' functions outside of OS specific blocks
	24-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove the namespace from UPlatform since these functions
		are global in nature and replace or emmulate global functions
	26-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Make sprintf_s for Linux a real function instead of a #define
	25-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		add mkgmtime to Linux
		Moved the definitions of the Linux glue functions into the
		cpp file.
	22-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Add stdlib.h to get getenv function
	20-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for localtime_s function
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add Linux compatible gmtime_s and getenv_s functions
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	14-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Disable use of these functions for OS_MSWIN
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for new "compatibility" string routines
	03-Sep-2009			J.Griswold		(Reviewed by: R.Hosea)
		Fix ifdef vsnprintf_s to remove the arguments from the ifdef
	30-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		Add fopen_s inline function
	28-Aug-2009			J.Griswold
		Add vsnprintf_s to support the Format function on CCharString
	07-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_UPlatform
#define _H_UPlatform
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "UOSIncludes.h"

#include "UPlatformIO.h"
#include "UPlatformString.h"
#include "UPlatformThreads.h"

#include "UTypes.h"
#include "UFile.h"
#include "UDeclSpec.h"
//#include "UMath.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/







#if defined( __GNUC__ )
#	if ! defined( __FUNCTION__ )
#		define	__FUNCTION__	__func__
#	endif
#elif defined( _MSC_VER )
#	define	__PRETTY_FUNCTION__		__FUNCSIG__
#endif





/*
	Macro to help out with code like:
	Single sequence of statements
	(helps with the problem of multiply nested ifs)

		do
		{
			some code;
			if ( cond )
				break;
			some code;
		} sequence;
*/

#	define	sequence	\
		BEGIN_IGNORE_WARNING( 4127 )	\
		while ( __LINE__ == -1 )		\
		END_IGNORE_WARNING


/*
	Macro to help out with code like:

	do_sequence
	{
		some code;
		if ( cond )
			break;
		some code;
	}
*/

#define PPCAT(a,b)	a##b
#define UNIQUENAME(a)	PPCAT(a,__LINE__)

#define	do_sequence		for ( int UNIQUENAME(seq) = 0; UNIQUENAME(seq) < 1; ++UNIQUENAME(seq))



/*
	Macro for looping forever

	forever_loop
	{
		some code;
		if ( cond )
			break;
	}
*/
#	define	forever_loop	\
		BEGIN_IGNORE_WARNING( 4127 )	\
		while ( 1 )		\
		END_IGNORE_WARNING

#	define	loop_forever	forever_loop



#if ! defined(UNREFERENCED_PARAMETER)
#	define UNREFERENCED_PARAMETER(x)	((x)=(x))
#endif




/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
#if defined( THREADS_POSIX )

	typedef void*		ULibraryHdl;
	typedef int			(*ULibraryFuncPtr)();

#elif defined( THREADS_WINDOWS )

	typedef HMODULE		ULibraryHdl;
	typedef FARPROC		ULibraryFuncPtr;

#endif

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

/**
 *	@brief GetApplicationFolder - get the path of the application
 */
DECL_API(const char*)
		GetApplicationFolder	///@return const path to the application
		(
		void
		);

/**
 *	@brief GetApplicationRootFolder
 *
 * 	If the application is nested in a "debug" or "release" folder
 *	this function returns the folder above
 */
DECL_API(const char*)
		GetApplicationRootFolder	///@return const path
		(
		void
		);

/**
 *	@brief	GetUserConfigFolder
 *
 * 	This function will return the equivalent of calling GetApplicationRootFolder
 *	and then appending "Config"
 */
DECL_API(const char*)
		GetUserConfigFolder		///@return const path
		(
		void
		);




/**
 *	DLLOpen - load a shared-library into memory
 */
DECL_API(ULibraryHdl)
		DLLOpen						///@return handle to open library
		(
		const char*	sLibraryName	///< [in] name of library file to open
		);

/**
 *	DLLGetProcedure - get a pointer to a named procedure/function
 *
 *	@see ULibraryFuncPtr
 */
DECL_API(ULibraryFuncPtr)
		DLLGetProcedure
		(
		ULibraryHdl	hLibrary,
		const char*	sFunctionName
		);


/**
 *	DLLClose - close and release the shared library handle
 */
DECL_API(void)
		DLLClose
		(
		ULibraryHdl	hLibrary		///< [in] handle to library @see DLLOpen
		);

/**
 *	DLLErrorString - get an extended error string
 */
DECL_API(const char*)
		DLLErrorString
		(
		void
		);



/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/





#endif /* _H_UPlatform */

