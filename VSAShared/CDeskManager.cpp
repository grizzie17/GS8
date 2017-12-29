/*---------------------------------------------------------------------+\
|
|	CDeskManager.cpp  --  brief description of what CDeskManager.cpp is for
|
|	Purpose:
|
| optional topics (delete if not used)
|	Usage:
|	Restrictions/Warnings:
|	Algorithms/Formats:
|	References:
|	Notes:
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|
|	Revision History:					(most recent entries first)
|
	16-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDeskManager.h"
//USING_NAMESPACE_COMMON
NAMESPACE_GADGET_BEGIN
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
/*---------------------------------------------------------------------+\

 * CDeskManager - constructor

\+---------------------------------------------------------------------*/
CDeskManager::CDeskManager
		(
		void
		)
		: VSupports()
{
}

CDeskManager::CDeskManager
		(
		ISupportsPtr	pOwner
		)
		: VSupports( pOwner )
{
}

CDeskManager::CDeskManager
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: VSupports( sName, pOwner )
{
}

/*---------------------------------------------------------------------+\

 * CDeskManager - copy constructor

\+---------------------------------------------------------------------*/
CDeskManager::~CDeskManager
		(
		void
		)
{
}

/*=====================================================================+\
||	 interface implementation functions
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IDeskManager
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
NResult
		CDeskManager::SomeFunction
		(
		)
{
	NResult	nr = NR_S_OK;

	return nr;
}


/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

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

/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CDeskManager::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = VSupports::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IDeskManager )
			pI = INTERFACE_THIS( IDeskManagerPtr );
		else
			pI = 0;
	}

	return pI;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/


NAMESPACE_GADGET_END

