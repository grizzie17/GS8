/*---------------------------------------------------------------------+\
|
|	CCircle.cpp  --  brief description of what CCircle.cpp is for
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
	01-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CCircle.h"
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

 * CCircle - constructor

\+---------------------------------------------------------------------*/
CCircle::CCircle
		(
		void
		)
		: VGraphic()
		, m_tAxis()
		, m_tRadius()
{
}

/*---------------------------------------------------------------------+\

 * CCircle - copy constructor

\+---------------------------------------------------------------------*/
CCircle::CCircle
		(
		CCircleRef	r
		)
		: VGraphic( r )
		, m_tAxis( r.m_tAxis )
		, m_tRadius( r.m_tRadius )
{
}

/*---------------------------------------------------------------------+\

 * ~CCircle - destructor

\+---------------------------------------------------------------------*/
CCircle::~CCircle
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/

/*----------------------------------------------------------------------+\

 * operator= - assignment operator

\+---------------------------------------------------------------------*/
CCircleRef
		CCircle::operator=
		(
		CCircleRef	r
		)
{
	VGraphic::operator=( r );
	m_tAxis = r.m_tAxis;
	m_tRadius = r.m_tRadius;
	return *this;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CCircle::Axis
		(
		void
		)
{
	return &m_tAxis;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CCircle::Radius
		(
		void
		)
{
	return &m_tRadius;
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
int		CCircle::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	nResult |= m_tAxis.Calculate( pDict );
	if ( m_tRadius.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CCircle::Render
		(
		VDictionaryPtr pDict,
		VDrawPtr pDraw
		)
{
	bool	bResult = VGraphic::Render( pDict, pDraw );

	GFLOAT	x = m_tAxis.GetX();
	GFLOAT	y = m_tAxis.GetY();
	GFLOAT	r = m_tRadius.GetCachedValue();

	pDraw->Circle( x, y, r );

	return bResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
