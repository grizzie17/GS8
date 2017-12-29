/*---------------------------------------------------------------------+\
|
|	CMouseProcessorWB.cpp  --  brief description of what CMouseProcessorWB.cpp is for
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
#include "CMouseProcessorWB.h"

#include "UFloat.h"
NAMESPACE_GADGET_BEGIN
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

 * CMouseProcessorWB - constructor

\+---------------------------------------------------------------------*/
CMouseProcessorWB::CMouseProcessorWB
		(
		void
		)
		: m_pRealProcessor( 0 )
		, m_pApplication( 0 )
		, m_tFudge()
{
	GFLOAT	fx = 1600;
	GFLOAT	fy = 900;
	CMatrix3x3	work;
	m_tFudge = work;

	work *= CMatrix3x3::_ReflectY();
	work *= CMatrix3x3::_ReflectX();
	work *= CMatrix3x3::_Translate( fx, fy );
	work *= CMatrix3x3::_Scale( double(8) );

	m_tFudge = work;
}


/*---------------------------------------------------------------------+\

 * ~CMouseProcessorWB - destructor

\+---------------------------------------------------------------------*/
CMouseProcessorWB::~CMouseProcessorWB
		(
		void
		)
{
	if ( m_pRealProcessor )
		delete m_pRealProcessor;
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * OnLButtonDown -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::SetMouseProcessor
		(
		VMouseProcessorWinPtr p
		)
{
	if ( p != m_pRealProcessor )
	{
		if ( m_pRealProcessor )
			delete m_pRealProcessor;
	}
	m_pRealProcessor = p;
}


/*---------------------------------------------------------------------+\

 * OnLButtonDown -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::OnLButtonDown
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	GFLOAT	fx = GFLOAT(x);
	GFLOAT	fy = GFLOAT(y);

	m_tFudge.Transform( fx, fy, fx, fy );

	x = int(fx);
	y = int(fy);

	m_pRealProcessor->OnLButtonDown( nFlags, x, y );
}

/*---------------------------------------------------------------------+\

 * OnLButtonUp -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::OnLButtonUp
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	GFLOAT	fx = GFLOAT(x);
	GFLOAT	fy = GFLOAT(y);

	m_tFudge.Transform( fx, fy, fx, fy );

	x = int(fx);
	y = int(fy);

	m_pRealProcessor->OnLButtonUp( nFlags, x, y );

}

/*---------------------------------------------------------------------+\

 * OnMouseMove -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::OnMouseMove
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	GFLOAT	fx = GFLOAT(x);
	GFLOAT	fy = GFLOAT(y);

	m_tFudge.Transform( fx, fy, fx, fy );

	x = int(fx);
	y = int(fy);

	m_pRealProcessor->OnMouseMove( nFlags, x, y );

}

/*---------------------------------------------------------------------+\

 * OnMouseHover -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::OnMouseHover
		(
		uint_t	nFlags,
		int		x,
		int		y
		)
{
	GFLOAT	fx = GFLOAT(x);
	GFLOAT	fy = GFLOAT(y);

	m_tFudge.Transform( fx, fy, fx, fy );

	x = int(fx);
	y = int(fy);

	m_pRealProcessor->OnMouseHover( nFlags, x, y );
}


/*---------------------------------------------------------------------+\

 * OnMouseLeave -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::OnMouseLeave
		(
		void
		)
{
	m_pRealProcessor->OnMouseLeave();
}



/*---------------------------------------------------------------------+\

 * SetApplication -

\+---------------------------------------------------------------------*/
void	CMouseProcessorWB::SetApplication
		(
		CApplicationGaugePtr p
		)
{
	m_pApplication = p;
	m_pRealProcessor->SetApplication( p );
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


NAMESPACE_GADGET_END




/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

