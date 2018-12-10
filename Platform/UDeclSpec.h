

#ifndef UDeclSpec_H
#define UDeclSpec_H




#ifndef DECLSPECEXPORT
#	if defined( MSC_VER )
#		define	DECLSPECEXPORT	__declspec(dllexport)
#	else
#		define	DECLSPECEXPORT
#	endif
#endif

#ifndef DECLSPECIMPORT
#	if defined( MSC_VER )
#		define	DECLSPECIMPORT	__declspec(dllimport)
#	else
#		define	DECLSPECIMPORT
#	endif
#endif

#if defined( MSC_VER )
#	define	CDECL		__cdecl
#	define	STD_CALL	__stdcall
#else
#	define	CDECL
#	define	STD_CALL
#endif

#if defined( DLL_EXPORT )
#	define DEF_API(t)	DECLSPECEXPORT t STD_CALL
#else
#	define DEF_API(t)	DECLSPECIMPORT t STD_CALL
#endif


// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LOGFILE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LOGFILE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
//#define OS_MSWIN 1
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




#endif // UDeclSpec_H
