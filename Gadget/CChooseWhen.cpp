/*---------------------------------------------------------------------+\
|
|	CChooseWhen.cpp  --  Implementation of the When of a Choose/When
|
|	Purpose:
|	File Custodian:		J.Griswold
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
	10-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CChooseWhen.h"

#include "CDrawQueue.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/

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

 * CChooseWhen - constructor

\+---------------------------------------------------------------------*/
CChooseWhen::CChooseWhen
		(
		void
		)
		: VElement(),
		m_tValue(),
		m_aList()
{
}

/*---------------------------------------------------------------------+\

 * CChooseWhen - copy constructor

\+---------------------------------------------------------------------*/
CChooseWhen::CChooseWhen
		(
		ConstCChooseWhenRef	r
		)
		: VElement( r ),
		m_tValue(),
		m_aList()
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CChooseWhen - destructor

\+---------------------------------------------------------------------*/
CChooseWhen::~CChooseWhen
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
CChooseWhenRef
		CChooseWhen::operator=
		(
		ConstCChooseWhenRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * CalculateWhen -

\+---------------------------------------------------------------------*/
int		CChooseWhen::CalculateWhen
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
		CChooseWhen::GetValue
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
bool	CChooseWhen::SetEquation
		(
		VEquationPtr pEq
		)
{
	return m_tValue.SetEquation( pEq );
}

/*---------------------------------------------------------------------+\

 * SetValue -

\+---------------------------------------------------------------------*/
bool	CChooseWhen::SetValue
		(
		ConstCVariantDataRef v
		)
{
	return m_tValue.SetValue( v );
}

/*---------------------------------------------------------------------+\

 * AddRenderable -

\+---------------------------------------------------------------------*/
bool	CChooseWhen::AddRenderable
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
int		CChooseWhen::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int				nResult = VRDR_CALCULATE_NONE;
	VRenderablePtr*	p = m_aList.PointArray();
	if ( p )
	{
		VRenderablePtr*	pEnd = p + m_aList.Length();

		while ( p < pEnd )
		{
			if ( *p )
				nResult |= (*p)->Calculate( pDict );
			++p;
		}
	}
	return nResult;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CChooseWhen::PreRender
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
bool	CChooseWhen::Render
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
int		CChooseWhen::GetChildContext
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
