/*---------------------------------------------------------------------+\
|
|	IDeskManager.h  --  brief description of what IDeskManager.h is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Restrictions/Warnings:
|	Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	15-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IDeskManager
#define _H_IDeskManager
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|
|	Defines
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Type Definitions
|
\+---------------------------------------------------------------------*/

typedef interface_ IDeskManager*			IDeskManagerPtr;

extern const Yogi::Common::IXID	IXID_IDeskManager;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IDeskManager : public Yogi::Common::ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult	SomeFunction
			(
			) PURE;
};


/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	Function Prototypes
||
\+=====================================================================*/
/*=====================================================================+\
||
||	Inline Functions
||
\+=====================================================================*/


}}


#endif /* _H_IDeskManager */
