/*---------------------------------------------------------------------+\
|
|	CEqOpDivide.cpp  --  brief description of what CEqOpDivide.cpp is for
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
	11-Dec-2018			J.Griswold
		Migrate to correctly using namespaces.
	09-Dec-2009			C.Cason			(Reviewed by:R.Hosea)
		Changed GFLOAT variable declaration and assignment call
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
#include "CEqOpDivide.h"
#include <math.h>
#include <float.h>
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

 * CEquationOperatorDivide - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorDivide::CEquationOperatorDivide
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorDivide - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorDivide::CEquationOperatorDivide
		(
		CEquationOperatorDivideRef	r
		)
		: VEquationOperatorBinary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorDivide - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorDivide::~CEquationOperatorDivide
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
CEquationOperatorDivideRef
		CEquationOperatorDivide::operator=
		(
		CEquationOperatorDivideRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorDivide::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	GFLOAT fLeft = m_pLeft->GetValue( pDict );
	GFLOAT fRight = m_pRight->GetValue( pDict );

	if ( GFLOAT_EPSILON < ::fabsf( fRight ) )
	{
		return CVariantData( fLeft / fRight );
	}
	else
	{
		return CVariantData( GFLOAT_0 );
	}
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
		CEquationOperatorDivide::Clone
		(
		void
		)
{
	return new CEquationOperatorDivide( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
