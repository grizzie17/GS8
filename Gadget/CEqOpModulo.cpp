/*---------------------------------------------------------------------+\
|
|	CEqOpModulo.cpp  --  brief description of what CEqOpModulo.cpp is for
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
	17-Nov-2009			J.Griswold		(Reviewed by: M.Rose)
		Assure that the units is set
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
#include "CEqOpModulo.h"
#include <math.h>
#include <float.h>
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

 * CEquationOperatorModulo - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorModulo::CEquationOperatorModulo
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorModulo - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorModulo::CEquationOperatorModulo
		(
		CEquationOperatorModuloRef	r
		)
		: VEquationOperatorBinary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorModulo - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorModulo::~CEquationOperatorModulo
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
CEquationOperatorModuloRef
		CEquationOperatorModulo::operator=
		(
		CEquationOperatorModuloRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorModulo::GetValue
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
		if ( GFLOAT_EPSILON < fRight )
			fResult = ::fmodf( fLeft, fRight );
		else
			fResult = GFLOAT_0;
		vResult = fResult;
	}
	else if ( CVariantData::T_INTEGER == tLeft
		&&	CVariantData::T_INTEGER == tRight )
	{
		long	nLeft = vLeft;
		long	nRight = vRight;

		if ( 0 < nRight )
			vResult = nLeft % nRight;
		else
			vResult = 0L;
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
		CEquationOperatorModulo::Clone
		(
		void
		)
{
	return new CEquationOperatorModulo( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

