/*---------------------------------------------------------------------+\
|
|	IServiceManager.h  --  brief description of what IServiceManager.h is for
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
#ifndef _H_IServiceManager
#define _H_IServiceManager
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"
#include "CCharString.h"
#include "IService.h"


namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ IServiceManager*		IServiceManagerPtr;

extern const IXID	IXID_IServiceManager;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IServiceManager : public ISupports
{
	virtual
	IServicePtr
			FindServiceByName
			(
			const char* sName
			) PURE;


	virtual
	ISupportsPtr
			FindServiceByIF
			(
			ConstIXIDRef rIID
			) PURE;
};




}}


#endif /* _H_IServiceManager */
