/*---------------------------------------------------------------------+\
|	Delete this comment block
|
|	globally substitute "CEventManager" to be the name of this file (no suffix).
|	globally substitute "26-Dec-2014" to be today's date.
|	globally substitute "J.Griswold" to be your First initial and Lastname
|	add brief description at the top of the file.
|
|	globally substitute "CEventManager" to be the name of this class.
|	substitute "BaseClass" to be the name of the base class.
|
|	Delete this comment block
\+---------------------------------------------------------------------*/
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
#include "VObject.h"

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
typedef class CEventManager*			CEventManagerPtr;
typedef class CEventManager&			CEventManagerRef;
typedef const class CEventManager&	ConstCEventManagerRef;
/*---------------------------------------------------------------------+\
|
|	Class Definitions
|
\+---------------------------------------------------------------------*/

class CEventManager : public VObject
{
	//	class lifecycle  ----------------------------------------------------
public:
	CEventManager();
	CEventManager(ConstCEventManagerRef r);	// copy constructor
	virtual			~CEventManager();

public:
	//	public types  -------------------------------------------------------

	//	public functions  ---------------------------------------------------

	CEventManagerRef	operator=(ConstCEventManagerRef r);		// assignment

protected:
	//	protected types  ----------------------------------------------------

	//	protected functions  ------------------------------------------------

	//	protected data  -----------------------------------------------------

private:
	//	private types  ------------------------------------------------------

	typedef VObject	inherited;

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

NAMESPACE_COMMON_END



#endif /* _H_CEventManager */

