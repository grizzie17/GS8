/*---------------------------------------------------------------------+\
|
|	CEqOpGreaterThan.cpp  --  brief description of what CEqOpGreaterThan.cpp is for
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
	08-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Change the GetValue function to use the local "Compare"
		on the CCharString instead of handing off to ::strcmp
	06-Dec-2009			J.Griswold		(Reviewed by: M.Rose)
		Add support for fixed-point replacement for float
	15-Sep-2009			J.Griswold		(Reviewed by: M.Rose)
		Fix compiler warnings
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
#include "CEqOpGreaterThan.h"
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

 * CEquationOperatorGreaterThan - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorGreaterThan::CEquationOperatorGreaterThan
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorGreaterThan - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorGreaterThan::CEquationOperatorGreaterThan
		(
		CEquationOperatorGreaterThanRef	r
		)
		: VEquationOperatorBinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorGreaterThan - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorGreaterThan::~CEquationOperatorGreaterThan
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
CEquationOperatorGreaterThanRef
		CEquationOperatorGreaterThan::operator=
		(
		CEquationOperatorGreaterThanRef	r
		)
{
	VEquationOperatorBinary::operator = ( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorGreaterThan::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	CVariantData::V_METATYPE	vTypeLeft = vLeft.GetMetaType();
	//CVariantData::V_METATYPE	vTypeRight = vRight.GetMetaType();

	bool	bResult = false;

	switch ( vTypeLeft )
	{
	case CVariantData::MT_CHARACTER:
		{
			CCharString	sLeft = vLeft;
			CCharString	sRight = vRight;
			if ( 0 < sLeft.Compare( sRight ) )
				bResult = true;
			else
				bResult = false;
		}
		break;
	case CVariantData::MT_COLOR:
		{
			CColor	cLeft = vLeft;
			CColor	cRight = vRight;
			if ( cLeft > cRight )
				bResult = true;
			else
				bResult = false;
		}
		break;
	case CVariantData::MT_LOGICAL:
		{
			bool	bLeft = vLeft;
			bool	bRight = vRight;
			if ( !bLeft  &&  bRight )
				bResult = true;
			else
				bResult = false;
		}
	case CVariantData::MT_NUMERIC:
		{
			GFLOAT	fLeft = vLeft;
			GFLOAT	fRight = vRight;

			if ( fLeft > fRight )
				bResult = true;
			else
				bResult = false;
		}
		break;
	default:
		bResult = false;
		break;
	}

	vResult = bResult;

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
		CEquationOperatorGreaterThan::Clone
		(
		void
		)
{
	return new CEquationOperatorGreaterThan( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
