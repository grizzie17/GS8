/*---------------------------------------------------------------------+\
|
|	CShift.cpp  --  brief description of what CShift.cpp is for
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
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	03-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the signature of Calculate to support the concept of
		foreground/background data
	08-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for Maximum and Minimum limits on the Shift
		object.
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	17-Jul-2009
		Use new VCoordinate class for most of implementation
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
#include <math.h>


#include "CShift.h"
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

 * CShift - constructor

\+---------------------------------------------------------------------*/
CShift::CShift
		(
		void
		)
		: VRenderable(),
		m_tExpression(),
		m_tMinimum(),
		m_tMaximum(),
		m_fScaleX( GFLOAT_0 ),
		m_fScaleY( GFLOAT_1 )
{
	CVariantData	zero( 0L );
	m_tExpression.SetValue( zero );
	m_tMinimum.SetValue( zero );
	m_tMaximum.SetValue( zero );
}

/*---------------------------------------------------------------------+\

 * CShift - copy constructor

\+---------------------------------------------------------------------*/
CShift::CShift
		(
		ConstCShiftRef	r
		)
		: VRenderable( r ),
		m_tExpression(),
		m_fScaleX( r.m_fScaleX ),
		m_fScaleY( r.m_fScaleY )
{
}

/*---------------------------------------------------------------------+\

 * ~CShift - destructor

\+---------------------------------------------------------------------*/
CShift::~CShift
		(
		void
		)
{
}

/*=====================================================================+\
||	 public member functions											|
\+=====================================================================*/


/*---------------------------------------------------------------------+\

 * Expression -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CShift::Expression
		(
		void
		)
{
	return &m_tExpression;
}


/*---------------------------------------------------------------------+\

 * Maximum -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CShift::Maximum
		(
		void
		)
{
	return &m_tMaximum;
}

/*---------------------------------------------------------------------+\

 * Minimum -

\+---------------------------------------------------------------------*/
CResultValuePtr
		CShift::Minimum
		(
		void
		)
{
	return &m_tMinimum;
}


/*---------------------------------------------------------------------+\

 * ScaleX -

\+---------------------------------------------------------------------*/
GFLOAT*	CShift::ScaleX
		(
		void
		)
{
	return &m_fScaleX;
}


/*---------------------------------------------------------------------+\

 * ScaleY -

\+---------------------------------------------------------------------*/
GFLOAT*	CShift::ScaleY
		(
		void
		)
{
	return &m_fScaleY;
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
int		CShift::Calculate
		(
		VDictionaryPtr pDict
		)
{
	int	nResult = VRDR_CALCULATE_NONE;
	if ( m_tExpression.Calculate( pDict ) )
		nResult |= VRDR_CALCULATE_UNDETERMINED;
	//if ( m_tMinimum.Calculate( pDict ) )
	//	nResult |= VRDR_CALCULATE_UNDETERMINED;
	//if ( m_tMaximum.Calculate( pDict ) )
	//	nResult |= VRDR_CALCULATE_UNDETERMINED;
	return nResult;
}

bool	CShift::Layout
		(
		VDictionaryPtr //pDict
		)
{
	return false;
}

/*---------------------------------------------------------------------+\

 * PreRender -

\+---------------------------------------------------------------------*/
bool	CShift::PreRender
		(
		VDictionaryPtr,
		VDrawQueuePtr	pQueue
		)
{
	GFLOAT	z = m_tExpression.GetCachedValue();
	GFLOAT	x = z * m_fScaleX;
	GFLOAT	y = z * m_fScaleY;
	//GFLOAT	mn = m_tMinimum.GetCachedValue();
	//GFLOAT	mx = m_tMaximum.GetCachedValue();
	//if ( mn < mx )
	//{
	//	if ( GFLOAT_EPSILON < ::fabsf( x ) )
	//	{
	//		if ( mx < x )
	//			x = mx;
	//		if ( x < mn )
	//			x = mn;
	//	}
	//	if ( GFLOAT_EPSILON < ::fabsf( y ) )
	//	{
	//		if ( mx < y )
	//			y = mx;
	//		if ( y < mn )
	//			y = mn;
	//	}
	//}

	return pQueue->SetShift( x, y );
}


/*---------------------------------------------------------------------+\

 * Render -

\+---------------------------------------------------------------------*/
bool	CShift::Render
		(
		VDictionaryPtr,
		VDrawPtr
		)
{
	// CShift does not actually render
	return true;
}



/*---------------------------------------------------------------------+\

 * GetSize -

\+---------------------------------------------------------------------*/
bool	CShift::GetSize
		(
		VDictionaryPtr	,//pDict,
		long&			rnWidth,
		long&			rnHeight
		)
{
	rnWidth = 0;
	rnHeight = 0;
	return true;
}

/*---------------------------------------------------------------------+\

 * IsDisplayed -

\+---------------------------------------------------------------------*/
bool	CShift::IsDisplayed
		(
		VDictionaryPtr	//pDict
		)
{
	return true;
}


/*---------------------------------------------------------------------+\

 * ProcessEvent -

\+---------------------------------------------------------------------*/
bool	CShift::ProcessEvent
		(
		VDictionaryPtr			,//pDict
		VDictionary::Selector	//nSel
		)
{
	return false;
}


/*---------------------------------------------------------------------+\

 * ProcessMouse -

\+---------------------------------------------------------------------*/
bool	CShift::ProcessMouse
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
