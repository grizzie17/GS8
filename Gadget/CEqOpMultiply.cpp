/*---------------------------------------------------------------------+\
|
|	CEqOpMultiply.cpp  --  brief description of what CEqOpMultiply.cpp is for
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
#include "CEqOpMultiply.h"
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

 * CEquationOperatorMultiply - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorMultiply::CEquationOperatorMultiply
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorMultiply - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorMultiply::CEquationOperatorMultiply
		(
		CEquationOperatorMultiplyRef	r
		)
		: VEquationOperatorBinary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorMultiply - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorMultiply::~CEquationOperatorMultiply
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
CEquationOperatorMultiplyRef
		CEquationOperatorMultiply::operator=
		(
		CEquationOperatorMultiplyRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorMultiply::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	CVariantData::V_TYPE	tLeft = vLeft.GetType();
	CVariantData::V_TYPE	tRight = vRight.GetType();

	if ( CVariantData::T_FLOAT == tLeft
		||	CVariantData::T_FLOAT == tRight )
	{
		GFLOAT	fLeft = vLeft;
		GFLOAT	fRight = vRight;
		GFLOAT	fResult;

		fResult = fLeft * fRight;
		vResult = fResult;
	}
	else if ( CVariantData::T_INTEGER == tLeft
		&&	CVariantData::T_INTEGER == tRight )
	{
		long	nLeft = vLeft;
		long	nRight = vRight;

		vResult = nLeft * nRight;

	}
	else
	{
		vResult = vLeft;
	}
	vResult.SetUnits( vLeft.GetUnits() );

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
		CEquationOperatorMultiply::Clone
		(
		void
		)
{
	return new CEquationOperatorMultiply( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

