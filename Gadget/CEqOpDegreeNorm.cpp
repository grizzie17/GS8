/*---------------------------------------------------------------------+\
|
|	CEqOpDegreeNorm.cpp  --  brief description of what CEqOpDegreeNorm.cpp is for
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
#include "CEqOpDegreeNorm.h"
#include <math.h>
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

 * CEquationOperatorDegreeNorm - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorDegreeNorm::CEquationOperatorDegreeNorm
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorDegreeNorm - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorDegreeNorm::CEquationOperatorDegreeNorm
		(
		ConstCEquationOperatorDegreeNormRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorDegreeNorm - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorDegreeNorm::~CEquationOperatorDegreeNorm
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
CEquationOperatorDegreeNormRef
		CEquationOperatorDegreeNorm::operator=
		(
		ConstCEquationOperatorDegreeNormRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorDegreeNorm::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	CVariantData::V_TYPE	t = vOperand.GetType();

	if ( CVariantData::T_INTEGER == t )
	{
		long	nOperand = vOperand;

		nOperand = nOperand % 360;
		if ( nOperand < 0 )
		{
			while ( nOperand < 0 )
				nOperand += 360;
		}
		vResult = nOperand;
	}
	else if ( CVariantData::T_FLOAT == t )
	{
		GFLOAT	fOperand = vOperand;

		fOperand = ::fmodf( fOperand, GFLOAT_360 );
		if ( fOperand < GFLOAT_0 )
		{
			while ( fOperand < GFLOAT_0 )
				fOperand += GFLOAT_360;
		}
		vResult = fOperand;
	}
	else
	{
		vResult = vOperand;
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
		CEquationOperatorDegreeNorm::Clone
		(
		void
		)
{
	return new CEquationOperatorDegreeNorm( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

