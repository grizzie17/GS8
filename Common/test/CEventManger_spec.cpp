#include "igloo/igloo.h"
#include "CheckLeaks.h"



#include "CEventManager.h"
#include "TPointer.h"

using namespace igloo;

using namespace Yogi::Common;
using namespace Yogi::Core;

Context(CEventManager_class)
{
	Spec(it_can_be_created_and_destroyed)
	{
		Leaks	k;
		{
			TPointer<CEventManager>	pEvtMgr = new CEventManager;
		}
		AssertThat(k.HasLeaks(), IsFalse());
	}



};

