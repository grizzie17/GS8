/*---------------------------------------------------------------------+\
|
|	ISupportsLocal.h  --  Base Class for all Interfaces
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
	03-Jul-2010			J.Griswold		(Reviewed by: PJH)
		Move definition of IXID to cpp file
		Move NResult to its own file
		Add QI_ macro
	20-Apr-2010			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_ISupportsLocal
#define _H_ISupportsLocal
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "ISupports.h"
#include "UNResult.h"

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

typedef interface_ ISupportsLocal* ISupportsLocalPtr;

extern const IXID COMMON_CLASS IXID_ISupportsLocal;


/*---------------------------------------------------------------------+\
|																		|
|	Class Definitions													|
|																		|
\+---------------------------------------------------------------------*/

interface_ ISupportsLocal : public ISupports
{
    virtual void* QueryInterfaceLocal(
            ConstIXIDRef rIID, Yogi::Core::NResultPtr pResult = 0 ) PURE;
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

}}  // namespace Yogi::Common


#endif /* _H_ISupportsLocal */
