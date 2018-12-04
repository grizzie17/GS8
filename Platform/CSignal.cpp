/*---------------------------------------------------------------------+\
|
|	CSignal.cpp  --  wrapper for signals/events
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
	03-Dec-2015			J.Griswold
		Move to 'Root' namespace.
	23-Feb-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CSignal.h"

#include "UPlatform.h"
#include "UPlatformString.h"
#if defined( SIGNAL_WINDOWS )
#	if ! defined( OS_WIN32_WCE )
#		include <process.h>
#	endif
#elif defined( SIGNAL_POSIX )
#	include <pthread.h>
#else
#	error "signal processing library not defined"
#endif
#include "NamespaceRoot.h"
NAMESPACE_ROOT_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

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

 * CSignal - constructor

\+---------------------------------------------------------------------*/
CSignal::CSignal
		(
		void
		)
		:
		m_bCreated( false )
{
#if defined( SIGNAL_WINDOWS )

	sprintf_s( m_sName, sizeof(m_sName), "sig-%p", this );
	//m_hEvent = CreateEventA( NULL, TRUE, FALSE, m_sName);
	m_hEvent = CreateEventA( NULL, FALSE, FALSE, NULL);
	if( m_hEvent )
	{
		m_bCreated = true;
	}

#elif defined( SIGNAL_POSIX )

	do
	{
		pthread_mutexattr_t mattr;

		pthread_mutexattr_init(&mattr);
		if ( pthread_mutex_init(&m_lock,&mattr) )
			break;

		if ( pthread_cond_init(&m_ready,NULL) )
			break;

		m_bCreated = true;

	} sequence;


#endif
}


/*---------------------------------------------------------------------+\

 * ~CSignal - destructor

\+---------------------------------------------------------------------*/
CSignal::~CSignal
		(
		void
		)
{
#if defined( SIGNAL_WINDOWS )
	if ( m_hEvent )
		CloseHandle(m_hEvent);
	m_hEvent = 0;
#elif defined( SIGNAL_POSIX )
	pthread_cond_destroy(&m_ready);
	pthread_mutex_destroy(&m_lock);
#endif
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Set -

\+---------------------------------------------------------------------*/
void	CSignal::Set
		(
		void
		)
{
#if defined( SIGNAL_WINDOWS )
	LOCAL_PRINT( "CSignal::Set -- sending event\n");
	if ( m_hEvent )
	{
		ResetEvent( m_hEvent );
		SetEvent(m_hEvent);
	}
#elif defined( SIGNAL_POSIX )
	pthread_mutex_lock(&m_lock);
	pthread_mutex_unlock(&m_lock);
	pthread_cond_signal(&m_ready);
#endif
}


/*---------------------------------------------------------------------+\

 * Wait -

\+---------------------------------------------------------------------*/
bool	CSignal::Wait
		(
		void
		)
{
#if defined( SIGNAL_WINDOWS )
	LOCAL_PRINT( "CSignal::Wait -- waiting\n" );
	if( WAIT_OBJECT_0 != WaitForSingleObject(m_hEvent,INFINITE) )
	{
		LOCAL_PRINT( "CSignal::Wait -- resuming with error\n" );
		return false;
	}
	else
	{
		LOCAL_PRINT( "CSignal::Wait -- resuming\n" );
		return true;
	}
#elif defined( SIGNAL_POSIX )
	if ( pthread_mutex_lock(&m_lock) )
	{
		LOCAL_PRINT( "CSignal::Wait -- failed to lock\n");
		return false;
	}

	if ( pthread_cond_wait(&m_ready,&m_lock) )
	{
		LOCAL_PRINT( "CSignal::Wait -- wait for event failed\n" );
		pthread_mutex_unlock( &m_lock );
		return false;
	}

	pthread_mutex_unlock( &m_lock );
	return true;
#endif
}


/*---------------------------------------------------------------------+\

 * Clear -

\+---------------------------------------------------------------------*/
void	CSignal::Clear
		(
		void
		)
{
#if defined( SIGNAL_WINDOWS )
	if ( m_hEvent )
	{
		ResetEvent( m_hEvent );
	}
#elif defined( SIGNAL_POSIX )
	pthread_mutex_unlock(&m_lock);
#endif
}

/*---------------------------------------------------------------------+\

 * IsCreated -

\+---------------------------------------------------------------------*/
bool	CSignal::IsCreated
		(
		void
		)
{
	return m_bCreated;
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


NAMESPACE_ROOT_END


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

