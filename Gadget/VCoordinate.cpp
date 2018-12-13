/*---------------------------------------------------------------------+\
|
|	VCoordinate.cpp  --  Implementation of VCoordinate
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
	09-Dec-2009			C.Cason			(Reviewed by: R.Hosea)
		Combined GFLOAT declaration/assignment in Render() for
		Linux build
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	30-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for ProcessEvent and ProcessMouse
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
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
#include "VCoordinate.h"
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

 * VCoordinate - constructor

\+---------------------------------------------------------------------*/
VCoordinate::VCoordinate
		(
		void
		)
		: inherited()
		, m_tX()
		, m_tY()
{
}

/*---------------------------------------------------------------------+\

 * VCoordinate - copy constructor

\+---------------------------------------------------------------------*/
VCoordinate::VCoordinate
		(
		ConstVCoordinateRef	r
		)
		: inherited( r )
		, m_tX( r.m_tX )
		, m_tY( r.m_tY )
{
}

/*---------------------------------------------------------------------+\

 * ~VCoordinate - destructor

\+---------------------------------------------------------------------*/
VCoordinate::~VCoordinate
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
VCoordinateRef
		VCoordinate::operator=
		(
		ConstVCoordinateRef	r
		)
{
	inherited::operator=( r );
	m_tX = r.m_tX;
	m_tY = r.m_tY;
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetValues -

\+---------------------------------------------------------------------*/
void	VCoordinate::SetValues
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	CVariantData	vX;
	CVariantData	vY;

	vX = x;
	vY = y;
	m_tX.SetValue( vX );
	m_tY.SetValue( vY );
}

void	VCoordinate::SetXValue
		(
		GFLOAT	f
		)
{
	CVariantData	v;

	v = f;
	m_tX.SetValue( v );
}

void	VCoordinate::SetYValue
		(
		GFLOAT	f
		)
{
	CVariantData	v;

	v = f;
	m_tY.SetValue( v );
}




/*---------------------------------------------------------------------+\

 * SetEquations -

\+---------------------------------------------------------------------*/
void	VCoordinate::SetEquations
		(
		VEquationPtr pX,
		VEquationPtr pY
		)
{
	m_tX.SetEquation( pX );
	m_tY.SetEquation( pY );
}

void	VCoordinate::SetXEquation
		(
		VEquationPtr p
		)
{
	m_tX.SetEquation( p );
}

void	VCoordinate::SetYEquation
		(
		VEquationPtr p
		)
{
	m_tY.SetEquation( p );
}


CResultValuePtr
		VCoordinate::X
		(
		void
		)
{
	return &m_tX;
}

CResultValuePtr
		VCoordinate::Y
		(
		void
		)
{
	return &m_tY;
}


/*---------------------------------------------------------------------+\

 * GetX -

\+---------------------------------------------------------------------*/
GFLOAT	VCoordinate::GetX
		(
		void
		)
{
	CVariantData	d = m_tX.GetCachedValue();
	return d;
}

/*---------------------------------------------------------------------+\

 * GetY -

\+---------------------------------------------------------------------*/
GFLOAT	VCoordinate::GetY
		(
		void
		)
{
	CVariantData	d = m_tY.GetCachedValue();
	return d;
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
int		VCoordinate::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int		nResult = VRDR_CALCULATE_NONE;
	if ( m_tX.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	if ( m_tY.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}


bool	VCoordinate::Layout
		(
		VDictionaryPtr //pDict
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	VCoordinate::PreRender
		(
		VDictionaryPtr ,
		VDrawQueuePtr
		)
{
	// don't do any processing this will most likely be overridden
	return true;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	VCoordinate::Render
		(
		VDictionaryPtr,
		VDrawPtr pDraw
		)
{
	GFLOAT x = m_tX.GetCachedValue();
	GFLOAT y = m_tY.GetCachedValue();

	return pDraw->Polypoint( x, y );
}

/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	VCoordinate::GetSize
		(
		VDictionaryPtr ,
		long& rnWidth,
		long& rnHeight
		)
{
	rnWidth = 0;
	rnHeight = 0;
	return true;
}

/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	VCoordinate::IsDisplayed
		(
		VDictionaryPtr
		)
{
	return true;
}




/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	VCoordinate::ProcessEvent
		(
		VDictionaryPtr			,
		VDictionary::Selector
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	VCoordinate::ProcessMouse
		(
		VDictionaryPtr		,
		CMouseLocatePtr
		)
{
	return false;
}



}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
