/*---------------------------------------------------------------------+\
|
|	IHusk.h  --  interface for generalized Husk
|
|	Purpose:
|
		A container for other containers
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
	14-Dec-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IHusk
#define _H_IHusk
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
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/

typedef interface_ IHusk*			IHuskPtr;

extern const IXID	IXID_IHusk;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IHusk : public ISupports
{
	//
	//	AddService
	//
	//	Add a new service to the Husk
	//
	virtual
	NResult	AddService
			(
			ISupportsPtr	pI,
			const char*		sName
			) PURE;

	virtual
	ISupportsPtr
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



	virtual
	NResult	AddStorage
			(
			ISupportsPtr	pI,
			const char*		sName
			) PURE;

	virtual
	ISupportsPtr
			FindStorageByName
			(
			const char* sName 
			) PURE;



	virtual
	NResult	AddWidget
			(
			ISupportsPtr	pI,
			const char*		sName
			) PURE;

	virtual
	ISupportsPtr
			MakeWidget
			(
			const char*		sName
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


#endif /* _H_IHusk */

