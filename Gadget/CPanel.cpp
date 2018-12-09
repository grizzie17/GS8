/*---------------------------------------------------------------------+\
|
|	CPanel.cpp  --  brief description of what CPanel.cpp is for
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
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose) [2]
		Optimize the mouse processing
	23-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Implement a "Layout" script capability that allows the
		use of registers and shared data during layout.
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
		Also finally support the concept of the Layout calculation
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	13-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Change class hierarchy and fix calculate bug relative to
		postion class on Gauge.
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
#include <limits.h>

#include "CPanel.h"
#include "CDictionaryMemory.h"


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

 * CPanel - constructor

\+---------------------------------------------------------------------*/
CPanel::CPanel
		(
		void
		)
		: VControlEventMap(),
		m_aChildren(),
		m_pLayout( 0 )
{
}

/*---------------------------------------------------------------------+\

 * CPanel - copy constructor

\+---------------------------------------------------------------------*/
CPanel::CPanel
		(
		CPanelRef	r
		)
		: VControlEventMap( r ),
		m_aChildren(),
		m_pLayout( 0 )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CPanel - destructor

\+---------------------------------------------------------------------*/
CPanel::~CPanel
		(
		void
		)
{
	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();

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
CPanelRef
		CPanel::operator=
		(
		CPanelRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*----------------------------------------------------------------------+\

 * AddChild - add a gauge or panel-division

\+---------------------------------------------------------------------*/
bool	CPanel::AddChild
		(
		VPanelChildPtr pChild
		)
{
	bool	bResult = false;
	index_t	n = (index_t)m_aChildren.Length();
	VPanelChildPtr*	p = m_aChildren.PointItem( n );

	if ( p )
	{
		*p = pChild;
		bResult = true;
	}

	return bResult;
}



/*---------------------------------------------------------------------+\

 * Layout -

\+---------------------------------------------------------------------*/
bool	CPanel::Layout
		(
		VDictionaryPtr	pDict
		)
{
	bool	bResult = false;

	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();

	VDictionaryPtr		pDictMem = pDict;
	CDictionaryMemory	tDictMemory( pDict, this );		// setup local registers
	//if ( 'M' != pDict->GetType() )
		pDictMem = &tDictMemory;

	if ( m_pLayout )
		CVariantData v = m_pLayout->GetValue( pDictMem );
	//VControlEventMap::Calculate( pDictMem );

	while ( p < pEnd )
	{
		if ( *p )
		{
			if ( (*p)->Layout( pDictMem ) )
				bResult = true;
		}
		++p;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * SetLayoutScript -

\+---------------------------------------------------------------------*/
void	CPanel::SetLayoutScript
		(
		VEquationPtr pEq
		)
{
	if ( m_pLayout )
		delete m_pLayout;
	m_pLayout = pEq;
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
int		CPanel::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int		nResult = VRDR_CALCULATE_NONE;

	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();
	//CPositionPtr	pPos;

	nResult |= VControlEventMap::Calculate( pDict );

	while ( p < pEnd )
	{
		if ( *p )
		{
			//pPos = (*p)->Position();
			//if ( pPos )
			//{
			//	if ( pPos->Calculate( pDict ) )
			//		nResult |= VRDR_CALCULATE_LAYOUT;
			//}
			nResult |= (*p)->Calculate( pDict );
		}
		++p;
	}
	return nResult;
}

/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CPanel::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool			bResult = true;
	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();
	CPositionPtr	pPos;
	bool			bProcess;
	GFLOAT			fx;
	GFLOAT			fy;
	long			x;
	long			y;
	long			w;
	long			h;

	long	nLeft;
	long	nTop;
	long	nRight;
	long	nBottom;

	pDraw->GetUpdateRectangle( &nLeft, &nTop, &nRight, &nBottom );

	while ( p < pEnd )
	{
		if ( *p )
		{
			bProcess = true;
			pPos = (*p)->Position();
			fx = pPos->GetX();
			fy = pPos->GetY();
			x = long(fx);
			y = long(fy);
			(*p)->GetSize( pDict, w, h );
			if ( 0 < w  &&  0 < h )
			{
				if ( x+w < nLeft )
					bProcess = false;
				else if ( y+h < nTop )
					bProcess = false;
				else if ( nRight < x )
					bProcess = false;
				else if ( nBottom < y )
					bProcess = false;
			}
			if ( bProcess )
			{
				pDraw->push( fx, fy, 0, 0, 0, 0, 0, 0 );
				bResult = (*p)->Render( pDict, pDraw );
				pDraw->pop();
				if ( ! bResult )
					break;
			}
		}
		++p;
	}
	return bResult;
}

/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	CPanel::GetSize
		(
		VDictionaryPtr,
		long&,
		long&
		)
{
	return false;
}



/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	CPanel::IsDisplayed
		(
		VDictionaryPtr
		)
{
	return true;
}



/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	CPanel::ProcessEvent
		(
		VDictionaryPtr			pDict,
		VDictionary::Selector	vEvent
		)
{
	bool		bResult = false;

	bResult = VControlEventMap::ProcessEvent( pDict, vEvent );
	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();

	while ( p < pEnd )
	{
		if ( *p )
			bResult = (*p)->ProcessEvent( pDict, vEvent )  ||  bResult;
		++p;
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	CPanel::ProcessMouse
		(
		VDictionaryPtr	pDict,
		CMouseLocatePtr	pMouseLocate
		)
{
	bool			bResult = true;		// is the mouse action going to bubble up
	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();
	CPositionPtr	pPos;
	bool			bProcess;
	GFLOAT			fx;
	GFLOAT			fy;
	//long			x;
	//long			y;
	long			w;
	long			h;

	pMouseLocate->push( 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 );
	while ( p < pEnd  &&  bResult )
	{
		if ( *p )
		{
			if ( 0 < (*p)->MouseAreas() )
			{
				bProcess = true;
				pPos = (*p)->Position();
				fx = pPos->GetX();
				fy = pPos->GetY();
				//x = long(fx);
				//y = long(fy);
				(*p)->GetSize( pDict, w, h );
				if ( 0 < w  &&  0 < h )
				{
					if ( ! pMouseLocate->Locate( fx, fy, fx+w, fy+h ) )
						bProcess = false;
				}
				if ( bProcess )
				{
					pMouseLocate->push( fx, fy, 0, 0, 0, 0, 0, 0 );
					bResult = (*p)->ProcessMouse( pDict, pMouseLocate );
					pMouseLocate->pop();
				}
			}
		}
		++p;
	}
	pMouseLocate->pop();
	return bResult;
}



/*---------------------------------------------------------------------+\

 * CalculateDirtyRectangle -

\+---------------------------------------------------------------------*/
int		CPanel::CalculateDirtyRectangle
		(
		VDictionaryPtr pDict,
		long*			pLeft,
		long*			pTop,
		long*			pRight,
		long*			pBottom
		)
{
	int		nResult = VRDR_CALCULATE_NONE;
	int		nCalc;
	long	nLeft = LONG_MAX;
	long	nTop = LONG_MAX;
	long	nRight = LONG_MIN;
	long	nBottom = LONG_MIN;

	VPanelChildPtr*	p = m_aChildren.PointArray();
	VPanelChildPtr*	pEnd = p + m_aChildren.Length();
	CPositionPtr	pPos;

	//nResult |= VControlEventMap::Calculate( pDict );

	while ( p < pEnd )
	{
		if ( *p )
		{
			nCalc = (*p)->Calculate( pDict );
			if ( nCalc )
			{
				pPos = (*p)->Position();
				if ( pPos )
				{
					long	x;
					long	y;
					long	w;
					long	h;

					(*p)->GetSize( pDict, w, h );
					if ( 0 < w  &&  0 < h )
					{
						x = long(pPos->GetX());
						y = long(pPos->GetY());
						if ( x < nLeft )
							nLeft = x;
						if ( y < nTop )
							nTop = y;
						w += x;
						h += y;
						if ( nRight < w )
							nRight = w;
						if ( nBottom < h )
							nBottom = h;
					}
					else
					{
						nLeft = 0;
						nTop = 0;
						nRight = LONG_MAX - 2;
						nBottom = LONG_MAX - 2;
					}
				}

			}
			nResult |= nCalc;
		}
		++p;
	}

	*pLeft = nLeft - 2;
	*pTop = nTop - 2;
	*pRight = nRight + 2;
	*pBottom = nBottom + 2;
	return nResult;
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
