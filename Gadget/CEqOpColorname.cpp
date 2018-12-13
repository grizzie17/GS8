/*---------------------------------------------------------------------+\
|
|	CEqOpColorname.cpp  --  brief description of what CEqOpColorname.cpp is for
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
	13-Dec-2009			J.Griswold		(Reviewed by: R.Hosea)
		Initial Revision
|
\+---------------------------------------------------------------------*/
/*---------------------------------------------------------------------+\
|																		|
|	Include Files														|
|																		|
\+---------------------------------------------------------------------*/
#include "stdafx.h"
#include "CEqOpColorname.h"

#include "CColor.h"
#include "CCharString.h"
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

 * CEquationOperatorColorname - constructor

\+---------------------------------------------------------------------*/
CEquationOperatorColorname::CEquationOperatorColorname
		(
		void
		)
		: VEquationOperatorUnary()
{
}

/*---------------------------------------------------------------------+\

 * CEquationOperatorColorname - copy constructor

\+---------------------------------------------------------------------*/
CEquationOperatorColorname::CEquationOperatorColorname
		(
		ConstCEquationOperatorColornameRef	r
		)
		: VEquationOperatorUnary( r )
{
	// handled by base class
}

/*---------------------------------------------------------------------+\

 * ~CEquationOperatorColorname - destructor

\+---------------------------------------------------------------------*/
CEquationOperatorColorname::~CEquationOperatorColorname
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
CEquationOperatorColornameRef
		CEquationOperatorColorname::operator=
		(
		ConstCEquationOperatorColornameRef
		)
{
	// TODO: add instructions to copy data "r" to "this"
	return *this;
}

/*---------------------------------------------------------------------+\

 * GetValue -

\+---------------------------------------------------------------------*/
CVariantData
		CEquationOperatorColorname::GetValue
		(
		VDictionaryPtr	pDict
		)
{
	CVariantData	vResult;
	CVariantData	vOperand( m_pOperand->GetValue( pDict ) );

	CVariantData::V_TYPE	t = vOperand.GetType();

	if ( CVariantData::T_STRING == t )
	{
		CCharString	s = vOperand;
		CColor		c = CColor::ColorFromName( s );

		vResult = c;
	}
	else if ( CVariantData::T_COLOR == t )
	{
		vResult = vOperand;
	}
	else if ( CVariantData::T_INTEGER == t )
	{
		unsigned long	n = vOperand.GetValueUnsignedInteger();
		unsigned long	r;
		unsigned long	g;
		unsigned long	b;
		//long	a;

		r = (n & 0x00FF0000) >> 16;
		g = (n & 0x0000FF00) >> 8;
		b = (n & 0x000000FF);
		//a = ((n & 0xFF000000) >> 24) & 0x00FF;

		CColor	c( r, g, b );
		vResult = c;
	}
	else
	{
		CColor	c = CColor::ErrorColor();

		vResult = c;
	}


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
		CEquationOperatorColorname::Clone
		(
		void
		)
{
	return new CEquationOperatorColorname( *this );
}



}}

/*---------------------------------------------------------------------+\

 * someFunction -

\+---------------------------------------------------------------------*/
