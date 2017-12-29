/*---------------------------------------------------------------------+\
|
|	IBox.h  --  brief description of what IBox.h is for
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
	21-Dec-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IBox
#define _H_IBox
#pragma once
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "ISupports.h"

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

typedef interface_ IBox*			IBoxPtr;

extern const IXID	IXID_IBox;

/*---------------------------------------------------------------------+\
|							
|	Interface Definitions	
|							
\+---------------------------------------------------------------------*/

interface_ IBox : public ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	NResult	OnLoad
			(
			) PURE;

	virtual
	NResult	OnUnload
			(
			) PURE;

	virtual
	NResult	OnShow
			(
			) PURE;

	virtual
	NResult	OnHide
			(
			) PURE;

	virtual
	NResult	OnFocus
			(
			) PURE;

	virtual
	NResult	OnBlur
			(
			) PURE;

	virtual
	NResult	OnResize
			(
			) PURE;

	virtual
	NResult	OnMove
			(
			) PURE;

	virtual
	NResult	OnMoving
			(
			) PURE;

	virtual
	NResult	OnDraw
			(
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


#endif /* _H_IBox */

