/*---------------------------------------------------------------------+\
|
|	CHusk.cpp  --  holder of other objects
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
	01-Nov-2011			J.Griswold		(Reviewed by: xxxx)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|					
|	Include Files	
|					
\+---------------------------------------------------------------------*/
#include "Stdafx.h"
#include "CHusk.h"
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

 * CHusk - constructor

\+---------------------------------------------------------------------*/
CHusk::CHusk
		(
		void
		)
		: inherited()
		, m_bRunning( false )
		, m_pConfiguration( 0 )
		, m_pServiceManager( 0 )
{
}

CHusk::CHusk
		(
		ISupportsPtr	pOwner
		)
		: inherited( pOwner )
		, m_bRunning( false )
		, m_pConfiguration( 0 )
		, m_pServiceManager( 0 )
{
}

CHusk::CHusk
		(
		const char*		sName,
		ISupportsPtr	pOwner
		)
		: inherited( sName, pOwner )
		, m_bRunning( false )
		, m_pConfiguration( 0 )
		, m_pServiceManager( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CHusk - copy constructor

\+---------------------------------------------------------------------*/
CHusk::~CHusk
		(
		void
		)
{
	if ( m_bRunning )
		Stop();

	if ( m_pServiceManager )
		m_pServiceManager->Release();
}

/*=====================================================================+\
||	 interface implementation functions
\+=====================================================================*/

/*---------------------------------------------------------------------+\
|	 IHusk
\+---------------------------------------------------------------------*/


/*---------------------------------------------------------------------+\

 * AddService -

\+---------------------------------------------------------------------*/
NResult
		CHusk::AddService
		(
		ISupportsPtr	,//pI,
		const char*		//sName
		)
{
	NResult	nr = NR_S_OK;

	return nr;
}


/*---------------------------------------------------------------------+\

 * AddStorage -

\+---------------------------------------------------------------------*/
NResult
		CHusk::AddStorage
		(
		ISupportsPtr	,//pI,
		const char*		//sName
		)
{
	NResult	nr = NR_S_OK;

	return nr;
}


/*---------------------------------------------------------------------+\

 * AddWidget -

\+---------------------------------------------------------------------*/
NResult
		CHusk::AddWidget
		(
		ISupportsPtr	,//pI,
		const char*		//sName
		)
{
	NResult	nr = NR_S_OK;

	return nr;
}




/*=====================================================================+\
||	 public member functions
\+=====================================================================*/

//virtual
bool	CHusk::SpecifyConfiguration
		(
		const char*	sPath
		)
{
	CFactoryConfiguration	factory;
	VConfigurationPtr	pCfg = factory.Make( sPath );
	if ( pCfg )
		return true;
	else
		return false;
}

//virtual
bool	CHusk::Start
		(
		void
		)
{
	// insert startup code here


	m_bRunning = true;
	return false;
}

//virtual
bool	CHusk::Stop
		(
		void
		)
{
	m_bRunning = false;

	// insert other shutdown code here
	return false;
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

/*---------------------------------------------------------------------+\

 * FindInternalInterface -

\+---------------------------------------------------------------------*/
void*	CHusk::FindInternalInterface
		(
		ConstIXIDRef	rIID
		)
{
	void*	pI = inherited::FindInternalInterface( rIID );
	if ( ! pI )
	{
		if ( rIID == IXID_IHusk )
			pI = INTERFACE_THIS( IHuskPtr );
		else
			pI = 0;
	}

	return pI;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/


NAMESPACE_GADGET_END

