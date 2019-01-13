/*=====================================================================*/
/**
*	@file	UPlatformThreads.cpp
* 	@see	UPlatformThreads.h
*/
/*=====================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	28-Nov-2015			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformThreads.h"

/*---------------------------------------------------------------------+\
|								
|	Local defines / constants	
|								
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|							
|	Local Type Definitions	
|							
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
/*---------------------------------------------------------------------+\
|							
|	Private Global Variables
|							
\+---------------------------------------------------------------------*/
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


#if defined( OS_MSWIN )
/*---------------------------------------------------------------------+\

 * SetThreadName

\+---------------------------------------------------------------------*/
//
// Usage: SetThreadName (-1, "MainThread");
//
static void
		SetThreadName
		(
		DWORD	dwThreadID,
		LPCSTR	szThreadName
		)
{
#if defined( _MSC_VER )
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // must be 0x1000
		LPCSTR szName; // pointer to name (in user addr space)
		DWORD dwThreadID; // thread ID (-1=caller thread)
		DWORD dwFlags; // reserved for future use, must be zero
	} THREADNAME_INFO;

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = szThreadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (ULONG_PTR*)&info );
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
#else
	UNREFERENCED_PARAMETER(dwThreadID);
	UNREFERENCED_PARAMETER(szThreadName);
#endif
}

#endif


/*---------------------------------------------------------------------+\

 * ThreadCreate

\+---------------------------------------------------------------------*/
UThreadHdl
		ThreadCreate
		(
		UThreadFunction	pFunc,
		void*			pArg,
		const char*		sName //= NULL
		)
{
	UThreadHdl	hResult = 0;

#if defined( THREADS_POSIX )

	int error = pthread_create(&hResult,0,pFunc,pArg);
	if ( 0 != error )
	{
		hResult = 0;
		LogPrint( "Thread Creation Failed\n" );
	}
	else
	{
//#	if defined( OS_LINUX )
//		if ( sName )
//			pthread_setname_np( hResult, sName );
//#	elif defined( OS_UNIX_BSD )
//		if ( sName )
//			pthread_set_name_np( hResult, sName );
//#	else
		UNREFERENCED_PARAMETER(sName);
//#	endif
	}

#elif defined( THREADS_WINDOWS )

	DWORD	nThreadID;

	hResult = CreateThread(NULL,0, pFunc,(LPVOID)pArg,0,&nThreadID);
	if( !hResult )
	{
		LogPrint( "Thread Creation Failed\n" );
	}
	else
	{
		if ( sName )
			SetThreadName( nThreadID, sName );
	}

#endif

	return hResult;
}

/*---------------------------------------------------------------------+\

 * ThreadClose

\+---------------------------------------------------------------------*/
void	ThreadClose
		(
		UThreadHdl	hThread
		)
{
#if defined( THREADS_POSIX )

	if ( hThread )
	{
		pthread_cancel( hThread );
	}

#elif defined( THREADS_WINDOWS )

	if ( hThread )
	{
		TerminateThread( hThread, 0 );
		CloseHandle( hThread );
	}

#endif
}






//}}


/**--------------------------------------------------------------------+\

 * <summary>someFunction - brief statement</summary>

 * <remarks/>

\+---------------------------------------------------------------------*/

