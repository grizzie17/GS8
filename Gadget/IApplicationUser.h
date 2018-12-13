/*---------------------------------------------------------------------+\
|
|	IApplicationUser.h  --  brief description of what IApplicationUser.h is for
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
	24-Oct-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IApplicationUser
#define _H_IApplicationUser
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "CApplicationGauge.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ IApplicationUser*			IApplicationUserPtr;

extern const Yogi::Common::IXID	IXID_IApplicationUser;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IApplicationUser : public Yogi::Common::ISupports
{
	//
	//!	SetApplication
	//!
	//!	Provide this object access to the application object
	//
	virtual
	bool	SetApplication
			(
			CApplicationGaugePtr	p	// IN:	application pointer
			) PURE;
};


/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	Function Prototypes													|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/


}}


#endif /* _H_IApplicationUser */
