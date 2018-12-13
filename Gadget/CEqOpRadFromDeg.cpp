/*---------------------------------------------------------------------+\
|
|	CEqOpRadFromDeg.cpp  --  convert degrees to radians
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
	07-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		fix references to commonly used floating point constants
		so we use predefined values.  This will help in the fixed
		point performance.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	18-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix reference to PI
		Also fix units
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
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
#include "CEqOpRadFromDeg.h"

#include "UMath.h"
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

 * CEquationOperatorRadiansFromDegrees - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRadiansFromDegrees::CEquationOperatorRadiansFromDegrees
		(
		void
		)
		: VEquationOperatorUnary()
{
	m_unitRadian.SetUsingName( "radian" );
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorRadiansFromDegrees - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRadiansFromDegrees::CEquationOperatorRadiansFromDegrees
		(
		ConstCEquationOperatorRadiansFromDegreesRef	r
		)
		: VEquationOperatorUnary( r ),
		m_unitRadian( r.m_unitRadian )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorRadiansFromDegrees - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorRadiansFromDegrees::~CEquationOperatorRadiansFromDegrees
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
CEquationOperatorRadiansFromDegreesRef
		CEquationOperatorRadiansFromDegrees::operator=
		(
		ConstCEquationOperatorRadiansFromDegreesRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorRadiansFromDegrees::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	if ( CVariantData::MT_NUMERIC == vOperand.GetMetaType() )
	{
		GFLOAT	d = vOperand;
		GFLOAT	r = d * GFLOAT_PI / GFLOAT_180;

		CVariantData	vResult = r;

		vResult.SetUnits( m_unitRadian.GetUnits() );
		return vResult;
	}
	else
	{
		return CVariantData( GFLOAT_0 );
	}
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

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationOperatorRadiansFromDegrees::Clone
		(
		void
		)
{
	return new CEquationOperatorRadiansFromDegrees( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
