/*---------------------------------------------------------------------+\
|
|	CEqOpRange.cpp  --  brief description of what CEqOpRange.cpp is for
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
#include "CEqOpRange.h"
/*---------------------------------------------------------------------+\
|																		|
|	Local defines / constants											|
|																		|
\+---------------------------------------------------------------------*/
namespace Yogi { namespace Gadget {
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

 * CEquationOperatorRange - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRange::CEquationOperatorRange
		(
		void
		)
		: VEquationOperatorTrinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorRange - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRange::CEquationOperatorRange
		(
		CEquationOperatorRangeRef	r
		)
		: VEquationOperatorTrinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorRange - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorRange::~CEquationOperatorRange
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
CEquationOperatorRangeRef
		CEquationOperatorRange::operator=
		(
		CEquationOperatorRangeRef	r
		)
{
	VEquationOperatorTrinary::operator =( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorRange::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vControl( m_pControl->GetValue( pDict ) );
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );
	bool			bDecision = false;

	switch ( vControl.GetType() )
	{
	case CVariantData::T_FLOAT:
		{
			GFLOAT	f = vControl;
			GFLOAT	f1 = vLeft;
			GFLOAT	f2 = vRight;

			if ( f1 < f2 )
				bDecision = f1 <= f  &&  f <= f2;
			else
				bDecision = f2 <= f  &&  f <= f1;
		}
		break;
	case CVariantData::T_INTEGER:
		{
			long	f = vControl;
			long	f1 = vLeft;
			long	f2 = vRight;

			if ( f1 < f2 )
				bDecision = f1 <= f  &&  f <= f2;
			else
				bDecision = f2 <= f  &&  f <= f1;
		}
		break;
	case CVariantData::T_STRING:
		{
			CCharString	f = vControl;
			CCharString	f1 = vLeft;
			CCharString	f2 = vRight;

			int			n = f1.Compare( f2 );

			// TODO: the following logic needs to validated
			if ( 0 == n )
			{
				if ( 0 == f.Compare( f1 ) )
					bDecision = true;
			}
			else if ( n < 0 )
			{
				if ( f1.Compare( f ) <= 0  &&  0 <= f.Compare( f2 ) )
					bDecision = true;
			}
			else
			{
				if ( f2.Compare( f ) <= 0  &&  0 <= f.Compare( f1 ) )
					bDecision = true;
			}
		}
		break;
	default:
		bDecision = false;
		break;
	}

	return CVariantData( bDecision );
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
		CEquationOperatorRange::Clone
		(
		void
		)
{
	return new CEquationOperatorRange( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
