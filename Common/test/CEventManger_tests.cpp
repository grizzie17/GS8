// #include "igloo/igloo.h"
#include "CheckLeaks.h"

#include "iggy.h"


#include "CEventManager.h"
#include "TPointer.h"

using namespace igloo;

using namespace Yogi::Common;
using namespace Yogi::Core;

TEST( CEventManagerTests, it_can_be_created_and_destroyed )
{
    Leaks k;
    {
        TPointer<CEventManager> pEvtMgr = new CEventManager;
    }
    ASSERT_FALSE( k.HasLeaks() );
}

// Context(CEventManager_class)
// {
// 	Spec(it_can_be_created_and_destroyed)
// 	{
// 	}


// };
