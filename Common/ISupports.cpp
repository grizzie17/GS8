#include "stdafx.h"
#include "ISupports.h"

NAMESPACE_COMMON_BEGIN


const IXID	IXID_ISupports( "BCG::Common::ISupports" );

// this is a special ID that should always return the controlling
//	ISupports of the local object (not the owner).
const IXID	IXID_IRootSupports( "BCG::Common::IRootSupports" );


NAMESPACE_COMMON_END
