/*---------------------------------------------------------------------+\
|
|	CTrigger.cpp  --  manage the equation and its resulting value
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
	16-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Resolve compiler warning generated by GCC++
	05-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add SetName that uses descriptor to send the name instead
		of null terminated string.
	29-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CTrigger.h"
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

 * CTrigger - constructor

\+---------------------------------------------------------------------*/
CTrigger::CTrigger
		(
		void
		)
		: VEquation()
		, m_tSelector()
		, m_pEquation( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CTrigger - copy constructor

\+---------------------------------------------------------------------*/
CTrigger::CTrigger
		(
		ConstCTriggerRef	r
		)
		: VEquation( r )
		, m_tSelector( r.m_tSelector )
		, m_pEquation( 0 )
{
	if ( r.m_pEquation )
		m_pEquation = r.m_pEquation->Clone();
}

/*---------------------------------------------------------------------+\

 * ~CTrigger - destructor

\+---------------------------------------------------------------------*/
CTrigger::~CTrigger
		(
		void
		)
{
	if ( m_pEquation )
		delete m_pEquation;
	m_pEquation = 0;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CTriggerRef
		CTrigger::operator=
		(
		ConstCTriggerRef	r
		)
{
	m_tSelector = r.m_tSelector;
	if ( m_pEquation )
		delete m_pEquation;
	if ( r.m_pEquation )
		m_pEquation = r.m_pEquation->Clone();
	else
		m_pEquation = 0;
	return *this;
}


/*---------------------------------------------------------------------+\

 * Calculate - calculated data

\+---------------------------------------------------------------------*/
bool	CTrigger::Calculate
		(
		VDictionaryPtr pDict
		)
{
	bool	bResult = false;
	if ( m_pEquation )
	{
		Yogi::Common::CVariantData	vData = m_pEquation->GetValue( pDict );

		bResult = true;
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * SetName -

\+---------------------------------------------------------------------*/
bool	CTrigger::SetName
		(
		const char*	sName
		)
{
	m_tSelector.SetName( sName );
	return true;
}


/*---------------------------------------------------------------------+\

 * SetName -

\+---------------------------------------------------------------------*/
bool	CTrigger::SetName
		(
		ConstCCharDescriptorRef rName
		)
{
	m_tSelector.SetName( rName );
	return true;
}


/*---------------------------------------------------------------------+\

 * SetEquation - Assign equation pointer

\+---------------------------------------------------------------------*/
bool	CTrigger::SetEquation
		(
		VEquationPtr pEquation
		)
{
	if ( pEquation )
	{
		if ( m_pEquation )
			delete m_pEquation;
		m_pEquation = pEquation;
		return true;
	}
	else
	{
		return false;
	}
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CTrigger::Equals
		(
		VDictionaryPtr			pDict,
		VDictionary::Selector	ds
		)
{
	bool					bResult = false;
	VDictionary::Selector	tSel;

	tSel = m_tSelector.GetSelector( pDict );
	if ( tSel )
	{
		if ( tSel == ds )
			bResult = true;
	}

	return bResult;
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

 * GetValue -

\+---------------------------------------------------------------------*/
Yogi::Common::CVariantData
		CTrigger::GetValue
		(
		VDictionaryPtr pDict
		)
{
	Yogi::Common::CVariantData	vData = (Yogi::Common::CVariantData)m_pEquation->GetValue( pDict );
	return vData;
}


/*---------------------------------------------------------------------+\

 * Clone -

\+---------------------------------------------------------------------*/
VEquationPtr
		CTrigger::Clone
		(
		void
		)
{
	return new CTrigger( *this );
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
