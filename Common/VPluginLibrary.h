/*---------------------------------------------------------------------+\
|
|	VPluginLibrary.h  --  brief description of what VPluginLibrary.h is for
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
	07-Jun-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_VPluginLibrary
#define _H_VPluginLibrary
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "IPluginLibrary.h"

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
typedef	IPluginLibrary		VPluginLibrary;
typedef	IPluginLibrary*		VPluginLibraryPtr;
#if 0
typedef class VPluginLibrary*		VPluginLibraryPtr;
typedef class VPluginLibrary&		VPluginLibraryRef;
typedef const class VPluginLibrary&	ConstVPluginLibraryRef;
#endif
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/
#if 0

class VPluginLibrary
{
//	class lifecycle  ----------------------------------------------------
public:
	virtual			~VPluginLibrary(){};

public:
//	public types  -------------------------------------------------------

//	public functions  ---------------------------------------------------

	virtual
	ISupportsPtr	Create
					(
					const char*		sLibraryname, 
					ISupportsPtr	pOwner = 0
					) = 0;
	virtual
	ISupportsPtr	Create
					( 
					ConstCCharDescriptorRef rLibraryname,
					ISupportsPtr	pOwner = 0
					) = 0;

	virtual
	void			SetBaseFolder
					(
					const char* sFolder
					) = 0;

	virtual
	void			SetRelativeFolder
					(
					const char*	sFolder
					) = 0;



};

#endif

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



#endif /* _H_VPluginLibrary */

