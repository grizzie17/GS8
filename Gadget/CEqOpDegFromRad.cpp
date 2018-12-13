/*---------------------------------------------------------------------+\
|
|	CEqOpDegFromRad.cpp  --  convert radians to degrees
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
	01-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpDegFromRad.h"

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

 * CEquationOperatorDegreesFromRadians - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorDegreesFromRadians::CEquationOperatorDegreesFromRadians
		(
		void
		)
		: VEquationOperatorUnary()
{
	m_unitDegree.SetUsingName( "degree" );
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorDegreesFromRadians - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorDegreesFromRadians::CEquationOperatorDegreesFromRadians
		(
		ConstCEquationOperatorDegreesFromRadiansRef	r
		)
		: VEquationOperatorUnary( r ),
		m_unitDegree( r.m_unitDegree )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorDegreesFromRadians - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorDegreesFromRadians::~CEquationOperatorDegreesFromRadians
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
CEquationOperatorDegreesFromRadiansRef
		CEquationOperatorDegreesFromRadians::operator=
		(
		ConstCEquationOperatorDegreesFromRadiansRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorDegreesFromRadians::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	if ( CVariantData::MT_NUMERIC == vOperand.GetMetaType() )
	{
		GFLOAT	r = vOperand;
		GFLOAT	d = r * GFLOAT_180 / GFLOAT_PI;

		vResult = d;

		vResult.SetUnits( m_unitDegree.GetUnits() );
	}
	else
	{
		vResult = GFLOAT_0;
	}

	return vResult;
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
		CEquationOperatorDegreesFromRadians::Clone
		(
		void
		)
{
	return new CEquationOperatorDegreesFromRadians( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
