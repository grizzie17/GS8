/*---------------------------------------------------------------------+\
|
|	CRectangle.cpp  --  Implementation of Rectangle object
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
	03-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Changes to support V2 Schema
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	05-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Implement Rectangle object
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
#include <float.h>

#include "CRectangle.h"

namespace Yogi { namespace Gadget {
//USING_NAMESPACE_COMMON
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

 * CRectangle - constructor

\+---------------------------------------------------------------------*/
CRectangle::CRectangle
		(
		void
		)
		: VGraphic(),
		m_tOrigin(),
		m_tSize(),
		m_eCornerStyle( VDraw::C_SQUARE ),
		m_tCorner()
{
}

/*---------------------------------------------------------------------+\

 * CRectangle - copy constructor

\+---------------------------------------------------------------------*/
CRectangle::CRectangle
		(
		CRectangleRef	r
		)
		: VGraphic( r ),
		m_tOrigin( r.m_tOrigin ),
		m_tSize( r.m_tSize ),
		m_eCornerStyle( r.m_eCornerStyle ),
		m_tCorner( r.m_tCorner )
{
	// TODO: add instructions to copy data from "r" to "this"
}

/*---------------------------------------------------------------------+\

 * ~CRectangle - destructor

\+---------------------------------------------------------------------*/
CRectangle::~CRectangle
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
CRectangleRef
		CRectangle::operator=
		(
		CRectangleRef	r
		)
{
	m_tOrigin = r.m_tOrigin;
	m_tSize = r.m_tSize;
	m_eCornerStyle = r.m_eCornerStyle;
	m_tCorner = r.m_tCorner;
	return *this;
}

/*---------------------------------------------------------------------+\

 * Origin -

\+---------------------------------------------------------------------*/
CPointValuePtr
		CRectangle::Origin
		(
		void
		)
{
	return &m_tOrigin;
}


/*---------------------------------------------------------------------+\

 * Size -

\+---------------------------------------------------------------------*/
CSizePtr
		CRectangle::Size
		(
		void
		)
{
	return &m_tSize;
}

/*---------------------------------------------------------------------+\

 * Width -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CRectangle::Width
		(
		void
		)
{
	return m_tSize.X();
}

/*---------------------------------------------------------------------+\

 * Height -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CRectangle::Height
		(
		void
		)
{
	return m_tSize.Y();
}

/*---------------------------------------------------------------------+\

 * SetCornerStyle -

\+---------------------------------------------------------------------*/
void	CRectangle::SetCornerStyle
		(
		VDraw::CORNERSTYLE	c
		)
{
	m_eCornerStyle = c;
}

/*---------------------------------------------------------------------+\

 * Corner -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CRectangle::Corner
		(
		void
		)
{
	return &m_tCorner;
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
int		CRectangle::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int	nResult = VGraphic::Calculate( pDict );
	nResult |= m_tOrigin.Calculate( pDict );
	nResult |= m_tSize.Calculate( pDict );
	if ( m_tCorner.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CRectangle::Render
		(
		VDictionaryPtr	pDict,
		VDrawPtr		pDraw
		)
{
	bool	bResult = VGraphic::Render( pDict, pDraw );

	GFLOAT	x = m_tOrigin.GetX();
	GFLOAT	y = m_tOrigin.GetY();
	GFLOAT	w = m_tSize.GetX();
	GFLOAT	h = m_tSize.GetY();
	GFLOAT	c = m_tCorner.GetCachedValue();

	bResult = pDraw->Rectangle( x, y, w, h, m_eCornerStyle, c );

	return bResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
