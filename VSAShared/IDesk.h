/*---------------------------------------------------------------------+\
|
|	IDesk.h  --  brief description of what IDesk.h is for
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
#ifndef _H_IDesk
#define _H_IDesk
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "IDraw.h"


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

typedef interface_ IDesk*			IDeskPtr;

extern const Yogi::Common::IXID	IXID_IDesk;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IDesk : public Yogi::Common::ISupports
{

	virtual
	Yogi::Core::NResult	OnActivate
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnDeactivate
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnRender
			(
			Yogi::Common::VDrawPtr	pDraw
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


#endif /* _H_IDesk */
