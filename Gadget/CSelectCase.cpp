/*---------------------------------------------------------------------+\
|
|	CSelectCase.cpp  --  Implementation of the Case of a Select/Case
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
	27-Aug-2009			J.Griswold
		Allow the "Expression" tag to be used within a "Case" tag
	14-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CSelectCase.h"
#include "CDrawQueue.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * CSelectCase - constructor

\+---------------------------------------------------------------------*/
CSelectCase::CSelectCase
		(
		void
		)
		: VElement(),
		m_tValue(),
		m_aList()
{
}

/*---------------------------------------------------------------------+\

 * CSelectCase - copy constructor

\+---------------------------------------------------------------------*/
CSelectCase::CSelectCase
		(
		ConstCSelectCaseRef	r
		)
		: VElement( r ),
		m_tValue(),
		m_aList()
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CSelectCase - destructor

\+---------------------------------------------------------------------*/
CSelectCase::~CSelectCase
		(
		void
		)
{
	VRenderablePtr*	p = m_aList.PointArray();
	VRenderablePtr*	pEnd = p + m_aList.Length();

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
CSelectCaseRef
		CSelectCase::operator=
		(
		ConstCSelectCaseRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * CalculateCase -

\+---------------------------------------------------------------------*/
int		CSelectCase::CalculateCase
		(
		VDictionaryPtr pDict
		)
{
	if ( m_tValue.Calculate( pDict ) )
		return VRDR_CALCULATE_UNDETERMINED;
	else
		return VRDR_CALCULATE_NONE;
}


/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CSelectCase::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	if ( pDict )
		m_tValue.Calculate( pDict );

	return m_tValue.GetCachedValue();
}


/*---------------------------------------------------------------------+\

 * SetEquation -

\+---------------------------------------------------------------------*/
bool	CSelectCase::SetEquation
		(
		VEquationPtr pEq
		)
{
	return m_tValue.SetEquation( pEq );
}

/*---------------------------------------------------------------------+\

 * SetValue -

\+---------------------------------------------------------------------*/
bool	CSelectCase::SetValue
		(
		ConstCVariantDataRef v
		)
{
	return m_tValue.SetValue( v );
}

/*---------------------------------------------------------------------+\

 * AddRenderable -

\+---------------------------------------------------------------------*/
bool	CSelectCase::AddRenderable
		(
		VRenderablePtr pComp
		)
{
	index_t	n = m_aList.AppendData( &pComp );
	return -1 < n ? true : false;
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

 * Calculate -

\+---------------------------------------------------------------------*/
int		CSelectCase::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int				nResult = VRDR_CALCULATE_NONE;
	VRenderablePtr*	p = m_aList.PointArray();
	VRenderablePtr*	pEnd = p + m_aList.Length();

	while ( p < pEnd )
	{
		if ( *p )
			nResult |= (*p)->Calculate( pDict );
		++p;
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CSelectCase::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr	pQueue
		)
{
	return pQueue->AddGraphic( this );
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CSelectCase::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool			bResult = true;
	VRenderablePtr	*p = m_aList.PointArray();
	VRenderablePtr	*pEnd = p + m_aList.Length();

	if ( p )
	{
		CDrawQueue	tQueue;

		while ( p < pEnd )
		{
			if ( *p )
			{
				bResult = (*p)->PreRender( pDict, &tQueue );
				if ( !bResult )
					break;
			}
			++p;
		}
		if ( bResult )
			bResult = tQueue.RenderGraphics( pDict, pDraw );
	}
	return bResult;
}



/*---------------------------------------------------------------------+\

 * GetChildContext -

\+---------------------------------------------------------------------*/
int		CSelectCase::GetChildContext
		(
		void
		)
{
	int		m = 0;
	VRenderablePtr*	h = m_aList.PointArray();
	if ( h )
	{
		VRenderablePtr*	hEnd = h + m_aList.Length();
		while ( h < hEnd )
		{
			m = (*h)->GetChildContext();
			IncludeContext( m );
			++h;
		}
	}
	return VElement::GetChildContext();
}





}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
