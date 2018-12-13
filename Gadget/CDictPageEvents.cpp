/*---------------------------------------------------------------------+\
|
|	CDictPageEvents.cpp  --  Lazy Load Variables
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
	17-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Better support the "standard" update functions
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	14-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Don't let raising events set the dictionary to dirty.
	10-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDictPageEvents.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {

/*---------------------------------------------------------------------+\
|																		|
|	Local Type Definitions												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Private Global Variables											|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Public Global Variables												|
|																		|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	External Variables													|
|																		|
\+---------------------------------------------------------------------*/
/*=====================================================================+\
||																		|
||	 Code																|
||																		|
\+=====================================================================*/
/*=====================================================================+\
||	 class lifecycle functions											|
\+=====================================================================*/
/*---------------------------------------------------------------------+\

 * CDictPageEvents - constructor

\+---------------------------------------------------------------------*/
CDictPageEvents::CDictPageEvents
		(
		void
		)
		: CDictPageLazyLoad()
		, m_pEventQueue( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageEvents - destructor

\+---------------------------------------------------------------------*/
CDictPageEvents::~CDictPageEvents
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * SetEventQueue - set event queue pointer

\+---------------------------------------------------------------------*/
void	CDictPageEvents::SetEventQueue
		(
		CQueuePtr	p
		)
{
	m_pEventQueue = p;
}



/*---------------------------------------------------------------------+\

 * EventQueue - get pointer to event queue

\+---------------------------------------------------------------------*/
CQueuePtr
		CDictPageEvents::EventQueue
		(
		void
		)
{
	return m_pEventQueue;
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/




/*---------------------------------------------------------------------+\

 * PutData -

\+---------------------------------------------------------------------*/
bool	CDictPageEvents::PutData
		(
		unsigned long			nSel,
		ConstCVariantDataPtr	pData
		)
{
	return UpdateEntry( nSel, *pData );
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageEvents::UpdateByName
		(
		ConstCCharDescriptorRef	rKey,
		ConstCVariantDataRef	rData
		)
{
	bool	bResult = false;
	long	n = long(m_aContent.IndexOf( CCharString( rKey ) ));
	if ( -1 < n )
	{
		bResult = UpdateEntry( (unsigned long)n, rData );
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * UpdateEntry -

\+---------------------------------------------------------------------*/
bool	CDictPageEvents::UpdateEntry
		(
		unsigned long			nSel,
		ConstCVariantDataRef	rData
		)
{
	CVariantDataPtr	p = m_aContent.ItemAtIndex( nSel );
	if ( p )
	{
		if ( m_pEventQueue )
		{
			VDictionary::Selector	vSel = m_pDictionary->MakeSelector( m_cPageID, (long)nSel );
			m_pEventQueue->Push( vSel );
		}
		if ( *p != rData )
		{
			*p = rData;
			//if ( ! m_pEventQueue )
				//m_pDictionary->SetDirty( true );
		}

		return true;
	}
	else
	{
		return false;
	}
}



/*---------------------------------------------------------------------+\

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageEvents::AddAlias
		(
		ConstCCharDescriptorRef	rKey,
		ConstCCharDescriptorRef	rAlias
		)
{
	CCharString	tKey( rKey );
	CCharString	tAlias( rAlias );
	return m_aContent.AddAlias( tKey, tAlias );
}




}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
