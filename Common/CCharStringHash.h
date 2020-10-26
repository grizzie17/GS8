/*---------------------------------------------------------------------+\
|
|	CCharStringHash.h  --  brief description of what CCharStringHash.h is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Remove from Gauge namespace
	31-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CCharStringHash_Common
#define _H_CCharStringHash_Common
#pragma once
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "CCharString.h"
#include "CVariantData.h"
#include "THash.h"
#include "UTypes.h"
#include "VPluginConfiguration.h"

/*---------------------------------------------------------------------+\
|																		|
|	Defines																|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Common {
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


//template<>
//unsigned long
//		THashValueFromKey<CCharString>
//		(
//		const CCharString&	key
//		);

template <>
inline uintmax_t
THashTable<Yogi::Core::CCharString, CVariantData>::THashValueFromKey(
        const Yogi::Core::CCharString& key ) const
{
    uintmax_t nHash = key.Hash();
    return nHash;
}


/*=====================================================================+\
||																		|
||	Inline Functions													|
||																		|
\+=====================================================================*/

}}  // namespace Yogi::Common


#endif /* _H_CCharStringHash */
