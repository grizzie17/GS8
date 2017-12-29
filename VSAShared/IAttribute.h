/*---------------------------------------------------------------------+\
|
|	IAttribute.h  --  brief description of what IAttribute.h is for
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
	30-Sep-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IAttribute
#define _H_IAttribute
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "CVariantData.h"
#include "CCharDescriptor.h"

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

typedef interface_ IAttribute*			IAttributePtr;

extern const IXID	IXID_IAttribute;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IAttribute : public ISupports
{
	//
	//	GetAttribute
	//
	//	Retrieves the named attribute as an argument of CVariantData.
	//
	virtual
	CVariantDataPtr
			GetAttribute
			(
			const char*		sName	// IN:	description of arg2
			) PURE;

	virtual
	CVariantDataPtr
			GetAttribute
			(
			ConstCCharDescriptorRef	rName	// IN:	description of arg2
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


#endif /* _H_IAttribute */

