

#ifndef UDeclSpec_H
#define UDeclSpec_H


#if defined( _WIN32 ) || defined( __CYGWIN__ )
#    if defined( __GNUC__ )
#        define DLLEXPORT __attribute__( ( dllexport ) )
#        define DLLIMPORT __attribute__( ( dllimport ) )
#        define CDECL
#        define STD_CALL
#    else
#        if defined( SHLIB )
#            define DLLEXPORT __declspec( dllexport )
#            define DLLIMPORT __declspec( dllimport )
#        else
#            define DLLEXPORT
#            define DLLIMPORT
#        endif
#        ifndef CDECL
#            define CDECL __cdecl
#        endif
#        define STD_CALL __stdcall
#    endif
#    define DLLPRIVATE
#else  // linux
#    if 4 <= __GNUC__
#        define DLLEXPORT  __attribute__( ( visibility( "default" ) ) )
#        define DLLPRIVATE __attribute__( ( visibility( "hidden" ) ) )
#    else
#        define DLLEXPORT
#        define DLLPRIVATE
#    endif
#    define DLLIMPORT
#    define CDECL
#    define STD_CALL
#endif


// #ifndef DECLSPECEXPORT
// #    if defined( _WIN32 )
// #        define DECLSPECEXPORT __declspec( dllexport )
// #    else
// #        define DECLSPECEXPORT
// #    endif
// #endif
// #define SHLIB_EXPORT DECLSPECEXPORT

// #ifndef DECLSPECIMPORT
// #    if defined( _WIN32 )
// #        define DECLSPECIMPORT __declspec( dllimport )
// #    else
// #        define DECLSPECIMPORT
// #    endif
// #endif

// #if defined( _WIN32 )
// #    ifndef CDECL
// #        define CDECL __cdecl
// #    endif
// #    define STD_CALL __stdcall
// #else
// #    define CDECL
// #    define STD_CALL
// #endif


// #undef STD_CALL
// #define STD_CALL

// #if defined( BUILDING_SHAREDLIB )
// #	define DECL_SHLIB	DECLSPECEXPORT
// #	define DECL_API(t)	t DECLSPECEXPORT
// #	define DECL_CLASS	DECLSPECEXPORT
// #else
// #	define DECL_SHLIB	DECLSPECIMPORT
// #	define DECL_API(t)	t DECLSPECIMPORT
// #	define DECL_CLASS	DECLSPECIMPORT
// #endif
// #define DEF_API( t ) STD_CALL t

// #undef DECLSPECEXPORT
// #undef DECLSPECIMPORT
// #define DECLSPECEXPORT
// #define DECLSPECIMPORT


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


#endif  // UDeclSpec_H
