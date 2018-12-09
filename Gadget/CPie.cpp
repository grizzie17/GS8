/*---------------------------------------------------------------------+\
|
|	CPie.cpp  --  Implementation of Pie graphic object
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
	28-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Make the StartAngle and EndAngle input in degrees to
		be compatible with the V2 schema
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
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
#include "CPie.h"
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

 * CPie - constructor

\+---------------------------------------------------------------------*/
CPie::CPie
		(
		void
		)
		: VGraphic(),
		m_tAxis(),
		m_tRadius(),
		m_tStartAngle(),
		m_tEndAngle()
{
}

/*---------------------------------------------------------------------+\

 * CPie - copy constructor

\+---------------------------------------------------------------------*/
CPie::CPie
		(
		CPieRef	r
		)
		: VGraphic( r ),
		m_tAxis( r.m_tAxis ),
		m_tRadius( r.m_tRadius ),
		m_tStartAngle( r.m_tStartAngle ),
		m_tEndAngle( r.m_tEndAngle )
{
}

/*---------------------------------------------------------------------+\

 * ~CPie - destructor

\+---------------------------------------------------------------------*/
CPie::~CPie
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
CPieRef
		CPie::operator=
		(
		CPieRef	r
		)
{
	VGraphic::operator=( r );
	m_tAxis = r.m_tAxis;
	m_tRadius = r.m_tRadius;
	m_tStartAngle = r.m_tStartAngle;
	m_tEndAngle = r.m_tEndAngle;
	return *this;
}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CPie::Axis
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
		CPie::Radius
		(
		void
		)
{
	return &m_tRadius;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CPie::StartAngle
		(
		void
		)
{
	return &m_tStartAngle;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CPie::EndAngle
		(
		void
		)
{
	return &m_tEndAngle;
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
int		CPie::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	nResult |= m_tAxis.Calculate( pDict );
	if ( m_tRadius.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	if ( m_tStartAngle.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	if ( m_tEndAngle.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
bool	CPie::Render
		(
		VDictionaryPtr pDict,
		VDrawPtr pDraw
		)
{
	bool	bResult = VGraphic::Render( pDict, pDraw );

	GFLOAT	x = m_tAxis.GetX();
	GFLOAT	y = m_tAxis.GetY();
	GFLOAT	r = m_tRadius.GetCachedValue();
	GFLOAT	s = m_tStartAngle.GetCachedValue();
	GFLOAT	e = m_tEndAngle.GetCachedValue();

	// convert to radians
	s *= GFLOAT_PI / GFLOAT_180;
	e *= GFLOAT_PI / GFLOAT_180;

	pDraw->Pie( x, y, r, s, e );

	return bResult;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
