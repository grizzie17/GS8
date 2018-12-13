/*---------------------------------------------------------------------+\
|
|	CEqOpAbs.cpp  --  brief description of what CEqOpAbs.cpp is for
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
	19-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Maintain units after processing
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
#include "CEqOpAbs.h"
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

 * CEquationOperatorAbs - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorAbs::CEquationOperatorAbs
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorAbs - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorAbs::CEquationOperatorAbs
		(
		ConstCEquationOperatorAbsRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorAbs - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorAbs::~CEquationOperatorAbs
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
CEquationOperatorAbsRef
		CEquationOperatorAbs::operator=
		(
		ConstCEquationOperatorAbsRef	r
		)
{
	VEquationOperatorUnary::operator = ( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorAbs::GetValue
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

		vResult = nOperand < 0 ? -nOperand : nOperand;
	}
	else if ( CVariantData::T_FLOAT == t )
	{
		GFLOAT	fOperand = vOperand;

		vResult = fOperand < GFLOAT_0 ? -fOperand : fOperand;
	}
	else
	{
		vResult = vOperand;
	}
	vResult.SetUnits( vOperand.GetUnits() );

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
		CEquationOperatorAbs::Clone
		(
		void
		)
{
	return new CEquationOperatorAbs( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
