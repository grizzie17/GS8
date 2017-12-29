/*---------------------------------------------------------------------+\
|
|	NamespaceGadget.h  --  brief description of what NamespaceGadget.h is for
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
	01-May-2010			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_NamespaceGadget
#define _H_NamespaceGadget
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceCommon.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#define NAMESPACE_DEFINE_GADGET	(1)

#if NAMESPACE_DEFINE_GADGET

#	define NAMESPACE_GADGET_BEGIN	\
			NAMESPACE_ROOT_BEGIN	\
			using namespace Common;	\
			namespace Gadget {
#	define NAMESPACE_GADGET_END		} NAMESPACE_ROOT_END
#	define USING_NAMESPACE_GADGET	\
			USING_NAMESPACE_ROOT	\
			USING_NAMESPACE_COMMON	\
			using namespace NAMESPACE_ROOT_PREFIX Gadget;
#	define NAMESPACE_GADGET_PREFIX	NAMESPACE_ROOT_PREFIX Gadget::

	NAMESPACE_GADGET_BEGIN
	//namespace Gadget {}
	NAMESPACE_GADGET_END

#else
#	define NAMESPACE_GADGET_BEGIN
#	define NAMESPACE_GADGET_END
#	define USING_NAMESPACE_GADGET
#	define NAMESPACE_GADGET_PREFIX
#endif


/*---------------------------------------------------------------------+\
|																		|
|	Type Definitions													|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/
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


#endif /* _H_NamespaceGadget */

