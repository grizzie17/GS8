/*---------------------------------------------------------------------+\
|
|	IPlugin.h  --  common interface for loadable plugins
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
	29-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Add new "ID" function.
	03-Jul-2010			J.Griswold		(Reviewed by: S.Snider)
		Move definition of IXID to cpp file
	20-Apr-2010			J.Griswold		(Reviewed by: S.Snider)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_IPlugin
#define _H_IPlugin
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"

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
typedef interface_ IPlugin*			IPluginPtr;

extern const IXID	IXID_IPlugin;

/*---------------------------------------------------------------------+\
|																		|
|	Interface Definitions												|
|																		|
\+---------------------------------------------------------------------*/

interface_ IPlugin : public ISupports
{

	virtual
	const char*	
			ClassName		///@return pointer to class name
			( 
			void
			) const throw() = 0;

	virtual
	const char*
			ID				///@return pointer to ID name
			(
			void
			) const throw() = 0;

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



#endif /* _H_IPlugin */

