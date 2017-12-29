/*---------------------------------------------------------------------+\
|
|	CEqOpLessThan.cpp  --  brief description of what CEqOpLessThan.cpp is for
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
#include "CEqOpLessThan.h"
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

 * CEquationOperatorLessThan - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorLessThan::CEquationOperatorLessThan
		(
		void
		)
		: VEquationOperatorBinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorLessThan - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorLessThan::CEquationOperatorLessThan
		(
		CEquationOperatorLessThanRef	r
		)
		: VEquationOperatorBinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorLessThan - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorLessThan::~CEquationOperatorLessThan
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
CEquationOperatorLessThanRef
		CEquationOperatorLessThan::operator=
		(
		CEquationOperatorLessThanRef	r
		)
{
	VEquationOperatorBinary::operator = ( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorLessThan::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	//CVariantData::V_METATYPE	vTypeRight = vRight.GetMetaType();

	bool	bResult = false;

#if 1
	bResult = vLeft < vRight;
#else
	CVariantData::V_METATYPE	vTypeLeft = vLeft.GetMetaType();
	switch ( vTypeLeft )
	{
	case CVariantData::MT_CHARACTER:
		{
			CCharString	sLeft = vLeft;
			CCharString	sRight = vRight;
			if ( 0 > sLeft.Compare( sRight ) )
				bResult = true;
			else
				bResult = false;
		}
		break;
	case CVariantData::MT_COLOR:
		{
			CColor	cLeft = vLeft;
			CColor	cRight = vRight;
			if ( cLeft < cRight )
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
			if ( CVariantData::T_INTEGER == vLeft.GetType() )
			{
				long	nLeft = vLeft;
				long	nRight = vRight;

				if ( nLeft < nRight )
					bResult = true;
				else
					bResult = false;
			}
			else
			{
				GFLOAT	fLeft = vLeft;
				GFLOAT	fRight = vRight;

				if ( fLeft < fRight )
					bResult = true;
				else
					bResult = false;
			}
		}
		break;
	default:
		bResult = false;
		break;
	}
#endif // 0

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
		CEquationOperatorLessThan::Clone
		(
		void
		)
{
	return new CEquationOperatorLessThan( *this );
}


NAMESPACE_GADGET_END

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/

