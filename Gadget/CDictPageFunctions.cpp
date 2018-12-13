/*---------------------------------------------------------------------+\
|
|	CDictPageFunctions.cpp  --  Process function requests
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
	29-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		AddAlias support
	16-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Enumerator
		Implement new globally standardized update functions
	22-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CDictPageFunctions.h"
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

 * CDictPageFunctions - constructor

\+---------------------------------------------------------------------*/
CDictPageFunctions::CDictPageFunctions
		(
		void
		)
		: CDictPageVariant()
		, m_pFunctions( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~CDictPageFunctions - destructor

\+---------------------------------------------------------------------*/
CDictPageFunctions::~CDictPageFunctions
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
void	CDictPageFunctions::SetFunctionProcessor
		(
		VFunctionProcessorPtr	p
		)
{
	m_pFunctions = p;
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
bool	CDictPageFunctions::PutData
		(
		unsigned long		nSel,
		const CVariantData*	pData
		)
{
	CVariantDataPtr	p = m_aContent.ItemAtIndex( nSel );
	if ( p )
	{
		if ( m_pFunctions )
		{
			VDictionary::Selector	vSel = m_pDictionary->MakeSelector( m_cPageID, (long)nSel );
			m_pFunctions->ProcessRequest( vSel, *pData );
		}
		if ( *p != *pData )
		{
			*p = *pData;
		}

		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * UpdateByName -

\+---------------------------------------------------------------------*/
bool	CDictPageFunctions::UpdateByName
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

 * AddAlias -

\+---------------------------------------------------------------------*/
bool	CDictPageFunctions::AddAlias
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
