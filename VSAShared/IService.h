/*---------------------------------------------------------------------+\
|
|	IService.h  --  brief description of what IService.h is for
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
	08-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IService
#define _H_IService
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"
#include "CCharString.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ IService*		IServicePtr;

extern const IXID	IXID_IService;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IService : public ISupports
{
	//
	//	Start
	//
	//	Begin processing the task
	//
	virtual
	NResult	Start
			(
			void
			) PURE;

	virtual
	NResult	Stop
			(
			void
			) PURE;


	// Properties

	virtual
	bool	IsRunning
			(
			void
			) PURE;

	virtual
	ConstCCharStringRef
			GetID
			(
			void
			) PURE;
};




NAMESPACE_GADGET_END


#endif /* _H_IService */

