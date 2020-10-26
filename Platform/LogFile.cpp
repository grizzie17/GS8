/*=====================================================================*/
/**
*	@file	LogFile.cpp
* 	@see	LogFile.h
*/
/*=====================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
// LogFile.cpp : Defines the entry point for the DLL application.
//


//#include "stdafx.h"
#include "UOSIncludes.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "UFile.h"
#include "UPlatform.h"
#include "UPlatformIO.h"
#include "UPlatformString.h"
#include "UPlatformThreads.h"

#include "CMutex.h"

#ifndef BUILDING_SHAREDLIB
#    define BUILDING_SHAREDLIB
#endif
#include "LogFile.h"

#undef LOGFILE_API
#define LOGFILE_API( t ) DEF_API( t )

/*---------------------------------------------------------------------+\
|
|	Local defines / constants
|
\+---------------------------------------------------------------------*/
//#define OUTPUT_CONSOLE	1
//#define OUTPUT_LOGFILE	1
//#define LOGPRINT_TO_FILE	1
/*---------------------------------------------------------------------+\
|
|	Local Type Definitions
|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|
|	Private Global Variables
|
\+---------------------------------------------------------------------*/
CMutex g_oMutex;
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


#if defined( OUTPUT_CONSOLE )
#    include <fstream>
#    include <iostream>
#    include <streambuf>
#    include <wincon.h>

class DebugConsole
{
public:
    DebugConsole();
    ~DebugConsole();

    void
    open();
    void
    close();

private:
    std::streambuf* _cinbuf;
    std::streambuf* _coutbuf;
    std::streambuf* _cerrbuf;
    std::ifstream   _console_cin;
    std::ofstream   _console_cout;
    std::ofstream   _console_cerr;
};


DebugConsole::DebugConsole()
        : _cinbuf( 0 )
        , _coutbuf( 0 )
        , _cerrbuf( 0 )
{
    open();
}

DebugConsole::~DebugConsole()
{
    close();
}

void
DebugConsole::open()
{
    AllocConsole();
    AttachConsole( GetCurrentProcessId() );
    this->_cinbuf = std::cin.rdbuf();
    this->_console_cin.open( "CONIN$" );
    std::cin.rdbuf( this->_console_cin.rdbuf() );
    this->_coutbuf = std::cout.rdbuf();
    this->_console_cout.open( "CONOUT$" );
    std::cout.rdbuf( this->_console_cout.rdbuf() );
    this->_cerrbuf = std::cerr.rdbuf();
    this->_console_cerr.open( "CONOUT$" );
    std::cerr.rdbuf( this->_console_cerr.rdbuf() );
}

void
DebugConsole::close()
{
    this->_console_cout.close();
    std::cout.rdbuf( this->_coutbuf );
    this->_console_cin.close();
    std::cin.rdbuf( this->_cinbuf );
    this->_console_cerr.close();
    std::cerr.rdbuf( this->_cerrbuf );
    FreeConsole();
}

DebugConsole g_console;

#endif


//
//#ifdef _MANAGED
//#pragma managed(push, off)
//#endif
//
//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//					 )
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		break;
//	}
//    return TRUE;
//}
//
//#ifdef _MANAGED
//#pragma managed(pop)
//#endif

#if defined( OUTPUT_CONSOLE )
static bool x_bConsoleOpen = false;
static char x_sLogPath[1024] = { 0 };
//static char g_sApplicationFolder[1024] = {0};
#endif


#if defined( OUTPUT_LOGFILE )
static void
WriteLogFile( const char* sString )
{
    FILE* pf;

    CMutexLocker oLocker( &g_oMutex );
    if ( x_sLogPath[0] )
    {
        if ( 0 == fopen_s( &pf, x_sLogPath, "a" ) )
        {
            fprintf( pf, "%s", sString );
            fclose( pf );
        }
    }
    else
    {
        const char* s = GetApplicationFolder();

        PathBuild( x_sLogPath, sizeof( x_sLogPath ), s, "ErrorLog.txt" );

        if ( 0 == fopen_s( &pf, x_sLogPath, "w+" ) )
        {
            fprintf( pf, "%s", sString );
            fclose( pf );
        }
    }
}
#else
inline void
WriteLogFile( const char*  //sString
)
{
    ( (void)0 );
}
#endif

