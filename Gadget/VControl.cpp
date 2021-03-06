/*---------------------------------------------------------------------+\
|
|	VControl.cpp  --  brief description of what VControl.cpp is for
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
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	11-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add update frequency support
	11-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "VControl.h"
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

 * VControl - constructor

\+---------------------------------------------------------------------*/
VControl::VControl
		(
		void
		)
		: VOwnership()
		, m_pName( 0 )
		, m_pUpdate( 0 )
		, m_nFrequency( 0 )
		, m_nNextUpdate( 0 )
		, m_pAction( 0 )
		, m_nMouseAreas( 0 )
{
}


/*---------------------------------------------------------------------+\

 * ~VControl - destructor

\+---------------------------------------------------------------------*/
VControl::~VControl
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Name -

\+---------------------------------------------------------------------*/
CCharStringPtr
		VControl::Name
		(
		void
		)
{
	if ( ! m_pName )
		m_pName = new CCharString;
	return m_pName;
}


/*---------------------------------------------------------------------+\

 * SetUpdate -

\+---------------------------------------------------------------------*/
bool	VControl::SetUpdate
		(
		VEquationPtr p
		)
{
	if ( m_pUpdate )
		delete m_pUpdate;
	m_pUpdate = p;
	return true;
}



/*---------------------------------------------------------------------+\

 * SetUpdateFrequency -

\+---------------------------------------------------------------------*/
bool	VControl::SetUpdateFrequency
		(
		int	n
		)
{
	m_nFrequency = n;
	m_nNextUpdate = 0;
	return true;
}


/*---------------------------------------------------------------------+\

 * Action -

\+---------------------------------------------------------------------*/
VActionPtr
		VControl::Action
		(
		void
		)
{
	return m_pAction;
}

/*---------------------------------------------------------------------+\

 * SetAction -

\+---------------------------------------------------------------------*/
bool	VControl::SetAction
		(
		VActionPtr	p
		)
{
	if ( m_pAction )
		delete m_pAction;
	m_pAction = p;
	return true;
}


/*---------------------------------------------------------------------+\

 * MouseAreas -

\+---------------------------------------------------------------------*/
int		VControl::MouseAreas
		(
		void
		)
{
	return m_nMouseAreas;
}

/*---------------------------------------------------------------------+\

 * IncrementMouseAreas -

\+---------------------------------------------------------------------*/
int		VControl::IncrementMouseAreas
		(
		int	n
		)
{
	if ( n < 1 )
		n = 1;
	m_nMouseAreas += n;
	return m_nMouseAreas;
}


/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	VControl::ProcessEvent
		(
		VDictionaryPtr			pDict,
		VDictionary::Selector	vEvent
		)
{
	bool	bResult = false;
	if ( m_pAction )
		bResult = m_pAction->ProcessEvent( pDict, vEvent );
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	VControl::ProcessMouse
		(
		VDictionaryPtr,
		CMouseLocatePtr
		)
{
	return false;
}


/*=====================================================================+\
||	 protected member functions											|
\+=====================================================================*/

/*---------------------------------------------------------------------+\

 * CanCalculate -

\+---------------------------------------------------------------------*/
bool	VControl::CanCalculate
		(
		VDictionaryPtr	pDict
		)
{
	bool	bCalc = true;
	if ( 0 < m_nFrequency )
	{
		long	nMilli = pDict->GetMilliseconds();
		if ( nMilli < m_nNextUpdate )
		{
			bCalc = false;
		}
		else
		{
			m_nNextUpdate = m_nFrequency + nMilli;
		}
	}
	return bCalc;
}

/*=====================================================================+\
||	 private member functions											|
\+=====================================================================*/

/*=====================================================================+\
||																		|
||	 Overrides															|
||																		|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
int		VControl::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int	nResult = VRDR_CALCULATE_NONE;

	if ( m_pUpdate )
		CVariantData v = m_pUpdate->GetValue( pDict );
	return nResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
