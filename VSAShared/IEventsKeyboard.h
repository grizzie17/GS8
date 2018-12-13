/*---------------------------------------------------------------------+\
|
|	IEventsKeyboard.h  --  brief description of what IEventsKeyboard.h is for
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
	05-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IEventsKeyboard
#define _H_IEventsKeyboard
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include <time.h>
#include "UKeys.h"


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

typedef interface_ IEventsKeyboard*			IEventsKeyboardPtr;

extern const Yogi::Common::IXID	IXID_IEventsKeyboard;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IEventsKeyboard : public ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult	KeyDown
			(
			int		k,
			time_t	nTime
			) PURE;

	virtual
	Yogi::Core::NResult	KeyUp
			(
			int		k,
			time_t	nTime
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


#endif /* _H_IEventsKeyboard */
