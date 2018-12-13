/*---------------------------------------------------------------------+\
|
|	CEqOpRGB.cpp  --  brief description of what CEqOpRGB.cpp is for
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
    14-Dec-2009         R.Hosea        (Reviewed by: J.Griswold)
        Fixed gcc compile problem for omniscape
	03-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"

#include "CEqOpRGB.h"

#include "CColor.h"
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

 * CEquationOperatorRGB - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRGB::CEquationOperatorRGB
		(
		void
		)
		: VEquationOperatorTrinary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorRGB - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRGB::CEquationOperatorRGB
		(
		CEquationOperatorRGBRef	r
		)
		: VEquationOperatorTrinary( r )
{
	// everything is handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorRGB - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorRGB::~CEquationOperatorRGB
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
CEquationOperatorRGBRef
		CEquationOperatorRGB::operator=
		(
		CEquationOperatorRGBRef	r
		)
{
	VEquationOperatorTrinary::operator =( r );
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorRGB::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CColor			color;
	CVariantData	vControl( m_pControl->GetValue( pDict ) );
	CVariantData	vLeft( m_pLeft->GetValue( pDict ) );
	CVariantData	vRight( m_pRight->GetValue( pDict ) );

	switch ( vControl.GetType() )
	{
	case CVariantData::T_FLOAT:
		{
			GFLOAT	f = vControl;
			GFLOAT	f1 = vLeft;
			GFLOAT	f2 = vRight;

			unsigned long	r = (unsigned long)( 255.0f * f1 );
			unsigned long	g = (unsigned long)( 255.0f * f2 );
			unsigned long	b = (unsigned long)( 255.0f * f );

			color = CColor( r, g, b );
		}
		break;
	case CVariantData::T_INTEGER:
		{
			unsigned long	f = vControl.GetValueUnsignedInteger();
			unsigned long	f1 = vLeft.GetValueUnsignedInteger();
			unsigned long	f2 = vRight.GetValueUnsignedInteger();

			color = CColor( f1, f2, f );
		}
		break;
	default:
		color = CColor::ErrorColor();
		break;
	}

	return CVariantData( color );
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
		CEquationOperatorRGB::Clone
		(
		void
		)
{
	return new CEquationOperatorRGB( *this );
}


}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
