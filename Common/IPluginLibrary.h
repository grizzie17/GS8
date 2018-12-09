/*---------------------------------------------------------------------+\
|
|	IPluginLibrary.h  --  brief description of what IPluginLibrary.h is for
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
	01-Jan-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IPluginLibrary
#define _H_IPluginLibrary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

#include "CCharString.h"
#include "CCharDescriptor.h"
#include "CVariantData.h"

namespace Yogi { namespace Common {
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

typedef interface_ IPluginLibrary*			IPluginLibraryPtr;

extern const IXID	IXID_IPluginLibrary;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IPluginLibrary : public ISupports
{
	virtual
	ISupportsPtr	Create
					(
					const char*		sLibraryname,
					ISupportsPtr	pOwner = 0
					) PURE;
	virtual
	ISupportsPtr	Create
					( 
					Yogi::Core::ConstCCharDescriptorRef rLibraryname,
					ISupportsPtr	pOwner = 0
					) PURE;

	virtual
	void			SetBaseFolder
					(
					const char* sFolder
					) PURE;

	virtual
	void			SetRelativeFolder
					(
					const char*	sFolder
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


#endif /* _H_IPluginLibrary */

