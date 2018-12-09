

#ifndef ULibrary_H
#define ULibrary_H


#ifndef DLL_EXPORT
#	if defined( MSC_VER )
#		define	DLL_EXPORT	__declspec(dllexport)
#	else
#		define	DLL_EXPORT
#	endif
#endif

#ifndef DLL_IMPORT
#	if defined( MSC_VER )
#		define	DLL_IMPORT	__declspec(dllimport)
#	else
#		define	DLL_IMPORT
#	endif
#endif

#if defined( MSC_VER )
#	define	DCL			__cdecl
#	define	STD_CALL	__stdcall
#else
#	define	DCL
#	define	STD_CALL
#endif

#if defined( FUNC_EXPORT )
#	define DEF_API(t)	DLL_EXPORT t STD_CALL
#else
#	define DEF_API(t)	DLL_IMPORT t STD_CALL
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




#endif // ULibrary_H_
