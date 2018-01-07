/*---------------------------------------------------------------------+\
|
|	NamespaceCommon.h  --  brief description of what NamespaceCommon.h is for
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
	07-Apr-2010			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_NamespaceCommon
#define _H_NamespaceCommon
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "NamespaceRoot.h"
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/






#define NAMESPACE_DEFINE_COMMON	(1)



#ifdef NAMESPACE_DEFINE_COMMON

#	define NAMESPACE_COMMON_BEGIN	NAMESPACE_ROOT_BEGIN namespace Common {
#	define NAMESPACE_COMMON_END		} NAMESPACE_ROOT_END
#	define USING_NAMESPACE_COMMON	\
			USING_NAMESPACE_ROOT	\
			using namespace NAMESPACE_ROOT_PREFIX Common;
#	define NAMESPACE_COMMON_PREFIX	NAMESPACE_ROOT_PREFIX Common::

	NAMESPACE_COMMON_BEGIN
	//namespace Common {}
	NAMESPACE_COMMON_END

#else
#	define NAMESPACE_COMMON_BEGIN	NAMESPACE_ROOT_BEGIN
#	define NAMESPACE_COMMON_END		NAMESPACE_ROOT_END
#	define USING_NAMESPACE_COMMON	USING_NAMESPACE_ROOT
#	define NAMESPACE_COMMON_PREFIX	NAMESPACE_ROOT_PREFIX
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


#endif /* _H_NamespaceCommon */
