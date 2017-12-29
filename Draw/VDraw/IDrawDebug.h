/*---------------------------------------------------------------------+\
|
|	IDrawDebug.h  --  brief description of what IDrawDebug.h is for
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
	dd-mmm-9999			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IDrawDebug
#define _H_IDrawDebug
#pragma once
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "UOSIncludes.h"


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

typedef interface_ IDrawDebug*			IDrawDebugPtr;

extern const IXID	IXID_IDrawDebug;

/*---------------------------------------------------------------------+\
|							
|	Interface Definitions	
|							
\+---------------------------------------------------------------------*/

interface_ IDrawDebug : public ISupports
{
	virtual
	void	SetDoubleBackingstore
			(
			bool	b
			) PURE;

	virtual
	void	SetDisplayDirtyRectangle
			(
			bool	b
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


#endif /* _H_IDrawDebug */

