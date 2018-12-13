/*---------------------------------------------------------------------+\
|
|	CEqOpNegate.cpp  --  brief description of what CEqOpNegate.cpp is for
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
#include "CEqOpNegate.h"
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

 * CEquationOperatorNegate - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorNegate::CEquationOperatorNegate
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorNegate - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorNegate::CEquationOperatorNegate
		(
		ConstCEquationOperatorNegateRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorNegate - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorNegate::~CEquationOperatorNegate
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
CEquationOperatorNegateRef
		CEquationOperatorNegate::operator=
		(
		ConstCEquationOperatorNegateRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorNegate::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	if ( CVariantData::T_INTEGER == vOperand.GetType() )
	{
		long	nOperand = vOperand;

		vResult = (- nOperand);
	}
	else
	{
		GFLOAT	fOperand = vOperand;

		vResult = (- fOperand);
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
		CEquationOperatorNegate::Clone
		(
		void
		)
{
	return new CEquationOperatorNegate( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
