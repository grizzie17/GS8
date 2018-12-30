/*---------------------------------------------------------------------+\
|
|	CMutex.cpp  --  brief description of what CMutex.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	31-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CMutex.h"
//#include "TPointer.h"
#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformString.h"
#if defined(OS_MSWIN)
#	if defined(OS_WIN32_WCE)
#		include <winbase.h>
#	else
#		include <process.h>
#	endif
#endif

namespace Yogi { namespace Core {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

//#define	USE_EVENTS	1


// change the comment below to allow printing of the local information

//#define	LOCAL_PRINT( fmt, ... )	DbgPrint( fmt, ## __VA_ARGS__ )
#define	LOCAL_PRINT( fmt, ... )


/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CMutex - constructor

\+---------------------------------------------------------------------*/
DECL_CLASS
CMutex::CMutex
		(
		void
		)
		: m_bCreated( true )
{
#if defined(OS_MSWIN)
	sprintf_s( m_sName, sizeof(m_sName), "mut-%p", this );
#	if defined( OS_MSWIN_WCE )
		TArrayPointer<WCHAR>	wsName = WideStringFromString( m_sName );
#		if defined( USE_EVENTS )
			m_mutex = CreateEvent( 0, FALSE, FALSE, wsName );
#		else
			m_mutex = CreateMutex( NULL, FALSE, wsName );
#		endif
#	else
#		if defined( USE_EVENTS )
			m_mutex = CreateEventA( 0, FALSE, FALSE, m_sName );
#		else
			m_mutex = CreateMutexA( NULL, FALSE, m_sName );
#		endif
#	endif
	if ( ! m_mutex )
		m_bCreated = false;
#else
	pthread_mutexattr_t	mAttr;

	pthread_mutexattr_init( &mAttr );
	pthread_mutex_init( &m_mutex, &mAttr );
#endif
}


/*---------------------------------------------------------------------+\

 * ~CMutex - destructor

\+---------------------------------------------------------------------*/
DECL_CLASS
CMutex::~CMutex
		(
		void
		)
{
	if ( m_bCreated )
	{
#if defined( OS_MSWIN )
		WaitForSingleObject( m_mutex, INFINITE );
		CloseHandle( m_mutex );
#else
		pthread_mutex_lock( &m_mutex );
		pthread_mutex_unlock( &m_mutex );
		pthread_mutex_destroy( &m_mutex );
#endif
		m_bCreated = false;
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * Lock - lock mutex

\+---------------------------------------------------------------------*/
DECL_SHLIB
void	CMutex::Lock
		(
		void
		)
{
	if ( m_bCreated )
	{
#if defined( OS_MSWIN )
		LOCAL_PRINT( "CMutex[%0X] Lock\n", m_mutex );
		WaitForSingleObject( m_mutex, INFINITE );
#else
		pthread_mutex_lock( &m_mutex );
#endif
	}
}



/*---------------------------------------------------------------------+\

 * Unlock - release mutex lock

\+---------------------------------------------------------------------*/
DECL_SHLIB
void	CMutex::Unlock
		(
		void
		)
{
	if ( m_bCreated )
	{
#if defined( OS_MSWIN )
		LOCAL_PRINT( "CMutex[%0X] Unlock\n", m_mutex );
#	if defined( USE_EVENTS )
		SetEvent( m_mutex );
#	else
		ReleaseMutex( m_mutex );
#	endif
#else
		pthread_mutex_unlock( &m_mutex );
#endif
	}
}

/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

