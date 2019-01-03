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


namespace Yogi { namespace Gadget {
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

extern const Yogi::Common::IXID	IXID_IBox;

/*---------------------------------------------------------------------+\
|
|	Interface Definitions
|
\+---------------------------------------------------------------------*/

interface_ IBox : public Yogi::Common::ISupports
{
	//
	//	SomeFunction
	//
	//	Description of what SomeFunction is used for along with any
	//	operational restrictions.
	//
	virtual
	Yogi::Core::NResult	OnLoad
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnUnload
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnShow
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnHide
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnFocus
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnBlur
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnResize
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnMove
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnMoving
			(
			) PURE;

	virtual
	Yogi::Core::NResult	OnDraw
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


}}


#endif /* _H_IBox */
