/*---------------------------------------------------------------------+\
|
|	CMouseLocate.cpp  --  brief description of what CMouseLocate.cpp is for
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
	20-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Add support for MouseDown, MouseUp, and MouseMove
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	05-Aug-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CMouseLocate.h"
#include "UPlatform.h"
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

 * CMouseLocate - constructor

\+---------------------------------------------------------------------*/
CMouseLocate::CMouseLocate
		(
		void
		)
		: VDrawTmx()
{
}

/*---------------------------------------------------------------------+\

 * CMouseLocate - copy constructor

\+---------------------------------------------------------------------*/
//CMouseLocate::CMouseLocate
//		(
//		ConstCMouseLocateRef	r
//		)
//		: VDrawTmx( r )
//{
//	// TODO: add instructions to copy data from "r" to "this"
//}

/*---------------------------------------------------------------------+\

 * ~CMouseLocate - destructor

\+---------------------------------------------------------------------*/
CMouseLocate::~CMouseLocate
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
CMouseLocateRef
		CMouseLocate::operator=
		(
		ConstCMouseLocateRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}


/*---------------------------------------------------------------------+\

 * SetAction -

\+---------------------------------------------------------------------*/
void	CMouseLocate::SetAction
		(
		CMouseLocate::E_TYPE t
		)
{
	m_action = t;
}


/*---------------------------------------------------------------------+\

 * GetAction -

\+---------------------------------------------------------------------*/
CMouseLocate::E_TYPE
		CMouseLocate::GetAction
		(
		void
		)
{
	return m_action;
}

/*---------------------------------------------------------------------+\

 * SetPoint -

\+---------------------------------------------------------------------*/
void	CMouseLocate::SetPoint
		(
		GFLOAT	x,
		GFLOAT	y
		)
{
	m_x = x;
	m_y = y;
}


/*---------------------------------------------------------------------+\

 * Locate -

\+---------------------------------------------------------------------*/
bool	CMouseLocate::Locate
		(
		GFLOAT	fLeft,
		GFLOAT	fTop,
		GFLOAT	fRight,
		GFLOAT	fBottom
		)
{
	bool	bResult = false;
	do	// sequence
	{
		if ( m_tx < fLeft )
			break;
		if ( fRight < m_tx )
			break;
		if ( m_ty < fTop )
			break;
		if ( fBottom < m_ty )
			break;
		bResult = true;
	} sequence;	// end sequence
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

 * push -

\+---------------------------------------------------------------------*/
bool	CMouseLocate::push
		(
		GFLOAT	xPosition,
		GFLOAT	yPosition,
		GFLOAT	xShift,
		GFLOAT	yShift,
		GFLOAT	xAxis,
		GFLOAT	yAxis,
		GFLOAT	rotation,
		GFLOAT	scale
		)
{
	bool	bResult = false;
	bResult = VDrawTmx::push( -xPosition, -yPosition,
								xShift, yShift,
								xAxis, yAxis,
								rotation, scale );
	if ( bResult )
	{
		TransformPoint( m_tx, m_ty, m_x, m_y );
	}
	return bResult;
}


/*---------------------------------------------------------------------+\

 * pop -

\+---------------------------------------------------------------------*/
bool	CMouseLocate::pop
		(
		void
		)
{
	bool	bResult = VDrawTmx::pop();
	TransformPoint( m_tx, m_ty, m_x, m_y );
	return bResult;
}


}}


/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
