/*---------------------------------------------------------------------+\
|
|	CEqOpUnitAbbrev.cpp  --  brief description of what CEqOpUnitAbbrev.cpp is for
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
	30-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CEqOpUnitAbbrev.h"

#include "CUnitsOfMeasure.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
using namespace Yogi::Core;
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

 * CEquationOperatorUnitAbbrev - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorUnitAbbrev::CEquationOperatorUnitAbbrev
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorUnitAbbrev - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorUnitAbbrev::CEquationOperatorUnitAbbrev
		(
		ConstCEquationOperatorUnitAbbrevRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorUnitAbbrev - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorUnitAbbrev::~CEquationOperatorUnitAbbrev
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
CEquationOperatorUnitAbbrevRef
		CEquationOperatorUnitAbbrev::operator=
		(
		ConstCEquationOperatorUnitAbbrevRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorUnitAbbrev::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	int		nUnits = vOperand.GetUnits();
	if ( 0 < nUnits )
	{
		CCharString	s = CUnitsOfMeasure::AbbrevFromUnits( nUnits );
		vResult = s;
	}
	else
	{
		vResult = "";
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
		CEquationOperatorUnitAbbrev::Clone
		(
		void
		)
{
	return new CEquationOperatorUnitAbbrev( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
