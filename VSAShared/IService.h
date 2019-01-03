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


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ IService*		IServicePtr;

extern const Yogi::Common::IXID	IXID_IService;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IService : public Yogi::Common::ISupports
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


	// Properties

	virtual
	bool	IsRunning
			(
			void
			) PURE;

	virtual
	Yogi::Core::ConstCCharStringRef
			GetID
			(
			void
			) PURE;
};




}}


#endif /* _H_IService */
