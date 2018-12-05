/*---------------------------------------------------------------------+\
|
|	CSemaphore.cpp  --  brief description of what CSemaphore.cpp is for
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
	dd-mmm-9999			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CSemaphore.h"

#include "LogFile.h"
#include "UPlatform.h"
#include "UPlatformString.h"
#if defined( SEMAPHORE_WINDOWS )
#	if ! defined( OS_MSWIN_WCE )
#		include <process.h>
#	endif
#else
#	include <pthread.h>
#	include <semaphore.h>
#	if defined( SEMAPHORE_MACINTOSH )
#		include <sys/time.h>
#	endif
#endif
namespace Yogi { namespace Core {
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

 * CSemaphore - constructor

\+---------------------------------------------------------------------*/
CSemaphore::CSemaphore
		(
		void
		)
{
#if defined( SEMAPHORE_WINDOWS )
#	if defined( OS_MSWIN_WCE )
	swprintf_s( m_sName, sizeof(m_sName), L"sem-%p", this );
	m_sem = CreateSemaphore(NULL, 0, 32767, m_sName );
#	elif defined( OS_MSWIN )
	sprintf_s( m_sName, sizeof(m_sName), "sem-%p", this );
	m_sem = CreateSemaphoreA(NULL, 0, 32767, m_sName);
#	endif
#elif defined( SEMAPHORE_MACINTOSH )
	sprintf_s( m_sName, sizeof(m_sName), "sem-%p", this );
	m_sem = sem_open( m_sName, O_CREAT );
#elif defined( SEMAPHORE_POSIX )
	sem_init(&m_sem, 0, 0);
#endif
}


/*---------------------------------------------------------------------+\

 * ~CSemaphore - destructor

\+---------------------------------------------------------------------*/
CSemaphore::~CSemaphore
		(
		void
		)
{
#if defined( SEMAPHORE_WINDOWS )
	CloseHandle( m_sem );
#elif defined( SEMAPHORE_MACINTOSH )
	sem_close( m_sem );
	sem_unlink( m_sName );
#elif defined( SEMAPHORE_POSIX )
	sem_destroy( &m_sem );
#endif
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Wait -

\+---------------------------------------------------------------------*/
bool	CSemaphore::Wait
		(
		unsigned	nTimeout	// = 0
		)
{
	bool	bResult = false;

	LOCAL_PRINT( "CSemaphore::Wait - pausing\n" );

#if defined( SEMAPHORE_WINDOWS )

	switch ( WaitForSingleObject(m_sem, DWORD(0 == nTimeout ? INFINITE : nTimeout)))
	{
	case WAIT_OBJECT_0:
		bResult = true;
		break;
	case WAIT_TIMEOUT:
		bResult = false;
		break;
	default:
		LogPrint( "CSemaphore::Wait - failure\n" );
		break;
	}

#elif defined( SEMAPHORE_MACINTOSH )

	if ( 0 == nTimeout )	// infinite
	{
		int	retValue;

		do
		{
			retValue = sem_wait( m_sem );
		} while ( retValue < 0  &&  EINTR == errno );

		if ( retValue < 0 )
		{
			LogPrint( "CSemaphore::Wait - failure\n" );
		}
		else
		{
			bResult = true;
		}
	}
	else
	{
		int			retValue = 0;
		itimerval	tv = {0};
#		define ITIMER_VIRTUAL	1

		// NEEDS_WORK: fill in the tv struct for millisecond wait value

		setitimer( ITIMER_VIRTUAL, &tv );
		retValue = sem_wait( m_sem );
		if ( retValue < 0 )
		{
			if ( EINTR == retValue  ||  SIGVTALRM == retValue )
			{
				bResult = false;
			}
			else
			{
				LogPrint( "CSemaphore::Wait - error = %s\n", strerror(errno) );
			}
		}
		else
		{
			bResult = true;
		}
	}

#elif defined( SEMAPHORE_POSIX )

	if ( 0 == nTimeout )	// infinite
	{
		int	retValue;

		do
		{
			retValue = sem_wait( &m_sem );
		} while ( retValue < 0  &&  EINTR == errno );

		if ( retValue < 0 )
		{
			LogPrint( "CSemaphore::Wait - failure\n" );
		}
		else
		{
			bResult = true;
		}
	}
	else
	{
		timespec	ts;

		if ( -1 == clock_gettime( CLOCK_REALTIME, &ts ) )
		{
			LogPrint( "CSemaphore::Wait - clock_gettime returned error\n" );
		}

		ts.tv_sec += nTimeout / 1000;
		ts.tv_nsec += (nTimeout % 1000) * 1000 * 1000;
		ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
		ts.tv_nsec = ts.tv_nsec % (1000 * 1000 * 1000);

		if ( -1 == sem_timedwait( &m_sem, &ts ) )
		{
			if ( ETIMEDOUT == errno )
			{
				bResult = false;
			}
			else
			{
				LogPrint( "CSemaphore::Wait - error = %s\n", strerror(errno) );
			}
		}
		else
		{
			bResult = true;
		}
	}

#endif

	LOCAL_PRINT( "CSemaphore::Wait - Resuming\n" );

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Signal -

\+---------------------------------------------------------------------*/
void	CSemaphore::Signal
		(
		void
		)
{
#if defined( SEMAPHORE_WINDOWS )

	LONG	n = 0;

	ReleaseSemaphore( m_sem, 1, &n );

	LOCAL_PRINT( "CSemaphore::Signal - prev semaphore count = %ld\n", n );

#elif defined( SEMAPHORE_MACINTOSH )

	int	n = sem_post( m_sem );
	if ( n < 0 )
	{
		DebugPrint( "CSemaphore::Signal - problem with semaphore %s - %x\n", m_sName, errno );
	}

#elif defined( SEMAPHORE_POSIX )

	sem_post( &m_sem );

	LOCAL_PRINT( "CSemaphore::Signal - sem_post\n" );
#endif
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

