#include "iggy.h"

#include "CSemaphore.h"
#include "UPlatform.h"
#include "UPlatformThreads.h"
#include "UPlatformTime.h"

// #include "igloo/igloo.h"
// using namespace igloo;

using namespace Yogi::Core;

class MockThread
{
public:
    UThreadHdl m_thread;
    int        m_nValue;
    void
    start()
    {
        m_thread = ::ThreadCreate(
                static_cast<UThreadFunction>( thread ), this );
    }
    static UThreadRtn THREADAPI
    thread( void* this_ )
    {
        MockThread* pThis = static_cast<MockThread*>( this_ );
        usleep( 1000 );
        pThis->m_nValue++;
        pThis->m_sem.Signal();
        return 0;
    }
    CSemaphore m_sem;

    MockThread()
            : m_thread( 0 )
            , m_nValue( 0 )
            , m_sem()
    {}
    ~MockThread()
    {
        if ( m_thread )
            ::ThreadClose( m_thread );
    }
};

TEST( CSemaphoreTests, it_should_wait_until_signaled )
{
    MockThread thrd;

    thrd.start();
    bool b = thrd.m_sem.Wait( 2000 );

    ASSERT_TRUE( b );
    ASSERT_EQ( 1, thrd.m_nValue );
}
