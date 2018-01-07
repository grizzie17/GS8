/*---------------------------------------------------------------------+\
|
|	CEqOpBoth.cpp  --  brief description of what CEqOpBoth.cpp is for
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
#include "CEqOpBoth.h"
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

 * CEquationOperatorBoth - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorBoth::CEquationOperatorBoth
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorBoth - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorBoth::CEquationOperatorBoth
		(
		CEquationOperatorBothRef	r
		)
		: VEquationOperatorBinary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorBoth - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorBoth::~CEquationOperatorBoth
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
CEquationOperatorBothRef
		CEquationOperatorBoth::operator=
		(
		CEquationOperatorBothRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorBoth::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	return vRight;
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
		CEquationOperatorBoth::Clone
		(
		void
		)
{
	return new CEquationOperatorBoth( *this );
}



NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
