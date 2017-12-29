/*---------------------------------------------------------------------+\
|
|	IEssStatus.h  --  brief description of what IEssStatus.h is for
|
|	Purpose:
|	File Custodian:		F.Lastname
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
	dd-mmm-9999			F.Lastname		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IEssStatus
#define _H_IEssStatus
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "CVariantData.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
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

typedef interface_ IEssStatus*			IEssStatusPtr;
typedef interface_ IEssStatus&			IEssStatusRef;
typedef const interface_ IEssStatus&	ConstIEssStatusRef;

extern const IXID	IXID_IEssStatus;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IEssStatus : public ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	NResult	UpdateCount
			(
			long		nIndex,
			long		nCount
			) PURE;

	virtual
	NResult	UpdateProcessorState
			(
			long		nPort,
			long		nProc,
			long		nState
			) PURE;

	virtual
	NResult	Notify
			(
			long		nIndex,
			ConstCCharStringRef	rMessage
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


NAMESPACE_GADGET_END


#endif /* _H_IEssStatus */

