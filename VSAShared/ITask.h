/*---------------------------------------------------------------------+\
|
|	ITask.h  --  brief description of what ITask.h is for
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
#ifndef _H_ITask
#define _H_ITask
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "NamespaceGadget.h"
NAMESPACE_GADGET_BEGIN
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ ITask*		ITaskPtr;

extern const IXID	IXID_ITask;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ ITask : public ISupports
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
};




NAMESPACE_GADGET_END


#endif /* _H_ITask */

