/*---------------------------------------------------------------------+\
|
|	CScreen.cpp  --
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
	12-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Optimize the handling of the active panel
	09-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Dirty-Rectangle processing for display management
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	13-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		React to hierarchy change to VControlKeyEventMap
	29-Aug-2009			J.Griswold		(Reviewed by: M.Rose)
		React to class hierarchy change for CCharString/CCharDescriptor
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
#include "CScreen.h"
#include "LogFile.h"

using namespace Yogi::Core;
using namespace Yogi::Common;
namespace Yogi { namespace Gadget {
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
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

 * CScreen - constructor

\+---------------------------------------------------------------------*/
CScreen::CScreen
		(
		void
		)
		: VControlEventMap()
		, m_vActivePanel()
		, m_pActivePanel( 0 )
		, m_tPanelList()
		, m_nWidth( 0 )
		, m_nHeight( 0 )
{
	m_tPanelList.SetHashTableSize( 20 );
}


/*---------------------------------------------------------------------+\

 * ~CScreen - destructor

\+---------------------------------------------------------------------*/
CScreen::~CScreen
		(
		void
		)
{
	CPanelPtr*	p = m_tPanelList.Items();
	CPanelPtr*	pEnd = p + m_tPanelList.Count();

	if ( p )
	{
		while ( p < pEnd )
		{
			if ( *p )
				delete *p;
			++p;
		}
	}
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * AddPanel -

\+---------------------------------------------------------------------*/
bool	CScreen::AddPanel
		(
		CPanelPtr	p,
		const char*	sName
		)
{
	CCharString	tName( sName );
	return m_tPanelList.Add( tName, p );
}


/*---------------------------------------------------------------------+\

 * GetEnumerator -

\+---------------------------------------------------------------------*/
CPanelEnumerator
		CScreen::GetEnumerator
		(
		void
		)
{
	return m_tPanelList.GetEnumerator();
}


/*---------------------------------------------------------------------+\

 * SetActivePanelEquation -

\+---------------------------------------------------------------------*/
bool	CScreen::SetActivePanelEquation
		(
		VEquationPtr p
		)
{
//	bool	bResult = false;

	return m_vActivePanel.SetEquation( p );
}


/*---------------------------------------------------------------------+\

 * PanelKeyEventMap - get the active panel's KeyEventMap

\+---------------------------------------------------------------------*/
CKeyEventMapPtr
		CScreen::PanelKeyEventMap
		(
		void
		)
{
	CKeyEventMapPtr	pResult = 0;
	CPanelPtr		pPanel = 0;

	CCharString	sActive = m_vActivePanel.GetCachedValue();
	if ( 0 < sActive.Length() )
	{
		CPanelPtr*	h = (CPanelPtr*)m_tPanelList.Find( sActive );
		if ( h )
		{
			pPanel = *h;
		}
	}
	if ( pPanel )
	{
		pResult = pPanel->KeyEventMap();
	}
	return pResult;
}



/*---------------------------------------------------------------------+\

 * SetSize -

\+---------------------------------------------------------------------*/
bool	CScreen::SetSize
		(
		int		x,
		int		y
		)
{
	bool	bResult = false;

	if ( x != m_nWidth )
	{
		bResult = true;
		m_nWidth = x;
	}
	if ( y != m_nHeight )
	{
		bResult = true;
		m_nHeight = y;
	}

	return bResult;
}


/*---------------------------------------------------------------------+\

 * Layout - calculate the panel layout

\+---------------------------------------------------------------------*/
bool	CScreen::Layout
		(
		VDictionaryPtr	pDict
		)
{
	bool		bResult = false;

	m_vActivePanel.Calculate( pDict );

	//if ( ! m_pActivePanel )
	//{
		CCharString	sActive = m_vActivePanel.GetCachedValue();
		if ( 0 < sActive.Length() )
		{
			CPanelPtr*	h = (CPanelPtr*)m_tPanelList.Find( sActive );
			if ( h )
			{
				m_pActivePanel = *h;
			}
			else
			{
 				LogPrint( "CScreen - Active Panel not found: %s\n", sActive.Pointer() );
			}
		}
		else
		{
			LogPrint( "CScreen - Calculate of Active Panel failed\n" );
		}
	//}
	if ( m_pActivePanel )
	{
		bResult = m_pActivePanel->Layout( pDict );
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

 * Calculate -

\+---------------------------------------------------------------------*/
int		CScreen::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int			nResult = VRDR_CALCULATE_NONE;
	CCharString	sActive;
	CVariantData	v;

	pDict->BeginCalculate();

	nResult |= VControlEventMap::Calculate( pDict );

	// ActivePanel calculate returns true then we have switched panels
	if ( m_vActivePanel.Calculate( pDict ) )
	{
		v = m_vActivePanel.GetCachedValue();
		sActive = v.GetValueCCharString();
		if ( 0 < sActive.Length() )
		{
			CPanelPtr*	h = (CPanelPtr*)m_tPanelList.Find( sActive );
			if ( h )
			{
				m_pActivePanel = *h;
			}
		}
		VDictionary::Selector tSel = pDict->LocateEntry( "E:ACTIVATE PANEL" );
		pDict->PutData( tSel, &v );
		nResult |= VRDR_CALCULATE_LAYOUT;
	}
	else
	{
		if ( m_pActivePanel )
		{
			nResult |= m_pActivePanel->Calculate( pDict );
		}
	}

	pDict->EndCalculate();

	return nResult;
}

/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CScreen::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool		bResult = false;

	if ( m_pActivePanel )
	{
		bResult = m_pActivePanel->Render( pDict, pDraw );
	}

	return bResult;
}

/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	CScreen::GetSize
		(
		VDictionaryPtr,
		long&			rnWidth,
		long&			rnHeight
		)
{
	rnWidth = m_nWidth;
	rnHeight = m_nHeight;
	return true;
}

/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	CScreen::IsDisplayed
		(
		VDictionaryPtr
		)
{
	return true;
}



/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	CScreen::ProcessEvent
		(
		VDictionaryPtr			pDict,
		VDictionary::Selector	vEvent
		)
{
	bool	bResult = false;

	pDict->BeginCalculate();

	bResult = VControlEventMap::ProcessEvent( pDict, vEvent );

	if ( m_pActivePanel )
	{
		bResult = m_pActivePanel->ProcessEvent( pDict, vEvent )  ||  bResult;
	}

	pDict->EndCalculate();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	CScreen::ProcessMouse
		(
		VDictionaryPtr	pDict,
		CMouseLocatePtr	pMouseLocate
		)
{
	bool		bResult = false;

	pDict->BeginCalculate();

	if ( m_pActivePanel )
	{
		if ( 0 < m_pActivePanel->MouseAreas() )
			bResult = m_pActivePanel->ProcessMouse( pDict, pMouseLocate )  ||  bResult;
	}

	pDict->EndCalculate();

	return bResult;
}


/*---------------------------------------------------------------------+\

 * CalculateDirtyRectangle -

\+---------------------------------------------------------------------*/
int		CScreen::CalculateDirtyRectangle
		(
		VDictionaryPtr	pDict,
		long*			pLeft,
		long*			pTop,
		long*			pRight,
		long*			pBottom
		)
{
	int			nResult = VRDR_CALCULATE_NONE;

	pDict->BeginCalculate();

	nResult |= VControlEventMap::Calculate( pDict );

	// ActivePanel calculate returns true then we have switched panels
	if ( m_vActivePanel.Calculate( pDict ) )
	{
		CCharString	sActive = m_vActivePanel.GetCachedValue();
		if ( 0 < sActive.Length() )
		{
			CPanelPtr*	h = (CPanelPtr*)m_tPanelList.Find( sActive );
			if ( h )
			{
				m_pActivePanel = *h;
			}
		}
		VDictionary::Selector tSel = pDict->LocateEntry( "E:ACTIVATE PANEL" );
		CVariantData	v( 1L );
		pDict->PutData( tSel, &v );
		nResult |= VRDR_CALCULATE_LAYOUT;
		*pLeft = 0;
		*pTop = 0;
		*pRight = m_nWidth;
		*pBottom = m_nHeight;
	}
	else
	{
		if ( m_pActivePanel )
		{
			int	nCalc = m_pActivePanel->CalculateDirtyRectangle( pDict, pLeft, pTop, pRight, pBottom );
			if ( nCalc )
			{
				if ( *pRight < *pLeft )
				{
					*pLeft = 0;
					*pRight = m_nWidth;
				}
				if ( *pBottom < *pTop )
				{
					*pTop = 0;
					*pBottom = m_nHeight;
				}
				// don't overflow the screen's limits
				if ( *pLeft < 0 )
					*pLeft = 0;
				if ( *pTop < 0 )
					*pTop = 0;
				if ( m_nWidth < *pRight )
					*pRight = m_nWidth;
				if ( m_nHeight < *pBottom )
					*pBottom = m_nHeight;
			}
			nResult |= nCalc;
		}
	}

	pDict->EndCalculate();

	return nResult;
}




}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
