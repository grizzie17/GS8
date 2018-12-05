#include "stdafx.h"
#include "ISupports.h"

namespace Yogi { namespace Common {


const IXID	IXID_ISupports( "Yogi::Common::ISupports" );

// this is a special ID that should always return the controlling
//	ISupports of the local object (not the owner).
const IXID	IXID_IRootSupports( "Yogi::Common::IRootSupports" );


}}
