/*---------------------------------------------------------------------+\
|
|	CEqOpRGBA.cpp  --  Select from list of items
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

#include "CEqOpRGBA.h"

#include "CColor.h"
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

 * CEquationOperatorRGBA - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRGBA::CEquationOperatorRGBA
		(
		void
		)
		: VEquationOperatorQuaternary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorRGBA - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorRGBA::CEquationOperatorRGBA
		(
		ConstCEquationOperatorRGBARef	r
		)
		: VEquationOperatorQuaternary( r )
{
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorRGBA - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorRGBA::~CEquationOperatorRGBA
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
CEquationOperatorRGBARef
		CEquationOperatorRGBA::operator=
		(
		ConstCEquationOperatorRGBARef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
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

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorRGBA::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CColor	color;
	CVariantData	vOperand1( m_pOperand1->GetValue( pDict ) );
	CVariantData	vOperand2( m_pOperand2->GetValue( pDict ) );
	CVariantData	vOperand3( m_pOperand3->GetValue( pDict ) );
	CVariantData	vOperand4( m_pOperand4->GetValue( pDict ) );

	CVariantData::V_TYPE	tOperand1 = vOperand1.GetType();
	CVariantData::V_TYPE	tOperand2 = vOperand2.GetType();
	CVariantData::V_TYPE	tOperand3 = vOperand3.GetType();
	CVariantData::V_TYPE	tOperand4 = vOperand4.GetType();


	if ( CVariantData::T_INTEGER == tOperand1
			&&	CVariantData::T_INTEGER == tOperand2
			&&	CVariantData::T_INTEGER == tOperand3
			&&	CVariantData::T_INTEGER == tOperand4 )
	{
		unsigned long	r = vOperand1;
		unsigned long	g = vOperand2;
		unsigned long	b = vOperand3;
		unsigned long	a = vOperand4;

		color = CColor( r, g, b, a );
	}
	else if ( CVariantData::T_FLOAT == tOperand1
			||	CVariantData::T_FLOAT == tOperand2
			||	CVariantData::T_FLOAT == tOperand3
			||	CVariantData::T_FLOAT == tOperand4 )
	{
		GFLOAT	fr = vOperand1;
		GFLOAT	fg = vOperand2;
		GFLOAT	fb = vOperand3;
		GFLOAT	fa = vOperand4;

		unsigned long	r = (unsigned long)( 255.0f * fr );
		unsigned long	g = (unsigned long)( 255.0f * fg );
		unsigned long	b = (unsigned long)( 255.0f * fb );
		unsigned long	a = (unsigned long)( 255.0f * fa );

		color.SetRGBA( r, g, b, a );
	}
	else
	{
		color = CColor::ErrorColor();
	}

	return CVariantData( color );
}

/*---------------------------------------------------------------------+\

 * Clone - make a copy of this

\+---------------------------------------------------------------------*/
VEquationPtr
		CEquationOperatorRGBA::Clone
		(
		void
		)
{
	return new CEquationOperatorRGBA( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
