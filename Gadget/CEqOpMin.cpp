/*---------------------------------------------------------------------+\
|
|	CEqOpMin.cpp  --  brief description of what CEqOpMin.cpp is for
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
#include "CEqOpMin.h"
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

 * CEquationOperatorMin - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorMin::CEquationOperatorMin
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorMin - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorMin::CEquationOperatorMin
		(
		CEquationOperatorMinRef	r
		)
		: VEquationOperatorBinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorMin - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorMin::~CEquationOperatorMin
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
CEquationOperatorMinRef
		CEquationOperatorMin::operator=
		(
		CEquationOperatorMinRef	r
		)
{
	VEquationOperatorBinary::operator = ( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorMin::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	//CVariantData	vResult;
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	//CVariantData::V_METATYPE	vTypeLeft = vLeft.GetMetaType();
	//CVariantData::V_METATYPE	vTypeRight = vRight.GetMetaType();

	if ( vLeft < vRight )
		return vLeft;
	else
		return vRight;

#if 0
	switch ( vTypeLeft )
	{
	case CVariantData::MT_CHARACTER:
		{
			CCharString	sLeft = vLeft;
			CCharString	sRight = vRight;
			if ( sLeft < sRight )
				vResult = sLeft;
			else
				vResult = sRight;
		}
		break;
	case CVariantData::MT_COLOR:
		{
			CColor	cLeft = vLeft;
			CColor	cRight = vRight;
			if ( cLeft < cRight )
				vResult = cLeft;
			else
				vResult = cRight;
		}
		break;
	case CVariantData::MT_LOGICAL:
		{
			bool	bLeft = vLeft;
			bool	bRight = vRight;
			if ( !bLeft  &&  bRight )
				vResult = bLeft;
			else
				vResult = bRight;
		}
	case CVariantData::MT_NUMERIC:
		{
			GFLOAT	fLeft = vLeft;
			GFLOAT	fRight = vRight;

			if ( fLeft < fRight )
				vResult = fLeft;
			else
				vResult = fRight;
		}
		break;
	default:
		vResult = vLeft;
		break;
	}
	vResult.SetUnits( vLeft.GetUnits() );

	return vResult;
#endif
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
		CEquationOperatorMin::Clone
		(
		void
		)
{
	return new CEquationOperatorMin( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
