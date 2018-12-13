/*---------------------------------------------------------------------+\
|
|	CEqOpNotEqual.cpp  --  brief description of what CEqOpNotEqual.cpp is for
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
	03-Oct-2009			J.Griswold		(Reviewed by: M.Rose)
		Protect from null pointer comparison by using CCharString
		not-equal operator
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
#include "CEqOpNotEqual.h"
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

 * CEquationOperatorNotEqual - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorNotEqual::CEquationOperatorNotEqual
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorNotEqual - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorNotEqual::CEquationOperatorNotEqual
		(
		CEquationOperatorNotEqualRef	r
		)
		: VEquationOperatorBinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorNotEqual - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorNotEqual::~CEquationOperatorNotEqual
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
CEquationOperatorNotEqualRef
		CEquationOperatorNotEqual::operator=
		(
		CEquationOperatorNotEqualRef	r
		)
{
	VEquationOperatorBinary::operator = ( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorNotEqual::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	//CVariantData::V_METATYPE	vTypeRight = vRight.GetMetaType();

	bool	bResult = false;
#if 1
	bResult = ! vLeft.EqualsVariant(vRight);
#else
	CVariantData::V_METATYPE	vTypeLeft = vLeft.GetMetaType();
	switch ( vTypeLeft )
	{
	case CVariantData::MT_CHARACTER:
		{
			CCharString	sLeft = vLeft;
			CCharString	sRight = vRight;
			if ( sLeft != sRight )
				bResult = true;
			else
				bResult = false;
		}
		break;
	case CVariantData::MT_COLOR:
		{
			CColor	cLeft = vLeft;
			CColor	cRight = vRight;
			if ( cLeft != cRight )
				bResult = true;
			else
				bResult = false;
		}
		break;
	case CVariantData::MT_LOGICAL:
		{
			bool	bLeft = vLeft;
			bool	bRight = vRight;
			if ( bLeft  !=  bRight )
				bResult = true;
			else
				bResult = false;
		}
	case CVariantData::MT_NUMERIC:
		{
			GFLOAT	fLeft = vLeft;
			GFLOAT	fRight = vRight;

			if ( fLeft != fRight )
				bResult = true;
			else
				bResult = false;
		}
		break;
	default:
		bResult = false;
		break;
	}
#endif // 0

	return CVariantData( bResult );
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
		CEquationOperatorNotEqual::Clone
		(
		void
		)
{
	return new CEquationOperatorNotEqual( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
