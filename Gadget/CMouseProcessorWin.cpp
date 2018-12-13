/*---------------------------------------------------------------------+\
|
|	CMouseProcessorWin.cpp  --  brief description of what CMouseProcessorWin.cpp is for
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
	13-Mar-2013			J.Griswold
		Change POINT into int x, y
	04-Mar-2010			J.Griswold		(Reviewed by: M.Rose)
		Support for MouseHover
	09-Feb-2010			M.Rose			(Reviewed by: J.Griswold)
		Quick fix for NATC demo, further investigation needed.
	24-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Fix some issues that affect double-click and mouse move.
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Finish the implementation of MouseUp, MouseMove and
		MouseLeave operations
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	03-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CMouseProcessorWin.h"

#include "UFloat.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
//#if defined(OS_MSWIN)

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

 * CMouseProcessorWin - constructor

\+---------------------------------------------------------------------*/
CMouseProcessorWin::CMouseProcessorWin
		(
		void
		)
		: m_pApplication( 0 )
		, m_nLastX( 0 )
		, m_nLastY( 0 )
		, m_bMouseDown( false )
{
}


/*---------------------------------------------------------------------+\

 * ~CMouseProcessorWin - destructor

\+---------------------------------------------------------------------*/
CMouseProcessorWin::~CMouseProcessorWin
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * OnLButtonDown -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWin::OnLButtonDown
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	m_nLastX = x;
	m_nLastY = y;
	m_bMouseDown = true;
	m_pApplication->OnMouseDown( 'L', nFlags, GFLOAT(x), GFLOAT(y) );
}

/*---------------------------------------------------------------------+\

 * OnLButtonUp -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWin::OnLButtonUp
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	m_nLastX = x;
	m_nLastY = y;
	if ( m_bMouseDown )
	{
		m_bMouseDown = false;
		m_pApplication->OnMouseUp( 'L', nFlags, GFLOAT(x), GFLOAT(y) );
	}
}

/*---------------------------------------------------------------------+\

 * OnMouseMove -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWin::OnMouseMove
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	if ( m_bMouseDown )
	{
		if ( x != m_nLastX  ||  y != m_nLastY )
		{
			m_nLastX = x;
			m_nLastY = y;
			m_pApplication->OnMouseMove( 'L', nFlags, GFLOAT(x), GFLOAT(y) );
		}
	}
	else
	{
		if ( x != m_nLastX  ||  y != m_nLastY )
		{
			m_nLastX = x;
			m_nLastY = y;
			m_pApplication->OnMouseHover( 'H', nFlags, GFLOAT(x), GFLOAT(y) );
		}
	}
}

/*---------------------------------------------------------------------+\

 * OnMouseHover -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWin::OnMouseHover
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	if ( ! m_bMouseDown )
	{
		if ( x != m_nLastX  ||  y != m_nLastY )
		{
			m_nLastX = x;
			m_nLastY = y;
			m_pApplication->OnMouseHover( 'H', nFlags, GFLOAT(x), GFLOAT(y) );
		}
	}
}


/*---------------------------------------------------------------------+\

 * OnMouseLeave -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWin::OnMouseLeave
		(
		void
		)
{
	if ( m_bMouseDown )
	{
		OnLButtonUp( 0, m_nLastX, m_nLastY );
	}
}



/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWin::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;
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


}}



//#endif	//	OS_MSWIN

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
