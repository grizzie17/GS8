/*---------------------------------------------------------------------+\
|
|	CEqOpAnd.cpp  --  perform logical AND operation
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
	14-Jan-2010			J.Griswold		(Reviewed by: M.Rose)
		Optimize the GetValue method so it will not always evaluate
		both operands if the first is false.
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	24-Jul-2009			J.Griswold
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpAnd.h"
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

 * CEquationOperatorAnd - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorAnd::CEquationOperatorAnd
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorAnd - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorAnd::CEquationOperatorAnd
		(
		CEquationOperatorAndRef	r
		)
		: VEquationOperatorBinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorAnd - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorAnd::~CEquationOperatorAnd
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
CEquationOperatorAndRef
		CEquationOperatorAnd::operator=
		(
		CEquationOperatorAndRef	r
		)
{
	VEquationOperatorBinary::operator = ( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorAnd::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	bool			bResult = false;
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	bool			bLeft = vLeft;
	if ( bLeft )
	{
		CVariantData	vRight( m_pRight->GetValue( pDict ) );
		bool			bRight = vRight;

		if ( bRight )
			bResult = true;
	}

	CVariantData	vResult( bResult );

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
		CEquationOperatorAnd::Clone
		(
		void
		)
{
	return new CEquationOperatorAnd( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
