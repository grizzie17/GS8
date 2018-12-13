/*---------------------------------------------------------------------+\
|
|	IRepeater.h  --  brief description of what IRepeater.h is for
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
	05-Jun-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IRepeater
#define _H_IRepeater
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "CCharDescriptor.h"
#include "CApplicationGauge.h"


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

typedef interface_ IRepeater*			IRepeaterPtr;

extern const Yogi::Common::IXID	IXID_IRepeater;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

// this "interface" is handed to the IRepeater::Initialize method
struct VRepeaterSetup
{
	virtual
	bool	RegisterRepeater
			(
			const char*	sName,
			long		nMilliSeconds
			) PURE;

	virtual
	bool	RegisterRepeater
			(
			Yogi::Core::ConstCCharDescriptorRef	rName,
			long								nMilliSeconds
			) PURE;
};

interface_ IRepeater : public Yogi::Common::ISupports
{
	virtual
	bool	Initialize
			(
			CApplicationGaugePtr	pApplication,
			VRepeaterSetup*			pRepeaterSetup = 0
			) PURE;

	virtual
	bool	Cycle
			(
			void
			) PURE;


	virtual
	bool	Idle
			(
			void
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


#endif /* _H_IRepeater */
