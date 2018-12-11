/*---------------------------------------------------------------------+\
|
|	CAction.cpp  --  brief description of what CAction.cpp is for
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
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	30-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CAction.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

namespace Yogi { namespace Gadget {
//USING_NAMESPACE_COMMON

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

 * CAction - constructor

\+---------------------------------------------------------------------*/
CAction::CAction
		(
		void
		)
		: VAction()
		, m_aTriggers()
{
}

/*---------------------------------------------------------------------+\

 * CAction - copy constructor

\+---------------------------------------------------------------------*/
CAction::CAction
		(
		ConstCActionRef	r
		)
		: VAction( r )
		, m_aTriggers()
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CAction - destructor

\+---------------------------------------------------------------------*/
CAction::~CAction
		(
		void
		)
{
	CTriggerPtr*	p = m_aTriggers.PointArray();
	CTriggerPtr*	pEnd = p + m_aTriggers.Length();

	while ( p < pEnd )
	{
		if ( *p )
			delete *p;
		++p;
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CActionRef
		CAction::operator=
		(
		ConstCActionRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}



/*----------------------------------------------------------------------+\

 * AddChild - add a gauge or panel-division

\+---------------------------------------------------------------------*/
bool	CAction::AddTrigger
		(
		CTriggerPtr pTrigger
		)
{
	bool			bResult = false;
	index_t			n = (index_t)m_aTriggers.Length();
	CTriggerPtr*	p = m_aTriggers.PointItem( n );

	if ( p )
	{
		*p = pTrigger;
		bResult = true;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CAction::Merge
		(
		CActionPtr pAction
		)
{
	CTriggerPtr*	p = pAction->m_aTriggers.PointArray();
	CTriggerPtr*	pEnd = p + pAction->m_aTriggers.Length();

	while ( p < pEnd )
	{
		if ( *p )
		{
			AddTrigger( *p );
			*p = 0;
		}
		++p;
	}

	pAction->m_aTriggers.Clear();
	return true;
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

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CAction::ProcessEvent
		(
		VDictionaryPtr			pDict,
		VDictionary::Selector	vEvent
		)
{
	bool	bResult = false;

	CTriggerPtr*	p = m_aTriggers.PointArray();
	if ( p )
	{
		CTriggerPtr*	pEnd = p + m_aTriggers.Length();

		while ( p < pEnd )
		{
			if ( *p )
			{
				if ( (*p)->Equals( pDict, vEvent ) )
					bResult = (*p)->Calculate( pDict )  ||  bResult;
			}
			++p;
		}
	}

	return bResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
