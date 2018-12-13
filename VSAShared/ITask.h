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


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ ITask*		ITaskPtr;

extern const Yogi::Common::IXID	IXID_ITask;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ ITask : public Yogi::Common::ISupports
{
	//
	//	Start
	//
	//	Begin processing the task
	//
	virtual
	Yogi::Core::NResult	Start
			(
			void
			) PURE;

	virtual
	Yogi::Core::NResult	Stop
			(
			void
			) PURE;
};




}}


#endif /* _H_ITask */
