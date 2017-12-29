/*---------------------------------------------------------------------+\
|
|	IKeyboard.h  --  brief description of what IKeyboard.h is for
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
	06-Jul-2012			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IKeyboard
#define _H_IKeyboard
#pragma once
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "NamespaceCommon.h"
NAMESPACE_COMMON_BEGIN
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

typedef interface_ IKeyboard*			IKeyboardPtr;

extern const IXID	IXID_IKeyboard;

/*---------------------------------------------------------------------+\
|							
|	Interface Definitions	
|							
\+---------------------------------------------------------------------*/

interface_ IKeyboard
{
	virtual
		bool	KeyDown
				(
				int nKeycode,
				int mModifier,
				int nRepeat
				) PURE;

	virtual
		bool	KeyUp
				(
				int nKeycode,
				int mModifier,
				int nRepeat
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


NAMESPACE_COMMON_END


#endif /* _H_IKeyboard */

