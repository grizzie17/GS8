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

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
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

extern const IXID	IXID_IRepeater;

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
			ConstCCharDescriptorRef	rName,
			long					nMilliSeconds
			) PURE;
};

interface_ IRepeater : public ISupports
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


NAMESPACE_GADGET_END


#endif /* _H_IRepeater */

