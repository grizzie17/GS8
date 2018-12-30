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
/*---------------------------------------------------------------------+\
|
|	Include Files
|
\+---------------------------------------------------------------------*/
//#include "stdafx.h"
#include "CEventManager.h"
namespace Yogi { namespace Common {
/*---------------------------------------------------------------------+\
|
|	Local defines / constants
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Local Type Definitions
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Private Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Public Global Variables
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	External Variables
|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||
||	 Code
||
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions
\+=====================================================================*/
/**--------------------------------------------------------------------+\

* <summary>CEventManager - constructor</summary>

* <remarks/>

\+---------------------------------------------------------------------*/
CEventManager::CEventManager
		(
		void
		)
		: inherited()
{
}

/**--------------------------------------------------------------------+\

* <summary>CEventManager - copy constructor</summary>

* <remarks/>

\+---------------------------------------------------------------------*/
CEventManager::CEventManager
		(
		ConstCEventManagerRef	r
		)
		: inherited(r)
{
	// TODO: add instructions to copy data from "r" to "this"
}

/**--------------------------------------------------------------------+\

* <summary>~CEventManager - destructor</summary>

* <remarks/>

\+---------------------------------------------------------------------*/
CEventManager::~CEventManager
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

/**---------------------------------------------------------------------+\

* <summary>operator= - assignment operator</summary>

* <remarks/>

\+---------------------------------------------------------------------*/
CEventManagerRef
		CEventManager::operator=
		(
		ConstCEventManagerRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*=====================================================================+\
||	 protected member functions
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions
\+=====================================================================*/

/*=====================================================================+\
||
||	 Overrides
||
\+=====================================================================*/


}}


/**--------------------------------------------------------------------+\

* <summary>someFunction - brief statement</summary>

* <remarks/>

\+---------------------------------------------------------------------*/
