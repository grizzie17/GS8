/*---------------------------------------------------------------------+\
|
|	IMouseTransform.h  --  load plugin configuration data
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
	09-Aug-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IMouseTransform
#define _H_IMouseTransform
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "UFloat.h"

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
extern const IXID	IXID_IMouseTransform;

typedef interface_ IMouseTransform*			IMouseTransformPtr;
/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IMouseTransform : public ISupports
{

	// set the size of the mouse area (screen)
	virtual
	bool	SetSize
			(
			long	nWidth,
			long	nHeight
			) = 0;


	virtual
	bool	Transform
			(
			GFLOAT*		pOutX,
			GFLOAT*		pOutY,
			GFLOAT&		rInX,
			GFLOAT&		rInY
			) = 0;


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



#endif /* _H_IMouseTransform */

