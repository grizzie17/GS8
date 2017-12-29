/*---------------------------------------------------------------------+\
|
|	NamespaceRoot.h  --  brief description of what NamespaceCommon.h is for
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
#ifndef _H_NamespaceRoot
#define _H_NamespaceRoot
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/

#define NAMESPACE_DEFINE_ROOT	(1)

#ifdef NAMESPACE_DEFINE_ROOT

#	define NAMESPACE_ROOT_BEGIN		namespace BCGRoot {
#	define NAMESPACE_ROOT_END		}
#	define USING_NAMESPACE_ROOT		using namespace BCGRoot;
#	define NAMESPACE_ROOT_PREFIX	BCGRoot::

	// declare namespace
	namespace BCGRoot {}


#else

#	define NAMESPACE_ROOT_BEGIN
#	define NAMESPACE_ROOT_END
#	define USING_NAMESPACE_ROOT
#	define NAMESPACE_ROOT_PREFIX	::

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


#endif /* _H_NamespaceRoot */

