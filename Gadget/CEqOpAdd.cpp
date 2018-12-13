/*---------------------------------------------------------------------+\
|
|	CEqOpAdd.cpp  --  add two values together (or concatenate strings)
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
	19-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Maintain units after processing
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
	15-Aug-2009			J.Griswold
		Add support for character strings.  The "Add" operator appends
		two strings.
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
#include "CEqOpAdd.h"
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

 * CEquationOperatorAdd - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorAdd::CEquationOperatorAdd
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorAdd - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorAdd::CEquationOperatorAdd
		(
		CEquationOperatorAddRef	r
		)
		: VEquationOperatorBinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorAdd - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorAdd::~CEquationOperatorAdd
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
CEquationOperatorAddRef
		CEquationOperatorAdd::operator=
		(
		CEquationOperatorAddRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorAdd::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );
	CVariantData::V_METATYPE	mt = vLeft.GetMetaType();

	switch ( mt )
	{
	case CVariantData::MT_NUMERIC:
		if ( vLeft.GetType() == vRight.GetType()  &&  CVariantData::T_INTEGER == vLeft.GetType() )
		{
			long	nLeft = vLeft;
			long	nRight = vRight;

			vResult = nLeft + nRight;
		}
		else
		{
			GFLOAT	fLeft = vLeft;
			GFLOAT	fRight = vRight;

			vResult = fLeft + fRight;
		}
		break;
	case CVariantData::MT_CHARACTER:
		{
			CCharString	sLeft = vLeft;
			CCharString	sRight = vRight.GetValueCCharString();
			sLeft.Append( sRight );

			vResult = sLeft;
		}
		break;
	default:
		{
			long	nLeft = vLeft;
			long	nRight = vRight;

			vResult = nLeft + nRight;
		}
		break;
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
		CEquationOperatorAdd::Clone
		(
		void
		)
{
	return new CEquationOperatorAdd( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
