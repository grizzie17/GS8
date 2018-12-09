/*---------------------------------------------------------------------+\
|
|	CElement.cpp  --  brief description of what CElement.cpp is for
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
	23-Jan-2009			J.Griswold		(Reviewed by: M.Rose)
		Fixed a problem regarding fore/background.
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	25-Jun-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CElement.h"

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

 * CElement - constructor

\+---------------------------------------------------------------------*/
CElement::CElement
		(
		void
		)
		: VElement(),
		m_aList(),
		m_pVisible( 0 ),
		m_eContext( CTX_GROUP )
{
}

/*---------------------------------------------------------------------+\

 * CElement - copy constructor

\+---------------------------------------------------------------------*/
CElement::CElement
		(
		CElementRef	r
		)
		: VElement( r )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CElement - destructor

\+---------------------------------------------------------------------*/
CElement::~CElement
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

	if ( m_pVisible )
		delete m_pVisible;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CElementRef
		CElement::operator=
		(
		CElementRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * AddRenderable -

\+---------------------------------------------------------------------*/
bool	CElement::AddRenderable
		(
		VRenderablePtr pComp
		)
{
	index_t	n = m_aList.AppendData( &pComp );
	return -1 < n ? true : false;
}


/*---------------------------------------------------------------------+\

 * SetVisible -

\+---------------------------------------------------------------------*/
bool	CElement::SetVisible
		(
		CVisiblePtr	p
		)
{
	m_pVisible = p;
	return true;
}


/*---------------------------------------------------------------------+\

 * SetContext -

\+---------------------------------------------------------------------*/
void	CElement::SetContext
		(
		CElement::EContext	ctx
		)
{
	m_eContext = ctx;
}


/*---------------------------------------------------------------------+\

 * Context -

\+---------------------------------------------------------------------*/
CElement::EContext
		CElement::Context
		(
		void
		)
{
	return m_eContext;
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

 * GetChildContext -

\+---------------------------------------------------------------------*/
int		CElement::GetChildContext
		(
		void
		)
{
	VRenderablePtr*	h = m_aList.PointArray();
	if ( h )
	{
		VRenderablePtr*	hEnd = h + m_aList.Length();
		while ( h < hEnd )
		{
			int	m = (*h)->GetChildContext();
			IncludeContext( m );
			++h;
		}
	}
	return VElement::GetChildContext();
}


/*---------------------------------------------------------------------+\

 * Calculate -

\+---------------------------------------------------------------------*/
int		CElement::Calculate
		(
		VDictionaryPtr	pDict
		)
{
	int				nResult = VRDR_CALCULATE_NONE;
	bool			bVis = true;
	VRenderablePtr	*p = m_aList.PointArray();
	VRenderablePtr	*pEnd = p + m_aList.Length();

	if ( m_pVisible )
	{
		nResult = m_pVisible->Calculate( pDict );
		if ( nResult )
		{
			nResult = m_mChildrenContext
					? m_mChildrenContext
					: VRDR_CALCULATE_UNDETERMINED;
		}
		bVis = m_pVisible->GetValue();
	}

	if ( bVis )
	{
		while ( p < pEnd )
		{
			if ( *p )
				nResult |= (*p)->Calculate( pDict );
			++p;
		}

	}

	// fix undetermined flag
	if ( 0 != (VRDR_CALCULATE_UNDETERMINED & nResult) )
	{
		nResult &= ~VRDR_CALCULATE_UNDETERMINED;	// clear flag
		switch ( m_eContext )
		{
		case CTX_FOREGROUND:
			nResult |= VRDR_CALCULATE_FOREGROUND;
			break;
		case CTX_BACKGROUND:
			nResult |= VRDR_CALCULATE_BACKGROUND;
			break;
		case CTX_APPLICATION:
			nResult |= VRDR_CALCULATE_APPLICATION;
			break;
		case CTX_GROUP:
		case CTX_UNDETERMINED:
		default:
			if ( 0 == (nResult
						& (VRDR_CALCULATE_BACKGROUND
							| VRDR_CALCULATE_FOREGROUND
							| VRDR_CALCULATE_APPLICATION)) )
			{
				nResult |= m_mChildrenContext
						? m_mChildrenContext
						: VRDR_CALCULATE_UNDETERMINED;
				//nResult |= VRDR_CALCULATE_UNDETERMINED;
			}
			break;
		}
	}

	return nResult;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CElement::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr	pQueue
		)
{
	if ( m_pVisible )
	{
		if ( m_pVisible->GetValue() )
			return pQueue->AddGraphic( this );
		else
			return true;
	}
	else
	{
		return pQueue->AddGraphic( this );
	}
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CElement::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool			bResult = true;
	bool			bVis = true;

	if ( m_pVisible )
	{
		bVis = m_pVisible->GetValue();
	}

	if ( bVis )
	{
		bool	bProcess = true;

		if ( pDraw->SupportsContext() )
		{
			VDraw::EDrawContexts	eDrawCtx;
			eDrawCtx = pDraw->CurrentContext();

			switch ( m_eContext )
			{
			case CTX_APPLICATION:
				if (VDraw::CTX_APPLICATION != eDrawCtx)
					bProcess = false;
				break;
			case CTX_BACKGROUND:
				if (VDraw::CTX_BACKGROUND != eDrawCtx)
					bProcess = false;
				break;
			case CTX_FOREGROUND:
				if (VDraw::CTX_FOREGROUND != eDrawCtx)
					bProcess = false;
				break;
			case CTX_GROUP:
			default:
				bProcess = true;
				break;
			}
		}

		if ( bProcess )
		{
			VRenderablePtr	*p = m_aList.PointArray();

			if ( p )
			{
				VRenderablePtr	*pEnd = p + m_aList.Length();
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
		}
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	CElement::GetSize
		(
		VDictionaryPtr,
		long&,
		long&
		)
{
	return true;
}


/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	CElement::IsDisplayed
		(
		VDictionaryPtr	pDict
		)
{
	if ( m_pVisible )
	{
		m_pVisible->Calculate( pDict );
		return m_pVisible->GetValue();
	}
	else
	{
		return true;
	}
}




}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
