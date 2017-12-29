/*---------------------------------------------------------------------+\
|
|	CEqOpNear.cpp  --  nearest integer
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
	17-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include <math.h>
#include "CEqOpNear.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
NAMESPACE_GADGET_BEGIN
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

 * CEquationOperatorNear - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorNear::CEquationOperatorNear
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorNear - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorNear::CEquationOperatorNear
		(
		ConstCEquationOperatorNearRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorNear - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorNear::~CEquationOperatorNear
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
CEquationOperatorNearRef
		CEquationOperatorNear::operator=
		(
		ConstCEquationOperatorNearRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorNear::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	CVariantData::V_TYPE	eType = vOperand.GetType();

	switch ( eType )
	{
	case CVariantData::T_FLOAT:
		{
			GFLOAT	f = vOperand;
			if ( f < GFLOAT_0 )
				vResult = static_cast<long>( f - GFLOAT_1_2 );
			else
				vResult = static_cast<long>( f + GFLOAT_1_2 );
			vResult.SetUnits( vOperand.GetUnits() );
		}
		break;
	case CVariantData::T_INTEGER:
	default:
		{
			long	n;
			n = vOperand;
			vResult = n;
			vResult.SetUnits( vOperand.GetUnits() );
		}
		break;
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
		CEquationOperatorNear::Clone
		(
		void
		)
{
	return new CEquationOperatorNear( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

