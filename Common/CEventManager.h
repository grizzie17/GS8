/*=====================================================================*/
/**
*	@file	CEventManager.h
*	@brief	description of what CEventManager.h is for
*
* @if optional_topics (delete if not used)
*	@details
*	@author	J.Griswold
*
*	@attention
*	@warning
*	@note
*	@see someOtherFile.h
* @endif
*/
/*=====================================================================*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	26-Dec-2014			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
#ifndef _H_CEventManager
#define _H_CEventManager
#pragma once
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
#include "UDeclCommon.h"
#include "VObject.h"

namespace Yogi { namespace Common {
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
typedef class CEventManager*       CEventManagerPtr;
typedef class CEventManager&       CEventManagerRef;
typedef const class CEventManager& ConstCEventManagerRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class COMMON_CLASS CEventManager : public VObject
{
    //	class lifecycle  ----------------------------------------------------
public:
    CEventManager();
    CEventManager( ConstCEventManagerRef r );  // copy constructor
    virtual ~CEventManager();

public:
    //	public types  -------------------------------------------------------

    //	public functions  ---------------------------------------------------

    CEventManagerRef
    operator=( ConstCEventManagerRef r );  // assignment

protected:
    //	protected types  ----------------------------------------------------

    //	protected functions  ------------------------------------------------

    //	protected data  -----------------------------------------------------

private:
    //	private types  ------------------------------------------------------

    typedef VObject inherited;

    //	private functions  --------------------------------------------------

    //	private data  -------------------------------------------------------

    //============================== Overrides ==============================
    // -- delete this section if this is a root class --
    //	root
    //	BaseClass-1
    //	BaseClass
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

}}  // namespace Yogi::Common


#endif /* _H_CEventManager */
