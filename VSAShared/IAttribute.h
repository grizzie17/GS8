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


namespace Yogi { namespace Gadget {
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

extern const Yogi::Common::IXID	IXID_IAttribute;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IAttribute : public Yogi::Common::ISupports
{
	//!
	//!	GetAttribute
	//!
	//!	Retrieves the named attribute as an argument of CVariantData.
	//!
	virtual
	Yogi::Common::CVariantDataPtr
			GetAttribute
			(
			const char*		sName	//!< [in] description of arg2
			) PURE;

	virtual
	Yogi::Common::CVariantDataPtr
			GetAttribute
			(
			Yogi::Core::ConstCCharDescriptorRef	rName	//!< [in] description of arg2
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


}}


#endif /* _H_IAttribute */
