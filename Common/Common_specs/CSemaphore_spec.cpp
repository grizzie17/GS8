#include "stdafx.h"
#include "igloo/igloo.h"

#include "UPlatform.h"
#include "UPlatformThreads.h"
#include "CSemaphore.h"

using namespace igloo;

USING_NAMESPACE_COMMON

class MockThread
{
public:
	UThreadHdl	m_thread;
	int			m_nValue;
	void start()
	{
		m_thread = ThreadCreate( static_cast<UThreadFunction>(thread), this );
	}
	static UThreadRtn THREADAPI thread( void * this_ )
	{
		MockThread*	pThis = static_cast<MockThread*>( this_ );
		usleep( 1000 );
		pThis->m_nValue++;
		pThis->m_sem.Signal();
		return 0;
	}
	CSemaphore	m_sem;

	MockThread() : m_thread( 0 ), m_nValue(0), m_sem()
	{}
	~MockThread()
	{
		if ( m_thread )
			ThreadClose( m_thread );
	}
};

Context( CSemaphore_class )
{
	Spec( it_should_wait_until_signaled )
	{
		MockThread	thrd;

		thrd.start();
		bool	b = thrd.m_sem.Wait( 2000 );

		AssertThat( b, Equals( true ) );
		AssertThat( thrd.m_nValue, Equals( 1 ) );
	}

};