#if defined( OUTPUT_CONSOLE )
#    if defined( OS_MSWIN )
static void
LogToConsole( const char* sString )
{
#        if defined( OS_MSWIN_WCE )
    printf( "%s", sString );
#        else
    std::cout << sString;
#        endif
}
#    endif
#else
inline void
LogToConsole( const char*  //sString
)
{
    ( (void)0 );
}
#endif


#if defined( LOGPRINT_TO_FILE )
static void
LogFile( const char* sText )
{
    WriteLogFile( sText );
}
#else
#    define LogFile( sText ) ( (void)0 )
#endif


static void
LogConsole( const char* sText )
{
#if defined( OUTPUT_CONSOLE )
#    if defined( OS_MSWIN )
    LogToConsole( sText );
#    endif
#else
    ( (void)0 );
#endif
}


/*---------------------------------------------------------------------+\

* DbgPrint - This function is inlined as nothing when not debug

\+---------------------------------------------------------------------*/
#ifdef DBG_PRINT
void
DbgPrint( char const* sFormat, ... )
{
    //int		nResult = 0;
    char    sBuffer[1024];
    va_list vargs;
    va_start( vargs, sFormat );
    //nResult =
    vsnprintf_s(
            sBuffer, sizeof( sBuffer ), sizeof( sBuffer ), sFormat, vargs );
    va_end( vargs );

#    if defined( OS_MSWIN )
#        if ! defined( OS_WIN32_WCE )
    OutputDebugStringA( sBuffer );
#        endif
    LogConsole( sBuffer );
#    else
    printf( "%s", sBuffer );
    fflush( stdout );
#    endif
#    if defined( LOGPRINT_TO_FILE )
    LogFile( sBuffer );
#    endif
}
#endif


/*---------------------------------------------------------------------+\

* DbgAssert - This function is inlined as nothing when not debug

\+---------------------------------------------------------------------*/
#if defined( _DEBUG )
void
DbgAssert( bool bAssertion, char const* sFormat, ... )
{
    if ( ! bAssertion )
    {
        //int		nResult = 0;
        char    sBuffer[256];
        va_list vargs;
        va_start( vargs, sFormat );
        //nResult =
        vsnprintf_s(
                sBuffer, sizeof( sBuffer ), sizeof( sBuffer ), sFormat, vargs );
        va_end( vargs );
#    if defined( MSC_VER )
#        if ! defined( OS_MSWIN_WCE )
        OutputDebugStringA( sBuffer );
#        endif
        LogConsole( sBuffer );
#    else
        printf( "%s", sBuffer );
        fflush( stdout );
#    endif
#    if defined( LOGPRINT_TO_FILE )
        LogFile( sBuffer );
#    endif
    }
}
#endif


/*---------------------------------------------------------------------+\

* LogPrint

\+---------------------------------------------------------------------*/
#if defined( LOG_PRINT )
void
LogPrint( char const* sFormat, ... )
{
    //int		nResult = 0;
    char    sBuffer[256];
    va_list vargs;
    va_start( vargs, sFormat );
    //nResult =
    vsnprintf_s(
            sBuffer, sizeof( sBuffer ), sizeof( sBuffer ), sFormat, vargs );

    va_end( vargs );
#    ifdef OS_MSWIN
#        if ! defined( OS_MSWIN_WCE )
    OutputDebugStringA( sBuffer );
#        endif
    LogConsole( sBuffer );
#    else
    printf( "%s", sBuffer );
    fflush( stdout );
#    endif
#    if defined( LOGPRINT_TO_FILE )
    LogFile( sBuffer );
#    endif

    // TODO: add logging to file
}
#endif


}}  // namespace Yogi::Core
